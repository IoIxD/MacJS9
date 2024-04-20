#include <stdio.h>
#include "main.hpp"
#include <string>

#include "interpreters/inter.hpp"

#include "interpreters/duktape/dinterpreter.hpp"

// #include <MacWindows.h>

int main(int argc, char **argv)
{
    try
    {
        Interpreter *interpreter = new DuktapeInterpreter();
        SetGlobalInterpreter(interpreter);

        interpreter->Initialize();
        interpreter->LoadFile("main.js");
        interpreter->Run();
    }
    catch (...)
    {
        auto eptr = std::current_exception();
        try
        {
            if (eptr)
                std::rethrow_exception(eptr);
        }
        catch (const std::exception &e)
        {
            std::cout << "C++ Exception: '" << e.what();
            printf("\n");
        }
    }
    printf("\n(Press Return)\n");
    getchar();
    return 0;
}
