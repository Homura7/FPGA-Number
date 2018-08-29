/*
        demo-udp-03: udp-recv: a simple udp server
	receive udp messages

        usage:  udp-recv

        Paul Krzyzanowski
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/mman.h>
#include "hwlib.h"
#include "soc_cv_av/socal/socal.h"
#include "soc_cv_av/socal/hps.h"
#include "soc_cv_av/socal/alt_gpio.h"
#include "hps_0.h"
#include <stdbool.h>
#include <pthread.h>
#include "hps.h"
#include "ADLX345.h"
#include "fpga.h"

#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

#define SERVICE_PORT 3009
#define BUFSIZE 2048

int main(int argc, char *argv[])
{
	if(!FPGAInit()){
		printf("can't initialize fpga");
		return 0;
	}
	//int16_t X,Y,Z;
	//m_file_gsensor = GsensorInit();
	//bool m_bGSensorDataValid = false;
	//uint32_t switchMask;
	//int valueToPrint = 0;
	

//////////////////////////////////////////////////////////////////////////////////////////
	struct sockaddr_in myaddr;	/* our address */
	struct sockaddr_in remaddr;	/* remote address */
	socklen_t addrlen = sizeof(remaddr);		/* length of addresses */
	int recvlen;			/* # bytes received */
	int fd;				/* our socket */
	unsigned char buf[BUFSIZE];	/* receive buffer */
	int result = 0;

	/* create a UDP socket */

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("cannot create socket\n");
		return 0;
	}

	/* bind the socket to any valid IP address and a specific port */

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(SERVICE_PORT);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
		return 0;
	}

	/* now loop, receiving data and printing what we received */
	for (;;) {
		printf("waiting on port %d\n", SERVICE_PORT);
		recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		printf("received %d bytes\n", recvlen);
		if (recvlen > 0) {
			buf[recvlen] = 0;
			result = atoi(buf);
			printf("received message: \"%d\"\n", result);
			setDisplay(result);
		}
	}
	/* never exits */

////////////////////////////////////////////////////////////////////////////////////////

	/*while(1){
		m_bGSensorDataValid = GsensorQuery(&X,&Y,&Z);
		if(m_bGSensorDataValid){
			printf("X = %d    Y = %d    Z = %d\r\n", X, Y, Z);
		}
		SwitchRead(&switchMask);
		// add your code here
		
		if(switchMask==0)
		{
			setDisplay(X);
		}
		else if(switchMask==1)
		{
			setDisplay(Y);
		}
		else if(switchMask==2)
		{
			setDisplay(Z);
		}
		
		usleep(500*1000);
	}
	return 1;*/
}

void setDisplay(int value){
	if(value > 999999){value = 99999;}
	else if(value < -9999){ value = -9999;}
	int temp;
	if(value<0){temp = -value;}
	else{temp = value;}
	int i = 0;
	while(temp!=0){
		HexSet(i++,temp%10);
		temp/=10;
	}
	if(value<0){HexSet(i++,16);} // add negative sign if necessary
	if(value==0){HexSet(i++,0);}
	for(i;i<6;i++){
		HexSet(i,17);	//clear out the leading spaces
	}
}
