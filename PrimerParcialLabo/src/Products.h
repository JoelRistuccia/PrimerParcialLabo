/*
 * BIBLIOTECA DESTINADA A CONTENER LAS FUNCIONES DE PRODUCTOS
 */

#ifndef PRODUCTS_H_
#define PRODUCTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utn.h"

#define MAX_PRODUCTS 1000
//STRING LENGHTS
#define MAX_LEN_STRING 64
#define MAX_LEN_NAME 25
//ISEMPTY STATES
#define FULL 2
#define OUT_OF_STOCK 1
#define EMPTY 0
#define DISABLED -1
//PRODUCT CATEGORIES

#define FOOD 1
#define CONSTRUCTION 2
#define FASHION 3
#define TECHNOLOGY 4


typedef struct{

	int productID;
	short int isEmpty;
	int FK_userID; //RELATION SELLER - PRODUCTS
	char productName[MAX_LEN_NAME];
	float price;
	short int category;
	int stock;

}sProduct;


int sProduct_initProducts(sProduct productsArray[], int len);
void sProduct_hardCodeProducts (sProduct productList[]);
int sProduct_findAvailableIndex(sProduct productList[], int len);
void sProduct_printProduct(sProduct Product);
int sProduct_listProducts(sProduct productList[], int len, int status1, int status2);
int sProduct_verifyProductsGlobalStatus(sProduct productList[], int len, int status1, int status2);
int sProduct_sortProductsByCategory(sProduct productList[], int len);
int sProduct_findProductIndexById(sProduct productList[], int len, int givenID);
int sProduct_buyProducts(sProduct productList[], int len);
int sProduct_addProduct(sProduct productList[], int len);
int sProduct_deleteProduct(sProduct productList[], int lenP);
sProduct sProduct_getProductInfo(void);
int sProduct_listUserProducts(sProduct productList[], int len, int status1, int status2, int userID);
int sProduct_chooseUserProduct(sProduct productList[], int len, int userID);
int sProduct_addProductStock(sProduct productList[], int len, int userID);
int sProduct_searchProductsByName(sProduct productList[], int len, int status1, int status2, char productName[]);
int sProduct_sortProductsByStock(sProduct productList[], int len);
int sProduct_verifyProductsByName(sProduct productList[], int len, char productName[]);
int sProduct_findProductsByName(sProduct productList[], int len);

#endif /* PRODUCTS_H_ */
