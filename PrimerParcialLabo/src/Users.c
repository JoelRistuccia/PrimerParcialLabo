#include "Users.h"

static int sUser_getUserID(void);
static int sUser_getUserID(void) {
	static int user_id = 1002;
	return user_id++;//CREATE USER ID
}


int sUser_initUsers(sUser usersArray[], int len) {
	int rtn;
	int i;

	if (usersArray != NULL)//VERIFY IF THE ARRAY EXISTS
	{
		if(len > 0)//VERIFY IF THE ARRAY LENGHT IS CORRECT
		{
			for (i = 0; i < len; i++)//LOOP OVER THE ARRAY
			{
				usersArray[i].isEmpty = EMPTY;//SET STATUS 'EMPTY'
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


int sUser_findAvailableIndex(sUser userList[], int len) {

	int rtn = -1;
	int i;

	if (userList != NULL)
	{
		if(len > 0)
		{
			for (i = 0; i < len; i++)//LOOP OVER THE ARRAY
			{
				if (userList[i].isEmpty == EMPTY)//ASK FOR STATUS "EMPTY"
				{
					rtn = i;//RETURNS THE FIRST INDEX WITH STATUS "EMPTY"
					break;
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


sUser sUser_getUserInfo(void) {
	sUser auxiliary;

	auxiliary.type = 2;//ASKS FOR ALL THE USER DATA FOR REGISTRY
	getEmail("Ingrese su email: ", "Error,  ingrese un email valido: ", 10, auxiliary.email);
	getPassword("\nIngrese su contrasenia (4 - 10 caracteres / Debe contener numeros y letras): ",
			"Error, ingrese una contrasenia valida: ", 4, 10, 10, auxiliary.password);
	getAddress("\nIngrese su direccion: ", "Error, ingrese una direccion valida: ", 10, auxiliary.direction);
	getInt("\nIngrese su codigo postal: ", 10, 0001, 9999,
			"Error, ingrese un codigo postal valido: ", &auxiliary.postalCode);

	return auxiliary;
}


int sUser_userRegister(sUser userList[], int len) {
	int rtn;
	int foundIndex;
	sUser userAuxiliary;
	//FIND AN AVAILABLE INDEX
	foundIndex = sUser_findAvailableIndex(userList, len);
	if (userList != NULL)
	{
		if (len > 0)
		{
			if (foundIndex >= 0)//ASKS IF FOUND INDEX IS VALID
			{
				userAuxiliary = sUser_getUserInfo();//ASKS FOR USER DATA
				userAuxiliary.userID = sUser_getUserID();//CREATE USER ID
				userAuxiliary.isEmpty = ACTIVE;//SET 'ISEMPTY' STATUS -> "ACTIVE"
				//ASKS FOR CONFIRMATION
				if(continueOrNot("\nDesea confirmar el registro? (S/N): ", "Error, reingrese (S/N): "))
				{	//IF USER CONFIRMS COPY THE AUXILIARY TO USERLIST AT FOUND INDEX
					userList[foundIndex] = userAuxiliary;
					puts("\nSu cuenta ha sido creada exitosamente.\n");
					rtn = 0;//RETURN 0 - IF OK
					system("pause");
					system("cls");
				}

			}
			else
			{
				rtn = -3;//ERROR - NO INDEX FOUND
			}
		}
		else
		{
			rtn = -2;//ERROR - ARRAY LENGHT
		}
	}
	else
	{
		rtn = -1;//ERROR - NULL POINTER
	}

	return rtn;
}


int sUser_getLoginData(sUser userList[], int len) {
	int rtn = 0;
	char email[MAX_LEN_EMAIL];
	char password[MAX_LEN_PASSWORD];
	int emailIndex = 0;
	int flagPass = 0;

	if(userList != NULL)
	{
		if(len > 0)
		{   //ASKS FOR EMAIL
			getEmail("Ingrese su correo electronico:\n", "\nError, ingrese un correo valido:\n", 10, email);
			while(emailIndex == 0)
			{	//CHECK IF EMAIL IS REGISTERED
				emailIndex = sUser_findUserIndexByEmail(userList, len, email);
				if(emailIndex > -1)//IF EMAIL EXISTS RETURNS > -1
				{	//CHECK IF USER ACCOUNT IS 'DELETED'
					while(userList[emailIndex].isEmpty == DELETED)
					{	//IF ITS DELETED ASKS FOR ANOTHER EMAIL
						puts("Usuario inhabilitado. Ingrese otro correo:");
						utn_myGets(email, MAX_LEN_EMAIL);
						emailIndex = sUser_findUserIndexByEmail(userList, len, email);
					}
					break;//BREAK THE 'WHILE' LOOP
				}
				else
				{   //IF EMAIL ISN'T REGISTERED ASKS AGAIN
					puts("\nCorreo electronico no registrado, intente nuevamente");
					getEmail("\nIngrese su correo electronico:\n", "\nError, ingrese un correo valido:\n", 10, email);
					emailIndex = sUser_findUserIndexByEmail(userList, len, email);
				}
			}
			//ASKS FOR PASSWORD
			getPassword("\nIngrese su contrasenia: ", "\nError, ingrese una contrasenia valida: ", 4, 10, 10, password);
			while(flagPass == 0)
			{
				if(strcmp(userList[emailIndex].password, password) == 0)//CHECK IF PASSWORD IS CORRECT
				{
					flagPass = 1;//SET FLAG IN 1
				}
				else
				{	//IF PASSWORD IS NOT CORRECT
					puts("Contrasenia incorrecta, intente nuevamente");
					utn_myGets(password, MAX_LEN_PASSWORD);
				}
			}
			rtn = emailIndex;//RETURN USER LOGIN INDEX IF OK
			puts("\nUsted ha ingresado exitosamente. Bienvenido.");
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

void sUser_printUser(sUser User) {
	//PRINTS ALL THE USER DATA
	printf("|%d", User.userID);//ID
	printf("%-2s", "|");
	printf("%-23s", User.email);//EMAIL
	printf("%-2s", "|");
	if(User.isEmpty == 1)	{//STATUS
		printf("%-10s", "ACTIVO");
	}
	else
	{
		if(User.isEmpty == -1)
			printf("%-10s", "ELIMINADO");
	}
	printf("%s", "|\n");
}

int sUser_listUsers(sUser userList[], int len, int status1, int status2) {
	int rtn = 0;
	int i;

	puts("\n\t> LISTADO DE USUARIOS");
	puts("+----+------------------------+-----------+");
	printf("| %1s%2s%14s%11s%8s%4s\n", "ID", "|", "EMAIL", "|", "ESTADO", "|");
	puts("+----+------------------------+-----------+");

	if (userList != NULL)
	{
		if (len > 0)
		{
			for (i = 0; i < len; i++)//LOOP OVER THE ARRAY AND PRINTS USERS WITH STATUS GIVEN
			{
				if (userList[i].isEmpty == status1 || userList[i].isEmpty == status2)
				{
					sUser_printUser(userList[i]);
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
	puts("+----+------------------------+-----------+\n");

	return rtn;
}


int sUser_deleteUser(sUser userList[], int len) {
	int rtn = 0;
	int idToCancel;
	int indexToCancel;

	if(userList != NULL)
	{
		if(len > 0)
		{
			sUser_listUsers(userList, len, ACTIVE, ACTIVE);//LISTS ALL THE USERS WITH STATUS 'ACTIVE'
			getInt("Ingrese el ID del usuario que desea dar de baja del sistema: ", 10, 1000, 3000,
					"\nError, ingrese un ID de la lista: ", &idToCancel);//ASKS FOR USERID TO DELETE

			indexToCancel = sUser_findUserIndexById(userList, len, idToCancel);//FIND USER INDEX

			while(indexToCancel == -1)
			{	//IF DOESN'T FOUND USER INDEX ASKS FOR ANOTHER ID
				getInt("El ID no existe, por favor ingrese un ID de la lista: ", 10, 4000, 5000,
						"\nError, ingrese un ID de la lista: ", &idToCancel);
				indexToCancel = sUser_findUserIndexById(userList, len, idToCancel);
			}
			//ASKS FOR CONFIRMATION
			if(continueOrNot("\nDesea confirmar la baja? (S/N): ", "\nError, ingrese una opcion "
					"valida (S/N): "))
			{
				userList[indexToCancel].isEmpty = -1;//SET STATUS 'DELETED'
				puts("El usuario ha sido dado de baja del sistema.\n");
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

	return rtn;//RETURN 0 - IF OK
}


int sUser_findUserIndexById(sUser userList[], int len, int givenID) {

	int rtn;
	int i;

	if(userList != NULL)//VERIFIES IF THE ARRAY EXISTS
	{
		if(len > 0)//VERIFIES IF ARRAY LENGHT IS LARGER THAN 0
		{
			for (i = 0; i < len; i++)//LOOP OVER THE ARRAY
			{
				//VERIFY IF ID EXISTS AND IF ITS STATE IS NOT "EMPTY "
				if(userList[i].userID == givenID && userList[i].isEmpty != EMPTY)
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

int sUser_findUserIndexByEmail(sUser userList[], int len, char givenEmail[]) {

	int rtn;
	int i;

	if(userList != NULL)//VERIFIES IF THE ARRAY EXISTS
	{
		if(len > 0)//VERIFIES IF ARRAY LENGHT IS LARGER THAN 0
		{
			for (i = 0; i < len; i++)//LOOP OVER THE ARRAY
			{
				//VERIFY IF ID EXISTS AND IF ITS STATE IS NOT "EMPTY "
				if((strcmp(userList[i].email, givenEmail)) == 0 && userList[i].isEmpty != EMPTY)
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

void sUser_hardCodeUserData(sUser userList[]) {
	//HARDCODE FUNCTION
	userList[0].userID = 1000;
	userList[0].isEmpty = 1;
	strcpy(userList[0].email, "admin@gmail.com");
	strcpy(userList[0].password, "admin123");
	userList[0].postalCode = 1824;
	userList[0].type = 1;
	strcpy(userList[0].direction, "BoucharD 833");

	userList[1].userID = 1001;
	userList[1].isEmpty = 1;
	strcpy(userList[1].email, "user@gmail.com");
	strcpy(userList[1].password, "user123");
	userList[1].postalCode = 3240;
	userList[1].type = 2;
	strcpy(userList[1].direction, "Nazar 1523");
}
