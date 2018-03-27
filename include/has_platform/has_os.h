#ifndef HAS_OS_H
#define HAS_OS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "has_errno.h"
#include "has_datatype.h"
#include "has_os_platform.h"

#define FS_NAME_LEN 64

typedef enum {
    /* Standard file attribute */
    APP_FS_ATTR_RDONLY         =   0x01,
    APP_FS_ATTR_HIDDEN         =   0x02,
    APP_FS_ATTR_SYSTEM         =   0x04,
    APP_FS_ATTR_VOLUME         =   0x08,
    APP_FS_ATTR_DIR            =   0x10,
    APP_FS_ATTR_ARCH           =   0x20,

    /* Other file attribute */
    APP_FS_ATTR_NONE           =   0x40,
    APP_FS_ATTR_ALL            =   0x7f,
    APP_FS_ATTR_FILE_ONLY      =   0x100,
} APP_FS_ATTR_T;

typedef struct {
	uint64_t size;
	uint32_t attr;
	uint32_t dateTime;
} has_fstat_t;

/**
 * @brief 动态内存分配
 *
 * @param size 字节数
 *
 * @return 非NULL 分配的内存段指针
 *         NULL 内存分配失败
 */
void *has_malloc(uint32_t size);

/**
 * @brief 动态内存分配并对齐（返回的地址为align的倍数）
 *
 * @param align 对齐基数，必须是2的幂
 *        size 字节数
 *
 * @return 非NULL 分配的对齐的内存段指针
 *         NULL 内存分配失败
 */
void *has_memalign(uint32_t align, uint32_t size);

/**
 * @brief 释放动态内存
 *
 * @param ptr 动态内存指针
 *
 * @return void
 */
void has_free(void *ptr);

/**
 * @brief 获取开机时间
 *
 * @param void
 *
 * @return 开机时间，单位为ms
 */
uint32_t has_uptime_ms();

/**
 * @brief 系统延时
 *
 * @param ms 延时时间，单位为ms
 *
 * @return void
 */
void has_sleep_ms(uint32_t ms);

/**
 * @brief 格式化字符串输出
 *
 * @param str 目标数组指针
 *        len 目标数组内存长度
 *        fmt 格式化字符串
 *        ... 格式化字符串参数
 *
 * @return 负数 输出失败
 *         非负 输出字符串长度
 */
int has_snprintf(char *str, const int len, const char *fmt, ...);

/**
 * @brief 格式化字符串标准输出
 *
 * @param fmt 格式化字符串
 *        ... 格式化字符串参数
 *
 * @return 负数 标准输出失败
 *         非负 输出字符串长度
 */
void has_printf(const char *fmt, ...);

/**
 * @brief 打开文件
 *
 * @param path 文件路径
 *        mode 打开模式：r只读，r+读写，w文件清零写，w+读写，a追加写，a+读和追加写
 *
 * @return NULL 打开文件失败
 *         非NULL 文件句柄
 */
has_file_t *has_fopen(const char *path, const char *mode);

/**
 * @brief 关闭文件
 *
 * @param fd 文件句柄
 *
 * @return FILE_CLOSE_ERROR 关闭文件失败
 *         SUCCESS 成功
 */
has_error_t has_fclose(has_file_t *fd);

/**
 * @brief 读文件
 *
 * @param buffer 缓冲区指针
 *        size 读取长度，单位为字节
 *        fd 文件句柄
 *
 * @return NULL_VALUE_ERROR 输入值NULL
 *         FILE_EOF 读到文件末尾
 *         FILE_READ_ERROR 读文件错误
 *         SUCCESS 成功
 */
has_error_t has_fread(void *buffer, uint32_t size, has_file_t *fd);

/**
 * @brief 写文件
 *
 * @param buffer 缓冲区指针
 *        size 写入长度，单位为字节
 *        fd 文件句柄
 *
 * @return NULL_VALUE_ERROR 输入值NULL
 *         FILE_WRITE_ERROR 写文件错误
 *         SUCCESS 成功
 */
has_error_t has_fwrite(const void *buffer, uint32_t size, has_file_t *fd);

/**
 * @brief 设置文件指示器位置
 *
 * @param fd 文件句柄
 *        offset 文件指示器距文件起始的偏移
 *
 * @return FILE_SETPOS_ERROR 设置文件指示器位置错误
 *         SUCCESS 成功
 */
has_error_t has_fsetpos(has_file_t *fd, uint64_t offset);

/**
 * @brief 获取文件指示器位置
 *
 * @param fd 文件句柄
 *        offset 文件指示器距文件起始的偏移
 *
 * @return FILE_GETPOS_ERROR 获取文件指示器位置错误
 *         SUCCESS 成功
 */
has_error_t has_fgetpos(has_file_t *fd, uint64_t *offset);

/**
 * @brief 强制同步缓冲区数据到内核
 *
 * @param fd 文件句柄
 *
 * @return FILE_FLUSH_ERROR 同步失败
 *         SUCCESS 成功
 */
has_error_t has_fflush(has_file_t *fd);

/**
 * @brief 删除文件
 *
 * @param file 文件的路径
 *
 * @return REMOVE_ERROR 删除失败
 *         SUCCESS 成功
 */
has_error_t has_remove(const char *file);

/**
 * @brief 获取文件或者目录的状态
 *
 * @param name 文件或者目录的路径
 * @param stat 文件或者目录的状态
 *
 * @return NULL_VALUE_ERROR 输入值NULL
 *         FSTAT_ERROR 获取状态失败
 *         OPEN_ERROR 打开文件失败
 *         SUCCESS 成功
 */
has_error_t has_fstat(const char *name, has_fstat_t *stat);

/**
 * @brief 创建目录
 *
 * @param dirname 目录的路径
 *
 * @return MKDIR_ERROR 创建目录失败
 *         SUCCESS 成功
 */
has_error_t has_mkdir(const char *dirname);

/**
 * @brief 删除目录
 *
 * @param dirname 目录的路径
 *
 * @return RMDIR_ERROR 删除目录失败
 *         SUCCESS 成功
 */
has_error_t has_rmdir(const char *dirname);

/**
 * @brief 打开目录
 *
 * @param dirname 目录的路径
 *
 * @return NULL 打开目录失败
 *         非NULL 目录句柄
 */
has_dir_t *has_opendir(const char *dirname);

/**
 * @brief 读取目录
 *
 * @param dir 目录句柄
 *
 * @return NULL 读取目录失败
 *         非NULL 目录结构句柄
 */
has_dirent_t *has_readdir(has_dir_t *dir);

/**
 * @brief 关闭目录
 *
 * @param dir 目录句柄
 *
 * @return CLOSEDIR_ERROR 关闭目录失败
 *         SUCCESS 成功
 */
has_error_t has_closedir(has_dir_t *dir);

#ifdef __cplusplus
}
#endif
#endif /* HAS_OS_H */
