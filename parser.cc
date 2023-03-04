#include <iostream>

#include "parser.h"
#include <stdio.h>

enum TokenID { TOK_END, TOK_NUMBER, TOK_PLUS };

struct Token {
  Token *next;
  int id;
  Expr::Value number;
  const char *text;
};

auto main() -> int { return 0; }
