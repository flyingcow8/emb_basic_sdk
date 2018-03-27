#include "gtest/gtest.h"
#include "has_os.h"


TEST(OS_TEST, MALLOC) {
  void *ptr = NULL;
  ptr = has_malloc(10000);
  EXPECT_TRUE(ptr);
  has_free(ptr);
}

TEST(OS_TEST, MEMALIGN) {
  void *ptr = NULL;
  ptr = has_memalign(16, 20000);
  EXPECT_TRUE(ptr);
  has_free(ptr);
}

TEST(OS_TEST, PRINT) {
  char s[16] = {0};

  int rc = has_snprintf(s, 16, "abc%d", 123);
  EXPECT_EQ(6, rc);
}

TEST(OS_TEST, FILE_IO) {
  // char wbuffer[100] = "it is a demo txt";
  // char rbuffer[100] = {0};
  // has_file_t *fd = has_fopen("file.txt", "w+"); 
  
  // EXPECT_NE(NULL, fd);
  // EXPECT_EQ(SUCCESS, has_fwrite(wbuffer, strlen(wbuffer), fd));
  // EXPECT_EQ(SUCCESS, has_fclose(fd));

  // has_file_t *fd = has_fopen("file.txt", "r"); 
  // EXPECT_EQ(FILE_EOF, has_fread(rbuffer, 100, fd));
  // EXPECT_EQ(SUCCESS, has_fclose(fd));
}