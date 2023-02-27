#include "InfixToPostfix.h"

node *makeNode(char x)
{
    node *newNode = new node();
    newNode -> data = x;
    newNode -> next = NULL;
    return newNode;
}

int prior(char oprt) //oprt = operator
{
    if(oprt == '+' || oprt == '-')
        return 1;
    else if(oprt == '*' || oprt == '/' || oprt == '%')
        return 2;
    else if(oprt == '^' )
        return 3;
    else return 0;
}

void push(node *&head,char x)
{
    node *newNode = makeNode(x);
    if(head == NULL)
    {
        head = newNode;
        return;
    }
    node *tmp = head;
    while (tmp -> next != NULL)
    {
        tmp = tmp -> next;
    }
    tmp -> next = newNode;
}

void pop(node *&St,node *&Qu)
{
    if(St == NULL) return;
    node *tmp = St;
    if(St -> next == NULL)
    {
        if(St -> data != '(')
        {
            push(Qu,St -> data);
        }
        St = NULL;
        return;
    }
    while(tmp ->  next -> next != NULL)
    {
        tmp = tmp -> next;   
    }
    node *last = tmp -> next;
    tmp -> next = NULL;
    if(last -> data != '(')
        push(Qu,last -> data);
    delete(last);
}

bool checkOpen(node *&St)
{
    node *tmp = St;
    while(tmp -> next != NULL)
    {
        if(tmp -> data == '(')
            return true;
        tmp = tmp -> next;
    }
    return false;
}

void checkSt(node *&St,node *&Qu, char x)
{
    node *tmp = St;
    if(St == NULL) return;
    while(tmp -> next != NULL)
    {
        tmp = tmp -> next;
    }
    if(prior(x) >= prior(tmp -> data)) return;
    if(checkOpen(St))
    {
        do
        {
            pop(St,Qu);
        }while(checkOpen(St));
        push(St,'(');
        return;
    }
    while(St != NULL)
    {
        pop(St,Qu);
    }
}

void load(node *head)
{
    while(head != NULL)
    {
        cout<<head -> data<<' ';
        head = head -> next;
    }
}

void InfixToPostfix()
{
    node *St = NULL;
    node *Qu = NULL;
    string input; cin>>input;
    for(int i = 0 ; i < input.length() ; ++i)
    {
        if(input[i] >= '0' && input[i] <= '9')
        {
            push(Qu,input[i]);
        }
        else
        {   
            if(input[i] == ')')
            {
                while (checkOpen(St))
                {
                    pop(St,Qu);
                }
                continue;
            }
            if(input[i] != '(')
                checkSt(St,Qu,input[i]);
            push(St,input[i]);
        }   
    }
    while (St != NULL)
    {
        pop(St,Qu);
    }
    load(Qu);
}

int main()
{
    InfixToPostfix();
    return 0;
}