/*
 * BIBLIOTECA DESTINADA A ALOJAR LAS FUNCIONES DE USUARIOS
 */

#ifndef USERS_H_
#define USERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utn.h"

#define MAX_USERS 100
//STRING LENGHTS
#define MAX_LEN_EMAIL 25
#define MAX_LEN_PASSWORD 10
#define MIN_LEN_PASSWORD 4
#define MAX_LEN_DIRECTION 50
//USER TYPES
#define ADMIN 1
#define USER 2
//USER STATES
#define ACTIVE 1
#define EMPTY 0
#define DELETED -1


typedef struct{

	int userID;
	short int isEmpty;
	//RELATION¿?
	short int type;
	char email[MAX_LEN_EMAIL];
	char password[MAX_LEN_PASSWORD];
	char direction[MAX_LEN_DIRECTION];
	int postalCode;

}sUser;

int sUser_initUsers(sUser arrayUsers[], int len);
int sUser_findAvailableIndex(sUser userList[], int len);
sUser sUser_getUserInfo(void);
int sUser_userRegister(sUser userList[], int len);
int sUser_deleteUser(sUser userList[], int len);
void sUser_hardCodeUserData(sUser userList[]);
int sUser_getLoginData(sUser userList[], int len);
void sUser_printUser(sUser User);
int sUser_listUsers(sUser userList[], int len, int status1, int status2);
int sUser_findUserIndexById(sUser userList[], int len, int givenID);
int sUser_findUserIndexByEmail(sUser userList[], int len, char givenEmail[]);

#endif /* USERS_H_ */
