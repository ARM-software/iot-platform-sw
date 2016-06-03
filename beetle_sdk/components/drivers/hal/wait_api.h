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

#ifndef BEETLE_WAIT_API_H
#define BEETLE_WAIT_API_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Read timer **/
uint32_t us_ticker_read();

/** Waits a given number of microseconds **/
void wait_us(uint32_t us);

/** Waits a given number of miliseconds **/
void wait_ms(uint32_t ms);

/** Waits a given number of seconds **/
void wait_sec(uint32_t sec);

#ifdef __cplusplus
}
#endif
#endif /* BEETLE_WAIT_API_H */
