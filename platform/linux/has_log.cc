/** 
 * @file    has_log.cc
 * @note    Copyright 2017-2018 Hikvision, Inc. All rights reserved.
 * @brief   log日志操作
 * @auther  zhanyuan@hikvision.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "glog/logging.h"
#include "has_errno.h"
#include "has_log.h"

has_error_t has_log_open(const char *name, const char *custom_dir) {
  char cmd[128] = {0};

  if (name == NULL) {
    return NULL_VALUE_ERROR;
  }

  if (custom_dir != NULL) {
    snprintf(cmd, sizeof(cmd), "mkdir -p %s", custom_dir);
    if (0 != system(cmd)) {
      return MKDIR_ERROR;
    }
    FLAGS_log_dir = custom_dir;
    google::InitGoogleLogging(name);
    FLAGS_stderrthreshold = google::GLOG_INFO;
    FLAGS_max_log_size = 10;
  } else {
	  google::InitGoogleLogging(name);
	  FLAGS_stderrthreshold = google::GLOG_INFO;
  }

  return SUCCESS;
}

void has_log_close() {
  google::ShutdownGoogleLogging();
}

void wrapper_log_info(const char *s) {
  DLOG(INFO) << s;
}

void wrapper_log_warn(const char *s) {
  LOG(WARNING) << s;
}

void wrapper_log_error(const char *s) {
  LOG(ERROR) << s;
}

void wrapper_log_fatal(const char *s) {
  LOG(DFATAL) << s;
}