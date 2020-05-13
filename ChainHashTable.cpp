/**
* Title : Hash Tables
* Author : Emre Batuhan Baloglu
* Description : class functions for chain hash table
*/
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <ctime>
#include <stdlib.h>
#include "ChainHashTable.h"
using namespace std;

/**
*Hash Function 1 for strings
*/
int hashAux(const string &key, int tableSize)
{
	int hashVal = 0;
	for (int i = 0; i < key.length(); i++)
		hashVal += key[i];
	return hashVal % tableSize;
}

ChainHashTable::ChainHashTable()
{
    items = new ChainNode*[MAX_SIZEE];
    for(int i = 0; i < MAX_SIZEE; i++)
        items[i] = NULL;
}
ChainHashTable::~ChainHashTable()
{
    for(int i = 0; i < MAX_SIZEE;i++) {
        if(items[i] != NULL) {
            while(items[i] != NULL) {
                ChainNode *tmp = items[i];
                items[i] = items[i]->next;
                delete tmp;
            }
        }
    }
    delete[] items;
}
void ChainHashTable::insertItem(string itemKey, int amount)
{
    ChainNode* ptr = new ChainNode;
    ptr->amount = amount;
    ptr->itemKey = itemKey;
    ptr->next = NULL;
    int key = hashAux(itemKey, MAX_SIZEE);
    if(items[key] == NULL) {
        items[key] = ptr;
    }else {
        ChainNode *tmp = items[key]->next;
        while(tmp != NULL) {
            tmp = tmp->next;
        }
        tmp = ptr;
        ptr = NULL;
    }
}
void ChainHashTable::retrieveItem(string itemKey, int &comparison)
{
    int key = hashAux(itemKey, MAX_SIZEE);
    if((items[key] != NULL) && (items[key]->itemKey == itemKey)) {
        cout<<items[key]->itemKey<<" = "<<items[key]->amount<<endl;
        comparison++;
        return;
    } else {
        ChainNode *tmp = items[key];
        while(tmp != NULL) {
            comparison++;
            if(tmp->itemKey == itemKey) {
                cout<<items[key]->itemKey<<" = "<<items[key]->amount<<endl;
                return;
            }
            tmp = tmp->next;
        }
    }
    cout<<"item with key: "<<itemKey<<" not found in the table."<<endl;
}
void ChainHashTable::deleteItem(string itemKey)
{
    int key = hashAux(itemKey, MAX_SIZEE);
    if((items[key] != NULL) && (items[key]->itemKey == itemKey)) {
        ChainNode *tmp = items[key];
        items[key] = items[key]->next;
        delete tmp;
        return;
    } else {
        ChainNode *tmp = items[key];
        while(tmp != NULL) {
            if(tmp->itemKey == itemKey) {
                ChainNode *tmp = items[key];
                items[key] = items[key]->next;
                delete tmp;
                return;
            }
            tmp = tmp->next;
        }
    }
    cout<<"item with key: "<<itemKey<<" not found in the table."<<endl;
}

void ChainHashTable::printItems()
{
    for(int i = 0; i < MAX_SIZEE; i++) {
        ChainNode *tmp = items[i];
        while(tmp != NULL) {
            cout<<i<<": "<<items[i]->itemKey<<" = "<<items[i]->amount<<","<<'\t';
            tmp = tmp->next;
        }
        if(items[i] != NULL)
            cout<<endl;
    }
}

void ChainHashTable::performanceAnalysis() {

    string name;
    string randomElements[150];

    signed int value;
    ifstream myfile ("items.txt");
    clock_t begin = clock();
    int cnt = 0;cout<<"!!!!!!123"<<endl;
    while (!myfile.eof())
    {
        getline(myfile,name,'\n');
        char delimiter = '\t';cout<<"!!!!!!127"<<endl;
        if(name != "") {
            string token = name.substr(0, name.find(delimiter));cout<<"!!!!!!129"<<endl;
            string later = name.substr(name.find(delimiter));
            stringstream geek(token);
            int amount = 0;
            geek >> amount;
            insertItem(later, amount);
            randomElements[cnt] = later;cout<<"!!!!!!130"<<endl;
            cnt++;
        }

    }
    clock_t end = clock();
    double insertionTime = double(end - begin) / CLOCKS_PER_SEC*100;

    int compCnt = 0;
    cout<<"!!!!!!144"<<endl;
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
    cout<<"Part b - Analysis of Separate Chain Hash Table"<<endl;
    cout<<"Parameter                Time Elapsed"<<endl;
    cout<<"Average Insertion Time       "<<insertionTime / 100<<" ms"<<endl;
    cout<<"Average Retrieval Time       "<<retrievalTime / 100<<" ms"<<endl;
    cout<<"Average Deletion Time       "<<deletionTime / 100<<" ms"<<endl<<endl;
    cout<<"Number of comparisons in Retrieval = "<<compCnt<<endl;
}
