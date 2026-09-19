"""
@file     algoB_Python_quickselect.py
@details  LeetCode 215 · Kth Largest Element in an Array — Quickselect (3-way partition)
@algorithm View the k-th largest element as the element at index (len(nums) - k)
           in ascending order. Repeatedly pick a random pivot, partition the
           current range into three regions (< pivot, == pivot, > pivot), and
           continue the search only in the region that contains this target
           index. Since we never fully sort the array, the expected running
           time is O(N).
@author   Team 5 김주경, 서상원
@date     2025-11-22
"""

from typing import List
import random


class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        # Index of the k-th largest element if the array were sorted ascending
        target = len(nums) - k
        left, right = 0, len(nums) - 1

        while True:
            # If only one element is left, that must be the answer
            if left == right:
                return nums[left]

            # 1) Choose a random pivot index and value within the current range
            pivot_index = random.randint(left, right)
            pivot = nums[pivot_index]

            # 2) Dutch National Flag 3-way partition around the pivot
            #    After partitioning:
            #      nums[left .. lt-1]  : elements < pivot
            #      nums[lt   .. gt]    : elements == pivot
            #      nums[gt+1 .. right] : elements > pivot
            lt, i, gt = left, left, right
            while i <= gt:
                if nums[i] < pivot:
                    # Move smaller elements to the left region
                    nums[lt], nums[i] = nums[i], nums[lt]
                    lt += 1
                    i += 1
                elif nums[i] > pivot:
                    # Move larger elements to the right region
                    nums[gt], nums[i] = nums[i], nums[gt]
                    gt -= 1
                    # Do not increment i here, because the swapped-in value
                    # at position i has not been examined yet
                else:  # nums[i] == pivot
                    # Elements equal to pivot stay in the middle region
                    i += 1

            # 3) Decide which region contains the target index and shrink range
            if target < lt:
                # The target index lies in the "< pivot" region
                right = lt - 1
            elif target > gt:
                # The target index lies in the "> pivot" region
                left = gt + 1
            else:
                # The target index lies inside the "== pivot" region,
                # so nums[target] has the correct rank (k-th largest)
                return nums[target]
