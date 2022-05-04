## 数据表介绍

1. 学生表
   Student(SId,Sname,Sage,Ssex)
   SId 学生编号,Sname 学生姓名,Sage 出生年月,Ssex 学生性别

2. 课程表
   Course(CId,Cname,TId)
   CId 课程编号,Cname 课程名称,TId 教师编号

3. 教师表
   Teacher(TId,Tname)
   TId 教师编号,Tname 教师姓名

4. 成绩表
   SC(SId,CId,score)
   SId 学生编号,CId 课程编号,score 分数

## 插入数据

### 学生表 Student

```sql
create table Student(SId varchar(10),Sname varchar(10),Sage datetime,Ssex varchar(10));
insert into Student values('01' , '赵雷' , '1990-01-01' , '男');
insert into Student values('02' , '钱电' , '1990-12-21' , '男');
insert into Student values('03' , '孙风' , '1990-12-20' , '男');
insert into Student values('04' , '李云' , '1990-12-06' , '男');
insert into Student values('05' , '周梅' , '1991-12-01' , '女');
insert into Student values('06' , '吴兰' , '1992-01-01' , '女');
insert into Student values('07' , '郑竹' , '1989-01-01' , '女');
insert into Student values('09' , '张三' , '2017-12-20' , '女');
insert into Student values('10' , '李四' , '2017-12-25' , '女');
insert into Student values('11' , '李四' , '2012-06-06' , '女');
insert into Student values('12' , '赵六' , '2013-06-13' , '女');
insert into Student values('13' , '孙七' , '2014-06-01' , '女');
```

### 科目表 Course

```sql
create table Course(CId varchar(10),Cname nvarchar(10),TId varchar(10));
insert into Course values('01' , '语文' , '02');
insert into Course values('02' , '数学' , '01');
insert into Course values('03' , '英语' , '03');
```

### 教师表 Teacher

```sql
create table Teacher(TId varchar(10),Tname varchar(10));
insert into Teacher values('01' , '张三');
insert into Teacher values('02' , '李四');
insert into Teacher values('03' , '王五');
```

### 成绩表 SC

```sql
create table SC(SId varchar(10),CId varchar(10),score decimal(18,1));
insert into SC values('01' , '01' , 80);
insert into SC values('01' , '02' , 90);
insert into SC values('01' , '03' , 99);
insert into SC values('02' , '01' , 70);
insert into SC values('02' , '02' , 60);
insert into SC values('02' , '03' , 80);
insert into SC values('03' , '01' , 80);
insert into SC values('03' , '02' , 80);
insert into SC values('03' , '03' , 80);
insert into SC values('04' , '01' , 50);
insert into SC values('04' , '02' , 30);
insert into SC values('04' , '03' , 20);
insert into SC values('05' , '01' , 76);
insert into SC values('05' , '02' , 87);
insert into SC values('06' , '01' , 31);
insert into SC values('06' , '03' , 34);
insert into SC values('07' , '02' , 89);
insert into SC values('07' , '03' , 98);
```

## 练习题目

1. 查询" 01 "课程比" 02 "课程成绩高的学生的信息及课程分数

   1.1 查询同时存在" 01 "课程和" 02 "课程的情况

   1.2 查询存在" 01 "课程但可能不存在" 02 "课程的情况(不存在时显示为 null )

   1.3 查询不存在" 01 "课程但存在" 02 "课程的情况

2. 查询平均成绩大于等于 60 分的同学的学生编号和学生姓名和平均成绩

3. 查询在 SC 表存在成绩的学生信息

4. 查询所有同学的学生编号、学生姓名、选课总数、所有课程的总成绩(没成绩的显示为 null )

   4.1 查有成绩的学生信息

5. 查询「李」姓老师的数量

6. 查询学过「张三」老师授课的同学的信息

7. 查询没有学全所有课程的同学的信息

8. 查询至少有一门课与学号为" 01 "的同学所学相同的同学的信息

9. 查询和" 01 "号的同学学习的课程 完全相同的其他同学的信息

10. 查询没学过"张三"老师讲授的任一门课程的学生姓名

11. 查询两门及其以上不及格课程的同学的学号，姓名及其平均成绩

12. 检索" 01 "课程分数小于 60，按分数降序排列的学生信息

13. 按平均成绩从高到低显示所有学生的所有课程的成绩以及平均成绩

14. 查询各科成绩最高分、最低分和平均分：以如下形式显示：课程 ID，课程 name，最高分，最低分，平均分，及格率，中等率，优良率，优秀率。及格为>=60，中等为：70-80，优良为：80-90，优秀为：>=90。要求输出课程号和选修人数，查询结果按人数降序排列，若人数相同，按课程号升序排列

15. 按各科成绩进行排序，并显示排名， Score 重复时保留名次空缺

    15.1 按各科成绩进行排序，并显示排名， Score 重复时合并名次

16. 查询学生的总成绩，并进行排名，总分重复时保留名次空缺

    16.1 查询学生的总成绩，并进行排名，总分重复时不保留名次空缺

17. 统计各科成绩各分数段人数：课程编号，课程名称，[100-85]，[85-70]，[70-60]，[60-0] 及所占百分比
18. 查询各科成绩前三名的记录
19. 查询每门课程被选修的学生数
20. 查询出只选修两门课程的学生学号和姓名
21. 查询男生、女生人数
22. 查询名字中含有「风」字的学生信息
23. 查询同名同性学生名单，并统计同名人数
24. 查询 1990 年出生的学生名单
25. 查询每门课程的平均成绩，结果按平均成绩降序排列，平均成绩相同时，按课程编号升序排列
26. 查询平均成绩大于等于 85 的所有学生的学号、姓名和平均成绩
27. 查询课程名称为「数学」，且分数低于 60 的学生姓名和分数
28. 查询所有学生的课程及分数情况（存在学生没成绩，没选课的情况）
29. 查询任何一门课程成绩在 70 分以上的姓名、课程名称和分数
30. 查询不及格的课程
31. 查询课程编号为 01 且课程成绩在 80 分以上的学生的学号和姓名
32. 求每门课程的学生人数
33. 成绩不重复，查询选修「张三」老师所授课程的学生中，成绩最高的学生信息及其成绩
34. 成绩有重复的情况下，查询选修「张三」老师所授课程的学生中，成绩最高的学生信息及其成绩
35. 查询不同课程成绩相同的学生的学生编号、课程编号、学生成绩
36. 查询每门功成绩最好的前两名
37. 统计每门课程的学生选修人数（超过 5 人的课程才统计）。
38. 检索至少选修两门课程的学生学号
39. 查询选修了全部课程的学生信息
40. 查询各学生的年龄，只按年份来算
41. 按照出生日期来算，当前月日 < 出生年月的月日则，年龄减一
42. 查询本周过生日的学生
43. 查询下周过生日的学生
44. 查询本月过生日的学生
45. 查询下月过生日的学生

## 题目答案

1. 查询" 01 "课程比" 02 "课程成绩高的学生的信息及课程分数。因为需要全部的学生信息，则需要在sc表中得到符合条件的SId后与student表进行join，可以left join 也可以 right join

   ```sql
   select * from Student RIGHT JOIN (
       select t1.SId, class1, class2 from
             (select SId, score as class1 from sc where sc.CId = '01')as t1, 
             (select SId, score as class2 from sc where sc.CId = '02')as t2
       where t1.SId = t2.SId AND t1.class1 > t2.class2
   )r 
   on Student.SId = r.SId;
   ```

   ```sql
   select * from  (
       select t1.SId, class1, class2 
       from
           (SELECT SId, score as class1 FROM sc WHERE sc.CId = '01') AS t1, 
           (SELECT SId, score as class2 FROM sc WHERE sc.CId = '02') AS t2
       where t1.SId = t2.SId and t1.class1 > t2.class2
   ) r
   LEFT JOIN Student
   ON Student.SId = r.SId;
   ```

   1.1 查询同时存在" 01 "课程和" 02 "课程的情况

   ```sql
   select * from 
       (select * from sc where sc.CId = '01') as t1, 
       (select * from sc where sc.CId = '02') as t2
   where t1.SId = t2.SId;
   ```

   1.2 查询存在" 01 "课程但可能不存在" 02 "课程的情况(不存在时显示为 null )

   ```sql
   select * from 
   (select * from sc where sc.CId = '01') as t1
   left join 
   (select * from sc where sc.CId = '02') as t2
   on t1.SId = t2.SId;
   ```

   ```sql
   select * from 
   (select * from sc where sc.CId = '02') as t2
   right join 
   (select * from sc where sc.CId = '01') as t1
   on t1.SId = t2.SId;
   ```

   1.3 查询不存在" 01 "课程但存在" 02 "课程的情况

   ```sql
   select * from sc
   where sc.SId not in (
       select SId from sc 
       where sc.CId = '01'
   ) 
   AND sc.CId= '02';
   ```

2. 查询平均成绩大于等于 60 分的同学的学生编号和学生姓名和平均成绩。根据学生ID把成绩分组，对分组中的score求平均值，最后在选取结果中AVG大于60的即可

   ```sql
   select student.SId,sname,ss from student,(
       select SId, AVG(score) as ss from sc  
       GROUP BY SId 
       HAVING AVG(score)> 60
       )r
   where student.sid = r.sid;
   ```

   ```sql
   select Student.SId, Student.Sname, r.ss from Student right join(
         select SId, AVG(score) AS ss from sc
         GROUP BY SId
         HAVING AVG(score)> 60
   )r on Student.SId = r.SId;
   ```

   ```sql
   select s.SId,ss,Sname from(
   select SId, AVG(score) as ss from sc  
   GROUP BY SId 
   HAVING AVG(score)> 60
   )r left join 
   (select Student.SId, Student.Sname from
   Student)s on s.SId = r.SId;
   ```

3. 查询在 SC 表存在成绩的学生信息

   ```sql
   select DISTINCT student.*
   from student,sc
   where student.SId=sc.SId
   ```

4. 查询所有同学的学生编号、学生姓名、选课总数、所有课程的成绩总和。联合查询不显示没选课的学生

   ```sql
   select student.sid, student.sname,r.coursenumber,r.scoresum
   from student,
   (select sc.sid, sum(sc.score) as scoresum, count(sc.cid) as coursenumber from sc 
   group by sc.sid)r
   where student.sid = r.sid;
   ```

   显示没选课的学生

   ```sql
   select s.sid, s.sname,r.coursenumber,r.scoresum
   from (
       (select student.sid,student.sname 
       from student
       )s 
       left join 
       (select 
           sc.sid, sum(sc.score) as scoresum, count(sc.cid) as coursenumber
           from sc 
           group by sc.sid
       )r 
      on s.sid = r.sid
   );
   ```

   4.1 查有成绩的学生信息

   ```sql
   select * from student 
   where exists (select sc.sid from sc where student.sid = sc.sid);
   ```

   ```sql
   select * from student
   where student.sid in (select sc.sid from sc);
   ```

5. 查询「李」姓老师的数量

   ```sql
   select count(*)
   from teacher
   where tname like '李%';
   ```

6. 查询学过「张三」老师授课的同学的信息

   ```sql
   select student.* from student,teacher,course,sc
   where 
       student.sid = sc.sid 
       and course.cid=sc.cid 
       and course.tid = teacher.tid 
       and tname = '张三';
   ```

7. 查询没有学全所有课程的同学的信息

   ```sql
   select * from student
   where student.sid not in (
     select sc.sid from sc
     group by sc.sid
     having count(sc.cid)= (select count(cid) from course)
   );
   ```

8. 查询至少有一门课与学号为" 01 "的同学所学相同的同学的信息

   ```sql
   select * from student 
   where student.sid in (
       select sc.sid from sc 
       where sc.cid in(
           select sc.cid from sc 
           where sc.sid = '01'
       )
   );
   ```

9. 查询和" 01 "号的同学学习的课程完全相同的其他同学的信息

   ```sql
   select student.* from student 
   right join (
   	select b.sid from (
   		select sid from SC left join (
   			select cid from sc where sid='01'
   		)a on sc.CId=a.CId
   	)b group by b.SId 
   	having COUNT(b.sid)>2 and b.SId > '01'
   )c on Student.SId=c.SId
   ```

10. 查询没学过"张三"老师讲授的任一门课程的学生姓名

    ```sql
    select * from student
        where student.sid not in(
            select sc.sid from sc where sc.cid in(
                select course.cid from course where course.tid in(
                    select teacher.tid from teacher where tname = "张三"
                )
            )
        );
    ```

    ```sql
    select * from student
    where student.sid not in(
        select sc.sid from sc,course,teacher 
        where
            sc.cid = course.cid
            and course.tid = teacher.tid
            and teacher.tname= "张三"
    );
    ```

11. 查询两门及其以上不及格课程的同学的学号，姓名及其平均成绩

    ```sql
    select student.sid, student.sname, AVG(sc.score) from student,sc
    where 
        student.sid = sc.sid and sc.score<60
    group by sc.sid 
    having count(*)>1;
    ```

12. 检索" 01 "课程分数小于 60，按分数降序排列的学生信息

    ```sql
    select student.*, sc.score from student, sc
    where student.sid = sc.sid
    and sc.score < 60
    and cid = "01"
    ORDER BY sc.score DESC;
    ```

13. 按平均成绩从高到低显示所有学生的所有课程的成绩以及平均成绩

    ```sql
    select *  from sc 
    left join (
        select sid,avg(score) as avscore from sc 
        group by sid
        )r 
    on sc.sid = r.sid
    order by avscore desc;
    ```

14. 查询各科成绩最高分、最低分和平均分

    ```sql
    select 
    sc.CId ,
    max(sc.score)as 最高分,
    min(sc.score)as 最低分,
    AVG(sc.score)as 平均分,
    count(*)as 选修人数,
    sum(case when sc.score>=60 then 1 else 0 end )/count(*)as 及格率,
    sum(case when sc.score>=70 and sc.score<80 then 1 else 0 end )/count(*)as 中等率,
    sum(case when sc.score>=80 and sc.score<90 then 1 else 0 end )/count(*)as 优良率,
    sum(case when sc.score>=90 then 1 else 0 end )/count(*)as 优秀率 
    from sc
    GROUP BY sc.CId
    ORDER BY count(*)DESC, sc.CId ASC
    ```

15. 按各科成绩进行排序，并显示排名， Score 重复时保留名次空缺

    ```sql
    select a.cid, a.sid, a.score, count(b.score)+1 as rank
    from sc as a 
    left join sc as b 
    on a.score<b.score and a.cid = b.cid
    group by a.cid, a.sid,a.score
    order by a.cid, rank ASC;
    ```

16. 查询学生的总成绩，并进行排名，总分重复时不保留名次空缺

    ```sql
    set @crank=0;
    select q.sid, total, @crank := @crank +1 as rank from(
    select sc.sid, sum(sc.score) as total from sc
    group by sc.sid
    order by total desc)q;
    ```

17. 统计各科成绩各分数段人数：课程编号，课程名称，[100-85]，[85-70]，[70-60]，[60-0] 及所占百分比

    ```sql
    select course.cname, course.cid,
    sum(case when sc.score<=100 and sc.score>85 then 1 else 0 end) as "[100-85]",
    sum(case when sc.score<=85 and sc.score>70 then 1 else 0 end) as "[85-70]",
    sum(case when sc.score<=70 and sc.score>60 then 1 else 0 end) as "[70-60]",
    sum(case when sc.score<=60 and sc.score>0 then 1 else 0 end) as "[60-0]"
    from sc left join course
    on sc.cid = course.cid
    group by sc.cid;
    ```

18. 查询各科成绩前三名的记录

    ```sql
    select * from sc
    where (
    select count(*) from sc as a 
    where sc.cid = a.cid and sc.score<a.score 
    )< 3
    order by cid asc, sc.score desc;
    ```

    ```sql
    select a.sid,a.cid,a.score from sc a 
    left join sc b on a.cid = b.cid and a.score<b.score
    group by a.cid, a.sid
    having count(b.cid)<3
    order by a.cid;
    ```

19. 查询每门课程被选修的学生数

    ```sql
    select cid, count(sid) from sc 
    group by cid;
    ```

20. 查询出只选修两门课程的学生学号和姓名

    ```sql
    select student.sid, student.sname from student
    where student.sid in
    (select sc.sid from sc
    group by sc.sid
    having count(sc.cid)=2
    );
    ```

    ```sql
    select student.SId,student.Sname
    from sc,student
    where student.SId=sc.SId  
    GROUP BY sc.SId
    HAVING count(*)=2；
    ```

21. 查询男生、女生人数

    ```sql
    select ssex, count(*) from student
    group by ssex;
    ```

22. 查询名字中含有「风」字的学生信息

    ```sql
    select *
    from student 
    where student.Sname like '%风%'
    ```

23. 查询同名学生名单，并统计同名人数

    ```sql
    select sname, count(*) from student
    group by sname
    having count(*)>1;
    ```

24. 查询 1990 年出生的学生名单

    ```sql
    select *
    from student
    where YEAR(student.Sage)=1990;
    ```

25. 查询每门课程的平均成绩，结果按平均成绩降序排列，平均成绩相同时，按课程编号升序排列

    ```sql
    select sc.cid, course.cname, AVG(SC.SCORE) as average from sc, course
    where sc.cid = course.cid
    group by sc.cid 
    order by average desc,cid asc;
    ```

26. 查询平均成绩大于等于 85 的所有学生的学号、姓名和平均成绩

    ```sql
    select student.sid, student.sname, AVG(sc.score) as aver from student, sc
    where student.sid = sc.sid
    group by sc.sid
    having aver > 85;
    ```

27. 查询课程名称为「数学」，且分数低于 60 的学生姓名和分数

    ```sql
    select student.sname, sc.score from student, sc, course
    where student.sid = sc.sid
    and course.cid = sc.cid
    and course.cname = "数学"
    and sc.score < 60;
    ```

28. 查询所有学生的课程及分数情况（存在学生没成绩，没选课的情况）

    ```sql
    select student.sname, cid, score from student
    left join sc
    on student.sid = sc.sid;
    ```

29. 查询任何一门课程成绩在 70 分以上学生的姓名、课程名称和分数

    ```sql
    select student.sname, course.cname,sc.score from student,course,sc
    where sc.score>70
    and student.sid = sc.sid
    and sc.cid = course.cid;
    ```

30. 查询存在不及格的课程

    ```sql
    select cid from sc
    where score< 60
    group by cid;
    ```

    ```sql
    select DISTINCT sc.CId
    from sc
    where sc.score <60;
    ```

31. 查询课程编号为 01 且课程成绩在 80 分及以上的学生的学号和姓名

    ```sql
    select student.sid,student.sname 
    from student,sc
    where cid="01"
    and score>=80
    and student.sid = sc.sid;
    ```

32. 求每门课程的学生人数

    ```sql
    select sc.CId,count(*) as 学生人数
    from sc
    GROUP BY sc.CId;
    ```

33. 成绩不重复，查询选修「张三」老师所授课程的学生中，成绩最高的学生信息及其成绩

    ```sql
    select student.*, sc.score, sc.cid from student, teacher, course,sc 
    where teacher.tid = course.tid
    and sc.sid = student.sid
    and sc.cid = course.cid
    and teacher.tname = "张三"
    having max(sc.score);
    ```

    ```sql
    select student.*, sc.score, sc.cid from student, teacher, course,sc 
    where teacher.tid = course.tid
    and sc.sid = student.sid
    and sc.cid = course.cid
    and teacher.tname = "张三"
    order by score desc
    limit 1;
    ```

34. 成绩有重复的情况下，查询选修「张三」老师所授课程的学生中，成绩最高的学生信息及其成绩

    ```sql
    select student.*, sc.score, sc.cid from student, teacher, course,sc 
    where teacher.tid = course.tid
    and sc.sid = student.sid
    and sc.cid = course.cid
    and teacher.tname = "张三"
    and sc.score = (
        select Max(sc.score) 
        from sc,student, teacher, course
        where teacher.tid = course.tid
        and sc.sid = student.sid
        and sc.cid = course.cid
        and teacher.tname = "张三"
    );
    ```

35. 查询不同课程成绩相同的学生的学生编号、课程编号、学生成绩

    ```sql
    select  a.cid, a.sid,  a.score from sc as a
    inner join 
    sc as b
    on a.sid = b.sid
    and a.cid != b.cid
    and a.score = b.score
    group by cid, sid;
    ```

36. 查询每门功成绩最好的前两名

    ```sql
    select a.sid,a.cid,a.score from sc as a 
    left join sc as b 
    on a.cid = b.cid and a.score<b.score
    group by a.cid, a.sid
    having count(b.cid)<2
    order by a.cid;
    ```

37. 统计每门课程的学生选修人数（超过 5 人的课程才统计）

    ```sql
    select sc.cid, count(sid) as cc from sc
    group by cid
    having cc >5;
    ```

38. 检索至少选修两门课程的学生学号

    ```sql
    select sid, count(cid) as cc from sc
    group by sid
    having cc>=2;
    ```

39. 查询选修了全部课程的学生信息

```sql
select student.*
from sc ,student 
where sc.SId=student.SId
GROUP BY sc.SId
HAVING count(*) = (select DISTINCT count(*) from course )
```

40. 查询各学生的年龄，只按年份来算

    ```
    
    ```

41. 按照出生日期来算，当前月日 < 出生年月的月日则，年龄减一

    ```sql
    select student.SId as 学生编号,student.Sname  as  学生姓名,
    TIMESTAMPDIFF(YEAR,student.Sage,CURDATE()) as 学生年龄
    from student
    ```

42. 查询本周过生日的学生

    ```sql
    select *
    from student 
    where WEEKOFYEAR(student.Sage)=WEEKOFYEAR(CURDATE());
    ```

43. 查询下周过生日的学生

    ```sql
    select *
    from student 
    where WEEKOFYEAR(student.Sage)=WEEKOFYEAR(CURDATE())+1;
    ```

44. 查询本月过生日的学生

    ```sql
    select *
    from student 
    where MONTH(student.Sage)=MONTH(CURDATE());
    ```

45. 查询下月过生日的学生

    ```sql
    select *
    from student 
    where MONTH(student.Sage)=MONTH(CURDATE())+1;
    ```

    

## 参考文献

[50道SQL练习题及答案与详细分析](https://blog.csdn.net/huaxiawudi/article/details/82288044?ops_request_misc=%7B%22request%5Fid%22%3A%22164976248816780261978565%22%2C%22scm%22%3A%2220140713.130102334.pc%5Fblog.%22%7D&request_id=164976248816780261978565&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~first_rank_ecpm_v1~rank_v31_ecpm-2-82288044.nonecase&utm_term=SQL&spm=1018.2226.3001.4450)