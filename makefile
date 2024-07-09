# World VTT
#
# Copyright (C) 2024, Asar Miniatures
# All rights reserved.
#
# This file is part of the [Project Name] project. It may be used, modified,
# and distributed under the terms specified by the copyright holder.

PWD ?= $(shell pwd)

ifeq ($(V),1)
Q :=
else
Q ?= @
endif

GCC = clang++-18
USER_DIR=./test_src

TARGET_NAME := app
prof: TARGET_NAME := prof_app

GTEST_DIR=./libs/googletest/googletest
CPPFLAGS_PROD := 
prof: CPPFLAGS_PROD += -pg
CPPFLAGS_PROD += -g 
CPPFLAGS_PROD += -isystem 
CPPFLAGS_PROD += -Wall 
CPPFLAGS_PROD += -pedantic
CPPFLAGS_PROD += -pthread 
CPPFLAGS_PROD += -std=c++20
CPPFLAGS_PROD += -fpermissive


CXXFLAGS := -g -Wall -Wextra -pthread
CPPFLAGS_TEST := -g -Wall -Wextra -pthread -isystem $(GTEST_DIR)/include


SOURCES_C := 

SOURCES_CPP := 
SOURCES_CPP += main.cpp
SOURCES_CPP += logger.cpp

OBJS := 
OBJS += $(SOURCES_C:%.c=%.o)
OBJS += $(SOURCES_CPP:%.cpp=%.o)

TEST_SOURCES_C :=
TEST_SOURCES_CPP := test_logger.cpp
TEST_SOURCES_CPP += logger.cpp

TEST_OBJS :=
TEST_OBJS += $(TEST_SOURCES_CPP:%.cpp=%.o)
TEST_OBJS += $(TEST_SOURCES_C:%.c=%.o)

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

INCLUDES :=
test: INCLUDES += libs/googletest/googletest/include/gtest/internal/
test: INCLUDES += libs/googletest/googletest/include/
INCLUDES += .
INCLUDES_PARAMS=$(foreach d, $(INCLUDES), -I"${PWD}/$d")

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

.setup:
	wget https://apt.llvm.org/llvm.sh
	chmod 777 llvm.sh
	./llvm.sh
	rm llvm.sh

gtest-all.o : $(GTEST_SRCS_)
	@echo 'Build file: $< -> $@'
	$(Q)$(GCC) $(CPPFLAGS_TEST) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	@echo 'Build file: $< -> $@'
	$(Q)$(GCC) $(CPPFLAGS_TEST) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

clean:
	@echo 'Clean'
	${Q}rm -rf test_exe
	${Q}rm -rf prof_app
	${Q}rm -rf *.txt
	${Q}rm -rf $(TARGET_NAME)
	${Q}rm -rf gmon.out
	${Q}find . -name "*.o" | xargs -r rm 
	
%.o : %.cpp
	@echo 'Build object file: $< -> $@'
	$(Q)$(GCC) $(CPPFLAGS_PROD) $(INCLUDES_PARAMS) -c -o "$@" "$<"

%.o: %.c
	@echo 'Build file: $< -> $@'
	$(Q)$(GCC) $(CPPFLAGS_PROD) $(INCLUDES_PARAMS) -c -o "$@" "$<"
	

test_filter: $(TEST_OBJS) gtest-all.o gtest_main.o 
	@echo 'Build file: test_main'
	$(Q)$(GCC) $(CPPFLAGS_PROD) $(INCLUDES_PARAMS) $^ -o test_exe
	./test_exe --gtest_filter=$(FILTER)
	
test: $(TEST_OBJS) gtest-all.o gtest_main.o 
	@echo 'Build file: test_main'
	$(Q)$(GCC) $(CPPFLAGS_PROD) $(INCLUDES_PARAMS) $^ -o test_exe 
	./test_exe --gtest_catch_exceptions=0

build: clean $(OBJS) 
	@echo 'Build executable file: $(TARGET_NAME)'
	$(Q)$(GCC) $(CPPFLAGS_PROD) $(INCLUDES_PARAMS) $(OBJS) -o $(TARGET_NAME) 

run: build
	@echo 'Exe file: $(TARGET_NAME)'
	$(Q)./$(TARGET_NAME)

prof: build
	@echo "Prof: $(TARGET_NAME)"
	$(Q)./$(TARGET_NAME) 
	$(Q)gprof ./$(TARGET_NAME) gmon.out > analysis.txt


valgrind: build
	@echo "Valgrind: $(TARGET_NAME)"
	$(Q) valgrind --tool=massif ./$(TARGET_NAME)

all: test_exe app
	$(Q)./test_exe --gtest_output=xml
