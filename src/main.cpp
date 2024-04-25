#include <stdio.h>
#include <string>

#include "interpreters/inter.hpp"
typedef void *(*start_proc)(void *, const void *, const void *);

typedef void (*switch_proc)(void *);

struct parameter_block
{
    start_proc start;
    void *param;

    switch_proc switch_in;
    switch_proc switch_out;

    const void *stack_bottom;
    const void *stack_limit;
};

// #include <MacWindows.h>
#include <Threads.h>

static void *other_thread_entry(void *, const void *, const void *)
{
    printf("fuck\n");
}

static void *thread_entry(void *arg)
{
    try
    {
        Interpreter *interpreter = new Interpreter();

        interpreter->Initialize();
        interpreter->EvalFile("main.js");
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
            std::cout << "C++ Exception: '" << e.what() << "'\n";
        }
    }
    printf("\n(Press Return)\n");
    getchar();
    return NULL;
}

int main(int argc, char **argv)
{
    /*::Size stack_size = 0;

    printf("GetDefaultThreadStackSize\n");
    OSStatus err = GetDefaultThreadStackSize(kCooperativeThread, &stack_size);
    if (err)
    {
        printf("Error trying to get default thread size: %d\n", err);
        getchar();
        return 0;
    }

    printf("returned %d\n", stack_size);

    printf("NewThreadEntryUPP\n");
    ThreadEntryTPP threadEntry = NewThreadEntryUPP(&thread_entry);
    ThreadID thread;

    printf("NewThread\n");

    void **res;
    parameter_block pb = {&other_thread_entry, NULL};

    err = NewThread(kCooperativeThread, threadEntry, &pb, stack_size / 8, kExactMatchThread, res, &thread);

    if (err)
    {
        printf("Error trying to get uhhhhhhh: %d\n", err);
        getchar();
        return 0;
    }

    printf("YieldToThread\n");
    err = YieldToThread(thread);
    if (err)
    {
        printf("Error trying to get uhhhhhhh: %d\n", err);
        getchar();
        return 0;
    }

    printf("good to go\n");
    getchar();*/

    thread_entry(NULL);

    return 0;
}
