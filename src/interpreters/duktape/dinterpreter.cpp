#include "dinterpreter.hpp"
#include "dobjectbuilder.hpp"
#include <string>
#include <functional>
#include <iostream>
#include <variant>

DuktapeInterpreter::DuktapeInterpreter()
{
    duk_context *ctx = duk_create_heap_default();

    this->ctx = ctx;
    if (this->ctx == NULL)
    {
        printf("Error creating interpreter.\n");
        throw std::exception();
    }
}

void ConsoleLog(FunctionBuilder *vars)
{
    bool is_null = false;
    while (!is_null)
    {
        is_null = vars->String();
    }

    auto f = [](std::vector<JSTypeVariant> v)
    {
        for (int i = v.size() - 1; i >= 0; i--)
        {
            if (auto c = std::get_if<JSString>(&v.at(i)))
            {

                std::cout << c->val;
            };
        }
        printf("\n");
    };
    vars->Build(f);
}
class file
{
public:
    static const char arg[];
};
decltype(file::arg) file::arg = "log";
void DuktapeInterpreter::Initialize()
{
    auto console = (DuktapeObjectBuilder *)this->NewObjectBuilder("console");

    console->Function<file::arg, DUK_VARARGS, ConsoleLog>();
    console->Build();
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
        printf("%s", duk_safe_to_string(ctx, -1));
        return 0;
    }
    duk_pop(this->ctx);
    return 1;
}

ObjectBuilder *DuktapeInterpreter::NewObjectBuilder(std::string name)
{
    return new DuktapeObjectBuilder(this, name);
}

DuktapeInterpreter::~DuktapeInterpreter()
{
    duk_destroy_heap(this->ctx);
}
