
目标：
-----
+ 1 多表查询编写
+ 2 子查询编写
+ 3 集合运算
+ 4 数据的增删改操作
+ 5 top-N问题的解决
+ 6 事物的相关概念

## 一 多表查询
+ 笛卡尔积就是

```
  a{1,2,3} b{3,2,1} a*b={(1,1,),(1,2,),(1,3),(2,1),(2,2),(2,3)}
```

  就是两个集合形成一个序列对集合
  对于两个表的笛卡尔积，我们需要一个过滤条件，对于n个表的笛卡尔积，我们需要n-1个条件进行过滤
  在sql中多表查询，笛卡尔积采用的是交叉连接，生成临时的笛卡尔积表

+ 内连接：可以这么理解，俩个表先采用交叉连接，再通过加上限制条件（sql中通过加上on关键字），剔除掉
      不符合要求的行得到的子集，得到的结果就是内连接。
+ 等值链接： 我们只用两个表中的公共的项目，可以最后实现我们的等值链接，通过一个等值的数据对我们的
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
+ 不等值链接：
      可以根据范围进行相关的筛选</br>
```sql
    SELECT e.empno,e.ename,e.sal,s.grade FROM emp e, salgrade s WHERE e.sal>=s.losal and e.sal<=s.hisal;
```
+ 左外链接

+ 右外链接
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

+ 自查询
     就是与自己进行多表查询，之后就可以实现相关的查询
```sql
    SELECT e.ename||'的老板是'||nvl(b.ename,'his wife')
    FROM emp e,emp b
    where e.mgr=b.empno(+);
```

## 二 子查询（sql嵌套sql）
```sql
    SELECT * from emp where sal>(SELECT sal FROM emp where ename='SCOTT');
```

    关于子查询的十点注意事项
      1.合理的书写风格：要合理的进行相应的换行、缩进
      2.使用小括号
      3.主查询和子查询可以是不同的表，只要子查询返回的值主查询可以使用就可以
      4.可以在主查询的where 、select、 having、from后面放置子查询
```sql
    SELECT empno,ename,deptno,(SELECT dname FROM dept where deptno=10)from emp where deptno=10;
```
        having 后面增加子查询
        SELECT deptno,avg(sal) FROM emp  GROUP BY deptno HAVING avg(sal)>(SELECT avg(sal) from emp WHERE deptno=30 GROUP by deptno);
      5.一个select查询的结果可以看成一个表，在from后面可以直接使用
      6.不可以在主查询的group by后面放置子查询（sql语法规范）
      7.单行子查询只可以使用单行操作符，多行子查询可以使用多行操作符
      多行操作符有In，any all
      8.一般不在子查询中使用order by,但是在top-N问题中，我们必须使用order by
      9.一般先采用子查询（内查询），在执行主查询（外查询），但是相关子查询除外
      10.子查询中的NULL值
## 三 集合运算
+ union 两个集合相同的部分保留一部分
+ union all 两个集合相同的部分都保留
+ intersect 两个集合交集：只保留两个集合相同的部分
+ minus 集合A-集合B，从A中减去A与B相同的部分，只保留A中与B不的部分。
  + 实例</br>
    + 查看部门号为10的表和部门号在（10，20）之间的记录的union集合，并按部门号排序。
    ```sql
    SELECT * FROM (SELECT* FROM emp WHERE deptno=10 UNION SELECT * FROM emp WHERE deptno in (10,20)) ORDER BY deptno ;
    ```
    + 保留上述共同部分的语句
    ```sql
    SELECT * FROM (SELECT * FROM emp WHERE deptno=10 UNION ALL SELECT * FROM emp WHERE deptno in (10,20)) ORDER BY deptno;
    ```
    + 求共同部分
    ```sql
    SELECT * FROM emp WHERE deptno in (10,30) INTERSECT SELECT * FROM emp WHERE deptno in (10,20);
    ```
    + 剔除相同的部分
    ```sql
    SELECT * FROM emp WHERE deptno in (10,20) MINUS SELECT * FROM emp WHERE deptno in (10,30);
    ```
    + 按照部门统计各部门不同工种的工资情况。
      + 第一步，按照deptno和job进行分组，查询deptno、job、sum(sal)
      + 第二步，数据直接按照deptno分组即可，与job无关，select只需查找deptno、sum(sal)
      + 第三步，数据不按任何条件分组，即group by null;select 查询sum(sal);
    ```sql
    SELECT deptno,job ,sum(sal) FROM emp GROUP BY deptno,job
    UNION SELECT deptno,TO_CHAR(null),SUM(sal) FROM emp GROUP by deptno
    UNION SELECT TO_NUMBER(null),TO_CHAR(null),SUM(sal) FROM emp ;
    ```

  + 注意事项：
    + 1 union表达式中，前后检索的列必须数据类型一致
      + 错误语法
      ```sql
      SELECT deptno,ename FROM emp WHERE conditon1 UNION SELECT ename ,deptno FROM emp WHERE conditon2
      ```
      + 正确语法
      ```sql
      SELECT deptno,ename FROM emp WHERE conditon1 UNION SELECT deptno,ename FROM emp WHERE conditon2
      ```
    + 2 集合的运算性能一般比较大
