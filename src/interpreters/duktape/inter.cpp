#include "inter.hpp"
#include <string>

DuktapeInterpreter::DuktapeInterpreter()
{
    duk_context *ctx = duk_create_heap_default();
    this->ctx = ctx;
}

void DuktapeInterpreter::Initialize()
{
    duk_idx_t obj_idx = duk_push_object(this->ctx);

    duk_push_c_function(ctx, ConsoleLog, DUK_VARARGS);
    duk_put_prop_string(ctx, obj_idx, "log");

    duk_put_global_string(ctx, "console");
}

void DuktapeInterpreter::LoadFile(std::string path)
{
    FILE *f;
    size_t len;
    char buf[16384];

    f = fopen(path.c_str(), "rb");
    if (f)
    {
        len = fread((void *)buf, 1, sizeof(buf), f);
        fclose(f);
        duk_push_lstring(this->ctx, (const char *)buf, (duk_size_t)len);
    }
    else
    {
        duk_push_undefined(this->ctx);
    }
}

int DuktapeInterpreter::Run()
{
    if (duk_peval(this->ctx) != 0)
    {
        return 0;
    }
    duk_pop(this->ctx);
    return 1;
}

DuktapeInterpreter::~DuktapeInterpreter()
{
    duk_destroy_heap(this->ctx);
}

duk_ret_t ConsoleLog(duk_context *ctx)
{
    duk_idx_t arg_num = duk_get_top(ctx);
    std::string str;

    if (arg_num >= 1)
    {
        for (int i = 0; i < arg_num; i++)
        {
            str += std::string(duk_to_string(ctx, i));
        }
        for (int i = 0; i < arg_num; i++)
        {
            duk_pop(ctx);
        }
    }

    str += "\n";
    printf("%s", str.c_str());
    duk_push_undefined(ctx);
    return 1;
}
