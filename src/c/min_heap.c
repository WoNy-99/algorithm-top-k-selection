/**
 * @file    algoA_C_min_heap.c
 * @details LeetCode 215 · Kth Largest Element in an Array — min-heap based solution
 * @algorithm Maintain a min-heap of size k while scanning the array.
 *            If the heap is not yet full, push the current element.
 *            Once the heap reaches size k, only keep elements larger than
 *            the current heap minimum by popping the minimum and inserting
 *            the new candidate. After processing all elements, the heap root
 *            is the k-th largest value.
 * @author  Team 5 강서윤
 * @date    2025-11-23
 */

#include <stdio.h>
#include <stdlib.h>

// Swap two integers by pointer
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Percolate a node up to restore the min-heap property after insertion
void heapifyUp(int heap[], int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        // If parent is larger than child, swap and move up
        if (heap[parent] > heap[index]) {
            swap(&heap[parent], &heap[index]);
            index = parent;
        } else {
            break;
        }
    }
}

// Percolate a node down to restore the min-heap property after deletion
void heapifyDown(int heap[], int size, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && heap[left] < heap[smallest])
            smallest = left;
        if (right < size && heap[right] < heap[smallest])
            smallest = right;

        // If a child is smaller than the current node, swap and continue
        if (smallest != index) {
            swap(&heap[smallest], &heap[index]);
            index = smallest;
        } else {
            break;
        }
    }
}

// Insert a value into the min-heap and increase its size
void push(int heap[], int *size, int value) {
    heap[*size] = value;
    heapifyUp(heap, *size);
    (*size)++;
}

// Remove and return the minimum value (root) from the min-heap
int pop(int heap[], int *size) {
    int root = heap[0];
    (*size)--;               // Decrease heap size first
    heap[0] = heap[*size];   // Move the last element to the root
    heapifyDown(heap, *size, 0);
    return root;
}

// Find the k-th largest element using a min-heap of size k
int findKthLargest(int* nums, int numsSize, int k) {
    int *heap = (int*)malloc(sizeof(int) * k);
    int heapSize = 0;

    for (int i = 0; i < numsSize; i++) {
        if (heapSize < k) {
            // Heap has space: simply insert the current value
            push(heap, &heapSize, nums[i]);
        } else if (nums[i] > heap[0]) {
            // Current value is larger than the smallest among top-k:
            // drop the smallest and insert the new candidate
            pop(heap, &heapSize);
            push(heap, &heapSize, nums[i]);
        }
        // If nums[i] <= heap[0] and heap is full, we ignore nums[i]
        // because it cannot belong to the top-k set.
    }

    // The minimum in the heap is the k-th largest element overall
    int result = heap[0];
    free(heap);
    return result;
}