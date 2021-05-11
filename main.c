#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
FILE *fl;

/* creating the data structure */
typedef struct data{
	char name[41];
	char number[14]; /* xx-xxxxx-xxxx */
	int day;
	int month;
	struct data* next;
};

typedef struct data Contact;

/* this variable will be used in the future funtions */
Contact* first;

Contact* CreateNode(){
	
	
	Contact* x = (Contact*)malloc(sizeof(Contact));
	if(x != NULL){
		return x;
	}else{
		return NULL;
	}
}

//pronto
void InsertContact(){

	
	fl = fopen("Agenda.txt", "a");
	if(fl == NULL){
		
		printf("\nError opening the file.\n");
		exit(1);
	}
	
	Contact* x;
	
	printf("\n-------------Add contact-------------\n\n");
	
	x = (Contact*)malloc(sizeof(Contact));
	if(x == NULL){
		
		printf("\Error: not possible to allocate memory.\n");
		exit(1);
	}
	
	fflush(stdin);
	printf("Name: ");
	scanf("%s",&x -> name);
	
	printf("Number ( please follow this format: xx-xxxxx-xxxx ): ");
	scanf("%s",&x -> number);
	
	fflush(stdin);
	printf("Birthday:");
	scanf("%d",&x -> day);
	
	fflush(stdin);
	printf("Month of birthday:");
	scanf("%d",&x -> month);
	
	fprintf(fl, "%s\t%s\t%d %d\n", x -> name, x -> number, x -> day, x -> month);
	
	printf("\nContat added successfully!\n\n-------------------------------------------\n");
	
	printf("\n\n");
	
	fclose(fl);
	free(x);
}

//pronto
void RemoveContact(){
	
	char var1[41];
	char cmp[41];
	char var2[14]; 
	int var3;
	int var4;
	int i = 0;
	int count;
	int aux = 0;
	
	fl = fopen("Agenda.txt", "r");
	
	printf("\n\n-----------------Removing contacts-----------------\n\n");
	
	printf("Which contact shoud be removed?\nContact: ");
	scanf("%s",&cmp);
	
	//counts how many rows are there
	while((fscanf(fl,"%s %s %d %d", &var1, &var2, &var3, &var4)) != EOF){
			i++;
	}
	
	fclose(fl);
	
	fl = fopen("Agenda.txt", "r");
	
	Contact* x;
	Contact* y;
	
	if( i > 0){
		
		for( count = 0; count < i; count++){
						
			if(count == 0){
				
				x = CreateNode();
			
				fscanf(fl,"%s %s %d %d", &x->name, &x->number, &x->day, &x->month);
				//printf("%s %s %d %d\n", x->name, x->number, x->day, x->monthz);
				
				first = x;
				y = x;
				y->next = x;
			}
			
			if((count > 0) && (count < i-1)){
				
				x = CreateNode();
				fscanf(fl,"%s %s %d %d", &x->name, &x->number, &x->day, &x->month);
				
				y->next = x;
				
				y = x;
				
				//printf("%s %s %d %d\n", x->name, x->number, x->day, x->month);
					
			}
			if(count == i-1){
				x = CreateNode();
				
				y->next = x;
				
				fscanf(fl,"%s %s %d %d", &x->name, &x->number, &x->day, &x->month);
				
				//printf("%s %s %d %d\n", x->name, x->number, x->day, x->month);
				
				x->next =NULL;
				
			}
				
		}
		
		fclose(fl);
		
	}else{ 
		printf("\n\nThe contact list is empty.\n\n");
	}
	
	fl = fopen("Agenda.txt","w");
	
	x = first;
			
		while(x != NULL){
			if(strcmp(cmp,x->name) != 0){
			fprintf(fl,"%s %s %d %d\n", x->name, x->number, x->day, x->month);
			x = x->next;
			}else{
			x = x->next;
			aux ++;
			
			printf("\nContact removed successfully!");
			}
			
		}
		if(aux == 0){
			printf("\n\nThere is no %s in the contact list.\n\n", cmp);
		}
		x =first;
		
		for(count = 0; count < i; count++){
			
			x = x->next;
			
			free(first);

			first = x;
		}
		
		printf("\n\n----------------------------------------------------\n\n");

	fclose(fl);	
}

//pronto
void SearchName(){
	
	char cmp[41], name[41], number[14];
	int day, month, count, i = 0, aux = 0;
	
	fl = fopen("Agenda.txt","a");
	
	printf("\n\n-----------------Finding Contacts-----------------\n\n");
	printf("OBS: Upper and lower cases are read as different letters.\n\n");
	
	printf("Contact");
	scanf("%s",cmp);
	
	while(fscanf(fl, "%s %s %d %d",&name, &number,&day, &month) != EOF){
		i++;		
	}
	
	fclose(fl);
	
	fl = fopen("Agenda.txt","r");
	
	for(count = 0; count < i; count++){
		
		fscanf(fl,"%s %s %d %d",&name, &number, &day, &month);
		
		if(strcmp(cmp, name) == 0){
			printf("\nName: %s\nNumber: %s\nBirthday: %d / %d \n\n", name, number, day, month);
		}else{
			aux++;
			if(aux == i){
				printf("\nThere is no %s \n", cmp);
			}
		}
	}
	
	printf("\n\n------------------------------------------------------\n\n");
	
	fclose(fl);
	
}

//pronto
void ListContacts(){
	
	char cmp[41], name[41], number[14];
	int day, month, i = 0, count;
	
	fl = fopen("Agenda.txt","r");
	printf("----------------- Contacts-----------------\n\n");
	while(fscanf(fl, "%s %s %d %d",&name, &number, &day, &month) != EOF){
			printf("Name: %s\nNumber: %s\nBirthday: %d / %d \n\n", name, number, day, month);
		i++;		
	}
	
	printf("\n----------------------------------------------------\n\n");
	
	fclose(fl);
		
}

//pronto
void SearchForLetter(){
	
	
	char cmp, aux, name[41], number[14];
	int day, month, i = 0, count = 0, aux1 = 0;
	
	fl = fopen("Agenda.txt", "r");
	
	while(fscanf(fl,"%s %s %d %d",&name, &number, &day, &month) != EOF){
		
		i++;
		
	}
	
	fclose(fl);
	
	printf("\n\n-----------------Looking for letter-----------------\n\n");
	printf("OBS: Upper and lower cases are read as different letters.\n\n");
	printf("Search for letters\nLetter: ");
	fflush(stdin);
	scanf("%c",&cmp);
	
	fl = fopen("Agenda.txt", "r");
	
	printf("\n");
	for( count = 0; count < i; count++){
		
		
		fscanf(fl,"%s %s %d %d",&name, &number, &day, &month);
		aux = name[0];
		
		if(cmp == aux){
			printf("\nName: %s\nNumber %s\nBirthday: %d / %d\n", name, number, day, month);
		}else{
			aux1++;
		}if(aux1 == i){
			printf("There is no contact that starts with the letter: %c", cmp);
		}
	
	}
	printf("\n\n------------------------------------------------------\n\n");
	printf("\n\n");
	
	fclose(fl);
}


//pronto
void PrintBirthdayOfTheMonth(){
	
char  aux, name[41], number[14];
	int cmp, day, month, i = 0, count = 0, aux1 = 0;
	
	fl = fopen("Agenda.txt", "r");
		
	while(fscanf(fl,"%s %s %d %d",&name, &number, &day, &month) != EOF){
		i++;	
	}
	
	fclose(fl);
	
	printf("\n\n-----------------Birthday of the Month-----------------\n\n");
	printf("Month: ");
	fflush(stdin);
	scanf("%d",&cmp);
	
	
	fl = fopen("Agenda.txt", "r");
	
	for( count = 0; count < i; count++){
		
		fscanf(fl,"%s %s %d %d",&name, &number, &day, &month);
		
		if(cmp == month){
			printf("\nName: %s\nNumber %s\nBirthday: %d / %d\n", name, number, day, month);
		}else{
			aux1++;
		}if(aux1 == i){
			printf("There is no birthday in: %d\n", cmp);
		}
	}
	
	printf("\n\n-------------------------------------------------------\n\n\n\n");

	fclose(fl);
	
}


int main(){
	
	setlocale(LC_ALL, "Portuguese");
	
	bool key = true;
	int menu = 0, aux;
	
	
	while(key){
		
		printf("[1] Insert contact\n");
		printf("[2] Remove contact\n");
		printf("[3] Search name\n");
		printf("[4] List contacts\n");
		printf("[5] Search for letter\n");
		printf("[6] Birthday of the month\n");
		printf("[7] Exit \n\nChoice: ");
		fflush(stdin);
		scanf("%d",&menu);
		printf("\n\n");
			
			if((menu != 1) && (menu != 2) && (menu != 3) &&(menu != 4) && (menu != 5) &&(menu != 6) &&(menu != 7)){
			menu = 8;
		}
		switch(menu){
			case 1:InsertContact();					
				break;
			case 2: RemoveContact();
				break;
			case 3:SearchName();
				break;
			case 4:ListContacts();
				break;
			case 5:SearchForLetter();
				break;
			case 6:PrintBirthdayOfTheMonth();
				break;
			case 7:printf("Closing...\n");
				key = false;
				break;
			case 8: printf("\n\nInvalid data, choose one of the above\nPress enter to continue\n\n");
				getch();
				break;		
		}	
	}
	return 0;
}
