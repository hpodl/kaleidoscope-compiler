#ifndef PARSER_HPP
#define PARSER_HPP
#include "ExprAST.hpp"
#include "Parser.cpp"

static std::unique_ptr<ExprAST> ParseExpression();
/// GetTokPrecedence - Get the precedence of the pending binary operator token.
static int GetTokPrecedence();

/// LogError* - These are little helper functions for error handling.
std::unique_ptr<ExprAST> LogError(const char *Str);
std::unique_ptr<PrototypeAST> LogErrorP(const char *Str);

/// numberexpr ::= number
static std::unique_ptr<ExprAST> ParseNumberExpr();

/// parenexpr ::= '(' expression ')'
static std::unique_ptr<ExprAST> ParseParenExpr();

/// identifierexpr
///   ::= identifier
///   ::= identifier '(' expression* ')'
static std::unique_ptr<ExprAST> ParseIdentifierExpr();

/// primary
///   ::= identifierexpr
///   ::= numberexpr
///   ::= parenexpr
static std::unique_ptr<ExprAST> ParsePrimary();

/// binoprhs
///   ::= ('+' primary)*
static std::unique_ptr<ExprAST> ParseBinOpRHS(
    int ExprPrec, std::unique_ptr<ExprAST> LHS);

/// expression
///   ::= primary binoprhs
///
static std::unique_ptr<ExprAST> ParseExpression();

/// prototype
///   ::= id '(' id* ')'
static std::unique_ptr<PrototypeAST> ParsePrototype();

/// definition ::= 'def' prototype expression
static std::unique_ptr<FunctionAST> ParseDefinition();

/// toplevelexpr ::= expression
static std::unique_ptr<FunctionAST> ParseTopLevelExpr();

/// external ::= 'extern' prototype
static std::unique_ptr<PrototypeAST> ParseExtern();

#endif