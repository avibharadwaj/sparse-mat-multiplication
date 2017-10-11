#include<conio.h>
#include<stdio.h>
#include<malloc.h>
#include<bits/stdc++.h>
#define MAX 100

typedef struct node
{
	struct node *left;
	struct node *up;
	int row,col,val;
}node;

node *mrow1[MAX];
node *ncol1[MAX];

node *mrow2[MAX];
node *ncol2[MAX];

node *crow[MAX];
node *ccol[MAX];

void head_row(int m,int c)
{
	//node *mrow[m];
	for(int i=0;i<m;i++)             /*Initialising head nodes for row*/
	{
	  if(c==1)
	  {
		  mrow1[i]=(node*)malloc(sizeof(node));
		  mrow1[i]->col=0;
		  mrow1[i]->left=mrow1[i];

		  crow[i]=(node*)malloc(sizeof(node));
		  crow[i]->col=0;
		  crow[i]->left=crow[i];
	  }
	  else
	  {
		  mrow2[i]=(node*)malloc(sizeof(node));
		  mrow2[i]->col=0;
		  mrow2[i]->left=mrow2[i];
	  }

	}
}
void head_col(int n,int c)
{
	//node* ncol[n];
	for(int i=0;i<n;i++)		/*Initialising head nodes for column*/
	{
	  if(c==1)
	  {
		  ncol1[i]=(node *)malloc(sizeof(node));
		  ncol1[i]->row=0;
		  ncol1[i]->up=ncol1[i];
	  }
	  else
	  {
		  ncol2[i]=(node *)malloc(sizeof(node));
		  ncol2[i]->row=0;
		  ncol2[i]->up=ncol2[i];

		  ccol[i]=(node *)malloc(sizeof(node));
		  ccol[i]->row=0;
		  ccol[i]->up=ccol[i];
	  }

	}
}
void create(/*int m,int n,*/int cc)		      /*creating nodes for non-zero elements*/
{
	int r,c,v,x;
	node *temp1,*temp2,*p;


	printf("Enter the number of non-zero elements\n");
	scanf("%d",&x);
	printf("Enter the row, column and value for the matrix\n");
	while(x>0)
	{
		//printf("x=%d",x);
		scanf("%d %d %d",&r,&c,&v);
		p=(node *)malloc(sizeof(node));
		p->row=r;
		p->col=c;
		p->val=v;

		if(cc==1)
		{
		  temp1=mrow1[r];
		}
		else
		{
		  temp1=mrow2[r];
		}

		if(temp1->left!=temp1)
		{

		   while((p->col) < (temp1->left->col))
		   {
			temp1=temp1->left;
		   }
		   p->left = temp1->left;
		   temp1->left = p;
		}
		else
		{
		   //printf("\nrow empty\n");
		   temp1->left=p;
		   p->left=temp1;
		}
		//printf("next");
		if(cc==1)
		{
		  temp2=ncol1[c];
		}
		else
		{
		  temp2=ncol2[c];
		}

		if(temp2->up!=temp2)
		{
		   while((p->row) < (temp2->up->row))
		   {
			temp2=temp2->up;
		   }
		   p->up = temp2->up;
		   temp2->up = p;
		}
		else
		{
		   //printf("\ncolumn empty\n");
		   temp2->up=p;
		   p->up=temp2;
		}
		x--;
	}
	//printf("calling displ");
	//display(1);

}
void display(int x)
{
  int choice, r, c;
  int y,select=1;
  node *temp1=(node *)malloc(sizeof(node));
  while(select!=0)
  {
    printf("Enter 1 to print a row and 2 to print a column\n");
    scanf("%d",&choice);
    switch(choice)
    {
      case 1:

	printf("Enter the row");
	scanf("%d",&r);
	if(x==1)
	{
		temp1=mrow1[r]->left;
		while(temp1!=mrow1[r])
		{
		  printf("%d ,",temp1->val);
		  temp1=temp1->left;
	  /*scanf("%d",&y);
	  if(y!=1)break;*/
		}
	}
      else if(x==2)
      {
	temp1=mrow2[r]->left;
	while(temp1!=mrow2[r])
	{
	  printf("%d,",temp1->val);
	  temp1=temp1->left;
	}
      }
      else
      {
	temp1=crow[r]->left;
	while(temp1!=crow[r])
	{
	  printf("%d,",temp1->val);
	  temp1=temp1->left;
	}
      }

    break;
    case 2:

      printf("Enter the column");
      scanf("%d",c);

      if(x==1)
      {
	temp1=ncol1[r]->up;
	while(temp1!=ncol1[r])
	{
	  printf("%d ,",temp1->val);
	  temp1=temp1->up;
	  /*scanf("%d",&y);
	  if(y!=1)break;*/
	}
      }
      else if(x==2)
      {
	temp1=ncol2[r]->up;
	while(temp1!=ncol2[r])
	{
	  printf("%d,",temp1->val);
	  temp1=temp1->up;
	}
      }
      else
      {
	temp1=ccol[r]->up;
	while(temp1!=ccol[r])
	{
	  printf("%d,",temp1->val);
	  temp1=temp1->up;
	}
      }

    break;
    default:
      printf("wrong input");
    break;
  }
	printf("Enter 0 to exit display");
	scanf("%d",&select);
}
}
void multiply(int n,int m)
{
	int i,j,sum;
	node *p,*a,*b;

	for(i=1;i<=m;i++)
	{
		for(j=1;j<=n;j++)
		{
			a=mrow1[i]->left;
			b=ncol2[j]->up;
			sum=0;
			   while(a->col!=0 && b->row!=0)
			   {
				if(b->row > a->col)
				{
					b=b->up;
				}
				else if(a->col > b->row)
				{
					a=a->left;
				}
				else
				{
					sum+=(a->val * b->val);
					a=a->left;
					b=b->up;
				}

				if(sum!=0)
				{
					p=(node *)malloc(sizeof(node));
					p->row=i;
					p->col=j;
					p->val=sum;
					p->left = crow[i]->left;
					crow[i]->left = p;
					p->up = ccol[j]->up;
					ccol[j]->up = p;
				}
			   }
		}
	}

}

int main()
{

	printf("Sparse Matrix Multiplication\n");
	int m1,n1,m2,n2;

	printf("Enter the number of rows and columns of matrix A ");
	scanf("%d %d",&m1,&n1);
	head_row(m1,1);
	head_col(n1,1);
	create(1);
	display(1);
	printf("\nEnter the number of rows and columns of matrix B ");
	scanf("%d %d",&m2,&n2);
	head_row(m2,2);
	head_col(n2,2);
	create(2);
	display(2);
	if(n1==m2)
	{
		multiply(n2,m1);
		display(3);
	}
	else
	{
		printf("\nArray multiplication not possible");
	}
	getch();
}
