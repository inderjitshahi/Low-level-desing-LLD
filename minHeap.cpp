#include <bits/stdc++.h>
using namespace std;

class minHeap
{
private:
    vector<int> heap;

    void heapifyUp(int i)
    {
        while (i > 0)
        {
            int parent = (i - 1) / 2;
            if (heap[parent] > heap[i])
            {
                swap(heap[parent], heap[i]);
                i = parent;
            }
            else
                break;
        }
    }

    void heapifyDown(int i)
    {
        int n = heap.size();
        while (true)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;
            if (left < n and heap[smallest] > heap[left])
            {
                smallest = left;
            }
            if (right < n and heap[smallest] > heap[right])
            {
                smallest = right;
            }

            if (smallest != i)
            {
                swap(heap[smallest], heap[i]);
                i = smallest;
            }
            else
                break;
        }
    }

public:
    void push(int val)
    {
        heap.push_back(val);
        heapifyUp(heap.size()-1);
    }

    int top(){
        return heap.empty()?-1:heap[0];
    }

    void pop(){
        if(heap.empty())return;
        heap[0]=heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    bool empty(){
        return heap.empty();
    }
};

int main(){
    minHeap pq=minHeap();
    pq.push(10);
    pq.push(23);
    pq.push(2);
    pq.push(-10);
    pq.push(100);
    pq.push(2);
    cout<<pq.top()<<" ";
    pq.pop();
    cout<<pq.top()<<" ";
    cout<<pq.empty();
    return 0;
}
