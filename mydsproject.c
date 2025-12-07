#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct Member {
    char usn[11];
    char name[20];
    struct Member *link;
} Member;

typedef struct Date {
    int day;
    int month;
    int year;
} Date;

typedef struct Club {
    char clubName[20];
    char description[80];
    char eventMsg[80];
    Date eventDate;
    Member *first;
}Club;
int clubcount=0;
Member *get_node()
{
    Member *temp=(Member *)malloc(sizeof(Member));
    if(temp==NULL)
    {
        printf("Memory Allocation Failed");
        exit(0);
    }
    return temp;
}
void read_data(Member *new)
{
    printf("Enter USN : ");
    scanf("%s",new->usn);
    printf("Enter Name : ");
    getchar();
    gets(new->name);
}
void addMember(int n, Club clubs[])
{
    Member *new=get_node();
    new->link=NULL;
    read_data(new);
    if(clubs[n].first==NULL)
    {
        clubs[n].first=new;
        return;
    }
    Member *temp=clubs[n].first;
    while(temp->link!=NULL)temp=temp->link;
    temp->link=new;

}
void removeMember(int n,Club clubs[])
{
    char usn[11];
    printf("Enter USN of the Member you want to remove : ");
    scanf("%s",usn);
    if(clubs[n].first==NULL)
    {
        printf("No Members ");
        return;
    }
    if(clubs[n].first->link==NULL)
    {
       
        if(strcmp(clubs[n].first->usn,usn)==0)
        {
            free(clubs[n].first);
            printf("Member Deleted\n");
            clubs[n].first = NULL; 
        }
        else
        {
            printf("Member not found\n");
        }
        return;
    }
     Member *cur = clubs[n].first;
     Member *prev = NULL;

    if (strcmp(cur->usn, usn) == 0)
    {
        clubs[n].first = cur->link;
        free(cur);
        printf("Member Deleted\n");
        return;
    }
    prev=cur;
    cur=cur->link;
    while(cur!=NULL)
        {
            if(strcmp(cur->usn,usn)==0)
            {
                prev->link=cur->link;
                free(cur);
                printf("Member Deleted\n");
                return;
            }
            prev=cur;
            cur=cur->link;
        }
        printf("Member not found\n");
}
void displayMembers(int n ,Club clubs[])
{
    if(clubs[n].first==NULL)
    {
        printf("No Members\n");
        return;
    }
    printf("\n----Members----\n");
    printf("%-15s %s\n","USN","NAME");
    Member *temp=clubs[n].first;
    while(temp!=NULL)
    {
        printf("%-15s %s\n",temp->usn,temp->name);
        temp=temp->link;
    }

}
void announceEvent(int n,Club clubs[])
{
    if(strcmp(clubs[n].eventMsg,"No events yet.")==0)
    {
        printf("Event date (dd mm yyyy): ");
        scanf("%d %d %d",&clubs[n].eventDate.day,&clubs[n].eventDate.month,&clubs[n].eventDate.year);
        printf("Enter the Event Message: ");
        getchar();
        gets(clubs[n].eventMsg);
        return ;
    }
    printf("Already even annouced! ");
}
void displayClubInfo(int n,Club clubs[])
{
    printf("\n====%s Club====\n",clubs[n].clubName);
    printf("Description: %s\n",clubs[n].description);
    printf("\nEvents:\n Date:%d/%d/%d\nMessage:%s",clubs[n].eventDate.day,clubs[n].eventDate.month,clubs[n].eventDate.year,clubs[n].eventMsg);
}

void clubmenu(Club clubs[],int n)
{
    int ch;
    
        while(1)
        {
            printf("\n----Club Menu ----\n");
            printf("\n--- %s Club Menu ---\n",clubs[n].clubName);
            printf("-----------------------\n");
            printf("1. Add Member\n");
            printf("2. Remove Member\n");
            printf("3. Display Members\n");
            printf("4. Announce Event\n");
            printf("5. Display Club Info\n");
            printf("6. Exit to Main Menu\n");
            printf("Enter choice: ");
            scanf("%d", &ch);
            switch(ch) 
            {
                case 1: addMember(n,clubs); break;
                case 2: removeMember(n,clubs); break;
                case 3: displayMembers(n,clubs); break;
                case 4: announceEvent(n,clubs); break;
                case 5: displayClubInfo(n,clubs); break;
                case 6:return;
            }
        }
    }

int main()
{
    Club clubs[10];
    int ch,n;
    printf("Enter the number of clubs\n");
    scanf("%d",&clubcount);
    for (int i = 0; i < clubcount; i++) {
        printf("\nEnter name for Club %d: ", i+1);
        scanf("%s",clubs[i].clubName);
        printf("Enter description: ");
        getchar();
        gets(clubs[i].description);
        strcpy(clubs[i].eventMsg, "No events yet.");
        clubs[i].eventDate.day = 0;
        clubs[i].eventDate.month = 0;
        clubs[i].eventDate.year = 0;
        clubs[i].first = NULL;
    }
    int i;
  
    while(1)
    {
        printf("\n----Main Menu---\n");
        for(i=0;i<clubcount;i++)
        {
            printf("%d.%s\n",i+1,clubs[i].clubName);
        }
        printf("%d.Exit\n",i+1);
        printf("Enter choice: ");
        scanf("%d", &n);
        if(n==clubcount + 1)
            exit(0);
        clubmenu(clubs,n-1);
    }
}
