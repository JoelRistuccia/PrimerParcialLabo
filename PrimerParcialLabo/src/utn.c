#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "utn.h"


float sumar(float num1, float num2) {
	float rtn;
	rtn = num1 + num2;

	return rtn;
}

float restar(float num1, float num2) {
	float rtn;

	rtn = num1 - num2;

	return rtn;
}

float multiplicar(float num1, float num2) {
	float rtn;
	rtn = num1 * num2;

	return rtn;
}

float dividir(float num1, float num2) {
	float rtn;

	rtn=num1/num2;
	if(num2==0){
		rtn=0;
	}
	return rtn;

	return rtn;
}

int utn_myGets(char cadena[], int longitud){

	int retorno = -1;

	fflush(stdin);
	if(cadena != NULL && longitud > 0 && fgets(cadena, longitud, stdin))
	{
		fflush(stdin);
		if(cadena[strlen(cadena)-1] == '\n')
		{
			cadena[strlen(cadena)-1] = '\0' ;
		}
		retorno = 0;//OK
	}
	return retorno;
}


int utn_Get_Int(int *pResultado) {

	int retorno = -1;
	char buffer[64];

	fflush(stdin);
	utn_myGets(buffer, 64);

	if(utn_esNumerica(buffer)==0)
	{
		*pResultado = atoi(buffer);
		retorno = 0;
	}

	return retorno;
}


int utn_Get_Float(float *pResultado) {

	int retorno = -1;
	char buffer[64];

	fflush(stdin);
	utn_myGets(buffer, 64);

	if(utn_esNumerica(buffer)==0)
	{
		*pResultado = atof(buffer);
		retorno = 0;
	}

	return retorno;
}

int utn_esNumerica (char cadena[]){

	int retorno = 0;
	int i = 0;

	if(cadena != NULL && strlen(cadena) > 0)
	{
		while(cadena[i] != '\0')
		{
			if(cadena[i] < 48 || cadena[i] > 57)
			{
				retorno = -1;
				break;
			}
			i++;
		}
	}
	return retorno;
}

int getInt(char mensaje[],int reintentos, int minimo, int maximo, char mensajeError[], int *pNumeroIngresado){

	int rtn = -1;
	int auxiliarInt;
	int retorno;

	if(mensaje != NULL && reintentos > 0 && minimo < maximo && mensajeError !=NULL && pNumeroIngresado != NULL){

		printf("%s", mensaje);
		fflush(stdin);
		retorno = utn_Get_Int(&auxiliarInt);
		do{
			if(auxiliarInt<minimo || auxiliarInt>maximo || retorno != 0)
			{
				printf("%s", mensajeError);
				fflush(stdin);
				retorno = utn_Get_Int(&auxiliarInt);
				reintentos--;
			}
			else
			{
				*pNumeroIngresado=auxiliarInt;
				reintentos = 0;
				rtn = 0;
			}

		}while(reintentos > 0);
	}
	return rtn;
}


int getFloat(char mensaje[],int reintentos, int minimo, int maximo, char mensajeError[], float *pNumeroIngresado){

	int rtn= -1;
	float auxiliarFloat;
	int retorno;

	if(mensaje!=NULL && reintentos>0 && minimo<maximo && mensajeError!=NULL && pNumeroIngresado!=NULL){

		printf("%s", mensaje);
		fflush(stdin);
		retorno = utn_Get_Float(&auxiliarFloat);
		do{
			if(auxiliarFloat < minimo || auxiliarFloat > maximo || retorno != 0)
			{
				printf("%s", mensajeError);
				fflush(stdin);
				retorno = utn_Get_Float(&auxiliarFloat);
				reintentos--;
			}
			else
			{
				*pNumeroIngresado=auxiliarFloat;
				reintentos=0;
				rtn = 0;
			}
		}while(reintentos > 0);
	}

	return rtn;
}

int continueOrNot(char message[], char errorMessage[]){

	int rtn = -1;//RETURN -1 IF ERROR
	char answer;

	if(message != NULL && errorMessage != NULL)
	{
		printf(message);
		fflush(stdin);
		utn_myGets(&answer, 2);
		answer = toupper(answer);

		while(answer != 83 && answer != 78)
		{
			printf(errorMessage);
			fflush(stdin);
			utn_myGets(&answer, 2);
			answer = toupper(answer);
		}

		if(answer==83)
		{
			rtn = 1;//RETURN 1 IF IT DOES WANT TO CONTINUE
		}
		else
		{
			rtn = 0;//RETURN 0 IF IT DOESN'T WANT TO CONTINUE
		}
	}

	return rtn;
}

int getChar(char message[], int retries, char errorMessage[], char *character) {

	int rtn = -1;//ERROR - NULL POINTER

	if(message != NULL && errorMessage != NULL && character != NULL)
	{
		if(retries > 0)
		{
			printf(message);
			fflush(stdin);
			utn_myGets(character, 2);
			do{
				if(*character < 65 || (*character > 90 && *character < 97) || *character > 122)
				{
					retries--;
					printf(errorMessage);
					fflush(stdin);
					utn_myGets(character, 2);
				}
				else
				{
					retries = 0;
					rtn = 0;
				}
			}while(retries > 0);
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

	return rtn;//RETURN 0 IF OK

}

int getEmail(char message[], char errorMessage[], int retries, char email[]) {
	int rtn;
	char auxiliary[25] = "";
	int i;
	int flag1;
	int flag2;


	if(message != NULL && errorMessage != NULL && email)
	{
		printf(message);
		fflush(stdin);
		utn_myGets(auxiliary, 25);
		do{
			flag1 = 0;
			flag2 = 0;
			for(i=0; i < 25; i++)
			{
				if(flag1 == 0 && auxiliary[i] == 64)
				{
					flag1 = 1;
				}

				if(flag1 == 1 && flag2 == 0 && auxiliary[i] == 46)
				{
					flag2 = 1;
				}

			}

			if(flag1 != 1 || flag2 != 1)
			{
				printf(errorMessage);
				fflush(stdin);
				utn_myGets(auxiliary, 25);
				retries--;
			}
			else
			{
				retries = 0;
				strcpy(email, auxiliary);
			}

		}while(retries > 0);
	}
	else
	{
		rtn = -1;//ERROR - NULL POINTER
	}

	return rtn;
}

long int time_Current(void) {
	return time(NULL);
}


long int time_Add(double secondsAdd) {
	return secondsAdd + time_Current();
}


int getPassword(char message[], char errorMessage[], int min, int max, int retries, char password[]) {
	int rtn;
	char auxiliary[50];
	int flagNum;
	int flagLet;
	int i;

	if(message != NULL && errorMessage != NULL && password != NULL)
	{
		fflush(stdin);
		printf(message);
		utn_myGets(auxiliary, 50);

		do{
			flagNum = 0;//INICIALIZO BANDERAS EN 0 EN CADA LOOP
			flagLet = 0;
			//VERIFICO SI RESPETA MINIMO Y MAXIMO DE LONGITUD
			while(strlen(auxiliary) < min || strlen(auxiliary) > max)
			{
				printf(errorMessage);//SI NO LO RESPETA VUELVO A PEDIR Y RESTO INTENTOS
				retries--;
				fflush(stdin);
				utn_myGets(auxiliary, 50);
			}
			//RECORRO EL STRING
			for(i = 0; i < strlen(auxiliary); i++)
			{	//VERIFICO QUE HAYA INGRESADO SOLO NUMEROS Y LETRAS
				if(auxiliary[i] < 48 || (auxiliary[i] > 57 && auxiliary[i] < 64)
						|| (auxiliary[i] > 90 && auxiliary[i] < 97) || auxiliary[i] > 122)
				{
					printf(errorMessage);//CASO CONTRARIO VUELVO A PEDIR Y RESTO INTENTOS
					retries--;
					fflush(stdin);
					utn_myGets(auxiliary, 50);
					break;
				}
				else
				{	//VERIFICO SI INGRESO AL MENOS 1 NUMERO
					if(auxiliary[i] > 47 && auxiliary[i] < 58)
					{
						flagNum = 1;
					}
					//VERIFICO SI INGRESO AL MENOS 1 LETRA
					if((auxiliary[i] > 64 && auxiliary[i] < 91) || (auxiliary[i] > 96 && auxiliary[i] < 123))
					{
						flagLet = 1;
					}
				}
			}
			//SI SE CUMPLEN LAS 2 CONDICIONES (NUMEROS/LETRAS)
			if(flagNum == 1 && flagLet == 1)
			{
				retries = 0;//SETEO INTENTOS EN 0 PARA SALIR DEL BUCLE
				strcpy(password, auxiliary);//COPIO EL AUXILIAR AL STRING DESTINO
				rtn = 0;

			}
			else
			{	//SI NO SE CUMPLEN LAS 2 VUELVO A PEDIR Y RESTO INTENTOS
				printf(errorMessage);
				retries--;
				fflush(stdin);
				utn_myGets(auxiliary, 50);
			}
		}while(retries > 0);
	}
	else
	{
		rtn = -1;//ERROR NULL POINTER
	}

	return rtn;//RETURN 0 SI SALIO OK
}


int getAddress(char message[], char errorMessage[], int reTries, char address[]) {
	int rtn;
	char auxiliary[50];
	int flagNum;
	int flagLet;
	int flagSpace;
	int i;

	if(message != NULL && errorMessage != NULL && address != NULL)
	{
		fflush(stdin);
		printf(message);
		utn_myGets(auxiliary, 50);

		do{
			flagNum = 0;//INICIALIZO BANDERAS EN 0 EN CADA LOOP
			flagLet = 0;
			flagSpace = 0;
			//RECORRO EL STRING
			for(i = 0; i < strlen(auxiliary); i++)
			{	//VERIFICO QUE HAYA INGRESADO SOLO NUMEROS Y LETRAS Y ESPACIOS
				if(auxiliary[i] < 32 || (auxiliary[i] > 32 && auxiliary[i] < 48) ||
						(auxiliary[i] > 57 && auxiliary[i] < 64)|| (auxiliary[i] > 90 && auxiliary[i] < 97)
						|| auxiliary[i] > 122)
				{
					printf(errorMessage);//CASO CONTRARIO VUELVO A PEDIR Y RESTO INTENTOS
					reTries--;
					fflush(stdin);
					utn_myGets(auxiliary, 50);
					break;
				}
				else
				{
					//VERIFICO SI INGRESO AL MENOS 1 LETRA
					if((auxiliary[i] > 64 && auxiliary[i] < 91) || (auxiliary[i] > 96 && auxiliary[i] < 123))
					{
						flagLet = 1;
					}
					//VERIFICO SI INGRESO AL MENOS 1 ESPACIO
					if(flagLet == 1 && auxiliary[i] == 32)
					{
						flagSpace = 1;
					}
					//VERIFICO SI INGRESO AL MENOS 1 NUMERO
					if(flagLet == 1 && flagSpace == 1 && auxiliary[i] > 47 && auxiliary[i] < 58)
					{
						flagNum = 1;
					}

				}
			}
			//SI SE CUMPLEN LAS 2 CONDICIONES (NUMEROS/LETRAS)
			if(flagNum == 1 && flagSpace == 1 && flagLet == 1)
			{
				reTries = 0;//SETEO INTENTOS EN 0 PARA SALIR DEL BUCLE
				strcpy(address, auxiliary);//COPIO EL AUXILIAR AL STRING DESTINO
				rtn = 0;
			}
			else
			{	//SI NO SE CUMPLEN LAS 2 VUELVO A PEDIR Y RESTO INTENTOS
				printf(errorMessage);
				reTries--;
				fflush(stdin);
				utn_myGets(auxiliary, 50);
			}
		}while(reTries > 0);
	}
	else
	{
		rtn = -1;//ERROR NULL POINTER
	}

	return rtn;//RETURN 0 SI SALIO OK0000000000
}


