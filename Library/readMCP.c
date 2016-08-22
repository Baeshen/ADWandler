#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <errno.h>

void mcpSetup()
{
  int Fd;
  if ((Fd = wiringPiSPISetup (0, 1000000)) < 0)
  {
    fprintf (stderr, "Can't open the SPI bus: %s\n", strerror(errno));
    exit(EXIT_FAILURE) ;
  }
}


float readMcpChannel(int channel)
{
  unsigned char buffer[3] = {1};
  buffer[1] = (8 + channel) << 4; // Setz die Konfiguration, 8 setht fuer 
  wiringPiSPIDataRW(0, buffer, 3); // Liest die Daten von dem AD - Wandler
  return (((buffer[1] & 3) << 8 ) + buffer[2]) * 0.00322265625; // Gibt den gelesenen Wert als Spannung zurueck
}
