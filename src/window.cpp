#include <node.h>
#include <windows.h>

namespace demo {

    using v8::Exception;
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Number;
    using v8::Integer;
    using v8::Undefined;
    using v8::Null;
    using v8::Function;
    using v8::Object;
    using v8::Array;
    using v8::String;
    using v8::Value;
    using v8::Context;
    using v8::Map;
    using v8::ArrayBuffer;


#define NODEERROR(str) isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate,str).ToLocalChecked()))
#define FIELD(str) String::NewFromUtf8(isolate, str).ToLocalChecked()
#define GET(filed) Get(context, FIELD(filed)).ToLocalChecked()


    void SetWindowParent(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        Local<Context> context = isolate->GetCurrentContext();

        // Check the number of arguments passed.
        if (args.Length() < 2) {
            NODEERROR("Wrong number of arguments");
            return;
        }

        auto WndChild = args[0].As<Object>();       // hwnd окна, у которого изменяем владельца
        auto WndParent = args[1].As<Object>();      // hwnd окна владельца
        if (!WndChild->IsNumber()) {
            NODEERROR("First parametr has to be type Number - hwnd child !");
            return;
        }

        if (!WndParent->IsNumber()) {
            NODEERROR("Second parametr has to be type Number - hwnd parent !");
            return;
        }

        HWND hWndParent = (HWND)(long)(WndParent.As<v8::Number>()->Value());
        HWND hWndChild  = (HWND)(long)(WndChild.As<v8::Number>()->Value());

        RECT rect{};
        GetClientRect(hWndParent, &rect);

        //SetWindowLongPtrA (handle, GWLP_HWNDPARENT, newOwner);
        //SetWindowLongPtrA (handle, GWL_STYLE, WS_CHILD | WS_VISIBLE);
        SetParent(hWndChild, hWndParent);
        SetWindowPos(hWndChild, 0, rect.left, rect.top, rect.right, rect.bottom, 0);
        SetActiveWindow(hWndChild);

        args.GetReturnValue().Set(v8::Boolean::New(isolate, TRUE));
    }

    void Add(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        Local<Context> context = isolate->GetCurrentContext();

        // Check the number of arguments passed.
        if (args.Length() < 2) {
            NODEERROR("Wrong number of arguments");
            return;
        }

        auto A = args[0].As<Object>();       // hwnd окна, у которого изменяем владельца
        auto B = args[1].As<Object>();      // hwnd окна владельца
        if (!A->IsNumber()) {
            NODEERROR("First parametr has to be type Number !");
            return;
        }

        if (!B->IsNumber()) {
            NODEERROR("Second parametr has to be type Number !");
            return;
        }

        auto a = A.As<v8::Number>()->Value();
        auto b = B.As<v8::Number>()->Value();

        args.GetReturnValue().Set(v8::Number::New(isolate, a+b));
    }



    void Init(Local<Object> exports) {
        NODE_SET_METHOD(exports, "SetWindowParent", SetWindowParent);
        NODE_SET_METHOD(exports, "Add", Add);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, Init)

}  // name