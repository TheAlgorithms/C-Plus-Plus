# Analysis of `add` in `range_queries/mo.cpp`

Based on lines 14–18 in [mo.cpp](file:///Users/prishi/C-Plus-Plus/range_queries/mo.cpp#L14-L18):

```cpp
14: void add(int index) {
15:     cnt[a[index]]++;
16:     if (cnt[a[index]] == 1)
17:         ans++;
18: }
```

---

### 1. What does `add` take as input?
- **Formal parameter:** An integer parameter `int index` (representing the array index in `a` whose element is being added to the current window).
- **Global variables read:**
  - `a`: global array containing the input elements (`a[index]` is read on lines 15 and 16).
  - `cnt`: global frequency array (`cnt[a[index]]` is read on lines 15 and 16).
  - `ans`: global counter variable (read and incremented on line 17).

---

### 2. Does it return something?
- **Return type:** `void` (line 14).
- It returns **nothing**.

---

### 3. What does it change?
- **`cnt[a[index]]` (line 15):** Increments the frequency count of the value `a[index]` in the current window (`cnt[a[index]]++`).
- **`ans` (line 17):** Increments the global distinct element count (`ans++`) if `cnt[a[index]] == 1` (i.e., when a number appears in the current window for the first time).

---

### 4. What does it depend on?
- **Headers:** Included at lines 1–3 (`<algorithm>`, `<cmath>`, `<iostream>`), though `add` itself relies only on built-in C++ language features and operators.
- **Namespace:** Sits in the global namespace (after `using namespace std;` on line 5).
- **Global declarations:**
  - `const int N = 1e6 + 5;` (line 6)
  - `int a[N], cnt[N];` (line 7)
  - `int ans = 0;` (line 12)

---

### 5. Preconditions and Line Numbers
- **Line 6:** `const int N = 1e6 + 5;` defines the upper bound size `N` used to size the arrays.
- **Line 7:** `int a[N], bucket[N], cnt[N];` declares the global arrays:
  - `a` must contain the elements to be queried and `index` must satisfy $0 \le \text{index} < N$.
  - `cnt` must be zero-initialized (or properly tracked) and sized sufficiently such that $0 \le a[\text{index}] < N$ to avoid out-of-bounds indexing.
- **Line 12:** `int ans = 0;` declares and initializes the global variable `ans` tracking the number of distinct elements in the current range.
