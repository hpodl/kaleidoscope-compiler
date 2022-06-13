all:
	clang++ -g -O3 parser.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -o comp.out