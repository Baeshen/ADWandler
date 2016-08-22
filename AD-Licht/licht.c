#include<stdio.h>
#include<readMCP.h>

#include"licht.h"

int main (void)
{
  int i;
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
  float lux;
  float r; 
  float temp[10];
  
  while (1)
  {
    while (1)
    {	
      delay(1000);
       
      r = (10 * readMcpChannel(2)) / ( 3.3 - readMcpChannel(2) );

      int skalaSize = sizeof(skala) / sizeof(scale_t);

      for (i = 0 ; i < skalaSize ; i++ )
      {
	temp[0] = skala[i].res   - r;
	temp[1] = skala[i+1].res - r;
	
	if (  i + 1 == skalaSize || ((temp[0] < 0) ? (temp[0] * -1) : (temp[0])) <= ((temp[1] < 0) ? (temp[1] * -1) : (temp[1])) )
	{ 
	  temp[2] = skala[i].res - r;
	  
	  temp[3] = skala[i].res - skala[i + 1].res ;
	  
	  temp[4] = temp[2] / (temp[3] < 0 ) ? temp[3] + -1: temp[3];
	  lux = skala[i].lux + ( (skala[i + 1].lux - skala[i].lux) * temp[4]);
	
	  break;
	}
		      
      }

      system("clear");   
      
      printf("\"Licht\"  - Lux: %0.3F\n", lux);	
      printf("         - R  : %0F  \n", r);
      printf("         - V  : %0F  \n", readMcpChannel (2));
    }	
  }
}
