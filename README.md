> This is a cross-platform SDK sample, including several basic system functions. HAS is a project code, you can use anyone else like EMB or MAS.

## 构建
x86平台构建为例，下载源码
```
cd build
cmake ..
make
```

## 测试
由于涉及线程操作，需要取得超级用户权限

使用ctest来执行测试用例：
```
sudo make test
```

使用gtest来执行测试用例：
```
sudo ./has_platform_unittest
```

## 安装
```
make install
```
静态库和头文件的安装位置是在release/目录下
