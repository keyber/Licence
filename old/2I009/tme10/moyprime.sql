ACCEPT A_lieutournoi PROMPT "Donnez le lieu du tournoi: "
ACCEPT A_annee NUMBER PROMPT "Donnez l'année: "
SET SERVEROUTPUT ON
SET VERIFY OFF
execute PROCmoyprime('&A_lieutournoi', &A_annee);
