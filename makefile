# Copyright (C) 2023 Grinn sp. z o.o.
#
# These computer program listings and specifications, are the property of
# Grinn sp. z o.o. and shall not be reproduced or copied or used in
# whole or in part without written permission from Grinn sp. z o.o.


PWD ?= $(shell pwd)

ifeq ($(V),1)
Q :=
else
Q ?= @
endif

GCC = g++
USER_DIR=./test_src
GTEST_DIR=./libs/googletest/googletest
CPP_FLAGS := -g -isystem -Wall -pthread -lpthread -std=c++20 -fpermissive
CXXFLAGS := -g -Wall -Wextra -pthread
CPPFLAGS := -g -Wall -Wextra -pthread -isystem $(GTEST_DIR)/include

SOURCES_C := 

SOURCES_CPP := 
SOURCES_CPP += main.cpp

OBJS := 
OBJS += $(SOURCES_C:%.c=%.o)
OBJS += $(SOURCES_CPP:%.cpp=%.o)

TEST_SOURCES_C :=
TEST_SOURCES_CPP := test_logger.cpp

TEST_OBJS :=
TEST_OBJS += $(TEST_SOURCES_CPP:%.cpp=%.o)
TEST_OBJS += $(TEST_SOURCES_C:%.c=%.o)

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

INCLUDES :=
INCLUDES += libs/googletest/googletest/include/gtest/internal/
INCLUDES += libs/googletest/googletest/include/
INCLUDES += .
INCLUDES_PARAMS=$(foreach d, $(INCLUDES), -I"${PWD}/$d")

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

gtest-all.o : $(GTEST_SRCS_)
	@echo 'Build file: $< -> $@'
	$(Q)$(GCC) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	@echo 'Build file: $< -> $@'
	$(Q)$(GCC) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

clean:
	@echo 'Clean'
	${Q}rm -rf test_exe
	${Q}rm -rf app
	${Q}find . -name "*.o" | xargs -r rm 
	
%.o : %.cpp
	@echo 'Build file: $< -> $@'
	$(Q)$(GCC) $(CPP_FLAGS) $(INCLUDES_PARAMS) -c -o "$@" "$<"

%.o: %.c
	@echo 'Build file: $< -> $@'
	$(Q)$(GCC) $(CPP_FLAGS) $(INCLUDES_PARAMS) -c -o "$@" "$<"
	

test_filter: $(TEST_OBJS) gtest-all.o gtest_main.o 
	@echo 'Build file: test_main'
	$(Q)$(GCC) $(CPP_FLAGS) $(INCLUDES_PARAMS) $^ -o test_exe
	./test_exe --gtest_filter=$(FILTER)
	
test: $(TEST_OBJS) gtest-all.o gtest_main.o 
	@echo 'Build file: test_main'
	$(Q)$(GCC) $(CPP_FLAGS) $(INCLUDES_PARAMS) $^ -o test_exe
	./test_exe

build: clean $(OBJS) 
	@echo 'Build file: app'
	$(Q)$(GCC) $(CPP_FLAGS) $(INCLUDES_PARAMS) $(OBJS) -o app 

run: build
	@echo 'Exe file: app'
	$(Q)./app

all: test_exe app
	$(Q)./test_exe --gtest_output=xml
