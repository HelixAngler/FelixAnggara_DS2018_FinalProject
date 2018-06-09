#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<iomanip>
#include<map>
#include <queue>
#include<utility>
#include <dirent.h>
#include<fstream>
#include<sstream>
#include<cctype>
#include "bstemergency.h"
#include "hashing.h"
#include "form.h"
using namespace std;
//Check if the string is float or not
//Credit for Bill the Lizard from Stack Overflow
bool isFloat(string temp){
    istringstream iss(temp);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();
}
//Check if the string is digit
bool isInteger(string temp){
    for(int i;i<temp.length();i++){
        if(temp[i]<'0' || temp[i]>'9'){
            return false;
        }
    }
    return true;
}
//Scan .txt from Data folder
//Credit for Flying Dutchman from forum.codecall.net
queue<string> open() {
    DIR*    dir;
    dirent* pdir;
    queue<string> files;
    system("IF NOT EXIST Data (mkdir Data)");
    string path="./Data";
    dir = opendir(path.c_str());

    while (pdir = readdir(dir)) {
        files.push(pdir->d_name);
    }
    files.pop();
    files.pop();
    return files;
}
void add(map<int,map<string,string>*> &Yr, map<int,map<string,string>*> &Smst, map<string,string> &nameinfo, map<bool,map<string,string>*> &Sts, Hash<Identity> &data, Identity &contain);
void edit(map<int,map<string,string>*> &Yr, map<int,map<string,string>*> &Smst, map<string,string> &nameinfo, map<bool,map<string,string>*> &Sts, Hash<Identity> &data, Identity &contain);
void removing(map<int,map<string,string>*> &Yr, map<int,map<string,string>*> &Smst, map<string,string> &nameinfo, map<bool,map<string,string>*> &Sts, Hash<Identity> &data, Identity &contain);
void browse(map<int,map<string,string>*> &Yr, map<int,map<string,string>*> &Smst, map<string,string> &nameinfo, map<bool,map<string,string>*> &Sts, Hash<Identity> &data, Identity &contain, Identity &emptycontain);

int main(){
    map<int,map<string,string>*> Yr;
    map<int,map<string,string>*> Smst;
    map<bool,map<string,string>*> Sts;
    map<string,string> nameinfo;
    Hash<Identity> Store;
    Identity emptycontainer;
    Identity container;
    emptycontainer.year=0;
    emptycontainer.Semester=0;
    emptycontainer.status=0;
    emptycontainer.Currgrade=0;
    queue<string> f;
    f = open();
    string rd;
    string tempor;
    while(!f.empty()){
        rd = "Data/"+f.front();
        ifstream reading(rd,ios::in);
        if(reading.is_open()){
            if(reading.good()){
                getline(reading,container.IdName,'\n');
                getline(reading,container.FullName,'\n');
                getline(reading,container.Address,'\n');
                getline(reading,tempor,'\n');
                container.Semester=stoi(tempor);
                getline(reading,tempor,'\n');
                container.year=stoi(tempor);
                getline(reading,tempor,'\n');
                container.Currgrade=stof(tempor);
                getline(reading,tempor,'\n');
                container.status=stoi(tempor);
                getline(reading,container.email,'\n');
                getline(reading,container.callnum,'\n');
            }
        }
        else {
            reading.close();
            return 0;
        }
        reading.close();
        if(!(Yr.count(container.year)>0)){
            Yr.insert(make_pair(container.year,new map<string,string>));
        }
        if(!(Smst.count(container.Semester)>0)){
            Smst.insert(make_pair(container.Semester,new map<string,string>));
        }
        if(!(Sts.count(container.status)>0)){
            Sts.insert(make_pair(container.status,new map<string,string>));
        }
        nameinfo.insert(make_pair(container.IdName,container.FullName));
        Yr[container.year]->insert(make_pair(container.IdName,container.FullName));
        Smst[container.Semester]->insert(make_pair(container.IdName,container.FullName));
        Sts[container.status]->insert(make_pair(container.IdName,container.FullName));
        Store.add(container.IdName,container);
        f.pop();
    }
    container.IdName="";
    container.FullName="";
    container.Address="";
    container.Semester=NULL;
    container.year=NULL;
    container.Currgrade=NULL;
    container.status=NULL;
    container.email="";
    container.callnum="";
    int option = 0;
    int navigate;
    bool run = true;
    int availoptions = 4;
    char selected[] = {'>',' ',' ',' ',' '};
    while(run){
        container=emptycontainer;
        system("cls");
        cout<<right<<setw(70)<<"Student Archieve Library"<<endl;
        cout<<endl<<"Choose the following options :"
            <<endl<<selected[0]<<" Add"
            <<endl<<selected[1]<<" Search"
            <<endl<<selected[2]<<" Edit"
            <<endl<<selected[3]<<" Remove"
            <<endl<<selected[4]<<" Exit"
            <<endl;

        navigate=getch();
        if(navigate == 115){
            option+=1;
            if(option > availoptions){
                selected[availoptions] = ' ';
                option = 0;
                selected[option] = '>';
            }
            else{
                selected[option-1] = ' ';
                selected[option] = '>';
            }
        }
        else if(navigate == 119){
            option-=1;
            if(option < 0){
                selected[0] = ' ';
                option = availoptions;
                selected[option] = '>';
            }
            else{
                selected[option+1] = ' ';
                selected[option] = '>';
            }
        }
        else if(navigate == 13){
            switch(option){
                case 0:{
                    add(Yr,Smst,nameinfo,Sts,Store,container);
                    break;
                }
                case 1:{
                    browse(Yr,Smst,nameinfo,Sts,Store,container,emptycontainer);
                    break;
                }
                case 2:{
                    edit(Yr,Smst,nameinfo,Sts,Store,container);
                    break;
                }
                case 3:{
                    removing(Yr,Smst,nameinfo,Sts,Store,container);
                    break;
                }
                case 4:{
                    run = false;
                    break;
                }
            }
        }
    }
}
//Add function with UI
void add(map<int,map<string,string>*> &Yr, map<int,map<string,string>*> &Smst, map<string,string> &nameinfo, map<bool,map<string,string>*> &Sts, Hash<Identity> &data, Identity &contain){
    int option = 0;
    int navigate;
    int availoptions = 10;
    char selected[] = {'>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
    char selectedtf[]= {'>',' '};
    bool run = true;
    int tf = 0;
    string tmpry;
    while(run){
        system("cls");
        cout<<right<<setw(70)<<"Fill The new form"<<endl;

        cout<<"ID Name      :"<<contain.IdName<<endl
            <<"Full Name    :"<<contain.FullName<<endl
            <<"Address      :"<<contain.Address<<endl
            <<"Semester     :"<<contain.Semester<<endl
            <<"Batch        :"<<contain.year<<endl
            <<"Current Grade:"<<contain.Currgrade<<endl
            <<"Status       :"<<contain.status<<endl
            <<"E-Mail       :"<<contain.email<<endl
            <<"Phone Number :"<<contain.callnum<<endl;

        cout<<endl<<"Choose the following options :"
            <<endl<<selected[0]<<" ID Name"
            <<endl<<selected[1]<<" Full Name"
            <<endl<<selected[2]<<" Address"
            <<endl<<selected[3]<<" Semester"
            <<endl<<selected[4]<<" Batch"
            <<endl<<selected[5]<<" Current Grade"
            <<endl<<selected[6]<<" Status"
            <<endl<<selected[7]<<" E-Mail"
            <<endl<<selected[8]<<" Phone Number"
            <<endl<<selected[9]<<" Cancel"
            <<endl<<selected[10]<<" Confirm"
            <<endl;

        navigate = getch();

        if(navigate == 115){
            option+=1;
            if(option > availoptions){
                selected[availoptions] = ' ';
                option = 0;
                selected[option] = '>';
            }
            else{
                selected[option-1] = ' ';
                selected[option] = '>';
            }
        }
        else if(navigate == 119){
            option-=1;
            if(option < 0){
                selected[0] = ' ';
                option = availoptions;
                selected[option] = '>';
            }
            else{
                selected[option+1] = ' ';
                selected[option] = '>';
            }
        }
        else if(navigate == 13){
//==================================================ID Name
            if(option == 0){
                while(true){
                    system("cls");
                    cout<<"New ID Name  :";
                    getline(cin,contain.IdName);
                    if(!data.checkav(contain.IdName,contain)){
                        break;
                    }
                    else{
                        cout<<"Already Exist"<<endl;
                        getch();
                    }
                }
            }
//==================================================Full Name
            else if(option == 1){
                system("cls");
                cout<<"New Full Name  :";
                getline(cin,contain.FullName);
            }
//==================================================Address
            else if(option == 2){
                system("cls");
                cout<<"New Address  :";
                getline(cin,contain.Address);
            }
//==================================================Semester
            else if(option == 3){
                while(true){
                    system("cls");
                    cout<<"Change Semester  :";
                    getline(cin,tmpry);
                    if(isInteger(tmpry) && tmpry.length()<=2 && tmpry.length()>=1){
                        contain.Semester = stoi(tmpry);
                        break;
                    }
                    else{
                        cout<<"Invalid"<<endl;
                        getch();
                    }
                }
            }
//==================================================Year
            else if(option == 4){
                while(true){
                    system("cls");
                    cout<<"Change Batch  :";
                    getline(cin,tmpry);
                    if(isInteger(tmpry) && tmpry.length()<=5 && tmpry.length()>=1){
                        contain.year = stoi(tmpry);
                        break;
                    }
                    else{
                        cout<<"Invalid Year"<<endl;
                        getch();
                    }
                }
            }
//==================================================Current Grade
            else if(option == 5){
                while(true){
                    system("cls");
                    cout<<"Change Current Grade  :";
                    getline(cin,tmpry);
                    if(isFloat(tmpry)){
                        contain.Currgrade = stof(tmpry);
                        break;
                    }
                    else{
                        cout<<"Invalid Value"<<endl;
                        getch();
                    }
                }
            }
//==================================================Status
            else if(option == 6){
                while(true){
                    system("cls");
                    cout<<"Change Status  :";
                    cout<<endl<<selectedtf[0]<<"Active"
                        <<endl<<selectedtf[1]<<"Inactive"
                        <<endl;
                    navigate = getch();
                    if(navigate == 115){
                        tf+=1;
                        if(tf > 1){
                            selectedtf[1] = ' ';
                            tf = 0;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf-1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 119){
                        tf-=1;
                        if(tf < 0){
                            selectedtf[0] = ' ';
                            tf = 1;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf+1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 13){
                        if(tf == 0){
                            contain.status=true;
                        }
                        else{
                            contain.status=false;
                        }
                        selectedtf[0]='>';
                        selectedtf[1]=' ';
                        tf = 0;
                        break;
                    }
                }
            }
//==================================================E-mail
            else if(option == 7){
                system("cls");
                cout<<"New E-Mail  :";
                getline(cin,contain.email);
            }
//==================================================Phone Number
            else if(option == 8){
                while(true){
                    system("cls");
                    cout<<"New Phone Number  :";
                    getline(cin,tmpry);
                    if(isInteger(tmpry)){
                        contain.callnum=tmpry;
                        break;
                    }
                    else{
                        cout<<"Invalid Number"<<endl;
                        getch();
                    }
                }
            }
//==================================================Cancel
            else if(option == 9){
                run = false;
            }
//==================================================Confirm
            else if(option == 10){
                if(contain.IdName!="" && contain.FullName!="" && contain.Address!="" &&
                    contain.Semester>0 && contain.year>0 && contain.Currgrade!=NULL &&
                    contain.email!="" && contain.callnum!="" ){
                        ofstream initiate("Data/"+contain.IdName+".txt");
                        if(initiate.is_open()){
                            data.add(contain.IdName,contain);
                            if(!(Yr.count(contain.year)>0)){
                                Yr.insert(make_pair(contain.year,new map<string,string>));
                            }
                            if(!(Smst.count(contain.Semester)>0)){
                                Smst.insert(make_pair(contain.Semester,new map<string,string>));
                            }
                            if(!(Sts.count(contain.status)>0)){
                                Sts.insert(make_pair(contain.status,new map<string,string>));
                            }
                            nameinfo.insert(make_pair(contain.IdName,contain.FullName));
                            Yr[contain.year]->insert(make_pair(contain.IdName,contain.FullName));
                            Smst[contain.Semester]->insert(make_pair(contain.IdName,contain.FullName));
                            Sts[contain.status]->insert(make_pair(contain.IdName,contain.FullName));
                            initiate<<contain.IdName<<"\n"
                                    <<contain.FullName<<"\n"
                                    <<contain.Address<<"\n"
                                    <<contain.Semester<<"\n"
                                    <<contain.year<<"\n"
                                    <<contain.Currgrade<<"\n"
                                    <<contain.status<<"\n"
                                    <<contain.email<<"\n"
                                    <<contain.callnum<<"\n";
                            initiate.close();
                        }

                        contain.IdName="";
                        contain.FullName="";
                        contain.Address="";
                        contain.Semester=NULL;
                        contain.year=NULL;
                        contain.Currgrade=NULL;
                        contain.status=NULL;
                        contain.email="";
                        contain.callnum="";
                        run = false;
                }
                else{
                    cout<<endl<<"Data Incomplete"<<endl;
                    getch();
                }
            }
        }
    }
}


//Edit function with UI
void edit(map<int,map<string,string>*> &Yr, map<int,map<string,string>*> &Smst, map<string,string> &nameinfo, map<bool,map<string,string>*> &Sts, Hash<Identity> &data, Identity &contain){
    Identity former;
    Identity temporar;
    bool check = true;
    bool run = false;
    bool ok = true;
    int option = 0;
    int navigate;
    int availoptions = 10;
    char selected[] = {'>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
    char selectedtf[]= {'>',' '};
    int tf = 0;
    string tmpry;
    while(check){
        system("cls");
        cout<<"Type the ID Name that want to be edited :";
        getline(cin,contain.IdName);
        former=data.get_thing(contain.IdName,contain);
                while(true){
                    system("cls");
                    cout<<contain.IdName<<endl;
                    cout<<endl<<selectedtf[0]<<"Proceed"
                        <<endl<<selectedtf[1]<<"Cancel"
                        <<endl;
                    navigate = getch();
                    if(navigate == 115){
                        tf+=1;
                        if(tf > 1){
                            selectedtf[1] = ' ';
                            tf = 0;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf-1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 119){
                        tf-=1;
                        if(tf < 0){
                            selectedtf[0] = ' ';
                            tf = 1;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf+1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 13){
                        if(tf == 0){
                            if(former.IdName!=""){
                                contain=former;
                                run = true;
                                check = false;
                            }
                        }
                        else{
                            check=false;
                        }
                        selectedtf[0]='>';
                        selectedtf[1]=' ';
                        tf = 0;
                        break;
                    }
                }

    }
    while(run){
        system("cls");
        cout<<right<<setw(70)<<"Fill The new form"<<endl;

        cout<<"ID Name      :"<<contain.IdName<<endl
            <<"Full Name    :"<<contain.FullName<<endl
            <<"Address      :"<<contain.Address<<endl
            <<"Semester     :"<<contain.Semester<<endl
            <<"Batch        :"<<contain.year<<endl
            <<"Current Grade:"<<contain.Currgrade<<endl
            <<"Status       :"<<contain.status<<endl
            <<"E-Mail       :"<<contain.email<<endl
            <<"Phone Number :"<<contain.callnum<<endl;

        cout<<endl<<"Choose the following options :"
            <<endl<<selected[0]<<" ID Name"
            <<endl<<selected[1]<<" Full Name"
            <<endl<<selected[2]<<" Address"
            <<endl<<selected[3]<<" Semester"
            <<endl<<selected[4]<<" Batch"
            <<endl<<selected[5]<<" Current Grade"
            <<endl<<selected[6]<<" Status"
            <<endl<<selected[7]<<" E-Mail"
            <<endl<<selected[8]<<" Phone Number"
            <<endl<<selected[9]<<" Cancel"
            <<endl<<selected[10]<<" Confirm"
            <<endl;

        navigate = getch();

        if(navigate == 115){
            option+=1;
            if(option > availoptions){
                selected[availoptions] = ' ';
                option = 0;
                selected[option] = '>';
            }
            else{
                selected[option-1] = ' ';
                selected[option] = '>';
            }
        }
        else if(navigate == 119){
            option-=1;
            if(option < 0){
                selected[0] = ' ';
                option = availoptions;
                selected[option] = '>';
            }
            else{
                selected[option+1] = ' ';
                selected[option] = '>';
            }
        }
        else if(navigate == 13){
//==================================================ID Name
            if(option == 0){
                ok = true;
                while(ok){
                    system("cls");
                    cout<<"New ID Name  :";
                    getline(cin,temporar.IdName);

                    while(true){
                    system("cls");
                    cout<<temporar.IdName<<endl;
                    cout<<endl<<selectedtf[0]<<"Proceed"
                        <<endl<<selectedtf[1]<<"Cancel"
                        <<endl;
                    navigate = getch();
                    if(navigate == 115){
                        tf+=1;
                        if(tf > 1){
                            selectedtf[1] = ' ';
                            tf = 0;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf-1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 119){
                        tf-=1;
                        if(tf < 0){
                            selectedtf[0] = ' ';
                            tf = 1;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf+1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 13){
                        if(tf == 0){
                            if(!data.checkav(temporar.IdName,temporar)){
                                contain.IdName=temporar.IdName;
                                ok=false;
                            }
                            else{
                                cout<<"Already Exist"<<endl;
                                getch();
                            }
                        }
                        else{
                            ok=false;
                        }
                        selectedtf[0]='>';
                        selectedtf[1]=' ';
                        tf = 0;
                        break;
                    }
                }

                }
            }
//==================================================Full Name
            else if(option == 1){
                ok = true;
                while(ok){
                    system("cls");
                    cout<<"New Full Name  :";
                    getline(cin,temporar.FullName);
                    while(true){
                    system("cls");
                    cout<<temporar.FullName<<endl;
                    cout<<endl<<selectedtf[0]<<"Proceed"
                        <<endl<<selectedtf[1]<<"Cancel"
                        <<endl;
                    navigate = getch();
                    if(navigate == 115){
                        tf+=1;
                        if(tf > 1){
                            selectedtf[1] = ' ';
                            tf = 0;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf-1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 119){
                        tf-=1;
                        if(tf < 0){
                            selectedtf[0] = ' ';
                            tf = 1;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf+1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 13){
                        if(tf == 0){
                            contain.FullName=temporar.FullName;
                            ok=false;
                        }
                        else{
                            ok=false;
                        }
                        selectedtf[0]='>';
                        selectedtf[1]=' ';
                        tf = 0;
                        break;
                    }
                }
                }
            }
//==================================================Address
            else if(option == 2){
                ok = true;
                while(ok){
                    system("cls");
                    cout<<"New Address  :";
                    getline(cin,temporar.Address);
                    while(true){
                    system("cls");
                    cout<<temporar.Address<<endl;
                    cout<<endl<<selectedtf[0]<<"Proceed"
                        <<endl<<selectedtf[1]<<"Cancel"
                        <<endl;
                    navigate = getch();
                    if(navigate == 115){
                        tf+=1;
                        if(tf > 1){
                            selectedtf[1] = ' ';
                            tf = 0;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf-1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 119){
                        tf-=1;
                        if(tf < 0){
                            selectedtf[0] = ' ';
                            tf = 1;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf+1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 13){
                        if(tf == 0){
                            contain.Address=temporar.Address;
                            ok=false;
                        }
                        else{
                            ok=false;
                        }
                        selectedtf[0]='>';
                        selectedtf[1]=' ';
                        tf = 0;
                        break;
                    }
                }

                }
            }
//==================================================Semester
            else if(option == 3){
                ok = true;
                while(ok){
                    system("cls");
                    cout<<"Change Semester  :";
                    getline(cin,tmpry);
                     while(true){
                    system("cls");
                    cout<<tmpry<<endl;
                    cout<<endl<<selectedtf[0]<<"Proceed"
                        <<endl<<selectedtf[1]<<"Cancel"
                        <<endl;
                    navigate = getch();
                    if(navigate == 115){
                        tf+=1;
                        if(tf > 1){
                            selectedtf[1] = ' ';
                            tf = 0;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf-1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 119){
                        tf-=1;
                        if(tf < 0){
                            selectedtf[0] = ' ';
                            tf = 1;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf+1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 13){
                        if(tf == 0){
                            if(isInteger(tmpry) && tmpry.length()<=2 && tmpry.length()>=1){
                                contain.Semester = stoi(tmpry);
                                ok=false;
                            }
                            else{
                                cout<<"Invalid"<<endl;
                                getch();
                            }

                        }
                        else{
                            ok=false;
                        }
                        selectedtf[0]='>';
                        selectedtf[1]=' ';
                        tf = 0;
                        break;
                    }
                }

                }
            }
//==================================================Year
            else if(option == 4){
                ok = true;
                while(ok){
                    system("cls");
                    cout<<"Change Batch  :";
                    getline(cin,tmpry);
                    while(true){
                    system("cls");
                    cout<<tmpry<<endl;
                    cout<<endl<<selectedtf[0]<<"Proceed"
                        <<endl<<selectedtf[1]<<"Cancel"
                        <<endl;
                    navigate = getch();
                    if(navigate == 115){
                        tf+=1;
                        if(tf > 1){
                            selectedtf[1] = ' ';
                            tf = 0;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf-1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 119){
                        tf-=1;
                        if(tf < 0){
                            selectedtf[0] = ' ';
                            tf = 1;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf+1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 13){
                        if(tf == 0){
                            if(isInteger(tmpry) && tmpry.length()<=5 && tmpry.length()>=1){
                                contain.year = stoi(tmpry);
                                ok=false;
                            }
                            else{
                                cout<<"Invalid Year"<<endl;
                                getch();
                            }

                        }
                        else{
                            ok=false;
                        }
                        selectedtf[0]='>';
                        selectedtf[1]=' ';
                        tf = 0;
                        break;
                    }
                }
                }
            }
//==================================================Current Grade
            else if(option == 5){
                ok = true;
                while(ok){
                    system("cls");
                    cout<<"Change Current Grade  :";
                    getline(cin,tmpry);
                    while(true){
                    system("cls");
                    cout<<tmpry<<endl;
                    cout<<endl<<selectedtf[0]<<"Proceed"
                        <<endl<<selectedtf[1]<<"Cancel"
                        <<endl;
                    navigate = getch();
                    if(navigate == 115){
                        tf+=1;
                        if(tf > 1){
                            selectedtf[1] = ' ';
                            tf = 0;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf-1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 119){
                        tf-=1;
                        if(tf < 0){
                            selectedtf[0] = ' ';
                            tf = 1;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf+1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 13){
                        if(tf == 0){
                            if(isFloat(tmpry)){
                                contain.Currgrade = stof(tmpry);
                                ok=false;
                            }
                            else{
                                cout<<"Invalid Value"<<endl;
                                getch();
                            }

                        }
                        else{
                            ok=false;
                        }
                        selectedtf[0]='>';
                        selectedtf[1]=' ';
                        tf = 0;
                        break;
                    }
                }
                }
            }
//==================================================Status
            else if(option == 6){
                while(true){
                    system("cls");
                    cout<<"Change Status  :";
                    cout<<endl<<selectedtf[0]<<"Active"
                        <<endl<<selectedtf[1]<<"Inactive"
                        <<endl;
                    navigate = getch();
                    if(navigate == 115){
                        tf+=1;
                        if(tf > 1){
                            selectedtf[1] = ' ';
                            tf = 0;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf-1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 119){
                        tf-=1;
                        if(tf < 0){
                            selectedtf[0] = ' ';
                            tf = 1;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf+1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 13){
                        if(tf == 0){
                            contain.status=true;
                        }
                        else{
                            contain.status=false;
                        }
                        selectedtf[0]='>';
                        selectedtf[1]=' ';
                        tf = 0;
                        break;
                    }
                }
            }
//==================================================E-mail
            else if(option == 7){
                ok = true;
                while(ok){
                    system("cls");
                    cout<<"New E-Mail  :";
                    getline(cin,temporar.email);
                    while(true){
                    system("cls");
                    cout<<temporar.email<<endl;
                    cout<<endl<<selectedtf[0]<<"Proceed"
                        <<endl<<selectedtf[1]<<"Cancel"
                        <<endl;
                    navigate = getch();
                    if(navigate == 115){
                        tf+=1;
                        if(tf > 1){
                            selectedtf[1] = ' ';
                            tf = 0;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf-1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 119){
                        tf-=1;
                        if(tf < 0){
                            selectedtf[0] = ' ';
                            tf = 1;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf+1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 13){
                        if(tf == 0){
                            contain.email=temporar.email;
                            ok=false;
                        }
                        else{
                            ok=false;
                        }
                        selectedtf[0]='>';
                        selectedtf[1]=' ';
                        tf = 0;
                        break;
                    }
                }

                }
            }
//==================================================Phone Number
            else if(option == 8){
                ok = true;
                while(ok){
                    system("cls");
                    cout<<"New Phone Number  :";
                    getline(cin,tmpry);
                    while(true){
                    system("cls");
                    cout<<tmpry<<endl;
                    cout<<endl<<selectedtf[0]<<"Proceed"
                        <<endl<<selectedtf[1]<<"Cancel"
                        <<endl;
                    navigate = getch();
                    if(navigate == 115){
                        tf+=1;
                        if(tf > 1){
                            selectedtf[1] = ' ';
                            tf = 0;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf-1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 119){
                        tf-=1;
                        if(tf < 0){
                            selectedtf[0] = ' ';
                            tf = 1;
                            selectedtf[tf] = '>';
                        }
                        else{
                            selectedtf[tf+1] = ' ';
                            selectedtf[tf] = '>';
                        }
                    }
                    else if(navigate == 13){
                        if(tf == 0){
                            if(isInteger(tmpry)){
                                contain.callnum = tmpry;
                                ok=false;
                            }
                            else{
                                cout<<"Invalid Number"<<endl;
                                getch();
                            }

                        }
                        else{
                            ok=false;
                        }
                        selectedtf[0]='>';
                        selectedtf[1]=' ';
                        tf = 0;
                        break;
                    }
                }

                }
            }
//==================================================Cancel
            else if(option == 9){
                run = false;
            }
//==================================================Confirm
            else if(option == 10){
                ;

                if(contain.IdName!="" && contain.FullName!="" && contain.Address!="" &&
                    contain.Semester>0 && contain.year>0 && contain.Currgrade!=NULL &&
                    contain.email!="" && contain.callnum!="" ){

                        ofstream initiate("Data/"+contain.IdName+".txt");
                        if(initiate.is_open()){
                            data.del(former.IdName,former);
                            nameinfo.erase(former.IdName);
                            Yr[former.year]->erase(former.IdName);
                            Smst[former.Semester]->erase(former.IdName);
                            Sts[former.status]->erase(former.IdName);
                            tmpry="del /s "+former.IdName+".txt";
                            system(tmpry.c_str());
                            data.add(contain.IdName,contain);
                            if(!(Yr.count(contain.year)>0)){
                                Yr.insert(make_pair(contain.year,new map<string,string>));
                            }
                            if(!(Smst.count(contain.Semester)>0)){
                                Smst.insert(make_pair(contain.Semester,new map<string,string>));
                            }
                            if(!(Sts.count(contain.status)>0)){
                                Sts.insert(make_pair(contain.status,new map<string,string>));
                            }
                            nameinfo.insert(make_pair(contain.IdName,contain.FullName));
                            Yr[contain.year]->insert(make_pair(contain.IdName,contain.FullName));
                            Smst[contain.Semester]->insert(make_pair(contain.IdName,contain.FullName));
                            Sts[contain.status]->insert(make_pair(contain.IdName,contain.FullName));
                            initiate<<contain.IdName<<"\n"
                                    <<contain.FullName<<"\n"
                                    <<contain.Address<<"\n"
                                    <<contain.Semester<<"\n"
                                    <<contain.year<<"\n"
                                    <<contain.Currgrade<<"\n"
                                    <<contain.status<<"\n"
                                    <<contain.email<<"\n"
                                    <<contain.callnum<<"\n";
                            initiate.close();
                        }

                        contain.IdName="";
                        contain.FullName="";
                        contain.Address="";
                        contain.Semester=NULL;
                        contain.year=NULL;
                        contain.Currgrade=NULL;
                        contain.status=NULL;
                        contain.email="";
                        contain.callnum="";
                        run = false;
                }
            }
        }
    }
}
//Remove function with UI
void removing(map<int,map<string,string>*> &Yr, map<int,map<string,string>*> &Smst, map<string,string> &nameinfo, map<bool,map<string,string>*> &Sts, Hash<Identity> &data, Identity &contain){
    int option = 0;
    int suboption=1;
    int navigate;
    bool run = true;
    bool ok = true;
    bool inside = false;
    int availoptions = 2;
    char selected[] = {'>',' ',' '};
    char selecting[] = {'>',' '};
    while(run){
        system("cls");
        cout<<right<<setw(70)<<"Student Archieve Library"<<endl;
        cout<<endl<<"Selected :"<<contain.IdName
            <<endl<<"Choose the following options :"
            <<endl<<selected[0]<<" Fill The ID Name"
            <<endl<<selected[1]<<" Cancel"
            <<endl<<selected[2]<<" Confirm"
            <<endl;

        navigate=getch();
        if(navigate == 115){
            option+=1;
            if(option > availoptions){
                selected[availoptions] = ' ';
                option = 0;
                selected[option] = '>';
            }
            else{
                selected[option-1] = ' ';
                selected[option] = '>';
            }
        }
        else if(navigate == 119){
            option-=1;
            if(option < 0){
                selected[0] = ' ';
                option = availoptions;
                selected[option] = '>';
            }
            else{
                selected[option+1] = ' ';
                selected[option] = '>';
            }
        }
        else if(navigate == 13){
            if(option == 0){
                ok = true;
                while(ok){
                    system("cls");
                    cout<<"Type ID Name :";
                    getline(cin,contain.IdName);
                    if(data.checkav(contain.IdName,contain)){
                        contain = data.get_thing(contain.IdName,contain);
                        ok = false;
                    }
                    else{
                        inside = true;
                        while(inside){
                            system("cls");
                            cout<<"Not Found"<<endl;
                            cout<<selecting[0]<<"Check again"<<endl
                                <<selecting[1]<<"Cancel"<<endl;
                            navigate = getch();
                            if(navigate == 115){
                                suboption+=1;
                                if(suboption > 1){
                                    selecting[1] = ' ';
                                    suboption = 0;
                                    selecting[suboption] = '>';
                                }
                                else{
                                    selecting[suboption-1] = ' ';
                                    selecting[suboption] = '>';
                                }
                            }
                            else if(navigate == 119){
                                suboption-=1;
                                if(suboption < 0){
                                    selecting[0] = ' ';
                                    suboption = 1;
                                    selecting[suboption] = '>';
                                }
                                else{
                                    selecting[suboption+1] = ' ';
                                    selecting[suboption] = '>';
                                }
                            }
                            else if(navigate == 13){
                                if(suboption == 1){
                                    contain.IdName="";
                                    inside = false;
                                    ok = false;
                                }
                                else{
                                    inside=false;
                                }
                                selecting[0] = '>';
                                selecting[1] = ' ';
                                suboption = 0;

                            }
                        }
                    }
                }
            }
            else if(option == 1){
                contain.IdName="";
                run=false;
            }
            else if(option == 2){
                if(contain.IdName!=""){
                    data.del(contain.IdName,contain);
                    nameinfo.erase(contain.IdName);
                    Yr[contain.year]->erase(contain.IdName);
                    Smst[contain.Semester]->erase(contain.IdName);
                    Sts[contain.status]->erase(contain.IdName);
                    string tmpry="del /s "+contain.IdName+".txt";
                    system(tmpry.c_str());
                    contain.IdName="";
                    run=false;
                }
                else{
                    cout<<"Invalid"<<endl;
                    getch();
                }
            }
        }
    }
}
//Search function with UI
void browse(map<int,map<string,string>*> &Yr, map<int,map<string,string>*> &Smst, map<string,string> &nameinfo, map<bool,map<string,string>*> &Sts, Hash<Identity> &data, Identity &contain, Identity &emptycontain){
    int option = 0;
    int navigate;
    map<string,string>::iterator iter;
    bool run = true;
    bool allowsearch = false;
    int tempornum;
    int availoptions = 5;
    char selected[] = {'>',' ',' ',' ',' ',' '};
    string tmpry;
    while(run){
        tmpry="";
        contain=emptycontain;
        system("cls");
        cout<<right<<setw(70)<<"Search Name"<<endl;
        cout<<endl<<"Choose the following options :"
            <<endl<<selected[0]<<" By Batch"
            <<endl<<selected[1]<<" By Semester"
            <<endl<<selected[2]<<" By Full Name"
            <<endl<<selected[3]<<" By ID Name(specific plus data view)"
            <<endl<<selected[4]<<" Show All Names"
            <<endl<<selected[5]<<" Exit"
            <<endl;

        navigate=getch();
        if(navigate == 115){
            option+=1;
            if(option > availoptions){
                selected[availoptions] = ' ';
                option = 0;
                selected[option] = '>';
            }
            else{
                selected[option-1] = ' ';
                selected[option] = '>';
            }
        }
        else if(navigate == 119){
            option-=1;
            if(option < 0){
                selected[0] = ' ';
                option = availoptions;
                selected[option] = '>';
            }
            else{
                selected[option+1] = ' ';
                selected[option] = '>';
            }
        }
        else if(navigate == 13){
            if(option == 0){
                while(true){
                    system("cls");
                    cout<<"Search by Year  :";
                    getline(cin,tmpry);
                    if(isInteger(tmpry) && tmpry.length()<=5 && tmpry.length()>=1){
                        tempornum = stoi(tmpry);
                        break;
                    }
                    else{
                        cout<<"Invalid Year"<<endl;
                        getch();
                    }
                }
                if(Yr.count(tempornum)>0){
                    system("cls");
                    iter = Yr[tempornum]->begin();
                    for(iter;iter != Yr[tempornum]->end();iter++){
                        cout<<iter->first<<"|        |"<<iter->second<<endl;
                    }
                    getch();
                }

            }

            else if(option == 1){
                while(true){
                    system("cls");
                    cout<<"Search By Semester  :";
                    getline(cin,tmpry);
                    if(isInteger(tmpry) && tmpry.length()<=2 && tmpry.length()>=1){
                        tempornum = stoi(tmpry);
                        break;
                    }
                    else{
                        cout<<"Invalid"<<endl;
                        getch();
                    }
                }
                if(Smst.count(tempornum)>0){
                    system("cls");
                    iter = Smst[tempornum]->begin();
                    for(iter;iter != Smst[tempornum]->end();iter++){
                        cout<<iter->first<<"|        |"<<iter->second<<endl;
                    }
                    getch();
                }
            }

            else if(option == 2){
                system("cls");
                cout<<"Search by Real Name  :";
                getline(cin,tmpry);
                if(tmpry!=""){
                    allowsearch = true;
                }
                else{
                    system("cls");
                    cout<<"Nothing for Search"<<endl;
                    allowsearch=false;
                    getch();
                }
                if(allowsearch){
                    system("cls");
                    iter = nameinfo.begin();
                    for(iter;iter != nameinfo.end();iter++){
                        if(iter->second==tmpry){
                            cout<<iter->first<<"|        |"<<iter->second<<endl;
                        }
                    }
                    getch();
                }

            }

            else if(option == 3){
                system("cls");
                cout<<"Specific search (by ID Name):";
                getline(cin,contain.IdName);
                contain = data.get_thing(contain.IdName,contain);
                if(!contain.isempty()){
                    if(contain.status==true){
                        tmpry="Active";
                    }
                    else{
                        tmpry="InActive/Graduate/Drop Out/Expelled";
                    }
                    system("cls");
                    cout<<"ID Name          :"<<contain.IdName<<endl
                        <<"Full Name        :"<<contain.FullName<<endl
                        <<"Address          :"<<contain.Address<<endl
                        <<"Semester         :"<<contain.Semester<<endl
                        <<"Year             :"<<contain.year<<endl
                        <<"Current Grade    :"<<contain.Currgrade<<endl
                        <<"Status           :"<<tmpry<<endl
                        <<"E-Mail           :"<<contain.email<<endl
                        <<"Phone Number     :"<<contain.callnum<<endl;
                    getch();
                }
                else{
                    cout<<"Not Found"<<endl;
                    getch();
                }
            }

            else if(option == 4){
                system("cls");
                iter = nameinfo.begin();
                    for(iter;iter != nameinfo.end();iter++){
                        cout<<iter->first<<"|        |"<<iter->second<<endl;
                    }
                    getch();
            }

            else if(option == 5){
                run = false;
                break;
            }
        }
    }
}
