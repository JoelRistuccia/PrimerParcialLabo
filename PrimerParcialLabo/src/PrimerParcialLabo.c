#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utn.h"
#include "Relations.h"


int main(void) {
	setbuf(stdout, NULL);

	int chosenOption;
	sUser userList[MAX_USERS];
	sProduct productList[MAX_PRODUCTS];
	sTracking trackingList[MAX_TRACKINGS];

	sUser_initUsers(userList, MAX_USERS);//INIT USERS ARRAY
	sUser_hardCodeUserData(userList);

	sProduct_initProducts(productList, MAX_PRODUCTS);//INIT PRODUCTS ARRAY
	sProduct_hardCodeProducts(productList);

	sTracking_initTracking(trackingList, MAX_TRACKINGS);//INIT TRACKINGS ARRAY
	sTracking_hardCodeTrackings(trackingList);

	do{
		system("cls");
		puts("\t\t*********************************");
		puts("\t\t****** 1er EXAM LAB I - 1H ******");
		puts("\t\t*********************************\n\n");
		puts("1) INGRESAR");
		puts("2) REGISTRARSE\n");

		puts("0) SALIR\n");
		//ASKS FOR MENU OPTION
		getInt("Ingrese la opcion deseada: ", 10, 0, 2, "Error, ingrese una opcion valida: ", &chosenOption);


		switch(chosenOption)
		{
		case 1:
			system("cls");//LOGIN OPTION
			Relations_userLogin(userList, MAX_USERS, productList, 100, trackingList, 1000);
			break;
		case 2:
			system("cls");//REGISTER OPTION
			sUser_userRegister(userList, MAX_USERS);
			break;
		}
	}while(chosenOption != 0);//0 FOR EXIT PROGRAM







}
