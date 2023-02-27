#include <iostream>
#include <string>

using namespace std;

struct node
{
    char data;
    node *next;
};

node *makeNode(char);

int prior(char x);

void push(node*& , node*&);
void pop(node*& , node*&);
void checkSt(node*& , node*& , char);
void load(node*);

bool checkOpen(node*&);