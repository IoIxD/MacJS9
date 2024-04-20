#pragma once

#include "../inter.hpp"
#include "duktape.hpp"
#include "dinterpreter.hpp"
#include "dfunctionbuilder.hpp"

template <const char *name, JSFuncType func>
duk_ret_t RealFunc(duk_context *ctx)
{
    DuktapeFunctionBuilder *builder = new DuktapeFunctionBuilder(std::string(name));
    func(builder);

    return DUK_TYPE_UNDEFINED;
}

class DuktapeObjectBuilder : public ObjectBuilder
{
private:
    DuktapeInterpreter *interpreter;
    duk_idx_t obj;
    std::string name;

public:
    DuktapeObjectBuilder(DuktapeInterpreter *interpreter, std::string name);
    void PushField(std::string name, JSTypeVariant ty) override;
    void Build() override;

    template <const char *name, int argSize, JSFuncType func>
    void Function()
    {
        auto ctx = this->interpreter->ctx;
        duk_c_function target = RealFunc<name, func>;
        duk_push_c_function(ctx, target, argSize);
        duk_put_prop_string(ctx, this->obj, name);
    };
};
