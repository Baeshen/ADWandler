#ifndef _READMCP_H_
#define	_READMCP_H_
/* 
 * Die Libary benutzt die WiringPi libary um das SPI interface auszulesen, so muss man
 * die Libary beim Compilieren mit einbinden.
 * 
 * 
 * 
 * Compiler Tags: -lwiringPi -lreadMCP
 * 
*/




void mcpSetup();

float readMcpChannel(int);

	

#endif
