/**
 * @file  	has_mq.c
 * @note  	Copyright 2017-2018 Hikvision, Inc. All rights reserved.
 * @brief 	POSIX消息队列
 * @auther	zhanyuan@hikvision.com
 */

#include <fcntl.h>
#include <time.h>
#include <mqueue.h>
#include "has_mq.h"

static void getTimespec(int wait_ms, struct timespec *tp) {
	time_t sec, t;
	long long int nsec;
	sec = 0;
	if (wait_ms == NO_WAIT) {
		nsec = 0;
	} else {
		nsec = wait_ms * 1000000LL;
	}

	if (clock_gettime(CLOCK_REALTIME, tp) == -1) {
		tp->tv_sec = time(NULL) + 1;
		tp->tv_nsec = 0;
	} else {
		t = time(NULL) + 1;
		if ((int)(tp->tv_sec - t) > 30) {
			tp->tv_sec = t;
			tp->tv_nsec = 0;
		}
	}

	nsec += tp->tv_nsec;
	if (nsec >= 1000000000) {
		sec = nsec / 1000000000;
		nsec = nsec % 1000000000;
	}
	tp->tv_sec += sec;
	tp->tv_nsec = nsec;
}

has_error_t has_mq_create(has_mq_t *mqid, has_mq_attr_t *attr) {
  struct mq_attr mqa;

	if (mqid == NULL || attr == NULL) {
		return NULL_VALUE_ERROR;
	}

  if (attr->default_attr == false) {
    mqa.mq_maxmsg = attr->mq_maxmsg;
    mqa.mq_msgsize = attr->mq_msgsize;
    if ((*mqid = mq_open(attr->name, O_CREAT|O_EXCL|O_RDWR, 0777, &mqa)) == -1) {
      return MQ_CREATE_ERROR;
    }
  } else {
      if ((*mqid = mq_open(attr->name, O_CREAT|O_EXCL|O_RDWR, 0777, NULL)) == -1) {
      return MQ_CREATE_ERROR;
    }
  }

  return SUCCESS;
}

has_error_t has_mq_delete(const char *name) {
	if (name == NULL) {
		return NULL_VALUE_ERROR;
	}

  if (0 != mq_unlink(name)) {
    return MQ_DELETE_ERROR;
  }

  return SUCCESS;
}

has_error_t has_mq_open(const char *name) {
	if (name == NULL) {
		return NULL_VALUE_ERROR;
	}

  if (mq_open(name, O_RDWR) == -1) {
      return MQ_OPEN_ERROR;
  }

  return SUCCESS;
}

has_error_t has_mq_close(has_mq_t mqid) {
  if (0 != mq_close(mqid)) {
    return MQ_CLOSE_ERROR;
  }

  return SUCCESS;
}

has_error_t has_mq_send(has_mq_t mqid, const char *msg, int len, int wait_ms) {
	struct timespec timeout;

	if (wait_ms == WAIT_FOREVER) {
		if (0 != mq_send(mqid, msg, len, 0)) {
      return MQ_SEND_ERROR;
    }
	} else {
		getTimespec(wait_ms, &timeout);
		if (0 != mq_timedsend(mqid, msg, len, 0, &timeout)) {
      return MQ_TIMED_SEND_ERROR;
    }
	}

	return SUCCESS;
}

int has_mq_receive(has_mq_t mqid, char *msg, int len, int wait_ms) {
  int rc = 0;
	struct timespec timeout;

	struct mq_attr attr;
	mq_getattr(mqid, &attr);

	if (wait_ms == WAIT_FOREVER) {
		if ((rc = mq_receive(mqid, msg, len, NULL)) == -1) {
			perror("mq_receive failed");
      return MQ_RECEIVE_ERROR;
    }
	} else {
		getTimespec(wait_ms, &timeout);
		if ((rc = mq_timedreceive(mqid, msg, len, NULL, &timeout)) == -1) {
			perror("mq_timereceive failed");
      return MQ_TIMED_RECEIVE_ERROR;
    }
	}

	return rc;
}

int has_mq_size(has_mq_t mqid) {
  struct mq_attr attr;

	if (0 != mq_getattr(mqid, &attr)) {
    return MQ_GETATTR_ERROR;
	}

	return attr.mq_curmsgs;
}