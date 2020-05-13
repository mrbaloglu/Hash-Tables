/**
* Title : Hash Tables
* Author : Emre Batuhan Baloglu
* Description : header file for chain hash table
*/
#ifndef CHAINHASHTABLE_H
#define CHAINHASHTABLE_H

using namespace std;
const int MAX_SIZEE = 150;

class ChainHashTable {
public:
    ChainHashTable();
    ~ChainHashTable();
    void insertItem(string key, int amount);
    void retrieveItem(string itemKey, int &comparison);
    void deleteItem(string itemKey);
    void printItems();
    void performanceAnalysis();
private:
    struct ChainNode {
        int amount;
        string itemKey;
        ChainNode *next;
    };
    ChainNode** items;
};
#endif // CHAINHASHTABLE_H
