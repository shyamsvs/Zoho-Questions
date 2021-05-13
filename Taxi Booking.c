#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>

int alloted(char,int,int);
void book();
void cancel();
void display();
void taxi_detail();

int earnings[5] = {0};
int taxi[5] = {'A','A','A','A','A'};
int book_id = 1000;
int available_time[5] = {0};


struct booking
{
    int booking_id;
    int customer_id;
    char pickup_point;
    char drop_point;
    int pickup_time;
    int drop_time;
    int alloted_taxi;
    int amount;
    struct booking* link;
};
typedef struct booking BOOK;
BOOK *start = NULL,*tptr,*prev,*newnode;


int main()
{
    int choice;
    int flag=1;
    printf(" 1) BOOK\n 2) CANCEL \n 3) DISPLAY \n 4) TAXI DETAILS \n 5)EXIT ");
    while(flag)
    {
        printf("\nENTER YOUR CHOICE \n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1 : book();
                     break;
            /*case 2 : cancel();
                     break;      */
            case 3 : display();
                     break;
            case 4 : taxi_detail();
                     break;
            case 5:  flag = 0;  
                     break;
            default: printf("ENTER VALID CHOICE");
        }

    }
    return 0;
}

void book()
{
    int diff_btween_points;
    char pick;
    newnode = (BOOK*)malloc(sizeof(BOOK));
    newnode->booking_id=book_id++;

    printf("\nENTER THE CUSTOMER ID: ");
    scanf("%d",&newnode->customer_id);//printf("%d",newnode->customer_id);

    printf("\nENTER THE PICKUP POINT: ");
    scanf("%s",&newnode->pickup_point);//printf("%c",newnode->pickup_point);

    printf("\nENTER THE DROP POINT: ");
    scanf("%s",&newnode->drop_point);//printf("%c",newnode->drop_point);

    printf("\nENTER THE PICKUP TIME: ");
    scanf("%d",&newnode->pickup_time);// printf("%d",newnode->pickup_time);

    newnode->drop_time = abs((newnode->drop_point - newnode->pickup_point)) + newnode->pickup_time;

    //printf("DROP TIME %d",newnode->drop_time);

    diff_btween_points = abs(newnode->drop_point - newnode->pickup_point);
    //printf("Difference %d", diff_btween_points);
    pick=newnode->pickup_point;
    newnode->alloted_taxi = alloted(pick,newnode->pickup_time,diff_btween_points);

    taxi[newnode->alloted_taxi] = newnode->drop_point;

    available_time[newnode->alloted_taxi] = newnode->pickup_time + diff_btween_points;

    if(diff_btween_points == 1)
    {
        newnode->amount=200;
        earnings[newnode->alloted_taxi] = earnings[newnode->alloted_taxi]+200;
    }    
    else
    {
        newnode->amount=200 + (150 * (diff_btween_points - 1));
        earnings[newnode->alloted_taxi] = earnings[newnode->alloted_taxi]+200 + (150 * (diff_btween_points - 1));
    }

    newnode->link = NULL;

    if(newnode->alloted_taxi == 0)
        printf("\nNo taxi available\n");
    else
        printf("\nYour booking has been done\n\n Taxi number is %d\n",newnode->alloted_taxi);

    if(start == NULL)
    {
        start = newnode;
    }
    else
    {
        for(tptr=start;tptr->link!=NULL;tptr = tptr->link)
        ;
            tptr->link = newnode;
        
    }
}


int alloted(char pickup_point,int pickuptime,int diff)
{
    int trav , trav1 ,minimum = INT_MAX , taxialloted=0;
    /*for(trav = 1;trav<5; trav++ )
    {
        if(taxi[trav] == pickup_point && available_time[trav] >= pickuptime)
            {
                available_time[trav] = pickuptime + diff;
                return trav;
            }
    }*/

    for(trav = 1;trav<5;trav++)
    {
        if(abs(taxi[trav]-pickup_point)<minimum  && pickuptime>=available_time[trav])
        {
          minimum=abs(taxi[trav]-pickup_point);
          taxialloted=trav;
        }
        else if(abs(taxi[trav]-pickup_point)==minimum)
        {
          if(earnings[taxialloted]>earnings[trav])
            taxialloted=trav; 
        }
    }
    available_time[trav] = pickuptime + diff;
    
    return taxialloted;
}

void display()
{   
    int cid;
    printf("Enter your customer ID :\n");
    scanf("%d",&cid);
   for(tptr=start;tptr;tptr = tptr->link)
        {
            if(tptr->customer_id == cid)
            {
                printf("\nCUSTOMER ID :%d",tptr->customer_id);
                printf("\nPICKUP POINT :%c",tptr->pickup_point);   
                printf("\nDROP POINT :%c",tptr->drop_point);   
                printf("\nPICKUP TIME :%d",tptr->pickup_time);
                printf("\nDROP TIME :%d",tptr->drop_time);
                printf("\nALLOTED TAXI :%d\n",tptr->alloted_taxi);
            }
        }

    
}

void taxi_detail()
{
    int tnum;
    printf("Enter the taxi number :\n");
    scanf("%d",&tnum);
    printf("\nTAXI %d --- Total Earnings :%d",tnum,earnings[tnum]);
    for(tptr=start;tptr;tptr = tptr->link)
    {
            if(tptr->alloted_taxi == tnum)
            {    
                printf("\nBOOKING ID :%d",tptr->booking_id);
                printf("\nCUSTOMER ID :%d",tptr->customer_id);
                printf("\nPICKUP POINT :%c",tptr->pickup_point);   
                printf("\nDROP POINT :%c",tptr->drop_point);   
                printf("\nPICKUP TIME :%d",tptr->pickup_time);
                printf("\nDROP TIME :%d",tptr->drop_time);
                printf("\nEarnings for this trip :%d\n",tptr->amount);
                
            }
    }
}
