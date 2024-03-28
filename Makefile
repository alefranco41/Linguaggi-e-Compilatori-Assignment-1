OBJs := $(subst .cpp,.o,$(wildcard lib/*.cpp))


all: optimize

optimize: $(C_FILE) $(OPTIMIZER)
	clang -O2 -S -emit-llvm -c test/test.c -o test/test.ll
	opt -S -passes=LocalOpts test/test.ll -o=test/test_optimized.ll

.PHONY: clean
clean:
	rm -f test/*.ll
