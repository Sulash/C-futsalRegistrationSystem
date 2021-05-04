#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
FILE *f1,*f2;

typedef struct{
	int id;
	char name[30];
	char phoneNum[10];
	char date[11];
	char time[10];
}bookersDetail;


void showReservation(){
	bookersDetail bd;
	f1=NULL;
	f1=fopen("bookedDetail.txt","r");
	if(f1==NULL){
		printf("Error");
		exit(0);
	}
	printf("Id\tName\tPhone Num\tDate    \tTime\n");
	fflush(stdin);
	while(fscanf(f1,"%d %s %s %s %s",&bd.id,bd.name,bd.phoneNum,bd.date,bd.time)!=EOF){
		printf("%d\t%s\t%s\t%s\t%s\n",bd.id,bd.name,bd.phoneNum,bd.date,bd.time);
	}
	printf("Press any key to continue...");
	getch();
	fclose(f1); //closing file
	f1=NULL; //clearing space 
}

void showPricing(){
		printf(" ------------Details Of Pricing---------------\n");
		printf(" =============================================\n");
		printf(" 1 . Morning __________________________Rs 1200\n");
		printf(" 2 . Afternoon ________________________Rs 1500\n");
		printf(" 3 . Evening __________________________Rs 1800\n");
		printf("\n============================================\n");
					
}

void addReservation(){
	bookersDetail bd,bd1;//structure variable 
	bd.id=0;//default value of id.
	int flag=0;
	
	//writing file
	f1=fopen("bookedDetail.txt","a+");
	if(f1==NULL){							//
		fclose(f1);							// ERROR HANDLING
		f1=fopen("bookedDetail.txt","w+");  //
	}
		
	//fetching id from the database
	while(fscanf(f1,"%d %s %s %s %s",&bd.id,bd.name,bd.phoneNum,bd.date,bd.time)!=EOF){
		//printf("%d\t",bd.id);  //displaying value
	}
	bd.id++;
	
	
	//asking user for data
	fflush(stdin);
	printf("Enter your name:");
	scanf("%[^\n]",bd.name);
	printf("Enter your phone number:");
	scanf("%d",&bd.phoneNum);
	fflush(stdin);
	printf("Enter date you want to book:(dd/mm/yyyy):");
	scanf("%s",bd.date);
	printf("Date:%s\n",bd.date);
	showPricing();
	printf("From above choose one time(morning/afternoon/evening):");
	fflush(stdin);
	scanf("%s",&bd.time);
	
	f2=fopen("bookedDetail.txt","r");

	//verifying the reservation
	while(fscanf(f2,"%d %s %s %s %s",&bd1.id,bd1.name,bd1.phoneNum,bd1.date,bd1.time)!=EOF){
		int a = strcmp(bd.date,bd1.date); 
		int b = strcmp(bd.time,bd1.time);
		if(a==0 && b==0 ){
			printf("Reservation is already full.\n");
			printf("Please select another time or date.");
			flag=1;
		}
	}
	fclose(f2);
	
	if(flag!=1){
		//updating user data to the database(.txt);
		fprintf(f1,"%d %s %s %s %s\n",bd.id,bd.name,bd.phoneNum,bd.date,bd.time);
		printf("Your information detail:\n");
		printf("---------------------------\n");
		printf("id:%d\n",bd.id);  
		printf("Name:%s\n",bd.name);
		printf("Phone:%d\n",bd.phoneNum);
		printf("Date:%s\n",bd.date);
		printf("Time:%s\n",bd.time);
		printf("---------------------------");
		printf("\nSuccessfully added data.");
	}
	fclose(f1);
	f1=NULL;

	printf("\nPress any key to go to menu..");
	getch();	
}


void cancelReservation(){
	int deleteRecordId;
	bookersDetail bd;
	showReservation();
	printf("------------------------------");
	printf("\nEnter an id to delete a record:");//input record id from user to delete
	scanf("%d",&deleteRecordId);
	
	f1=fopen("bookedDetail.txt","r");    //opening in read format
	if(f1==NULL){
		printf("Error file not found");
		exit(0);
	}
	f2=fopen("temp.txt","w");   //opening in write format
	if(f2==NULL){
		printf("Error file not made");
		exit(0);
	}
	
	//reading records from the file and applying logic
	while(fscanf(f1,"%d %s %s %s %s",&bd.id,bd.name,bd.phoneNum,bd.date,bd.time)!=EOF){
		if(bd.id==deleteRecordId){
			printf("Successfully deleted...\n");
			continue;  //bypass the code
		}
		fprintf(f2,"%d\t%s\t%s\t%s\t%s\n",bd.id,bd.name,bd.phoneNum,bd.date,bd.time);
	}
	fclose(f1);
	fclose(f2);
	int a=remove("bookedDetail.txt");  //remove the bookersDetail file and return integer type data if 1 then deleted
	int b=rename("temp.txt","bookedDetail.txt");  //same as above line 120
	printf("Press any key to continue..");
	getch();
}

int main()
{
	int c; //variable for switch
	printf("\n               Futsal Reservation Chart\n");
	printf(" =========================================================\n");
	printf("||             1 . Reservation                            ||\n");
	printf("||             2 . Show of Reservation                    ||\n");
	printf("||             3 . Cancel reservation                     ||\n");
	printf("||             4 . Exit                                   ||\n");
	printf(" =========================================================\n");
	printf("Enter your option: ");
	scanf("%d",&c);
	switch(c)
	{
		case 1:
			{
				system("cls");	
				addReservation();
				system("cls");	
				main(); //re-call main function.
				break;
			}
				
			case 2:
				{
					system("cls");
					showReservation();
					system("cls");
					main(); //re-call main function.
					break;
				}
		case 3:
			{
				system("cls");
				cancelReservation();
				system("cls");
				main(); //re-call main function.
				break;
			}
			case 4:
				exit (0);
			default :
				{
					printf("....Oops.. Yours choice is invalid. Please try again!!!");
					printf("\nPress any key to continue...");
					getch();
					system("cls");
					main(); //re-call main function.
				}
	}
	getch();
}
