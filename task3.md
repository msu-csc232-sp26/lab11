# Task 3: Recursive Insertion Sort Strategy

## Background and Learning Objectives

In this task, you will implement **recursive insertion sort**, which emphasizes sorting by building a sorted prefix one
element at a time.

After completing this task, you should be able to:

- Describe insertion sort recursively
- Understand how recursive calls can prepare a sorted prefix
- Carefully manage indices and boundaries during insertion

---

## Review: How Insertion Sort Works

Insertion sort processes elements sequentially, inserting each new element into its proper position relative to the
elements before it.

---

## Recursive Insight

The key idea underlying a recursive approach is:

> If the first `n - 1` elements are sorted, inserting the `n`th element completes the sort.

---

## Recursive Formulation

### Base Case

An array of size 0 or 1 is already sorted.

### Recursive Step

1. Recursively sort the first `size - 1` elements
2. Save the last element
3. Shift larger elements to the right
4. Insert the saved element into its correct position

Most of the work happens after the recursive call returns.

---

## Mapping to the Provided Code

You are given a recursive helper function:

```cpp
void insertion_sort(T* array, std::size_t size);
```

Ensure that:

- The recursive call occurs before insertion
- You do not access out-of-bounds indices
- You handle unsigned index arithmetic carefully

---

## Common Pitfalls

- Performing insertion before recursion
- Forgetting to save the element before shifting
- Allowing unsigned index underflow

---

## Summary

Recursive insertion sort highlights how recursion can be used to incrementally build solutions. Correct ordering of
recursive calls and careful index management are essential for correctness.
