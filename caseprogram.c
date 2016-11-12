#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100
#define MIN 0

void add_good();
void pid();	
int login();
void delete_good();
void readinfo();
void ownerfile();
void bfgoodsin();
void billnumber();
void bfgoodsout();
void goodscount();
void supplierslist();
void suppliersinfo();
void supplierstock();
void balancefile();
void suppliersstockinfo(int);
void billing(int,int,int tempid[],int tempno[],int,int);

char itemname[50][30]={"Tea","Oil","Shop","Suger","Salt","Registers","Rice","Toothpaste","Shampoo"};
char suppliers[10][30]={"Supplier1","Supplier2","Supplier3","Supplier4","Supplier5","Supplier6"};
int contactno[6]={900001,900002,900003,900004,900005,900006};
int quantity[50]={25,25,25,25,25,25,25,25,25};
int price[50]={10,50,75,90,25,45,75,95,35};

int tempid[100],tempno[100];
const int maximum=100;
int ac,size,cash,uniquebill,productcount;
FILE *s,*fos,*fsl,*fss[6],*temp,*sb,*ub,*pb;


int main()
{
		int switch_choice,login_value,error_choice;
		login_value=login();
		while(login_value==0)
		{
				printf("\n Would u like to Re-enter Login ? Enter 1 for YES or 0 for NO : \n");
				scanf("%d",&error_choice);
				if(error_choice==0)
				{
						exit(1);
				}
				else
				{
						login_value=login();
				}
		}
		printf("                               Inventory Stock Management                                                     ");
		while(1)
		{
				printf("\n\n");
				printf("  1 : Information of Stock \n  2 : Check In of Item \n  3 : Check Out of Item \n  4 : Add Item to Stock \n");
				printf("  5 : Delete Item from Stock \n  6 : Reset Stock \n  7 : Exit\n");
				printf("\n  Enter your choice : ");
				scanf("%d",&switch_choice);
				switch(switch_choice)
				{
					case 1 :    readinfo();
								break;
					case 2 :	bfgoodsin();
								break;
					case 3 :	bfgoodsout();
								break;	
					case 4 :	add_good();	
								break;
					case 5 : 	delete_good();
								break;
					case 6 :    ownerfile();
								supplierslist();
								supplierstock();
								goodscount();
								balancefile();
								billnumber();
								pid();	
								break;
					case 7 :	exit(1);
								break;
					default :   printf("       Wrong input \n");
				}
		
		}
		return 0;
}


int login()						// Authentication Module 
{
	
		int count=0,flag=0;
		char ch,temperary_id[256],temperary_password[256];
		char original_id[256]="user";
		char original_password[256]="password";
		printf("			*** 	LOGIN		***\n");
		printf("Enter User Id : ");
		scanf("%s",temperary_id);
		printf("Enter Password : ");
		while(1)
		{
				ch=getch();
				if(ch==8&&count>0)
				{
						count--;
						printf("\b \b");
				}
				else
				if(isprint(ch))
				{
						temperary_password[count]=ch;
						count++;
						printf("*");
				}
				else 
				if(ch==13)
				break;
		}
		temperary_password[count]='\0';
		if((strcmp(temperary_id,original_id)==0)&&(strcmp(temperary_password,original_password)==0))
		{
				flag=1;
				printf("\nLogin Successfull \n");
		}
		else
		{
				printf("\nLogin Unsuccessfull \n");
		}
		return flag;
}


void ownerfile()			// Creates File for Owner Stock
{
		int j,i=0;
		fos=fopen("ownerfile.txt","w");
		if(fos==NULL)
		{
				printf("Error in creating a file \n");
		}
		else
		{
				for(i=0;i<9;i++)
				{
						fseek(fos,((80*i)),SEEK_SET);
						fprintf(fos,"  PID : %d",(i+1));
						fseek(fos,((80*i)+16),SEEK_SET);
						fprintf(fos,"  Item : %s",itemname[i]);
						fseek(fos,((80*i)+36),SEEK_SET);
						fprintf(fos,"  Available : %d",quantity[i]);
						fseek(fos,((80*i)+66),SEEK_SET);
						fprintf(fos,"  Price : %d\n",price[i]);
				}
				fclose(fos);
		}
}


void readinfo()			// Display Owner Stock Information
{
		char lines[100],ch;
		fos=fopen("ownerfile.txt","r+");
		s=fopen("arraysize.txt","r+");
		sb=fopen("stockbalance.txt","r+");
		fseek(s,0,SEEK_SET);
		fscanf(s,"%d",&size);
		if(size<=0)
		{
			printf("Empty Stock");
		}
		else
		while((ch=fgetc(fos))!=EOF)
		{
				printf("%c",ch);
		}
		printf("\n  Available Balance : ");
		fscanf(sb,"%d",&cash);
		printf("%d",cash);
		fclose(sb);
		fclose(s);
		fclose(fos);
}


void balancefile()				// File for Stock Balance
{
		cash=50000;
		sb=fopen("stockbalance.txt","w");
		fprintf(sb,"%d",cash);
		fclose(sb);
}


void billnumber()				// File for Bill number
{
		uniquebill=1000;
		ub=fopen("transactionbill.txt","w");
		fprintf(ub,"%d",uniquebill);
		fclose(ub);
}


void pid()							// File for PID
{
		productcount=9;
		pb=fopen("productid.txt","w");
		fprintf(pb,"%d",productcount);
		fclose(pb);
}


void bfgoodsin()		// Supplying  Quantity of Goods to Stock
{
		int i,num,uid,q,flag,temppid,tempprice;
		int ac=0,f,j,k,bytes,sid,ui,e,g,finalprice=0;
		char c,p,lines[100];
		suppliersinfo();
		printf("\nSelect Supplier id : ");
		scanf("%d",&sid);
		while(sid>6||sid<1)				// For Invalid Input
		{
				printf("ERROR : Invalid Supplier Id . Select Id from given Supplier List only ");
				printf("\n Would u like to Re-enter input ? Enter 1 for YES or 0 for NO : \n");
				scanf("%d",&ui);
				if(ui==0)
				{
						exit(1);
				}
				else
				{
						printf("\nSelect Supplier id : ");
						scanf("%d",&sid);
				}
		}
		suppliersstockinfo(sid);
		printf("\nEnter number of items to update : ");
		scanf("%d",&num);
		s=fopen("arraysize.txt","r+");
		fseek(s,0,SEEK_SET);
		fscanf(s,"%d",&size);
		while(num>size||num<1)				// For Invalid Input
		{
				printf("ERROR : Invalid Input : Given Number is out of range of size of Stock ");
				printf("\n Would u like to Re-enter input ? Enter 1 for YES or 0 for NO : \n");
				scanf("%d",&ui);
				if(ui==0)
				{
						exit(1);
				}
				else
				{
						printf("\nEnter number of items to update : ");
						scanf("%d",&num);
				}
		}
		fclose(s);
		for(i=0;i<num;i++)
		{
				printf("Enter PID of Item : ");
				scanf("%d",&uid);
				flag=1;
				k=1;
				fos=fopen("ownerfile.txt","r+");
				s=fopen("arraysize.txt","r+");
				fseek(s,0,SEEK_SET);
				fscanf(s,"%d",&size);
				while((k<=size))
				{
						fseek(fos,((80*(k-1))+7),SEEK_SET);
						fscanf(fos,"%d",&temppid);
						fseek(fos,-8,SEEK_CUR);
						if(temppid!=uid)
						{
								k++;	
						}
						else
						{		
								fseek(fos,((80*(k-1))+76),SEEK_SET);
								fscanf(fos,"%d",&tempprice);
								fseek(fos,-77,SEEK_CUR);
								flag=0;
								k++;
						}
				}
				fclose(fos);
				
				while(flag==1||uid>=10)				// For Invalid Input
				{
						printf("ERROR : Invalid PID ");
						printf("\n Would u like to Re-enter input ? Enter 1 for YES or 0 for NO : \n");
						scanf("%d",&ui);
						if(ui==0)
						{
								exit(1);
						}
						else
						{
								bfgoodsin();
						}
				}
				fclose(s);
				tempid[i]=uid-1;
				printf("Enter quantity of items : ");
				scanf("%d",&q);
				fos=fopen("ownerfile.txt","r+");
				f=fseek(fos,0,SEEK_SET);		//positioning cursor to start of a file	
				k=0;
				if(f!=0)
				{
						printf("Unsuccessfull");
						exit(0);
				}				
				bytes=(80*(uid-1))+36+14;
				f=fseek(fos,bytes,SEEK_SET);
				fscanf(fos,"%d",&k);
				k=k+q;
				while(k>MAX)				// For Invalid Input
				{
						printf("ERROR : stock capacity exceeds ..Cant add googd to Stock");
						printf("\n Would u like to Re-enter input ? Enter 1 for YES or 0 for NO : \n");
						scanf("%d",&ui);
						if(ui==0)
						{
								exit(1);
						}
						else
						{
								k=k-q;
								printf("Enter quantity of items : ");
								scanf("%d",&q);
								k=k+q;
						}
				}
				e=0;
				fss[sid-1]=fopen("supplierstock.txt","r+");
				g=fseek(fss[sid-1],0,SEEK_SET);
				bytes=(80*(uid-1))+36+14;
				g=fseek(fss[sid-1],bytes,SEEK_SET);
				fscanf(fss[sid-1],"%d",&e);
				e=e-q;
				while(e<MIN)				// For Invalid Input
				{
						printf("ERROR : Supplier can not provide given good ..Cant add good to Stock");
						printf("\n Would u like to Re-enter input ? Enter 1 for YES or 0 for NO : \n");
						scanf("%d",&ui);
						if(ui==0)
						{	
								exit(1);
						}
						else
						{
								e=e+q;
								printf("Enter quantity of items : ");
								scanf("%d",&q);
								e=e-q;
						}
				}
				tempno[i]=q;
				
				finalprice=finalprice+(q*tempprice);
				sb=fopen("stockbalance.txt","r+");
				fscanf(sb,"%d",&cash);
				while(finalprice>cash)
				{
						printf("\n  ERROR : Stock Balance is less for this transaction \n");
						printf("\n Would u like to Re-enter input ? Enter 1 for YES or 0 for NO : \n");
						scanf("%d",&ui);
						if(ui==0)
						{
								exit(1);
						}
						else
						{
								bfgoodsin();
						}		
				}
				fclose(sb);
				f=fseek(fos,0,SEEK_SET);
				f=fseek(fos,bytes,SEEK_SET);
				fprintf(fos,"%d",k);
				fclose(fos);
				g=fseek(fss[sid-1],0,SEEK_SET);
				g=fseek(fss[sid-1],bytes,SEEK_SET);
				fprintf(fss[sid-1],"%d",e);
				fclose(fss[sid-1]);
		
		}
		printf("\n Goods in Successfully");
		billing(sid,ac,tempid,tempno,finalprice,num);
}


void bfgoodsout()			// Retriving Goods From Stock
{
		int i,num,uid,q,f,j,k,bytes,ui,finalprice=0,flag,temppid,tempprice;
		char lines[100],c,p;
		ac=1;
		printf("\nEnter number of items to update : ");
		scanf("%d",&num);
		s=fopen("arraysize.txt","r+");
		fseek(s,0,SEEK_SET);
		fscanf(s,"%d",&size);
		while(num>size||num<1)				// For Invalid Input
		{
				printf("ERROR : Invalid Number : Enter Number of the Range (1-%d) ",size);
				printf("\n Would u like to Re-enter input ? Enter 1 for YES or 0 for NO : \n");
				scanf("%d",&ui);
				if(ui==0)
				{
						exit(1);
				}
				else
				{
						printf("\nEnter number of items to update : ");
						scanf("%d",&num);
				}
		}
		fclose(s);
		for(i=0;i<num;i++)
		{
				flag=1;
				s=fopen("arraysize.txt","r+");
				fseek(s,0,SEEK_SET);
				fscanf(s,"%d",&size);
				printf("Enter PID of Item : ");
				scanf("%d",&uid);
					k=1;
					fos=fopen("ownerfile.txt","r+");
				while((k<=size))
				{
						fseek(fos,((80*(k-1))+7),SEEK_SET);
						fscanf(fos,"%d",&temppid);
						fseek(fos,-8,SEEK_CUR);
						if(temppid!=uid)
						{
								k++;	
						}
						else
						{		
								fseek(fos,((80*(k-1))+76),SEEK_SET);
								fscanf(fos,"%d",&tempprice);
								fseek(fos,-77,SEEK_CUR);
								flag=0;
								k++;
						}
				}
				fclose(fos);
				while((flag==1))				// For Invalid Input
				{
						printf("ERROR : Invalid PID ");
						printf("\n Would u like to Re-enter input ? Enter 1 for YES or 0 for NO : \n");
						scanf("%d",&ui);
						if(ui==0)
						{
								exit(1);
						}
						else
						{
								bfgoodsout();
						}
				}
				fclose(s);
				tempid[i]=uid-1;
				printf("Enter quantity of items : ");
				scanf("%d",&q);
				tempno[i]=q;
				
				fos=fopen("ownerfile.txt","r+");
				rewind(fos);				//positioning cursor to start of a file	
				f=fseek(fos,0,SEEK_SET);		//positioning cursor to start of a file	
				k=0;
				if(f!=0)
				{
						printf("Unsuccessfull");
						exit(0);
				}				
				bytes=(80*(uid-1))+36+14;
				f=fseek(fos,bytes,SEEK_SET);
				fscanf(fos,"%d",&k);
				k=k-q;
				while(k<MIN)				// For Invalid Input
				{
						printf("ERROR : stock capacity exceeds ..Cant take good from Stock");
						printf("\n Would u like to Re-enter input ? Enter 1 for YES or 0 for NO : \n");
						scanf("%d",&ui);
						if(ui==0)
						{
								exit(1);
						}
						else
						{
								k=k+q;
								printf("Enter quantity of items : ");
								scanf("%d",&q);
								k=k-q;
						}
				}
				finalprice=finalprice+(q*tempprice);
				f=fseek(fos,0,SEEK_SET);
				f=fseek(fos,bytes,SEEK_SET);
				fprintf(fos,"%d",k);
				fclose(fos);
		}	
		printf("\n Goods Out Successfully\n");
		billing(0,ac,tempid,tempno,finalprice,num);
}


void billing(int sid,int ac,int tempid[],int tempno[],int finalprice,int num)  // Generates bill for Goods in And Goods out
{
		int i,tempprice;
		char name[100],ch;
		const char shop[100]="AIO General Store";
		const char number[100]="9112939020";
		const char ownername[100]="Mr ShopOwner";
		FILE *bfp;
		fos=fopen("ownerfile.txt","r+");
		bfp=fopen("billfile.txt","w");
		printf("\n		***		BILLING		***				\n");
		printf(" %s\t\t\t%s\tContact: %s\n\n",shop,ownername,number);
		if(ac==0)
		{
				printf("Supplier Name : %s		Contact Number : %d\n",suppliers[sid-1],contactno[sid-1]);
				for(i=0;i<num;i++)
				{
						fseek(fos,((80*(tempid[i]))+76),SEEK_SET);
						fscanf(fos,"%d",&tempprice);
						fseek(fos,-77,SEEK_CUR);
						fseek(fos,((80*(tempid[i]))+25),SEEK_SET);
						fscanf(fos,"%s",name);
						fseek(fos,-26,SEEK_CUR);
						fseek(bfp,(i*80),SEEK_SET);
						fprintf(bfp,"\nItem : %s",name);
						fseek(bfp,((i*80)+30),SEEK_SET);
						fprintf(bfp,"Price of Item : %d",tempprice);
						fseek(bfp,((i*80)+60),SEEK_SET);
						fprintf(bfp,"Quantity : %d",tempno[i]);
				}
				fclose(bfp);
				bfp=fopen("billfile.txt","r+");
				while((ch=fgetc(bfp))!=EOF)
				{
					printf("%c",ch);
				}
				fclose(bfp);
				sb=fopen("stockbalance.txt","r+");
				fscanf(sb,"%d",&cash);
				cash=cash-finalprice;
				fseek(sb,0,SEEK_SET);
				fprintf(sb,"%d",cash);
				fclose(sb);
				fclose(fos);
				
		}
		else
		{
				for(i=0;i<num;i++)
				{
						fseek(fos,((80*(tempid[i]))+76),SEEK_SET);
						fscanf(fos,"%d",&tempprice);
						fseek(fos,-77,SEEK_CUR);
						fseek(fos,((80*(tempid[i]))+25),SEEK_SET);
						fscanf(fos,"%s",name);
						fseek(fos,-26,SEEK_CUR);
						fseek(bfp,(i*80),SEEK_SET);
						fprintf(bfp,"\nItem : %s",name);
						fseek(bfp,((i*80)+30),SEEK_SET);
						fprintf(bfp,"Price of Item : %d",tempprice);
						fseek(bfp,((i*80)+60),SEEK_SET);
						fprintf(bfp,"Quantity : %d",tempno[i]);
				}
				fclose(bfp);
				bfp=fopen("billfile.txt","r+");
				fseek(bfp,0,SEEK_SET);
				while((ch=fgetc(bfp))!=EOF)
				{
					printf("%c",ch);
				}
				fclose(bfp);
				sb=fopen("stockbalance.txt","r+");
				fscanf(sb,"%d",&cash);
				cash=cash+finalprice;
				fseek(sb,0,SEEK_SET);
				fprintf(sb,"%d",cash);
				fclose(sb);
				fclose(fos);
		}
		ub=fopen("transactionbill.txt","r+");
		fscanf(ub,"%d",&uniquebill);
		uniquebill++;
		fseek(ub,0,SEEK_SET);
		fprintf(ub,"%d",uniquebill);
		printf("\n\nFinal Amount : %d",finalprice);
		printf("\t\t\t\tBILL Number  : %d",uniquebill);
		fclose(ub);
}


void supplierslist()		// Creates file for Supplier List
{
		fsl=fopen("supplierslist.txt","w");
		int j,i=0;
		if(fsl==NULL)
		{
				printf("Error in creating a file \n");
		}
		else
		{
				for(i=0;i<6;i++)
				{
						fprintf(fsl,"\n  SID : %d",(i+1));
						fprintf(fsl,"  Supplier Name  : %s",suppliers[i]);
						fprintf(fsl,"  Contact Number : %d",contactno[i]);
	
				}
				fclose(fsl);
		}	
}


void suppliersinfo()		// Display information for Supplier List
{
		fsl=fopen("supplierslist.txt","r+");
		char lines[100];
		while(fgets(lines,100,fsl)!=NULL)
		{
				printf("%s",lines);
		}
		fclose(fsl);
}


void supplierstock()		//  Create Stock for Each Supplier
{
	
		int i,j;
		for(i=0;i<6;i++)
		{
				fss[i]=fopen("supplierstock.txt","w");		
				if(fss[i]==NULL)
				{
						printf("Error in creating a file \n");
				}
				else
				{
						for(j=0;j<9;j++)
						{
								fseek(fss[i],((80*j)),SEEK_SET);
								fprintf(fss[i],"  PID : %d",(j+1));
								fseek(fss[i],((80*j)+16),SEEK_SET);
								fprintf(fss[i],"  Item : %s",itemname[j]);
								fseek(fss[i],((80*j)+36),SEEK_SET);
								fprintf(fss[i],"  Available : %d",quantity[j]);
								fseek(fss[i],((80*j)+66),SEEK_SET);
								fprintf(fss[i],"  Price : %d\n",price[j]);
						}
						fclose(fss[i]);
				}
		}
}


void suppliersstockinfo(int sid)	// Display Stock Information of Supplier
{
		printf("Supplier Name : %s			Contact Number : %d\n",suppliers[sid-1],contactno[sid-1]);
		fss[sid-1]=fopen("supplierstock.txt","r+");
		char lines[100],ch;
		while((ch=fgetc(fss[sid-1]))!=EOF)
		{
				printf("%c",ch);
		}
		fclose(fss[sid-1]);
}


void goodscount()					// Create a file for Total numbe of goods in Stock
{
		char ch;
		s=fopen("arraysize.txt","w");
		fprintf(s,"%d",9);
		fclose(s);
}


void add_good()				// Add a New item to Stock
{
		char name[5];
		int q,p;
		s=fopen("arraysize.txt","r+");
		fseek(s,0,SEEK_SET);
		fscanf(s,"%d",&size);
		size++;
		fclose(s);
		s=fopen("arraysize.txt","w");
		fprintf(s,"%d",size);
		fclose(s);
		pb=fopen("productid.txt","r+");
		fseek(pb,0,SEEK_SET);
		fscanf(pb,"%d",&productcount);
		productcount++;
		fseek(pb,0,SEEK_SET);
		fprintf(pb,"%d",productcount);
		fclose(pb);
		printf("Enter Name of good : ");
		scanf("%s",&name);
		printf("Enter quantity : ");
		scanf("%d",&q);
		printf("Enter price for good : ");
		scanf("%d",&p);
		fos=fopen("ownerfile.txt","r+");
		if(fos==NULL)
		{
				printf("Error in opening a file\n");
		}
		else
		{
						fseek(fos,((80*(size-1))),SEEK_SET);
						fprintf(fos,"  PID : %d",productcount);
						fseek(fos,((80*(size-1))+16),SEEK_SET);
						fprintf(fos,"  Item : %s",name);
						fseek(fos,((80*(size-1))+36),SEEK_SET);
						fprintf(fos,"  Available : %d",q);
						fseek(fos,((80*(size-1))+66),SEEK_SET);
						fprintf(fos,"  Price : %d\n",p);
		}
		fclose(fos);
		printf("\nGood Added successfully to Stock\n");
}


void delete_good()		// Delete an Existing Item from Stock
{
		int i=1,pos,j,ui,temppid,tempprice,tempavailability,c=1,k;
		long int l;
		char string[100],ch,tempname[30];	
		s=fopen("arraysize.txt","r+");
		fseek(s,0,SEEK_SET);
		fscanf(s,"%d",&size);
		if(size<=0)
		{
			printf("Error : Stock does not exit...");
			exit(1);
		}
		
		printf("Enter PID of good to be deleted : ");
		scanf("%d",&pos);
		while(pos<=0)				// For Invalid Input
		{
				printf("ERROR : Invalid PID : Enter PID of the Range (1-%d) ",size);
				printf("\n Would u like to Re-enter input ? Enter 1 for YES or 0 for NO : \n");
				scanf("%d",&ui);
				if(ui==0)
				{
						exit(1);
				}
				else
				{
						printf("Enter PID of good to be deleted : ");
						scanf("%d",&pos);
				}
		}
		fclose(s);
		fos=fopen("ownerfile.txt","r+");
		temp=fopen("temperaryfile.txt","w");
		s=fopen("arraysize.txt","r+");
		fseek(s,0,SEEK_SET);
		fseek(fos,0,SEEK_SET);
		fseek(temp,0,SEEK_SET);
		fscanf(s,"%d",&size);
		i=1,k=1;
		ch=fgetc(fos);
		while(i<=size)
		{
				fseek(fos,((80*(i-1))+7),SEEK_SET);
				fscanf(fos,"%d",&temppid);
				if(temppid!=pos)
				{
						fseek(fos,((80*(i-1))+76),SEEK_SET);
						fscanf(fos,"%d",&tempprice);
						fseek(fos,((80*(i-1))+25),SEEK_SET);
						fscanf(fos,"%s",tempname);
						fseek(fos,((80*(i-1))+50),SEEK_SET);
						fscanf(fos,"%d",&tempavailability);
						fseek(temp,((80*(k-1))),SEEK_SET);
						fprintf(temp,"  PID : %d",temppid);
						fseek(temp,((80*(k-1))+16),SEEK_SET);
						fprintf(temp,"  Item : %s",tempname);
						fseek(temp,((80*(k-1))+36),SEEK_SET);
						fprintf(temp,"  Available : %d",tempavailability);
						fseek(temp,((80*(k-1))+66),SEEK_SET);
						fprintf(temp,"  Price : %d\n",tempprice);
						k++;
						i++;
				}
				else
				{		
						c=0;
						i++;
				}
		}
		fclose(temp);
		fclose(fos);
		fclose(s);
		remove("ownerfile.txt");
		rename("temperaryfile.txt","ownerfile.txt");
		if(c==1)
		{
				printf("Error : PID does not exit \n");
		}
		else
		{
				s=fopen("arraysize.txt","r+");
				fseek(s,0,SEEK_SET);
				fscanf(s,"%d",&size);
				size--;
				fclose(s);
				s=fopen("arraysize.txt","w");
				fprintf(s,"%d",size);
				fclose(s);
				printf("\nGood Deleted successfully from Stock\n");
		}
}
