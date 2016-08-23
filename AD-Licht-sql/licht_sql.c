#include <stdio.h>
#include <readMCP.h>

#include<mysql.h>

#include"licht_sql.h"

int main (void)
{
  int i;
  MYSQL *mySql;  

  mySql = mysql_init(NULL);

  if (mysql_library_init(0, NULL, NULL))
  {
    fprintf(stderr, "could not initialize MySQL library\n");
    exit(1);
  }
  else
    printf("\n MySQL library initialized \n"); 
  
  if ( mysql_real_connect (
	mySql,		/* Zeiger auf MySql-Handler	  */
	"localhost",	/* Host-Name 			  */
	"prog_lux",	/* User-Name 			  */
	"lux",		/* Passwort für user-name	  */
	"prog_lux",	/* Name der Datenbank 		  */
	0,		/* Port (default = 0) 		  */
	NULL,		/* Socket (default = NULL) 	  */
	0 		/* Flags ( in diesem Fahl keine ) */ ) == NULL) 
	{
	  fprintf (stderr, "could not establish a connection to the MySql server : mysql_real_connenct" 
			  "%u (%s)",mysql_errno (mySql), mysql_error(mySql));
	}
  else
    printf("\n Connection to the MySQL server successfully establish \n");
 
   

  mcpSetup();
  //lux - widerstand in k Ohm
  scale_t skala[] = {
	{0.1,100    },
	{0.2, 70    },
	{0.3, 50    },
	{0.4, 38    },
	{0.5, 35    },
	{0.6, 33    },
	{0.7, 31    },
	{0.8, 30    },
	{0.9, 29    },
	{  1, 27    },
	{  2, 19    },
	{  3, 15    },
	{  4, 13    },
	{  5, 11    },
	{  6,  9    },
	{  7,  8.5  },
	{  8,  8    },
	{  9,  7.5  },
	{ 10,  7.0  },
	{ 20,  5.0  },
	{ 30,  4.0  },
	{ 40,  3.3  },
	{ 50,  3.0  },
	{ 60,  2.7  },
	{ 70,  2.5  },
	{ 80,  2.3  },
	{ 90,  2.1  },
	{100,  1.9  },
	{200,  1.5  },
	{300,  1.1  },
	{400,  1.0  },
	{500,  0.95 },
	{600,  0.8  },
	{700,  0.7  },
	{800,  0.65 },
	{900,  0.5  },
	{1000, 0.48 }
};
  int index = 0;

  float v;	
  float lux;
  float r; 
  float temp[10];
  float ps;
  float slux;  

  while (1)
  {
    while (1)
    {	
       
      r = (10 * readMcpChannel(2)) / ( 3.3 - readMcpChannel(2) );
      v = readMcpChannel(2);
   
      int skalaSize = sizeof(skala) / sizeof(scale_t);

      for (i = 0 ; i < skalaSize ; i++ )
      {
	temp[0] = skala[i].res   - r;
	temp[1] = skala[i+1].res - r;
	
	if (  i + 1 == skalaSize || ((temp[0] < 0) ? (temp[0] * -1) : (temp[0])) <= ((temp[1] < 0) ? (temp[1] * -1) : (temp[1])) )
	{ 
	  ps = 2 - (r / skala[i].res) ;
	  slux = skala[i].lux;
	  lux = skala[i].lux * ps;
	  
  
	  break;
	}
		      
      }
      char query[160];
      sprintf(query, "INSERT INTO prog_lux (datum, zeit, spannung, widerstand, lux, prozentsatz, skala_lux) VALUES(CURDATE(), CURTIME(), %f ,%f ,%f, %f, %f)", v ,r ,lux, ps, slux);
	
  

      mysql_query( mySql, query);
      system("clear");   
  
      printf("\n Query %s \n", query);
    
      printf("\"Licht\"  - Lux: %0.3F\n", lux);	
      printf("         - R  : %0F  \n", r);
      printf("         - V  : %0F  \n", v);
      printf("    - PS + Lux: %F, %F\n", ps, slux);
      delay(1000);
    }	
  }
}
