
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

    typedef struct {
        char* addr;
        char* name;
    } xdevice;

#endif