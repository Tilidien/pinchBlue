#include <pthread.h>
#include "pinchBlue_plist.c"


void pinchBlue_adapter_thread(int dev_id, int socket,int* keepRunning, pthread_mutex_t* mutex, plist data[3])
{
    while (pinchBlue_adapter_checkTermination(keepRunning, mutex))
    {
        if (pinchBlue_plist_count(&data[0]))
        {
            pinchBlue_adapter_imitate(dev_id, socket, data);
        }
        else 
        {
            pinchBlue_adapter_updateList(data);
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

int pinchBlue_adapter_imitate(int dev_id, int socket, plist data[3])
{

}

int pinchBlue_adapter_search(int dev_id, int socket, plist data[3])
{

}

void pinchBlue_adapter_updateList(plist data[3])
{

}