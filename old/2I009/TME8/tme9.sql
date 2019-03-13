insert into Employe(numss,nome,prenome,villee,datenaiss) values (25345,'a','b','paris',to_Date('1/01/2000','dd/mm/YYYY'));

insert into Projet values(123,'proj',12345,'paris',2);

insert into Grille_sal values('admin',80000);

delete from employe where numss=90011;

alter table embauche drop constraint fk_emb_emp;
alter table embauche add constraint fk_emb_emp foreign key (NumSS) references Employe on delete cascade;

update employe set nome ='newnom';
delete from employe where nome='newnom';

select * from employe;

select * from projet;

drop table employe;

drop table embauche;
