/*
 * Copyright 2011 Christoph Bumiller
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "nv50_ir.h"
#include "nv50_ir_target.h"

namespace nv50_ir {

// Converts nv50 IR generated from TGSI to SSA form.

// DominatorTree implements an algorithm for finding immediate dominators,
// as described by T. Lengauer & R. Tarjan.
class DominatorTree : public Graph
{
public:
   DominatorTree(Graph *cfg);
   ~DominatorTree() { }
   
   bool dominates(BasicBlock *, BasicBlock *);

   void findDominanceFrontiers();

private:
   void build();
   void buildDFS(Node *);

   void squash(int);
   inline void link(int, int);
   inline int eval(int);

   void debugPrint();

   Graph *cfg;

   Node **vert;
   int *data;
   const int count;

   #define SEMI(i)     (data[(i) + 0 * count])
   #define ANCESTOR(i) (data[(i) + 1 * count])
   #define PARENT(i)   (data[(i) + 2 * count])
   #define LABEL(i)    (data[(i) + 3 * count])
   #define DOM(i)      (data[(i) + 4 * count])
};

void DominatorTree::debugPrint()
{
   for (int i = 0; i < count; ++i) {
      INFO("SEMI(%i) = %i\n", i, SEMI(i));
      INFO("ANCESTOR(%i) = %i\n", i, ANCESTOR(i));
      INFO("PARENT(%i) = %i\n", i, PARENT(i));
      INFO("LABEL(%i) = %i\n", i, LABEL(i));
      INFO("DOM(%i) = %i\n", i, DOM(i));
   }
}

DominatorTree::DominatorTree(Graph *cfgraph) : cfg(cfgraph),
                                               count(cfg->getSize())
{
   Iterator *iter;
   int i;

   vert = new Node * [count];
   data = new int[5 * count];

   for (i = 0, iter = cfg->iteratorDFS(true); !iter->end(); iter->next(), ++i) {
      vert[i] = reinterpret_cast<Node *>(iter->get());
      vert[i]->tag = i;
      LABEL(i) = i;
      SEMI(i) = ANCESTOR(i) = -1;
   }
   cfg->putIterator(iter);

   build();

   delete[] vert;
   delete[] data;
}

void DominatorTree::buildDFS(Graph::Node *node)
{
   SEMI(node->tag) = node->tag;

   for (Graph::EdgeIterator ei = node->outgoing(); !ei.end(); ei.next()) {
      if (SEMI(ei.getNode()->tag) < 0) {
         buildDFS(ei.getNode());
         PARENT(ei.getNode()->tag) = node->tag;
      }
   }
}

void DominatorTree::squash(int v)
{
   if (ANCESTOR(ANCESTOR(v)) >= 0) {
      squash(ANCESTOR(v));

      if (SEMI(LABEL(ANCESTOR(v))) < SEMI(LABEL(v)))
         LABEL(v) = LABEL(ANCESTOR(v));
      ANCESTOR(v) = ANCESTOR(ANCESTOR(v));
   }
}

int DominatorTree::eval(int v)
{
   if (ANCESTOR(v) < 0)
      return v;
   squash(v);
   return LABEL(v);
}

void DominatorTree::link(int v, int w)
{
   ANCESTOR(w) = v;
}

void DominatorTree::build()
{
   DLList *bucket = new DLList[count];
   Node *nv, *nw;
   int p, u, v, w;

   buildDFS(cfg->getRoot());

   for (w = count - 1; w >= 1; --w) {
      nw = vert[w];
      assert(nw->tag == w);
      for (Graph::EdgeIterator ei = nw->incident(); !ei.end(); ei.next()) {
         nv = ei.getNode();
         v = nv->tag;
         u = eval(v);
         if (SEMI(u) < SEMI(w))
            SEMI(w) = SEMI(u);
      }
      p = PARENT(w);
      bucket[SEMI(w)].insert(nw);
      link(p, w);

      for (DLList::Iterator it = bucket[p].iterator(); !it.end(); it.erase()) {
         v = reinterpret_cast<Node *>(it.get())->tag;
         u = eval(v);
         DOM(v) = (SEMI(u) < SEMI(v)) ? u : p;
      }
   }
   for (w = 1; w < count; ++w) {
      if (DOM(w) != SEMI(w))
         DOM(w) = DOM(DOM(w));
   }
   DOM(0) = 0;

   insert(&BasicBlock::get(cfg->getRoot())->dom);
   do {
      p = 0;
      for (v = 1; v < count; ++v) {
         nw = &BasicBlock::get(vert[DOM(v)])->dom;;
         nv = &BasicBlock::get(vert[v])->dom;
         if (nw->getGraph() && !nv->getGraph()) {
            ++p;
            nw->attach(nv, Graph::Edge::TREE);
         }
      }
   } while (p);

   delete[] bucket;
}

#undef SEMI
#undef ANCESTOR
#undef PARENT
#undef LABEL
#undef DOM

void DominatorTree::findDominanceFrontiers()
{
   Iterator *dtIter;
   BasicBlock *bb;

   for (dtIter = this->iteratorDFS(false); !dtIter->end(); dtIter->next()) {
      EdgeIterator succIter, chldIter;

      bb = BasicBlock::get(reinterpret_cast<Node *>(dtIter->get()));
      bb->getDF().clear();

      for (succIter = bb->cfg.outgoing(); !succIter.end(); succIter.next()) {
         BasicBlock *dfLocal = BasicBlock::get(succIter.getNode());
         if (dfLocal->idom() != bb)
            bb->getDF().insert(dfLocal);
      }

      for (chldIter = bb->dom.outgoing(); !chldIter.end(); chldIter.next()) {
         BasicBlock *cb = BasicBlock::get(chldIter.getNode());

         DLList::Iterator dfIter = cb->getDF().iterator();
         for (; !dfIter.end(); dfIter.next()) {
            BasicBlock *dfUp = BasicBlock::get(dfIter);
            if (dfUp->idom() != bb)
               bb->getDF().insert(dfUp);
         }
      }
   }
   this->putIterator(dtIter);
}

// liveIn(bb) = usedBeforeAssigned(bb) U (liveOut(bb) - assigned(bb))
void
Function::buildLiveSetsPreSSA(BasicBlock *bb, const int seq)
{
   BitSet usedBeforeAssigned(allLValues.getSize(), true);
   BitSet assigned(allLValues.getSize(), true);

   bb->liveSet.allocate(allLValues.getSize(), false);

   int n = 0;
   for (Graph::EdgeIterator ei = bb->cfg.outgoing(); !ei.end(); ei.next()) {
      BasicBlock *out = BasicBlock::get(ei.getNode());
      if (out == bb)
         continue;
      if (out->cfg.visit(seq))
         buildLiveSetsPreSSA(out, seq);
      if (!n++)
         bb->liveSet = out->liveSet;
      else
         bb->liveSet |= out->liveSet;
   }
   if (!n && !bb->liveSet.marker)
      bb->liveSet.fill(0);
   bb->liveSet.marker = true;

   for (Instruction *i = bb->getEntry(); i; i = i->next) {
      for (int s = 0; i->srcExists(s); ++s)
         if (i->getSrc(s)->asLValue() && !assigned.test(i->getSrc(s)->id))
            usedBeforeAssigned.set(i->getSrc(s)->id);
      for (int d = 0; i->defExists(d); ++d)
         assigned.set(i->getDef(d)->id);
   }

   bb->liveSet.andNot(assigned);
   bb->liveSet |= usedBeforeAssigned;
}

class RenamePass
{
public:
   RenamePass(Function *);
   ~RenamePass();

   bool run();
   void search(BasicBlock *);

   inline LValue *getStackTop(Value *);

private:
   Stack *stack;
   Function *func;
   Program *prog;
   Instruction *undef;
};

bool
Program::convertToSSA()
{
   for (ArrayList::Iterator fi = allFuncs.iterator(); !fi.end(); fi.next()) {
      Function *fn = reinterpret_cast<Function *>(fi.get());
      if (!fn->convertToSSA())
         return false;
   }
   return true;
}

// XXX: add edge from entry to exit ?

// Efficiently Computing Static Single Assignment Form and
//  the Control Dependence Graph,
// R. Cytron, J. Ferrante, B. K. Rosen, M. N. Wegman, F. K. Zadeck
bool
Function::convertToSSA()
{
   // 0. calculate live in variables (for pruned SSA)
   int seq = cfg.nextSequence();
   for (unsigned i = 0; i <= loopNestingBound; seq = cfg.nextSequence(), ++i)
      buildLiveSetsPreSSA(BasicBlock::get(cfg.getRoot()), seq);

   // reset liveSet marker for use in regalloc
   for (ArrayList::Iterator bi = allBBlocks.iterator(); !bi.end(); bi.next())
      reinterpret_cast<BasicBlock *>(bi.get())->liveSet.marker = false;

   // 1. create the dominator tree
   domTree = new DominatorTree(&cfg);
   reinterpret_cast<DominatorTree *>(domTree)->findDominanceFrontiers();

   // 2. insert PHI functions
   DLList workList;
   LValue *lval;
   BasicBlock *bb;
   int var;
   int iterCount = 0;
   int *hasAlready = new int[allBBlocks.getSize() * 2];
   int *work = &hasAlready[allBBlocks.getSize()];

   memset(hasAlready, 0, allBBlocks.getSize() * 2 * sizeof(int));

   // for each variable
   for (var = 0; var < allLValues.getSize(); ++var) {
      if (!allLValues.get(var))
         continue;
      lval = reinterpret_cast<Value *>(allLValues.get(var))->asLValue();
      if (!lval || !lval->defs)
         continue;
      ++iterCount;

      // TODO: don't add phi functions for values that aren't used outside
      //  the BB they're defined in

      // gather blocks with assignments to lval in workList
      for (ValueDef::Iterator d = lval->defs->iterator(); !d.end(); d.next()) {
         bb = d.get()->getInsn()->bb;
         if (!bb)
            continue; // instruction likely been removed but not XXX deleted

         if (work[bb->getId()] == iterCount)
            continue;
         work[bb->getId()] = iterCount;
         workList.insert(bb);
      }

      // for each block in workList, insert a phi for lval in the block's
      //  dominance frontier (if we haven't already done so)
      for (DLList::Iterator wI = workList.iterator(); !wI.end(); wI.erase()) {
         bb = BasicBlock::get(wI);

         DLList::Iterator dfIter = bb->getDF().iterator();
         for (; !dfIter.end(); dfIter.next()) {
            Instruction *phi;
            BasicBlock *dfBB = BasicBlock::get(dfIter);

            if (hasAlready[dfBB->getId()] >= iterCount)
               continue;
            hasAlready[dfBB->getId()] = iterCount;

            // pruned SSA: don't need a phi if the value is not live-in
            if (!dfBB->liveSet.test(lval->id))
               continue;

            // TODO: use dedicated PhiInstruction to lift this limit
            assert(dfBB->cfg.incidentCount() <= NV50_IR_MAX_SRCS);

            phi = new_Instruction(this, OP_PHI, typeOfSize(lval->reg.size));
            dfBB->insertTail(phi);

            phi->setDef(0, lval);
            for (int s = 0; s < dfBB->cfg.incidentCount(); ++s)
               phi->setSrc(s, lval);

            if (work[dfBB->getId()] < iterCount) {
               work[dfBB->getId()] = iterCount;
               wI.insert(dfBB);
            }
         }
      }
   }
   delete[] hasAlready;

   RenamePass rename(this);
   return rename.run();
}

RenamePass::RenamePass(Function *fn) : func(fn), prog(fn->getProgram())
{
   BasicBlock *root = BasicBlock::get(func->cfg.getRoot());

   undef = new_Instruction(func, OP_NOP, TYPE_U32);
   undef->setDef(0, new_LValue(func, FILE_GPR));
   root->insertHead(undef);

   stack = new Stack[func->allLValues.getSize()];
}

RenamePass::~RenamePass()
{
   if (stack)
      delete[] stack;
}

LValue *
RenamePass::getStackTop(Value *val)
{
   if (!stack[val->id].getSize())
      return 0;
   return reinterpret_cast<LValue *>(stack[val->id].peek().u.p);
}

bool RenamePass::run()
{
   if (!stack)
      return false;
   search(BasicBlock::get(func->domTree->getRoot()));

   ArrayList::Iterator iter = func->allInsns.iterator();
   for (; !iter.end(); iter.next()) {
      Instruction *insn = reinterpret_cast<Instruction *>(iter.get());
      for (int d = 0; insn->defExists(d); ++d)
         insn->def[d].restoreDefList();
   }

   return true;
}

void RenamePass::search(BasicBlock *bb)
{
   LValue *lval;
   int d, s;
   const Target *targ = prog->getTarget();

   for (Instruction *stmt = bb->getFirst(); stmt; stmt = stmt->next) {
      if (stmt->op != OP_PHI) {
         for (s = 0; stmt->srcExists(s); ++s) {
            lval = stmt->getSrc(s)->asLValue();
            if (!lval)
               continue;
            lval = getStackTop(lval);
            if (!lval)
               lval = static_cast<LValue *>(undef->getDef(0));
            stmt->setSrc(s, lval);
         }
      }
      for (d = 0; stmt->defExists(d); ++d) {
         lval = stmt->def[d].get()->asLValue();
         assert(lval);
         stmt->def[d].setSSA(
            new_LValue(func, targ->nativeFile(lval->reg.file)));
         stmt->def[d].get()->reg.data.id = lval->reg.data.id;
         stack[lval->id].push(stmt->def[d].get());
      }
   }

   for (Graph::EdgeIterator ei = bb->cfg.outgoing(); !ei.end(); ei.next()) {
      Instruction *phi;
      int p = 0;
      BasicBlock *sb = BasicBlock::get(ei.getNode());

      // which predecessor of sb is bb ?
      for (Graph::EdgeIterator ei = sb->cfg.incident(); !ei.end(); ei.next()) {
         if (ei.getNode() == &bb->cfg)
            break;
         ++p;
      }
      assert(p < sb->cfg.incidentCount());

      for (phi = sb->getPhi(); phi && phi->op == OP_PHI; phi = phi->next) {
         lval = getStackTop(phi->getSrc(p));
         if (!lval)
            lval = undef->getDef(0)->asLValue();
         phi->setSrc(p, lval);
      }
   }

   for (Graph::EdgeIterator ei = bb->dom.outgoing(); !ei.end(); ei.next())
      search(BasicBlock::get(ei.getNode()));

   for (Instruction *stmt = bb->getFirst(); stmt; stmt = stmt->next) {
      for (d = 0; stmt->defExists(d); ++d)
         stack[stmt->def[d].preSSA()->id].pop();
   }
}

} // namespace nv50_ir
