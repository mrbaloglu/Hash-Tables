/**
* Title : Hash Tables
* Author : Emre Batuhan Baloglu
* Description : header file for open hash table
*/
#ifndef OPENHASTABLE_H
#define OPENHASHTABLE_H
#include <string>
using namespace std;
const int MAX_SIZE = 150;

class OpenHashTable {
public:
    OpenHashTable();
    ~OpenHashTable();
    void insertItem(string key, int amount, int &collision);
    void retrieveItem(string itemKey, int &comparison);
    void deleteItem(string itemKey);
    void printItems();
    void performanceAnalysis();
private:
    struct Node {
        int amount;
        string itemKey;
    };
    Node** items;
};
#endif // OPENHASTABLE_H
