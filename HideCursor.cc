#include <nan.h>
#include <iostream>

#ifdef IS_MAC
#include <Carbon/Carbon.h>
#include <AppKit/AppKit.h>
#define NOT_HIDECURSOR_KEY "Menubar"
#endif

#ifdef IS_WINDOWS
#include <Windows.h>
#endif

NAN_METHOD(hide);
NAN_METHOD(show);

// Example with node ObjectWrap
// Based on https://nodejs.org/api/addons.html#addons_wrapping_c_objects but using NAN
class HideCursor : public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(Init);

  private:
    explicit HideCursor();
    ~HideCursor();

    static NAN_METHOD(New);
    static Nan::Persistent<v8::Function> constructor;
};

Nan::Persistent<v8::Function> HideCursor::constructor;

NAN_MODULE_INIT(HideCursor::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("HideCursor").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("HideCursor").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

HideCursor::HideCursor() {
}

HideCursor::~HideCursor() {
}

NAN_METHOD(HideCursor::New) {
  if (info.IsConstructCall()) {
    HideCursor *obj = new HideCursor();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } 
  else {
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = {info[0]};
    v8::Local<v8::Function> cons = Nan::New(constructor);
    info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
  }
}

using v8::FunctionTemplate;


NAN_METHOD(hide) {
  #ifdef IS_MAC
    [NSCursor hide];
  #endif

  #ifdef IS_WINDOWS
    CURSORINFO cursor_info = {sizeof(CURSORINFO)};

    if (GetCursorInfo(&cursor_info) && cursor_info.flags == 1) {
      // std::cout << "hide\n";
      while(ShowCursor(false)>=0);
    }
    // else
    // {
    //     std::cout << "Win32 error: " << GetLastError() << std::endl; // GetCursorInfo function failed
    // }

  #endif
}

NAN_METHOD(show) {
  #ifdef IS_MAC
    [NSCursor unhide];
    [NSCursor unhide];
    [NSCursor unhide];
  #endif

  #ifdef IS_WINDOWS
    CURSORINFO cursor_info = {sizeof(CURSORINFO)};

    if (GetCursorInfo(&cursor_info) && cursor_info.flags == 0) {
      // std::cout << "show\n";
      while(ShowCursor(true)<=0);
    }
    // else
    // {
    //   std::cout << "Win32 error: " << GetLastError() << std::endl; // GetCursorInfo function failed
    // }
  #endif
}

NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, Nan::New("hide").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(hide)).ToLocalChecked());
  Nan::Set(target, Nan::New("show").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(show)).ToLocalChecked());

  // Passing target down to the next NAN_MODULE_INIT
  HideCursor::Init(target);
}

#if NODE_MAJOR_VERSION >= 10
NAN_MODULE_WORKER_ENABLED(HideCursor, InitAll);
#else
NODE_MODULE(HideCursor, InitAll);
#endif