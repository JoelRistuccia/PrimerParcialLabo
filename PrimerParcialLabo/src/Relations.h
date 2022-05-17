/*
 *  BIBLIOTECA DEDICADA A ALOJAR LAS FUNCIONES DE RELACION ENTRE LAS 3 ENTIDADES
 */

#ifndef RELATIONS_H_
#define RELATIONS_H_

#include <ctype.h>
#include "Users.h"
#include "Products.h"
#include "Tracking.h"


int Relations_userLogin(sUser userList[], int lenU, sProduct productList[], int lenP,
		sTracking trackingList[], int lenT);
int Relations_loginUserType(sUser userList[], int lenU, sProduct productList[], int lenP,
		sTracking trackingList[], int lenT, int userIndex);
int Relations_loginAdminType(sUser userList[], int lenU, sProduct productList[], int lenP,
		sTracking trackingList[], int lenT);
int Relations_confirmPurchase (sUser userList[], int lenU, sProduct productList[], int lenP,
		sTracking trackingList[], int lenT, int userIndex);
int Relations_confirmSell(sProduct productList[], sUser userList[], int *index);
void Relations_printPurchase(sTracking tracking, sProduct product);
int Relations_listPurchases(sTracking trackingList[], int lenT, sProduct productList[],
		int lenP, int userID);
int Relations_checkPurchasesStatus(sTracking trackingList[], int lenT, sProduct productList[],
		int lenP, int userID);
int Relations_checkFinishedSellings(sTracking trackingList[], int lenT, sProduct productList[],
		int lenP, int userID);
int Relations_checkProductsStock(sProduct productList[], int len, int userID);
int Relations_checkSellingsStatus(sTracking trackingList[], int lenT, sProduct productList[],
		int lenP, int userID);
int Relations_verifyFinishedSellings(sTracking trackingList[], int lenT, sProduct productList[],
		int lenP, int userID);
int Relations_verifyProductsStock(sProduct productList[], int len, int userID);
void Relations_printTracking(sTracking tracking, sProduct product);
int Relations_listGlobalTrackings(sTracking trackingList[], int lenT, sProduct productList[],
		int lenP, int status);





#endif /* RELATIONS_H_ */
