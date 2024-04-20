#pragma once

#include "../inter.hpp"
#include "duktape.hpp"
#include "dinterpreter.hpp"
#include <optional>

class DuktapeFunctionBuilder : public FunctionBuilder
{
private:
    // required in constructor
    std::string name;

    // might not be set
    std::vector<JSTypeVariant> types = std::vector<JSTypeVariant>();
    JSFuncType2 *func = NULL;
    duk_idx_t obj;

public:
    bool PushType(JSType ty) override;
    DuktapeFunctionBuilder(std::string name);
    void Build(JSFuncType2 val) override;
};