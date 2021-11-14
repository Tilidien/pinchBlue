
#ifndef PINCHBLUE_H
#   define PINCHBLUE_H
#   include <stdio.h>
#   include <stdlib.h>
#   include <unistd.h>
#   include <sys/socket.h>
#   include <bluetooth/bluetooth.h>
#   include <bluetooth/hci.h>
#   include <bluetooth/hci_lib.h>
#   include <pthread.h>

typedef struct	s_elem
{
	void*	data;
	elem*	next;

}				elem;

typedef struct	s_protecter_list
{
	pthread_mutex_t*	mutex;
	elem*				start;
}				plist;

typedef struct	bluetoothdevice
{
	char*	addr;
	char*	name;
}				xdevice;

#   ifndef PINCHBLUE_SNIFFER_C
#       include "pinchBlue_sniffer.c"
#   endif

#   ifndef PINCHBLUE_PLIST_C
#       include "pinchBlue_plist.c"
#   endif

#   ifndef PINCHBLUE_ADAPTER_C
#       include "pinchBlue_adapter.c"
#   endif
#endif
