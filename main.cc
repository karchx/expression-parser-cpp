#include "parser.h"
#include <stdio.h>

static void check(const char *input) {
  try {
    Parser::Expr::parse(input);
  } catch(const Parser::Expr::Error &e) {
    printf("[ FAIL ] \"%s\" unexpected error: %s\n", input, e.message());
  }
}

auto main() -> int {
  check("+");
  return 0;
}
