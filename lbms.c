/* Library Management System
by Aditi Paul
*/
#include<ctype.h>                 
#include<dos.h>              
#include<time.h>
#include <windows.h>		
#include<stdio.h>            
#include<conio.h>                  
#include <stdlib.h>			 
#include<string.h>                 


#define RETURNTIME 1 	
char BOOKS[][16]={"Mathematics","History","English","French","Fiction","Science"}; 	
void returnfunc(void);		
void welcome(void);			
void login();			
void main_menu();		
void addbooks(void);		
void deletebooks(void);		
void searchbooks(void);		
void issuebooks(void);		
void bookslist(void);		
void exitapplication(void);		
int  getdata();
int  checkid(int);
int t(void);

void issue_book();			

COORD coord = {0, 0}; 		
COORD max_res,cursor_size;
void gotoxy (int x, int y)		
{
        coord.X = x; coord.Y = y;		 
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();		
											
    while (goal > clock());
}
FILE *fp,*ft,*fs;	

int s;
char findbook;

struct meroDate
{
    int mm,dd,yy;
};
struct books
{
    int id;
    char stname[20];
    char name[20];
    char Writer[20];
    int quantity;
    float Amount;
    int bookno;
    char *cat;
    struct meroDate issued;
    struct meroDate duedate;
};
struct books r;
int main()

{
	welcome();
      login();
      getch();
   return 0;

}

void welcome()	
{
	gotoxy(4,6);
	printf("\n Aditi Paul\n");		
	gotoxy(1,10);
	printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
	gotoxy(32,12);
	printf("WELCOME TO LIBRARY MANAGEMENT SYSTEM");
	gotoxy(32,14);
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
	sleep(3);
	system("cls");
	getch();		
	login();
	main_menu();
}
char u[30],p[30];
void login()		
{
	do{
	printf("\n\n\n\t\t\t ENTER THE USERNAME AND PASSWORD\n\n\n\n");
	printf("\n\t\t\tUSERNAME: ");
	scanf("%s",&u);						
	printf("\n\t\t\tPASSWORD: ");
	scanf("%s",&p);
	if((strcmp(u,"admin")==0) && (strcmp(p,"admin")==0))
	{
		printf("\n\n\t\t login successful");
		printf("\n\n\n\t\t\t\t Press any key for main menu.....");
		getch();
		main_menu();
	}
	else
	{
		printf("\n\n\t\tInvalid username and password");
	}
	
	}while("number_of_try");
	
}


void main_menu()
{

    system("cls");
	int i; 
	gotoxy(20,3);
	printf(" MAIN MENU ");
	gotoxy(20,5);
	printf(" 1. Add Books   ");
	gotoxy(20,7);
	printf(" 2. Delete books");
	gotoxy(20,9);
	printf(" 3. Search Books");
	gotoxy(20,11);
	printf(" 4. Issue Books");
	gotoxy(20,13);
	printf(" 5. Book list");
	gotoxy(20,15);
	
	printf(" 6. Exit Application");
	gotoxy(20,18);
	t();
	gotoxy(20,19);
	printf("Enter your choice:");
	switch(getch())
	{
		case '1':
		addbooks();
		break;
	case '2':
		deletebooks();
		break;
		case '3':
		searchbooks();
	    break;
	case '4':
		issuebooks();
	    break;
	    case '5':
		bookslist();
		break;
	    
	    case '6':
	    {
		system("cls");
		delay(3000);
		exit(0);
	    }
	    default:
		{
		gotoxy(10,23);
		printf("\nWrong Entry!!");
		if(getch())
		main_menu();
		}

    }
}
void addbooks(void)    
{
	system("cls");
	int i;			
gotoxy(20,5);
	printf("\tSELECT CATEGOIES");
	gotoxy(20,7);
	printf(" 1. Mathematics");
	gotoxy(20,9);
	printf(" 2. History");
	gotoxy(20,11);
	printf(" 3. English");
	gotoxy(20,13);
	printf(" 4. French");
	gotoxy(20,15);
	printf(" 5. Fiction");
	gotoxy(20,17);
	printf(" 6. Science");
	gotoxy(20,19);
	printf(" 7. Main menu");
	gotoxy(20,21);
	printf("Enter your choice:");
	scanf("%d",&s);
	if(s==7)

	main_menu() ;
	system("cls");
	fp=fopen("Project.txt","wr+");
	if(getdata()==1)
	{
	r.cat=BOOKS[s-1];				
	fseek(fp,0,SEEK_END);			
	fwrite(&r,sizeof(r),1,fp);		
	fclose(fp);
	gotoxy(21,14);
	printf("The record is sucessfully saved");
	gotoxy(21,15);
	printf("Save any more?(Y / N):");
	if(getch()=='n')
	    main_menu();
	else
	    system("cls");
	    addbooks();
	}
}
void deletebooks()   
    system("cls");
    int d;
    char another='y';
    while(another=='y')  	
    {
	system("cls");
	gotoxy(10,5);
	printf("Enter the Book ID to  delete:");
	scanf("%d",&d);
	fp=fopen("Project.txt","wr+");
	rewind(fp);
	while(fread(&r,sizeof(r),1,fp)==1)
	{
	    if(r.id==d)
	    {

		gotoxy(10,7);
		printf("The book record is available");
		gotoxy(10,8);
		printf("Book name is %s",r.name);
		gotoxy(10,9);
		printf("Book No. is %d",r.bookno);
		findbook='t';
	    }
	}
	if(findbook!='t')
	{
	    gotoxy(10,10);
	    printf("No record is found to delete the search");
	    if(getch())
	    main_menu();
	}
	if(findbook=='t' )
	{
	    gotoxy(10,9);
	    printf("Do you want to delete it?(Y/N):");
	    if(getch()=='y')
	    {
		ft=fopen("temp.txt","wr+");   
		rewind(fp);							while(fread(&r,sizeof(r),1,fp)==1)
		{
		    if(r.id!=d)
		    {
			fseek(ft,0,SEEK_CUR);			
			fwrite(&r,sizeof(r),1,ft); 	  
		    }                              
		}
		fclose(ft);
		fclose(fp);
		remove("Project.txt");
		rename("temp.txt ","Project.txt"); 		
		fp=fopen("Project.txt","wr+");    
		if(findbook=='t')
		{
		    gotoxy(10,10);
		    printf("The record is sucessfully deleted");
		    gotoxy(10,11);
		    printf("Delete another record?(Y/N)");
		}
	    }
	else
	main_menu();
	fflush(stdin);		
	another=getch();
	}
	}
    gotoxy(10,15);
    main_menu();
}
void searchbooks()	    
    system("cls");
    int d;
    gotoxy(20,6);
    printf("Search Books ");
    gotoxy(20,10);
    printf(" 1. Search By ID");
    gotoxy(20,14);
    printf(" 2. Search By Name");
    gotoxy( 15,20);
    printf("Enter Your Choice");
    fp=fopen("Project.txt","wr+"); 		
    rewind(fp);   		
    switch(getch())
    {
	  case '1':
	{
	    system("cls");
	    gotoxy(25,4);
	    printf("Search Books By Id ");
	    gotoxy(20,5);
	    printf("Enter the book id:");
	    scanf("%d",&d);
	    gotoxy(20,7);
	    printf("Searching........");
	    while(fread(&r,sizeof(r),1,fp)==1)
	    {
		if(r.id==d)
		{
		    delay(2);
		    gotoxy(20,7);
		    printf("The Book is available");
		    gotoxy(20,9);
		    printf(" ID:%d",r.id);
		    gotoxy(20,10);
		    printf(" Name:%s",r.name);
		    gotoxy(20,11);
		    printf(" Writer:%s ",r.Writer);
		    gotoxy(20,12);
		    printf(" Qantity:%d ",r.quantity);
		    gotoxy(20,13);
		    printf(" Amount:Rs.%.2f",r.Amount);
		    gotoxy(20,14);
		    printf(" Book No:%d ",r.bookno);
		    
		    findbook='t';
		}

	    }
	    if(findbook!='t')  		
	    {
	   
	    gotoxy(22,9);
		printf("\rNo Record Found");
	    }
	    gotoxy(20,17);
	    printf("Try another search?(Y/N)");
	    if(getch()=='y')
	    searchbooks();
	    else
	    main_menu();
	    break;
	}
	case '2':
	{
	    char s[15];
	    system("cls");
	    gotoxy(25,4);
	    printf("Search Books By Name ");
	    gotoxy(20,5);
	    printf("Enter Book Name:");
	    scanf("%s",s);
	    int d=0;
	    while(fread(&r,sizeof(r),1,fp)==1)
	    {
		if(strcmp(r.name,(s))==0) 		
		{
		    gotoxy(20,7);
		    printf("The Book is available");
		    gotoxy(20,9);
		    printf(" ID:%d",r.id);
		    gotoxy(20,10);
		    printf(" Name:%s",r.name);
		    gotoxy(20,11);
		    printf(" Writer:%s",r.Writer);
		    gotoxy(20,12);
		    printf(" Qantity:%d",r.quantity);
		    gotoxy(20,13);
		    printf(" Amount:Rs.%.2f",r.Amount);
		    gotoxy(20,14);
		    printf(" Book No:%d ",r.bookno);
		   
		    d++;
		}

	    }
	    if(d==0)
	    {
	    
	    gotoxy(22,9);
		printf("\rNo Record Found");
	    }
	    gotoxy(20,17);
	    printf("Try another search?(Y/N)");
	    if(getch()=='y')
	    searchbooks();
	    else
	    main_menu();
	    break;
	}
	default :
	getch();
	searchbooks();
    }
    fclose(fp);
}
void issuebooks(void)  	{
    int t;		

    system("cls");
    gotoxy(10,3);
    printf("   ISSUE SECTION ");
    gotoxy(10,5);
    printf(" 1. Issue a Book");
    gotoxy(10,7);
    printf(" 2. View Issued Book");
    gotoxy(10,9);
    printf(" 3. Search Issued Book");
    gotoxy(10,11);
    printf(" 4. Remove Issued Book");
    gotoxy(10,14);
    printf("Enter a Choice:");
    switch(getch())
    {
	case '1':  //issue book
	{
		system("cls");
		int c=0;
		char another='y';
		while(another=='y')		//infinite loop
		{
			system("cls");
			gotoxy(15,4);
			printf(" Issue Book section ");
			gotoxy(10,6);
			printf("Enter the Book Id:");
			scanf("%d",&t);
			fp=fopen("Project.txt ","wr+");
			fs=fopen("Issue.txt","wr+");
			if(checkid(t)==0)
			{
			     gotoxy(10,8);
			     printf("The book record is available");
			     gotoxy(10,9);
			     printf("There are %d unissued books in library ",r.quantity);
			     gotoxy(10,10);
			     printf("The name of book is %s",r.name);
			     gotoxy(10,11);
			     printf("Enter student name:");
			     scanf("%s",r.stname);
			     gotoxy(10,12);
			     printf("Issued date=%d-%d-%d",r.issued.dd,r.issued.mm,r.issued.yy);				     	     gotoxy(10,13);
			     printf("The BOOK of ID %d is issued",r.id);		
			     r.duedate.dd=r.issued.dd+RETURNTIME;   		
			     r.duedate.mm=r.issued.mm;
			     r.duedate.yy=r.issued.yy;
			     if(r.duedate.dd>30)
			     {
				 r.duedate.mm+=r.duedate.dd/30;
				 r.duedate.dd-=30;

			     }
			     if(r.duedate.mm>12)
			     {
				r.duedate.yy+=r.duedate.mm/12;
				r.duedate.mm-=12;

			     }
			     gotoxy(10,14);
			     printf("To be return:%d-%d-%d",r.duedate.dd,r.duedate.mm,r.duedate.yy);
			     fseek(fs,sizeof(r),SEEK_END);		
			     fwrite(&r,sizeof(r),1,fs);
			     fclose(fs);
			     c=1;
			}
			if(c==0)
			{
			gotoxy(10,11);
			printf("No record found");
			}
			gotoxy(10,15);
			printf("Issue any more(Y/N):");
			fflush(stdin);
			another=getche();
			fclose(fp);
		}

		break;
	}
	case '2':  	
	{
		system("cls");
		int j=4;
		gotoxy(2,1);
		printf("                          Issued book list                               ");
		gotoxy(2,2);
		printf("STUDENT NAME    CATEGORY    ID    BOOK NAME    ISSUED DATE    RETURN DATE");
	       fs=fopen("Issue.txt","wr+");
		while(fread(&r,sizeof(r),1,fs)==1)
		{

			gotoxy(2,j);
			printf("%s",r.stname);
			gotoxy(18,j);
			printf("%s",r.cat);
			gotoxy(30,j);
			printf("%d",r.id);
			gotoxy(36,j);
			printf("%s",r.name);
			gotoxy(51,j);
			printf("%d-%d-%d",r.issued.dd,r.issued.mm,r.issued.yy );
			gotoxy(65,j);
			printf("%d-%d-%d",r.duedate.dd,r.duedate.mm,r.duedate.yy);
			gotoxy(50,25);
			
			j++;

		}
		fclose(fs);
		gotoxy(1,25);
		returnfunc();
	}
	break;
	case '3':   
	{
		system("cls");
		gotoxy(10,6);
		printf("Enter Book ID:");
		int p,c=0;
		char another='y';
		while(another=='y')
		{

			scanf("%d",&p);
			fs=fopen("Issue.txt","wr+");
			while(fread(&r,sizeof(r),1,fs)==1)
			{
				if(r.id==p)
				{
					issue_book();
					gotoxy(10,12);
					printf("Press any key.......");
					getch();
					issue_book();
					c=1;
				}

			}
			fflush(stdin);
			fclose(fs);
			if(c==0)
			{
				gotoxy(10,8);
				printf("No Record Found");
			}
			gotoxy(10,13);
			printf("Try Another Search?(Y/N)");
			another=getch();
		}
	}
	break;
	case '4':  	
	{
		system("cls");
		int b;
		FILE *fg;  	
		char another='y';
		while(another=='y')
		{
			gotoxy(10,5);
			printf("Enter book id to remove:");
			scanf("%d",&b);
			fs=fopen("Issue.txt","wr+");
			while(fread(&r,sizeof(r),1,fs)==1)
			{
				if(r.id==b)
				{
					issue_book();
					findbook='t';
				}
				if(findbook=='t')
				{
					gotoxy(10,12);
					printf("Do You Want to Remove it?(Y/N)");
					if(getch()=='y')
					{
						fg=fopen("record.txt","wr+");
						rewind(fs);
						while(fread(&r,sizeof(r),1,fs)==1)
						{
							if(r.id!=b)
							{
							fseek(fs,0,SEEK_CUR);
							fwrite(&r,sizeof(r),1,fg);
							}
						}
						fclose(fs);
						fclose(fg);
						remove("Issue.txt");
						rename("record.txt","Issue.txt");
						gotoxy(10,14);
						printf("The issued book is removed from list");

				       }

				}
				if(findbook!='t')
				{
					gotoxy(10,15);
					printf("No Record Found");
				}
			}
			gotoxy(10,16);
			printf("Delete any more?(Y/N)");
			another=getch();
		}
	}
	default:
	gotoxy(10,18);
	printf("\nWrong Entry!!");
    getch();
	issuebooks();
	break;
      }
      gotoxy(1,30);
      returnfunc();
}
void bookslist(void)  
{	
    int i=0,j;
    system("cls");
    gotoxy(1,1);
    printf("                              Book List                                   \n");
    gotoxy(2,2);
    printf(" CATEGORY     ID    BOOK NAME     WRITER       QTY     AMOUNT     BOOK NO ");
    j=4;
    fp=fopen("Project.txt","wr+");
    while(fread(&r,sizeof(r),1,fp)==1)
    {
	gotoxy(3,j);
	printf("%s",r.cat);
	gotoxy(16,j);
	printf("%d",r.id);
	gotoxy(22,j);
	printf("%s",r.name);
	gotoxy(36,j);
	printf("%s",r.Writer);
	gotoxy(50,j);
	printf("%d",r.quantity);
	gotoxy(57,j);
	printf("%.2f",r.Amount);
	gotoxy(69,j);
	printf("%d",r.bookno);
	printf("\n\n");
	j++;
	i=i+r.quantity;
      }
      gotoxy(3,25);
      printf("Total Books =%d",i);
      fclose(fp);
      gotoxy(35,25);
      returnfunc();
}
void returnfunc(void)
{
    {
	printf(" Press ENTER to return to main menu");
    }
    r:
    if(getch()==13) 	
    else
    goto r;
}
int getdata()
{
	int t;
	gotoxy(20,3);
	printf("Enter the Information Below");
	gotoxy(21,5);
	printf("Category:");
	gotoxy(31,5);
	printf("%s",BOOKS[s-1]);
	gotoxy(21,6);
	printf("Book ID:\t");
	gotoxy(30,6);
	scanf("%d",&t);
	if(checkid(t) == 0)
	{
		gotoxy(21,13);
		printf("\nThe book id already exists\n");
		getch();
		main_menu();
		return 0;
	}
	r.id=t;
	gotoxy(21,7);
	printf("Book Name:");
	scanf("%s",r.name);
	gotoxy(21,8);
	printf("Writer:");
	scanf("%s",r.Writer);
	gotoxy(21,9);
	printf("Quantity:");
	scanf("%d",&r.quantity);
	gotoxy(21,10);
	printf("Amount:");
	scanf("%f",&r.Amount);
	gotoxy(21,11);
	printf("Book No:");
	scanf("%d",&r.bookno);
	return 1;
}
int checkid(int t)  	
{
	rewind(fp);
	while(fread(&r,sizeof(r),1,fp)==1)		
	if(r.id==t)
	return 0;  		
      return 1; 	
}
int t(void) 	
{
time_t t;
time(&t);
printf("Date and time:%s\n",ctime(&t));

return 0 ;
}

void issue_book()  	
{
		 system("cls");
		 gotoxy(10,8);
		 printf("The Book has taken by Mr. %s",r.stname);
		 gotoxy(10,9);
		 printf("Issued Date:%d-%d-%d",r.issued.dd,r.issued.mm,r.issued.yy);
		 gotoxy(10,10);
		 printf("Returning Date:%d-%d-%d",r.duedate.dd,r.duedate.mm,r.duedate.yy);
}


