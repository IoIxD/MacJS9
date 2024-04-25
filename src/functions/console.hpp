#pragma once

#include "../interpreters/quickjs.hpp"

namespace functions
{
    namespace console
    {
        JSValue log(JSContext *ctx, JSValue this_val, int argc, JSValue *argv)
        {
            for (int i = 0; i < argc; i++)
            {
                auto st = JS_ToCString(ctx, argv[i]);
                printf("%s", st);
                if (argc >= 2)
                {
                    if (i != argc - 1)
                    {
                        printf(" ");
                    }
                }

                JS_FreeCString(ctx, st);
            }
            printf("\n");
            return JS_UNDEFINED;
        }
        JSValue warn(JSContext *ctx, JSValue this_val, int argc, JSValue *argv)
        {
            printf("\e[1;33m");
            for (int i = 0; i < argc; i++)
            {
                auto st = JS_ToCString(ctx, argv[i]);
                printf("%s", st);
                if (argc >= 2)
                {
                    if (i != argc - 1)
                    {
                        printf(" ");
                    }
                }

                JS_FreeCString(ctx, st);
            }
            printf("\e[0m\n");
            return JS_UNDEFINED;
        }

        JSValue error(JSContext *ctx, JSValue this_val, int argc, JSValue *argv)
        {
            printf("\e[1;31m");
            for (int i = 0; i < argc; i++)
            {
                auto st = JS_ToCString(ctx, argv[i]);
                printf("%s", st);
                if (argc >= 2)
                {
                    if (i != argc - 1)
                    {
                        printf(" ");
                    }
                }

                JS_FreeCString(ctx, st);
            }
            printf("\e[0m\n");

            JS_Throw(ctx, JS_NewString(ctx, "stop"));
            return JS_UNDEFINED;
        }

        void initialize_functions(JSContext *ctx)
        {
            JSValue global_obj, console, foo;

            foo = JS_NewObject(ctx);
            JS_SetPropertyStr(ctx, foo, "log",
                              JS_NewCFunction(ctx, console::log, "log", 0));
            JS_SetPropertyStr(ctx, foo, "warn",
                              JS_NewCFunction(ctx, console::warn, "warn", 0));
            JS_SetPropertyStr(ctx, foo, "error",
                              JS_NewCFunction(ctx, console::error, "error", 0));

            global_obj = JS_GetGlobalObject(ctx);
            JS_SetPropertyStr(ctx, global_obj, "console", foo);
            JS_FreeValue(ctx, global_obj);
        }

    }
}