/**
* Title : Hash Tables
* Author : Emre Batuhan Baloglu
* Description : class functions for open hash table
*/
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include "OpenHashTable.h"
using namespace std;

/**
*Hash Function 1 for strings
*/
int hash(const string &key, int tableSize)
{
	int hashVal = 0;
	for (int i = 0; i < key.length(); i++)
		hashVal += key[i];
	return hashVal % tableSize;
}

OpenHashTable::OpenHashTable()
{
    items = new Node*[MAX_SIZE];
    for(int i = 0; i <MAX_SIZE; i++)
        items[i] = NULL;
}
OpenHashTable::~OpenHashTable()
{
    delete[] items;
}
void OpenHashTable::insertItem(string itemKey, int amount, int &collision)
{
    Node* ptr = new Node;
    ptr->amount = amount;
    ptr->itemKey = itemKey;
    int key = hash(itemKey, MAX_SIZE);
    if(items[key] == NULL) {
        items[key] = ptr;
        return;
    }
    int iter = 1;
    while(items[key] != NULL && iter < MAX_SIZE) {
        key += iter*iter;
        key = key % MAX_SIZE;
        iter++;
    }
    items[key] = ptr;
    collision = iter;
}
void OpenHashTable::retrieveItem(string itemKey, int &comparison)
{
    int key = hash(itemKey, MAX_SIZE);
    if((items[key] != NULL) && (items[key]->itemKey == itemKey)) {
        cout<<items[key]->itemKey<<" = "<<items[key]->amount<<endl;
        comparison++;
        return;
    }

    int iter = 1;
    while((items[key] != NULL) && (items[key]->itemKey != itemKey) && (iter < MAX_SIZE)) {
        key += iter*iter;
        key -= (iter-1)*(iter-1);
        key = key % MAX_SIZE;
        if(items[key] == NULL) {
            cout<<"item with key: "<<itemKey<<" not found in the table."<<endl;
            return;
        }
        comparison++;
        if(items[key]->itemKey == itemKey) {
            cout<<items[key]->itemKey<<" = "<<items[key]->amount<<endl;
            return;
        }
        iter++;
    }
    cout<<"item with key: "<<itemKey<<" not found in the table."<<endl;
}
void OpenHashTable::deleteItem(string itemKey)
{
    int key = hash(itemKey, MAX_SIZE);
    if((items[key] != NULL) && (items[key]->itemKey == itemKey)) {
        delete items[key];
        items[key] = NULL;
        return;
    }
    int iter = 1;
    while((items[key] != NULL) && (items[key]->itemKey != itemKey) && (iter < MAX_SIZE)) {
        int tmp = key;
        key += iter*iter;
        key -= (iter-1)*(iter-1);
        key = key % MAX_SIZE;
        if(items[key] == NULL) {
            cout<<"item with key: "<<itemKey<<" not found in the table."<<endl;
            return;
        }
        if(items[key]->itemKey == itemKey) {
            delete items[key];
            items[key] = NULL;
            return;
        }
        iter++;
    }
    cout<<"item with key: "<<itemKey<<" not found in the table."<<endl;
}

void OpenHashTable::printItems()
{
    for(int i = 0; i < MAX_SIZE; i++) {
        if(items[i] != NULL)
            cout<<i<<": "<<items[i]->itemKey<<" = "<<items[i]->amount<<","<<endl;
    }
}

void OpenHashTable::performanceAnalysis() {

    string name;
    string randomElements[150];

    signed int value;
    ifstream myfile ("items.txt");
    clock_t begin = clock();
    int cnt = 0;
    int collisionCnt = 0;
    while (!myfile.eof())
    {
        getline(myfile,name,'\n');
        char delimiter = '\t';
        if(name != "") {
            string token = name.substr(0, name.find(delimiter));
            string later = name.substr(name.find(delimiter));
            stringstream geek(token);
            int amount = 0;
            geek >> amount;
            insertItem(later, amount, collisionCnt);
            randomElements[cnt] = later;
            cnt++;
        }

    }
    clock_t end = clock();
    double insertionTime = double(end - begin) / CLOCKS_PER_SEC*100;

    int compCnt = 0;
    begin = clock();
    for(int i = 0; i < 100; i++) {
        int tmp = rand() % 150;
        retrieveItem(randomElements[tmp], compCnt);
    }
    end = clock();
    double retrievalTime = double(end - begin) / CLOCKS_PER_SEC*100;

    begin = clock();
    for(int i = 0; i < 100; i++) {
        int tmp = rand() % 150;
        deleteItem(randomElements[tmp]);
    }
    end = clock();

    double deletionTime = double(end - begin) / CLOCKS_PER_SEC*100;

    cout<<"-----------------------------------------------------"<<endl;
    cout<<"Part a - Analysis of Open Addressing Hash Table"<<endl;
    cout<<"Parameter                Time Elapsed"<<endl;
    cout<<"Average Insertion Time       "<<insertionTime / 100<<" ms"<<endl;
    cout<<"Average Retrieval Time       "<<retrievalTime / 100<<" ms"<<endl;
    cout<<"Average Deletion Time       "<<deletionTime / 100<<" ms"<<endl<<endl;
    cout<<"Number of comparisons in Retrieval = "<<compCnt<<endl;
    cout<<"Number of collisions in Insertion = "<<collisionCnt<<endl;
    cout<<"-----------------------------------------------------"<<endl;
}
