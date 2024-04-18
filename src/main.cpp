#include <stdio.h>
#include "duktape.h"
#include "main.hpp"
#include <string>

int main(int argc, char **argv)
{
    duk_context *ctx = duk_create_heap_default();

    duk_idx_t obj_idx = duk_push_object(ctx);

    duk_push_c_function(ctx, ConsoleLog, DUK_VARARGS);
    duk_put_prop_string(ctx, obj_idx, "log");

    duk_put_global_string(ctx, "console");

    PushFileAsString(ctx, "main.js");
    if (duk_peval(ctx) != 0)
    {
        printf("Error: %s\n", duk_safe_to_string(ctx, -1));
        goto finished;
    }
    duk_pop(ctx); /* ignore result */
finished:
    printf("\n(Press Return)\n");
    getchar();

    duk_destroy_heap(ctx);

    return 0;
}

void PushFileAsString(duk_context *ctx, const char *filename)
{
    FILE *f;
    size_t len;
    char buf[16384];

    f = fopen(filename, "rb");
    if (f)
    {
        len = fread((void *)buf, 1, sizeof(buf), f);
        fclose(f);
        duk_push_lstring(ctx, (const char *)buf, (duk_size_t)len);
    }
    else
    {
        duk_push_undefined(ctx);
    }
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