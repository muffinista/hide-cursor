#include <node.h>
#include "hidecursor.h"


namespace HideCursor {
  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::Boolean;
  using v8::Value;

  void hide(const FunctionCallbackInfo<Value>& args) {
    doHide();
  }

  void show(const FunctionCallbackInfo<Value>& args) {
    doShow();
  }

  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "hide", hide);
    NODE_SET_METHOD(exports, "show", show);
  }

  NODE_MODULE(hideCursor, init)
}  // HideCursor
