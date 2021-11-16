#   include <stdio.h>
#   include <stdlib.h>
#   include <unistd.h>
#   include <sys/socket.h>
#   include <bluetooth/bluetooth.h>
#   include <bluetooth/hci.h>
#   include <bluetooth/hci_lib.h>
#	include <bluetooth/rfcomm.h>
#   include <pthread.h>
#	include <sys/ioctl.h>

typedef struct{
	int* 				client;
	int*				keepRunning;
	pthread_mutex_t*	keepRunning_mutex;
} arg;

void* pinchBlue_printData_listen(void* args)
{
	arg*	input 		= (arg*)args;
	int 	nobrk 		= 1;
	int		bytecount 	= 0;
	char	buf[1024];

	while (nobrk)
	{
		memset(buf, 0, sizeof(buf));
		bytecount = read(*(input->client), buf, 1024);
		if(bytecount>0)
		{
			printf("Recieved Package:\n");
			write(1, buf, bytecount);
			write(1,"\n\n", 1);
		}
		pthread_mutex_lock(input->keepRunning_mutex);
		nobrk = *(input->keepRunning);
		pthread_mutex_unlock(input->keepRunning_mutex);
	}
	return 0;
}

int main()
{
	int					s;
	int					client;
	char				buf[1024];
	struct sockaddr_rc 	loc_addr, rem_addr;
	int 				listener_keepRunning 		= 1;
	pthread_mutex_t 	listener_keepRunning_mutex 	= PTHREAD_MUTEX_INITIALIZER;
	pthread_t 			listener 					= 0;
	socklen_t 			opt 						= sizeof(rem_addr);
	arg					arguments;

	s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
	loc_addr.rc_family = AF_BLUETOOTH;
	loc_addr.rc_bdaddr = *BDADDR_ANY;
	loc_addr.rc_channel = 1;
	bind(s, (struct sockaddr*)&loc_addr, sizeof(loc_addr));
	listen(s, 1);
	client = accept(s, (struct sockaddr *)&rem_addr, &opt);
	ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "accepted connection from %s\n", buf);

	arguments.keepRunning = &listener_keepRunning;
	arguments.keepRunning_mutex = &listener_keepRunning_mutex;
	arguments.client = &client;
	pthread_create(&listener, NULL, pinchBlue_printData_listen, &arguments);
	memset(buf, 0, 1024);
	while(strncmp(buf, "Exit", 4))
	{
		fgets(buf,1024,stdin);
	}
	close(s);
	close(client);
	return 0;
}