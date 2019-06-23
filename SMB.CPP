#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>

class product
{
int pno;
char name[50];
float price,qty,tax,dis;
public:
product()
{
	pno = 0;
	price = 0;
	qty = 0;
	tax = 0;
	dis = 0;
}
void create_product();
void show_product();

int retpno()
{return pno;}

float retprice()
{return price;}

char* retname()
{return (char*)name;}

int retdis()
{return dis;}

int rettax()
{return tax;}
};
void product::create_product()
{
cout<<"\nPlease Enter The Product No. of The Product ";
cin>>pno;
cout<<"\n\nPlease Enter The Name of The Product ";
gets((char*)name);
cout<<"\nPlease Enter The Price of The Product ";
cin>>price;
cout<<"\nPlease Enter The Discount (%) ";
cin>>dis;
tax = 14;
}
void product::show_product()
{
cout<<"\nThe Product No. of The Product : "<<pno;
cout<<"\nThe Name of The Product : ";
puts((char*)name);
cout<<"\nThe Price of The Product : "<<price;
cout<<"\nDiscount : "<<dis;
}
// global declaration for stream object, object
fstream fp;
// function to write in file
void write_product()
{
product pr;
fp.open("Shop.dat",ios::out|ios::app);
pr.create_product();
fp.write((char*)&pr,sizeof(pr));
fp.close();
cout<<"\n\nThe Product Has Been Created ";
getch();
}
// function to read all records from file
void display_all()
{
product pr;
clrscr();
cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
fp.open("Shop.dat",ios::in);
while(fp.read((char*)&pr,sizeof(pr)))
{
pr.show_product();
cout<<"\n\n====================================\n";
getch();
}
fp.close();
getch();
}
// function to read specific record from file
void display_sp(int n)
{
product pr;
int flag=0;
fp.open("Shop.dat",ios::in);
while(fp.read((char*)&pr,sizeof(product)))
{
if(pr.retpno()==n)
{
clrscr();
pr.show_product();
flag=1;
}
}
fp.close();
if(flag==0)
cout<<"\n\nrecord not exist";
getch();
}
// function to modify record of file
void modify_product()
{
product pr;
int no,found=0;
clrscr();
cout<<"\n\n\tTo Modify ";
cout<<"\n\n\tPlease Enter The Product No. of The Product";
cin>>no;
fp.open("Shop.dat",ios::in|ios::out);
while(fp.read((char*)&pr,sizeof(product)) && found==0)
{
if(pr.retpno()==no)
{
pr.show_product();
cout<<"\nPlease Enter The New Details of Product"<<endl;
pr.create_product();
int pos=-1*sizeof(pr);
fp.seekp(pos,ios::cur);
fp.write((char*)&pr,sizeof(product));
cout<<"\n\n\t Record Updated";
found=1;
}
}
fp.close();
if(found==0)
cout<<"\n\n Record Not Found ";
getch();
}
// function to delete record of file
void delete_product()
{
product pr;
int no;
clrscr();
cout<<"\n\n\n\tDelete Record";
cout<<"\n\nPlease Enter The product no. of The Product You Want To Delete";
cin>>no;
fp.open("Shop.dat",ios::in|ios::out);
fstream fp2;
fp2.open("Temp.dat",ios::out);
fp.seekg(0,ios::beg);
while(fp.read((char*)&pr,sizeof(product)))
{
if(pr.retpno()!=no)
{
fp2.write((char*)&pr,sizeof(product));
}
}
fp2.close();
fp.close();
remove("Shop.dat");
rename("Temp.dat","Shop.dat");
cout<<"\n\n\tRecord Deleted ..";
getch();
}
// function to display all products price list
void menu()
{
product pr;
clrscr();
fp.open("Shop.dat",ios::in);
if(!fp)
{
cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
cout<<"\n\n\n Program is closing.. ";
getch();
exit(0);
}

cout<<"\n\n\t\tProduct MENU\n\n";
cout<<"====================================================\n";
cout<<"P.NO.\t\tNAME\t\tPRICE\n";
cout<<"====================================================\n";

while(fp.read((char*)&pr,sizeof(product)))
{
cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
}
fp.close();
}
// function to place order and generating bill for Products
void place_order()
{
product pr;
int order_arr[50],quan[50],c=0;
float amt,damt,total=0,tamt;
char ch='Y';
menu();
cout<<"\n============================";
cout<<"\n PLACE YOUR ORDER";
cout<<"\n============================\n";
do{
cout<<"\n\nEnter The Product No. Of The Product : ";
cin>>order_arr[c];
cout<<"\nQuantity in number : ";
cin>>quan[c];
c++;
cout<<"\nDo You Want To Order Another Product ? (y/n)";
cin>>ch;
}while(ch=='y'||ch=='Y');
cout<<"\n\nThank You For Placing The Order";getch();clrscr();
cout<<'/n';

cout<<"\n********************************INVOICE************************\n";
cout<<"\nPr No.\tPr Name\tQuantity\tPrice\tAmount\tAmount after discount\n";
for(int x=0;x<=c;x++)
{
fp.open("Shop.dat",ios::in);
fp.read((char*)&pr,sizeof(product));
while(!fp.eof())
{
if(pr.retpno()==order_arr[x])
{
amt=pr.retprice()*quan[x];
damt=amt-(amt*pr.retdis()/100);
tamt=damt-(damt*pr.rettax()/100);
cout<<'\n'<<order_arr[x]<<'\t'<<pr.retname()<<'\t'<<quan[x]<<"\t\t"<<pr.retprice()<<'\t'<<amt<<"\t\t"<<damt;
total=total+tamt;
}
fp.read((char*)&pr,sizeof(product));
}

fp.close();
}
cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
getch();
}

//INTRODUCTION

void intro()
{
clrscr();
gotoxy(31,11);
cout<<"SUPER MARKET BILLING";
gotoxy(35,13);
cout<<"PROJECT";
cout<<"\n\nMADE BY : HARINI VENUGOPAL";
cout<<"\n\nCOLLEGE : MEENAKSHI SUNDARARAJAN ENGINEERING COLLEGE";
getch();
}
// ADMINSTRATOR MENU FUNCTION
void admin_menu()
{
clrscr();
char ch2;
cout<<"\n\n\n\tADMIN MENU";
cout<<"\n\n\t1.CREATE PRODUCT";
cout<<"\n\n\t2.DISPLAY ALL PRODUCTS";
cout<<"\n\n\t3.QUERY ";
cout<<"\n\n\t4.MODIFY PRODUCT";
cout<<"\n\n\t5.DELETE PRODUCT";
cout<<"\n\n\t6.VIEW PRODUCT MENU";
cout<<"\n\n\t7.BACK TO MAIN MENU";
cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
ch2=getche();
switch(ch2)
{
case '1': clrscr();
write_product();
break;
case '2': display_all();break;
case '3':
int num;
clrscr();
cout<<"\n\n\tPlease Enter The Product No. ";
cin>>num;
display_sp(num);
break;
case '4': modify_product();break;
case '5': delete_product();break;
case '6': menu();
getch();
case '7': break;
default:cout<<'\a';admin_menu();
}
}
//MAIN FUNCTION
void main()
{
char ch;
intro();
do
{
clrscr();
cout<<"\n\n\n\tMAIN MENU";
cout<<"\n\n\t01. CUSTOMER";
cout<<"\n\n\t02. ADMINISTRATOR";
cout<<"\n\n\t03. EXIT";
cout<<"\n\n\tPlease Select Your Option (1-3) ";
ch=getche();
switch(ch)
{
case '1': clrscr();
place_order();
getch();
break;
case '2': admin_menu();
break;
case '3':exit(0);
default :cout<<'\a';
}
}while(ch!='3');
}
//END


 
