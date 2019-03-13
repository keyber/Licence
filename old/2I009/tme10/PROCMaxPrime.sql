CREATE or REPLACE PROCEDURE PROCmaxprime ( P_Annee1 GAIN.annee%TYPE, P_Annee2 GAIN.annee%TYPE, Sponsor GAIN.sponsor%TYPE) IS
	AnneeSponsorMin GAIN.annee%TYPE;
	AnneeSponsorMax GAIN.annee%TYPE;
	V_Nom Joueur.nom%type;
	V_MaxPrime Gain.Prime%type;
	cursor C_MaxPrime is
	select nom, max(prime)
	from GAIN, JOUEUR
	where annee between P_Annee1 and P_Annee2 and gain.NuJoueur=joueur.NuJoueur
	group by nom;
BEGIN
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
	dbms_output.put_line(
		select min(annee),max(annee)
		from gain
		where ponsor);

END;
/
show err
