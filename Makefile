##===- projects/sample/Makefile ----------------------------*- Makefile -*-===##
#
# This is a sample Makefile for a project that uses LLVM.
#
##===----------------------------------------------------------------------===##

#
# Indicates our relative path to the top of the project's root directory.
#
LEVEL = .
DIRS = lib
EXTRA_DIST = include

#
# Include the Master Makefile that knows how to build all.
#
include $(LEVEL)/Makefile.common

LIBRARYNAME = iron3men
LLVM_SRC_ROOT = /home/dong0/Work/llvm-2.8
LLVM_OBJ_ROOT = /home/dong0/Work/llvm-2.8
PROJ_SRC_ROOT = $(LLVM_SRC_ROOT)/projects/iron3men
LEVEL = .
PROJ_INSTALL_ROOT = .
SHARED_LIBRARY = 1
ENABLE_OPTIMIZE = 1
ENABLE_PROFILING = 1
include $(LLVM_OBJ_ROOT)/Makefile.config
include $(LLVM_SRC_ROOT)/Makefile.rules 

