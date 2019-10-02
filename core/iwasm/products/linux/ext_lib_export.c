/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "lib_export.h"
#include "wasm_export.h"
#include "native_interface.h"
#include <stdlib.h>
#include <stdio.h>


void writeln(int buffer_offset, int size)
{
    // We need to convert the wasm memory relative address to absolute address in heap
    // And then use Zephyr's printk to write to output or serial
    wasm_module_inst_t module_inst = get_module_inst();
    char *buffer = NULL;

    if (!validate_app_addr(buffer_offset, size))
        return;

    buffer = addr_app_to_native(buffer_offset);

    if (buffer != NULL) {
        printf("%s\n", buffer);
    }
}

void pinout(int pin, int state)
{
    // show gpio state on output
    printf("GPIO pin: %d, set to %d \n", pin, state);
}

void thread_sleep(int millis)
{
    // sleep on linux
    sleep(millis/1000);
}

void print_test(int num)
{
    printf("Hello from web assembly module: %d \n", num);
}

static NativeSymbol extended_native_symbol_defs[] = {
    EXPORT_WASM_API(writeln),
    EXPORT_WASM_API(pinout),
    EXPORT_WASM_API(thread_sleep),
    EXPORT_WASM_API(print_test)
};

#include "ext_lib_export.h"
