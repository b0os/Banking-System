#include <iostream>
#include <regex>
#include "sqlite/sqlite3.h"

using namespace std;

class Client{

private:
    string name;
    string address;
    string phone;

public:
    static bool checkValidNum(string num);
    Client() : name("client"), address("Un-known"), phone("01000000000"){}; // default constructor

    Client(string nm, string adr, string ph);

    // setters
    void setName(string nm);
    void setAddress(string adr);
    void setPhone(string ph);


};


bool Client::checkValidNum(string num) {
    regex validNum("01[0125][0-9]{8}");
    return regex_match(num,validNum);

}

Client::Client(string nm, string adr, string ph) {

    // should check regex of number and then set the values
    bool isValid = checkValidNum(ph);
    if(isValid)
    {
        // set the values to the variables
        name = nm;
        address = adr;
        phone = ph;

    } else {
        cout << "invalid phone nubmer";
        exit(0);
    }

}


void Client::setName(string nm) {
    name = nm;
}
void Client::setAddress(string adr) {
    address = adr;
}
void Client::setPhone(string ph) {
    phone = ph;
}


class BankAccount{
protected:
    string ID;
    double balance;
    static int counter;
public:

    BankAccount(){
        this->balance = 0;
    } // default
    BankAccount(double bal){
        this->balance = bal;

    }

    string getID(){
        return ID;
    }
    void init(double bal) {
        balance = bal;
    }
    int getBal() {
        return this->balance;
    }

    void withdraw(double amount)
    {
        balance -= amount;
    }
    void deposite(double amount)
    {
        balance += amount;
    }
};
class SavingBankAccount : public BankAccount{
private:
    static double minimumBalance;
public:

    SavingBankAccount() {};
    SavingBankAccount(double bal) : BankAccount(bal) {
        this->balance = bal;
    }

    void init(double bal) {
        balance = bal;
    }

    int getBal() {
        return this->balance;
    }

    void withdraw(double amount)
    {
        if (amount < balance && amount > 0 && balance-amount >= minimumBalance)
        {
            balance -= amount;
        }
    }
    void deposite(double amount)
    {
        if (amount >= 100)
        {
            balance += amount;
        }
    }
};
int BankAccount::counter = 1;
double SavingBankAccount::minimumBalance = 1000;


// header
class BankApplication {

public:
    BankApplication();

};

// cpp
BankApplication ::BankApplication() {
    string name, ph, type, zeros, sql, id, idNum, sql2, currentType, typeo;
    char addr[90];
    sqlite3_stmt *stmt, *stmt2;
    char *msgErr;
    int tp, choise, count = 0, ch, startBl = 0, idC = 1, len, withDraw, deposit;

    Client user;
    // declare account type
    BankAccount bUser;
    SavingBankAccount sUser;
    // open database
    sqlite3 *db;
    sqlite3_open("Db.db", &db);

    do {
        cout << " Welcome to FCAI Banking Application \n"
                "1. Create a New Account \n"
                "2. List Clients and Accounts\n"
                "3. Withdraw Money \n"
                "4. Deposit Money\n"
                "5. Exit\n"
                "Please enter your choose:";
        cin >> choise;
        switch (choise) {

            // create a new account
            case 1:

                cout << "\nPlease Enter Client Name : ";
                cin >> name;
                // set name value to the client object
                user.setName(name);

                do {
                    if (count >= 1) {
                        cout << "\nPlease Enter VALID Client Phone : ";
                        cin >> ph;
                    } else {
                        cout << "\nPlease Enter Client Phone : ";
                        cin >> ph;
                        count++;
                    }
                } while (!Client::checkValidNum(ph));

                // set number value of the object
                user.setPhone(ph);

                cout << "\nPlease Enter Client Address :";

                cin.ignore();
                cin.getline(addr, 90, '\n');

                // set address value of the object
                user.setAddress(addr);

                do {
                    cout << "\nWhat Type of Account Do You Like? (1) Basic (2) Saving";
                    cin >> tp;
                } while (tp < 1 || tp > 2);

                do {
                    cout << "\nPlease Enter the Starting Balance:";
                    cin >> startBl;
                } while (startBl < 0);

                // Select account type from the input ... Basic or Saving
                type = (tp == 1) ? "Basic" : "Saving";


                // insert values into the database
                sql = "INSERT INTO CLIENTS (NAME, ADDRESS, PHONE, TYPE, BALANCE) "
                      "VALUES('" + name + "', '" + addr + "', '" + ph + "', '" + type + "',"
                                                                                        "'" + to_string(startBl) +
                      "');";

                int maxId;
                ch = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &msgErr);

                if (ch != SQLITE_OK) {
                    cerr << "error insert client" << endl;
                    sqlite3_free(msgErr);
                } else {
                    // will return the last id inserted in the table
                    sql = "SELECT max(ID) FROM CLIENTS;";
                    sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, nullptr);
                    sqlite3_step(stmt);
                    maxId = sqlite3_column_int(stmt, 0);

                    // add zeros left to the number ... 001 010 100 002
                    len = to_string(maxId).length();
                    while (len < 3) {
                        zeros += "0";
                        len++;
                    }
                    zeros += to_string(maxId);


                    cout << "An account was created with ID FCAI-" << zeros << ""
                                                                               " and starting Balance " << startBl
                         << " L.E.";
                    sqlite3_close(db);
                }
                break;


                // list of clients And accounts
            case 2:

                sql = "SELECT * FROM CLIENTS;";
                sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);


                while (sqlite3_step(stmt) == SQLITE_ROW) {
                    sql = "SELECT ID FROM CLIENTS WHERE ID == ?;";
                    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt2, nullptr);
                    sqlite3_bind_int(stmt2, 1, idC);
                    sqlite3_step(stmt2);
                    tp = sqlite3_column_int(stmt2, 0);

                    id = to_string(tp);
                    len = (int) id.length();
                    while (len < 3) {
                        zeros += "0";
                        len++;
                    }
                    zeros += id;


                    printf("-------%s-------\nAddress: %s\nPhone: %s\nAccount ID: FCAI-%s  (%s)\n"
                           "Balance: %d L.E.\n", sqlite3_column_text(stmt, 1), sqlite3_column_text(stmt, 2),
                           sqlite3_column_text(stmt, 3), zeros.c_str(), sqlite3_column_text(stmt, 4),
                           sqlite3_column_int(stmt, 5));

                    // empty the zeros variable
                    zeros = "";
                    idC++;
                }
                sqlite3_close(db);
                break;

                // Withdraw
            case 3 :
                id = "";
                cout << "Please Enter Account ID (e.g., FCAI-015):";
                cin >> id;

                // add the last three characters into a string then convert it to int
                idNum = id[5];
                idNum += id[6];
                idNum += id[7];

                // number of the id in the database
                idC = stoi(idNum);

                sql = "SELECT TYPE,BALANCE FROM CLIENTS WHERE ID == '" + to_string(idC) + "';";

                sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
                sqlite3_step(stmt);

                // to know if the id exists in the database or not ... will return 1 if exists , 0 if not
                sql2 = "SELECT COUNT(*) FROM CLIENTS WHERE ID == '" + to_string(idC) + "';";
                sqlite3_prepare_v2(db, sql2.c_str(), -1, &stmt2, nullptr);
                sqlite3_step(stmt2);
                ch = sqlite3_column_int(stmt2, 0);


                if (ch == 0) {
                    cerr << "Error.. There is no such ID in the system\n";
                } else {

                    // set value of the stored balance in the database
                    startBl = sqlite3_column_int(stmt, 1);
                    cout << "Account ID: " << id << "\nAcocunt Type: " << sqlite3_column_text(stmt, 0)
                         << "\nBalance: " << startBl;


                    if (sqlite3_column_text(stmt, 0)[0] == 'B') {
                        currentType = "Basic";
                        bUser.init(startBl);
                    } else if (sqlite3_column_text(stmt, 0)[0] == 'S') {
                        currentType = "Saving";
                        sUser.init(startBl);
                    }


                    do {
                        cout << "\nPlease Enter The Amount to Withdraw:";
                        cin >> withDraw;
                        if (withDraw > startBl) {
                            cout << "\n\"Sorry. This is more than what you can withdraw.\"";
                        } else if (currentType == "Saving" && startBl - withDraw < 1000) {
                            cout << "\n\"Sorry. You Cant withdraw this amount \n"
                                    "because your balance will reach the minimum\"\n";
                        } else {

                            if (currentType == "Basic") {
                                bUser.withdraw(withDraw);
                                cout << "Thank you.\nAccount ID: " << id << "\nNew Balance: " << bUser.getBal();

                                // update the new balance to the database
                                sql = "UPDATE CLIENTS SET BALANCE = '" + to_string(bUser.getBal()) + "' "
                                                                                                     "WHERE ID == '" +
                                      to_string(idC) + "';";

                            } else if (currentType == "Saving") {


                                sUser.withdraw(withDraw);
                                cout << "Thank you.\nAccount ID: " << id << "\nNew Balance: " << sUser.getBal();

                                // update the new balance to the database
                                sql = "UPDATE CLIENTS SET BALANCE = '" + to_string(sUser.getBal()) + "' "
                                                                                                     "WHERE ID == '" +
                                      to_string(idC) + "';";

                            }

                            sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
                        }
                    } while (withDraw > startBl || (currentType == "Saving" && startBl - withDraw < 1000));

                }

                break;

                // deposit
            case 4:
                cout << "Please Enter Account ID (e.g., FCAI-015):";
                cin >> id;

                // add the last three characters into a string then convert it to int
                idNum = id[5];
                idNum += id[6];
                idNum += id[7];

                // number of the id in the database
                idC = stoi(idNum);

                sql = "SELECT TYPE,BALANCE FROM CLIENTS WHERE ID == '" + to_string(idC) + "';";

                sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
                sqlite3_step(stmt);

                // to know if the id exists in the database or not ... will return 1 if exists , 0 if not
                sql2 = "SELECT COUNT(*) FROM CLIENTS WHERE ID == '" + to_string(idC) + "';";
                sqlite3_prepare_v2(db, sql2.c_str(), -1, &stmt2, nullptr);
                sqlite3_step(stmt2);
                ch = sqlite3_column_int(stmt2, 0);


                if (ch == 0) {
                    cerr << "Error.. There is no such ID in the system\n";
                } else {

                    // set value of the stored balance in the database
                    startBl = sqlite3_column_int(stmt, 1);
                    cout << "Account ID: " << id << "\nAcocunt Type: " << sqlite3_column_text(stmt, 0)
                         << "\nBalance: " << startBl;


                    if (sqlite3_column_text(stmt, 0)[0] == 'B') {
                        currentType = "Basic";
                        bUser.init(startBl);
                    } else if (sqlite3_column_text(stmt, 0)[0] == 'S') {
                        currentType = "Saving";
                        sUser.init(startBl);
                    }

                    do {
                        cout << "\nPlease Enter The Amount to Deposit";
                        cin >> deposit;

                        if (currentType == "Saving" && deposit < 100) {
                            cout << "\n\"Sorry. You cant deposit amount less than 100 L.E.\"\n";
                        } else {

                            if (currentType == "Basic") {
                                bUser.deposite(deposit);

                                cout << "Thank you.\nAccount ID: " << id << "\nNew Balance: " << bUser.getBal();

                                // update the new balance to the database
                                sql = "UPDATE CLIENTS SET BALANCE = '" + to_string(bUser.getBal()) + "' "
                                                                                                     "WHERE ID == '" +
                                      to_string(idC) + "';";

                            } else if (currentType == "Saving") {

                                sUser.deposite(deposit);

                                cout << "Thank you.\nAccount ID: " << id << "\nNew Balance: " << sUser.getBal();

                                // update the new balance to the database
                                sql = "UPDATE CLIENTS SET BALANCE = '" + to_string(sUser.getBal()) + "' "
                                                                                                     "WHERE ID == '" +
                                      to_string(idC) + "';";

                            }

                        }
                        sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
                    } while (currentType == "Saving" && deposit < 100);

                    break;
                    default:
                        break;

                }
        }
        cout << "\nDo you want another process? 1- Yah , 2- No";
        cin >> ch;
        if(ch == 1) {
            continue;
        } else {
            exit(0);
        }

    } while (choise != 5);

}

int main() {

    BankApplication a;

    return 0;
}
