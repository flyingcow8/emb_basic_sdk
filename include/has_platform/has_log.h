#ifndef HAS_LOG_H
#define HAS_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "has_errno.h"

#define HAS_DEBUG(...) \
  {\
    char s[128] = {0};\
    snprintf(s, sizeof(s), __VA_ARGS__);\
    wrapper_log_info(s);\
  }

#define HAS_WARN(...) \
  {\
    char s[128] = {0};\
    snprintf(s, sizeof(s), __VA_ARGS__);\
    wrapper_log_warn(s);\
  }

#define HAS_ERROR(...) \
  {\
    char s[128] = {0};\
    snprintf(s, sizeof(s), __VA_ARGS__);\
    wrapper_log_error(s);\
  }

#define HAS_FATAL(...) \
  {\
    char s[128] = {0};\
    snprintf(s, sizeof(s), __VA_ARGS__);\
    wrapper_log_fatal(s);\
  }

/**
 * @brief INFO等级（最低）LOG输出包裹函数
 *
 * @param s 用于LOG记录的消息字符串
 *
 * @return void
 */
void wrapper_log_info(const char *s);

/**
 * @brief WARN等级LOG输出包裹函数
 *
 * @param s 用于LOG记录的消息字符串
 *
 * @return void
 */
void wrapper_log_warn(const char *s);

/**
 * @brief ERROR等级LOG输出包裹函数
 *
 * @param s 用于LOG记录的消息字符串
 *
 * @return void
 */
void wrapper_log_error(const char *s);

/**
 * @brief FATAL等级（最高）LOG输出包裹函数
 *
 * @param s 用于LOG记录的消息字符串
 *
 * @return void
 */
void wrapper_log_fatal(const char *s);

/**
 * @brief 初始化日志模块，设定日志保存路径
 *
 * @param name 日志名
 * @param dir 日志保存路径，可以是绝对或者相对路径
 *
 * @return NULL_VALUE_ERROR 输入值NULL
 *         MKDIR_ERROR      创建路径失败
 *         SUCCESS          成功
 */
has_error_t has_log_open(const char *name, const char *dir);

/**
 * @brief 关闭日志模块
 *
 * @param void
 *
 * @return void
 */
void has_log_close();

#ifdef __cplusplus
}
#endif
#endif /* HAS_LOG_H */
