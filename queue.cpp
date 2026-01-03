#include <bits/stdc++.h>
using namespace std;

/**
Use TWO stacks:
inStack → for enqueue
outStack → for dequeue
Invariant:
    outStack always has the front of the queue on top
 **/
class CircularQueue
{
    int *arr;
    int front, rear, size, capacity;

public:
    CircularQueue(int cap)
    {
        capacity = cap;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        size = 0;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    bool isFull()
    {
        return size == capacity;
    }

    void enqueue(int x)
    {
        if (isFull())
        {
            cout << "Queue Overflow\n";
            return;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = x;
        size++;
    }

    void dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue Underflow\n";
            return;
        }
        front = (front + 1) % capacity;
        size--;
    }

    int peek()
    {
        if (isEmpty())
            return -1;
        return arr[front];
    }
};
