#include "Tracking.h"

static int sTracking_getTrackingID(void);
static int sTracking_getTrackingID(void) {
	static int tracking_id = 10005;
	return tracking_id++;
}

int sTracking_initTracking(sTracking trackingList[], int len) {
	int rtn;
	int i;

	if (trackingList != NULL)//VERIFY IF THE ARRAY EXISTS
	{
		if(len > 0)//VERIFY IF THE ARRAY LENGHT IS CORRECT
		{
			for (i = 0; i < len; i++)//LOOP OVER THE ARRAY
			{
				trackingList[i].isEmpty = AVAILABLE;//SET STATUS 'AVAILABLE'
			}
		}
		else
		{
			rtn = -1;//ERROR - ARRAY LENGHT
		}
	}
	else
	{
		rtn = -2;//ERROR - NULL POINTER
	}

	return rtn;
}


int sTracking_findAvailableIndex(sTracking trackingList[], int len) {

	int rtn = -1;
	int i;

	if (trackingList != NULL)//VERIFY IF THE ARRAY EXISTS
	{
		if(len > 0)//VERIFY ARRAY LENGHT
		{
			for (i = 0; i < len; i++)//LOOP OVER THE ARRAY
			{
				if (trackingList[i].isEmpty == AVAILABLE)//ASK FOR STATUS "AVAILABLE"
				{
					rtn = i;//SAVE THE FIRST INDEX 'AVAILABLE'
					break;
				}
			}
		}
	}
	else
	{
		rtn = -2;//ERROR - NULL POINTER
	}

	return rtn;
}

int sTracking_addTracking(sTracking trackingList[], int len, int idProduct, int quantity, int postalCode){
	int rtn = 0;
	int trackingIndex;
	sTracking auxiliary;

	if(trackingList != NULL)
	{
		if(len > 0)
		{
			trackingIndex = sTracking_findAvailableIndex(trackingList, len);
			auxiliary = sTracking_getTrackingData(idProduct, quantity, postalCode);
			auxiliary.trackingID = sTracking_getTrackingID();
			auxiliary.isEmpty = IN_PROGRESS;
			trackingList[trackingIndex] = auxiliary;
			rtn = trackingIndex;//RETURNS INDEX OF TRACKING
		}
		else
		{
			rtn = -1;
		}
	}
	else
	{
		rtn = -2;
	}


	return rtn;
}



sTracking sTracking_getTrackingData(int idProduct, int quantity, int postalCode) {
	sTracking auxiliary;

	int timeToAdd;

	if(idProduct > 0 && quantity > 0 && postalCode > 0)
	{
		auxiliary.productID = idProduct;
		auxiliary.quantity = quantity;
		if(postalCode < 9999 && postalCode > 8001)
		{
			auxiliary.distanceKM = 150;
		}
		else
		{
			if(postalCode < 8000 && postalCode > 5001)
			{
				auxiliary.distanceKM = 80;
			}
			else
			{
				if(postalCode < 5000 && postalCode > 3001)
				{
					auxiliary.distanceKM = 50;
				}
				else
				{
					if(postalCode < 3000 && postalCode > 1001)
					{
						auxiliary.distanceKM = 30;
					}
					else
					{
						auxiliary.distanceKM = 20;
					}

					timeToAdd = auxiliary.distanceKM / 10 * 20;
					auxiliary.arrivalTime = time_Add(timeToAdd);
				}
			}
		}
	}
	else
	{
		printf("Error de parametros\n");
	}



	return auxiliary;
}


int sTracking_trackingStatusUpdate(sTracking trackingList[], int len) {
	int rtn = 0;
	int i;
	long int actualTime;

	if(trackingList != NULL)
	{
		if(len > 0)
		{
			actualTime = time_Current();

			for(i = 0; i < len; i++)
			{
				if(trackingList[i].isEmpty == 1)
				{
					if(actualTime > trackingList[i].arrivalTime)
					{
						trackingList[i].isEmpty = -1;
					}
				}
			}
		}
		else
		{
			rtn = -1;//ERROR - ARRAY LENGHT
		}
	}
	else
	{
		rtn = -2;//ERROR - NULL POINTER
	}


	return rtn;
}

int sTracking_deleteTracking(sTracking trackingList[], int lenT) {
	int rtn = 0;
	int idToCancel;
	int indexToCancel;

	if(trackingList != NULL)
	{
		if(lenT > 0)
		{
			getInt("Ingrese el ID de la compra que desea cancelar: ", 10, 10000, 12000,
					"\nError, ingrese un ID de la lista: ", &idToCancel);
			indexToCancel = sTracking_findTrackingIndexById(trackingList, lenT, idToCancel);

			while(trackingList[indexToCancel].isEmpty != 1)
			{
				getInt("\nSolo puede cancelar compras cuyo estado sea \"EN VIAJE\", ingrese otro ID: " ,
						10, 10000, 12000, "\nError, ingrese un ID de la lista: ", &idToCancel);
				indexToCancel = sTracking_findTrackingIndexById(trackingList, lenT, idToCancel);
			}

			if(continueOrNot("\nDesea confirmar la cancelacion? (S/N): ",
					"\nError, ingrese una opcion valida (S/N): "))
			{
				trackingList[indexToCancel].isEmpty = -2;
				puts("Su compra ha sido cancelada.");
				system("pause");
				system("cls");
			}
		}
		else
		{
			rtn = -1;//ERROR - ARRAY LENGHT
		}
	}
	else
	{
		rtn = -2;//ERROR - ARRAY LENGHT
	}

	return rtn;
}

int sTracking_findTrackingIndexById(sTracking trackingList[], int len, int givenID) {

	int rtn;
	int i;

	if(trackingList != NULL)//VERIFIES IF THE ARRAY EXISTS
	{
		if(len > 0)//VERIFIES IF ARRAY LENGHT IS LARGER THAN 0
		{
			for (i = 0; i < len; i++)//LOOP OVER THE ARRAY
			{
				//VERIFY IF ID EXISTS AND IF ITS STATE IS NOT "EMPTY "
				if(trackingList[i].trackingID == givenID && trackingList[i].isEmpty != AVAILABLE)
				{
					rtn = i;//RETURNS INDEX OF ID GIVEN
					break;
				}
				else
				{
					rtn = -1;//ERROR - ID DOESN'T EXISTS
				}
			}
		}
		else
		{
			rtn = -2;//ERROR - ARRAY LENGHT
		}
	}
	else
	{
		rtn = -3;//ERROR - ARRAY DOESN'T EXIST
	}
	return rtn;
}

int sTracking_findTrackingIndexByUserId(sTracking trackingList[], int len, int givenID) {

	int rtn;
	int i;

	if(trackingList != NULL)//VERIFIES IF THE ARRAY EXISTS
	{
		if(len > 0)//VERIFIES IF ARRAY LENGHT IS LARGER THAN 0
		{
			for (i = 0; i < len; i++)//LOOP OVER THE ARRAY
			{
				//VERIFY IF ID EXISTS AND IF ITS STATE IS NOT "EMPTY "
				if(trackingList[i].FK_userID == givenID && trackingList[i].isEmpty != AVAILABLE)
				{
					rtn = i;//RETURNS INDEX OF ID GIVEN
					break;
				}
				else
				{
					rtn = -1;//ERROR - ID DOESN'T EXISTS
				}
			}
		}
		else
		{
			rtn = -2;//ERROR - ARRAY LENGHT
		}
	}
	else
	{
		rtn = -3;//ERROR - ARRAY DOESN'T EXIST
	}
	return rtn;
}

void sTracking_hardCodeTrackings(sTracking trackingList[]) {

	trackingList[0].FK_userID = 1001;
	trackingList[0].arrivalTime = time_Current();
	trackingList[0].distanceKM = 30;
	trackingList[0].isEmpty = -1;
	trackingList[0].productID = 4004;
	trackingList[0].quantity = 1;
	trackingList[0].trackingID = 10000;

	trackingList[1].FK_userID = 1001;
	trackingList[1].arrivalTime = time_Current();
	trackingList[1].distanceKM = 30;
	trackingList[1].isEmpty = -2;
	trackingList[1].productID = 4005;
	trackingList[1].quantity = 6;
	trackingList[1].trackingID = 10001;

	trackingList[2].FK_userID = 1001;
	trackingList[2].arrivalTime = time_Current();
	trackingList[2].distanceKM = 30;
	trackingList[2].isEmpty = -1;
	trackingList[2].productID = 4007;
	trackingList[2].quantity = 2;
	trackingList[2].trackingID = 10002;

	trackingList[3].FK_userID = 1001;
	trackingList[3].arrivalTime = time_Current();
	trackingList[3].distanceKM = 30;
	trackingList[3].isEmpty = -2;
	trackingList[3].productID = 4001;
	trackingList[3].quantity = 3;
	trackingList[3].trackingID = 10003;

	trackingList[4].FK_userID = 1001;
	trackingList[4].arrivalTime = time_Current();
	trackingList[4].distanceKM = 30;
	trackingList[4].isEmpty = -1;
	trackingList[4].productID = 4002;
	trackingList[4].quantity = 3;
	trackingList[4].trackingID = 10004;

}
