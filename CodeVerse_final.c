#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30

typedef struct MemberDetails 
{
    char USN[15];
    char name[30];
    int sem;
    char Role[20];
    struct MemberDetails *link;
}Member;

typedef struct Date
{
    int day;
    int month;
    int year;
}Date;

typedef struct EventDetails 
{
    char eventName[100];
    Date eventDate;
    struct EventDetails *link;
}Event;

typedef struct ClubDetails 
{
    char clubName[20];
    char description[50];
    Member *memberLink;
    Event *eventLink;
    int memberCount;
    int eventCount;
}Club;

void clubMenu(Club *c);
void addMember(Club *c);
void removeMember(Club *c);
void displayMembers(Club *c);
void addEvent(Club *c);
void deleteEvent(Club *c); 
void displayEvents(Club *c);
void displayClubInformation(Club *c);

void readMemberDetails(Member *new)
{
    printf("Enter USN: ");
    scanf("%s",new->USN);
    printf("Enter Name: ");
    scanf(" %29[^\n]",new->name);
    printf("Enter Semester: ");
    scanf("%d",&new->sem);
    printf("Enter Role: ");
    scanf(" %19[^\n]",new->Role);
}
void readEventDetails(Event *new)
{
    printf("\nEnter event details: ");
    scanf(" %99[^\n]",new->eventName);
    printf("Enter date (DD MM YYYY): ");
    scanf("%d %d %d",&new->eventDate.day,&new->eventDate.month,&new->eventDate.year);
}
Member *getMemberNode()
{
    Member *new=(Member *)malloc(sizeof(Member));
    if(new==NULL)
    {
        printf("Memory allocation failed!\n");
        exit(0);
    }   
    new->link=NULL;
    return new;
}
Event *getEventNode()
{
    Event *new=(Event *)malloc(sizeof(Event));
    if(new==NULL)
    {
        printf("Memory allocation failed!\n");
        exit(0);
    }
    new->link=NULL;
    return new;
}
int main()
{
    int N=0;
    int i,choice;
    Club clubs[MAX];

    printf("\n\nEnter number of clubs: ");
    scanf("%d",&N);

    for(i=0;i<N;i++)
    {
        printf("\nEnter name for Club %d: ",i+1);
        scanf(" %19[^\n]",clubs[i].clubName);

        printf("Enter description: ");
        scanf(" %49[^\n]",clubs[i].description);

        clubs[i].memberLink=NULL;
        clubs[i].eventLink=NULL;
        clubs[i].memberCount=0;
        clubs[i].eventCount=0;
    }

    for(;;)
    {
        printf("\n------- MAIN MENU ------\n");
        for(i=0;i<N;i++)
            printf("%d. %s\n",i+1,clubs[i].clubName);
        printf("%d. Exit\n",N+1);
        printf("Enter choice: ");
        scanf("%d",&choice);

        if(choice == N+1)
            exit(0);

        if(choice>=1 && choice<=N)
            clubMenu(&clubs[choice-1]);
        else
            printf("Invalid choice. Try again.\n\n");
    }
    return 0;
}

void clubMenu(Club *c)
{
    int ch;
    for(;;)
    {
        printf("\n--- %s Club Menu ---\n",c->clubName);
        printf("1. Add Member\n");
        printf("2. Remove Member\n");
        printf("3. Add Event\n");
        printf("4. Delete Event\n");
        printf("5. Display Members\n");
        printf("6. Display Events\n");
        printf("7. Display Club Information\n");
        printf("8. Exit to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1: addMember(c);
                    break;
            case 2: removeMember(c);
                    break;
            case 3: addEvent(c);
                    break;
            case 4: deleteEvent(c);
                    break;
            case 5: displayMembers(c);
                    break;
            case 6: displayEvents(c);
                    break;
            case 7: displayClubInformation(c);
                    break;
            case 8: printf("Exiting to Main Menu...\n\n");
                    return;
            default:printf("Invalid choice. Try again.\n");
        }
    }
}

void addMember(Club *c)
{
    Member *new=getMemberNode();
    readMemberDetails(new);

    if(c->memberLink==NULL)
        c->memberLink=new;
    else
    {
        Member *temp=c->memberLink;
        while(temp->link!=NULL)
            temp=temp->link;
        temp->link=new;
    }
    c->memberCount++;
    printf("Member (%s) added successfully!\n",new->USN);
    return;
}

void removeMember(Club *c)
{
    if(c->memberLink == NULL) 
    {
        printf("No members in this club.\n");
        return;
    }
    
    char USN[15];
    printf("Enter USN to remove: ");
    scanf("%s",USN);

    Member *cur=c->memberLink, *prev=NULL;
    if(strcmp(cur->USN,USN) == 0) // first member is the one to remove.......
    {
        c->memberLink=cur->link;
        printf("Member (%s) removed.\n",cur->USN);
        free(cur);
        c->memberCount--;
        return;
    }

    while(cur!=NULL)
    {
        if(strcmp(cur->USN,USN) == 0)
            break;
        prev=cur;
        cur=cur->link;
    }

    if(cur==NULL)
    {
        printf("Member (%s) not found.\n\n",USN);
        return;
    }

    prev->link=cur->link;
    printf("Member (%s) removed.\n\n",cur->USN);
    free(cur);
    c->memberCount--;
    return;
}

void displayMembers(Club *c)
{
    Member *temp=c->memberLink;
    if(temp==NULL)
    {
        printf("No members in this club.\n\n");
        return;
    }

    printf("\nMembers of %s :\n",c->clubName);
    printf("--------------------------------------------------------------\n");
    printf("%-15s%-30s%-5s%-20s\n","USN","NAME","SEM","ROLE");
    printf("--------------------------------------------------------------\n");

    while(temp!=NULL)
    {
        printf("%-15s%-30s%-5d%-20s\n",temp->USN,temp->name,temp->sem,temp->Role);
        temp=temp->link;
    }
    printf("--------------------------------------------------------------\n");
    printf("Total members: %d\n", c->memberCount);
    return;
}

void addEvent(Club *c)
{
    Event *newEvent=getEventNode();
    readEventDetails(newEvent);

    if(c->eventLink==NULL)
        c->eventLink=newEvent;
    else
    {
        Event *temp=c->eventLink;
        while(temp->link!=NULL)
            temp=temp->link;
        temp->link=newEvent;
    }
    c->eventCount++;
    printf("Event added Successfully!\n");
    return;
}

void deleteEvent(Club *c)
{
    if(c->eventLink==NULL)
    {
        printf("No events to delete.\n\n");
        return;
    }
    
    char name[100];
    printf("Enter event name to delete: ");
    scanf(" %99[^\n]", name);

    Event *cur=c->eventLink,*prev=NULL;

    if(strcmp(cur->eventName,name)==0) // .....
    {
        c->eventLink=cur->link;
        printf("Event (%s) deleted.\n\n",cur->eventName);
        free(cur);
        c->eventCount--;
        return;
    }

    while(cur!=NULL)
    {
        if(strcmp(cur->eventName,name)==0)
            break;
        prev=cur;
        cur=cur->link;
    }

    if(cur==NULL)
    {
        printf("Event (%s) not found.\n\n",name);
        return;
    }

    prev->link=cur->link;
    printf("Event (%s) deleted.\n\n",cur->eventName);
    free(cur);
    c->eventCount--;
    return;
}

void displayEvents(Club *c)
{
    Event *temp=c->eventLink;
    if(temp==NULL)
    {
        printf("No events yet.\n");
        return;
    }

    printf("\nEvents for %s:\n",c->clubName);
    while(temp!=NULL)
    {
        printf("\nDate: %02d-%02d-%04d\nEvent: %s\n",temp->eventDate.day,temp->eventDate.month,temp->eventDate.year,temp->eventName);
        temp=temp->link;
    }
    printf("\nTotal events: %d\n\n", c->eventCount);
    return;
}

void displayClubInformation(Club *c)
{
    displayMembers(c);
    displayEvents(c);
    return;
}
