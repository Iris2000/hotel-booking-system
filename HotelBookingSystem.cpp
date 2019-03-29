#include <iostream>
#include <iomanip>
#include <cmath>
#include <cctype>
#include <fstream>
using namespace std;

//declare fuction 
string RegisterPage();
string LoginPage();
void bookingPage();
void packageSelection();
void roomType();
void priceNight();
void summary(int);
void payment(double);
void reservation();

//declare global variables
int nights, rooms, guests;    //for bookingPage function
float discount;              //for bookingPage function
string code;                //for bookingPage function
bool getOfferCode = false; //for bookingPage function
int package, typeRoom;    //for packageSelection function and roomType function
string passw;            //for paymentpage 
string packageRoom, type_room; 

main()
{	
	int PPnight;
	char select;
	string mainPage;
	
	
	cout << "**************************************************************************************************\n" << endl;
	cout << "\t\t***      ***   ***       ***     ***      ***********   ***********" << endl;
	cout << "\t\t***      ***    ***     ***     ** **     ***********   ***********" << endl;
	cout << "\t\t***      ***     ***   ***     **   **        ***           ***" << endl;
	cout << "\t\t************      *******     ***   ***       ***           ***" << endl;
	cout << "\t\t************       *****     ***     ***      ***           ***" << endl;
	cout << "\t\t***      ***        ***  ** *** ***** *** **  ***           ***" << endl;
	cout << "\t\t***      ***        *** ** *************** ** ***           ***" << endl;
	cout << "\t\t***      ***      *****    ***         ***   *****          ***" << endl;  
	cout << "\t\t                ***       ***           ***      ***" << endl;
	cout << "\t\t               *         ***             ***        *\n" << endl;
	cout << "\t\t\t\tWELCOME TO HYATT REGENCY\n";
	cout << "**************************************************************************************************\n" << endl;  
		
	
	do
	{
		cout << "**************************************************************************************************\n" << endl;
		cout << "\tRegister --- R\t\tLogin --- L" << endl;
		cout << "\n\tPlease select : ";
		cin >> select;
		select = (char)toupper(select);
		
		while (select != 'R' && select != 'L')
		{
			cout << "\n\tInvalid input\n";
			cout << "\n\tPlease enter again : ";
			cin >> select;
			select = (char)toupper(select);	
		}
		
		if (select == 'R')
		{
			mainPage = RegisterPage();
		}
		else
		{
			mainPage = LoginPage();
			
		}
		
	}while(mainPage == "main");
	
	packageSelection();
	roomType();
	priceNight();
}

string RegisterPage()
{
	//create a register file
	ofstream UserRegister("UserInfo.txt", ios_base::app);
	
	string username;
	string password;
	string stored_username;
	string stored_password;
	
	if (!UserRegister)
	{
		cout << "File cannot be opened" << endl;
		cout << "Back to main page" << endl;
		return "main";
	}
	
	cin.ignore();
	cout << "\n\tWelcome to HYATT registration page!\n";
	cout << "\n\t\tEnter username : ";
	getline (cin, username);
	cout << "\n\t\tEnter password : ";
	getline (cin, password);
	
	UserRegister << username << "\n" << password << "\n";
	cout << "\n\tRegistration Successful.\n" << endl;
	cout<<"**************************************************************************************************\n"<<endl;	
	return "main";	

	UserRegister.close();
}

string LoginPage()
{
	bool found = false;
	//login varification
	ifstream UserLogin ("UserInfo.txt", ios::in);
	string stored_username, stored_password;
	string username, password;
	
	//to check if the file is open
	if (!UserLogin)
	{
		cout << "\t\tFile cannot be opened" << endl;
		cout << "\t\tBack to main page" << endl;
		return "main";
	}
	else
	{
		cin.ignore();
		cout<<"\n\tWelcome to HYATT login page, please enter your username and password.\n";
		cout << "\n\t\tUsername : ";
		getline (cin, username);
		cout << "\n\t\tPassword : ";
		getline (cin, password);
	}
	
	while (UserLogin >> stored_username >> stored_password)
	{
		if (username == stored_username && password == stored_password)
		{
			cout << "\n\tLogin successful." << endl;
			cout << "\tWelcome to Hyatt Booking System. " << endl;
			cout << "**************************************************************************************************\n" << endl;
			found = true;
			bookingPage();
		}
	}

	if (!found)
	{	
		//found = false
		cout << "\tFail to login" << endl;
		return "main";
	}
	
	UserLogin.close();
}

void bookingPage()
{
	//for user to enter number of nights, rooms, and guests.
	//check offer code.
	int i;
	string offerCode[3] = {"123a", "234b", "345c"};
	char y_n;
	
	cout << "**************************************************************************************************\n" << endl;
	cout << "\tPlease fill in the details below:\n" << endl;
	cout << "\t\tnumber of nights : ";
	cin >> nights;
	cout << "\n\t\tnumber of rooms  : ";
	cin >> rooms;
	cout << "\n\t\tnumber of guests : ";
	cin >> guests;
	
	do
	{
		cout << "\n\t\toffer code (Enter 'N' if no offer code) : ";
		cin >> code;
		
		//to check if there is a discount for user
		if (code == "n" || code == "N")
		{
			cout << "\t\tNo discount." << endl;
			break;
		}
		else
		{
			for (i=0; i<=2; i++)
			{
				if (offerCode[i].compare(code) == 0)
				{
					cout << "\n\t\tDiscount get." << endl;
					getOfferCode = true;
					y_n = 'N';
				}
			}
				
			if (!getOfferCode)
			{
				cout << "\t\tNo offer code found.\a\a\a" << endl;
				cout << "\t\tAre you wish to try again? [y/n] : ";
				cin >> y_n;
				y_n = (char)toupper(y_n);
					
			}
			
			while (y_n != 'Y' && y_n != 'N')
			{
				cout << "\t\t\a\a\aInvalid input. Please enter again : ";
				cin >> y_n;
				y_n = (char)toupper(y_n);	
			}
		}
		
	}while (y_n == 'Y');
	
	cout << "\n\tContinue with package selection..."<<endl;
	cout << "**************************************************************************************************\n" << endl;	
	packageSelection();
}

void packageSelection()
{
	//for user to select package
	cout << "*************************************************************************************************\n" << endl;
	
	cout << "\tPlease select one package with the number given.\n" << endl;
	cout << "\t\tStandard Package\t\t---1" << endl;
	cout << "\t\tDetails: no additional services\n" << endl;
	cout << "\t\tBreakfast Package\t\t---2" << endl;
	cout << "\t\tDetails: breakfast provided every day\n" << endl;
	cout << "\t\tSpa Package\t\t\t---3" << endl;
	cout << "\t\tDetails: spa provided every night\n" << endl;
	cout << "\t\tExplore Package\t\t\t---4" << endl;
	cout << "\t\tDetails: access to all facilities\n" << endl;
	cout << "\t\tFull Package\t\t\t---5" << endl;
	cout << "\t\tDetails: breakfast+spa+facilities\n" << endl;
	cout << "\tYou have select package number : ";
	cin >> package;
	
	while (package < 1 || package > 5)
	{
		cout << "\t\a\a\aInvalid choice. Please enter again." << endl;
		cout << "\tYou have select package number : ";
		cin >> package;
	}
	
	cout << "\n\tContinue with room type selection..." << endl;
	cout << "*************************************************************************************************\n" << endl;
	roomType();
}

void roomType()
{
	//for user to select type of room
	cout << "*************************************************************************************************\n" << endl;
	
	cout << "\tPlease select the room type with the number given.\n" << endl;
	cout << "\t\tSingle Room --- 1" << endl;
	cout << "\t\tDouble Room --- 2" << endl;
	cout << "\t\tFamily Room --- 3\n" << endl;
	cout << "\tYou have select room type : ";
	cin >> typeRoom;
		
	while (typeRoom < 1 || typeRoom > 3)
	{
		cout << "\t\a\a\aInvalid choice. Please enter again." << endl;
		cout << "\tYou have select room type : ";
		cin >> typeRoom;
	}

	cout << "\n\tContinue with booking details and summary of charges..." << endl;
	cout << "*************************************************************************************************\n" << endl;
	priceNight(); 
}

void priceNight()
{	
	//calculate price per night with the type of package and room selected
	int ppNight;
	
	if (package == 1 && typeRoom == 1)
	{
		ppNight = 88;
	}
	else if (package == 1 && typeRoom == 2)
	{
		ppNight = 188;
	}
	else if (package == 1 && typeRoom ==3)
	{
		ppNight = 288;
	}
	else if ((package == 2 && typeRoom == 1) || (package == 3 && typeRoom == 1) || (package == 4 && typeRoom ==1))
	{
		ppNight = 99;
	}
	else if ((package == 2 && typeRoom == 2) || (package == 3 && typeRoom == 2) || (package == 4 && typeRoom == 2))
	{
		ppNight = 199;
	}
	else if ((package == 2 && typeRoom == 3) || (package == 3 && typeRoom == 3) || (package == 4 && typeRoom ==3))
	{
		ppNight = 320;	
	}
	else if (package == 5 && typeRoom == 1)
	{
		ppNight = 120;
	}
	else if (package == 5 && typeRoom == 2)
	{
		ppNight = 220;
	}
	else
	{
		ppNight = 420;
	}
	
	summary(ppNight);
	
}

void summary(int PPnight)
{ 
	double subtotal, countyTax, serviceTax, feesTaxes, total_ppRoom, total;
	
	//for further display 
	//display package name for each package number
	if (package == 1)
	{
		packageRoom = "Standard Package";
	}
	else if (package == 2)
	{
		packageRoom = "Breakfast Package";
	}
	else if (package == 3)
	{
		packageRoom = "Spa Package";
	}
	else if (package == 4)
	{
		 packageRoom = "Explore Package";
	}
	else
	{
		packageRoom = "Full Package";
	}
	
	//for further display
	//display room name for each number
	if (typeRoom == 1)
	{
		type_room = "Single Room";
	}
	else if (typeRoom == 2)
	{
		type_room = "Double Room";
	}
	else
	{
		type_room = "Family Room";
	}
	
	//calculate price
	cout<<setprecision(2)<<fixed;
	subtotal = PPnight * nights;
	countyTax = subtotal * 0.06;
	serviceTax = subtotal * 0.10;
	feesTaxes = countyTax + serviceTax;
	
	//calculate discount
	if (code == "n" || code == "N" || getOfferCode == false)
	{
		discount = 0;
	}
	else
	{
		discount = (subtotal + feesTaxes) * 0.10;
	}
	
	total_ppRoom = (subtotal + feesTaxes) - discount;
	total = ceil(total_ppRoom * rooms);
	
	//display summary
	cout << "*************************************************************************************************\n" << endl;
	cout << "\tHere is your booking details:\n" << endl;
	cout << "\t number of nights : " << nights << endl;
	cout << "\t number of rooms  : " << rooms << endl;
	cout << "\t number of guests : " << guests << endl;
	cout << "\t room package     : " << packageRoom << endl;
	cout << "\t type of room     : " << type_room << endl << endl;
	
	cout << "\tSummary of Charges:\n" << endl;
	cout << "\t Price per night\t: RM " << PPnight << endl;
	cout << "\t Subtotal\t\t: RM " << subtotal << endl;
	cout << "\t County tax\t\t: RM " << countyTax << endl;
	cout << "\t Service tax\t\t: RM " << serviceTax << endl;
	cout << "\t Total fees & taxes\t: RM " << feesTaxes << endl;
	cout << "\t Discount\t\t: RM " << discount << endl;
	cout << "\t Total price per room\t: RM " << total_ppRoom << endl << endl;
	cout << "\t TOTAL PRICE : RM " << total << endl << endl;
	cout << "*************************************************************************************************\n" << endl;
	
	cin.ignore();
	
	payment(total);
	
}
void payment(double total)
{
	char pay_sel, choice;
	int month, year, bcn, i; 
	string ccard;
	bool p_w = false;
	double amount, balance;
	string pword [4] = {"1357aceg","2468bdfh","7531geca","8642hfdb"};
		
	cout << "*************************************************************************************************\n";
	cout << "\n\tDo you want to proccess your payment with credit card (C) or bank in (B)? [C/B] : ";
	cin >> pay_sel;
	pay_sel = (char)toupper(pay_sel);
	
	while (pay_sel != 'C' && pay_sel != 'B')
	{
		cout << "\n\tInvalid input! Please Re-enter again : ";
		cin >> pay_sel;
		pay_sel = (char)toupper(pay_sel);	
	}
	
	if (pay_sel == 'C')
	{
		//Credit Card Detail
		cout << "\n\tYou have select credit card payment. Please enter your credit card number";
		cout << "\n\tand expiration date.";
		cout << "\n\n\n\t\tCredit card number : ";
		cin >> ccard;
		cout << "\n\n\t\tExpiration date ";
		cout << "\n\t\tMonth[MM] : ";
		cin >> month;
		cout << "\n\t\tYear[YY] : ";
		cin >> year;
				
		while ((month<0 || month>13) && (year<18 || year>25))
		{
			cout << "\n\tInvalid Date! Please Re-enter again!\n";
			cout << "\n\n\t\tExpiration date ";
			cout << "\n\t\tMonth : ";
			cin >> month;
			cout << "\n\t\tYear : ";
			cin >> year;
		}
		
		cout << "\n\n\tPayment Success.";
		cout << "\n\n\tThank you for using our hotel online booking system!";
		cout << "\n\n\n**********************************************************************************************\n";
		
	}
		
	if (pay_sel == 'B')
	{
		do
		{	
			//Bank-in Detail 
			cout << "\n\tYou have choose to bank-in. Please enter your bank account number, ";	
			cout << "\n\tpassword and amount.";
			cout << "\n\n\n\t\tBank account number : ";
			cin >> bcn;
			cout << "\n\n\t\tPassword\t: ";
			cin >> passw;
			
			for (i=0; i<=3; i++)
			{
				if (pword[i].compare(passw) == 0)
				{
					p_w = true;
					choice = 'N';
				}
			}
					
			if (!p_w)
			{
				cout << "\t\tIncorrect passward!\n";
				cout << "\t\tAre you wish to try again? [y/n] : ";
				cin >> choice;
				choice = (char)toupper(choice);
			}
				
			while (choice != 'Y' && choice != 'N')
			{
				cout << "\t\t\a\a\aInvalid input. Please enter again : ";
				cin >> choice;
				choice = (char)toupper(choice);	
			}
			
		}while (choice == 'Y');

		
		cout << "\n\n\t\tEnter the amount you wish to transfer\t: RM ";
		cin >> amount;
		
		while (amount < total)
		{
			cout << "\n\n\t\tThe amount you wish to transfer are not enoungh! Please try again.";
			cout << "\n\t\tEnter the amount you wish to transfer\t: RM ";
			cin >> amount;
		}
		
		if (amount > total)
		{
			balance = amount - total;
			cout << "\n\t\tThe amount you transfer are more than total amount.";
			cout << "\n\t\tThe total fee for your booking is : RM " << total;
			cout << "\n\t\tYour balance : RM " << balance;
		}
		else 
		{
			cout << "\n\t\tTransfer succesful!";
		}
		
		cout << "\n\n\tThank you for using our hotel online booking system!";
		cout << "\n\n\n**********************************************************************************************\n";
		}
		
		reservation();
}

void reservation ()
{
	//Reservation confirmation page 
	cout << "\n**********************************************************************************************\n";
	cout << "\n\tThis is your reservation confirmation page, please show this to our hotel when";
	cout << "\n\tyou check in.";
	cout << "\n\n\t\tnumber of nights : " << nights << endl;
	cout << "\n\t\tnumber of room     : " << rooms << endl;
	cout << "\n\t\tnumber of guests   : " << guests << endl;
	cout << "\n\t\troom package       : " << packageRoom << endl;
	cout << "\n\t\ttype of room       : " << type_room << endl;
	cout << "\n\t\tcheck-in time      : After 12:00 p.m.";
	cout << "\n\n\t\tcheck-out time   : Before 12.00 p.m."; 
	cout << "\n\n\n**********************************************************************************************\n";
}
	

