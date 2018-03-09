#数据库第一天
数据库的作用：是为了管理和存储数据，便于程序开发
常见的数据库:oracle db2(IBM) mysql sysbase SQLserver MongoDB(更灵活)
<a name="1">体系架构</a>
##一 oracle 体系架构
      实例+数据库组成
      客户端向数据库发送请求
      oracle数据库管理系统，通过各种的数据，依赖我们服务器的各种服务，之后在内存中完成相关的请求响应，这样的我们叫做实例（instance） =服务+内存
      数据存放在磁盘之中
      请求提交给PGA(程序全局区)---之后提交给SGA（系统全局区---之后SGA到DB（数据库区）中去那我们要用的数据

      数据库中有两个以上的实例，我们叫做集群。集群可以提高并发访问量，提高访问的效率。
      另外的是提高我们数据库系统的安全性

      表空间和数据文件
      逻辑上讲：表空间是由多个数据文件组成，位于实例上的，这个是在我们的内存中的。我们实例真正
      操作的是表空间
      物理上讲：我们的数据文件是位于磁盘上(dbf)
              三个文件：控制文件、日志文件和数据文件

      表空间 段  区  块之间的关系
      表空间是有段组成，段是区的集合，区是数据块的集合，数据块会被映射到磁盘上

##二 数据库的启动
   1 windows
      启动OracleServerORCL   (实例名，也是数据库的库名 )
      启动home1TNSListener    (监听服务，接受客户端的服务请求)
   2 linux启动oracle
      启动oracle数据库服务
        使用oracle 用户  su Oracle
      在用户下面使用
        sqlplus sys/ as sysdba
        SQL>startup
      停止数据库的服务
        shutdown immediate
        exit

      启动oracle数据库 监听服务
        lsnrctl start
      停止oracle监听服务
        关闭监听服务
        lsnrctl stop

##三 oracle 数据库的登录
      普通用户登录: sqlplus scott/tiger@orcl   sqlplus scott/tinger@//192.168.137.111/oracle
      sys用户登录: sqlplus sys / as sysdba
      解锁用户:  alter user scott accout unlock
      加锁用户:  alter user scott accout lock
      修改用户密码: alter user scott identified by tiger
      查看当前语言环境: select userenv('language') from  dual
