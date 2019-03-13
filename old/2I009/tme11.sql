1.3

select nomath, prenomath
from athlete natural join athletesequipe natural join rangEquipe natural join epreuve natural join sport
where rang =1 and nomsp='Biathlon' and nomep='relais 4x6km' and categorie='Femmes';

1.7

select a.aid, a.nomath, e.eqid
from AthletesEquipe ae full outer join Equipe e on e.eqid=ae.eqid
     	     	       full outer join Athlete a on ae.aid=a.aid
order by a.nomath, e.eqid;
/*Where a.nomath is null or e.eqid is null*/

1.8

select nomsp, nomEP, nomath, rang
from Sport natural join Epreuve natural join athlete natural join rangindividuel/* natural join (select * from rangindividuel, rangequipe)*/ 
order by sid, nomep, rang;

select nomsp, nomEP, categorie, nomath, rang
from Sport natural join Epreuve natural join athlete natural join ((select rang from rangequipe natural join athletesequipe) UNION (select rang from rangindividuel));


order by sid, nomep, categorie,rang;

desc Athlete;

desc Equipe;

desc epreuve;

COLUMN nomath FORMAT A20
COLUMN prenomath FORMAT A20;
