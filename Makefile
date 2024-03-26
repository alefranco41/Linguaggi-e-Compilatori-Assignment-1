OPTIMIZER := lib/libLocalOpts.so
OBJs := $(subst .cpp,.o,$(wildcard lib/*.cpp))
LL_FILE := test/test.ll
OPTIMIZED_LL_FILE := test/test_optimized.ll
C_FILE := test/test.c

CXXFLAGS := $(shell llvm-config --cxxflags) -fPIC

all: $(OPTIMIZER) optimize

$(OPTIMIZER): $(OBJs)
	$(CXX) -dylib -shared $^ -o $@

optimize: $(C_FILE) $(OPTIMIZER)
	clang -O0 -S -emit-llvm -c $(C_FILE) -o $(LL_FILE)
	opt -load-pass-plugin=$(OPTIMIZER) -passes=local-opts -disable-output < $(LL_FILE) > $(OPTIMIZED_LL_FILE)

.PHONY: clean
clean:
	$(RM) $(OPTIMIZER) $(OBJs) $(LL_FILE) $(OPTIMIZED_LL_FILE)
