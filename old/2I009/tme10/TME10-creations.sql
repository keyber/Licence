create table Employe(       
			NumSS	number(5)		, 
			NomE  	varchar2(20) 	,
			PrenomE	varchar2(20) 	, 
			VilleE	varchar2(20) 	,  
			DateNaiss date 	   		 
			); 


create  table Projet(      
			NumProj	Number(3),
			NomProj	varchar2(20),
			RespProj	number,       
			VilleP	varchar2(20),       
			Budget		number	  
		    ); 

create table Grille_sal(       
			profil	varchar2(20),       
			salaire	number(7,2)
		     ); 


create table Embauche(       
			NumSS	number ,
			NumProj	number ,       
			DateEmb	date default sysdate,       
			Profil	varchar2(20)
	             ); 

SET LINESIZE 150
SET COLSEP |
COLUMN NUMSS FORMAT 999999
COLUMN NOME FORMAT A20
COLUMN PRENOME FORMAT A20
COLUMN VILLEE FORMAT A20

COLUMN NUMPROJ FORMAT 9999
COLUMN NOMPROJ FORMAT A20
COLUMN RESPPROJ FORMAT 999999
COLUMN VILLEP FORMAT A20
COLUMN BUDGET FORMAT 99999999

COLUMN DATEEMB FORMAT A15
COLUMN PROFIL FORMAT A20
COLUMN SALAIRE FORMAT 9999999999
