#include <napi.h>
#include "hashint-link.h"

// class HashInt : public Napi::Addon<HashInt> {
//     public:
//         HashInt(Napi::Env env, Napi::Object exports) {
//             DefineAddon(exports, {
//                 InstanceMethod("hashint16", &HashInt::HashInt16)
//             });
//         }

//     private:
//         Napi::Value HashInt16(const Napi::CallbackInfo &info) {
//             Napi::Env env = info.Env();
//             uint8_t err = 0;
//             if(info.Length() != 2) {
//                 Napi::Error::New(env,"Expected 2 arguments.").ThrowAsJavaScriptException();
//                 err = 1;
//             }
//             if(!info[0].IsNumber()) {
//                 Napi::TypeError::New(env,"Number expected in first argument.").ThrowAsJavaScriptException();
//                 err = 1;
//             }
//             if(!info[1].IsString()) {
//                 Napi::TypeError::New(env,"String expected in second argument.").ThrowAsJavaScriptException();
//                 err = 1;
//             }

//             uint16_t input = (uint16_t)info[0].ToNumber().Int32Value();
//             std::string secret = (std::string)info[1].ToString();
//             if(secret.length() == 0) {
//                 Napi::Error::New(env,"Expected non-empty secret key.").ThrowAsJavaScriptException();
//                 err = 1;
//             }
//             if(err)
//                 return env.Null();

//             std::string result = hashint16(input,secret);

//             return Napi::String::New(env, result);
//         }
// };

// NODE_API_ADDON(HashInt)

Napi::Value HashInt8(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    uint8_t err = 0;
    std::string secret = "";
    if(info.Length() == 0 || info.Length() > 2) {
        Napi::Error::New(env,"Expected 1 or 2 arguments.").ThrowAsJavaScriptException();
        return env.Null();
    }
    if(!info[0].IsNumber()) {
        Napi::TypeError::New(env,"Number expected in first argument.").ThrowAsJavaScriptException();
        return env.Null();
    }
    if(info.Length() > 1){
        if(!info[1].IsString()) {
            Napi::TypeError::New(env,"String expected in second argument.").ThrowAsJavaScriptException();
            return env.Null();
        } else {
            secret = (std::string)info[1].ToString();
        }
    }
    uint8_t input = (uint8_t)info[0].ToNumber().Int32Value();
    // if(secret.length() == 0) {
    //     Napi::Error::New(env,"Expected non-empty secret key.").ThrowAsJavaScriptException();
    //     return env.Null();
    // }

    std::string result = hashint8(input,secret);

    return Napi::String::New(env, result);
}

Napi::Value HashInt16(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    uint8_t err = 0;
    std::string secret = "";
    if(info.Length() == 0 || info.Length() > 2) {
        Napi::Error::New(env,"Expected 1 or 2 arguments.").ThrowAsJavaScriptException();
        return env.Null();
    }
    if(!info[0].IsNumber()) {
        Napi::TypeError::New(env,"Number expected in first argument.").ThrowAsJavaScriptException();
        return env.Null();
    }
    if(info.Length() > 1){
        if(!info[1].IsString()) {
            Napi::TypeError::New(env,"String expected in second argument.").ThrowAsJavaScriptException();
            return env.Null();
        } else {
            secret = (std::string)info[1].ToString();
        }
    }
    uint16_t input = (uint16_t)info[0].ToNumber().Int32Value();
    // if(secret.length() == 0) {
    //     Napi::Error::New(env,"Expected non-empty secret key.").ThrowAsJavaScriptException();
    //     return env.Null();
    // }

    std::string result = hashint16(input,secret);

    return Napi::String::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "hashint16"), Napi::Function::New(env, HashInt16));
    exports.Set(Napi::String::New(env, "hashint8"), Napi::Function::New(env, HashInt8));
    return exports;
}

NODE_API_MODULE(hashint, Init);
