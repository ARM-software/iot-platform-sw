/*
 * Copyright (c) 2016 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdbool.h>
#include "wait_api.h"
#include "apb_timer.h"
#include "cmsis.h"

typedef struct {
  bool is_init;
  // us ticker overflow
  uint32_t us_ticker_overflow;
} time_var_t;

static time_var_t timeVars;

void TIMER1_Handler(void) {
  Timer_ClearInterrupt(TIMER1);
  timeVars.us_ticker_overflow++;
}

/** Enables the wait timer */
void enable_Timer_(void) {
  timeVars.is_init = true;

  Timer_Initialize(TIMER1, 0);
  Timer_Enable(TIMER1);

  /* Timer 1 get IRQn */
  uint32_t us_ticker_irqn1 = Timer_GetIRQn(TIMER1);
  NVIC_EnableIRQ((IRQn_Type)us_ticker_irqn1);
}

uint32_t us_ticker_read() {
  if(!timeVars.is_init) {
    enable_Timer_();
  }
  return Timer_Read(TIMER1);
}

void wait_us(uint32_t us) {
  enable_Timer_();
  uint32_t start_time = Timer_Read(TIMER1);
  while((Timer_Read(TIMER1) - start_time) < us);
}

void wait_ms(uint32_t ms) {
  wait_us(ms*1000);
}

void wait_sec(uint32_t sec) {
  wait_ms(sec*1000);
}
