#include <node.h>

#include "add.h"
#include "subtract.h"

void init(v8::Handle<v8::Object> exports) {
  NODE_SET_METHOD(exports, "add", add);
  NODE_SET_METHOD(exports, "subtract", subtract);
}

NODE_MODULE(vector, init)