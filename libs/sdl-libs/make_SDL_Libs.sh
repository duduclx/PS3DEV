#!/bin/sh
CFLAGS="-I$PSL1GHT/ppu/include/SDL -I$PS3DEV/portlibs/ppu/include/ -I$PS3DEV/portlibs/ppu/include/freetype2"
LDFLAGS="-L$PSL1GHT/ppu/lib -L$PS3DEV/portlibs/ppu/lib -lrt -llv2"
PKG_CONFIG_PATH="$PS3DEV/portlibs/ppu/lib/pkgconfig"
export CFLAGS
export LDFLAGS
export PKG_CONFIG_PATH
for SCRIPT in scripts/*.sh; do "$SCRIPT" || { echo "$SCRIPT: Failed."; exit 1; } done

