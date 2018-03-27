#ifndef HAS_MQ_H
#define HAS_MQ_H

#ifdef __cplusplus
extern "C" {
#endif

#include "has_datatype.h"
#include "has_errno.h"
#include "has_mq_platform.h"

#define WAIT_FOREVER -1
#define NO_WAIT 0

typedef struct {
  char *name;       // required. 消息队列的名称，类似"/somename"的形式，必须以斜杠开头
  int mq_maxmsg;    // option(required if default_attr is false).自定义消息队列中最大的消息个数 
  int mq_msgsize;   // option(required if default_attr is false). 自定义最大消息长度
  bool default_attr;  // required.是否使用默认消息队列属性，如果为true，则使用系统默认的mq_maxmsg和mq_msgsize值
} has_mq_attr_t;

/**
 * @brief 新建消息队列
 *    如果attr的default_attr成员变量为true，则使用默认属性；如果为false，则使用自定义属性
 *
 * @param mqid 消息队列描述符
 * @param attr 消息队列属性
 *
 * @return NULL_VALUE_ERROR 输入值NULL
 *         MQ_CREATE_ERROR 消息队列创建失败
 *         SUCCESS 成功
 */
has_error_t has_mq_create(has_mq_t *mqid, has_mq_attr_t *attr);

/**
 * @brief 删除消息队列
 *
 * @param name 消息队列名称
 *
 * @return NULL_VALUE_ERROR 输入值NULL
 *         MQ_DELETE_ERROR 消息队列删除失败
 *         SUCCESS 成功
 */
has_error_t has_mq_delete(const char *name);

/**
 * @brief 打开消息队列
 *
 * @param name 消息队列名称
 *
 * @return NULL_VALUE_ERROR 输入值NULL
 *         MQ_OPEN_ERROR 消息队列打开失败
 *         SUCCESS 成功
 */
has_error_t has_mq_open(const char *name);

/**
 * @brief 关闭消息队列
 *
 * @param mqid 消息队列描述符
 *
 * @return MQ_CLOSE_ERROR 消息队列关闭失败
 *         SUCCESS 成功
 */
has_error_t has_mq_close(has_mq_t mqid);

/**
 * @brief 发送消息
 *
 * @param mqid 消息队列描述符
 *        msg 发送消息内存指针
 *        len 发送消息内存长度
 *        wait_ms 发送超时时间，单位为ms
 *
 * @return MQ_SEND_ERROR 消息队列发送失败
 *         MQ_TIMED_SEND_ERROR 消息队列发送超时失败
 *         SUCCESS 成功
 */
has_error_t has_mq_send(has_mq_t mqid, const char *msg, int len, int wait_ms);

/**
 * @brief 接收消息
 *
 * @param mqid 消息队列描述符
 *        msg 接收消息内存指针
 *        len 接收消息内存长度
 *        wait_ms 接收超时时间，单位为ms
 *
 * @return MQ_RECEIVE_ERROR 消息队列接收失败
 *         MQ_TIMED_RECEIVE_ERROR 消息队列接收超时失败
 *         SUCCESS 成功
 */
int has_mq_receive(has_mq_t mqid, char *msg, int len, int wait_ms);

/**
 * @brief 获取消息队列当前的消息个数
 *
 * @param mqid 消息队列描述符
 *
 * @return 消息个数
 */
int has_mq_size(has_mq_t mqid);

#ifdef __cplusplus
}
#endif
#endif /* HAS_MQ_H */
