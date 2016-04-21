
################################# SETTINGS #####################################

# Specify the target architecture for which the system will be built
ARCH:=x86_64

# release and version numbers. */
OS_RELEASE:= "0"
OS_VERSION:= "0"
OS_NAME   := ""

# System application options
_SYS_APPLICATION:=0

# DESKTOP  0
# SERVER   1
# MOBILE   2
# EMBEDDED 3

_REAL_TIME:= 0	# build specifically for realtime system

DEBUG:= 1

######################### AUTOMATIC CONFIGURATIONS #############################

MODULES :=
CFLAGS  := -std=c11
CCF32   := -std=c11
CPPFLAGS:=

CWARNINGS:=	-Wall -Wextra -pedantic \
	-Wmissing-prototypes -Wstrict-prototypes -Wmissing-declarations \
	-Wredundant-decls -Wnested-externs -Wshadow \
	-Wpointer-arith -Wcast-align \
	-Wuninitialized -Wmaybe-uninitialized \
	-Winline -Wno-long-long \
	-Wwrite-strings #-Wconversion

##################### ARCHITECTURE SPECIFIC SETTINGS

ifeq ($(ARCH), x86_64)
AR     :=$(ARCH)-elf-ar
AS     :=nasm
CC     :=$(ARCH)-elf-gcc
CPP    :=$(ARCH)-elf-g++

CC32:= i686-elf-gcc
ASF32:= -f elf32
ASF64:= -f elf64

MODULES += stage32

else ifeq ($(ARCH), aarch64)

endif

#################### BUILD CASE

ifeq ($DEBUG, 1)

CFLAGS+=-g -DDEBUG $(CWARNINGS)
CCF32 +=-g -DDEBUG $(CWARNINGS)

else # production

endif

# PROGRAMS

INSTALL:= install
SHELL  := /bin/bash

# PATHS

PREFIX=./iso

CFGDIR:=${PREFIX}/cfg
DOCDIR:=${PREFIX}/doc
EXEDIR:=${PREFIX}/exe
LIBDIR:=${PREFIX}/lib
HDRDIR:=$(PREFIX)/headers


