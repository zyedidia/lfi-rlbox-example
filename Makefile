CXX=c++
LFI_CC=x86_64-lfi-linux-musl-clang
INCLUDE=-Ideps/rlbox/code/include -Ideps/rlbox_lfi_sandbox/include -Ideps/lfi-runtime/install/include
LIBLFI=deps/lfi-runtime/install/lib/liblfi.a

main: main.cc lib.lfi
	$(CXX) $< $(INCLUDE) -std=gnu++20 -O2 lib_embed.S $(LIBLFI) -o $@

lib.lfi: lib.c
	$(LFI_CC) -Wl,--export-dynamic -static-pie -O2 -o $@ $< -lboxrt

clean:
	rm -f lib.lfi main

.PHONY: clean
