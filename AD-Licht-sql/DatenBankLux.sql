BEGIN;



CREATE TABLE prog_lux
  (
    datum 	varchar(50),
    zeit  	varchar(50),
  	
    spannung    float,
    widerstand  float,
    lux		float,
    prozentsatz float,
    skala_lux   float
  ); 

COMMIT;
