#!/bin/sh 

# psl1ght.sh
# 
#
# Created by dudu clx on 15/05/12.
# Copyright 2012 home. All rights reserved.

## Go to the build directory.
cd $BUILDDIR/psl1ght

## Compile and install.
${MAKE:-make} install-ctrl && ${MAKE:-make} && ${MAKE:-make} install
