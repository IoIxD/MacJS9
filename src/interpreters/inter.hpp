#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <variant>

#include <mutex>

class ObjectBuilder;
class FunctionBuilder;
class JSBoolean;
class JSString;
class JSNumber;
class JSNull;
class JSUndefined;
class JSArray;
class JSFunction;
class Interpreter;
using JSTypeVariant = std::variant<JSBoolean, JSString, JSNumber, JSNull, JSUndefined, JSArray, JSFunction>;

typedef void (*JSFuncType)(FunctionBuilder *vars);
using JSFuncType2 = std::function<void(std::vector<JSTypeVariant>)>;

void SetGlobalInterpreter(Interpreter *val);
/**
 * Execute a function with the global interpreter, making sure to lock it so that multiple threads can't access it at the same time. Useful for when Javascript function needs to call back to it.
 */
std::tuple<bool, std::vector<JSTypeVariant>> InterpreterMT(std::function<std::tuple<bool, std::vector<JSTypeVariant>>(Interpreter *)> fun);

enum JSType
{
    Boolean,
    String,
    Number,
    Array,
    Function
};

class JSBoolean
{
public:
    bool val;

    JSBoolean(bool v) { this->val = v; };
};

class JSString
{
public:
    std::string val;

    JSString(std::string v) { this->val = v; };
};

class JSNumber
{
public:
    float val;

    JSNumber(float v) { this->val = v; };
};

class JSNull
{
public:
    JSNull(){};
};

class JSUndefined
{
public:
    JSUndefined(){};
};

class JSFunction
{
public:
    std::function<FunctionBuilder()> val;
    JSFunction(std::function<FunctionBuilder()> v) { this->val = v; };
};

class JSArray
{
public:
    std::vector<JSTypeVariant> val;
    JSArray(std::vector<JSTypeVariant> v) { this->val = v; };
};

class ObjectBuilder
{
private:
    virtual void PushField(std::string name, JSTypeVariant ty) = 0;

public:
    virtual void Build() = 0;
    void Boolean(std::string name, bool val) { this->PushField(name, JSBoolean(val)); };
    void String(std::string name, std::string val) { this->PushField(name, JSString(val)); };
    void Number(std::string name, float val) { this->PushField(name, JSNumber(val)); };
    void Null(std::string name) { this->PushField(name, JSNull()); };
    void Undefined(std::string name) { this->PushField(name, JSUndefined()); }
    void Array(std::string name, std::vector<JSTypeVariant> val) { this->PushField(name, JSArray(val)); };

    template <std::string *name, std::vector<JSType> *types, JSFuncType *func>
    void Function();
};

class FunctionBuilder
{
public:
    virtual bool PushType(JSType ty) = 0;
    virtual void Build(JSFuncType2 val) = 0;
    bool Boolean() { return this->PushType(JSType::Boolean); };
    bool String()
    {
        return this->PushType(JSType::String);
    };
    bool Number() { return this->PushType(JSType::Number); };
    bool Array() { return this->PushType(JSType::Array); };
    bool Function() { return this->PushType(JSType::Function); }
};

class Interpreter
{
public:
    virtual void Initialize() = 0;
    virtual void LoadFile(std::string path) = 0;
    virtual int Run() = 0;
    virtual ObjectBuilder *NewObjectBuilder(std::string name) = 0;

    Interpreter(){};
    virtual ~Interpreter(){};
};

template <class... Ts>
struct overload : Ts...
{
    using Ts::operator()...;
};
template <class... Ts>
overload(Ts...) -> overload<Ts...>;
