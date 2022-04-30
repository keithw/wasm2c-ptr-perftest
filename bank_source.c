#include <stdint.h>
#include <stdbool.h>

static uint64_t s_bank_balance = 0;
static uint64_t s_candy_pieces = 0;
static const uint8_t s_cost_of_candy = 3;

void deposit_money(uint64_t amount) __attribute((export_name("deposit_money")));
bool can_buy_candy(void) __attribute((export_name("can_buy_candy")));
void buy_candy(void) __attribute((export_name("buy_candy")));
uint64_t candy_pieces(void)  __attribute((export_name("candy_pieces")));

void wasm_abort(void) __attribute((import_module("main")));

void deposit_money(uint64_t amount)
{
  s_bank_balance += amount;
}

bool can_buy_candy(void)
{
  return s_bank_balance >= s_cost_of_candy;
}

void buy_candy(void)
{
  if (!can_buy_candy()) {
    wasm_abort();
  }

  s_bank_balance -= s_cost_of_candy;
  s_candy_pieces++;
}

uint64_t candy_pieces(void)
{
  return s_candy_pieces;
}
