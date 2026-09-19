/**
 * @file    algoB_C_quickselect.c
 * @details LeetCode 215 · Kth Largest Element in an Array — Quickselect (3-way partition)
 * @algorithm Treat the k-th largest element as the element at index (k-1)
 *            in a descending order. Repeatedly choose a random pivot and
 *            partition the current range into three parts: > pivot, == pivot,
 *            and < pivot. Then narrow the search interval to the part that
 *            can still contain the k-th largest position. Since we never
 *            fully sort the array, the expected running time is O(N).
 * @author  Team 5 이영민, 임재윤
 * @date    2025-11-22
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Swap two integers by pointer
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * 3-way partition around a randomly chosen pivot.
 *
 * After partitioning the subarray nums[left..right], we have:
 *   nums[left .. lt-1]  : elements strictly greater than pivot
 *   nums[lt   .. gt]    : elements equal to pivot
 *   nums[gt+1 .. right] : elements strictly less than pivot
 *
 * The indices lt and gt are returned by reference.
 */
void partition3(int* nums, int left, int right, int* lt, int* gt) {
    // Choose a random pivot index in [left, right]
    int pivotIndex = left + rand() % (right - left + 1);
    int pivot = nums[pivotIndex];

    // Move pivot to the front for convenience
    swap(&nums[left], &nums[pivotIndex]);

    int i = left;
    *lt = left;      // next position to place an element > pivot
    *gt = right;     // next position to place an element < pivot

    // Dutch National Flag partitioning
    while (i <= *gt) {
        if (nums[i] > pivot) {
            // For k-th "largest", values greater than pivot go to the left side
            swap(&nums[i], &nums[*lt]);
            (*lt)++;
            i++;
        } else if (nums[i] < pivot) {
            // Values smaller than pivot go to the right side
            swap(&nums[i], &nums[*gt]);
            (*gt)--;
            // do not increment i here, because the swapped-in element at i
            // still needs to be examined
        } else {
            // nums[i] == pivot → stay in the middle region
            i++;
        }
    }
}

/**
 * Quickselect to find the k-th largest element (1-based k) in-place.
 *
 * nums  : array of integers
 * left  : left boundary of the current search range
 * right : right boundary of the current search range
 * k     : rank of the desired element in descending order (1-based)
 */
int quickSelect(int* nums, int left, int right, int k) {
    // Target index in "descending" order is (k - 1) in 0-based indexing
    int targetIndex = k - 1;

    while (left <= right) {
        int lt, gt;
        partition3(nums, left, right, &lt, &gt);

        // Region mapping (in descending order):
        //   [left .. lt-1]  : indices 0 .. (lt-1-left)
        //   [lt   .. gt]    : all equal to pivot
        //   [gt+1 .. right] : smaller than pivot

        if (targetIndex < lt) {
            // k-th largest lies in the "greater than pivot" region
            right = lt - 1;
        } else if (targetIndex > gt) {
            // k-th largest lies in the "less than pivot" region
            left = gt + 1;
        } else {
            // targetIndex is within [lt .. gt] (== pivot region)
            // any element in this region has the correct rank
            return nums[lt];
        }
    }
    // Should not be reached if k is valid
    return -1;
}

int findKthLargest(int* nums, int numsSize, int k) {
    // Initialize random seed so that pivot selection varies between runs
    srand((unsigned int)time(NULL));

    // Run Quickselect on the full range
    return quickSelect(nums, 0, numsSize - 1, k);
}
