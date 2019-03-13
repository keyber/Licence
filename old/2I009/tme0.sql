select * from Athlete;
COLUMN nom FORMAT A20
COLUMN prenom FORMAT A17
COLUMN pays FORMAT A40

select nom, prenom from athlete where pays = 'Inde';

select prenom from athlete where nom = 'GOLD';

select pays from athlete where nom = 'AONO' and prenom = 'Ryo';

select sport, epreuve, nomAth,prenomAth from rangEpreuve where rang=1
order by sport, epreuve;

select distinct sport, epreuve, categorie, dateFin from rangEpreuve
order by dateFin;

select * from athlete where pays = 'France' and extract(year from dateNaissance) between 1995 and 2000;

select distinct a.*
from athlete a,RangEpreuve b, RangEpreuve e
where a.pays ='Suisse' and a.nom=b.nomAth and a.prenom=b.prenomAth and e.sport='Biathlon' and e.rang is null and e.nomAth=b.nomAth and e.prenomAth=b.prenomAth;
