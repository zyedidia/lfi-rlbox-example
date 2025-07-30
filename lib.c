#include <stdio.h>
#include "lib.h"

void hello() {
    printf("Hello from lib\n");
}

unsigned int add(unsigned int a, unsigned int b) {
    return a + b;
}

void echo(const char *str) {
    printf("echo: %s\n", str);
}

void call_cb(void (*cb)(const char *str)) {
    cb("hi again!");
}
