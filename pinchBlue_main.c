#include "pinchBlue.h"

int main()
{
	plist* database[3];
	for(int i = 0;i<3;i++)
	{
		database[i] = pinchBlue_plist_createPlist();
	}
	int currentSocket 	= -1;
	int currentDevice	= -1;
	for(int i = 0;i<10;i++)
	{
		currentDevice = hci_get_route( NULL );
		currentSocket = hci_open_dev( currentDevice );

	}
}