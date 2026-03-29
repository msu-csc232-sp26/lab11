# Task 1: Recursive Selection Sort Strategy

## Background and Learning Objectives

In this task, you will implement a **recursive version of selection sort** as a concrete strategy in the Strategy Design
Pattern.

By completing this task, you should be able to:

- Explain how selection sort works conceptually
- Formulate selection sort recursively
- Translate a recursive algorithm into a templated member function
- Reason about base cases and recursive progress
- Work within a provided class structure without modifying its interface

---

## Review: How Selection Sort Works

Selection sort organizes an array by repeatedly selecting the **smallest element** from the unsorted portion and
swapping it into its correct position.

At a high level:

1. Assume the first element is the minimum
2. Scan the rest of the array to find a smaller element
3. Swap the smallest element into the current position
4. Repeat for the remainder of the array

---

## Recursive Formulation

After placing the smallest element at position `start_index`, the remaining task is to sort the subarray that begins at
`start_index + 1`. This naturally leads to a recursive solution.

### Base Case

If `start_index >= size - 1`, the array (or remaining subarray) is already sorted.

### Recursive Step

1. Find the index of the smallest element in the range `[start_index, size)`
2. Swap that element with the element at `start_index`
3. Recursively apply selection sort starting at the next index

Each recursive call reduces the size of the remaining unsorted region.

---

## Mapping to the Provided Code

You are given a public `sort` member function that makes the initial recursive call:

```cpp
selection_sort(array, size, 0);
```

Your job is to implement the recursive helper function:

```cpp
void selection_sort(T* array, std::size_t size, std::size_t start_index);
```

You must not change the function signatures or convert the algorithm into an iterative one.

---

## Common Pitfalls

- Forgetting or misidentifying the base case
- Searching for the minimum element starting at index 0 instead of `start_index`
- Recursing without progressing toward the base case
- Swapping elements unnecessarily

---

## Summary

Recursive selection sort works by fixing exactly one element per call and delegating the rest of the work to a smaller
subproblem. Once the recursive structure is clear, the implementation follows naturally.
