/** 
 * @file    has_thread.c
 * @note    Copyright 2017-2018 Hikvision, Inc. All rights reserved.
 * @brief   pthread线程操作
 * @auther  zhanyuan@hikvision.com
 */

#include <stdio.h>
#include <pthread.h>
#include "sys/prctl.h"
#include "has_thread.h"

has_error_t has_mutex_create(has_mutex_t *pMutex) {
  if (pMutex == NULL) {
    return NULL_VALUE_ERROR;
  }

	if (0 != pthread_mutex_init(pMutex, NULL)) {
		return MUTEX_INIT_ERROR;
	}

	return SUCCESS;
}

has_error_t has_mutex_lock(has_mutex_t *pMutex) {
  if (pMutex == NULL) {
    return NULL_VALUE_ERROR;
  }

  if (0 != pthread_mutex_lock(pMutex)) {
    return MUTEX_LOCK_ERROR;
  }

  return SUCCESS;
}

has_error_t has_mutex_unlock(has_mutex_t *pMutex) {
  if (pMutex == NULL) {
    return NULL_VALUE_ERROR;
  }

  if (0 != pthread_mutex_unlock(pMutex)) {
    return MUTEX_UNLOCK_ERROR;
  }

  return SUCCESS;
}

has_error_t has_mutex_destroy(has_mutex_t *pMutex) {
  if (pMutex == NULL) {
    return NULL_VALUE_ERROR;
  }

  if (0 != pthread_mutex_destroy(pMutex)) {
    return MUTEX_DESTROY_ERROR;
  }

  return SUCCESS;
}

has_error_t has_thread_start(has_thread_t *tid, VOID_FUN func, void *arg, has_thread_param_t *param) {
  if (tid == NULL) {
    return NULL_VALUE_ERROR;
  }
 
  if (param != NULL) {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    // set sched policy
    pthread_attr_setschedpolicy(&attr, SCHED_RR);
    // set detached
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    // set priority
    struct sched_param s_param;
    pthread_attr_getschedparam(&attr, &s_param);
    s_param.sched_priority = param->priority;
    pthread_attr_setschedparam(&attr, &s_param);
    // set inherit schedule
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    // set stack size
    pthread_attr_setstacksize(&attr, param->stack_size);

    if (pthread_create(tid, &attr, func, arg) != 0) {
      pthread_attr_destroy(&attr);
      return THREAD_START_ERROR;
    }
    pthread_attr_destroy(&attr);
  } else {
    if (0 != pthread_create(tid, NULL, func, arg)) {
      return THREAD_START_ERROR;
    }
    pthread_detach(*tid);
  }

  return SUCCESS;
}

has_error_t has_thread_stop(has_thread_t tid) {
  if (0 != pthread_cancel(tid)) {
    return THREAD_STOP_ERROR;
  }

  return SUCCESS;
}

void has_set_thread_name(const char *name) {
  prctl(15, (unsigned long)name);     //name 最多15个字符
}