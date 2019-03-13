@vider

create table employe(
numss number(15) check (length(numss)=15),
primary key(numss),
nome varchar2(20),
prenome varchar2(20),
villee varchar2(9) check (lower(villee)in('paris','lyon','marseille')),
datenais date
);

COLUMN numss FORMAT 999999999999999
COLUMN nome FORMAT A20
COLUMN prenome FORMAT A20
COLUMN villee FORMAT A20


create table projet(
numproj number,
primary key(numproj),
nomproj varchar2(20),
respProj number,
foreign key (respProj) references employe(numss),
villep varchar2(5),
budget number
);

COLUMN numproj FORMAT 999999
COLUMN nomproj FORMAT A6
COLUMN respproj FORMAT 999999999999999
COLUMN villep FORMAT A6

insert into employe values(123456789012345, 'Bon','jean','paris',to_date('23/01/5678','DD/MM/YYYY'));

insert into projet values(920537, 'nomduProjet','123456789012345','Paris',1);

select *
from projet;

select *
from employe;
