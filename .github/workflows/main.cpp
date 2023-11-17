#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Character{
protected:
    static const int EXP_LV=100;
    static const int INI_EXP=50;
    string name;
    int level;
    int exp;
    int str;
    int wis;
    int agi;
    void levelUp(int strInc, int wisInc, int agiInc );
public:
    Character(string name, int level, int exp, int str, int mag, int agi);
    virtual void print();
    virtual void beatMonster(int exp)=0;  //pure virtual function
    string getName();
};


Character::Character(string n, int lv, int exp, int st, int wi, int ag)
    :name(n), level(lv), exp((pow((lv-1),2) *EXP_LV)+INI_EXP) ,str(st),wis(wi),agi(ag)
{}

void Character::print(){
    cout    << this->name
            << ": Level" << this ->level
            << " (" << this->exp << "/" << pow(this->level, 2) * EXP_LV << "), "
            << this-> str << "-" << this->wis << "-" << this->agi << "\n";
}


string Character::getName()
{
    return this->name;
}



void Character::levelUp(int strInc, int wisInc, int agiInc){
    this->level++;
    this->str += strInc;
    this->wis += wisInc;
    this->agi += agiInc;
}


class Warrior:public Character
{
private:
    static const int str_lv = 10;
    static const int wis_lv = 5;
    static const int agi_lv = 8;
public:
    Warrior(string n, int lv);
    void print();
    void beatMonster(int exp);

};


Warrior::Warrior(string n, int level)
    : Character(n, level, exp, level*str_lv, level*wis_lv, level*agi_lv ) {}

void Warrior::print() { cout<< "Warrior:"; Character::print();}

void Warrior::beatMonster(int exp)
    {
        this->exp += exp;
        while(this->exp >= pow((this->exp),2)*(Character::EXP_LV))
            {this->levelUp(str_lv, wis_lv, agi_lv);}
    }
/*
template <typename KeyType>
class Wizard:public Character<KeyType>
{
private:
    static const int str_lv = 5;
    static const int wis_lv = 10;
    static const int agi_lv = 6;
public:
    Wizard(KeyType n, int level=1)
        : Character<KeyType>(n, level, exp, level*str_lv, level*wis_lv, level*agi_lv ) {}
    void print() { cout<< "Wizard:"; Character<KeyType>::print();}
    void beatMonster(int exp)
    {
        this->exp += exp;
        while(this->exp >= pow((this->exp),2)*(Character<KeyType>::EXP_LV))
            {this->levelUp(str_lv, wis_lv, agi_lv);}
    }
};
*/

class Team{
private:
    static const int team_max =10;
    string team_name;
    int membercnt;
    Character* member[team_max];
public:
    Team(string team_name);
    ~Team();
    void addMember(string name, int level);
    void printMember(string name);
};


Team::Team(string n):team_name(n)
{
    membercnt=0;
    for(int i=0; i<team_max;i++)
        member[i] = nullptr;
}


Team::~Team(){
    for(int i=0; i<team_max;i++)
        delete member[i];
}


void Team::addMember(string name, int level){
    if(membercnt<10){
        member[membercnt] = new Warrior(name, level);
        membercnt ++;
    }
}

void Team::printMember(string name){
    for(int i=0; i<team_max;i++){
        if(member[i]->getName() == name)
        {
            cout << this->team_name;
            member[i]->print();
            break;
        }
    }
}

int main(){

    Character* c[3];
    c[0] = new Warrior("Amy",1);
    c[1] = new Warrior("Jason",10);
    c[2] = new Warrior("son",10);
    //c[2] = new Character("Clement",5,10,25,25,25);
    for(int i=0; i<3; i++){
        c[i]->print();
        c[i]->getName();
    }


    /*
    Team a("FW");
    a.addMember("Alexpo", 10);
    a.printMember("Alexpo");
*/
    return 0;
}