/*
 * asm.h
 *
 * Copyright (C) 2013-2014 Aerospike, Inc.
 *
 * Portions may be licensed to Aerospike, Inc. under one or more contributor
 * license agreements.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/
 */

/*
 *  SYNOPSIS
 *    The ASMalloc interface provides the connection between the
 *    Aerospike Server and the ASMalloc memory accounting tool by
 *    defining threshold parameters for notification of memory
 *    allocation changes and functions to invoke the callback
 *    hook from, and send commands to, the ASMalloc library.
 */

#pragma once

#ifdef USE_ASM

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <dlfcn.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>

#include "asmalloc.h"


/*  在主线程的堆栈上分配最大的数量的内存，它应该比 NUM_MALLOCATIONS 大
 *  Maximum number of mallocations allocated on the stack in the main thread.
 *  [Note:  This number must be at least as great as the value of "NUM_MALLOCATIONS"
 *           in the generated file "gen/mallocations.h".]
 */
#define MAX_NUM_MALLOCATIONS               (1024)

/* 触发内存分配报警 的   最小块的大小
 *  Default minimum size of blocks triggering mallocation alerts.
 */
#define DEFAULT_THRESH_BLOCK_SIZE_BYTES    (512 * 1024)

/*  触发每个线程内存分配报警的默认最小 DELTA(三角)大小，
 *  Default minimum delta size between mallocation alerts per thread.
 */
#define DEFAULT_THRESH_DELTA_SIZE_BYTES    (1024 * 1024)

/* 触发每个线程内存分配报警的默认最小时间周期，单位（秒）
 *  Default minimum time between mallocation alerts per thread.
 */
#define DEFAULT_THRESH_DELTA_TIME_SECONDS  (60)

/*   钩子 bool：是否周期性分配内容时，打印相关的消息日志
 *  Is periodic invocation of the ASMalloc hook and logging of messages enabled?
 */
extern bool g_asm_hook_enabled;

/*  是否在AS内存分配之后执行callback
 *  Is the ASMalloc callback function enabled?
 */
extern bool g_asm_cb_enabled;

/*  触发内存分配回调的阀值
 *  Threshold values for triggering memory allocation callbacks.
 */
extern size_t g_thresh_block_size;
extern size_t g_thresh_delta_size;
extern time_t g_thresh_delta_time;

/*  将被传递给回调函数的用户提供的私有数据，
 *  User-supplied private data to be passed to the callback function.
 */
extern void *g_my_cb_udata;

/*  当库被重新加载时，调用这个方法来重新分配内存
 *  Initialize ASMalloc functions if the library has been preloaded.
 */
void asm_init(void);

/*  调用ASMalloc的钩子方法
 *  Invoke the ASMalloc hook function.
 */
int as_asm_hook(void *arg, asm_stats_t **asm_stats, vm_stats_t **vm_stats);

/*  调用ASMalloc的命令的函数
 *  Invoke the ASMalloc command function.
 */
int as_asm_cmd(asm_cmd_t cmd, ...);

#endif // defined(USE_ASM)
