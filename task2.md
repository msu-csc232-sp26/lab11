# Task 2: Recursive Bubble Sort Strategy

## Background and Learning Objectives

In this task, you will implement **bubble sort using recursion** as another concrete sorting strategy.

After completing this task, you should be able to:

- Describe bubble sort in terms of recursive problem reduction
- Identify correct base cases for shrinking array problems
- Understand how a single pass enables recursion

---

## Review: How Bubble Sort Works

Bubble sort repeatedly traverses the array and swaps adjacent elements that are out of order. After one full pass, the
largest element in the unsorted portion is guaranteed to be in its correct position.

---

## Recursive Insight

The key observation is:

> After completing one pass through the array, the last element no longer needs to be considered.

This allows us to treat each recursive call as operating on a strictly smaller prefix of the array.

---

## Recursive Formulation

### Base Case

If the size of the array is 0 or 1, it is already sorted.

### Recursive Step

1. Perform one full pass over the array, swapping adjacent elements when necessary
2. Recursively apply bubble sort to the first `size - 1` elements

---

## Mapping to the Provided Code

The public `sort` function calls a recursive helper:

```cpp
bubble_sort(array, size);
```

Your job is to implement this helper so that:

- One recursive call corresponds to one full pass
- Each call reduces the effective problem size

---

## Common Pitfalls

- Performing multiple passes in one recursive call
- Forgetting to reduce the problem size
- Looping beyond valid array boundaries

---

## Summary

Recursive bubble sort demonstrates how a simple invariant—moving the largest element to the end—allows an
iterative-looking algorithm to be expressed recursively.
