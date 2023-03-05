#include "parser.h"
#include <stdarg.h>
#include <stdio.h>

Parser::Expr::Error::Error(const char *message, ...) {
  va_list args;

  va_start(args, message);
  vsnprintf(m_message, sizeof(m_message), message, args);
  va_end(args);
}

enum TokenID { TOK_END, TOK_NUMBER, TOK_PLUS };

// LEXER
struct Token {
  Token *next;
  int id;
  Parser::Expr::Value number;
  const char *text;
};

struct TokenList {
  Token *first;
  Token *last;
};

static bool isDigit(char ch) {
  switch (ch) {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    return true;
  }
  return false;
}

static void emitToken(TokenList *list, TokenID id,
                      Parser::Expr::Value number = 0, const char *text = NULL) {
  Token *token = new Token;
  token->next = NULL;
  token->id = id;
  token->number = number;
  token->text = text;
  printf("[ EMIT ] \"%d\"\n", id);

  if (!list->first)
    list->first = token;
  else
    list->last->next = token;
  list->last = token;
}

static TokenList scan(const char *input) {
  TokenList list;
  list.first = NULL;
  list.last = NULL;

  for (;;) {
    switch (*input) {
    case '+':
      ++input;
      emitToken(&list, TOK_PLUS);
      continue;
    default:
      throw Parser::Expr::Error("unexpected character '%c'.", *input);
    }
  }
}

//////////////////////////////////////////////////////////////////////
/// Parser

struct Context {
  Token *curToken;
};

static Parser::Expr *expression(Context *c);

static Parser::Expr *primaryExpression(Context *c) {
  Parser::Expr *result;

  switch (c->curToken->id) {
  case TOK_PLUS:
    result = expression(c);
    return result;
  default:
    throw Parser::Expr::Error("syntax error in expression.");
  }
}

static Parser::Expr *expression(Context *c) {
#define NEXT primaryExpression
  return NEXT(c);
#undef NEXT
}

Parser::Expr *Parser::Expr::parse(const char *input) {
  TokenList list = scan(input);

  Context c;
  c.curToken = list.first;

  Parser::Expr *result = expression(&c);
  return result;
}
