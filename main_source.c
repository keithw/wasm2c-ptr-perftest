#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>

void deposit_money(uint64_t amount) __attribute((import_module("bank")));
bool can_buy_candy(void) __attribute((import_module("bank")));
void buy_candy(void) __attribute((import_module("bank")));
uint64_t candy_pieces(void) __attribute((import_module("bank")));

void wasm_abort(void) __attribute((export_name("wasm_abort")));

int main(void) __attribute((export_name("main")))
{
  deposit_money(10000000000);
  while (can_buy_candy()) {
    buy_candy();
  }
  printf("Purchased %" PRIu64 " pieces of candy.\n", candy_pieces());
  return 0;
}

 __attribute((noreturn)) void wasm_abort(void)
{
  abort();
}
