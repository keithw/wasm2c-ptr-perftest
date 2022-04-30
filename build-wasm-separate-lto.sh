#!/bin/bash -ex

clang -g -Weverything -Werror -Ofast -mtune=native -march=native main_source.c -o main.wasm -nostdlib -Wl,--no-entry -Wl,--allow-undefined

clang -g -Weverything -Werror -Ofast -mtune=native -march=native bank_source.c -o bank.wasm -nostdlib -Wl,--no-entry -Wl,--allow-undefined

wasm2c main.wasm -o main.c

wasm2c bank.wasm -o bank.c

WASM_ARGS=" -Wno-unused-macros -Wno-redundant-parens -Wno-undef -Wno-padded -Wno-missing-noreturn -Wno-unused-variable -Wno-unused-function"

/usr/bin/clang -flto -g -Weverything -Werror $WASM_ARGS -Ofast -mtune=native -march=native -c -o main.o main.c

/usr/bin/clang -flto -g -Weverything -Werror $WASM_ARGS -Ofast -mtune=native -march=native -c -o bank.o bank.c

/usr/bin/clang -flto -g -Weverything -Werror $WASM_ARGS -Wno-format-nonliteral -Ofast -mtune=native -march=native -c -o candy-runner.o candy-runner.c

/usr/bin/clang -flto -g -Wall -Werror -Ofast -mtune=native -march=native -c -o wasm-rt-impl.o ../wabt/wasm2c/wasm-rt-impl.c

/usr/bin/clang -flto -Weverything -Werror -Ofast -mtune=native -march=native -o candy-runner main.o bank.o wasm-rt-impl.o candy-runner.o
