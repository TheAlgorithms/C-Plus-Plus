# Meet in the Middle

## 📘 Overview
**Meet in the Middle** is an optimization technique used for solving problems  
that would otherwise take **exponential time (O(2^N))**.  
It divides the problem into two halves and combines the results,  
reducing complexity to **O(2^(N/2))**, which is much faster.

---

## ⚙️ How It Works
1. **Divide** the input set or problem into two halves.  
2. **Generate all possible results** (like subset sums) for each half.  
3. **Sort one list** and use **binary search or two-pointer** techniques  
   to efficiently combine results from both halves.

