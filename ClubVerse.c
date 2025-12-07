#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30

int clubCount=0;
int Memcount=0;

typedef struct MemberDetails{
    char USN[15];
    char name[30];
    int sem;
    char Role[20];
    struct MemberDetails *link;
}Member;

typedef struct EventDetails
{
    char info[100];
    int day,month,year;
    struct EventDetails *link;
}Event;

typedef struct ClubDetails{
    char clubName[20];
    char description[50];
    Member *first;
    struct Event *eventHead;
}Club;


void clubMenu(int n,Club clubs[])
{
    int ch=0;
    while(ch!=7)
    {
        printf("\n--- %s Club Menu ---\n",clubs[n].clubName);
        printf("1. Add Member\n2. Remove Member\n3. Display Members\n4. Announce Event\n5. Delete event\n6. Display Club Info\n7. Exit to Main Menu\nEnter choice: ");
        scanf("%d",&ch);

        switch(ch){
            case 1: addMember(n,clubs);
                    break;
            case 2: removeMember(n,clubs);
                    break;
            case 3: displayMembers(n,clubs);
                    break;
            case 4: addEvent(n,clubs);
                    break;
            case 5: deleteEvent(n,clubs);
                    break;
            case 6: displayEventsSorted(n,clubs);
                    break;
        }
    }
}

void addMember(int n,Club clubs[])
{
    Member *new=(Member *)malloc(sizeof(Member));
    new->link=NULL;

    printf("Enter USN: ");
    scanf("%s",new->USN);

    printf("Enter member name: ");
    getchar();
    fgets(new->name,30,stdin);
    new->name[strcspn(new->name,"\n")]=0;

    printf("Enter sem: ");
    scanf("%d",&new->sem);

    printf("Enter Role: ");
    getchar();
    fgets(new->Role,20,stdin);
    new->Role[strcspn(new->Role,"\n")]=0;
    
    if(clubs[n].first==NULL)
    {
        clubs[n].first=new;
    }
    else
    {
        Member *temp=clubs[n].first;
        while(temp->link!=NULL)temp=temp->link;
        temp->link=new;
    }
    printf("Member (%s) added successfully!\n",new->USN);
    Memcount++;
}

void removeMember(int n,Club clubs[])
{
    char USN[15];
    printf("Enter USN to remove: ");
    scanf("%s",USN);

    Member *temp=clubs[n].first,*prev=NULL;
    if(temp==NULL)
    {
        printf("Member (%s) not found.\n",USN);
        return;
    }

    if(strcmp(temp->USN,USN)==0)
    {
        clubs[n].first=temp->link;
        free(temp);
        Memcount--;
        printf("Member (%s) removed.\n",USN);
        return;
    }

    while(temp!=NULL && strcmp(temp->USN,USN)!=0)
    {
        prev=temp;
        temp=temp->link;
    }

    if(temp==NULL)
    {
        printf("Member (%s) not found.\n",USN);
        return;
    }
    prev->link=temp->link;
    free(temp);
    Memcount--;
    printf("Member (%s) removed.\n",USN);
}

void displayMembers(int n,Club clubs[])
{
    Member *temp=clubs[n].first;

    if(temp==NULL){
        printf("No members in this club.\n");
        return;
    }

    printf("\nMembers of %s:\n",clubs[n].clubName);
    printf("--------------------------------------------------------------\n");
    printf("%-15s%-30s%-5s%-20s\n","USN","NAME","SEM","ROLE");
    printf("--------------------------------------------------------------\n");

    while(temp!=NULL){
        printf("%-15s%-30s%-5d%-20s\n",temp->USN,temp->name,temp->sem,temp->Role);
        temp=temp->link;
    }
    printf("--------------------------------------------------------------\nTotal members: %d\n",Memcount);
}

void addEvent(int n,Club clubs[])
{
    Event *newEvent=(Event *)malloc(sizeof(Event));
    printf("Enter event details: ");
    getchar();
    fgets(newEvent->info,100,stdin);

    newEvent->info[strcspn(newEvent->info,"\n")]=0;
    printf("Enter date (DD MM YYYY): ");
    scanf("%d %d %d",&newEvent->day,&newEvent->month,&newEvent->year);

    newEvent->link=NULL;

    if(clubs[n].eventHead==NULL)
    {
        clubs[n].eventHead=newEvent;
    }else
    {
        Event *temp=clubs[n].eventHead;
        while(temp->link!=NULL)
            temp=temp->link;
        temp->link=newEvent;
    }
    printf("Event added!\n");
}

void deleteEvent(int n,Club clubs[])
{
    if(clubs[n].eventHead==NULL){
        printf("No events to delete.\n");
        return;
    }
    char name[100];
    printf("Enter event name to delete: ");
    getchar();
    fgets(name,100,stdin);
    name[strcspn(name,"\n")]=0;

    Event *temp=clubs[n].eventHead,*prev=NULL;
    while(temp!=NULL)
    {
        if(strcmp(temp->info,name)==0)
        {
            if(prev==NULL)
                clubs[n].eventHead=temp->link;
            else 
                prev->link=temp->link;
            free(temp);
            printf("Event deleted.\n");
            return;
        }
        prev=temp;
        temp=temp->link;
    }
    printf("Event not found.\n");
}

void sortEvents(Event *head)
{
    if (head == NULL || head->link == NULL) 
    {
        printf("No events\n");
        return;
    }

    Event *i = head;
    while (i != NULL)
    {
        Event *j = i->link;
        while (j != NULL)
        {
            if (i->year > j->year ||
               (i->year == j->year && i->month > j->month) ||
               (i->year == j->year && i->month == j->month && i->day > j->day))
            {
                // swap event details
                char even[100];
                int dd = i->day, mm = i->month, yy = i->year;

                strcpy(even, i->info);
                strcpy(i->info, j->info);
                i->day = j->day;
                i->month = j->month;
                i->year = j->year;

                strcpy(j->info, even);
                j->day = dd;
                j->month = mm;
                j->year = yy;
            }
            j = j->link;
        }
        i = i->link;
    }
}


void displayEventsSorted(int n,Club clubs[])
{
    struct Event *head=clubs[n].eventHead;
    if(head==NULL){
        printf("No events yet.\n");
        return;
    }
    sortEvents(head);

    Event *temp=head;
    printf("\nEvents for %s:\n",clubs[n].clubName);

    while(temp!=NULL){
        printf("\nDate: %02d-%02d-%04d\nEvent: %s\n",temp->day,temp->month,temp->year,temp->info);
        temp=temp->link;
    }
}

int main()
{
    Club clubs[MAX];
    printf("Enter number of clubs: ");
    scanf("%d",&clubCount);
    getchar();

    for(int i=0;i<clubCount;i++)
    {
        printf("\nEnter name for Club %d: ",i+1);
        fgets(clubs[i].clubName,20,stdin);
        clubs[i].clubName[strcspn(clubs[i].clubName,"\n")]=0;

        printf("Enter description: ");
        fgets(clubs[i].description,50,stdin);
        clubs[i].description[strcspn(clubs[i].description,"\n")]=0;

        clubs[i].first=NULL;
        clubs[i].eventHead=NULL;
    }

    int choice=0;
    while(choice!=clubCount+1)
    {
        printf("\n------- MAIN MENU ------\n");
        for(int i=0;i<clubCount;i++)
            printf("%d. %s\n",i+1,clubs[i].clubName);
            
        printf("%d. Exit\nEnter choice: ",clubCount+1);
        scanf("%d",&choice);
        
        if(choice>=1&&choice<=clubCount)
            clubMenu(choice-1,clubs);
    }
    return 0;
}