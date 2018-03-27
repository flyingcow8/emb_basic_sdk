/**
 * @file    has_os.c
 * @note    Copyright 2017-2018 Hikvision, Inc. All rights reserved.
 * @brief   系统操作相关的常用接口
 * @auther  zhanyuan@hikvision.com
 */

#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <memory.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include "has_os.h"

void *has_malloc(uint32_t size) {
	return malloc(size);
}

void *has_memalign(uint32_t align, uint32_t size) {
	return memalign(align, size);
}

void has_free(void *ptr) {
  free(ptr);
}

uint32_t has_uptime_ms() {
  struct timeval tv = { 0 };
  uint32_t time_ms;

  gettimeofday(&tv, NULL);
  time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
  return time_ms;
}

void has_sleep_ms(uint32_t ms) {
  usleep(1000 * ms);
}

int has_snprintf(char *str, const int len, const char *fmt, ...) {
  va_list args;
  int rc;

  va_start(args, fmt);
  rc = vsnprintf(str, len, fmt, args);
  va_end(args);

  return rc;
}

void has_printf(const char *fmt, ...) {
  va_list args;

  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);

  fflush(stdout);
}

has_file_t *has_fopen(const char *path, const char *mode) {
  return fopen(path, mode);
}

has_error_t has_fclose(has_file_t *fd) {
  if (0 != fclose(fd)) {
    return FILE_CLOSE_ERROR;
  }
  
  return SUCCESS;
}

has_error_t has_fread(void *buffer, uint32_t size, has_file_t *fd) {
  if (buffer == NULL || fd == NULL) {
    return NULL_VALUE_ERROR;
  }

	if (fread(buffer, 1, size, fd) < size) {
    if (feof(fd) != 0) return FILE_EOF;
    if (ferror(fd) != 0) return FILE_READ_ERROR;
  }

  return SUCCESS;
}

has_error_t has_fwrite(const void *buffer, uint32_t size, has_file_t *fd) {
  if (buffer == NULL || fd == NULL) {
    return NULL_VALUE_ERROR;
  }

	if (fwrite(buffer, 1, size, fd) < size) {
    return FILE_WRITE_ERROR;
  }

  return SUCCESS;
}

has_error_t has_fsetpos(has_file_t *fd, uint64_t offset) {
	if (0 != fseek(fd, offset, SEEK_SET)) {
    return FILE_SETPOS_ERROR;
  }

  return SUCCESS;
}

has_error_t has_fgetpos(has_file_t *fd, uint64_t *offset) {
	if ((*offset = ftell(fd)) == -1) {
    return FILE_GETPOS_ERROR;
  }
  
  return SUCCESS;
}

has_error_t has_fflush(has_file_t *fd) {
  if (0 != fflush(fd)) {
    return FILE_FLUSH_ERROR;
  }

  return SUCCESS;
}

has_error_t has_remove(const char *file) {
  if (0 != remove(file)) {
    return REMOVE_ERROR;
  }

  return SUCCESS;
}

has_error_t has_fstat(const char *name, has_fstat_t *stat) {
	int fd;
	struct stat statbuf;

	if (NULL == name || NULL == stat) {
		return NULL_VALUE_ERROR;
	}

	if(-1 != (fd = open(name, O_RDONLY, 0))) {
		if(0 == fstat(fd, &statbuf)) {
			stat->size = statbuf.st_size;
			if(S_ISREG(statbuf.st_mode)) {
				stat->attr |= APP_FS_ATTR_FILE_ONLY;
			} if(S_ISDIR(statbuf.st_mode)) {
				stat->attr |= APP_FS_ATTR_DIR;
			}
			stat->dateTime = statbuf.st_mtime;
			close(fd);
		} else {
      close(fd);
      return FSTAT_ERROR;
    }
	} else {
    return OPEN_ERROR;
  }
	
	return SUCCESS;
}

has_error_t has_mkdir(const char *dirname) {
  if (0 != mkdir(dirname, 0777)) {
    return MKDIR_ERROR;
  }

  return SUCCESS;
}

has_error_t has_rmdir(const char *dirname) {
  if (0 != rmdir(dirname)) {
    return RMDIR_ERROR;
  }

  return SUCCESS;
}

has_dir_t *has_opendir(const char *dirname) {
  return opendir(dirname);
}

has_dirent_t *has_readdir(has_dir_t *dir) {
  return readdir(dir);
}

has_error_t has_closedir(has_dir_t *dir) {
  if (0 != closedir(dir)) {
    return CLOSEDIR_ERROR;
  }

  return SUCCESS;
}
