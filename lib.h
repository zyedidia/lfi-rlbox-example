#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void hello();
unsigned int add(unsigned int, unsigned int);
void echo(const char *str);
void call_cb(void (*cb) (const char *str));

#ifdef __cplusplus
}
#endif
