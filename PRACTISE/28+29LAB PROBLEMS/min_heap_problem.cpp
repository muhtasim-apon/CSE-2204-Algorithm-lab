#include <stdio.h>

int heap[100005];  // Array to store heap elements
int heap_size = 0; // Current number of elements in heap

// Swap two integers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify up - move element at index idx up to maintain min heap property
void heapify_up(int idx)
{
    while (idx > 0)
    {
        int parent = (idx - 1) / 2;
        if (heap[idx] < heap[parent])
        {
            swap(&heap[idx], &heap[parent]);
            idx = parent;
        }
        else
        {
            break;
        }
    }
}

// Heapify down - move element at index idx down to maintain min heap property
void heapify_down(int idx)
{
    while (true)
    {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;

        if (left < heap_size && heap[left] < heap[smallest])
        {
            smallest = left;
        }
        if (right < heap_size && heap[right] < heap[smallest])
        {
            smallest = right;
        }

        if (smallest != idx)
        {
            swap(&heap[idx], &heap[smallest]);
            idx = smallest;
        }
        else
        {
            break;
        }
    }
}

// Insert element into min heap
void insert(int value)
{
    heap[heap_size] = value;
    heapify_up(heap_size);
    heap_size++;
}

// Extract minimum element from heap
int extract_min()
{
    int min_value = heap[0];
    heap_size--;
    heap[0] = heap[heap_size];
    heapify_down(0);
    return min_value;
}

int main()
{
    int n;
    scanf("%d", &n);

    // Insert all elements into min heap
    for (int i = 0; i < n; i++)
    {
        int value;
        scanf("%d", &value);
        insert(value);
    }

    // Extract all elements from min heap
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", extract_min());
    }

    return 0;
}
