// 12 A7 PROJECT 2017
// By The Junk Values


#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<process.h>
#include<ctype.h>

class hotel
{
	int room_no,days;
	char name[30],address[50],phno[10];
	public:
	void menu();
	void addrec(); //To add customer record
	void display(); //To display customer record
	void rooms(); //To display rooms allotted
	void edit(); //To edit customer record
	int check(int r); //To check room status
	void modify(int r); //To modify record
	void delete_rec(int r); //To delete the record
	void checkout(); //To bid farewell to the customer
	void bill(int r); //To view bill for stay
	void checkphno(char phno[]); //To check validity of phone no
}h;

void hotel::menu()
{
	int c;
	clrscr();
	cout<<endl<<"\t\t\t ************************";
	cout<<endl<<"\t\t\t * THE JUNK VALUE HOTEL *";
	cout<<endl<<"\t\t\t ************************";
	cout<<endl<<endl<<"\t\t\t 1. Book a room";
	cout<<endl<<"\t\t\t 2. View customer record";
	cout<<endl<<"\t\t\t 3. Rooms allotted";
	cout<<endl<<"\t\t\t 4. Edit record";
	cout<<endl<<"\t\t\t 5. Exit";
	cout<<endl<<endl<<"\t\t\t Enter your choice: ";
	cin>>c;
	switch(c)
	  {
	   case 1:
		   addrec();
		   break;
	   case 2:
		   display();
		   break;
	   case 3:
		   rooms();
		   break;
	   case 4:
		   edit();
		   break;
	   case 5:
		   checkout();
		   break;
	   default:
		   cout<<"\t\t Invalid choice";
		   break;
	  }
}

void hotel::addrec()
{
	clrscr();
	int r,flag;
	cout<<endl;
	cout<<"Room no. \t Suite \t\t\t Price per day";
	cout<<endl<<"1 to 35   \t The Quaint Suite \t Rs. 2500";
	cout<<endl<<"36 to 70  \t The Special Suite \t Rs. 4000";
	cout<<endl<<"71 to 100 \t The Deluxe Suite  \t Rs. 6000";
	cout<<endl;
	ofstream fout("Record.dat",ios::binary|ios::app);
	if(!fout)
	  {
	  cout<<"Error";
	  exit(0);
	  }
	else
	{
	  cout<<endl<<"Enter customer details: ";
	  cout<<endl<<"Enter room no: ";
	  cin>>r;
	  flag=check(r);
	  if(flag)
	   cout<<"Sorry, the room has already been booked. ";
	  else
	  {
	    room_no=r;
	    cout<<"Enter name: ";
	    gets(name);
	    cout<<"Enter address: ";
	    gets(address);
	    cout<<"Enter phone no: ";
	    gets(phno);
	    checkphno(phno);
	    cout<<"Enter no. of days of stay: ";
	    cin>>days;
	    fout.write((char*)&h,sizeof(h));
	    cout<<endl<<"Room has been booked."<<endl<<endl;
	    bill(r);
	  }
	}
	fout.close();
}

void hotel::display()
{
	clrscr();
	ifstream fin("Record.dat",ios::binary|ios::app);
	int r,flag;
	cout<<"Enter room no: ";
	cin>>r;
	if(!fin)
	{
	 cout<<"Error";
	 exit(0);
	}
	else
	{
	  while(!fin.eof())
	  {
	     fin.read((char*)&h,sizeof(h));
	     if(room_no==r)
	     {
		clrscr();
		cout<<endl<<"Customer Details: ";
		cout<<endl<<endl<<"Room no: "<<room_no;
		cout<<endl<<"Name: "<<name;
		cout<<endl<<"Address: "<<address;
		cout<<endl<<"Phone no: "<<phno;
		flag=1;
		break;
	     }
	  }
	}
	if(flag==0)
	cout<<"Sorry, the room no. not found or is unoccupied.";
	fin.close();
}

void hotel::rooms()
{
	clrscr();
	ifstream fin("Record.dat",ios::binary|ios::app);
	if(!fin)
	{
	 cout<<"Error";
	 exit(0);
	}
	else
	{
	  cout<<"List of Rooms Allotted: ";
	  cout<<endl<<endl<<"Room no. \tName \t\tAddress \tPhone no. ";
	  while(!fin.eof())
	  {
	    fin.read((char*)&h,sizeof(h));
	    if(fin.eof())
	    break;
	    else
		cout<<endl<<room_no<<"\t\t"<<name<<"\t\t"<<address<<"\t\t"<<phno;
	  }
	}
	fin.close();
}

void hotel::edit()
{
	clrscr();
	int c,r;
	cout<<"Edit menu: ";
	cout<<endl<<"1. Modify customer record";
	cout<<endl<<"2. Delete customer record";
	cout<<endl<<endl<<"Enter choice: ";
	cin>>c;
	clrscr();
	cout<<"Enter room no: ";
	cin>>r;
	switch(c)
	  {
	  case 1:
		  modify(r);
		  break;
	  case 2:
		  delete_rec(r);
		  break;
	  default:
		  cout<<"Invalid choice";
		  break;
	  }
}

int hotel::check(int r)
{
	int flag=0;
	ifstream fin("Record.dat",ios::binary|ios::app);
	if(!fin)
	{
	 cout<<"Error";
	 exit(0);
	}
	else
	{
	  while(!fin.eof())
	  {
	     fin.read((char*)&h,sizeof(h));
	     if(room_no==r)
	     {
	      flag=1;
	      break;
	     }
	  }
	}
	fin.close();
	return flag;
}

void hotel::modify(int r)
{
	int flag=0;
	fstream file("Record.dat",ios::binary|ios::in|ios::out);
	if(!file)
	{
	 cout<<"Error";
	 exit(0);
	}
	else
	{
	  while(!file.eof())
	  {
	    file.read((char*)&h,sizeof(h));
	    if(room_no==r)
	    {
	    cout<<endl<<"Enter new details: ";
	    cout<<endl<<"Enter name: ";
	    gets(name);
	    cout<<"Enter address: ";
	    gets(address);
	    cout<<"Enter phone no: ";
	    gets(phno);
	    checkphno(phno);
	    cout<<"Enter no. of days of stay: ";
	    cin>>days;
	    file.seekp(file.tellp()-sizeof(h),ios::beg);
	    file.write((char*)&h,sizeof(h));
	    cout<<endl<<"Record has been modified."<<endl<<endl;
	    bill(r);
	    flag=1;
	    break;
	    }
	  }
	}
	if(flag==0)
	cout<<"Sorry, room no. not found or is unoccupied.";
	file.close();
}

void hotel::delete_rec(int r)
{
	int flag=0;
	ifstream fin("Record.dat",ios::binary);
	ofstream fout("Temp.dat",ios::binary);
	if(!fin||!fout)
	{
	 cout<<"Error";
	 exit(0);
	}
	else
	{
	  while(!fin.eof())
	  {
	    fin.read((char*)&h,sizeof(h));
	    if(fin.eof())
	     break;
	    else
	    {
	    if(room_no!=r)
	    {
	     fout.write((char*)&h,sizeof(h));
	     flag=1;
	    }
	    }
	  }
	if(flag==0)
	cout<<"Sorry, room no. not found or is unoccupied.";
	else
	cout<<endl<<"Record has been deleted.";
	fin.close();
	fout.close();
	}
	remove("Record.dat");
	rename("Temp.dat","Record.dat");
}

void hotel::checkout()
{
	clrscr();
	cout<<endl<<"\t\t    THANK YOU FOR CHECKING IN AT OUR HOTEL!";
	cout<<endl<<"\t\t        WE HOPE TO SEE YOU AGAIN LATER."<<endl;
	getch();
	exit(0);
}

void hotel::bill(int r)
{
	if((r>=1)&&(r<=35))
	  cout<<"The bill for your stay is Rs. "<<days*2500.00;
	else if((r>=36)&&(r<=70))
	  cout<<"The bill for your stay is Rs. "<<days*4000.00;
	else if((r>=71)&&(r<=100))
	  cout<<"The bill for your stay is Rs. "<<days*6000.00;
	else
	  cout<<"Room no. not in hotel.";
}

void hotel::checkphno(char phno[])
{
	for(int i=0;phno[i]!='\0';i++)
	{
	 if(isdigit(phno[i]))
	  continue;
	 else
	 {
	  cout<<"Enter a valid phone number: ";
	  gets(phno);
	  break;
	 }
	}
	if(i==10)
	 return;
	else
	 {
	  cout<<"Enter a valid phone number: ";
	  gets(phno);
	 }
}
void main()
{
	clrscr();
	char rep;
	cout<<endl<<"\t\t\t****************************";
	cout<<endl<<"\t\t\t* HOTEL MANAGEMENT PROJECT *";
	cout<<endl<<"\t\t\t****************************";
	cout<<endl;
	cout<<endl<<"\t\t\tMade by the Junk Values: ";
	cout<<endl<<"\t\t\tJ. Neythra \t 41";
	cout<<endl<<"\t\t\tS. Pooja   \t 43";
	cout<<endl<<"\t\t\tS. Varsha  \t 47";
	cout<<endl<<"\t\t\tK. Visalya \t 48"<<endl;
	cout<<endl<<"\t\t\tPress any key to continue. ";
	getch();
	do
	{
	  h.menu();
	  cout<<endl<<endl<<"Do you wish to continue? (Enter y/n): ";
	  cin>>rep;
	} while((rep=='y')||(rep=='Y'));
	if((rep=='n')||(rep=='N'))
	  h.checkout();
	else
	  cout<<"Enter a valid response please. (Enter y/n)";
}




