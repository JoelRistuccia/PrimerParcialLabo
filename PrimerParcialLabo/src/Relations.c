#include "Relations.h"


int Relations_userLogin(sUser userList[], int lenU, sProduct productList[], int lenP,
		sTracking trackingList[], int lenT) {

	int rtn = 0;
	int userIndex;

	if(userList != NULL && productList != NULL)
	{
		if(lenP > 0 && lenU > 0)
		{
			fflush(stdin);//ASK AND VALIDATE USER DATA AND RETURNS INDEX OF THE USER LOGGED
			userIndex = sUser_getLoginData(userList, lenU);

			switch(userList[userIndex].type)
			{
			case USER://IF USERTYPE IS USER
				fflush(stdin);
				Relations_loginUserType(userList, lenU, productList, lenP, trackingList, lenT, userIndex);
				break;
			case ADMIN://IF USERTYPE IS ADMIN
				fflush(stdin);
				Relations_loginAdminType(userList, lenU, productList, lenP, trackingList, lenT);
				break;
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

	return rtn;//RETURN 0 IF OK
}


int Relations_confirmPurchase (sUser userList[], int lenU, sProduct productList[], int lenP,
		sTracking trackingList[], int lenT, int userIndex) {

	int rtn = 0;
	int purchaseIndex;
	int priceToPay;
	int quantityToBuy;
	int trackingIndex;

	if(userList != NULL && productList != NULL && trackingList != NULL)//VERIFIES IF THE ARRAYS EXISTS
	{
		if(lenU > 0 && lenP > 0 && lenT > 0)//VERIFIES ARRAY LENGHTS
		{	//VERIFY IF THERES PRODUCTS AVAILABLE TO BUY
			purchaseIndex = sProduct_verifyProductsGlobalStatus(productList, lenP, FULL, OUT_OF_STOCK);
			if(purchaseIndex == 1)//RETURNS 1 IF FIND AT LEAST AN AVAILABLE PRODUCT
			{					//ASKS WHAT PRODUCT WANTS TO BUY
				purchaseIndex = sProduct_buyProducts(productList, lenP);//RETURNS PRODUCT INDEX
				if(purchaseIndex >= 0)
				{	//ASKS QUANTITY TO BUY AND CALCULATE THE TOTAL PRICE
					getInt("Ingrese la cantidad que desea comprar: ", 10, 1, productList[purchaseIndex].stock,
							"Error, ingrese una cantidad valida: ", &quantityToBuy);
					priceToPay = productList[purchaseIndex].price * quantityToBuy;
					printf("\nEl total de su compra es: $%d\n\n", priceToPay);
						//ASKS FOR CONFIRMATION
					if(continueOrNot("Desea confirmar la compra? (S/N): ", "Error, ingrese una opcion valida (S/N): "))
					{	//IF USER CONFIRMS SUBSTRACT THE QUANTITY FROM STOCK AND CREATES THE TRACKING
						productList[purchaseIndex].stock -= quantityToBuy;
						trackingIndex = sTracking_addTracking(trackingList, lenT, productList[purchaseIndex].productID, quantityToBuy,
								userList[userIndex].postalCode);
						trackingList[trackingIndex].FK_userID = userList[userIndex].userID;
						printf("\nSu compra ha sido efectuada.\nFecha y hora estimadas para su envio: %s\n",
								ctime(&trackingList[trackingIndex].arrivalTime));
						puts("Gracias por su compra!");
						system("pause");
						system("cls");
					}
				}
				else
				{
					system("cls");
				}
			}
			else
			{	//IF THERES NO PRODUCTS AVAILABLE TO BUY
				system("cls");
				printf("No hay productos disponibles a la venta.\n\n");
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
		rtn = -2;//ERROR - NULL POINTER
	}

	return rtn;//RETURN 0 IF OK
}


int Relations_confirmSell(sProduct productList[], sUser userList[], int *index) {
	int rtn = 0;
	int productIndex;
	int chosenOption;

	if(productList != NULL && userList != NULL)
	{
		if(index > 0)
		{	//ASKS FOR AN OPTION
			getInt("Que accion desea realizar?\n\n"
					"\t1) Publicar un producto\n"
					"\t2) Reponer stock\n\n"
					"\t0) Volver al menu anterior\n\n"
					"Ingrese la opcion deseada: ", 10, 0, 2,
					"Error, ingrese una opcion valida: ", &chosenOption);
			switch(chosenOption)
			{
			case 1:
				system("cls");//ASKS FOR NEW PRODUCT DATA
				productIndex = sProduct_addProduct(productList, MAX_PRODUCTS);
				if(productIndex > -1)
				{	//IF PRODUCT ADD ITS OK ASSING THE FOREING KEY OF THE SELLER
					productList[productIndex].FK_userID = userList[*index].userID;
				}
				else
				{	//GO BACK
					system("cls");
				}
				break;
			case 2:
				system("cls");//ASKS FOR PRODUCT STOCK RENEWAL
				sProduct_addProductStock(productList, MAX_PRODUCTS, userList[*index].userID);
				break;
			case 0://GO BACK
				system("cls");
				break;
			}
		}
		else
		{
			rtn = -1;//ERROR - INVALID INDEX
		}
	}
	else
	{
		rtn = -2;//ERROR - NULL POINTER
	}

	return rtn;//RETURN 0 IF OK
}

void Relations_printPurchase(sTracking tracking, sProduct product) {

	float totalPrice;
	//CALCULATES THE TOTAL PRICE
	totalPrice = tracking.quantity * product.price;
	//PRINTS ALL THE PURCHASE INFO
	printf("|%d", tracking.trackingID);
	printf("%-2s", "|");
	printf("%-23s", product.productName);
	printf("%-2s", "|");
	printf("%-9d", tracking.quantity);
	printf("%-2s", "|");
	printf("%-9.2f", totalPrice);
	printf("%-2s", "|");

	switch(tracking.isEmpty)
	{
	case 1:
		printf("%-14s", "EN VIAJE");
		break;
	case -1:
		printf("%-14s", "ENTREGADO");
		break;
	case -2:
		printf("%-14s", "CANCELADO");
		break;
	}
	printf("%-2s", "|\n");
}


int Relations_listPurchases(sTracking trackingList[], int lenT, sProduct productList[],
		int lenP, int userID) {
	int rtn = 0;
	int i;
	int index;
	int productID;

	puts("\n\t> LISTADO DE COMPRAS");//HEADER
	puts("+-----+------------------------+----------+----------+---------------+");
	printf("| %1s%3s%14s%11s%8s%3s%6s%5s%10s%6s\n", "ID", "|", "PRODUCTO", "|", "CANTIDAD", "|",
			"TOTAL", "|", "ESTADO", "|");
	puts("+-----+------------------------+----------+----------+---------------+");

	if (productList != NULL && trackingList != NULL)
	{
		if (lenT > 0 && lenP > 0)
		{
			for (i = 0; i < lenT; i++)
			{	//ASKS FOR TRACKINGS WITH FOREIGN KEY OF BUYER
				if (trackingList[i].FK_userID == userID)
				{	//IF FINDS A TRACKING SAVES THE PRODUCT ID
					productID = trackingList[i].productID;//FIND THE PRODUCT INDEX OF THE ID
					index = sProduct_findProductIndexById(productList, lenP, productID);
					Relations_printPurchase(trackingList[i], productList[index]);
					//PRINTS THE PURCHASE INFO (PRODUCT/TRACKING)
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
	puts("+-----+------------------------+----------+----------+---------------+");

	return rtn;
}


int Relations_checkPurchasesStatus(sTracking trackingList[], int lenT, sProduct productList[],
		int lenP, int userID) {
	int rtn = 0;
	int userIndex;
	int chosenOption;

	if(trackingList != NULL && productList != NULL)
	{
		if(lenT > 0 && lenP > 0)
		{	//CHECK IF USER HAS ANY TRACKING / RETURN INDEX IF FIND AT LEAST 1 TRACKING
			userIndex = sTracking_findTrackingIndexByUserId(trackingList, lenT, userID);
			if(userIndex >= 0)//IF FIND AT LEAST 1 TRACKING
			{
				sTracking_trackingStatusUpdate(trackingList, lenT);//UPDATE THE TRACKINGS STATUS
				Relations_listPurchases(trackingList, lenT, productList, lenP, userID);
				getInt("\nQue accion desea realizar?\n\n"//LISTS ALL THE TRACKINGS OF THE USER
						"\t1) Cancelar una compra\n "//ASKS FOR AN OPTION
						"\t0) Volver al menu anterior\n\n"
						"Ingrese la opcion deseada: ",
						10, 0, 1, "Error, ingrese una opcion valida: ", &chosenOption);
				if(chosenOption == 1)
				{	//ASKS FOR ID TO CANCEL
					sTracking_deleteTracking(trackingList, lenT);
				}
				else
				{	//GO BACK
					system("cls");
				}
			}
			else
			{	//IF DOESN'T FIND ANY TRACKINGS FOR THE USER
				system("cls");
				printf("Usted no tiene compras disponibles para mostrar.\n\n");
				system("pause");
				system("cls");
			}
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


int Relations_checkFinishedSellings(sTracking trackingList[], int lenT, sProduct productList[],
		int lenP, int userID) {

	int rtn = 0;
	int i;
	int j;

	puts("\n\t> LISTADO DE VENTAS FINALIZADAS");//HEADER
	puts("+-----+------------------------+----------+----------+---------------+");
	printf("| %1s%3s%14s%11s%8s%3s%6s%5s%10s%6s\n", "ID", "|", "PRODUCTO", "|", "CANTIDAD", "|",
			"TOTAL", "|", "ESTADO", "|");
	puts("+-----+------------------------+----------+----------+---------------+");

	if (productList != NULL && trackingList != NULL)
	{
		if (lenT > 0 && lenP > 0)
		{
			for (i = 0; i < lenP; i++)//LOOP OVER THE PRODUCTS ARRAY
			{	//CHECK FOR PRODUCTS WITH THE FOREIGN KEY OF THE SELLER
				if(productList[i].FK_userID == userID)
				{
					for(j = 0; j < lenT; j++)//LOOP OVER THE TRACKINGS ARRAY
					{	//CHECK FOR TRACKINGS WITH THE SAME ID OF THE PRODUCT
						if(trackingList[j].productID == productList[i].productID)
						{	//CHECK TRACKING STATUS
							if(trackingList[j].isEmpty == DELIVERED || trackingList[j].isEmpty == CANCELLED)
							{	//IF ALL CONDITIONS MATCHES PRINTS THE TRACKING/PRODUCT INFO
								Relations_printPurchase(trackingList[j], productList[i]);
							}
						}
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
	puts("+-----+------------------------+----------+----------+---------------+\n\n");

	return rtn;//RETURN 0 IF OK
}

int Relations_checkProductsStock(sProduct productList[], int len, int userID) {
	int rtn = 0;
	int i;

	puts("\n\t> LISTADO DE PRODUCTOS CON STOCK DISPONIBLE");//HEADER
	puts("+----+------------------------+----------+----------+---------------+");
	printf("| %1s%2s%15s%10s%8s%3s%6s%5s%10s%6s\n", "ID", "|", "NOMBRE", "|", "PRECIO", "|",
			"STOCK", "|", "CATEGORIA", "|");
	puts("+----+------------------------+----------+----------+---------------+");

	if(productList != NULL)
	{
		if(len > 0 && userID > 0)
		{
			for(i = 0; i < len; i++)//LOOP OVER THE ARRAY
			{	//CHECK IF FOREIG KEY OF THE PRODUCT MATCHES WITH USER ID
				if(productList[i].FK_userID == userID)
				{	//CHECK IF PRODUCT THERES STOCK AVAILABLE
					if(productList[i].stock > 0)
					{	//IF ALL CONDITIONS MATCHES PRINTS THE PRODUCT
						sProduct_printProduct(productList[i]);
					}
				}
			}
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
	puts("+----+------------------------+----------+----------+---------------+\n\n");

	return rtn;
}


int Relations_checkSellingsStatus(sTracking trackingList[], int lenT, sProduct productList[],
		int lenP, int userID) {
	int rtn = 0;
	int chosenOption;

	if(trackingList != NULL && productList != NULL)
	{
		if(lenT > 0 && lenP > 0)
		{	//ASKS FOR AN OPTION
			getInt("Que accion desea realizar?\n\n"
					"\t1) Listado de ventas finalizadas\n"
					"\t2) Ver productos con stock disponible\n\n"
					"0) Volver al menu anterior\n\n"
					"Ingrese la opcion deseada: ", 10, 0, 2,
					"\nError, ingrese una opcion valida: ", &chosenOption);

			if(chosenOption == 1)
			{	//SORT PRODUCTS BY CATEGORY
				sProduct_sortProductsByCategory(productList, lenP);
				sTracking_trackingStatusUpdate(trackingList, lenT);//UPDATE TRACKINGS STATUS
				if(Relations_verifyFinishedSellings(trackingList, lenT, productList, lenP, userID))
				{//VERIFIES IF THERES ANY FINISHED SELLING
					system("cls");//IF FIND ANY FINISHED SELLING PRINTS THE LIST
					Relations_checkFinishedSellings(trackingList, lenT, productList, lenP, userID);
					system("pause");
					system("cls");
				}
				else
				{
					system("cls");//IF THERES NO FINISHED SELLINGS
					printf("Usted no tiene ventas finalizadas para mostrar.\n\n");
					system("pause");
					system("cls");
				}
			}
			else
			{
				if(chosenOption == 2)
				{	//VERIFIES IF THERES ANY PRODUCT WITH STOCK AVAILABLE
					if(Relations_verifyProductsStock(productList, lenP, userID))
					{
						system("cls");//IF FIND ANY PRODUCT WITH STOCK PRINTS THE LIST
						Relations_checkProductsStock(productList, lenP, userID);
						system("pause");
						system("cls");
					}
					else
					{
						system("cls");
						printf("Usted no tiene productos con stock disponible para mostrar.\n\n");
						system("pause");
						system("cls");
					}
				}
				else
				{
					system("cls");
				}
			}
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


int Relations_verifyFinishedSellings(sTracking trackingList[], int lenT, sProduct productList[],
		int lenP, int userID) {

	int rtn = 0;
	int i;
	int j;
	int index;

	if (productList != NULL && trackingList != NULL)
	{
		if (lenT > 0 && lenP > 0)
		{
			for (i = 0; i < lenP; i++)
			{
				if(productList[i].FK_userID == userID)
				{
					index = sProduct_findProductIndexById(productList, lenP, productList[i].productID);
					for(j = 0; j < lenT; j++)
					{
						if(trackingList[j].productID == productList[index].productID )
						{
							if(trackingList[j].isEmpty == DELIVERED || trackingList[j].isEmpty == CANCELLED)
							{
								rtn = 1;
							}
						}
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


int Relations_verifyProductsStock(sProduct productList[], int len, int userID) {
	int rtn = 0;
	int i;

	if(productList != NULL)
	{
		if(len > 0 && userID > 0)
		{
			for(i = 0; i < len; i++)
			{
				if(productList[i].FK_userID == userID)
				{
					if(productList[i].stock > 0)
					{
						rtn = 1;
					}
				}
			}
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

int Relations_loginUserType(sUser userList[], int lenU, sProduct productList[], int lenP,
		sTracking trackingList[], int lenT, int userIndex) {

	int rtn = 0;
	int chosenOption;

	if(userList != NULL && productList != NULL && trackingList != NULL)
	{
		if(lenU > 0 && lenP > 0 && lenT > 0)
		{
			do{
				puts("\t\t\t\t\t*********************************");
				puts("\t\t\t\t\t****** 1er EXAM LAB I - 1H ******");
				puts("\t\t\t\t\t*********** USUARIO *************");
				puts("\t\t\t\t\t*********************************\n\n");
				puts("1) COMPRAR");
				puts("2) VENDER");
				puts("3) ESTADO DE COMPRAS");
				puts("4) ESTADO DE VENTAS\n");

				puts("0) SALIR\n");

				fflush(stdin);
				getInt("Ingrese la opcion deseada: ", 10, 0, 4, "Error, ingrese una opcion valida\n",
						&chosenOption);


				switch(chosenOption)
				{
				case 1://COMPRAR
					system("cls");
					Relations_confirmPurchase(userList, lenU, productList, lenP, trackingList,
							lenT, userIndex);
					break;
				case 2://VENDER
					system("cls");
					Relations_confirmSell(productList, userList, &userIndex);
					break;
				case 3://ESTADO DE COMPRAS
					system("cls");
					Relations_checkPurchasesStatus(trackingList, lenT, productList, lenP,
							userList[userIndex].userID);
					break;
				case 4://ESTADO DE VENTAS
					system("cls");
					Relations_checkSellingsStatus(trackingList, lenT, productList, lenP,
							userList[userIndex].userID);
					break;
				case 0://SALIR
					break;
				}
			}while(chosenOption != 0);
		}
		else
		{
			rtn = -1;//ERROR - ARRAY LENGHTS
		}
	}
	else
	{
		rtn = -2;//ERROR - NULL POINTER
	}

	return rtn;
}

int Relations_listGlobalTrackings(sTracking trackingList[], int lenT, sProduct productList[],
		int lenP, int status) {
	int rtn = 0;
	int i;
	int productIndex;

	puts("\n\t -> TRACKING GLOBAL <-");
	puts("+-----+-------------+----------+------------+");
	printf("| %2s%3s%12s%2s%8s%3s%9s%2s\n", "ID", "|", "ID COMPRADOR", "|", "ESTADO", "|",
			"ID VENDEDOR", "|");
	puts("+-----+-------------+----------+------------+");

	if (productList != NULL && trackingList != NULL)
	{
		if (lenT > 0 && lenP > 0)
		{
			for (i = 0; i < lenT; i++)
			{
				if (trackingList[i].isEmpty != status)
				{
					productIndex = sProduct_findProductIndexById(productList, lenP, trackingList[i].productID);
					Relations_printTracking(trackingList[i], productList[productIndex]);
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
	puts("+-----+-------------+----------+------------+\n");

	return rtn;
}

void Relations_printTracking(sTracking tracking, sProduct product) {
	printf("|%d", tracking.trackingID);
	printf("%-5s", "|");
	printf("%-9d", tracking.FK_userID);
	printf("%-1s", "|");
	switch(tracking.isEmpty)
	{
	case 1:
		printf("%-10s", "EN VIAJE");
		break;
	case -1:
		printf("%-10s", "ENTREGADO");
		break;
	case -2:
		printf("%-10s", "CANCELADO");
		break;
	}
	printf("%-4s", "|");
	printf("%-9d", product.FK_userID);
	printf("%s", "|\n");

}

int Relations_loginAdminType(sUser userList[], int lenU, sProduct productList[], int lenP,
		sTracking trackingList[], int lenT) {
	int rtn = 0;
	char chosenOption;

	if(userList != NULL && productList != NULL && trackingList != NULL)
	{
		if(lenU > 0 && lenP > 0 && lenT > 0)
		{
			do{
				puts("\t\t\t\t\t*********************************");
				puts("\t\t\t\t\t****** 1er EXAM LAB I - 1H ******");
				puts("\t\t\t\t\t************* ADMIN *************");
				puts("\t\t\t\t\t*********************************\n");
				puts("\tGESTION E INFORMES\n");
				puts("A) LISTAR ESTADO DE TODOS LOS USUARIOS");
				puts("B) LISTAR TODOS LOS PRODUCTOS POR CATEGORIA");
				puts("C) BAJA DE UN PRODUCTO");
				puts("D) BAJA DE UN USUARIO");
				puts("E) VER TRACKING GLOBAL");
				puts("F) FILTRAR POR NOMBRE DE PRODUCTO\n");

				puts("0) SALIR\n");

				printf("Ingrese la opcion deseada: ");
				utn_myGets(&chosenOption, 2);
				chosenOption = toupper(chosenOption);
				while(chosenOption != 65 && chosenOption != 66 && chosenOption != 67 && chosenOption != 68
						&& chosenOption != 69 && chosenOption != 70 && chosenOption != 48)
				{
					printf("Error, ingrese una opcion valida: ");
					utn_myGets(&chosenOption, 2);
					chosenOption = toupper(chosenOption);
				}

				switch(chosenOption)
				{
				case 'A':
					system("cls");
					sUser_listUsers(userList, lenU, ACTIVE, DELETED);
					system("pause");
					system("cls");
					break;
				case 'B':
					system("cls");
					sProduct_sortProductsByCategory(productList, lenP);
					sProduct_listProducts(productList, lenP, FULL, FULL);
					system("pause");
					system("cls");
					break;
				case 'C':
					system("cls");
					sProduct_deleteProduct(productList, lenP);
					break;
				case 'D':
					system("cls");
					sUser_deleteUser(userList, lenU);
					break;
				case 'E':
					system("cls");
					Relations_listGlobalTrackings(trackingList, lenT, productList, lenP, AVAILABLE);
					system("pause");
					system("cls");
					break;
				case 'F':
					system("cls");
					sProduct_findProductsByName(productList, lenP);
					break;
				}

			} while(chosenOption != '0');
			system("cls");
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
