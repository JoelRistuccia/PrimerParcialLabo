#include "Products.h"

static int sProduct_getProductID(void);
static int sProduct_getProductID(void) {
	static int product_id = 4009;//CREATE PRODUCT ID
	return product_id++;
}

int sProduct_initProducts(sProduct productsArray[], int len) {
	int rtn;
	int i;

	if (productsArray != NULL)//VERIFY IF THE ARRAY EXISTS
	{
		if(len > 0)//VERIFY IF THE ARRAY LENGHT IS CORRECT
		{
			for (i = 0; i < len; i++)//LOOP OVER THE ARRAY
			{
				productsArray[i].isEmpty = EMPTY;//SET STATUS 'EMPTY'
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

int sProduct_findAvailableIndex(sProduct productList[], int len) {

	int rtn = -1;
	int i;

	if (productList != NULL)
	{
		if(len > 0)
		{
			for (i = 0; i < len; i++)//LOOP OVER THE ARRAY
			{
				if (productList[i].isEmpty == EMPTY)//ASK FOR STATUS "EMPTY"
				{
					rtn = i;//SAVE THE FIRST INDEX "EMPTY"
					break;//BREAK THE 'FOR' LOOP
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

void sProduct_printProduct(sProduct Product) {
	//PRINTS ALL THE PRODUCT INFO
	printf("|%d", Product.productID);
	printf("%-2s", "|");
	printf("%-23s", Product.productName);
	printf("%-2s", "|");
	printf("%-9.2f", Product.price);
	printf("%-2s", "|");
	if(Product.stock == 0)
	{
		printf("%-8s", "SIN STOCK");
	}
	else
	{
		printf("%-9d", Product.stock);
	}
	printf("%-2s", "|");
	switch(Product.category)
	{
	case 1:
		printf("%-14s", "COMIDA");
		break;
	case 2:
		printf("%-14s", "CONSTRUCCION");
		break;
	case 3:
		printf("%-14s", "MODA");
		break;
	case 4:
		printf("%-14s", "TECNOLOGIA");
		break;
	}
	printf("%-2s", "|\n");
}

int sProduct_listProducts(sProduct productList[], int len, int status1, int status2) {
	int rtn = 0;
	int i;

	puts("\n\t> LISTADO DE PRODUCTOS");
	puts("+----+------------------------+----------+----------+---------------+");
	printf("| %1s%2s%15s%10s%8s%3s%6s%5s%10s%6s\n", "ID", "|", "NOMBRE", "|", "PRECIO", "|",
			"STOCK", "|", "CATEGORIA", "|");
	puts("+----+------------------------+----------+----------+---------------+");

	if (productList != NULL)
	{
		if (len > 0)
		{
			for (i = 0; i < len; i++)
			{		//LISTS EVERY PRODUCT WITH STATUS GIVEN
				if (productList[i].isEmpty == status1 || productList[i].isEmpty == status2)
				{
					sProduct_printProduct(productList[i]);
					rtn = 1;
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
	puts("+----+------------------------+----------+----------+---------------+\n");

	return rtn;
}

int sProduct_sortProductsByCategory(sProduct productList[], int len) {

	int rtn;
	int i;
	int j;
	sProduct aux;

	if (productList != NULL)
	{
		if(len > 0)
		{
			for(i = 0; i < len - 1; i++)//LOOP OVER THE ARRAY
			{
				for(j = i + 1; j < len; j++)//LOOP OVER THE ARRAY 1 INDEX
				{
					//ORDERING CRITERIA - BY CATEGORY - ASCENDING
					if (productList[i].category > productList[j].category)
					{
						aux = productList[i];//EXCHANGE ARRAY POSITIONS
						productList[i] = productList[j];
						productList[j] = aux;
					}
					else
					{
						if(productList[i].category == productList[j].category)
						{
							if((strcmp(productList[i].productName, productList[j].productName)) > 0)
							{
								aux = productList[i];//EXCHANGE ARRAY POSITIONS
								productList[i] = productList[j];
								productList[j] = aux;
							}
						}
					}
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

int sProduct_buyProducts(sProduct productList[], int len) {
	int rtn;
	int idProduct;
	int indexProduct;
	int chosenOption;

	if(productList != NULL)
	{
		if(len > 0)
		{
			sProduct_sortProductsByCategory(productList, len);
			sProduct_listProducts(productList, len, FULL, OUT_OF_STOCK);
			getInt("Que accion desea realizar?\n\n"
					"\t1) Comprar un producto\n"
					"\t0) Volver al menu anterior\n\n"
					"Ingrese la opcion deseada: ", 10, 0, 1,
					"Error, ingrese una opcion valida: ", &chosenOption);
			if(chosenOption == 1)
			{
				getInt("Ingrese el ID del producto que desea comprar: ", 10, 4000, 6000,
						"Error, ingrese un ID de la lista: ", &idProduct);
				indexProduct = sProduct_findProductIndexById(productList, len, idProduct);
				while(productList[indexProduct].stock == 0)
				{
					getInt("\nProducto sin stock disponible, ingrese otro ID: ", 10, 4000, 6000,
							"Error, ingrese un ID de la lista: ", &idProduct);
					indexProduct = sProduct_findProductIndexById(productList, len, idProduct);
				}
				rtn = indexProduct;
			}
			else
			{
				rtn = -1;//RETURNS -1 IF WANT TO GO BACK
				system("cls");
			}
		}
		else
		{
			rtn = -2;//ERROR - ARRAY LENGHT
		}
	}
	else
	{
		rtn = -3;//ERROR - NULL POINTER
	}

	return rtn;
}

int sProduct_findProductIndexById(sProduct productList[], int len, int givenID) {

	int rtn;
	int i;

	if(productList != NULL)//VERIFIES IF THE ARRAY EXISTS
	{
		if(len > 0)//VERIFIES IF ARRAY LENGHT IS LARGER THAN 0
		{
			for (i = 0; i < len; i++)//LOOP OVER THE ARRAY
			{
				//VERIFY IF ID EXISTS AND IF ITS STATE IS NOT "EMPTY "
				if(productList[i].productID == givenID && productList[i].isEmpty != EMPTY)
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

int sProduct_addProduct(sProduct productList[], int len) {
	int rtn = -1;
	int index;
	sProduct auxiliary;

	if(productList != NULL)
	{
		if(len > 0)
		{
			index = sProduct_findAvailableIndex(productList, len);
			auxiliary = sProduct_getProductInfo();
			if(auxiliary.category > 0)
			{
				auxiliary.productID = sProduct_getProductID();
				auxiliary.isEmpty = 2;

				if(continueOrNot("\nDesea confirmar la publicacion de venta? (S/N): ",
						"\nError, ingrese una opcion valida: (S/N): "))
				{
					productList[index] = auxiliary;
					rtn = index;
					puts("\nSu venta ha sido publicada. Muchas gracias!");
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

int sProduct_deleteProduct(sProduct productList[], int lenP) {
	int rtn = 0;
	int idToCancel;
	int indexToCancel;
	int chosenOption;

	if(productList != NULL)
	{
		if(lenP > 0)
		{
			sProduct_sortProductsByCategory(productList, lenP);
			sProduct_listProducts(productList, lenP, FULL, OUT_OF_STOCK);
			getInt("Que accion desea realizar?\n\n"
					"\t1) Dar de baja un producto\n"
					"\t0) Volver al menu anterior\n\n"
					"Ingrese la opcion deseada: ", 10, 0, 1,
					"Error, ingrese una opcion valida: ", &chosenOption);
			if(chosenOption == 1)
			{
				getInt("Ingrese el ID del producto que desea dar de baja del sistema: ", 10, 4000, 5000,
						"\nError, ingrese un ID de la lista: ", &idToCancel);
				indexToCancel = sProduct_findProductIndexById(productList, lenP, idToCancel);

				while(indexToCancel == -1)
				{
					getInt("El ID no existe, por favor ingrese un ID de la lista: ", 10, 4000, 5000,
							"\nError, ingrese un ID de la lista: ", &idToCancel);
					indexToCancel = sProduct_findProductIndexById(productList, lenP, idToCancel);
				}

				if(continueOrNot("\nDesea confirmar la baja? (S/N): ", "\nError, ingrese una opcion "
						"valida (S/N): "))
				{
					productList[indexToCancel].isEmpty = -1;
					puts("El producto ha sido dado de baja del sistema.\n");
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

sProduct sProduct_getProductInfo(void) {
	sProduct auxiliary;
	int category;

	getInt("Que tipo de producto desea vender? Elija una categoria:\n\n"
			"\t1) Alimentos\n"
			"\t2) Construccion\n"
			"\t3) Moda\n"
			"\t4) Tecnologia\n\n"
			"\t0) Volver al menu anterior\n\n"
			"Ingrese la opcion deseada: ", 10, 0, 4, "Error, ingrese una opcion valida: ", &category);
	if(category > 0)
	{
		auxiliary.category = category;
		printf("Ingrese el nombre del producto: ");
		utn_myGets(auxiliary.productName, MAX_LEN_NAME);
		getFloat("Ingrese el precio del producto: ", 10, 1, 1000000,
				"Error, ingrese un precio valido: ", &auxiliary.price);
		getInt("Ingrese la cantidad de unidades que desea publicar: ", 10, 1, 1000000,
				"Error, ingrese una cantidad valida: ", &auxiliary.stock);
	}
	else
	{
		auxiliary.category = category;
		system("cls");
	}
	return auxiliary;
}

int sProduct_verifyProductsGlobalStatus(sProduct productList[], int len, int status1, int status2) {
	int rtn = 0;
	int i;

	if (productList != NULL)
	{
		if (len > 0)
		{
			for (i = 0; i < len; i++)//LOOP OVER THE ARRAY
			{
				if (productList[i].isEmpty == status1 || productList[i].isEmpty == status2)
				{
					rtn = 1;//RETURNS 1 IF FIND AT LEAST 1 PRODUCT WITH THE STATUS GIVEN
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

int sProduct_chooseUserProduct(sProduct productList[], int len, int userID) {
	int rtn;
	int idProduct;
	int indexProduct;
	int chosenOption;

	if(productList != NULL)
	{
		if(len > 0)
		{
			sProduct_sortProductsByCategory(productList, len);
			sProduct_listUserProducts(productList, len, FULL, OUT_OF_STOCK, userID);
			getInt("Que accion desea realizar?\n\n"
					"\t1) Reponer stock de un producto\n"
					"\t0) Volver al menu anterior\n\n"
					"Ingrese la opcion deseada: ", 10, 0, 1,
					"\nError, ingrese una opcion valida: ", &chosenOption);
			if(chosenOption == 1)
			{
				getInt("\nIngrese el ID del producto del cual desea agregar stock: ", 10, 4000, 6000,
						"Error, ingrese un ID de la lista: ", &idProduct);
				indexProduct = sProduct_findProductIndexById(productList, len, idProduct);
				while(productList[indexProduct].FK_userID != userID)
				{
					getInt("\nError, ingrese un ID de la lista: ", 10, 4000, 6000,
							"Error, ingrese un ID de la lista: ", &idProduct);
					indexProduct = sProduct_findProductIndexById(productList, len, idProduct);
				}
				rtn = indexProduct;
			}
			else
			{
				rtn = -1;//RETURNS -1 IF WANT TO GO BACK
				system("cls");
			}
		}
		else
		{
			rtn = -2;//ERROR - ARRAY LENGHT
		}
	}
	else
	{
		rtn = -3;//ERROR - NULL POINTER
	}

	return rtn;
}


int sProduct_listUserProducts(sProduct productList[], int len, int status1, int status2, int userID) {
	int rtn = 0;
	int i;

	puts("\n\t> LISTADO DE PRODUCTOS");
	puts("+----+------------------------+----------+----------+---------------+");
	printf("| %1s%2s%15s%10s%8s%3s%6s%5s%10s%6s\n", "ID", "|", "NOMBRE", "|", "PRECIO", "|",
			"STOCK", "|", "CATEGORIA", "|");
	puts("+----+------------------------+----------+----------+---------------+");

	if (productList != NULL)
	{
		if (len > 0)
		{
			for (i = 0; i < len; i++)
			{		//LISTS EVERY PRODUCT WITH STATUS GIVEN
				if(productList[i].FK_userID == userID)
				{
					if (productList[i].isEmpty == status1 || productList[i].isEmpty == status2)
					{
						sProduct_printProduct(productList[i]);
						rtn = 1;
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
	puts("+----+------------------------+----------+----------+---------------+\n");

	return rtn;
}

int sProduct_addProductStock(sProduct productList[], int len, int userID) {
	int rtn = 0;
	int productIndex;
	int flag;
	int stockToAdd;

	if(productList != NULL)
	{
		if(len > 0 && userID > 0)
		{
			flag = sProduct_verifyUserProducts(productList, len, userID);
			if(flag == 1)
			{
				productIndex = sProduct_chooseUserProduct(productList, len, userID);
				if(productIndex > -1)
				{
					getInt("Ingrese la cantidad de unidades que desea agregar: ", 10, 1, 10000,
							"\nError, ingrese una cantidad valida: ", &stockToAdd);
					if(continueOrNot("Desea confirmar el ingreso de stock? (S/N): ",
							"Error, ingrese una opcion valida (S/N)"))
					{
						productList[productIndex].stock += stockToAdd;
						printf("El stock se ha renovado exitosamente.\n\n");
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
			{
				printf("Usted no tiene productos disponibles para renovar stock.\n");
				system("pause");
				system("cls");

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

	return rtn;
}

int sProduct_searchProductsByName(sProduct productList[], int len, int status1, int status2, char productName[]) {
	int rtn = 0;
	int i;

	puts("\n\t> LISTADO DE PRODUCTOS");
	puts("+----+------------------------+----------+----------+---------------+");
	printf("| %1s%2s%15s%10s%8s%3s%6s%5s%10s%6s\n", "ID", "|", "NOMBRE", "|", "PRECIO", "|",
			"STOCK", "|", "CATEGORIA", "|");
	puts("+----+------------------------+----------+----------+---------------+");

	if (productList != NULL && productName != NULL)
	{
		if (len > 0)
		{
			for (i = 0; i < len; i++)
			{	//LISTS EVERY PRODUCT WITH STATUS GIVEN
				if(strcmp(productList[i].productName, productName) == 0)
				{
					if (productList[i].isEmpty == status1 || productList[i].isEmpty == status2)
					{
						sProduct_printProduct(productList[i]);
						rtn = 1;
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
	puts("+----+------------------------+----------+----------+---------------+\n");

	return rtn;
}

int sProduct_sortProductsByStock(sProduct productList[], int len) {

	int rtn;
	int i;
	int j;
	sProduct aux;

	if (productList != NULL)
	{
		if(len > 0)
		{
			for(i = 0; i < len - 1; i++)//LOOP OVER THE ARRAY
			{
				for(j = i + 1; j < len; j++)//LOOP OVER THE ARRAY 1 INDEX
				{
					//ORDERING CRITERIA - BY CATEGORY - ASCENDING
					if (productList[i].stock > productList[j].category)
					{
						aux = productList[i];//EXCHANGE ARRAY POSITIONS
						productList[i] = productList[j];
						productList[j] = aux;
					}
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

int sProduct_findProductsByName(sProduct productList[], int len) {
	int rtn = 0;
	char productName[MAX_LEN_NAME];
	int productReturn;

	if (productList != NULL)
	{
		if (len > 0)
		{
			sProduct_sortProductsByStock(productList, len);
			printf("Ingrese el nombre del producto que desea buscar: ");
			utn_myGets(productName, MAX_LEN_NAME);
			productReturn = sProduct_verifyProductsByName(productList, len, productName);
			while(productReturn < 1)
			{
				printf("No existen productos dados de alta con ese nombre, intente nuevamente: ");
				utn_myGets(productName, MAX_LEN_NAME);
				productReturn = sProduct_verifyProductsByName(productList, len, productName);
			}
			sProduct_searchProductsByName(productList, len, FULL, OUT_OF_STOCK, productName);
			system("pause");
			system("cls");

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

int sProduct_verifyProductsByName(sProduct productList[], int len, char productName[]) {
	int rtn = 0;
	int i;

	if (productList != NULL && productName != NULL)
	{
		if (len > 0)
		{
			for (i = 0; i < len; i++)
			{	//LISTS EVERY PRODUCT WITH STATUS GIVEN
				if(strcmp(productList[i].productName, productName) == 0)
				{
					if (productList[i].isEmpty == FULL|| productList[i].isEmpty == OUT_OF_STOCK)
					{
						rtn = 1;
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

int sProduct_verifyUserProducts(sProduct productList[], int len, int userID) {
	int rtn = 0;
	int i;

	if (productList != NULL)
	{
		if (len > 0 && userID > 0)
		{
			for (i = 0; i < len; i++)
			{	//LISTS EVERY PRODUCT WITH STATUS GIVEN
				if(productList[i].FK_userID == userID)
				{
					if (productList[i].isEmpty == FULL|| productList[i].isEmpty == OUT_OF_STOCK)
					{
						rtn = 1;
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

void sProduct_hardCodeProducts (sProduct productList[]) {

	productList[0].productID = 4000;
	productList[0].FK_userID = 1000;
	productList[0].isEmpty = 2;
	productList[0].category = 4;
	strcpy(productList[0].productName, "Pendrive Kingston");
	productList[0].price = 2000;
	productList[0].stock = 100;

	productList[1].productID = 4001;
	productList[1].FK_userID = 1002;
	productList[1].isEmpty = 2;
	productList[1].category = 3;
	strcpy(productList[1].productName, "Pantalon Jean");
	productList[1].price = 1500;
	productList[1].stock = 25;

	productList[2].productID = 4002;
	productList[2].FK_userID = 1002;
	productList[2].isEmpty = 1;
	productList[2].category = 1;
	strcpy(productList[2].productName, "Papas Pringles");
	productList[2].price = 200;
	productList[2].stock = 0;

	productList[3].productID = 4003;
	productList[3].FK_userID = 1002;
	productList[3].isEmpty = 2;
	productList[3].category = 2;
	strcpy(productList[3].productName, "Ladrillos huecos");
	productList[3].price = 100;
	productList[3].stock = 1000;

	productList[4].productID = 4004;
	productList[4].FK_userID = 1000;
	productList[4].isEmpty = 2;
	productList[4].category = 4;
	strcpy(productList[4].productName, "SmartWatch Apple");
	productList[4].price = 20000;
	productList[4].stock = 50;

	productList[5].productID = 4005;
	productList[5].FK_userID = 1002;
	productList[5].isEmpty = 2;
	productList[5].category = 1;
	strcpy(productList[5].productName, "Galletitas Oreo");
	productList[5].price = 150;
	productList[5].stock = 100;

	productList[6].productID = 4006;
	productList[6].FK_userID = 1002;
	productList[6].isEmpty = 2;
	productList[6].category = 2;
	strcpy(productList[6].productName, "Bolsas de cemento 15kg");
	productList[6].price = 1200;
	productList[6].stock = 65;

	productList[7].productID = 4007;
	productList[7].FK_userID = 1000;
	productList[7].isEmpty = 2;
	productList[7].category = 4;
	strcpy(productList[7].productName, "Memoria RAM 16Gb");
	productList[7].price = 11000;
	productList[7].stock = 10;

	productList[8].productID = 4008;
	productList[8].FK_userID = 1000;
	productList[8].isEmpty = 2;
	productList[8].category = 4;
	strcpy(productList[8].productName, "Pendrive Kingston");
	productList[8].price = 2000;
	productList[8].stock = 55;
}
