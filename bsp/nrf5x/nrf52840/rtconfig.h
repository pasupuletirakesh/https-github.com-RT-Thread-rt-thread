#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Generated by Kconfiglib (https://github.com/ulfalizer/Kconfiglib) */

/* Hardware Drivers Config */

#define SOC_NRF52840
#define SOC_NORDIC
#define BSP_BOARD_PCA_10056

/* Onboard Peripheral Drivers */

#define BSP_USING_JLINK_TO_USART
#define RT_BSP_LED_PIN 13
/* end of Onboard Peripheral Drivers */

/* On-chip Peripheral Drivers */

#define BSP_USING_GPIO
#define BSP_USING_UART
#define NRFX_USING_UART
#define BSP_USING_UART0
#define BSP_UART0_RX_PIN 8
#define BSP_UART0_TX_PIN 6

/* MCU flash config */

#define MCU_FLASH_START_ADDRESS 0x00000000
#define MCU_FLASH_SIZE_KB 1024
#define MCU_SRAM_START_ADDRESS 0x20000000
#define MCU_SRAM_SIZE_KB 256
#define MCU_FLASH_PAGE_SIZE 0x1000
/* end of MCU flash config */
/* end of On-chip Peripheral Drivers */
#define BLE_STACK_USING_NULL
#define NRFX_CLOCK_ENABLED 1
#define NRFX_CLOCK_DEFAULT_CONFIG_IRQ_PRIORITY 7
#define NRFX_CLOCK_CONFIG_LF_SRC 1
#define NRFX_UART_ENABLED 1
#define NRFX_UART0_ENABLED 1
#define NRFX_GPIOTE_ENABLED 1
/* end of Hardware Drivers Config */

/* RT-Thread Kernel */

#define RT_NAME_MAX 8
#define RT_ALIGN_SIZE 4
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 100
#define RT_USING_HOOK
#define RT_USING_IDLE_HOOK
#define RT_IDLE_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 256
#define RT_USING_TIMER_SOFT
#define RT_TIMER_THREAD_PRIO 4
#define RT_TIMER_THREAD_STACK_SIZE 512

/* kservice optimization */

/* end of kservice optimization */

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
/* end of Inter-Thread communication */

/* Memory Management */

#define RT_USING_MEMPOOL
#define RT_USING_SMALL_MEM
#define RT_USING_HEAP
/* end of Memory Management */

/* Kernel Device Object */

#define RT_USING_DEVICE
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uart0"
/* end of Kernel Device Object */
#define RT_VER_NUM 0x40100
/* end of RT-Thread Kernel */

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 2048
#define RT_MAIN_THREAD_PRIORITY 10

/* C++ features */

/* end of C++ features */

/* Command shell */

#define RT_USING_FINSH
#define RT_USING_MSH
#define FINSH_USING_MSH
#define FINSH_THREAD_NAME "tshell"
#define FINSH_THREAD_PRIORITY 20
#define FINSH_THREAD_STACK_SIZE 4096
#define FINSH_USING_HISTORY
#define FINSH_HISTORY_LINES 5
#define FINSH_USING_SYMTAB
#define FINSH_CMD_SIZE 80
#define MSH_USING_BUILT_IN_COMMANDS
#define FINSH_USING_DESCRIPTION
#define FINSH_ARG_MAX 10
/* end of Command shell */

/* Device virtual file system */

/* end of Device virtual file system */

/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_PIPE_BUFSZ 512
#define RT_USING_SERIAL
#define RT_USING_SERIAL_V1
#define RT_SERIAL_RB_BUFSZ 64
#define RT_USING_PIN

/* Using USB */

/* end of Using USB */
/* end of Device Drivers */

/* POSIX layer and C standard library */


/* POSIX (Portable Operating System Interface) layer */

/* end of POSIX (Portable Operating System Interface) layer */
/* end of POSIX layer and C standard library */

/* Network */

/* Socket abstraction layer */

/* end of Socket abstraction layer */

/* Network interface device */

/* end of Network interface device */

/* light weight TCP/IP stack */

/* end of light weight TCP/IP stack */

/* AT commands */

/* end of AT commands */
/* end of Network */

/* VBUS(Virtual Software BUS) */

/* end of VBUS(Virtual Software BUS) */

/* Utilities */

/* end of Utilities */
/* end of RT-Thread Components */

/* RT-Thread Utestcases */

/* end of RT-Thread Utestcases */

/* RT-Thread online packages */

/* IoT - internet of things */


/* Wi-Fi */

/* Marvell WiFi */

/* end of Marvell WiFi */

/* Wiced WiFi */

/* end of Wiced WiFi */
/* end of Wi-Fi */

/* IoT Cloud */

/* end of IoT Cloud */
/* end of IoT - internet of things */

/* security packages */

/* end of security packages */

/* language packages */

/* end of language packages */

/* multimedia packages */

/* LVGL: powerful and easy-to-use embedded GUI library */

/* end of LVGL: powerful and easy-to-use embedded GUI library */

/* u8g2: a monochrome graphic library */

/* end of u8g2: a monochrome graphic library */

/* PainterEngine: A cross-platform graphics application framework written in C language */

/* end of PainterEngine: A cross-platform graphics application framework written in C language */
/* end of multimedia packages */

/* tools packages */

/* end of tools packages */

/* system packages */

/* acceleration: Assembly language or algorithmic acceleration packages */

/* end of acceleration: Assembly language or algorithmic acceleration packages */

/* CMSIS: ARM Cortex-M Microcontroller Software Interface Standard */

/* end of CMSIS: ARM Cortex-M Microcontroller Software Interface Standard */

/* Micrium: Micrium software products porting for RT-Thread */

/* end of Micrium: Micrium software products porting for RT-Thread */
/* end of system packages */

/* peripheral libraries and drivers */

#define PKG_USING_NRFX
#define PKG_USING_NRFX_LATEST_VERSION
/* end of peripheral libraries and drivers */

/* AI packages */

/* end of AI packages */

/* miscellaneous packages */

/* samples: kernel and components samples */

/* end of samples: kernel and components samples */

/* entertainment: terminal games and other interesting software packages */

/* end of entertainment: terminal games and other interesting software packages */
/* end of miscellaneous packages */
/* end of RT-Thread online packages */

#endif
