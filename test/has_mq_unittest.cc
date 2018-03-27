#include "gtest/gtest.h"
#include "has_mq.h"
#include "has_mq_platform.h"
#include "has_os.h"

TEST(MQ_TEST, MQ_CREATE_DEFAULT) {
  has_mq_t mqid;
  has_mq_attr_t attr;

  EXPECT_EQ(NULL_VALUE_ERROR, has_mq_create(NULL, &attr));
  EXPECT_EQ(NULL_VALUE_ERROR, has_mq_create(&mqid, NULL));

  attr.name = "/mq_default666";
  attr.default_attr = true;
  EXPECT_EQ(SUCCESS, has_mq_create(&mqid, &attr));

  const char *msg = "msg for mq test";

  EXPECT_EQ(SUCCESS, has_mq_send(mqid, msg, strlen(msg), WAIT_FOREVER));
  EXPECT_EQ(SUCCESS, has_mq_send(mqid, msg, strlen(msg), NO_WAIT));
  EXPECT_EQ(SUCCESS, has_mq_send(mqid, msg, strlen(msg), 100));

  char *msg_r = (char *)malloc(10000);

  EXPECT_EQ(strlen(msg), has_mq_receive(mqid, msg_r, 10000, WAIT_FOREVER));
  EXPECT_EQ(0, strcmp(msg_r, msg));
  bzero(msg_r, 10000);
  EXPECT_EQ(strlen(msg), has_mq_receive(mqid, msg_r, 10000, NO_WAIT));
  EXPECT_EQ(0, strcmp(msg_r, msg));
  bzero(msg_r, 10000);
  EXPECT_EQ(strlen(msg), has_mq_receive(mqid, msg_r, 10000, 100));
  EXPECT_EQ(0, strcmp(msg_r, msg));
  bzero(msg_r, 10000);

  EXPECT_EQ(SUCCESS, has_mq_delete(attr.name));
}

TEST(MQ_TEST, MQ_CREATE_CUSTOM) {
  has_mq_t mqid;
  has_mq_attr_t attr;

  EXPECT_EQ(NULL_VALUE_ERROR, has_mq_create(NULL, &attr));
  EXPECT_EQ(NULL_VALUE_ERROR, has_mq_create(&mqid, NULL));

  attr.name = "/mqhahaha888";
  attr.mq_maxmsg = 3;
  attr.mq_msgsize = 32;
  attr.default_attr = false;
  EXPECT_EQ(SUCCESS, has_mq_create(&mqid, &attr));

  const char *msg = "msg for mq test";

  EXPECT_EQ(SUCCESS, has_mq_send(mqid, msg, strlen(msg), WAIT_FOREVER));
  EXPECT_EQ(SUCCESS, has_mq_send(mqid, msg, strlen(msg), NO_WAIT));
  EXPECT_EQ(SUCCESS, has_mq_send(mqid, msg, strlen(msg), 100));
  EXPECT_EQ(MQ_TIMED_SEND_ERROR, has_mq_send(mqid, msg, strlen(msg), NO_WAIT));

  EXPECT_EQ(3, has_mq_size(mqid));

  char msg_r[32] = {0};
  EXPECT_EQ(strlen(msg), has_mq_receive(mqid, msg_r, sizeof(msg_r), WAIT_FOREVER));
  EXPECT_EQ(0, strcmp(msg_r, msg));
  bzero(msg_r, 32);
  EXPECT_EQ(strlen(msg), has_mq_receive(mqid, msg_r, sizeof(msg_r), NO_WAIT));
  EXPECT_EQ(0, strcmp(msg_r, msg));
  bzero(msg_r, 32);
  EXPECT_EQ(strlen(msg), has_mq_receive(mqid, msg_r, sizeof(msg_r), 100));
  EXPECT_EQ(0, strcmp(msg_r, msg));
  bzero(msg_r, 32);

  EXPECT_EQ(SUCCESS, has_mq_delete(attr.name));
}

TEST(MQ_TEST, MQ_DELETE) {
  EXPECT_EQ(MQ_DELETE_ERROR, has_mq_delete("/anoexistmq"));
  has_mq_t mqid;
  has_mq_attr_t attr;
  attr.name = "/mqhahaha888";
  attr.mq_maxmsg = 3;
  attr.mq_msgsize = 32;
  attr.default_attr = false;
  EXPECT_EQ(SUCCESS, has_mq_create(&mqid, &attr));
  EXPECT_EQ(SUCCESS, has_mq_close(mqid));
  EXPECT_EQ(MQ_CLOSE_ERROR, has_mq_close(mqid));
  EXPECT_EQ(SUCCESS, has_mq_delete("/mqhahaha888"));
  EXPECT_EQ(MQ_DELETE_ERROR, has_mq_delete("/mqhahaha888"));
}



