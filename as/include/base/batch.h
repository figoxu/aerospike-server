/*
 * batch.h
 *
 * Copyright (C) 2008-2015 Aerospike, Inc.
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

#pragma once

#include "base/transaction.h"
#include "dynbuf.h"

struct as_batch_shared;
//初始化批处理
int as_batch_init();
//批量 队列 任务
int as_batch_queue_task(as_transaction* tr);
//批量  添加 结果
void as_batch_add_result(as_transaction* tr, as_namespace* ns, char* setname, uint32_t generation,
	uint32_t void_time, uint16_t n_bins, as_bin** bins, as_msg_op** ops);

//批量  添加  结果（代理）
void as_batch_add_proxy_result(struct as_batch_shared* shared, uint32_t index, cf_digest* digest, cl_msg* cmsg, size_t size);


//批量添加 错误
void as_batch_add_error(struct as_batch_shared* shared, uint32_t index, int result_code);

//批量 线程 扩容
int as_batch_threads_resize(uint32_t threads);

//批量 队列 的 信息
void as_batch_queues_info(cf_dyn_buf* db);

//批量任务中  尚未使用的buffer
int as_batch_unused_buffers();


//销毁批量任务
void as_batch_destroy();
