#include <functional>
#include <tuple>
#include <iostream>
#include "../inter.hpp"
#include "duktape.hpp"
#include "dinterpreter.hpp"
#include "dfunctionbuilder.hpp"

DuktapeFunctionBuilder::DuktapeFunctionBuilder(std::string name)
{
    this->name = name;
};

bool DuktapeFunctionBuilder::PushType(JSType ty)
{
    auto v = InterpreterMT(std::function(
        [ty](Interpreter *inter)
        {
            auto interpreter = (DuktapeInterpreter *)inter;
            auto types = std::vector<JSTypeVariant>();

            auto ctx = interpreter->ctx;

            int t = duk_get_top_index(ctx);

            switch (ty)
            {
            case JSType::Boolean:
                types.push_back(JSBoolean(duk_to_boolean(ctx, t)));
                break;

            case JSType::String:
            {
                std::string you = duk_to_string(ctx, t);
                auto fuck = JSString(you);
                types.push_back(fuck);
                break;
            }

            case JSType::Number:
                types.push_back(JSNumber(duk_to_number(ctx, t)));
                break;

                /* case JSType::Array:
                 {
                     std::vector<JSTypeVariant> vec = std::vector<JSTypeVariant>();

                     duk_size_t outerArraySize = duk_get_length(ctx, t);

                     // Loop through the outer array.
                     for (duk_size_t outerIndex = 0; outerIndex < outerArraySize; ++outerIndex)
                     {
                         // Get the property at [outerIndex] of the outer array (still) at
                         // stack index 0.
                         // This function puts the property at the top of the stack, at index -1.
                         // We'll pop it later when finished.
                         duk_get_prop_index(ctx, 0, outerIndex);

                         // Now it gets a little more complicated. This time, we use the property at the top
                         // of the stack, at index -1, which is the inner array.
                         // First, we have to get its size.
                         // Note that this function merely returns a value; it does not change the stack.
                         duk_size_t innerArraySize = duk_get_length(ctx, -1);

                         // Loop through the inner array.
                         for (duk_size_t innerIndex = 0; innerIndex < innerArraySize; ++innerIndex)
                         {
                             // Just like before, we get the property at [innerIndex] of the inner array
                             // at index -1.
                             // This puts the property at the top of the stack, so we'll need to pop it
                             // when finished.
                             duk_get_prop_index(ctx, -1, innerIndex);

                             auto dukType = duk_get_type(ctx, -1);
                             switch (dukType)
                             {
                             case DUK_TYPE_BOOLEAN:
                                 vec.push_back(JSBoolean(duk_to_boolean(ctx, -1)));
                                 break;
                             case DUK_TYPE_STRING:
                                 vec.push_back(JSString(duk_to_string(ctx, -1)));
                                 break;
                             case DUK_TYPE_NUMBER:
                                 vec.push_back(JSNumber(duk_to_number(ctx, -1)));
                                 break;
                             case DUK_TYPE_NULL:
                                 vec.push_back(JSNull());
                                 break;
                             case DUK_TYPE_UNDEFINED:
                                 vec.push_back(JSUndefined());
                                 break;
                             }

                             // Pop the inner array's property off the stack; now, the inner array will be
                             // back at the top of the stack, at index -1.
                             duk_pop(ctx);
                         }

                         // Pop the property that we got earlier using duk_get_prop_index(); now, the
                         // outer array will be back at the top of the stack, at index -1.
                         duk_pop(ctx);
                     }
                     types.push_back(JSArray(vec));

                     break;
                 }
                 case JSType::Function:
                     duk_throw(ctx);
                     break;
     */
            default:
                break;
            }
        skip:
            auto ret = std::tuple(duk_is_null(ctx, t) || duk_get_top_index(ctx) == 0, types);

            duk_pop(ctx);
            return ret;
        }));
    this->types.push_back(std::get<1>(v).at(0));
    return std::get<0>(v);
}

void DuktapeFunctionBuilder::Build(JSFuncType2 func)
{
    func(this->types);
};
