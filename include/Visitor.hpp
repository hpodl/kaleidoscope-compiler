#ifndef VISITOR_H
#define VISITOR_H

#include "ExprAST.hpp"

// TODO: remove absolute paths
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

class NumberExprAST;
class VariableExprAST;
class BinaryExprAST;
class CallExprAST;
class PrototypeAST;
class FunctionAST;

class Visitor{
public:
    virtual void visitNumberExprAST(const NumberExprAST* exp) = 0;
    virtual void visitVariableExprAST(const VariableExprAST* exp) = 0;
    virtual void visitBinaryExprAST(const BinaryExprAST* exp) = 0;
    virtual void visitCallExprAST(const CallExprAST* exp) = 0;
    virtual void visitPrototypeAST(const PrototypeAST* exp) = 0;
    virtual void visitFunctionAST(const FunctionAST* exp) = 0;
};

class CodeGenVisitor{
    // llvm::Value* gencode; 
public:
    void visitNumberExprAST(const NumberExprAST* exp);
    void visitVariableExprAST(const VariableExprAST* exp);
    void visitBinaryExprAST(const BinaryExprAST* exp);
    void visitCallExprAST(const CallExprAST* exp);
    void visitPrototypeAST(const PrototypeAST* exp);
    void visitFunctionAST(const FunctionAST* exp);
};

#endif