#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "classFile.hpp"
using namespace std;

string registration();
bool checkCredentials(string username, string password);
void createFile(string username, string password);

int main(int argc, const char * argv[]) {

    string uspass, choice,  choice1, firstName, lastName, username, password;
    bankAccount myClass;

    do{
    cout<<"If you already have an account type l to log in, otherwiser type r instead of username to register\n";
    cin>> choice1;
    if(choice1 == "r") username = registration(); // creates acc in credentials
    else if (choice1 == "l"){
        do{
        cout << "Please log in.\n";
        cout << "Username: ";
        cin >> username;
        cout<<"Password: ";
        cin>> password;
        
       if (checkCredentials(username, password))
       {
           cout << "Login successful!\n";
           myClass.getInfo(username);
        }
       else
           cout << "Login failed, please try again\n";
    }while(!checkCredentials(username, password));
    }
    }while(choice1 != "r" && choice1 !="l");
    
    do
    {
        cout << "Press b to view balance, d to deposit money, press w to withdraw money and q to exit"<<endl;
        cin >> choice;
        if(choice == "b") myClass.printBalance();
        else if(choice == "w") myClass.withdraw(username);
        else if(choice == "d") myClass.deposit(username);
    } while(choice != "q");
    return 0;
}//end main

string registration()
{
    string username, password;
    bankAccount myClass;
    do{
        cout<<"Create username: ";
        cin>>username;
        if(myClass.testUsername(username)) cout <<"Username already taken, please try again.\n";
    }while (myClass.testUsername(username));
    
    cout<<"Create password: ";
    cin>>password;
    
    while(password.length() < 7)
    {
        cout << "Please enter a password with 7 characters or more: ";
        cin>>password;
    }
    createFile(username, password);
    return username;
}//end registration

bool checkCredentials(string username, string password)
{
    fstream loginFile(username + ".txt");
    string line;
    getline(loginFile, line);
    if(line == password)
    {
        loginFile.close();
        return true;
    }
    loginFile.close();
    return false;
}// end checkCredentials

void createFile(string username, string password)
{
    string firstName, lastName, bDay;
    string accountNumber;
    cout << "Enter first name: ";
    cin>> firstName;
    cout << "Enter last name: ";
    cin>> lastName;
    fstream accountFile(username + ".txt", ios::app);
    accountFile << password << endl;
    accountFile <<firstName << endl;
    accountFile <<lastName << endl;
    cout << "Enter BirthDay (DD/MM/YY): ";
    cin >> bDay;
    accountFile <<bDay << endl;
    accountNumber = to_string(rand() % 1000000);
    cout << "Your account number is: " << accountNumber << endl;
    accountFile <<accountNumber << endl;
    accountFile.close();
}
