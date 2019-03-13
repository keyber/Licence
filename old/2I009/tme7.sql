select s.nomSp, count(*)
from rangIndividuel r, sport s, epreuve e
where e.sid=s.sid and r.epid=e.epid and r.rang<=3
group by s.sid, s.nomSp;

select p.nomP, s.nomSp, count(distinct a.aid) as nb
from pays p, athlete a, rangindividuel r, epreuve e, sport s
where p.codePays=a.codePays and a.aid=r.aid and e.epid=r.epid and e.sid=s.sid and r.rang<=3
group by p.codePays, p.nomP, s.sid, s.nomSp
order by nb desc;

//3
select s.nsp
from sponsorise s, joueur j
where s.njo=j.njo
group by s.nSp
having count(distinct j.eq)= (select count(*) from equipe);

//4
select distinct s.nsp
from sponsorise s, joueur j
where s.njo=j.njo
group by s.nSp, j.eq
having count(distinct j.njo)= 1;

select m.eq1, sum(d.nbkm)
from  match m, match m2, dist d
where m.eq1=m2.eq1 and d.st1=m.st and d.st2=m2.st and m.dateM<m2.dateM and not exists (select * from match m3 where m3.eq1=m.eq1 and m3.dateM>m.dateM and m3.dateM<m2.dateM)
group by m.eq1;
