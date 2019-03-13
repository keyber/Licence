CREATE or REPLACE PROCEDURE PROCSponsor (Spons GAIN.sponsor%TYPE) IS
	AnneeSponsorMin GAIN.annee%TYPE;
	AnneeSponsorMax GAIN.annee%TYPE;
	V_Nom Joueur.nom%type;
	V_MaxPrime Gain.Prime%type;

	cursor C_MaxPrime is
	select nom, max(prime)
	from GAIN, JOUEUR
	where annee between AnneeSponsorMin and AnneeSponsorMax and gain.NuJoueur=joueur.NuJoueur and Spons = sponsor
	group by nom;
BEGIN
	select min(annee),max(annee) into AnneeSponsorMin, AnneeSponsorMax
	from gain
	where Spons = sponsor;
	open C_MaxPrime;
	loop
		fetch C_MaxPrime into V_Nom, V_MaxPrime;
		exit when C_MaxPrime%NOTFOUND;
		if C_Maxprime%ROWCOUNT=1 then 
			dbms_output.put_line('Plus forte prime gagnée par:');
		end if;
		dbms_output.put_line(rpad(V_Nom,14,'.')|| lpad(to_char(V_MaxPrime),8,'.')||' F');
	end loop;
	if C_MaxPrime%ROWCOUNT=0 then 
		dbms_output.put_line('Aucun tournoi n''est répertorié entre ces dates');
	end if;
	close C_MaxPrime;


END;
/
show err