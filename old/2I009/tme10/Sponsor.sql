SET SERVEROUTPUT ON
SET VERIFY OFF
ACCEPT nomSp char PROMPT 'sponsor: '
execute PROCSponsor('&nomSp');
