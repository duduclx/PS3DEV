#!/bin/bash -e
# psl1ght.sh by Dan Peori (dan.peori@oopo.net)

## Go to the build directory.
cd $BUILDDIR/psl1ght

## Compile and install.
${MAKE:-make} install-ctrl && ${MAKE:-make} && ${MAKE:-make} install
