Cmake 简介
=========
目录
------
 + [为什么要使用Cmake](#title_01)
 + [Cmake的安装]()
 + []()
 + []()
 + []()

### <span id='title_01'>一 为什么要使用Cmake</span>
   cmake是一个比make更高级的编译工具平台，它可以根据不同的平台、不同的编译器，生成相应makefile文件或者vcproj项目
   通过Cmakelist.txt，可以控制生成的makefile，从而控制编译过程。
   cmake自动生成的makefile不仅可以通过make命令构建项目生成目标文件，还支持安装(make install)、测试安装的程序能否正确执行
   (make test或者是ctest)，生成当前平台的安装包(make package)生成源码包(make package_source)、产生dashboard显示数据并上传等高级功能，只要在cmakelist.txt中简单配置，就可以完成很多复杂功能，包括测试用例。如果有嵌套子目录，子目录下面会有自己的cmakelists.txt

### <span id='title_02'>二 Cmake的安装</span>
  mac os安装cmake
  1 首先从官网上现在所需要的版本[官网地址](src='https://cmake.org/download/)</br>
  2 下载mac os 需要的dmg格式</br>
  3 安装dmg包</br>
  4 执行```sudo "/Applications/CMake.app/Contents/bin/cmake-gui" --install```，之后环境变量配置完成。


### <span id='title_03'>三 Cmake的主要特点</span>
+ 开放源代码，使用类BSDx许可发布
+ 跨平台，并可生成native编译配置文件，在linux/unix平台可以生成makefile文件，苹果平台，可以生成xcode
+ 能够管理大型项目
+ 简化编译构建过程和编译过程
