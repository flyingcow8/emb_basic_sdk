#ifndef HAS_THREAD_H
#define HAS_THREAD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "has_errno.h"
#include "has_thread_platform.h"

#define PRIORITY_HIGH 90
#define PRIORITY_MID  80
#define PRIORITY_LOW  70

typedef void *(*VOID_FUN)(void *);

typedef struct {
  int priority;     /* 线程优先级，取值为0~100。数字越大，优先级越高 */
  int stack_size;   /* 线程栈大小，单位为byte*/
} has_thread_param_t;

/**
 * @brief 新建互斥量
 *
 * @param pMutex 互斥量对象
 *
 * @return NULL_VALUE_ERROR 输入值NULL
 *         MUTEX_INIT_ERROR 互斥量初始化失败
 *         SUCCESS 成功
 */
has_error_t has_mutex_create(has_mutex_t *pMutex);

/**
 * @brief 互斥量加锁
 *
 * @param pMutex 互斥量对象
 *
 * @return NULL_VALUE_ERROR 输入值NULL
 *         MUTEX_LOCK_ERROR 互斥量加锁失败
 *         SUCCESS 成功
 */
has_error_t has_mutex_lock(has_mutex_t *pMutex);

/**
 * @brief 互斥量解锁
 *
 * @param pMutex 互斥量对象
 *
 * @return NULL_VALUE_ERROR 输入值NULL
 *         MUTEX_UNLOCK_ERROR 互斥量解锁失败
 *         SUCCESS 成功
 */
has_error_t has_mutex_unlock(has_mutex_t *pMutex);

/**
 * @brief 销毁互斥量
 *
 * @param pMutex 互斥量对象
 *
 * @return NULL_VALUE_ERROR 输入值NULL
 *         MUTEX_DESTROY_ERROR 互斥量解锁失败
 *         SUCCESS 成功
 */
has_error_t has_mutex_destroy(has_mutex_t *pMutex);

/**
 * @brief 开启线程
 *        当param为NULL时，使用系统默认的线程属性，否则使用param中的线程属性。
 *
 * @param tid 线程id
 *        func 线程函数
 *        arg 线程函数参数
 *        param 线程属性
 *
 * @return NULL_VALUE_ERROR 输入值NULL
 *         THREAD_START_ERROR 开启线程失败
 *         SUCCESS 成功
 */
has_error_t has_thread_start(has_thread_t *tid, VOID_FUN func, void *arg, has_thread_param_t *param);

/**
 * @brief 结束线程
 *
 * @param tid 线程id
 *
 * @return THREAD_STOP_ERROR 结束线程失败
 *         SUCCESS 成功
 */
has_error_t has_thread_stop(has_thread_t tid);

/**
 * @brief 设置线程名
 *
 * @param name 线程名
 *
 * @return void
 */
void has_set_thread_name(const char *name);

#ifdef __cplusplus
}
#endif
#endif /* HAS_THREAD_H */

