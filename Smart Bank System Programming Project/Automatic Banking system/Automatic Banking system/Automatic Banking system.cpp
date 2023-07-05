#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void first_page();
void store_user();
void store_pass();
void store_Amount();
void check_user(int f_choice);
void check_pass(string f_user, string f_pass, int f_choice);
void login_page();
void login_page_choice(string f_user, string f_pass, int f_choice, int* ptr_choice);
void Deposit(string f_user, string f_pass);
void Withdraw(string f_user, string f_pass);
void Amount(string f_user, string f_pass);
void data(string f_user, string f_pass);
void edit(string f_user, string f_pass);
void delete_user(string f_user, string f_pass);

int main()
{
	int choice;
	do {
		first_page();

		cout << " Enter your choice : ";
		cin >> choice;
		cout << endl;

		if (choice == 1)
		{
			store_user();
			store_pass();
			store_Amount();

		}
		else if (choice == 2)
		{
			check_user(choice);
		}
		else
		{
			if (choice != 3)
			{
				cout << "     **Wrong choice** " << endl << endl;
			}
		}
	} while (choice != 3);
	return 0;
}

void first_page()   //This function displays the main menu choices
{
	cout << " \t *choose one of them* " << endl << endl;
	cout << "  (1) New Account " << endl << endl;
	cout << "  (2) Login " << endl << endl;
	cout << "  (3) Exit " << endl << endl;
}

void store_user()   //This function lets the user enter new username 
{
	string new_user, user, pass;
	double Amount;

	fstream temp_data1("temp_data.txt", ios::app);  //To make sure the files have been created
	fstream data_file1("data.txt", ios::app);
	data_file1.close();
	temp_data1.close();

	fstream data_file("data.txt", ios::in);    //To read from the file

	cout << " Enter username : ";

	if (data_file >> user >> pass >> Amount)  // To check if the file is empty or not
	{
		data_file.close();
		data_file.open("data.txt");   // To start searching from the begining of file

		do
		{
			cin >> new_user;
			cout << endl;

			while (data_file >> user >> pass >> Amount)  //To read data from file
			{
				if (new_user == user) // To check if the userame is repeated
				{
					cout << "     This username is already exist  " << endl << endl;
					cout << " please Enter another username : ";
					data_file.close();
					data_file.open("data.txt");
					break;
				}
			}
		} while (new_user == user);


		if (new_user != user)
		{
			data_file.close();
			fstream data_file1("data.txt", ios::app);
			data_file1 << new_user << endl;
			data_file1.close();
		}
	}
	else
	{
		data_file.close();
		cin >> new_user;
		cout << endl;
		fstream data_file1("data.txt", ios::app);
		data_file1 << new_user << endl;
		data_file1.close();
	}
}

void store_pass()    //This function lets the user enter new password
{
	string pass;
	fstream data_file("data.txt", ios::app);

	cout << " Enter password : ";
	cin >> pass;
	cout << endl;

	data_file << pass << endl;
	data_file.close();
}

void store_Amount()     //This function lets the user enter the amount of money to open the account
{
	long double Amount;

	fstream data_file("data.txt", ios::app);

	cout << " Enter your amount : ";
	do
	{
		cin >> Amount;
		cout << endl;
		if (Amount < 1000)   //To check if the amount >= 1000
		{
			cout << "     The minimum value \"1000\"    " << endl << endl;
			cout << " please Enter Amount again : ";
		}
		else
		{
			data_file << Amount << endl;
		}

	} while (Amount < 1000);
	data_file.close();
}

void check_user(int f_choice)    //This function lets the user enter username to login
{
	string login_user, user, pass;
	double Amount;

	cout << " Enter your username : ";
	cin >> login_user;
	cout << endl;

	fstream data_file("data.txt", ios::in);
	while (data_file >> user >> pass >> Amount)
	{
		if (user == login_user)  //To check if he username exists
		{
			check_pass(user, pass, f_choice);

		}
	}
	if (user != login_user)
	{
		cout << "     userName is not available " << endl << endl;
	}

	data_file.close();
}

void check_pass(string f_user, string f_pass, int f_choice)    //This function lets the user enter password to login
{
	int* ptr_choice = &f_choice;
	string login_pass;

	cout << " Enter your password : ";
	do
	{
		cin >> login_pass;
		cout << endl;

		if (f_pass == login_pass)  //To make sure the password is correct
		{
			cout << "     **login success**  " << endl << endl;
			do
			{
				login_page();
				cout << " Enter your choice : ";
				cin >> f_choice;
				cout << endl;

				login_page_choice(f_user, f_pass, f_choice, ptr_choice);

			} while (f_choice != 7);
		}
		else
		{
			cout << "     **Wrong password** " << endl << endl;
			cout << " please Enter your password again : ";
		}
	} while (login_pass != f_pass);
}

void login_page()     //This function displays the functions that the user can make
{
	cout << " \t *choose one of them* " << endl << endl;
	cout << "  (1) Deposit Amount " << endl << endl;
	cout << "  (2) Withdraw Amount " << endl << endl;
	cout << "  (3) Balance " << endl << endl;
	cout << "  (4) data " << endl << endl;
	cout << "  (5) edit " << endl << endl;
	cout << "  (6) delete " << endl << endl;
	cout << "  (7) Exit " << endl << endl;
}

void login_page_choice(string f_user, string f_pass, int f_choice, int* ptr_choice)
{   //This function will direct the user to the function he has chosen
	if (f_choice == 1)
	{
		Deposit(f_user, f_pass);
	}
	else if (f_choice == 2)
	{
		Withdraw(f_user, f_pass);
	}
	else if (f_choice == 3)
	{
		Amount(f_user, f_pass);
	}
	else if (f_choice == 4)
	{
		data(f_user, f_pass);
	}
	else if (f_choice == 5)
	{
		edit(f_user, f_pass);
		*ptr_choice = 7;  //To return the user to main menu
	}
	else if (f_choice == 6)
	{
		delete_user(f_user, f_pass);
		*ptr_choice = 7;  //To return the user to main menu
	}
	else
	{
		if (f_choice != 7)
		{
			cout << "     **Wrong choice** " << endl << endl;
		}
	}
}

void Deposit(string f_user, string f_pass)    //This function lets the user depoist money in his account
{
	long double DepositAmount = 0;
	string temp_user, temp_pass;
	long double  temp_amount, res;

	fstream temp_data("temp_data.txt", ios::out);
	fstream data_file("data.txt", ios::in);
	// Use temp_data to edit in data

	cout << " Enter Deposit Amount : ";
	cin >> DepositAmount;
	cout << endl;

	while (data_file >> temp_user >> temp_pass >> temp_amount)
	{
		if (temp_user == f_user && temp_pass == f_pass) //To search in file for the correct account
		{
			temp_data << temp_user << endl;
			temp_data << temp_pass << endl;
			res = temp_amount + DepositAmount;
			temp_data << res << endl;
			cout << " your Amount is : " << res << endl << endl;
		}
		else  //Keeps the other accounts with no change
		{
			temp_data << temp_user << endl;
			temp_data << temp_pass << endl;
			temp_data << temp_amount << endl;
		}
	}
	temp_data.close();
	data_file.close();

	temp_data.open("temp_data.txt");
	data_file.open("data.txt");

	while (temp_data >> temp_user >> temp_pass >> temp_amount) //Transfer data from temp_data to data_file
	{
		data_file << temp_user << endl;
		data_file << temp_pass << endl;
		data_file << temp_amount << endl;
	}
	data_file.close();
	temp_data.close();
}

void Withdraw(string f_user, string f_pass)   //This function lets the user withdraw his money from account
{
	long double WithdrawAmount = 0;
	string temp_user, temp_pass;
	long double  temp_amount, res;

	fstream temp_data("temp_data.txt", ios::out);
	fstream data_file("data.txt", ios::in);
	// Use temp_data to edit in data

	cout << " Enter Withdraw Amount : ";

	while (data_file >> temp_user >> temp_pass >> temp_amount)
	{
		if (temp_user == f_user && temp_pass == f_pass)
		{
			do
			{
				cin >> WithdrawAmount;
				cout << endl;

				if (WithdrawAmount > temp_amount)  //To check if the withdrawn amount <= user amount 
				{
					cout << "     Withdraw Amount is greater than your amount " << endl << endl;
					cout << " please Enter Withdraw Amount again : ";
				}
				else
				{
					temp_data << temp_user << endl;
					temp_data << temp_pass << endl;
					res = temp_amount - WithdrawAmount;
					temp_data << res << endl;
					cout << "your Amount is : " << res << endl << endl;
				}
			} while (WithdrawAmount > temp_amount);
		}
		else    //Keeps the other accounts with no change
		{
			temp_data << temp_user << endl;
			temp_data << temp_pass << endl;
			temp_data << temp_amount << endl;
		}
	}
	temp_data.close();
	data_file.close();

	temp_data.open("temp_data.txt");
	data_file.open("data.txt");

	while (temp_data >> temp_user >> temp_pass >> temp_amount)  //Transfer data from temp_data to data_file
	{
		data_file << temp_user << endl;
		data_file << temp_pass << endl;
		data_file << temp_amount << endl;
	}
	data_file.close();
	temp_data.close();
}

void Amount(string f_user, string f_pass)   //This function displays the user's amount of money available
{
	fstream data_file("data.txt", ios::in);

	string temp_user, temp_pass;
	long double  temp_amount;

	while (data_file >> temp_user >> temp_pass >> temp_amount)
	{
		if (temp_user == f_user && temp_pass == f_pass)    //To search in file for the correct account
		{
			cout << "your Amount is : " << temp_amount << endl << endl;
		}
	}
	data_file.close();
}

void data(string f_user, string f_pass)  //This function displays the user's data
{
	fstream data_file("data.txt", ios::in);

	string temp_user, temp_pass;
	long double  temp_amount;

	while (data_file >> temp_user >> temp_pass >> temp_amount)
	{
		if (temp_user == f_user && temp_pass == f_pass)   //To search in file for the correct account
		{
			cout << "userName is : " << temp_user << endl << endl;
			cout << "pass is : " << temp_pass << endl << endl;
			cout << "your Amount is : " << temp_amount << endl << endl;
		}
	}
	data_file.close();
}

void edit(string f_user, string f_pass)        //This function edits the user's password
{
	string temp_user, temp_pass, old_pass, new_pass;
	long double  temp_amount;

	fstream temp_data("temp_data.txt", ios::out);
	fstream data_file("data.txt", ios::in);

	cout << " Enter your old password : ";
	do
	{
		cin >> old_pass;
		cout << endl;

		if (old_pass != f_pass)  //To check if the data written by user = saved data in file
		{
			cout << "     **Wrong password** " << endl << endl;
			cout << " please Enter your password again : ";
		}

	} while (old_pass != f_pass);

	while (data_file >> temp_user >> temp_pass >> temp_amount)
	{

		if (temp_user == f_user && temp_pass == f_pass && old_pass == f_pass)  //To search in file for the correct account
		{
			temp_data << temp_user << endl;

			cout << " Enter New password : ";
			cin >> new_pass;
			cout << endl;

			temp_pass = new_pass;
			temp_data << temp_pass << endl;
			temp_data << temp_amount << endl;

			cout << " Your new password is : " << temp_pass << endl << endl;
		}
		else   //Keeps the other accounts with no change
		{
			temp_data << temp_user << endl;
			temp_data << temp_pass << endl;
			temp_data << temp_amount << endl;
		}
	}


	temp_data.close();
	data_file.close();

	temp_data.open("temp_data.txt");
	data_file.open("data.txt");

	while (temp_data >> temp_user >> temp_pass >> temp_amount)  //Transfer data from temp_data to data_file
	{
		data_file << temp_user << endl;
		data_file << temp_pass << endl;
		data_file << temp_amount << endl;
	}
	data_file.close();
	temp_data.close();

}

void delete_user(string f_user, string f_pass)   //This function deletes all the user's information
{
	string temp_user, temp_pass;
	long double  temp_amount;

	fstream temp_data1("temp_data.txt", ios::app);
	fstream data_file1("data.txt", ios::app);
	data_file1.close();
	temp_data1.close();

	fstream temp_data("temp_data.txt", ios::out);
	fstream data_file("data.txt", ios::in);

	while (data_file >> temp_user >> temp_pass >> temp_amount)
	{
		if (temp_user == f_user && temp_pass == f_pass)  //To search in file for the correct account
		{
			temp_user = "none";
			temp_pass = "none";
			temp_amount = 1;
			temp_data << temp_user << endl;
			temp_data << temp_pass << endl;
			temp_data << temp_amount << endl;
		}
		else   //Keeps the other accounts with no change
		{
			temp_data << temp_user << endl;
			temp_data << temp_pass << endl;
			temp_data << temp_amount << endl;
		}
	}
	temp_data.close();
	data_file.close();

	temp_data.open("temp_data.txt");
	data_file.open("data.txt");

	while (temp_data >> temp_user >> temp_pass >> temp_amount)  //Transfer data from temp_data to data_file
	{
		data_file << temp_user << endl;
		data_file << temp_pass << endl;
		data_file << temp_amount << endl;
	}
	data_file.close();
	temp_data.close();
}