#ifndef PARSER_H_
#define PARSER_H_

#include <stddef.h>
#include <stdint.h>

namespace Expr {
typedef int Value;
typedef unsigned int UnsignedValue;

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
}; // namespace Expr

#endif
