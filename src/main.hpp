#pragma once

#include "duktape.h"

void PushFileAsString(duk_context *ctx, const char *filename);
// void Initialize();
// void ErrorWindow(char *str);
int main(int argc, char **argv);
duk_ret_t ConsoleLog(duk_context *ctx);