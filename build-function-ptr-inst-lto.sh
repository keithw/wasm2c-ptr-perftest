#!/bin/bash -ex

WASM_ARGS=" -Wno-unused-macros -Wno-pedantic -Wno-redundant-parens -Wno-undef -Wno-padded -Wno-missing-noreturn -Wno-unused-variable -Wno-unused-function -I../wabt/wasm2c"

/usr/bin/clang -flto -g -Weverything -Werror $WASM_ARGS -Ofast -mtune=native -march=native -c -o main.o main.c

/usr/bin/clang -flto -g -Weverything -Werror $WASM_ARGS -Ofast -mtune=native -march=native -c -o bank.o bank.c

/usr/bin/clang -flto -g -Weverything -Werror $WASM_ARGS -Wno-format-nonliteral -Ofast -mtune=native -march=native -c -o candy-runner.o candy-runner-inst.c

/usr/bin/clang -flto -g -Wall -Werror $WASM_ARGS -Ofast -mtune=native -march=native -c -o wasm-rt-impl.o ../wabt/wasm2c/wasm-rt-impl.c

/usr/bin/clang -static -flto -g -Weverything -Werror -Ofast -mtune=native -march=native -o candy-runner main.o bank.o wasm-rt-impl.o candy-runner.o

strip candy-runner
