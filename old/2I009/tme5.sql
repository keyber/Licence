select distinct p.nomP
from sport s, epreuve ep, equipe eq, rangEquipe r, pays p
where ep.categorie='Femmes' and ep.nomEp='relais 4x6km' and s.nomSp='Biathlon' and r.rang=1
and ep.sid=s.sid and ep.epid=r.epid and eq.codePays=p.codePays and r.eqid=eq.eqid;

6
select ath.nomath
from athlete ath
where exists (select *
      	     from epreuve e, rangIndividuel r
	     where e.epid=r.epid and ath.aid=r.aid)
     and exists (select *
      	     from epreuve ep, athletesEquipe ae, rangEquipe r
	     where ep.epid=r.epid and ath.aid=ae.aid and ae.eqid=r.eqid)
	     ;
7
select distinct a1.nomath
from athlete a1
where exists (select *
      	     from athlete a2
	     where a1.aid<>a2.aid and a1.nomAth=a2.nomAth);

8
select ath.nomAth
from athlete ath
where exists (select *
      	     from rangIndividuel r1, rangIndividuel r2
	     where r1.epid<>r2.epid and r1.aid=r2.aid and r1.aid=ath.aid);

9
select distinct r1.aid
from rangIndividuel r1
where r1.rang<4 and exists(select *
      		    	from rangIndividuel r2
			where r1.epid<>r2.epid and r2.rang is null and r2.aid=r1.aid);

10
select distinct r.aid
from rangIndividuel r
where r.rang<4;

TME
2

select ath.nomath, ath.prenomath, p.nomp, r.rang
from athlete ath, pays p, rangindividuel r, epreuve e, sport s
where e.nomep='1000m' and s.nomsp='Patinage de vitesse' and e.categorie='Femmes'
and ath.codepays=p.codepays and ath.aid=r.aid and e.sid=s.sid and e.epid=r.epid  ;

3
select ath.nomath, ath.prenomath
from athlete ath, epreuve e, sport s, rangEquipe r, athletesequipe ae
where e.nomep='relais 4x6km' and s.nomsp='Biathlon'and e.categorie='Femmes' and r.rang=1
and s.sid=e.sid and e.epid=r.epid and ae.eqid=r.eqid and ae.aid=ath.aid ;

4
select  s.nomsp 
from sport s, athlete ath, epreuve e, rangindividuel r 
where ath.nomath='LESSER'and ath.prenomath='Erik'and r.aid=ath.aid and s.sid=e.sid and e.epid=r.epid ;

5
select ath.nomAth
from athlete ath
where exists (select *
      	     from rangIndividuel r1, rangIndividuel r2, epreuve e, epreuve e2
	     where r1.epid<>r2.epid and r1.aid=r2.aid and r1.aid=ath.aid and e.epid=r1.epid
	     and e2.epid=r2.epid and e.sid<>e2.sid);


select 
from
where
