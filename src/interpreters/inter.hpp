#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <variant>

#include <mutex>

#include "quickjs.hpp"
using namespace quickjs;

class Interpreter
{
private:
    JSRuntime *rt;
    JSContext *ctx;

public:
    void Initialize();
    int EvalFile(std::string path);

    Interpreter();
};
