# ⚙️ Meet in the Middle — Algorithmic Technique

## 📘 Overview

**Meet in the Middle (MITM)** is an optimization technique used to reduce the time complexity of problems that would otherwise require exploring all possible subsets (`O(2^N)`).

The key idea:

> Instead of generating all possible combinations directly, we **split the problem into two halves**, solve each half independently, and then **combine** the results efficiently.

---

## 🧠 Why It Works

For problems like subset sum, product optimization, or combinatorial selection:

- Direct brute-force → `O(2^N)` → infeasible when `N > 30`
- Meet in the Middle → `O(2^(N/2) * log(2^(N/2)))` → manageable for `N ≤ 40`

It leverages:

- **Divide and Conquer**
- **Binary Search / Hashing**
- **Combination of precomputed subsets**

---
