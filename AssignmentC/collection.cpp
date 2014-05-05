#include <string>
#include "collection.h"
#include <vector>
#include "datamodel.h"

Collection::Collection()
{

}

Collection::Collection(string type, string dataType, string title, string version, /*int idenCode,*/ string publisher, int yearRecored, int duration, string category)
    : type (type), dataType(dataType) , title(title), version(version),/* idenCode(idenCode),*/publisher(publisher) ,yearRecored(yearRecored), duration(duration),  category(category)
{
    currentID = currentID + 1;
    id = currentID;
}

Collection::Collection(int id,string type, string dataType, string title, string version, /*int idenCode,*/ string publisher, int yearRecored, int duration, string category)
    :id(id), type (type), dataType(dataType) , title(title), version(version),/* idenCode(idenCode),*/publisher(publisher) ,yearRecored(yearRecored), duration(duration),  category(category)
{
    int max = 0;
    vector<Collection> itemv = DataModel::getCollectionList();
    for(int i = 0; i < itemv.size(); i++) {
        if (max <= ((Collection)itemv[i]).getId() ) {
            max = ((Collection)itemv[i]).getId();
        }
    }
    if (max <= id) {
        max = id;
    }
    currentID = max;
}


int Collection::getId() const
{
    return id;
}

void Collection::setId(int value)
{
    id = value;
}
string Collection::getType() const
{
    return type;
}

void Collection::setType(const string &value)
{
    type = value;
}
string Collection::getDataType() const
{
    return dataType;
}

void Collection::setDataType(const string &value)
{
    dataType = value;
}
string Collection::getTitle() const
{
    return title;
}

void Collection::setTitle(const string &value)
{
    title = value;
}
string Collection::getVersion() const
{
    return version;
}

void Collection::setVersion(const string &value)
{
    version = value;
}
//int Collection::getIdenCode() const
//{
//    return idenCode;
//}

//void Collection::setIdenCode(int value)
//{
//    idenCode = value;
//}
string Collection::getPublisher() const
{
    return publisher;
}

void Collection::setPublisher(const string &value)
{
    publisher = value;
}
int Collection::getYearRecored() const
{
    return yearRecored;
}

void Collection::setYearRecored(int value)
{
    yearRecored = value;
}
int Collection::getDuration() const
{
    return duration;
}

void Collection::setDuration(int value)
{
    duration = value;
}
string Collection::getCategory() const
{
    return category;
}

void Collection::setCategory(const string &value)
{
    category = value;
}

bool Collection::before(const Collection &c1, const Collection &c2)
{
    int o = c1.title.compare(c2.title);
    if (o < 0) {
        return false;
    } else {
        return true;
    }
    //    return c1.title < c2.i;
}

bool Collection::after(const Collection &c1, const Collection &c2)
{

    int i1 = DataModel::findNumberItemOfColl(c1.getId());

    int i2 = DataModel::findNumberItemOfColl(c2.getId());

    return i1 < i2;

}

int Collection::currentID;








