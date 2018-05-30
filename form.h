#ifndef FORM
#define FORM
#include<iostream>
#include<string>
using namespace std;
//data container
class Identity{
public:
    string IdName;
    string FullName;
    string Address;
    int Semester;
    int year;
    float Currgrade;
    bool status;
    string email;
    string callnum;
    //operator overload
    bool operator==(const Identity &secondary)const{
        return this->IdName == secondary.IdName;
    }
    bool operator>(const Identity &secondary)const{
        return this->IdName > secondary.IdName;
    }
    bool operator<(const Identity &secondary)const{
        return this->IdName < secondary.IdName;
    }
    bool operator>=(const Identity &secondary)const{
        return this->IdName >= secondary.IdName;
    }
    bool operator<=(const Identity &secondary)const{
        return this->IdName <= secondary.IdName;
    }
    bool isempty(){
        return this->IdName.empty();
    }
    Identity operator=(const Identity &secondary){
        this->IdName=secondary.IdName;
        this->FullName=secondary.FullName;
        this->Address=secondary.Address;
        this->Semester=secondary.Semester;
        this->year=secondary.year;
        this->Currgrade=secondary.Currgrade;
        this->status=secondary.status;
        this->email=secondary.email;
        this->callnum=secondary.callnum;
        return *this;
    }
};

#endif
