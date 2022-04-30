#include <stdio.h>
#include <stdlib.h>

#include "bank.h"
#include "main.h"

int main(void) {
  /* Initialize the Wasm runtime. */
  wasm_rt_init();

  /* Initialize the modules. */
  Z_main_init();
  Z_bank_init();

  Z_mainZ_main();

  /* Free the modules. */
  Z_bank_free();
  Z_main_free();

  /* Free the Wasm runtime state. */
  wasm_rt_free();

  return 0;
}

uint32_t printf_hook(const uint32_t str_ptr, const uint32_t val);

uint32_t printf_hook(const uint32_t str_ptr, const uint32_t val_ptr)
{
  uint32_t val;
  memcpy( &val, Z_mainZ_memory->data + val_ptr, sizeof( val ) );
  return (uint32_t)printf( (char*)Z_mainZ_memory->data + str_ptr, val );
}

u32 (*Z_envZ_printf)(u32, u32) = printf_hook;
void (*Z_envZ_abort)(void) = abort;
