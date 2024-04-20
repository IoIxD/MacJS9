#include <string>
#include "duktape.hpp"
#include "../inter.hpp"
#include "dobjectbuilder.hpp"
#include "dfunctionbuilder.hpp"
#include <cstdio>
#include "../inter.hpp"

DuktapeObjectBuilder::DuktapeObjectBuilder(DuktapeInterpreter *interpreter, std::string name)
{
    this->interpreter = interpreter;
    this->name = name;
    this->obj = duk_push_object(this->interpreter->ctx);
};

void DuktapeObjectBuilder::PushField(std::string name, JSTypeVariant ty)
{
    auto ctx = this->interpreter->ctx;
    auto visitor = overload{
        [ctx](const JSBoolean &val)
        { duk_push_boolean(ctx, val.val); },
        [ctx](const JSString &val)
        { duk_push_string(ctx, val.val.c_str()); },
        [ctx](const JSNumber &val)
        { duk_push_number(ctx, val.val); },
        [ctx](const JSNull &val)
        { duk_push_null(ctx); },
        [ctx](const JSUndefined &val)
        { duk_push_undefined(ctx); },
        [ctx](const JSArray &val)
        { duk_push_array(ctx); }};

    duk_put_prop_string(ctx, this->obj, name.c_str());
};

void DuktapeObjectBuilder::Build()
{
    duk_put_global_string(this->interpreter->ctx, this->name.c_str());
}
