"""
@file     algoA_Python_min-heap.py
@details  LeetCode 215 · Kth Largest Element in an Array — min-heap based solution
@algorithm Maintain a min-heap of size k while scanning the array.
           If the heap has fewer than k elements, push the current value.
           Once it reaches size k, keep pushing new values and immediately
           pop the smallest so that the heap always stores the k largest
           elements seen so far. The heap root is then the k-th largest value.
@author   Team 5 김주경, 서상원
@date     2025-11-22
"""

from typing import List
import heapq


class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        # Min-heap storing at most k elements (the current top-k)
        heap: List[int] = []

        for num in nums:
            # Insert current number into the heap
            heapq.heappush(heap, num)

            # If we now have more than k elements, discard the smallest one.
            # This keeps only the k largest elements in the heap.
            if len(heap) > k:
                heapq.heappop(heap)

        # After processing all numbers, the heap contains the k largest values.
        # The smallest among them (the root) is exactly the k-th largest element.
        return heap[0]