#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
struct prkng_slot//declaring parking slot
{
    char s_nm;
    char car_num[40];
    char enter_time[100];
    int status;//1 means vacant 0 means occupied
    struct prkng_slot *next;
}*head=NULL,*temp=NULL;
int i=0;
void make_prkng_slot(char nm,int s)//make a new parking slot
{
    struct prkng_slot *p_slot;//add new slot
p_slot=(struct prkng_slot*)malloc(sizeof(struct prkng_slot));
p_slot->s_nm=nm;
p_slot->status=s;
if(head==NULL)
{
    head=p_slot;
    temp=p_slot;
    temp->next=NULL;
}
else
{
 temp->next=p_slot;
 temp=p_slot;
 temp->next=NULL;
}
}
void create_slots(int n)//generate parking slots
{
    int i=1;static char nm='A';
    for(i=1;i<=n;i++)
        make_prkng_slot(nm++,1);
}

void parking_status()
{
    struct prkng_slot *ptr=head;
    while(ptr)
    {
        if(ptr->status==1)
        {
            gotoxy(16,i+=2);
         printf("%c\tEMPTY\t",ptr->s_nm);
         delay(500);
        }

        else
        {gotoxy(16,i+=2);
        printf("%c\tFILL\t",ptr->s_nm);
        delay(500);
        }
        ptr=ptr->next;
    }
}

void fill_parking(char car_no[],char time[])
{
    struct prkng_slot *p=head;
    while(p->status!=1)
    {
        p=p->next;
    }
    strcpy(p->car_num,car_no);
    strcpy(p->enter_time,time);
    p->status=0;
}

void car_details()
{
    struct prkng_slot *ptr=head;
    while(ptr)
    {
        if(ptr->status==0){
            gotoxy(16,i+=2);
        printf("%c",ptr->s_nm);
        delay(500);
        gotoxy(16,i+=2);
        printf("%s",ptr->car_num);
        delay(500);
        gotoxy(16,i+=2);
        printf("%s",ptr->enter_time);
        gotoxy(16,i+=2);
        ptr=ptr->next;}
    }
}

void append(int x)
{
    struct prkng_slot *temp;
    int i;
    for(i=0;i<x;i++)
    {
    temp=(struct prkng_slot*)malloc(sizeof(struct prkng_slot));
    temp->status=1;
    temp->next=NULL;
    struct prkng_slot *p=head;
    while(p->next)
    {
        p=p->next;
    }
    p->next=temp;
    temp->s_nm=p->s_nm+1;
    }
}

void fair(char ent[],char ext[])
{
    int i=0,t;
    while(1)
    {
        if(ent[i++]==':')
        break;
    }
    t= (((int)ext[i-2]*10 + (int)ext[i-1]) - ((int)ent[i-2]*10 + (int)ent[i-1]))/10;
    if(t<=3){
            gotoxy(16,i+=2);
        printf("fair is:%d",20);
           delay(500);
    }
    else{
            gotoxy(16,i+=2);
        printf("fair is:%d",20+(t-3)*5);
        delay(500);
    }
    return ;
}

void exit_parking(char c)
{
    struct prkng_slot *p=head;
    time_t t=time(NULL);
    char ex[50];
    strcpy(ex,ctime(&t));
    while(p)
    {
        if(p->status==0)
        {
            if(p->s_nm==c)
            {
                p->status=1;
                gotoxy(16,i+=2);
                printf("car no:%s\tentry time:%s\texit time=%s",p->car_num,p->enter_time,ex);
                strcpy(p->car_num,"NULL");
                strcpy(p->enter_time,"NULL");
                 fair(p->enter_time,ex);
                break;
            }
        }
        p=p->next;
    }

}
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds =  number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds)
        ;
}
void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void start()
{
    gotoxy(16,i);
    SetColor(19);
    printf("\xDB2\xDB2\xDB2\xDB2\xDB2\xDB2\xDB2\xDB2\xDB2\xDB2\xDB2\xDB2\xDB2B2PARKING MANAGEMENT SYSTEM\xDB2\xDB2\xDB2\xDB2\xDB2\xDB2\xDB2\xDB2\xDB2\xDB2\xDB2");
    gotoxy(16,i+=2);
    printf("=============================================");
    SetColor(8);
    gotoxy(16,i+=2);
    delay(1200);
    printf("    INSTRUCTIONS ARE AS FOLLOWS               ");
    gotoxy(16,i);
    delay(1000);
    printf("             CHECK:                ");
    delay(1000);
    gotoxy(16,i+=2);
    printf("\xB10 Please check the height of the car before parking");

    delay(1000);
    gotoxy(16,i+=2);
    printf("\xB10 Please check the compatibility of car width");

    delay(1000);
    gotoxy(16,i+=2);
    printf("\xB10 Please check the car weight and platform carrying capacity.");
    delay(1000);
    gotoxy(16,i+=2);
    printf("\xB10 Only driver is allowed in the car while parking.");
    SetColor(67);
    delay(1000);
    gotoxy(16,i+=2);
    printf("=============================================");
}
void SetColor(int ForgC)//TO SET THE COLOUR OF THE TEXT IN THE CONSOLE WINDOW
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
}
void main()
{
    start();
    delay(1000);
    gotoxy(16,i+=2);
    printf("\xB10 1.Create Parking");
    delay(1000);
    gotoxy(16,i+=2);
    printf("\xB10 2.Parking Status");
    delay(1000);
    gotoxy(16,i+=2);
    printf("\xB10 3.Park Car");
    delay(1000);
    gotoxy(16,i+=2);
    printf("\xB10 4.Details");
    delay(1000);
    gotoxy(16,i+=2);
    printf("\xB10 5.Append");
    delay(1000);
    gotoxy(16,i+=2);
    printf("\xB10 6.Exit");
    delay(1000);

    while(1)
    {
        int ch;
         gotoxy(16,i+=2);
    printf("YOUR CHOICE : ");
    delay(800);
        scanf("%d",&ch);
        switch(ch)
        {
        case 1:
            {
                int n;
                gotoxy(16,i+=2);
                printf("enter size of parking:");
                delay(500);
                scanf("%d",&n);
                 create_slots(n);
                 break;
            }
        case 2:
            parking_status();
            break;
        case 3:
            {
                char car_no[40];
                gotoxy(16,i+=2);
                printf("enter car no:");
                delay(500);
                scanf("%s",&car_no);
                time_t t=time(NULL);
                char time[100];
                strcpy(time,ctime(&t));
                fill_parking(car_no,time);
                break;
            }
        case 4:
            car_details();
            break;
        case 5:
            {
            int x;
            gotoxy(16,i+=2);
            printf("no to add parking slot:");
            delay(500);
            scanf("%d",&x);
            append(x);
            break;
            }
        case 6:
            {
                 char c;
                 gotoxy(16,i+=2);
                 printf("enter parking slot:");
                 scanf("%c",&c);
                 exit_parking(toupper(c));
                 break;
            }
        case 7:
            exit(0);
        }

    }
}









