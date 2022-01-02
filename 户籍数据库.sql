CREATE database HuKou;
--新建户籍管理系统数据库
use hukou;
CREATE Table HK
--新建户籍信息表
(
    Hno VARCHAR(20) PRIMARY KEY NOT NULL,--户号
    Hname VARCHAR(20) NOT NULL,--户主
    ID VARCHAR(20) NOT NULL,--户主身份证
    Adr VARCHAR(50) NOT NULL,--地址
    regdate DATETIME NOT NULL--登记日期
);
CREATE TABLE person 
--新建个人信息表
(
  ID varchar(20) NOT NULL,
  name varchar(20) NOT NULL,
  Sex char(2) NOT NULL check(sex in('男','女')),
  nation VARCHAR(10) NOT NULL,
  province varchar(10) NOT NULL,
  birthdata datetime NOT NULL,
  birthplace varchar(50) NOT NULL,
  liveplace VARCHAR(50) NOT NULL,
  Education varchar(10) NOT NULL,
  PRIMARY KEY(ID)
);

CREATE table relation
--人口关系表
(
    Hno VARCHAR(20) NOT NULL,--户号
    ID varchar(20) NOT NULL,--身份证
    name VARCHAR(20) NOT NULL,
    relat VARCHAR(20) NOT NULL,--户主或与户主关系
    indate DATETIME,--何时迁入
    wherein VARCHAR(20),--迁入地
    PRIMARY KEY(Hno,ID),
    FOREIGN KEY(Hno) REFERENCES HK(Hno),
    FOREIGN KEY(ID) REFERENCES person(ID)
);

CREATE Table Hout
--户口迁出信息表
(
    Hno char(20) NOT NULL,
    Hname varchar(10) NOT NULL,
    outdata datetime NOT NULL,
    originadr VARCHAR(50) NOT NULL,
    outadress varchar(50) NOT NULL,
    PRIMARY KEY(Hno,originadr,outadress) 
);

CREATE Table perout
--人口迁出信息表
(    
    ID varchar(20),
    name varchar(20) NOT NULL,
    outHno varchar(20),
    inHno VARCHAR(20),
    outdata datetime NOT NULL,
    PRIMARY KEY(ID,outHno,inHno)
);

CREATE Table Hdis
--户口注销表
(
    Hno varchar(20) PRIMARY KEY,
    name varchar(10) NOT NULL,
    disdata datetime NOT NULL,
    reason varchar(50),
    prove varchar(50)
);

CREATE Table operator
--管理员表
(
    username VARCHAR(20) PRIMARY KEY,
    password VARCHAR(20) NOT NULL,
    phone VARCHAR(20)
);


CREATE Trigger hukouinsert --添加户主关系触发器
after insert
on HK
for each row
insert into relation
values 
(new.Hno,new.ID,new.Hname,'户主',new.regdate,null);

DELIMITER $$
CREATE Trigger hkcheck--户主信息确认触发器
before insert
on HK
for each row
begin
    if (new.Hname<>(select name from person where person.ID=new.ID)) ||
    (new.id in (SELECT id from relation ))
    then
    SIGNAL SQLSTATE '45000' 
SET MESSAGE_TEXT = "身份信息错误或已被使用";
end if;
END$$
DELIMITER ;

drop trigger hkcheck;

CREATE Trigger deletehukouper --添加户口注销关联人口触发器
before delete
on HK
for each row
delete from relation
where Hno=old.Hno;

CREATE Trigger markdelete--记录删除户口触发器
after delete
on hk
for each row
insert into hdis
values(old.Hno,old.Hname,now(),null,null);


DELIMITER $$
CREATE Trigger hkout--户口迁出触发器
after update
on HK
for each row
    if old.Adr!=new.Adr then
    insert into hout
    VALUES(new.Hno,new.Hname,now(),old.Adr,new.Adr);
    end if;
DELIMITER ;
DROP trigger hkout;


DELIMITER $$
CREATE Trigger personout--人口迁出触发器
after update
on relation
for each row
    if old.Hno<>new.Hno then
    insert into perout
    VALUES(new.ID,new.name,old.Hno,new.Hno,now());
    end if;
DELIMITER ;

INSERT INTO operator
VALUES('admin','admin','18616512114');

CREATE View 无户籍居民
as
SELECT ID as 身份证号,name as 姓名,sex as 性别,nation as 民族,province as 祖籍,birthdata as 出生日,birthplace as 出生地,liveplace as 现居地,education as 学历
FROM person
WHERE ID not IN (SELECT ID FROM relation);

DELIMITER $$
CREATE Trigger personname--改名触发器
after update
on person
for each row
    if old.name<>new.name then
    update hk set Hname=new.name where hk.ID=new.ID;
    update relation set name=new.name where relation.ID=new.ID;
    update hout set Hname=new.name where hout.Hno in(SELECT Hno FROM hk where hk.ID=new.ID);
    update perout set name=new.name where perout.ID=new.ID;
    end if;
DELIMITER ;

DROP Trigger personname;

CREATE View hkpersonage--户籍居民年龄排序
as 
select hno as 户籍号,person.id as 身份证号,person.name as 姓名, year(NOW())-year(birthdata) as 年龄,liveplace as 现居地
FROM relation,person 
WHERE relation.ID=person.ID;

SELECT * FROM hkpersonage ORDER BY 年龄 DESC;--对户籍居民按年龄排序

DELIMITER $$
CREATE Trigger relationnamecheck--关系表姓名确认触发器
before update
on relation
for each row
    if (new.name<>(select name from person where person.ID=new.ID))
    then
    SIGNAL SQLSTATE '45000' 
SET MESSAGE_TEXT = "身份信息错误或已被使用";end if;
DELIMITER ;

SHOW TRIGGERs;

