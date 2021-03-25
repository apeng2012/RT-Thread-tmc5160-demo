/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-02     RT-Thread    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include "tmc51xx.h"

#define LED_PIN GET_PIN(I, 8)

#define TMC5160_PIN_DIAG0 GET_PIN(H, 7)
#define TMC5160_PIN_EN    GET_PIN(H, 8)
#define TMC5160_PIN_DIR   GET_PIN(H, 9)
#define TMC5160_PIN_STEP  GET_PIN(H, 10)

int main(void)
{
    rt_uint32_t count = 1;
    struct tmc51xx_io_config tmc5160_ioc;

    tmc5160_ioc.spi_bus_name = "spi2";
    tmc5160_ioc.spi_device_name = "spi20";
    tmc5160_ioc.cs_gpiox = GPIOI;
    tmc5160_ioc.cs_gpio_pin = GPIO_PIN_0;
    tmc5160_ioc.pin_en = TMC5160_PIN_EN;
    tmc5160_ioc.pin_step = TMC5160_PIN_STEP;
    tmc5160_ioc.pin_dir = TMC5160_PIN_DIR;
    tmc5160_ioc.pin_diga0 = TMC5160_PIN_DIAG0;

    tmc51xx_init(&tmc5160_ioc);

    rt_pin_write(TMC5160_PIN_EN, PIN_LOW);
    while(count++)
    {
        rt_thread_mdelay(1);
        rt_pin_write(TMC5160_PIN_STEP, PIN_HIGH);
        rt_thread_mdelay(1);
        rt_pin_write(TMC5160_PIN_STEP, PIN_LOW);
    }
    return RT_EOK;
}

#include "stm32h7xx.h"
static int vtor_config(void)
{
    /* Vector Table Relocation in Internal QSPI_FLASH */
    SCB->VTOR = QSPI_BASE;
    return 0;
}
INIT_BOARD_EXPORT(vtor_config);


