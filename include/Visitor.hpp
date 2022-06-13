#ifndef VISITOR_H
#define VISITOR_H

#include "ExprAST.hpp"

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