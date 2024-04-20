#pragma once

#include "../inter.hpp"
#include "duktape.hpp"

void ConsoleLog(FunctionBuilder *vars);

class DuktapeInterpreter : public Interpreter
{
public:
    duk_context *ctx;
    DuktapeInterpreter();

    void Initialize() override;
    void LoadFile(std::string path) override;
    int Run() override;
    ObjectBuilder *NewObjectBuilder(std::string name) override;
    ~DuktapeInterpreter() override;
};
