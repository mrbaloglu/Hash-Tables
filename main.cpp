/**
* Title : Hash Tables
* Author : Emre Batuhan Baloglu
* Description : tester file
*/
#include "OpenHashTable.h"
#include "ChainHashTable.h"
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
using namespace std;

void simulateOpenHashTable() {
    OpenHashTable oht;
    string name;
    ifstream myfile ("items.txt");
    int insertcnt = 0;
    while (!myfile.eof())
    {
        getline(myfile,name,'\n');
        char delimiter = '\t';
        if(name != "") {
            string token = name.substr(0, name.find(delimiter));
            string later = name.substr(name.find(delimiter)+1);
            stringstream geek(token);
            int amount = 0;
            geek >> amount;
            oht.insertItem(later, amount, insertcnt);
        }
    }
    oht.printItems();
    int compcnt = 0;
    cout<<"========================================="<<endl;
    oht.retrieveItem("apple fuji ", compcnt);
    oht.retrieveItem("banana", compcnt);
    oht.retrieveItem("apricots", compcnt);
    cout<<"========================================="<<endl;
    oht.deleteItem("broccoli");
    oht.deleteItem("bok choy");
    oht.deleteItem("spinach");

    oht.printItems();
    cout<<"========================================="<<endl;
}

void simulateChainHashTable() {
    ChainHashTable cht;
    string name;
    ifstream myfile ("items.txt");
    while (!myfile.eof())
    {
        getline(myfile,name,'\n');
        char delimiter = '\t';
        if(name != "") {
            string token = name.substr(0, name.find(delimiter));
            string later = name.substr(name.find(delimiter)+1);
            stringstream geek(token);
            int amount = 0;
            geek >> amount;
            cht.insertItem(later, amount);
        }
    }
    cht.printItems();
    int compcnt = 0;
    string str = "apple fuji";
    cout<<"========================================="<<endl;
    cht.retrieveItem(str, compcnt);
    cht.retrieveItem("banana", compcnt);
    cht.retrieveItem("apricots", compcnt);
    cout<<"========================================="<<endl;
    cht.deleteItem("broccoli");
    cht.deleteItem("bok choy");
    cht.deleteItem("spinach");

    cht.printItems();
    cout<<"========================================="<<endl;
}

int main() {
    simulateOpenHashTable();
    simulateChainHashTable();
    return 0;
}

