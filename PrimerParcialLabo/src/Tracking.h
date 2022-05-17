/*
 * 	                      BIBLIOTECA DEDICADA A ALOJAR LAS FUNCIONES DE TRACKING
 */
#ifndef TRACKING_H_
#define TRACKING_H_

#define MAX_TRACKINGS 1000
//ISEMPTY STATES
#define IN_PROGRESS 1
#define AVAILABLE 0
#define DELIVERED -1
#define CANCELLED -2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utn.h"

typedef struct{

	int trackingID;
	int productID;
	short int isEmpty;
	int FK_userID;//RELATION BUYER - PRODUCT
	int quantity;
	int distanceKM;
	long int arrivalTime;//20SEG CADA 10KM

}sTracking;


int sTracking_initTracking(sTracking trackingList[], int len);
int sTracking_findAvailableIndex(sTracking trackingList[], int len);
sTracking sTracking_getTrackingData(int idProduct, int quantity, int postalCode);
int sTracking_addTracking(sTracking trackingList[], int len, int idProduct, int quantity, int postalCode);
int sTracking_deleteTracking(sTracking trackingList[], int lenT);
int sTracking_trackingStatusUpdate(sTracking trackingList[], int len);
void sTracking_hardCodeTrackings(sTracking trackingList[]);
int sTracking_findTrackingIndexById(sTracking trackingList[], int len, int givenID);
int sTracking_findTrackingIndexByUserId(sTracking trackingList[], int len, int givenID);

#endif /* TRACKING_H_ */
