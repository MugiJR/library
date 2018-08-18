//HEADER FILE
#include<fstream>
#include<stdio.h>
#include<string>
#include<iomanip>
#include<conio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

//CLASS DEFINITION
class book
{
	char bno[6];
	char bname[20];
	char aname[20];
	char publisher[20];
	char copies[10];
	char count[10];
public:
	void create_book()
	{
		cout<<"\nNEW BOOK ENTRY...\n";
		TRY2:
		try{
		cout<<"\nEnter The book no.";
		cin>>bno;
		for(int i=0;bno[i]!='\0';i++)
			if(isalpha(bno[i])!=0)
				throw 0;
		}
		catch(int )
		{
		cout << "enter a valid integer only"<<endl;
		goto TRY2;
		}
		cout<<"\n\nEnter The Name of The Book ";
		gets(bname);
		gets(bname);
		cout<<"\n\nEnter The Author's Name ";
		gets(aname);
		cout<<"\n\nEnter the Publisher Name: ";
		gets(publisher);
		TRY1:
		try{
		cout<<"\n\nEnter the No.of Copies: ";
		cin>>copies;
		for(int i=0;copies[i]!='\0';i++)
			if(isalpha(copies[i])!=0)
				throw 0;
		}
		catch(int )
		{
		cout << "enter a valid integer only"<<endl;
		goto TRY1;
		}
		cout<<"\n\n\nBook Created..";
		strcpy(count,copies);
	}
	void show_book()
	{
		cout<<"\nBOOK NUMBER : "<<bno;
		cout<<"\nBOOK NAME   : "<<bname;
		cout<<"\nAUTHOR NAME : "<<aname;
		cout<<"\nPublisher   : "<<publisher;
		cout<<"\nCopies      : "<<copies;
	}
	void modify_book()
	{
		cout<<"\nBook no. : "<<bno;
		cout<<"\nModify Book Name : ";
		gets(bname);
		gets(bname);
		cout<<"\nModify Author's Name of Book : ";
		gets(aname);
		cout<<"\nModify Publisher Name: ";
		gets(publisher);
		cout<<"\nEnter No. of copies: ";
		cin>>copies;
	
	}
	char* retbno()
	{
		return bno;
	}
	char* retcopies()
	{
		return copies;
	}
	bool dec_copies(char c[])
	{
		int i;
		char temp[10];
		i=(atoi(c))-1;
		if(i==-1)
		{
			return false;
		}
		else
		{
		_itoa_s(i,temp,10);
		strcpy_s(copies,temp);
		return true;
		}

	}
	bool inc_copies(char c[])
	{
		int i;
		char temp[10];
		i=(atoi(c))+1;
		int w=(atoi(count));
		if(i==w+1)
			return false;
		else
		{
		_itoa_s(i,temp,10);
		strcpy_s(copies,temp);
		return true;
		}
	}
	void report()
	{
		cout<<bno<<"\t\t"<<bname<<"\t\t"<<aname<<"\t\t"<<publisher<<"\t\t  "<<copies<<endl;
		
	}

};        

    
//GLOBAL DECLARATIONS
fstream file,file1;
book b;


//FUNCTION TO WRTIE BOOK DETAILS INTO THE FILE
void write_book()
{
	char ch;
	file.open("INVENTORY.DAT",ios::out|ios::app);
	do
	{
		b.create_book();
		file.write((char*)&b,sizeof(book));
		file<<'\n';
		cout<<"\n\nDo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	file.close();
}

//FUNCTION TO PRINTING EQUALS
void printLine()
{
	cout<<"===============================================================================\n";
}

//FUNCTION TO READ BOOK DETAILS FROM THE FILE
void displayAllBooks()
{
	int flag=0;
	file.open("INVENTORY.DAT",ios::in);
	if(!file)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
       	return;
     	}

	cout<<"\n\n\t\tBook LIST\n\n";
	printLine();
	cout<<"Book No"<<"\t\t"<<"Book Name"<<"\t"<<"Author"<<"\t\t"<<"Publisher"<<"\t "<<"copies"<<endl;
    printLine();
	while(file.read((char*)&b,sizeof(book)))
	{
		b.report();
		file<<'\n';
		flag=1;
	}
     	file.close();
		
		if(flag==0)
		{
			system("cls");
			cout<<"Inventory is Empty...Admin! Add books to the Inventory"<<endl;
		}
     	
}

//FUNCTION TO READ SPECIFIC RECORD FROM THE FILE
void displaySpecificBook(char n[])
{
	cout<<"\nBOOK DETAILS\n";
	int flag=0;
	file.open("INVENTORY.DAT",ios::in);
	while(file.read((char*)&b,sizeof(book)))
	{
		if(strcmp(b.retbno(),n)==0)
		{
			b.show_book();
		 	flag=1;
		}
		else
		{
			file<<'\n';
		}
	}
	
	file.close();
	if(flag==0)
		cout<<"\n\nBook does not exist";

}

//FUNCTION TO MODIFY SPECIFIC RECORD IN THE FILE
void modify_book()
{
	char n[6];
	int found=0;
	cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
	cout<<"\n\n\tEnter the Book Number: ";
	cin>>n;
	file.open("INVENTORY.DAT",ios::in|ios::out);
	while(file.read((char*)&b,sizeof(book)) && found==0)
	{
		if(strcmp(b.retbno(),n)==0)
		{
			b.show_book();
			cout<<"\nEnter The New Details of book"<<endl;
			b.modify_book();
			int pos=1*sizeof(book);
		    file.seekp(-pos,ios::cur);
		    file.write((char*)&b,sizeof(book))<<flush;
		    cout<<"\n\n\t Record Updated";
		    found=1;
		}
		else
		{
			file<<'\n';
		}
	}

    	file.close();
    	if(found==0)
    		cout<<"\n\n Record Not Found ";
    	
}

//FUNCTION TO DELETE SPECIFIC RECORD IN THE FILE
void delete_book()
{
	char n[6];
	cout<<"\n\nEnter The Book no. of the Book You Want To Delete : ";
	cin>>n;
	int found=0;
	file.open("INVENTORY.DAT",ios::in|ios::out);
	fstream file2;
	file2.open("Temp.dat",ios::out);
	file.seekg(0,ios::beg);
	while(file.read((char*)&b,sizeof(book)))
	{
		if(strcmp(b.retbno(),n)!=0)  
		{
			file2.write((char*)&b,sizeof(book));
			file2<<'\n';
			file<<'\n';
			found=1;
		}
		else
		{
			file<<'\n';
		}
		
	}
	if(found==0)
	{
    	cout << "Book is not found in the inventory" <<endl;
	}
	else
	{
		cout<<" RECORD HAS BEEN DELETED SUCCESSFULLY"<<endl;
	}
	file2.close();
    file.close();
    remove("INVENTORY.DAT");
    rename("Temp.dat","INVENTORY.DAT");
    	
    	
}

//FUNCTION TO ISSUE BOOK
void book_issue()
{
	char bn[6];
	int found=0,flag=0;
	cout<<"\n\nBOOK ISSUE ...";
    file.open("INVENTORY.DAT",ios::in|ios::out);
		      	cout<<"\n\n\tEnter the book no. ";
				cin>>bn;
				while(file.read((char*)&b,sizeof(book))&& flag==0)
				{
			   		if(strcmp(b.retbno(),bn)==0)
					{
						
						b.show_book();
						flag=1;
						if(b.dec_copies(b.retcopies())==false)
						{
							cout<< " \nOFF SHELF"<<endl;
								break;
						}
						else{
					    int pos=1*sizeof(book);
						file.seekp(-pos,ios::cur);
						file.write((char*)&b,sizeof(book))<<flush;
						cout<<"\n\n\t Book issued successfully"<<endl;
						}}
					else
					{
						file<<'\n';
					}
		    		}
		  		if(flag==0)
		    			cout<<"Book no does not exist"<<endl;
				file.close();
				}

//FUNCTION TO DEPOSIT BOOK	    		
void book_deposit()
{
	char bn[6];
	int found=0,flag=0;
	cout<<"\n\nBOOK Deposit ...";
    file.open("INVENTORY.DAT",ios::in|ios::out);
		      	cout<<"\n\n\tEnter the book no. ";
				cin>>bn;
				while(file.read((char*)&b,sizeof(book))&& flag==0)
				{
			   		if(strcmp(b.retbno(),bn)==0)
					{
						b.show_book();
						flag=1;
						if(b.inc_copies(b.retcopies())==false)
						{
							cout << "\nNo More Copies to Deposit" << endl;
							break;
						}
						else{
					    int pos=1*sizeof(book);
						file.seekp(-pos,ios::cur);
						file.write((char*)&b,sizeof(book))<<flush;
						cout<<"\n\n\t Book Deposited successfully"<<endl;
						}
}
					else
					{
						file<<'\n';
					}
		    		}
		  		if(flag==0)
		    			cout<<"Book does not exist in the Inventory"<<endl;
				file.close();
			}

//FUNCTION FOR ADMIN ACCESS
void librarian()
{

	int op;
	cout<<"\n\n\n\tADMINISTRATOR MENU";
	cout<<"\n\n\t1.CREATE BOOK ";
	cout<<"\n\n\t2.DISPLAY ALL BOOKS ";
	cout<<"\n\n\t3.DISPLAY SPECIFIC BOOK ";
	cout<<"\n\n\t4.MODIFY BOOK ";
	cout<<"\n\n\t5.DELETE BOOK ";
	cout<<"\n\n\t6.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice :  ";
	cin>>op;
	switch(op)
	{
    		case 1:write_book();
					break;
    		
      		
		    case 2:displayAllBooks();
			        break;
			case 3: char num[6];
				cout<<"\n\n\tPlease Enter The book No. ";
	       		cin>>num;
	       		displaySpecificBook(num);
	       		break;
			case 4: modify_book();
				break;
      		case 5: delete_book();
				break;
     		case 6: return;
      		default:cout<<"INVALID SELECTION";
				break;
   	}
   	librarian();
	
}

//FUNCTION TO CHECK WHETHER USER IS ADMIN OR NOT
bool adminCheck(int usr, int psw)
{
	int user,password;
	user=1234;
	password=1234;
	if(usr==user && psw==password)
	{
		return true;
	}
	else 
	{
		return false;
	

	}

}

//MAIN FUNCTION


void main()
{
	char ch;
	bool y;
	int usr,psw;
	do
	{
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. BOOK ISSUE";
		cout<<"\n\n\t02. BOOK DEPOSIT";
	  	cout<<"\n\n\t03. ADMINISTRATOR MENU";
		cout<<"\n\n\t04. DISPLAY BOOK COLLECTION";
	  	cout<<"\n\n\t05. EXIT";
	  	cout<<"\n\n\tPlease Select Your Option :  ";
	  	cin>>ch;
	  	switch(ch)
	  	{
			case '1': book_issue();
			   	       break;
		  	case '2': book_deposit();
			    	 break;
		  	case '3':
					retry:
					system("cls");
					cout<<"\tENTER THE USERNAME: ";
					cin>>usr;
					cout<<"\tENTER THE PASSWORD: ";
					cin>>psw;
					y=adminCheck(usr,psw);
					if(y==true)
					{
						librarian();
					}
					else
					{
						cout<<"Invalid Username Or Password"<<endl;
						goto retry;
					}
				     break;
			case '4': displayAllBooks();
				     break;
		  	case '5':exit(0);
		  	default :cout<<"\a";
		}
    	}while(ch!='5');
}
