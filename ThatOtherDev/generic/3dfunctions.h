#ifdef GX
	Mtx44 perspective;
	Mtx cammatrix;
	Mtx savedmatrix;
#endif

#ifdef RSX
	#include "glhProjectf.h"
	float cammodelviewmatrix[16];
	float camprojectionmatrix[16];
	float savedcammodelviewmatrix[16];
	float savedcamprojectionmatrix[16];
#endif

void set2dcamera(float top,float bottom,float left,float right){
	#ifdef OPENGL
	//disable depth test
	glDisable(GL_DEPTH_TEST);
	//setup the camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//apply the top, bottom, left and right settings
	gluOrtho2D(left,right,bottom,top);
	#endif
	#ifdef GX
	Mtx44 perspective;
	//guOrtho(Mtx44 mt,f32 t,f32 b,f32 l,f32 r,f32 n,f32 f);
	guOrtho(perspective,
		-(bottom-top)*0.5,
		(bottom-top)*0.5,
		(right-left)*0.5,
		-(right-left)*0.5,
		0.1,10);
	GX_LoadProjectionMtx(perspective, GX_PERSPECTIVE);
	guVector cam = {0.0F, 0.0F, 0.0F};
	guVector up = {0.0F, 1.0F, 0.0F};
	guVector look = {0.0F, 0.0F, 1.0F};
	Mtx cammatrix;
	guLookAt(cammatrix,&cam,&up,&look);
	guMtxApplyTrans(cammatrix,cammatrix,-(right-left)*0.5,-(bottom-top)*0.5,0);
	guMtxApplyTrans(cammatrix,cammatrix,-left,-top,0);
	GX_LoadPosMtxImm(cammatrix,GX_PNMTX3);
	GX_SetCurrentMtx(GX_PNMTX3);
	#endif
	#ifdef RSX
	realityBlendEnable(context,1);
	screenw=res.width;
	screenh=res.height;
	screena=(float)screenw/(float)screenh;
	realityViewportScale(context,
		screenw/(right-left),
		screenh/(bottom-top),
		1.f,0.f);
	realityViewportTranslate(context,
		(0.f-left)*screenw/(right-left),
		(0.f-top)*screenh/(bottom-top),
		0.f,0.f);
	#endif
}

#ifdef PS3
void draw2dquad(float posx,float posy,float sizex,float sizey,float *texturecoords,int centerandrotate,float angle){
#endif
#ifndef PS3
void draw2dquad(float posx,float posy,float sizex,float sizey,float *texturecoords,bool centerandrotate=0,float angle=0){
#endif
	#ifdef OPENGL
	if(centerandrotate==0){
		float verts[]={
			posx,		posy+sizey,
			posx+sizex,	posy+sizey,
			posx+sizex,	posy,
			posx,		posy,};
		glVertexPointer(2,GL_FLOAT,0,verts);
		glTexCoordPointer(2,GL_FLOAT,0,texturecoords);
		glDrawArrays(GL_QUADS,0,4);
	}else if(angle==0){
		sizex*=0.5f;
		sizey*=0.5f;
		float verts[]={
			posx-sizex,	posy+sizey,
			posx+sizex,	posy+sizey,
			posx+sizex,	posy-sizey,
			posx-sizex,	posy-sizey,};
		glVertexPointer(2,GL_FLOAT,0,verts);
		glTexCoordPointer(2,GL_FLOAT,0,texturecoords);
		glDrawArrays(GL_QUADS,0,4);
	}else{
		sizex*=0.5f;
		sizey*=0.5f;
		float verts[]={
			0-sizex,	0+sizey,
			0+sizex,	0+sizey,
			0+sizex,	0-sizey,
			0-sizex,	0-sizey,};
		glPushMatrix();
		glTranslatef(posx,posy,0);
		glRotatef(angle*degreesinradian,0,0,1);
		glVertexPointer(2,GL_FLOAT,0,verts);
		glTexCoordPointer(2,GL_FLOAT,0,texturecoords);
		glDrawArrays(GL_QUADS,0,4);
		glPopMatrix();
	}
	#endif
	#ifdef GX
	if(centerandrotate==0){
		float verts[]={
			posx,		posy+sizey,
			posx+sizex,	posy+sizey,
			posx+sizex,	posy,
			posx,		posy,};
		GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		for(int b=0;b<4;b++){
			GX_Position3f32(verts[b*2],verts[b*2+1],1.0f);
			GX_Color3f32(1.0f,1.0f,1.0f);
			GX_TexCoord2f32(texturecoords[b*2],texturecoords[b*2+1]);
		}
	}else if(angle==0){
		sizex*=0.5f;
		sizey*=0.5f;
		float verts[]={
			posx-sizex,	posy+sizey,
			posx+sizex,	posy+sizey,
			posx+sizex,	posy-sizey,
			posx-sizex,	posy-sizey,};
		GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		for(int b=0;b<4;b++){
			GX_Position3f32(verts[b*2],verts[b*2+1],1.0f);
			GX_Color3f32(1.0f,1.0f,1.0f);
			GX_TexCoord2f32(texturecoords[b*2],texturecoords[b*2+1]);
		}
	}else{
		angle*=-1;
		sizex*=0.5f;
		sizey*=0.5f;
		float vertsunrotated[]={
			0-sizex,	0+sizey,
			0+sizex,	0+sizey,
			0+sizex,	0-sizey,
			0-sizex,	0-sizey,};
		float verts[]={
			posx+vertsunrotated[1]*sin(angle)+vertsunrotated[0]*cos(angle),	posy+vertsunrotated[1]*cos(angle)-vertsunrotated[0]*sin(angle),
			posx+vertsunrotated[3]*sin(angle)+vertsunrotated[2]*cos(angle),	posy+vertsunrotated[3]*cos(angle)-vertsunrotated[2]*sin(angle),
			posx+vertsunrotated[5]*sin(angle)+vertsunrotated[4]*cos(angle),	posy+vertsunrotated[5]*cos(angle)-vertsunrotated[4]*sin(angle),
			posx+vertsunrotated[7]*sin(angle)+vertsunrotated[6]*cos(angle),	posy+vertsunrotated[7]*cos(angle)-vertsunrotated[6]*sin(angle),};
		GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		for(int b=0;b<4;b++){
			GX_Position3f32(verts[b*2],verts[b*2+1],1.0f);
			GX_Color3f32(1.0f,1.0f,1.0f);
			GX_TexCoord2f32(texturecoords[b*2],texturecoords[b*2+1]);
		}
	}
	#endif
	#ifdef RSX
	//realityDrawVertexBuffer(gcmContextData *context,uint32_t type,uint32_t start,uint32_t count);
	if(centerandrotate==0){
		float verts[]={
			posx,		posy+sizey,
			posx+sizex,	posy+sizey,
			posx+sizex,	posy,
			posx,		posy,};
		realityVertexBegin(context,REALITY_QUADS);{
			for(int b=0;b<4;b++){
				realityTexCoord2f(context,texturecoords[b*2],texturecoords[b*2+1]);
				realityVertex4f(context,verts[b*2],verts[b*2+1],0.0,1.0);
			}
		}
		realityVertexEnd(context);
	}else if(angle==0){
		sizex*=0.5f;
		sizey*=0.5f;
		float verts[]={
			posx-sizex,	posy+sizey,
			posx+sizex,	posy+sizey,
			posx+sizex,	posy-sizey,
			posx-sizex,	posy-sizey,};
		realityVertexBegin(context,REALITY_QUADS);{
			for(int b=0;b<4;b++){
				realityTexCoord2f(context,texturecoords[b*2],texturecoords[b*2+1]);
				realityVertex4f(context,verts[b*2],verts[b*2+1],0.0,1.0);
			}
		}
		realityVertexEnd(context);
	}else{
		angle*=-1;
		sizex*=0.5f;
		sizey*=0.5f;
		float vertsunrotated[]={
			0-sizex,	0+sizey,
			0+sizex,	0+sizey,
			0+sizex,	0-sizey,
			0-sizex,	0-sizey,};
		float verts[]={
			posx+vertsunrotated[1]*sin(angle)+vertsunrotated[0]*cos(angle),	posy+vertsunrotated[1]*cos(angle)-vertsunrotated[0]*sin(angle),
			posx+vertsunrotated[3]*sin(angle)+vertsunrotated[2]*cos(angle),	posy+vertsunrotated[3]*cos(angle)-vertsunrotated[2]*sin(angle),
			posx+vertsunrotated[5]*sin(angle)+vertsunrotated[4]*cos(angle),	posy+vertsunrotated[5]*cos(angle)-vertsunrotated[4]*sin(angle),
			posx+vertsunrotated[7]*sin(angle)+vertsunrotated[6]*cos(angle),	posy+vertsunrotated[7]*cos(angle)-vertsunrotated[6]*sin(angle),};
		realityVertexBegin(context,REALITY_QUADS);{
			for(int b=0;b<4;b++){
				realityTexCoord2f(context,texturecoords[b*2],texturecoords[b*2+1]);
				realityVertex4f(context,verts[b*2],verts[b*2+1],0.0,1.0);
			}
		}
		realityVertexEnd(context);
	}
	#endif
}

void savecammatrix(){
	#ifdef OPENGL
	glPushMatrix();
	#endif
	#ifdef GX
	guMtxCopy(cammatrix,savedmatrix);
	#endif
	#ifdef RSX
	for(int a=0;a<16;a++)savedcammodelviewmatrix[a]=cammodelviewmatrix[a];
	for(int a=0;a<16;a++)savedcamprojectionmatrix[a]=camprojectionmatrix[a];
	#endif
}

void loadcammatrix(){
	#ifdef OPENGL
	glPopMatrix();
	#endif
	#ifdef GX
	guMtxCopy(savedmatrix,cammatrix);
	GX_LoadPosMtxImm(cammatrix,GX_PNMTX3);
	#endif
	#ifdef RSX
	for(int a=0;a<16;a++)cammodelviewmatrix[a]=savedcammodelviewmatrix[a];
	for(int a=0;a<16;a++)camprojectionmatrix[a]=savedcamprojectionmatrix[a];
	#endif
}

#ifdef RSX
void multiplymatrixtocammatrix(float newmatrix[16]){
	//http://fhtr.blogspot.com/2010/02/4x4-float-matrix-multiplication-using.html
	float tempmatrix[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,};
	for(int a=0;a<16;a++)tempmatrix[a]=cammodelviewmatrix[a];
	float *a=&tempmatrix[0];
	float *b=&newmatrix[0];
	float *c=&cammodelviewmatrix[0];
	for(int i=0; i<16; i+=4)for(int j=0; j<4; j++)
		c[i+j] = b[i]*a[j] + b[i+1]*a[j+4] + b[i+2]*a[j+8] + b[i+3]*a[j+12];
}
#endif

void translatecam(float x,float y,float z){
	#ifdef OPENGL
	glTranslatef(x,y,z);
	#endif
	#ifdef GX
	guMtxApplyTrans(cammatrix,cammatrix,x,y,z);
	GX_LoadPosMtxImm(cammatrix,GX_PNMTX3);
	#endif
	#ifdef RSX
	float result[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,};
	result[3*4+0] = x;
	result[3*4+1] = y;
	result[3*4+2] = z;
	multiplymatrixtocammatrix(result);
	#endif
}

void rotatecam(float angle,float x,float y,float z){
	#ifdef OPENGL
	glRotatef(angle,x,y,z);
	#endif
	#ifdef GX
	Mtx44 rotMtx;
	guVector aboutAxis = {x,y,z};
	guMtxRotAxisDeg(rotMtx,&aboutAxis,angle);
	guMtxConcat(cammatrix,rotMtx,cammatrix);
	GX_LoadPosMtxImm(cammatrix,GX_PNMTX3);
	#endif
	#ifdef RSX
	float fcos = cos(angle*radiansindegree), fsin = sin(angle*radiansindegree);
	float result[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,};
	if(x==1){
		result[1*4+1]=fcos;
		result[2*4+1]=-fsin;
		result[1*4+2]=fsin;
		result[2*4+2]=fcos;
	}else if(y==1){
		result[0*4+0]=fcos;
		result[2*4+0]=fsin;
		result[0*4+2]=-fsin;
		result[2*4+2]=fcos;
	}else if(z==1){
		result[0*4+0]=fcos;
		result[1*4+0]=-fsin;
		result[0*4+1]=fsin;
		result[1*4+1]=fcos;
	}
	multiplymatrixtocammatrix(result);
	#endif
}

void scalecam(float x,float y,float z){
	#ifdef OPENGL
	glScalef(x,y,z);
	#endif
	#ifdef GX
	#endif
	#ifdef RSX
	float result[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,};
    result[0*4+0]=x;
    result[1*4+1]=y;
    result[2*4+2]=z;
	multiplymatrixtocammatrix(result);
	#endif
}

void set3dcamera(float posx,float posy,float posz,float xang,float yang,float zang,float fov,float aspect,float nearrange,float farrange){
	#ifdef OPENGL
	//enable depth test
	glEnable(GL_DEPTH_TEST);
	//setup the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov,aspect,nearrange,farrange);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//rotate
	rotatecam(xang*degreesinradian,1,0,0);
	rotatecam(yang*degreesinradian,0,1,0);
	rotatecam(zang*degreesinradian,0,0,1);
	//position
	translatecam(-posx,-posy,-posz);
	#endif
	#ifdef GX
	guPerspective(perspective, fov, aspect, nearrange, farrange);
	GX_LoadProjectionMtx(perspective, GX_PERSPECTIVE);
	guVector cam = {0.0F, 0.0F, 0.0F};
	guVector up = {0.0F, 1.0F, 0.0F};
	guVector look = {0.0F, 0.0F, -1.0F};
	guVector axis = {0,0,0};
	Mtx tempmatrix;
	guLookAt(cammatrix,&cam,&up,&look);
	axis.x = 1.0f;
	axis.y = 0.0f;
	axis.z = 0.0f;
	guMtxRotAxisDeg(tempmatrix,&axis,xang*degreesinradian);
	guMtxConcat(cammatrix,tempmatrix,cammatrix);
	axis.x = 0.0f;
	axis.y = 1.0f;
	axis.z = 0.0f;
	guMtxRotAxisDeg(tempmatrix,&axis,yang*degreesinradian);
	guMtxConcat(cammatrix,tempmatrix,cammatrix);
	axis.x = 0.0f;
	axis.y = 0.0f;
	axis.z = 1.0f;
	guMtxRotAxisDeg(tempmatrix,&axis,zang*degreesinradian);
	guMtxConcat(cammatrix,tempmatrix,cammatrix);	
	guMtxApplyTrans(cammatrix,cammatrix,-posx,-posy,-posz);
	GX_LoadPosMtxImm(cammatrix,GX_PNMTX3);
	GX_SetCurrentMtx(GX_PNMTX3);
	guMtxCopy(cammatrix,tempmatrix);
	#endif
	#ifdef RSX
	realityBlendEnable(context,0);
	realityDepthTestFunc(context,REALITY_ZFUNC_LESSOREQUAL);
	realityDepthWriteEnable(context,1);
	realityDepthTestEnable(context,1);
	set2dcamera(screenh,0.f,0.f,screenw);
	//diy matrix
	float tempmatrix1[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,};
	for(int a=0;a<16;a++)cammodelviewmatrix[a]=tempmatrix1[a];
	float tempmatrix2[16]={1.29904,0,0,0,0,1.73205,0,0,0,0,-1.002,-1,0,0,-2.002,0,};
	for(int a=0;a<16;a++)camprojectionmatrix[a]=tempmatrix2[a];
	//rotate
	rotatecam(xang*degreesinradian,1,0,0);
	rotatecam(yang*degreesinradian,0,1,0);
	rotatecam(zang*degreesinradian,0,0,1);
	//position
	translatecam(-posx,-posy,-posz);
	#endif
}

#ifdef PS3
void draw3dquadmesh(int vertexcount,float *verts,float *texturecoords,float *colors,float *normals){
#endif
#ifndef PS3
void draw3dquadmesh(int vertexcount,float *verts,float *texturecoords,float *colors = NULL,float *normals = NULL){
#endif
	#ifdef OPENGL
	glVertexPointer(3,GL_FLOAT,0,verts);
	glTexCoordPointer(2,GL_FLOAT,0,texturecoords);
	if(colors!=NULL)glColorPointer(3,GL_FLOAT,0,colors);
	if(normals!=NULL)glNormalPointer(GL_FLOAT,0,normals);
	glDrawArrays(GL_QUADS,0,vertexcount);
	#endif
	#ifdef GX
	GX_Begin(GX_QUADS,GX_VTXFMT0,vertexcount);	
	if(colors==NULL){
		//int a2=0,a3=0;
		for(int a=0; a<vertexcount; a++){
			GX_Position3f32(verts[a*3],verts[a*3+1],verts[a*3+2]);
			GX_Color3f32(1.0f,1.0f,1.0f);
			GX_TexCoord2f32(texturecoords[a*2],texturecoords[a*2+1]);
			//GX_Position3f32(verts[a3++],verts[a3++],verts[a3++]);
			//GX_Color3f32(1.0f,1.0f,1.0f);
			//GX_TexCoord2f32(texturecoords[a2++],texturecoords[a2++]);
		}
	}else{
		for(int a=0; a<vertexcount; a++){
			GX_Position3f32(verts[a*3],verts[a*3+1],verts[a*3+2]);
			GX_Color3f32(colors[a*3],colors[a*3+1],colors[a*3+2]);
			GX_TexCoord2f32(texturecoords[a*2],texturecoords[a*2+1]);
		}
	}
	GX_End();
	#endif
	#ifdef RSX
	int viewport[] = {0,0,screenw,screenh};
	float winpos[3*4];
	realityVertexBegin(context,REALITY_QUADS);
	for(int a=0; a<vertexcount; a+=4){
		glhProjectf(verts[a*3+0],verts[a*3+1],verts[a*3+2],&cammodelviewmatrix[0],&camprojectionmatrix[0],viewport,&winpos[0]);
		glhProjectf(verts[a*3+3],verts[a*3+4],verts[a*3+5],&cammodelviewmatrix[0],&camprojectionmatrix[0],viewport,&winpos[3]);
		glhProjectf(verts[a*3+6],verts[a*3+7],verts[a*3+8],&cammodelviewmatrix[0],&camprojectionmatrix[0],viewport,&winpos[6]);
		glhProjectf(verts[a*3+9],verts[a*3+10],verts[a*3+11],&cammodelviewmatrix[0],&camprojectionmatrix[0],viewport,&winpos[9]);
		if(winpos[2]<1.f && winpos[5]<1.f && winpos[8]<1.f && winpos[11]<1.f
		&& winpos[2]>0.f && winpos[5]>0.f && winpos[8]>0.f && winpos[11]>0.f){
			realityTexCoord2f(context,texturecoords[a*2+0],texturecoords[a*2+1]);
			realityVertex4f(context,winpos[0],winpos[1],winpos[2],1.0);
			realityTexCoord2f(context,texturecoords[a*2+2],texturecoords[a*2+3]);
			realityVertex4f(context,winpos[3],winpos[4],winpos[5],1.0);
			realityTexCoord2f(context,texturecoords[a*2+4],texturecoords[a*2+5]);
			realityVertex4f(context,winpos[6],winpos[7],winpos[8],1.0);
			realityTexCoord2f(context,texturecoords[a*2+6],texturecoords[a*2+7]);
			realityVertex4f(context,winpos[9],winpos[10],winpos[11],1.0);
		}
	}
	realityVertexEnd(context);
	#endif
}

bool polygonvisible(float x1,float y1,float x2,float y2,float x3,float y3){
	//http://cgafaq.info/wiki/2D_Polygon_Backface_Culling
	if((x1-x2)*(y3-y2)-(y1-y2)*(x3-x2)<0.f){return 1;}else{return 0;}
}

#ifdef PS3
void draw3dtrianglemesh(int vertexcount,float *verts,float *texturecoords,float *colors,float *normals){
#endif
#ifndef PS3
void draw3dtrianglemesh(int vertexcount,float *verts,float *texturecoords,float *colors = NULL,float *normals = NULL){
#endif
	#ifdef OPENGL
	glVertexPointer(3,GL_FLOAT,0,verts);
	glTexCoordPointer(2,GL_FLOAT,0,texturecoords);
	if(colors!=NULL)glColorPointer(3,GL_FLOAT,0,colors);
	if(normals!=NULL)glNormalPointer(GL_FLOAT,0,normals);
	glDrawArrays(GL_TRIANGLES,0,vertexcount);
	#endif
	#ifdef GX
	GX_Begin(GX_TRIANGLES,GX_VTXFMT0,vertexcount);	
	if(colors==NULL){
		for(int a=0; a<vertexcount; a++){
			GX_Position3f32(verts[a*3],verts[a*3+1],verts[a*3+2]);
			GX_Color3f32(1.0f,1.0f,1.0f);
			GX_TexCoord2f32(texturecoords[a*2],texturecoords[a*2+1]);
		}
	}else{
		for(int a=0; a<vertexcount; a++){
			GX_Position3f32(verts[a*3],verts[a*3+1],verts[a*3+2]);
			GX_Color3f32(colors[a*3],colors[a*3+1],colors[a*3+2]);
			GX_TexCoord2f32(texturecoords[a*2],texturecoords[a*2+1]);
		}
	}
	GX_End();
	#endif
	#ifdef RSX
	int viewport[] = {0,0,screenw,screenh};
	float winpos[3*3];
	realityVertexBegin(context,REALITY_TRIANGLES);
	for(int a=0; a<vertexcount; a+=3){
		glhProjectf(verts[a*3+0],verts[a*3+1],verts[a*3+2],&cammodelviewmatrix[0],&camprojectionmatrix[0],viewport,&winpos[0]);
		glhProjectf(verts[a*3+3],verts[a*3+4],verts[a*3+5],&cammodelviewmatrix[0],&camprojectionmatrix[0],viewport,&winpos[3]);
		glhProjectf(verts[a*3+6],verts[a*3+7],verts[a*3+8],&cammodelviewmatrix[0],&camprojectionmatrix[0],viewport,&winpos[6]);
		if(winpos[2]<1.f && winpos[5]<1.f && winpos[8]<1.f
		&& winpos[2]>0.f && winpos[5]>0.f && winpos[8]>0.f
		&& polygonvisible(winpos[0],winpos[1],winpos[3],winpos[4],winpos[6],winpos[7])){
			realityTexCoord2f(context,texturecoords[a*2+0],texturecoords[a*2+1]);
			realityVertex4f(context,winpos[0],winpos[1],winpos[2],1.0);
			realityTexCoord2f(context,texturecoords[a*2+2],texturecoords[a*2+3]);
			realityVertex4f(context,winpos[3],winpos[4],winpos[5],1.0);
			realityTexCoord2f(context,texturecoords[a*2+4],texturecoords[a*2+5]);
			realityVertex4f(context,winpos[6],winpos[7],winpos[8],1.0);
		}
	}
	realityVertexEnd(context);
	#endif
}
