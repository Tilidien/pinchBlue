#define PINCHBLUE_SNIFFER_C
#include "pinchBlue.h"


void pinchBlue_sniffer_thread(int* keepRunning, pthread_mutex_t* mutex, plist data[3] /*,TODO*/)
{
	int x = 1;
	while (x)
	{
		//interface with wireshark
		//read EIR
		//write unknown devices to data[0] (check for exsisting devices in whole database)
		//dont forget the mutex when reading or writing to anything in the database

		sleep(300);//wait 0.3 S //May be changed later
		pthread_mutex_lock(mutex);
		x = *keepRunning;
		pthread_mutex_unlock(mutex);
    }
}
