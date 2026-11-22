 
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <stack>
#include <queue>
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>
#include <ctime>
#include <limits>
#include <stdexcept>
#include <cctype>
using namespace std;

// UNIT I: Structure, enum, classes, objects, encapsulation, constructors,
// static members, friend function and operator overloading.
struct DateTime {
    static string now() {
        time_t t = time(nullptr);
        tm *lt = localtime(&t);
        stringstream ss;
        ss << put_time(lt, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
};

enum class TxType { ADD, TRANSFER_IN, TRANSFER_OUT, BILL, RECHARGE };

string typeName(TxType t) {
    switch (t) {
        case TxType::ADD: return "ADD MONEY";
        case TxType::TRANSFER_IN: return "TRANSFER IN";
        case TxType::TRANSFER_OUT: return "TRANSFER OUT";
        case TxType::BILL: return "BILL PAYMENT";
        case TxType::RECHARGE: return "RECHARGE";
    }
    return "UNKNOWN";
}

class User {
    string id, name, phone, pin;
    double balance;
    static int count;
public:
    User() : balance(0) {}
    User(string i, string n, string ph, string p, double b=0)
        : id(i), name(n), phone(ph), pin(p), balance(b) { ++count; }
    string getId() const { return id; }
    string getName() const { return name; }
    string getPhone() const { return phone; }
    double getBalance() const { return balance; }
    bool checkPin(const string& p) const { return pin == p; }
    void setBalance(double b) { balance = b; }
    static int totalUsers() { return count; }
    void display(bool detailed=false) const {
        cout << "\nUser ID: " << id << "\nName: " << name
             << "\nPhone: " << phone << "\nBalance: Rs. "
             << fixed << setprecision(2) << balance;
        if (detailed) cout << "\nAccount: Demo E-Wallet";
        cout << "\n";
    }
    friend ostream& operator<<(ostream& out, const User& u) {
        return out << u.id << " - " << u.name;
    }
};
int User::count = 0;

class Wallet {
    double balance;
public:
    Wallet(double b=0) : balance(b) {}
    double getBalance() const { return balance; }
    void credit(double a) {
        if (a <= 0) throw invalid_argument("Amount must be positive.");
        balance += a;
    }
    void debit(double a) {
        if (a <= 0) throw invalid_argument("Amount must be positive.");
        if (a > balance) throw runtime_error("Insufficient wallet balance.");
        balance -= a;
    }
    Wallet& operator+=(double a) { credit(a); return *this; }
};

class Transaction {
    string id, userId, description, timestamp;
    TxType type;
    double amount;
public:
    Transaction(string i="", string u="", TxType t=TxType::ADD,
                double a=0, string d="", string ts="")
        : id(i), userId(u), description(d), timestamp(ts), type(t), amount(a) {}
    string getId() const { return id; }
    string getUserId() const { return userId; }
    double getAmount() const { return amount; }
    string serialize() const {
        return id+"|"+userId+"|"+to_string((int)type)+"|"+to_string(amount)+"|"+description+"|"+timestamp;
    }
    static Transaction parse(const string& line) {
        stringstream s(line); string i,u,t,a,d,ts;
        getline(s,i,'|'); getline(s,u,'|'); getline(s,t,'|');
        getline(s,a,'|'); getline(s,d,'|'); getline(s,ts);
        return Transaction(i,u,(TxType)stoi(t),stod(a),d,ts);
    }
    void display() const {
        cout << left << setw(9) << id << setw(15) << typeName(type)
             << right << setw(10) << fixed << setprecision(2) << amount
             << "  " << description << "  " << timestamp << "\n";
    }
};

// UNIT II & III: Abstract base class, inheritance, virtual functions,
// overriding and runtime polymorphism.
class Payment {
protected:
    double amount;
public:
    Payment(double a) : amount(a) {}
    virtual bool process(Wallet& w, string& message)=0;
    virtual string name() const=0;
    virtual ~Payment() {}
};
class UpiPayment : public Payment {
    string receiver;
public:
    UpiPayment(double a, string r) : Payment(a), receiver(r) {}
    bool process(Wallet& w, string& m) override {
        try { w.debit(amount); m="UPI payment to "+receiver; return true; }
        catch (exception& e) { m=e.what(); return false; }
    }
    string name() const override { return "UPI Transfer"; }
};
class BillPayment : public Payment {
    string biller;
public:
    BillPayment(double a, string b) : Payment(a), biller(b) {}
    bool process(Wallet& w, string& m) override {
        try { w.debit(amount); m="Bill payment: "+biller; return true; }
        catch (exception& e) { m=e.what(); return false; }
    }
    string name() const override { return "Bill Payment"; }
};
class RechargePayment : public Payment {
    string mobile;
public:
    RechargePayment(double a, string m) : Payment(a), mobile(m) {}
    bool process(Wallet& w, string& msg) override {
        try { w.debit(amount); msg="Recharge: "+mobile; return true; }
        catch (exception& e) { msg=e.what(); return false; }
    }
    string name() const override { return "Mobile Recharge"; }
};

// UNIT IV: User-defined exception and file handling.
class InvalidPin : public runtime_error {
public: InvalidPin() : runtime_error("Incorrect PIN.") {}
};

class EWallet {
    map<string,User> users;                 // UNIT V: map
    map<string,string> pins;
    vector<Transaction> transactions;      // UNIT V: vector
    list<string> recent;                    // UNIT V: list
    stack<string> lastTransactions;         // UNIT V: stack
    queue<string> supportQueue;             // UNIT V: queue
    string loggedIn;
    int userNo=1, txNo=1;

    void load() {
        ifstream in("data/users.txt");
        string line;
        while (getline(in,line)) {
            stringstream s(line); string id,n,ph,pin,b;
            getline(s,id,'|'); getline(s,n,'|'); getline(s,ph,'|');
            getline(s,pin,'|'); getline(s,b);
            if (id.empty()) continue;
            try {
                users.emplace(id,User(id,n,ph,pin,stod(b)));
                pins[id]=pin;
                if (id.size()>1) userNo=max(userNo,stoi(id.substr(1))+1);
            } catch (...) {}
        }
        ifstream tin("data/transactions.txt");
        while (getline(tin,line)) {
            try { transactions.push_back(Transaction::parse(line)); } catch (...) {}
        }
        txNo=(int)transactions.size()+1;
    }
    void saveUsers() {
        ofstream out("data/users.txt",ios::trunc);
        for (auto& p:users) {
            User& u=p.second;
            out << u.getId()<<"|"<<u.getName()<<"|"<<u.getPhone()<<"|"
                <<pins[u.getId()]<<"|"<<fixed<<setprecision(2)<<u.getBalance()<<"\n";
        }
    }
    void record(string uid, TxType t, double amount, string desc) {
        string id="T"+to_string(txNo++);
        Transaction tx(id,uid,t,amount,desc,DateTime::now());
        transactions.push_back(tx);
        ofstream out("data/transactions.txt",ios::app);
        out << tx.serialize() << "\n";
        recent.push_front(id+" "+desc);
        if (recent.size()>8) recent.pop_back();
        lastTransactions.push(id);
    }
    User& current() { return users.at(loggedIn); }
    double amountInput() {
        double a; cout << "Amount (Rs.): ";
        if (!(cin>>a)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); throw invalid_argument("Enter a valid number."); }
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if (a<=0) throw invalid_argument("Amount must be greater than zero.");
        return a;
    }
    void registerUser() {
        string n,ph,p;
        cout<<"Name: "; getline(cin,n);
        cout<<"Phone (10 digits): "; getline(cin,ph);
        cout<<"Create 4-digit PIN: "; getline(cin,p);
        if(n.empty() || ph.size()<10 || p.size()!=4 ||
           !all_of(p.begin(),p.end(),[](unsigned char c){return isdigit(c);}))
            throw invalid_argument("Please enter a name, phone number and 4-digit PIN.");
        int newNumber = userNo++;
        string numberText = to_string(newNumber);
        string id = "U" + string(numberText.size() < 5 ? 5 - numberText.size() : 0, '0') + numberText;
        users.emplace(id,User(id,n,ph,p,0));
        pins[id]=p; saveUsers();
        cout<<"Account created. Your ID is "<<id<<"\n";
    }
    void login() {
        string id,p;
        cout<<"User ID: "; getline(cin,id);
        cout<<"PIN: "; getline(cin,p);
        if(!users.count(id)) throw invalid_argument("User not found.");
        if(pins[id]!=p) throw InvalidPin();
        loggedIn=id; cout<<"Welcome, "<<current().getName()<<"!\n";
    }
    void addMoney() {
        double a=amountInput(); Wallet w(current().getBalance()); w+=a;
        current().setBalance(w.getBalance()); saveUsers();
        record(loggedIn,TxType::ADD,a,"Wallet top-up");
        cout<<"Added successfully. Balance: Rs. "<<w.getBalance()<<"\n";
    }
    void pay(int mode) {
        double a=amountInput(); string detail;
        if(mode==1) cout<<"Recipient UPI ID / user ID: ";
        else if(mode==2) cout<<"Biller name: ";
        else cout<<"Mobile number: ";
        getline(cin,detail);
        Wallet w(current().getBalance());
        unique_ptr<Payment> p;
        if(mode==1 && users.count(detail) && detail!=loggedIn) {
            w.debit(a);
            Wallet recipient(users.at(detail).getBalance()); recipient.credit(a);
            current().setBalance(w.getBalance()); users.at(detail).setBalance(recipient.getBalance());
            saveUsers();
            record(loggedIn,TxType::TRANSFER_OUT,a,"Transfer to "+detail);
            record(detail,TxType::TRANSFER_IN,a,"Transfer from "+loggedIn);
            cout<<"Transfer successful. New balance: Rs. "<<w.getBalance()<<"\n";
            return;
        }
        if(mode==1) p=make_unique<UpiPayment>(a,detail);
        else if(mode==2) p=make_unique<BillPayment>(a,detail);
        else p=make_unique<RechargePayment>(a,detail);
        string message;
        if(!p->process(w,message)) throw runtime_error(message);
        current().setBalance(w.getBalance()); saveUsers();
        record(loggedIn,mode==1?TxType::TRANSFER_OUT:(mode==2?TxType::BILL:TxType::RECHARGE),a,message);
        cout<<p->name()<<" successful. "<<message<<"\nBalance: Rs. "<<w.getBalance()<<"\n";
    }
    void history() {
        bool any=false;
        for(auto it=transactions.rbegin();it!=transactions.rend();++it)
            if(it->getUserId()==loggedIn){it->display();any=true;}
        if(!any) cout<<"No transactions yet.\n";
    }
    void searchTx() {
        string id; cout<<"Transaction ID: "; getline(cin,id);
        auto it=find_if(transactions.begin(),transactions.end(),[&](const Transaction& t){return t.getId()==id && t.getUserId()==loggedIn;});
        if(it==transactions.end()) cout<<"Not found.\n"; else it->display();
    }
    void sortTx() {
        vector<Transaction> own;
        copy_if(transactions.begin(),transactions.end(),back_inserter(own),[&](const Transaction& t){return t.getUserId()==loggedIn;});
        sort(own.begin(),own.end(),[](const Transaction&a,const Transaction&b){return a.getAmount()>b.getAmount();});
        for(auto& t:own)t.display();
        make_heap(own.begin(),own.end(),[](const Transaction&a,const Transaction&b){return a.getAmount()<b.getAmount();});
        if(!own.empty()) cout<<"Highest amount (heap): Rs. "<<own.front().getAmount()<<"\n";
    }
    void dashboard() {
        int c= -1;
        while(c!=0) {
            cout<<"\n--- WALLET DASHBOARD ---\n1.Profile/balance\n2.Add money\n3.Send money\n4.Pay bill\n5.Mobile recharge\n6.Transaction history\n7.Search transaction\n8.Sort transactions\n9.Add support request\n10.Process support request\n11.Stack demo (latest transaction)\n0.Logout\nChoice: ";
            if(!(cin>>c)){cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n');continue;}
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            try {
                switch(c) {
                    case 1: current().display(true); break;
                    case 2: addMoney(); break;
                    case 3: pay(1); break;
                    case 4: pay(2); break;
                    case 5: pay(3); break;
                    case 6: history(); break;
                    case 7: searchTx(); break;
                    case 8: sortTx(); break;
                    case 9:{string q;cout<<"Request: ";getline(cin,q);supportQueue.push(q);cout<<"Queued.\n";break;}
                    case 10: if(supportQueue.empty())cout<<"Queue empty.\n";else{cout<<"Processing: "<<supportQueue.front()<<"\n";supportQueue.pop();}break;
                    case 11: if(lastTransactions.empty())cout<<"Stack empty.\n";else{cout<<"Top transaction: "<<lastTransactions.top()<<" (LIFO)\n";lastTransactions.pop();}break;
                    case 0: loggedIn.clear(); cout<<"Logged out.\n"; break;
                    default: cout<<"Invalid option.\n";
                }
            } catch(exception& e){cout<<"Error: "<<e.what()<<"\n";}
        }
    }
public:
    EWallet(){ load(); }
    void run() {
        int c=-1;
        while(c!=0) {
            cout<<"\n===== DIGITAL E-WALLET =====\n1.Register\n2.Login\n3.Total users\n0.Exit\nChoice: ";
            if(!(cin>>c)){cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n');continue;}
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            try {
                if(c==1) registerUser();
                else if(c==2){login();dashboard();}
                else if(c==3) cout<<"Registered users: "<<users.size()<<"\n";
                else if(c==0) cout<<"Goodbye!\n";
                else cout<<"Invalid option.\n";
            } catch(exception& e){cout<<"Error: "<<e.what()<<"\n";}
        }
        saveUsers();
    }
};

template<typename T>
void showTitle(const T& value) { cout<<"\n==== "<<value<<" ====\n"; }

int main() {
    try {
        EWallet app;
        showTitle("C++17 Mini Project");
        app.run();
    } catch(exception& e) {
        cerr<<"Fatal error: "<<e.what()<<"\n";
        return 1;
    }
    return 0;
}
