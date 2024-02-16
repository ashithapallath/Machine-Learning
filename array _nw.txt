create table stud_tb(stud_id int primary key, sname varchar2(20), tot_mark number);

insert into stud_tb(stud_id, sname, tot_mark) values (101, 'Lana', 98);
insert into stud_tb(stud_id, sname, tot_mark) values (102, 'Neha', 78);
insert into stud_tb(stud_id, sname, tot_mark) values (103, 'Amal', 65);
insert into stud_tb(stud_id, sname, tot_mark) values (104, 'Ganga', 99);
insert into stud_tb(stud_id, sname, tot_mark) values (105, 'Ganesh', 92);

select * from stud_tb;

create table topper(t_id int primary key, t_name varchar(20), t_marks number);
drop table topper;

declare
	cursor c1 is
	select stud_id, sname, tot_mark from stud_tb order by tot_mark desc;
	v_id stud_tb.stud_id%type;
	v_name stud_tb.sname%type;
	v_tot stud_tb.tot_mark%type;
	vcount number :=0;

Begin
	open c1;
		loop
			fetch c1 into v_id, v_name, v_tot;
			vcount:=vcount+1;
			if c1%notfound or vcount>3 then 
                exit;
			end if;
			insert into topper(t_id, t_name, t_marks) values (v_id, v_name, v_tot);
			commit;
		end loop;
	close c1;
end;
/

select * from topper;