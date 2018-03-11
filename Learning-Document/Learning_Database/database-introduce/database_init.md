数据库的启动
======

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
