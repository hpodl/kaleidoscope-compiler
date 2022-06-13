#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>


#include "/usr/include/llvm/ADT/APFloat.h"
#include "/usr/include/llvm/ADT/STLExtras.h"
#include "/usr/include/llvm/IR/BasicBlock.h"
#include "/usr/include/llvm/IR/Constants.h"
#include "/usr/include/llvm/IR/DerivedTypes.h"
#include "/usr/include/llvm/IR/Function.h"
#include "/usr/include/llvm/IR/IRBuilder.h"
#include "/usr/include/llvm/IR/LLVMContext.h"
#include "/usr/include/llvm/IR/Module.h"
#include "/usr/include/llvm/IR/Type.h"
#include "/usr/include/llvm/IR/Verifier.h"

#include "include/ExprAST.hpp"
#include "include/Lexer.hpp"
#include "include/Parser.hpp"

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder(TheContext);
static std::unique_ptr<llvm::Module> TheModule;
static std::map<std::string, llvm::Value*> NamedValues;

llvm::Value *LogErrorV(const char *str){
  LogError(str);
  return nullptr;
}

static void HandleDefinition() {
  if (ParseDefinition()) {
    fprintf(stderr, "Parsed a function definition.\n");
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

static void HandleExtern() {
  if (ParseExtern()) {
    fprintf(stderr, "Parsed an extern\n");
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

static void HandleTopLevelExpression() {
  // Evaluate a top-level expression into an anonymous function.
  if (ParseTopLevelExpr()) {
    fprintf(stderr, "Parsed a top-level expr\n");
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

/// top ::= definition | external | expression | ';'
static void MainLoop() {
  while (true) {
    fprintf(stderr, ">> ");
    switch (CurTok) {
    case tok_eof:
      return;
    case ';': // ignore top-level semicolons.
      getNextToken();
      break;
    case tok_def:
      HandleDefinition();
      break;
    case tok_extern:
      HandleExtern();
      break;
    default:
      HandleTopLevelExpression();
      break;
    }
  }
}

//===----------------------------------------------------------------------===//
// Main driver code.
//===----------------------------------------------------------------------===//

int test_syntax() {
  // Prime the first token.
  fprintf(stderr, ">> ");
  getNextToken();

  // Run the main "interpreter loop" now.
  MainLoop();

  return 0;
}

int main(){
    test_syntax();
}

  Value* NumberExprAST::codegen(){
    
  }
  Value* VariableExprAST::codegen(){}
  Value* BinaryExprAST::codegen(){}
  Value* CallExprAST::codegen(){}
  Value* PrototypeAST::codegen(){}
  Value* FunctionAST::codegen(){}

