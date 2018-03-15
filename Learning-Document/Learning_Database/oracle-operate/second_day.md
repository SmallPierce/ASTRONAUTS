
目标：
-----
+ <a href="#H-1">1 多表查询编写</a>
+ <a href="#H-2">2 子查询编写</a>
+ <a href="#H-3">3 集合运算</a>
+ <a href="#H-4">4 数据的增删改操作</a>
+ <a href="#H-5">5 top-N问题的解决</a>
+ <a href="#H-6">6 事物的相关概念</a>

## <a name="H-1">一 多表查询</a>
+ 1.1 笛卡尔积就是

```
  a{1,2,3} b{3,2,1} a*b={(1,1,),(1,2,),(1,3),(2,1),(2,2),(2,3)}
```

  就是两个集合形成一个序列对集合
  对于两个表的笛卡尔积，我们需要一个过滤条件，对于n个表的笛卡尔积，我们需要n-1个条件进行过滤
  在sql中多表查询，笛卡尔积采用的是交叉连接，生成临时的笛卡尔积表

+ 1.2 内连接：可以这么理解，俩个表先采用交叉连接，再通过加上限制条件（sql中通过加上on关键字），剔除掉
      不符合要求的行得到的子集，得到的结果就是内连接。
+ 1.3 等值链接： 我们只用两个表中的公共的项目，可以最后实现我们的等值链接，通过一个等值的数据对我们的
      笛卡尔集的表进行相关的筛选。
```sql
    SELECT e.empno,e.ename,e.sal,d.dname
    from emp e, dept d
    WHERE e.deptno=d.deptno
    ORDER BY d.dname;
```

>统计不同部门的人数

```sql
    SELECT d.deptno,d.dname,COUNT(e.empno)
    FROM dept d,emp e
    WHERE d.deptno=e.deptno
    GROUP BY d.deptno,d.dname;
```
+ 1.4 不等值链接：
      可以根据范围进行相关的筛选</br>
```sql
    SELECT e.empno,e.ename,e.sal,s.grade FROM emp e, salgrade s WHERE e.sal>=s.losal and e.sal<=s.hisal;
```
+ 1.5 左外链接

+ 1.6 右外链接
      要显示右边的数据，那么需要在左边的等号的时候加上（+）
      e表的部门编号比较少，d表的比较多，所以要在e表后面加
```sql
    SELECT d.deptno,d.dname,COUNT(e.empno)
    FROM dept d,emp e
    WHERE e.deptno(+)=d.deptno
    GROUP BY d.DEPTNO,d.DNAME
    ORDER BY d.DEPTNO;
```
      对count(*)和count(e.empno)的区别：
      count（*）只要一行不为空，可以是多个列不为空，有一行列不为空，那就不为空
      count（e.empno）：只有e.empno不为空，才会被统计上

+ 1.7 自查询
     就是与自己进行多表查询，之后就可以实现相关的查询
```sql
    SELECT e.ename||'的老板是'||nvl(b.ename,'his wife')
    FROM emp e,emp b
    where e.mgr=b.empno(+);
```

## <a name="H-2">二 子查询（sql嵌套sql)</a>
```sql
    SELECT * from emp where sal>(SELECT sal FROM emp where ename='SCOTT');
```

+ 2.1 关于子查询的十点注意事项
  + 2.1.1 合理的书写风格：要合理的进行相应的换行、缩进
  + 2.1.2 使用小括号
  + 2.1.3 主查询和子查询可以是不同的表，只要子查询返回的值主查询可以使用就可以
  + 2.1.4 可以在主查询的where 、select、 having、from后面放置子查询
  ```sql
  SELECT empno,ename,deptno,(SELECT dname FROM dept where deptno=10)from emp where deptno=10;
  ```
  having 后面增加子查询
  ```sql
  SELECT deptno,avg(sal) FROM emp  GROUP BY deptno HAVING avg(sal)>(SELECT avg(sal) from emp WHERE deptno=30 GROUP by deptno);
  ```
  + 2.1.5 一个select查询的结果可以看成一个表，在from后面可以直接使用
  + 2.1.6 不可以在主查询的group by后面放置子查询（sql语法规范）
  + 2.1.7 单行子查询只可以使用单行操作符，多行子查询可以使用多行操作符
      多行操作符有In，any all
  + 2.1.8 一般不在子查询中使用order by,但是在top-N问题中，我们必须使用order by
  + 2.1.9 一般先采用子查询（内查询），在执行主查询（外查询），但是相关子查询除外
  +2.1.10 子查询中的NULL值
## <a name="H-3">三 集合运算</a>
+ union 两个集合相同的部分保留一部分
+ union all 两个集合相同的部分都保留
+ intersect 两个集合交集：只保留两个集合相同的部分
+ minus 集合A-集合B，从A中减去A与B相同的部分，只保留A中与B不的部分。
  + 3.1 实例</br>
    + 3.1.1 查看部门号为10的表和部门号在（10，20）之间的记录的union集合，并按部门号排序。
    ```sql
    SELECT * FROM (SELECT* FROM emp WHERE deptno=10 UNION SELECT * FROM emp WHERE deptno in (10,20)) ORDER BY deptno ;
    ```
    + 3.1.2 保留上述共同部分的语句
    ```sql
    SELECT * FROM (SELECT * FROM emp WHERE deptno=10 UNION ALL SELECT * FROM emp WHERE deptno in (10,20)) ORDER BY deptno;
    ```
    + 3.1.3 求共同部分
    ```sql
    SELECT * FROM emp WHERE deptno in (10,30) INTERSECT SELECT * FROM emp WHERE deptno in (10,20);
    ```
    + 3.1.4 剔除相同的部分
    ```sql
    SELECT * FROM emp WHERE deptno in (10,20) MINUS SELECT * FROM emp WHERE deptno in (10,30);
    ```
    + 3.1.5 按照部门统计各部门不同工种的工资情况。
      + 第一步，按照deptno和job进行分组，查询deptno、job、sum(sal)
      + 第二步，数据直接按照deptno分组即可，与job无关，select只需查找deptno、sum(sal)
      + 第三步，数据不按任何条件分组，即group by null;select 查询sum(sal);
    ```sql
    SELECT deptno,job ,sum(sal) FROM emp GROUP BY deptno,job
    UNION SELECT deptno,TO_CHAR(null),SUM(sal) FROM emp GROUP by deptno
    UNION SELECT TO_NUMBER(null),TO_CHAR(null),SUM(sal) FROM emp ;
    ```

  + 3.2注意事项：
    + 3.2.1 union表达式中，前后检索的列必须数据类型一致，列数要一致。
      + 错误语法
      ```sql
      SELECT deptno,ename FROM emp WHERE conditon1 UNION SELECT ename ,deptno FROM emp WHERE conditon2
      ```
      + 正确语法
      ```sql
      SELECT deptno,ename FROM emp WHERE conditon1 UNION SELECT deptno,ename FROM emp WHERE conditon2
      ```
    + 3.2.2 集合的运算性能一般比较大
## <a name="H-4">四 数据库DML 增删查改</a>
+  3.1 insert 操作</br>

      语法： </br>
    ```sql
    insert into tablename （col1,col2,col3....） values (val1,val2,val3...)
      ```
   - 示例
      + 全部列插入
      ```sql
      INSERT into dept values(53,'53name','53loc');
      ```
      + 部分列插入(隐式插入null)
      ```sql
      INSERT INTO dept(deptno,dname) VALUES(10,'accouting');
      ```
      + 显式插入null
      ```sql
      INSERT INTO dept(deptno,dname,loc) VALUES(10,'accouting',null);
      ```
      + \&符号的使用（类似于c语言中的宏替换）
      ```sql
      INSERT INTO dept VALUES(&a,'&b','&c');
      ```
      oracle之后会要求你输入相关变量的值，完成插入操作。
      + 拷贝表的结构
        + 拷贝整个表，包括数据
        ```sql
        CREATE TABLE dept_03_13 as SELECT * FROM dept;
        ```
        + 只拷贝表结构，不拷贝数据，可以在建表的后面增加一条条件语句，只要条件永远为假，那么就没有数据完成匹配，就只会拷贝表结构。
        ```sql
        CREATE TABLE dept_03_13 AS SELECT * FROM dept   WHERE 1=2;
        ```
      + 批量插入
        ```sql
        CREATE TABLE dept_03_15 as SELECT deptno, dname FROM dept WHERE 1=2;
        INSERT INTO dept_03_15 SELECT deptno,dname FROM dept;
        SELECT * FROM dept_03_15;
        ```
+ 3.2 update 操作

  语法：</br>
    ```sql
    update table_name set col1=val1,col2=val2,col3=val3...where conditon
    ```
    + 示例
      + 更新表中的某个记录
      ```sql
        INSERT INTO EMP VALUES(7966,'TOM_CAT','CLERK',NULL,NULL,1500,NULL,30);
        UPDATE emp set sal=sal+100 WHERE ename='TOM_CAT';
        SELECT * FROM EMP WHERE ename='TOM_CAT;'
      ```
    + 注意：
      + update的时候。可以使用sal=null的格式
      + 使用update时，一定要加where条件，否则会修改表里面的所有数据
+ 3.2 delete 操作/truncate
delete语法：</br>
  ```sql
  delete from table_name where condition1 ...
  ```
   + 示例
     + 从emp表中删除TOM_CAT的员工记录
   ```sql
   DELETE FROM emp WHERE ename='TOM_CAT';
   ```

    + 注意：
      + 使用delete时，一定要加where条件，否则会修改表里面的所有数据
    + delete和truncate的区别
      + delete逐条删除表中的内容，truncate是先将表毁掉，之后再重新建立表。（由于delete使用频繁，oracle在对delete优化后，delete快于truncate）
      + delete是DML语句，truncate是DDL语句。DML语句可以闪回， DDL语句不可以闪回（闪回，一个操作错误之后并且commit之后，对应的撤回的行为）。
      + 由于delete是逐条操作语句，所以delete操作会产生碎片，truncate不会产生碎片。
        两个数据之间的数据被删除，删除的数据一一碎片，整理碎片，数据连续，行移动。
      + delete不会释放空间，truncate会释放空间。所以，delete可以回滚数据，而truncate是不可以回滚，确认表不在使用，可以使用truncate直接删除。
      + delete可以回滚rollback，truncate不可以回滚数据。


+ 3.3 批量的生成一个sql插入一个长10000的数据，之后查看delete和truncate的区别。
  + [shell脚本](Learning-Document/Learning_Database/oracle-operate/code/test.sh)，执行命令重定向后，生成一个批量插入数据的sql脚本。
  + 在oracle中执行sql脚本
    - @ sql脚本所在路径/脚本
    - start 脚本
  + 使用delete删除数据。
  + 使用truncate删除。
## <a name="H-5">五 事务相关 </a>
+ 事务的概念：
  - 事务， 是由有限的数据库操作序列组成的逻辑执行单元。这一系列的操作要不全部执行，要不全部放弃执行。
  - 事务的组成
    - 一个或者多个DML语句
    - 一个DDL语句
    - 一个DCL语句
  - 事务的特点，要不全部成功，要不全部失败。
  - 事务开始和结束
    - 开始：事务以DML语句开始，执行一系列的数据插入或者修改操作
    - 结束：
      - 1 提交结束:commit</br>
          隐私提交：执行DDL语句（如执行一个create表操作），正常退出
      - 2 显式回滚：rollback</br>
          隐式回滚：断电，宕机，异常退出等等。
  - 事务的特性：
    - 
