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


using namespace llvm;

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;
static std::map<std::string, Value*> NamedValues;

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
    return ConstantFP::get(TheContext, APFloat(Val));  
  }
  Value* VariableExprAST::codegen(){
    Value* val = NamedValues[Name];
    if(!val) 
      LogErrorV("Unknown variable name");
    return val;
  }

  Value* BinaryExprAST::codegen(){
    Value *L = LHS->codegen();
    Value *R = RHS->codegen();
    if(!L || !R)
      return nullptr;

    switch(Op){
      case '+':
        return Builder.CreateFAdd(L, R, "addtmp");
      case '-':
        return Builder.CreateFSub(L, R, "subtmp");
      case '*':
        return Builder.CreateFMul(L, R, "multmp");
      case '<':
        // ult: yields true if either operand is a QNAN or op1 is less than op2
        L = Builder.CreateFCmpULT(L, R, "cmptmp");
        // unsigned int to floating point
        return Builder.CreateUIToFP(L, Type::getDoubleTy(TheContext), "booltmp");

        default:
          return LogErrorV("Invalid binary operator");
    }
  }
  
  Function* PrototypeAST::codegen(){
    std::vector<Type*> doubles(Args.size(), Type::getDoubleTy(TheContext));
    FunctionType *FT = FunctionType::get(Type::getDoubleTy(TheContext), doubles, false);
    Function *F = Function::Create(FT, Function::ExternalLinkage, Name, TheModule.get());

    unsigned Idx = 0;
    for(auto &Arg : F->args())
      Arg.setName(Args[Idx++]);

    return F;
  }
  
  Function* FunctionAST::codegen(){
    Function *function = TheModule->getFunction(Proto->getName());

    // hasn't been defined as extern
    if(!function)
      function = Proto->codegen();

    if(!function)
      return nullptr;

    // already has a body
    if(!function->empty())
      return (Function*)LogErrorV("Function cannot be redefined");

    // only 1 block in a function for now
    BasicBlock *BB = BasicBlock::Create(TheContext, "entry", function);
    Builder.SetInsertPoint(BB);

    NamedValues.clear();
    for(auto &Arg : function->args())
      NamedValues[std::string(Arg.getName())] = &Arg;

    if(Value *RetVal = Body->codegen()){
      Builder.CreateRet(RetVal);
      verifyFunction(*function);

      return function;
    }

  }

  Value* CallExprAST::codegen(){

  }

