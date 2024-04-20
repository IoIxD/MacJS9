#include "inter.hpp"
#include <functional>
#include <tuple>

Interpreter *INTERPRETER = NULL;
int mutex = 0;

std::tuple<bool, std::vector<JSTypeVariant>> InterpreterMT(std::function<std::tuple<bool, std::vector<JSTypeVariant>>(Interpreter *)> fun)
{
    while (mutex == 1)
    {
    };
    mutex = 1;
    std::tuple<bool, std::vector<JSTypeVariant>> v = fun(INTERPRETER);
    mutex = 0;
    return v;
};

void SetGlobalInterpreter(Interpreter *val)
{
    INTERPRETER = val;
}