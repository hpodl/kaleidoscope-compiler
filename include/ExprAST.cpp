#include "ExprAST.hpp"

void NumberExprAST::accept(Visitor *visitor){
  visitor->visitNumberExprAST(this);
}

void VariableExprAST::accept(Visitor *visitor){
  visitor->visitVariableExprAST(this);
}

void BinaryExprAST::accept(Visitor *visitor){
  visitor->visitBinaryExprAST(this);
}

void CallExprAST::accept(Visitor *visitor){
  visitor->visitCallExprAST(this);
}

void PrototypeAST::accept(Visitor *visitor){
  visitor->visitPrototypeAST(this);
}

void FunctionAST::accept(Visitor *visitor){
  visitor->visitFunctionAST(this);
}
