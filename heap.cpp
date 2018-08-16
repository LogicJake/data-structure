#include <iostream>
using namespace std;

int capacity = 10;

//最大堆
void insertHeap(int *heap, int newValue)
{
    if (heap[0] >= capacity)
    {
        cout << "the heap is full" << endl;
        exit(0);
    }

    heap[0]++;
    heap[heap[0]] = newValue;
    int index = heap[0];
    int parentIndex = heap[0] / 2;
    while (index != 1 && heap[parentIndex] < heap[index])
    {
        int tmp = heap[parentIndex];
        heap[parentIndex] = heap[index];
        heap[index] = tmp;
        index = parentIndex;
        parentIndex = index / 2;
    }
}

int deleteMax(int *heap)
{
    if (heap[0] == 0)
    {
        cout << "the heap is empty";
        exit(0);
    }

    int max = heap[1];
    heap[1] = heap[heap[0]];
    heap[0]--;
    int index = 1;
    int leftIndex = index * 2;
    int rightIndex = leftIndex + 1;
    int maxIndex = heap[rightIndex] > heap[leftIndex] ? rightIndex : leftIndex;

    while (heap[index] < heap[maxIndex] && index <= heap[0] - (heap[0]+1) / 2)
    {
        int tmp = heap[index];
        heap[index] = heap[maxIndex];
        heap[maxIndex] = tmp;
        index = maxIndex;
        leftIndex = index * 2;
        rightIndex = leftIndex + 1;
        maxIndex = heap[rightIndex] > heap[leftIndex] ? rightIndex : leftIndex;
    }

    return max;
}
void printHeap(int *heap)
{

    for (int i = 1; i <= heap[0]; i++)
    {
        cout << heap[i] << " ";
    }
    cout << endl;
}
int main()
{
    int *heap = new int[capacity + 1];
    heap[0] = 0;
    insertHeap(heap, 1);
    insertHeap(heap, 8);
    insertHeap(heap, 10);
    insertHeap(heap, 3);
    printHeap(heap);
    cout << deleteMax(heap) << endl;
    printHeap(heap);
    delete[] heap;
}