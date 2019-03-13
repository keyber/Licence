select s.nomSP
from sport s
where not exists (select * from epreuve e where e.sid=s.sid and e.dateFin-e.dateDebut<>0) ;

select s.nomSP
from sport s
where not exists(select * from epreuve e where e.sid=s.sid and e.categorie='Mixte');

//question 3
//ne marche pas
select distinct ae.eqid
from athletesequipe ae
where not exists (select*from rangindividuel r where r.aid=ae.aid and r.rang<=3);

//252
select ae.eqid
from athletesequipe ae
minus
select ae2.eqid
from rangindividuel r, athletesequipe ae2
where r.aid=ae2.aid and r.rang<=3;

//265
select distinct eqid
from equipe eq
where not exists (select * from rangindividuel r, athletesequipe ae where r.aid=ae.aid and r.rang<=3 and ae.eqid=eq.eqid and r.aid=ae.aid);

//252
select distinct eqid
from athletesequipe ae
where not exists (select * from rangindividuel r, athletesequipe ae2 where r.aid=ae2.aid and r.rang<=3 and ae2.eqid=ae.eqid and r.aid=ae2.aid);

//ex 4
select a.datenaissance, p.nomP
from pays p, athlete a
where a.codepays=p.codepays and a.datenaissance>=all (select a2.dateNaissance from athlete a2 where a2.datenaissance is not null);

//ex 5
select a.datenaissance, p.nomP
from pays p, athlete a
where a.codepays=p.codepays and a.datenaissance is not null and a.datenaissance>=all (select a2.dateNaissance from athlete a2 where a2.datenaissance is not null and a2.codepays=a.codepays);
