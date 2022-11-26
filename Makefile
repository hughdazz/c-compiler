LLVM_CONFIG?=llvm-config

ifndef VERBOSE
QUIET:=@
endif

SRC_DIR?=$(PWD)/src
BUILD_DIR?=$(PWD)/build
DEPS_DIR?=$(PWD)/deps
TARGET=c-compiler

LDFLAGS+=$(shell $(LLVM_CONFIG) --ldflags)
COMMON_FLAGS=-Wall -Wextra
CXXFLAGS+=$(COMMON_FLAGS) $(shell $(LLVM_CONFIG) --cxxflags)
CPPFLAGS+=$(shell $(LLVM_CONFIG) --cppflags) -I$(SRC_DIR)

SOURCES=$(shell find $(SRC_DIR) -name *.cpp)
OBJS = $(patsubst %.cpp,%.o, $(SOURCES))
BUILD_OBJS = $(shell find $(BUILD_DIR) -name *.o)
default: $(TARGET)


#先编译所有的cpp文件到.o文件
%.o : %.cpp
	@echo ..Compiling $*.cpp
	$(QUIET)$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $(BUILD_DIR)/$(@F) -g

#链接所有的.o文件
$(TARGET) :yacc $(OBJS) $(BUILD_OBJS)
	@echo ..Linking $@
	@echo ..CXXFLAGS $(CXXFLAGS)
	@echo ..LDFLAGS $(LDFLAGS)
	@echo ..OBJS $(BUILD_OBJS)
	$(QUIET)$(CXX) $(CXXFLAGS) $(LDFLAGS) $(BUILD_OBJS) `$(LLVM_CONFIG) --libs bitreader core support` -o $(BUILD_DIR)/$@ -g

yacc:
	@echo ..Generate flex and bison
	$(QUIET)bison -d $(SRC_DIR)/parser/yacc.y -o $(SRC_DIR)/parser/yacc.tab.c
	$(QUIET)flex -o $(SRC_DIR)/parser/lex.yy.c --header-file=$(SRC_DIR)/parser/lex.yy.h $(SRC_DIR)/parser/lex.l 

	$(QUIET)gcc -c $(SRC_DIR)/parser/yacc.tab.c -o $(BUILD_DIR)/yacc.o -g
	$(QUIET)gcc -c $(SRC_DIR)/parser/lex.yy.c -o $(BUILD_DIR)/lex.o -g
	$(QUIET)gcc -c $(DEPS_DIR)/cJSON/cJSON.c -o $(BUILD_DIR)/cJSON.o -g