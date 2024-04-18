#pragma once

#include "../inter.hpp"
#include "duktape.h"
class DuktapeInterpreter : public Interpeter
{
private:
    duk_context *ctx;

public:
    DuktapeInterpreter();

    void Initialize() override;
    void LoadFile(std::string path) override;
    int Run() override;
    ~DuktapeInterpreter() override;
};

duk_ret_t ConsoleLog(duk_context *ctx);
