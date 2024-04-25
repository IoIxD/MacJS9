#include "inter.hpp"
#include <functional>
#include <tuple>
#include <fstream>
#include <sstream>

#include "../functions/functions.hpp"

Interpreter::Interpreter()
{
    this->rt = JS_NewRuntime();
    this->ctx = JS_NewContext(this->rt);
}

void Interpreter::Initialize()
{
    functions::console::initialize_functions(this->ctx);
}

int Interpreter::EvalFile(std::string file)
{
    std::ifstream t(file);
    std::stringstream buffer;
    buffer << t.rdbuf();

    auto str = buffer.str();
    JS_Eval(this->ctx, str.c_str(), str.length(), file.c_str(), 0);

    auto ev = JS_GetException(this->ctx);
    if (!JS_IsNull(ev))
    {
        auto what = JS_ToCString(this->ctx, ev);
        std::cout << what << std::endl;
        JS_FreeCString(ctx, what);
        return 1;
    }

    return 0;
}