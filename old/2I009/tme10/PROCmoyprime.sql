CREATE or REPLACE PROCEDURE PROCmoyprime(P_lieutournoi GAIN.lieutournoi%TYPE, P_annee GAIN.annee%TYPE )
IS
V_moyenne GAIN.prime%TYPE;
FIN exception;
BEGIN
select AVG(prime)
into V_moyenne
from GAIN
where lieutournoi=P_lieutournoi and annee=P_annee;
if V_moyenne is null then raise FIN;
end if;
dbms_output.put_line(P_lieutournoi||' '||to_char(P_annee)||': '
||to_char(V_moyenne));
EXCEPTION
when FIN then dbms_output.put_line('Tournoi non répertorié');
END;
/
