#ifndef PARSER_H_
#define PARSER_H_

#include <stddef.h>
#include <stdint.h>

namespace Parser {
class Expr {
public:
  typedef int Value;
  typedef unsigned int UnsignedValue;

  class Error {
  public:
    Error(const char *message, ...);
    const char *message() const { return m_message; };

  private:
    char m_message[2048];
  };

  struct ValuePtr {
    Value (*readValue)(void);
    const void *ptr;
    size_t sizeInBytes;
  };

  class Resolver {
  public:
    virtual ~Resolver() {}
    virtual bool resolverVariable(const char *name, ValuePtr &result) {
      (void)name;
      (void)result;
      return false;
    }
  };

  virtual ~Expr(){};
  static Expr *parse(const char *input);
};
}; // namespace Parser

#endif
