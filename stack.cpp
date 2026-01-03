#include <bits/stdc++.h>
using namespace std;

// stack using single queue : while pushing new element, pop and push all prev elements of the queue
class Stack
{
    int *arr;
    int capacity;
    int size;
    int top;

public:
    Stack(int c)
    {
        arr = new int[c];
        capacity = c;
        size = 0;
        top = -1;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    bool isFull()
    {
        return size == capacity;
    }

    void push(int val)
    {
        if (isFull())
        {
            return;
        }
        arr[++top] = val;
        size++;
    }

    void pop()
    {
        if (isEmpty())
        {
            return;
        }
        top--;
        size--;
    }

    int top()
    {
        if (isEmpty())
        {
            return -1;
        }
        return arr[top];
    }

    ~Stack()
    {
        delete[] arr;
    }
};

int main()
{
    Stack s = Stack(10);
    s.push(10);
    s.push(20);
    cout << s.top() << " ";
    s.pop();
    cout << s.top();
    return 0;
}