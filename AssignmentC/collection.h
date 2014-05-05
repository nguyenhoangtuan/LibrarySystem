#ifndef COLLECTION_H
#define COLLECTION_H

#include <string>
//#include <string.h>

using namespace std;

class Collection
{
public:
    Collection();

    Collection(
    string type,
    string dataType,
    string title,
    string version,
//    int idenCode,
    string publisher,
    int yearRecored,
    int duration,
    string category);

    Collection(int id,
    string type,
    string dataType,
    string title,
    string version,
    string publisher,
    int yearRecored,
    int duration,
    string category);


    int getId() const;
    void setId(int value);

    string getType() const;
    void setType(const string &value);

    string getDataType() const;
    void setDataType(const string &value);

    string getTitle() const;
    void setTitle(const string &value);

    string getVersion() const;
    void setVersion(const string &value);

//    int getIdenCode() const;
//    void setIdenCode(int value);

    string getPublisher() const;
    void setPublisher(const string &value);

    int getYearRecored() const;
    void setYearRecored(int value);

    int getDuration() const;
    void setDuration(int value);

    string getCategory() const;
    void setCategory(const string &value);

    static bool before( const Collection& c1, const Collection& c2 );
    static bool after( const Collection& c1, const Collection& c2 );


private:
    int id;
    string type;
    string dataType;
    string title;
    string version;

    string publisher;
    int yearRecored;
    int duration; // minutes
    string category;

    static int currentID;

};

#endif
// COLLECTION_H
//Type (CD/DVD/……..)
// Data type (images / audio/video….)
// Title
// Version
// Identification code (must be unique)
// Publisher
// Year of recorded/burned
// Duration (running time in minutes)
// Category (Engineering and Technology, History, Film and media studies,
