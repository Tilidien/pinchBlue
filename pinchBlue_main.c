#include "pinchBlue.h"

int main(int argc, char** argv)
{
	plist* 			database[3];
	pthread_t 		threads[7];
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	int 			keepRunning;

	memset(threads, 0, sizeof(pthread_t)*7);
	for(int i = 0;i<3;i++)
	{
		database[i] = pinchBlue_plist_createPlist();
	}
	pinchBlue_adapter_args adapterArgs;
	adapterArgs.keepRunning = &keepRunning;
	adapterArgs.mutex 		= &mutex;
	adapterArgs.dev_id		= hci_get_route( NULL );
	adapterArgs.socket		= hci_open_dev(adapterArgs.dev_id);
	adapterArgs.data		= database;
	close(adapterArgs.socket);
	pthread_create( &threads[0], NULL, pinchBlue_adapter_startThread, (void*) &adapterArgs);

	sleep(100000);
	pthread_mutex_lock(&mutex);
	keepRunning = 0;
	pthread_mutex_unlock(&mutex);
	pthread_join(threads[0], NULL);
}
