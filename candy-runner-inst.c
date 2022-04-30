#include <stdio.h>
#include <stdlib.h>

#include "bank.h"
#include "main.h"

typedef struct Z_env_module_instance_t
{
  wasm_rt_memory_t* main_memory;
} Z_env_module_instance_t;

int main(void) {
  /* Initialize the Wasm runtime. */
  wasm_rt_init();

  /* Initialize the modules. */
  Z_main_init_module();
  Z_bank_init_module();

  Z_main_module_instance_t main;
  Z_bank_module_instance_t bank;
  Z_env_module_instance_t env;

  Z_main_instantiate(&main, &bank, &env, Z_bankZ_buy_candy, Z_bankZ_can_buy_candy);
  Z_bank_instantiate(&bank, &main);
  env.main_memory = Z_mainZ_memory(&main);
  
  Z_mainZ_main(&main);

  /* Free the modules. */
  Z_bank_free(&bank);
  Z_main_free(&main);

  /* Free the Wasm runtime state. */
  wasm_rt_free();

  return 0;
}

void Z_envZ_abort(struct Z_env_module_instance_t *x);

void Z_envZ_abort(struct Z_env_module_instance_t *x __attribute((unused)))
{
  abort();
}

u32 Z_envZ_printf(struct Z_env_module_instance_t* env, u32 str_ptr, u32 val_ptr);

u32 Z_envZ_printf(struct Z_env_module_instance_t* env, u32 str_ptr, u32 val_ptr)
{
  uint32_t val;
  memcpy( &val, env->main_memory->data + val_ptr, sizeof( val ) );
  return (uint32_t)printf( (char*)env->main_memory->data + str_ptr, val );
}
