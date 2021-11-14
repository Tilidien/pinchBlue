#define PINCHBLUE_ADAPTER_C
#include "pinchBlue.h"


typedef struct{
	int					dev_id;
	int					socket;
	int*				keepRunning;
	pthread_mutex_t*	mutex;
	plist				data[3];
} pinchBlue_adapter_args;

void* pinchBlue_adapter_startThread(void* in)
{
	pinchBlue_adapter_args* args = (pinchBlue_adapter_args*)in;
	pinchBlue_adapter_thread(	args->dev_id, 
								args->socket,
								args->keepRunning, 
								args->mutex, 
								args->data);
}

void pinchBlue_adapter_thread(	int 				dev_id, 
								int					socket,
								int* 				keepRunning, 
								pthread_mutex_t* 	mutex, 
								plist 				data[3])
{
    int x = 0;
    while (pinchBlue_adapter_checkTermination(keepRunning, mutex))
    {
        pthread_mutex_lock(data[0].mutex);
        x = pinchBlue_plist_count(&data[0]);
        pthread_mutex_unlock(data[0].mutex);
        if (x)
        {
            pinchBlue_adapter_imitate(dev_id, socket, data);
        }
        else 
        {
            pinchBlue_adapter_search(dev_id, socket, data);
        }
    }
}

int pinchBlue_adapter_checkTermination(int* keepRunning, pthread_mutex_t* mutex)
{
    pthread_mutex_lock(mutex);
    int out = *keepRunning;
    pthread_mutex_unlock(mutex);
    return out;
}

void pinchBlue_adapter_imitate(int dev_id, int socket, plist data[3])
{
    xdevice* externalDevice = pinchBlue_pList_pop(&data[0]);

    pinchBlue_plist_addElem(externalDevice, &data[1]);
}

void pinchBlue_adapter_search(int dev_id, int socket, plist data[3])
{
    inquiry_info* ii = NULL;
    hci_inquiry(dev_id, 1, 255, NULL, &ii, NULL);
}
