#include "gtest/gtest.h"
#include "has_thread.h"
#include "has_common.h"

TEST(THREAD_TEST, MUTEX) {
  has_mutex_t mutex;
  EXPECT_EQ(NULL_VALUE_ERROR, has_mutex_create(NULL));
  EXPECT_EQ(SUCCESS, has_mutex_create(&mutex));
  EXPECT_EQ(SUCCESS, has_mutex_lock(&mutex));
  EXPECT_EQ(SUCCESS, has_mutex_unlock(&mutex));
  EXPECT_EQ(SUCCESS, has_mutex_destroy(&mutex));
}

void *thread_f(void *arg) {
  int a = 1;
  a++;
  return NULL; 
}


TEST(THREAD_TEST, THREAD_DEFAULT) {
  has_thread_t tid;
  EXPECT_EQ(SUCCESS, has_thread_start(&tid, thread_f, NULL, NULL));
}

TEST(THREAD_TEST, THREAD_CUSTOM) {
  has_thread_t tid;
  has_thread_param_t param;
  param.priority = PRIORITY_HIGH;
  param.stack_size = SIZE_32KB;
  
  EXPECT_EQ(SUCCESS, has_thread_start(&tid, thread_f, NULL, &param));
}