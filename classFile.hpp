//
//  classFile.hpp
//  LoginRegistration
//
//  Created by Antonij Simonovski on 10/24/21.
//

#ifndef classFile_hpp
#define classFile_hpp
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

class bankAccount
{
private:
    float balance;
    string firstName, lastName, accountNumber, bDay, password;
    void setBalance(int val, string username)
    {
        string line, fileName;
        balance+=val;
        if( remove((username + ".txt").c_str()) != 0 )
            perror( "Error deleting file" );
          else
            puts( "File successfully deleted" );
        ofstream accountFile(username + ".txt", ios::app);
        accountFile << password << endl;
        accountFile << firstName << endl;
        accountFile << lastName << endl;
        accountFile << bDay << endl;
        accountFile << accountNumber << endl;
        accountFile << balance << endl;
        accountFile.close();
    }//end setBalance
    
public:
    bool testUsername(string username)
    {
        fstream accountFile(username + ".txt");
        if (accountFile.is_open())
        {
            accountFile.close();
            return true;
        }
        return false; 
    }
    void getInfo(string username)
    {
        string line;
        int count = 0;
        fstream accountFile(username + ".txt");
        
        while( getline( accountFile, line ) )
        {
            if(count == 0) password = line;
            if(count == 1) firstName = line;
            if(count == 2) lastName = line;
            if(count == 3) bDay = line;
            if(count == 4) accountNumber = line;
            if(count == 5) balance = stoi( line );
            count++;
            };// end while
        accountFile.close();
    } // end getInfo
    void printBalance()
    {
        cout << "Your balance is: $" << balance <<endl;
    } // end printBalance
    
    void deposit(string username)
    {
        cout << "Insert the amount you want to deposit: $";
        float val;
        cin >> val;
        setBalance(val, username);
        cout << "Your new balance is: $" << balance << endl;
    } // end deposit
    
    void withdraw(string username)
    {
        float val;
        do{
        cout << "Insert the amount you want to withdraw: $";
        cin >> val;
        if(val > balance) cout << "Insufficient funds. Please try again.";
        } while(val > balance);
        val *= -1;
        setBalance(val, username);
        cout << "Your new balance is: $" << balance << endl;
    }// end withdraw
    
};//end bank account

    

#endif /* classFile_hpp */
