#ifndef UTN_H_
#define UTN_H_

float sumar(float num1, float num2);
float restar(float num1, float num2);
float multiplicar(float num1, float num2);
float dividir(float num1, float num2);
int utn_myGets(char cadena[], int longitud);
int utn_Get_Int(int *pResultado);
int getFloat(char mensaje[],int reintentos, int minimo, int maximo, char mensajeError[], float *pNumeroIngresado);
int getInt(char mensaje[],int reintentos, int minimo, int maximo, char mensajeError[], int *pNumeroIngresado);
int utn_esNumerica (char cadena[]);
int getChar(char message[], int retries, char min, char max, char errorMessage[], char *character);
int continueOrNot(char message[], char errorMessage[]);
int getEmail(char message[], char errorMessage[], int retries, char email[]);
int getPassword(char message[], char errorMessage[], int min, int max, int retries, char password[]);
int getAddress(char message[], char errorMessage[], int reTries, char address[]);
long int time_Current(void);
long int time_Add(double secondsAdd);

#endif
