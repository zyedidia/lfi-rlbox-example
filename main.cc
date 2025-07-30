#include <stdio.h>
#include <stdlib.h>

#define release_assert(cond, msg) \
    if (!(cond)) { fputs(msg "\n", stderr); abort(); }

#include "lib.h"

// We're going to use RLBox in a single-threaded environment.
#define RLBOX_SINGLE_THREADED_INVOCATIONS

#include "rlbox.hpp"
#include "rlbox_lfi_sandbox.hpp"

extern "C" {
    extern uint8_t lib_start[];
    extern uint8_t lib_end[];
};

RLBOX_DEFINE_BASE_TYPES_FOR(lib, lfi);

int main(int argc, char const *argv[]) {
    rlbox_sandbox_lib sandbox;
    sandbox.create_sandbox(lib_start, lib_end);

    sandbox.invoke_sandbox_function(hello);

    // Call the library add function.
    auto ret = sandbox.invoke_sandbox_function(add, 3, 4)
        .copy_and_verify([](unsigned val) {
            release_assert(val < 10, "unexpected result");
            return val;
        });
    printf("add(3, 4) = %d\n", ret);

    // Call the library echo function.
    const char* helloStr = "hi hi!";
    size_t helloSize = strlen(helloStr) + 1;
    tainted_lib<char*> taintedStr = sandbox.malloc_in_sandbox<char>(helloSize);
    strncpy(sandbox, taintedStr, helloStr, helloSize);
    sandbox.invoke_sandbox_function(echo, taintedStr);
    sandbox.free_in_sandbox(taintedStr);

    sandbox.destroy_sandbox();

    return 0;
}
