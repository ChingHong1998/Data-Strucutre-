#include "Income.h"

Income::Income()
{
    this->ID = createID();
}


void Income::display_category() {
    string categories[5] = {"Others", "Interest", "Commission","Dividend","Salary"};
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

void Income::add_record(double amount, string detail, string category) {
    ofstream fout;
    if(category == "1")
        category = "Salary";
    else if(category == "2")
        category = "Dividend";
    else if(category == "3")
        category = "Commission";
    else if(category == "4")
        category = "Interest";
    else if(category == "5")
        category = "Others";
    fout.open("incomes.txt",ios::app);
    if(fout.good()) {
        fout << getID()<<"\n";
        fout << setTime();
        fout << amount <<"\n";
        fout << category << "\n";
        fout << detail<<"\n";
    }
    cout << "\nSuccess! ";
}

string Income::getID(){
    return this->ID;
}

string Income::createID() {
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
    fin.open("incomes.txt",ios::in);
    string temp,lastDigit,lastID;
    double id1=0;
    int i =0;
    if(is_emptyf(fin)) {
        c = tostr(++counter);
        return id+c;
    }
    else {
        while(getline(fin, temp)) {
            // if lastID equal to temp
            if(temp.substr(0,6) == lastID.substr(0,6)) {
                id1 = toDouble(lastDigit);
                id1+=1;
                counter = id1;
                // update the lastID
                lastID = temp.substr(0,7);
                lastDigit = temp.substr(6,1);
                // skip the next if
                continue;
            }
            if(temp.substr(0,6) == id ) {
                lastID = temp.substr(0,7);
                lastDigit = temp.substr(6,1);
                counter++;
            }

        }
    }
    c = tostr(++counter);
    return id+c;
}

void Income::saveBack(vector <Income> vec) {
    ofstream fout;
    try {
        fout.open("temp.txt",ios::app | ios::out);
        if (fout.bad())
            throw &fout;
        else {
            for(int i = 0; i<vec.size();i++) {
                fout<<vec[i].getID()<<endl;
                fout<<vec[i].getDate()<<endl;
                fout<<vec[i].getAmount()<<endl;
                fout<<vec[i].getCategory()<<endl;
                fout<<vec[i].getDetail()<<endl;
            }
        }
    }catch (ifstream &x) {
        cerr<<"Error occurs when write to the file.";
    }
    fout.close();
    remove("incomes.txt");
    rename("temp.txt", "incomes.txt");
    cout<<"Save successful\n";
}

string Income::getAmount() {return tostr(this->amount);}
string Income::getDate() {return this->date;}
string Income::getDetail() {return this->detail;}
string Income::getCategory() {return this->category;}

void Income::display() {
    cout << "ID: " << getID()<<endl;
    cout << "Date: " << getDate()<<endl;
    cout << "Amount: " << getAmount()<<endl;
    cout << "Category: " << getCategory()<<endl;
    cout << "Detail: " << getDetail()<<endl;
}

void Income::remake(string dt, string a, string cat, string dtl) {
    if(dt != "")
        setDate(dt);
    if(a != "")
        setAmount(a);
    if(cat!= "") {
        if(cat == "1")
            cat = "Salary";
        else if(cat == "2")
            cat = "Dividend";
        else if(cat == "3")
            cat = "Commission";
        else if(cat == "4")
            cat = "Interest";
        else if(cat == "5")
            cat = "Others";
        setCategory(cat);
    }
    if(dtl != "")
        setDetail(dtl);
}
vector <Income> Income::returnExpensesVector() {
            ifstream fin;
            vector<Income> expensesVector;
            expensesVector.clear();
            string temp;
            try {
                fin.open("incomes.txt",ios::in|ios::app);
                if (fin.bad()){
                    throw &fin;
                }else {
                    while((!fin.eof()) && fin.good()) {
                        getline(fin,temp);
                        if(temp == "" || temp == "\n"){
                            break;
                        }
                        Income income;
                        income.setID(temp);
                        getline(fin,temp);
                        income.setDate(temp);
                        getline(fin,temp);
                        income.setAmount(temp);
                        getline(fin,temp);
                        income.setCategory(temp);
                        getline(fin,temp);
                        income.setDetail(temp);
                        expensesVector.push_back(income);
                    }
                cout << "Pushed finished"<<endl;
                }
            }catch (ifstream &x) {
                cerr<<"Error occurs when open the file.";
            }
            fin.close();
            return expensesVector;
}
void Income::setAmount(string amount) {this->amount = toDouble(amount);}
void Income::setDate(string date) {this->date = date;}
void Income::setDetail(string detail) {this->detail = detail;}
void Income::setCategory(string category) {this->category = category;}
void Income::setID(string id) {this->ID = id;}

void Income::merge(vector <Income>& theArray, int first, int mid, int last, int choice ){
    vector <Income> s = returnExpensesVector();
    int first1 = first;
    int last1 = mid;
    int first2 = mid+1;
    int last2 = last;

    int index;
    for(index=first; (first1<=last1) && (first2<=last2);++index) {
        if(choice == 1){
            if(toDouble(theArray[first1].getAmount()) < toDouble(theArray[first2].getAmount())) {
                s[index] = theArray[first1];
                ++first1;
            }
            else {
                s[index] = theArray[first2];
                ++first2;
            }
        }else if(choice == 2){
            if(toDouble(theArray[first1].getAmount()) > toDouble(theArray[first2].getAmount())) {
                s[index] = theArray[first1];
                ++first1;
            }
            else {
                s[index] = theArray[first2];
                ++first2;
            }
        }
    }

    while(first1 <=last1) {
        s[index] = theArray[first1];
        ++first1;
        ++index;
    }

    while(first2<=last2) {
        s[index] = theArray[first2];
        ++first2;
        ++index;
    }

    for(index=first;index<=last;++index){
        theArray[index] = s[index];
    }
}

void Income::mergeSort(vector <Income> &theArray, int first, int last, int choice){
   if(first < last) {
        int mid = (first+last)/2;
        mergeSort(theArray,first,mid,choice);
        mergeSort(theArray, mid + 1, last, choice);
        merge(theArray,first,mid,last,choice);
   }
}

int Income::leftmost(vector <Income> array, int min, int max, int value)
{
    if (min == max){
        return min;
    }
    int mid = (min + max) / 2;

    if (toDouble(array[mid].getAmount()) < value) {
        return leftmost(array, mid + 1, max, value);
    }
    else{
        return leftmost(array, min, mid, value);
    }
}

int Income::rightmost(vector <Income> array, int min, int max, int value)
{
    if (min == max){
        return min;
    }
    int mid = (min + max + 1) / 2;

    if (toDouble(array[mid].getAmount()) > value){
        return rightmost(array, min, mid - 1, value);
    }
    else{
        return rightmost(array, mid, max, value);
    }
}
