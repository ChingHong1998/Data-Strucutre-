#include<iostream>
#include<cstdlib>
#include <fstream>
#include "wallet.cpp"

void display_menu();
void check_account(Wallet *wallet);

Wallet *w1;


int main() {
    ifstream fin;
    fin.open("Wallet.txt",ios::in);
    if(is_emptyf(fin)) {
        ofstream fout;
        fout.open("Wallet.txt",ios::app);
        cout<< "Create a wallet.\nEnter your username: ";
        string username;
        cin >> username;
        cout << "Enter your balance in your wallet: ";
        double balance;
        cin>> balance;
        cout<< "Enter your budget(It will show warning message when your balance below budget): ";
        double budget;
        cin >> budget;
        cout << "Currency Available:\n 1.Malaysia(RM)\n 2.Singapore(SGD)\n 3.China(RMB)\n 4.Thailand(Baht)\n";
        string currency;
        cout <<"Enter your currency unit: ";
        int unit;
        cin >> unit;
        switch(unit)
        {
        case 1:
            currency = "RM ";
            break;
        case 2:
            currency = "SGD ";
            break;
        case 3:
            currency = "RMB ";
            break;
        case 4:
            currency = "Baht ";
            break;
        default:
            cout <<" Please choose from the available option: " <<endl;
        }
        w1 = new Wallet(username,balance,budget,currency);
        fout << "Username: "<< username <<endl;
        fout << "Balance: " << balance <<endl;
        fout << "Budget: " << w1->getBudget() << endl;
        fout << "Currency: " << currency <<endl;
        fout.close();
    }
    else {
        string username = "";
        string balance="";
        string budget = "";
        string currency = "";
        while(!fin.eof()&& (fin.good()))
        {
            string temp;
            getline(fin,temp);
            for(int i = 10; i< temp.length(); i++) {
                username += temp[i];
            }
            getline(fin,temp);
            for(int i = 9; i< temp.length(); i++) {
                balance += temp[i];
            }
            getline(fin,temp);
            for(int i = 8; i< temp.length(); i++) {
                budget += temp[i];
            }
            getline(fin,temp);
            for(int i = 10; i< temp.length(); i++) {
                currency += temp[i];
            }
        }
        w1 = new Wallet(username,toDouble(balance),toDouble(budget),currency);
    }
    fin.close();
    display_menu();
}

void display_menu() {
    ifstream fin;
    fin.open("expenses.txt", ios::in);
    ifstream fin2;
    fin2.open("incomes.txt", ios::in);
    system("CLS");
    cout << "Welcome to Personal Wallet.\n"<<w1->displayUsername()<<" current balance is "<< w1->getCurrency() <<" "<<w1->displayBalance() <<endl;
    w1->warning();
    cout << "Menu: \n 1. Add Expense. \n 2. Add Income \n 3. Display Expense \n 4. Display Income \n 5. Delete Expense \n";
    cout << " 6. Display all Expenses \n 7. Edit Expense\n 8. Show summary\nEnter Your choice: ";
    int option;
    cin>> option;
    switch(option) {
    case 1:
        w1->addExpense();
        break;
    case 2:
        w1->addIncome();
        break;
    case 3:
        w1->display_record(fin);
        break;
    case 4:
        w1->display_record(fin2);
        break;
    case 5: {
        string date;
        cout<<"Enter the date in [DDMMYY] form: ";
        cin>>date;
        w1->deleteExpense(date,fin);
        break;
    }
    case 6:
        w1->display_all_expenses();
        break;
    case 7: {
        string date;
        cout<<"Enter the date in [DDMMYY] form: ";
        cin.get();
        getline(cin,date);
        fin.close();
        w1->editExpense(date);
        break;
    }
    case 8:
        w1->displaySummary();
        break;
    default:
        cout << "\nInvalid option."<<endl;
    }
}

void check_account(Wallet *wallet) {

}



