ISTRUZIONI:

a) Installazione:
1) copia lib/LocalOptsPass.h in LLVM_SRC/llvm-project-llvmorg-17.0.6/llvm/include/llvm/Transforms/Utils/
2) Copia lib/LocalOptsPass.cpp in LLVM_SRC/llvm-project-llvmorg-17.0.6/llvm/lib/Transforms/Utils/
3) Copia lib/PassRegistry.def in LLVM_SRC/llvm-project-llvmorg-17.0.6/llvm/lib/Passes/
4) Aggiungi, in ordine alfabetico, "LocalOptsPass.cpp" al file  LLVM_SRC/llvm-project-llvmorg-17.0.6/llvm/lib/Transforms/Utils/CMakeLists.txt
5) Aggiungi "#include llvm/Transforms/Utils/LocalOptsPass.h" al file LLVM_SRC/llvm-project-llvmorg-17.0.6/llvm/lib/Passes/PassBuilder.cpp
6) Compiliamo il passo, tramite il comando "cd LLVM_BUILD && make opt"

b) Test:
è possibile testare il funzionamento del passo tramite il comando "make"
altrimenti è possibile inserire manualmente i seguenti comandi

clang -O2 -S -emit-llvm -c test/test.c -o test/test.ll
opt -S -passes=LocalOpts test/test.ll -o=test/test_optimized.ll
