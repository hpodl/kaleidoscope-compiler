all:
	clang++ -g -O3 compiler.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -o comp.out