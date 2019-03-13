create table employe(
numss number(15),
primary key(numss),
nome varchar2(20), prenome varchar2(20),
villee varchar2(9),
datenais date
);

create table projet(
numproj number,
primary key(numproj),
nomproj varchar2(20),
respProj number,
foreign key (respProj) references employe(numss),
villep varchar2(5),
budget number
);

desc employe;
