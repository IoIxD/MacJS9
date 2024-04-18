#include <stdio.h>
#include "main.hpp"
#include <string>

#include "interpreters/inter.hpp"
#include "interpreters/duktape/inter.hpp"

int main(int argc, char **argv)
{
    Interpeter *interpreter = new DuktapeInterpreter();
    interpreter->Initialize();
    interpreter->LoadFile("main.js");
    interpreter->Run();

    printf("\n(Press Return)\n");
    getchar();

    return 0;
}
