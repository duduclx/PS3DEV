# Makefile for libopf

ifeq ($(strip $(PSL1GHT)),)
$(error "PSL1GHT is not installed. Please install PSL1GHT.")
endif

TARGET		:= libopf.a
CFILES		:= opf.c opfcmds.c
OBJS		:= ${CFILES:.c=.o}

CFLAGS		:= -Wall -O3 -std=gnu99
INCLUDES	:= -I$(PSL1GHT)/ppu/include -I$(PSL1GHT)/portlibs/ppu/include

all: $(TARGET)

install:
	cp -v $(TARGET) $(PSL1GHT)/ppu/lib
	mkdir -p $(PSL1GHT)/ppu/include/opf
	cp -v *.h $(PSL1GHT)/ppu/include/opf

clean:
	rm -f $(OBJS) $(TARGET)

%.o: %.c
	ppu-gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET): $(OBJS)
	ar rcs $(TARGET) $(OBJS)

