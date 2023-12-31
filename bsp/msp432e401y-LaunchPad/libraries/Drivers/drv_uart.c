/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-15     yby          the first version
 */

#include "drv_uart.h"

#ifdef RT_USING_SERIAL
#include "uart_config.h"
#include "interrupt.h"
#include "uart.h"

#define   LOG_TAG  "drv.uart"
#include <drv_log.h>

#if !defined(BSP_USING_UART0)&&!defined(BSP_USING_UART1)&&!defined(BSP_USING_UART2)&&!defined(BSP_USING_UART3)
    #error "Please define at least one BSP_USING_UARTx"
#endif

enum
{
#ifdef BSP_USING_UART0
    UART0_INDEX,
#endif
#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif
#ifdef BSP_USING_UART2
    UART2_INDEX,
#endif
#ifdef BSP_USING_UART3
    UART3_INDEX,
#endif
};

uint32_t uart_intbase[] =
{
#ifdef BSP_USING_UART0
    INT_UART0,
#endif
#ifdef BSP_USING_UART1
    INT_UART1,
#endif
#ifdef BSP_USING_UART2
    INT_UART2,
#endif
#ifdef BSP_USING_UART3
    INT_UART3
#endif
};

static struct msp432_uart_config uart_config[] =
{
#ifdef BSP_USING_UART0
    UART0_CONFIG,
#endif

#ifdef BSP_USING_UART1
    UART1_CONFIG,
#endif

#ifdef BSP_USING_UART2
    UART2_CONFIG,
#endif

#ifdef BSP_USING_UART3
    UART3_CONFIG,
#endif
};
static struct msp432_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static rt_err_t msp432_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct msp432_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = rt_container_of(serial, struct msp432_uart, serial);

    UARTConfigSetExpClk(uart->config->uartbase, SystemCoreClock, uart->config->baudrate,
                        uart->config->mode);
    UARTIntEnable(uart->config->uartbase, UART_INT_RX);
    UARTEnable(uart->config->uartbase);
    UARTFIFODisable(uart->config->uartbase);
    IntEnable(uart->uartintbase);

    return RT_EOK;
}


static rt_err_t msp432_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct msp432_uart  *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct msp432_uart, serial);

    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        IntDisable(uart->uartintbase);
        UARTIntDisable(uart->config->uartbase, UART_INT_RX);
        break;
    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        IntEnable(uart->uartintbase);
        UARTIntEnable(uart->config->uartbase, UART_INT_RX);
        break;
    }

    return RT_EOK;
}

static int msp432_putc(struct rt_serial_device *serial, char c)
{
    struct msp432_uart *uart;
    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct msp432_uart, serial);
    UARTCharPut(uart->config->uartbase, c);

    return 1;
}

static int msp432_getc(struct rt_serial_device *serial)
{
    int ch;
    struct msp432_uart *uart;
    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct msp432_uart, serial);
    ch = -1;
    ch = UARTCharGetNonBlocking(uart->config->uartbase);

    return ch;
}

static rt_ssize_t msp432_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    /* this is an interface for uart dma, reserved for uptate. */
    return 0;
}

static const struct rt_uart_ops msp432_uart_ops =
{
    .configure = msp432_configure,
    .control = msp432_control,
    .putc = msp432_putc,
    .getc = msp432_getc,
    .dma_transmit = msp432_dma_transmit
};

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    struct msp432_uart *uart;
    uint32_t ui32Ints;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct msp432_uart, serial);

    ui32Ints = UARTIntStatus(uart->config->uartbase, true);
    UARTIntClear(uart->config->uartbase, ui32Ints);

    /* UART in mode Receiver -------------------------------------------------*/
    if (ui32Ints & (UART_INT_RX | UART_INT_RT))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
}

#if defined(BSP_USING_UART0)
void UART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART0_INDEX].serial));
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
void UART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART1_INDEX].serial));
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
void UART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART2_INDEX].serial));
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
void UART3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART3_INDEX].serial));
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

int rt_hw_usart_init(void)
{
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct msp432_uart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    uart_hw_config();

    for (int i = 0; i < obj_num; i++)
    {
        uart_obj[i].config        = &uart_config[i];
        uart_obj[i].uartintbase   = uart_intbase[i];
        uart_obj[i].serial.ops    = &msp432_uart_ops;
        uart_obj[i].serial.config = config;
        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial, uart_obj[i].config->name,
                                       RT_DEVICE_FLAG_RDWR
                                       | RT_DEVICE_FLAG_INT_RX
                                       | RT_DEVICE_FLAG_INT_TX
                                       | uart_obj[i].uart_dma_flag
                                       , NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* RT_USING_SERIAL */

/************************** end of file ******************/
