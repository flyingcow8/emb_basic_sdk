#include "has_log.h"
#include "has_errno.h"
#include "gtest/gtest.h"

TEST(LOG_TEST, LOG_OPEN) {
  EXPECT_EQ(NULL_VALUE_ERROR, has_log_open(NULL, "home"));
  EXPECT_EQ(SUCCESS, has_log_open("MYAPP", "mylogdir"));
  HAS_DEBUG("11111");
  HAS_WARN("22222");
  has_log_close();

  EXPECT_EQ(SUCCESS, has_log_open("MYAPPS", NULL));
  HAS_ERROR("333333");
  has_log_close();
}
