#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<string.h>
struct list
{
    char name[30];
    int d;
    struct list *next;
};
struct node
{
    char name[30];
    struct node *next;
    struct list *nbor;

};
int getkey(char a[]);
int checkexist(struct node *temp,char a[],char b[],int *sum);
int checkuniq(char a[50][30],int n);
int checkexist1(struct node *temp,char a[]);
int main()
{
    char c[30],a[30],b[30],z[50][30];
    int i,n,key,di,m,sum,op[60],t,k,j,p;
    struct node *city[30],*temp,*tmp;
    struct list *temp2,*tmp2,*tmp3;
    for(i=0;i<30;i++)
    {
        city[i]=NULL;
    }

    //city=(struct node *)malloc(sizeof(struct node )*30);
    //city=NULL;
    //printf("\n Enter the no. of cities: ");
    scanf("%d",&n);
    //printf("\n Enter the names of cities: ");
    for(i=0;i<n;i++)
    {
        scanf("%s",c);
        if(c[0]=='-')
            key=26;
        else
            key=((int)toupper(c[0]))-65;
        if(city[key]!=NULL)
        {
            temp=city[key];
            while(temp->next!=NULL)
                temp=temp->next;
            tmp=(struct node *)malloc(sizeof(struct node));
            strcpy(tmp->name,c);
            temp->nbor=NULL;
            tmp->next=NULL;
            temp->next=tmp;

        }
        else
        {

            city[key]=(struct node *)malloc(sizeof(struct node));
            strcpy(city[key]->name,c);
            city[key]->next=NULL;
            city[key]->nbor=NULL;

        }

    }
    /*printf("\n The cities are: ");
    for(i=0;i<30;i++)
    {
        if(city[i]!=NULL)
        {
            temp=city[i];
            while(temp!=NULL)
            {
                printf("%s ",temp->name);
                temp=temp->next;
            }
        }
    }*/
    /*printf("\n Enter no. of roads: ");
    scanf("%d",&m);
    */
    //printf("\n Enter the no. of routes: ");
    scanf("%d",&m);
    //printf("\n Enter %d routes \n",m);
    for(i=0;i<m;i++)
    {
        //printf("\n Enter city1, city2 and distance: ");
        scanf("%s %s %d",a,b,&di);
        //key=((int)toupper(a[0]))-65;

        if(a[0]=='-')
            key=26;
        else
            key=((int)toupper(a[0]))-65;

        temp=city[key];
        while(temp!=NULL)
        {

            if(strcmp(temp->name,a)==0)
            {

                tmp2=temp->nbor;
                tmp3=tmp2;

                while(tmp2!=NULL)
                {
                    tmp3=tmp2;
                    tmp2=tmp2->next;
                }

                temp2=(struct list *)malloc(sizeof(struct list));
                strcpy(temp2->name,b);

                temp2->d=di;
                temp2->next=NULL;
                if(tmp3!=NULL)
                    tmp3->next=temp2;
                else
                {
                    temp->nbor=temp2;
                }

                break;
            }
            temp=temp->next;
        }


    }
    //printf("\n Enter no of routes planned : ");
    scanf("%d",&t);
    //printf("\n Enter the planned routes ");
    for(i=0;i<t;i++)
    {
        //printf("\n Enter no. of cities: ");
        scanf("%d",&k);
        sum=0;
        for(j=0;j<k;j++)
        {
            //printf("\n enter city: ");
            scanf("%s",z[j]);
        }

        if(k==1)
        {
            key=getkey(z[0]);
            temp=city[key];
            if(checkexist1(temp,z[0]))
            {
                op[i]=0;

            }
            else
                op[i]=-99;
            continue;
        }
        op[i]=-9;
        if(checkuniq(z,k)!=1)
        {
            op[i]=-99;
            continue;
        }

        sum=0;

        for(p=0;p<k-1;p++)
        {

            key=getkey(z[p]);
            temp=city[key];

            op[i]=-9;
            if(checkexist(temp,z[p],z[p+1],&sum)!=1)
            {
                op[i]=-99;
                break;
            }


        }
        if(op[i]!=-99)
            op[i]=sum;
    }
    //printf("\n The ops are :\n ");
    for(i=0;i<t;i++)
    {
        if(op[i]==-99)
            printf("ERROR\n");
        else
            printf("%d\n",op[i]);
    }
    return 0;
}
int checkuniq(char a[50][30],int n)
{
    int i,j;

    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(strcmp(a[i],a[j])==0)
            {

                return 0;
            }

        }

    }

    return 1;
}
int getkey(char a[])
{
    int key;//=((int)toupper(a[0]))-65;
    if(a[0]=='-')
            key=26;
        else
            key=((int)toupper(a[0]))-65;
    return key;
}
int checkexist1(struct node *temp,char a[])
{
    while(temp!=NULL)
    {
        if(strcmp(temp->name,a)==0)
        {
            return 1;
        }
        temp=temp->next;
    }
    return 0;
}
int checkexist(struct node *temp,char a[],char b[],int *sum)
{
    struct node *tmp;
    struct list *temp1;
    if(temp==NULL)
    {
        return 0;
    }
    else
    {
        tmp=temp;
        while(tmp!=NULL)
        {

            if(strcmp(tmp->name,a)==0)
            {
                temp1=tmp->nbor;
                while(temp1!=NULL)
                {
                    if(strcmp(temp1->name,b)==0)
                    {
                        *sum=*sum+temp1->d;

                        return 1;
                    }
                    temp1=temp1->next;
                }
                return 0;
            }
            tmp=tmp->next;
        }
    }
    return 0;
}
