#include "bluegasm.h"

struct externalDevice
{
    char* baddr;
    char* name;
};
typedef struct externalDevice xdevice;

void printIntAsString(int in)
{
    while(in)
    {
        if(in & 1)
            printf("1");
        else   
            printf("0");
        in >>= 1;
    }
    printf("\n");
}

int getAudioDevices(xdevice** out)
{
	struct sockaddr_rc loc_addr, rem_addr;
    char buf[1024];
	int s, client, bytes_read;
	socklen_t opt = sizeof(rem_addr);

	//Allocate socket

	int ctl = socket(AF_BLUETOOTH, SOCK_RAW, BTPROTO_HCI);

	struct hci_dev_req dr;
	dr.dev_id = 0;  // hci0
	dr.dev_opt = SCAN_DISABLED;
	dr.dev_opt = SCAN_PAGE | SCAN_INQUIRY;
	ioctl(s, HCISETSCAN, (unsigned long) &dr);
	close(ctl);
	s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
	loc_addr.rc_family = AF_BLUETOOTH;
	loc_addr.rc_bdaddr = *BDADDR_ANY;
	loc_addr.rc_channel = 1;
	bind(s, (struct sockaddr*)&loc_addr, sizeof(loc_addr));
	listen(s,1);
	client = accept(s, (struct sockaddr *)&rem_addr, &opt);
	ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "accepted connection from %s\n", buf);
    memset(buf, 0, sizeof(buf));
	bytes_read = read(client, buf, sizeof(buf));
    if( bytes_read > 0 ) {
        printf("received [%s]\n", buf);
    }
	close(client);
    close(s);
    return 0;
}

int main()
{
    xdevice* x;
    getAudioDevices(&x);
    return 0;
}
