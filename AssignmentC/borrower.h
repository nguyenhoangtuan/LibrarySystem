#ifndef BORROWER_H
#define BORROWER_H
#include <string>
#include <vector>

using namespace std;

class Borrower
{
public:
    Borrower();

    Borrower(string name,
    string type,
    string department,
    string mobileNumber,
    int itemBorr,
    int itemLate);

    Borrower(int id,string name,
    string type,
    string department,
    string mobileNumber,
    int itemBorr,
    int itemLate);

    Borrower(int id,string name,
    string type,
    string department,
    string mobileNumber,
    int itemBorr,
    int itemLate,
    string itemString);

    int getId() const;
    void setId(int value);

    string getName() const;
    void setName(const string &value);

    string getType() const;
    void setType(const string &value);

    string getDepartment() const;
    void setDepartment(const string &value);

    string getMobileNumber() const;
    void setMobileNumber(const string &value);

    int getItemBorr() const;
    void setItemBorr(int value);

    int getItemLate() const;
    void setItemLate(int value);



    vector<int> *getIdItemVector() const;
    void setIdItemVector(vector<int> *value);

    string getItemString() const;
    void setItemString(const string &value);

    void addItem(int id);
    void deleteItem(int id);
    void showItemList();

    static bool before( const Borrower& c1, const Borrower& c2 );
    static bool after( const Borrower& c1, const Borrower& c2 );

private:
    int id;
    string name;
    string type;
    string department;
    string mobileNumber;
    int itemBorr;
    int itemLate;

    vector<int> *idItemVector;
    string itemString;

    static int currentID;
};

#endif // BORROWER_H

//The system must store at least the following information about borrowers:
// ID (unique)
// Name
// Type (student, teacher)
// Department (IT, BCOMM, etc.)
// Mobile number
// Number of items borrowed in the past
// Number of items returned late in the past
