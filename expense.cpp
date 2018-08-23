#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include "expense.hpp"
#include "stack.cpp"

using namespace std;



template <typename T> string tostr(const T& t) {
   ostringstream os;
   os<<t;
   return os.str();
}

string to2digit(string s) {
    if(s.length() < 2) {
        return ("0" + s);
    }
    else
        return s;
}

double toDouble(string s) {
    stringstream ss(s);
    double result;
    ss >> result;
    return result;
}

string setTime()
{
    time_t now = time(0);
    char* dt = ctime(&now);
    return dt;
}
bool is_emptyf(ifstream& pFile)
{
    return pFile.peek() == ifstream::traits_type::eof();
}

Expense::Expense() {
    this->ID = createID();
}
Expense::~Expense() {}

string Expense::getID() {
    return this->ID;
}

void Expense::setID(string id) {this->ID = id;}
void Expense::setAmount(string amount) {this->amount = toDouble(amount);}
void Expense::setDate(string date) {this->date = date;}
void Expense::setDetail(string detail) {this->detail = detail;}
void Expense::setCategory(string category) {this->category = category;}

void Expense::add_record(double amount, string detail, string category) {
    ofstream fout;
    if(category == "1")
        category = "Food";
    else if(category == "2")
        category = "Transport";
    else if(category == "3")
        category = "Clothes";
    else if(category == "4")
        category = "Accommodation";
    else if(category == "5")
        category = "Others";
    fout.open("expenses.txt",ios::app);
    if(fout.good()) {
        fout << getID()<<"\n";
        fout << setTime();
        fout << amount <<"\n";
        fout << category << "\n";
        fout << detail<<"\n";
    }
    cout << "\nSuccess! ";
}

void Expense::remove_record(string id) {

}

void Expense::display_category() {
    string categories[5] = {"Others", "Accommodation", "Clothes","Transport","Food"};
    Stack aStack;
    for(int i = 0; i<5;i++) {
        aStack.push(categories[i]);
    }
    string display;
    int i= 0;
    while(!aStack.isEmpty()) {
        aStack.pop(display);
        cout <<'\t'<< ++i <<". "<<display<<endl;
    }
}

string Expense::createID() {
    // create id using date
    time_t now = time(0);
    tm *ltm = localtime(&now);
    float year = 1900 + ltm->tm_year - 2000;
    float month = 1 + ltm->tm_mon;
    float day = ltm->tm_mday;
    string y = tostr(year);
    string m = to2digit(tostr(month));
    string d = to2digit(tostr(day));
    string id = d+m+y;
    int counter = 0;
    string c ;
    //check date in file
    ifstream fin;
    fin.open("expenses.txt",ios::in);
    string temp;
    int i =0;
    if(is_emptyf(fin)) {
        c = tostr(++counter);
        return id+c;
    }
    else {
        while(getline(fin, temp)) {
            if(temp.substr(0,6) == id ) {
                counter++;
            }
        }
    }
    c = tostr(++counter);
    return id+c;
}

