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

### <span id='title_04'>四 cmake 基本语法</span>
每个基于cmake的项目都必须包含一个名为```CmakeList.txt```的脚本，这个脚本定义的了目标，但他也可以做很多其他的事情，比如寻找第三方库或生成C++头文件。
#### 1 打印helloworld
  + 创建一个```hello.txt```文档
    ```txt
    message("hello world!");
    ```
  + cmake打印
    ```cmake
    cmake -P hello.txt
    ```

#### 2 所有变量都是字符串
 +   cmake中每一个变量都是一串字符串，你可以使用一个字符串文字来代替一个变量```${}```，称为```变量引用```，之后执行下面命令:</br>
     ```txt
     message("Hello ${NAME}!")       # Substitute a variable into the message
     ```

     ```cmake
     cmake -DNAME=smallwang911 -P hello.txt
     ```
     输出结果为：
     ```hello smallwang911!```
+  我们如何在脚本中定义变量，请使用```set```命令。语法格式：```set(variable,value)```</br>
  初学阶段，我们只需要了解，set可以显式的定义变量即可。</br>
  例如：
  ```cmakelist
  set(SRC_LIST main.c)
  ```
  也可以
  ```CmakeList
  set(SRC_LIST main.c test01.c test02.c)
  ```

#### 3 project语法指令
+ project语法指令
  ```CmakeList
  project(projectname [CXX] [C] [JAVA])
  ```
+ 注
  - 可以使用project指定工程名称，并可以指定工程使用的语言。支持的语言列表是可以忽略的。
  - 这个指令隐式的定义了两个cmake变量：
    ```<projectname>_BINARY_DIR```以及```<projectname>_SOURCE_DIR```</br>
    如果是内部编译，这两个变量就指向工程所在的路径，如果是外部编译的话，我们上述的链各个路径是需要修改的。
  - 为了统一，建议直接使用```PROJECT_BINARY_DIR```和```PROJECT_SOURCE_DIR```,这样即使修改了我们的项目名称，也不会影响这两个变量。

#### 4 message指令语法
+ message语法
  ```CmakeList
  MESSAGE([SEND_ERROR|STATUS|FATAL_ERROR] "要显示的信息" ...)
  ```
+ 注
  - 这个指令用于向终端输出用户定义的信息，包含了三中类型
    - ```SEND_ERROR```产生错误，生成过程被跳过
    - ```STATUS```输出前缀为```-```的信息
    - ```FATAL_ERROR```立即终止所有的cmake过程

#### 5 基本语法规则
  我们这边列举最简单的语法规则
  + 变量使用```${}```的方式取值，但是```IF```语句中直接使用变量名取值。
  + ```指令(参数1 参数2 ...)```参数使用括弧括起来，参数之间使用空格或者分号分开。
  例如：```ADD_EXECUTABLE(hello main.c func.c)```或者```ADD_EXECUTABLE(hello main.c;func.c)```
  + 指令是大小写无关的，参数变量是大小写相关的，但是我们尽量全部大写指令
  + 关于语法的疑惑。cmake的语法还是比较灵活而且考虑到各种情况的，比如
    ```SET(SRC_LIST main.c)  ```==```SET(SRC_LIST "main.c")```,这个是没有区别的。</br>
    但是一个源文件的名字是```fu nc.c```，中间是有空格的，那么必须添加双引号。</br>
    ```SET(SRC_LIST "fu nc.c")```</br>如果是```SET(SRC_LIST fu nc.c)```则会报错。</br>
    此外，你可以忽略掉source文件列表的源文件后缀。但是我们尽量还是不要偷懒，以避免源文件中真的存在``` main main.c```这样的冲突。

#### 6 清理工程
    同经典```autotools```系列工具一样，运行```make clean```可以对构建的结果进行清理。

### <span id='title_05'>五 内部构建和外部构建</span>
#### 1 解释
  + 内部构建(in-source build) 内部构建就是和源文件在一起构建工程。内部构建之后，我们会在源文件目录下面生成很多临时文件。
  + 外部构建(out-of-source build) 外部构建和源文件不在同一个目录下面。
  + 因为cmake没有理想的办法删除上面的相关的临时文件，所以我们尽量使用外部构建。
#### 2 cmake 外部构建的步骤
  + 首先，创建源文件的目录，编辑好我们的源文档，之后查看相关的文件目录```PROJECT_DIR```。
  + 创建外部构建的目录```build```
  + 我们进入build目录里面，执行我们```cmake PROJECT_DIR```命令，之后我们就生成了编译需要的makefile和其他中间文件。
  + 运行make构建工程，就会在我们的build里面发现我们要得到的目标文件。
#### 3 cmake外部构建简单的例子
  + 我们源文件的目录，我们创建build文件，来在里面外部构建项目
  ```
  ├── CMakeLists.txt
  ├── build
  └── hello.c
  ```
  + ```cd build``` 执行``` cmake ..```,我们可以看见生成了我们编译需要的```makefile```和其他中间文件
  ```
  ├── CMakeLists.txt
  ├── build
  │   ├── CMakeCache.txt
  │   ├── CMakeFiles
  │   ├── Makefile
  │   └── cmake_install.cmake
  └── hello.c
  ```

  + 执行```make```
   我们可以看见我们生成的目标文件hello
   ```
   ├── CMakeLists.txt
   ├── build
   │   ├── CMakeCache.txt
   │   ├── CMakeFiles
   │   ├── Makefile
   │   ├── cmake_install.cmake
   │   └── hello
   └── hello.c
   ```


   
