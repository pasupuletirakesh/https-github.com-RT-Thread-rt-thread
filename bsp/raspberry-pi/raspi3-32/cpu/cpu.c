/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-15     Bernard      first version
 * 2019-07-28     zdzn         add smp support
 */

#include <rthw.h>
#include <rtthread.h>
#include <board.h>
#include "cp15.h"

int rt_hw_cpu_id(void)
{
    int cpu_id;
    __asm__ volatile (
            "mrc p15, 0, %0, c0, c0, 5"
            :"=r"(cpu_id)
            );
    cpu_id &= 0xf;
    return cpu_id;
};


#ifdef RT_USING_SMP
void rt_hw_spin_lock_init(rt_hw_spinlock_t *lock)
{
    lock->slock = 0;
}

void rt_hw_spin_lock(rt_hw_spinlock_t *lock)
{
    unsigned long tmp;
    unsigned long newval;
    rt_hw_spinlock_t lockval;
    __asm__ __volatile__(
            "pld [%0]"
            ::"r"(&lock->slock)
            );

    __asm__ __volatile__(
            "1: ldrex   %0, [%3]\n"
            "   add %1, %0, %4\n"
            "   strex   %2, %1, [%3]\n"
            "   teq %2, #0\n"
            "   bne 1b"
            : "=&r" (lockval), "=&r" (newval), "=&r" (tmp)
            : "r" (&lock->slock), "I" (1 << 16)
            : "cc");

    while (lockval.tickets.next != lockval.tickets.owner)
    {
        __WFE();
        lockval.tickets.owner = *(volatile unsigned short *)(&lock->tickets.owner);
    }

    __DMB();
}

void rt_hw_spin_unlock(rt_hw_spinlock_t *lock)
{
    __DMB();
    lock->tickets.owner++;
    __DSB();
    __SEV();
}
#endif /*RT_USING_SMP*/

/**
 * @addtogroup ARM CPU
 */
/*@{*/


/*@}*/
