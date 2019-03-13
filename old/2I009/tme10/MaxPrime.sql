SET SERVEROUTPUT ON
SET VERIFY OFF
ACCEPT A_Annee1 NUMBER PROMPT 'Année de départ: '
ACCEPT A_Annee2 NUMBER PROMPT 'Dernière année: '
execute PROCmaxprime(&A_Annee1, &A_Annee2);
