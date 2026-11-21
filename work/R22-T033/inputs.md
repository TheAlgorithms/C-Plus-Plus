# Analysis and Notes: `imod` in `math/modular_inverse_simple.cpp`

Based on [math/modular_inverse_simple.cpp](file:///Users/prishi/C-Plus-Plus/math/modular_inverse_simple.cpp):

```cpp
21: uint64_t imod(uint64_t x, uint64_t y) {
22:     uint64_t aux = 0;  // auxiliary variable
23:     uint64_t itr = 0;  // iteration counter
24: 
25:     do {  // run the algorithm while not find the inverse
26:         aux = y * itr + 1;
27:         itr++;
28:     } while (aux % x);  // while module aux % x non-zero
29: 
30:     return aux / x;
31: }
```

---

### 1. Inputs
- **Line 21:** `imod(uint64_t x, uint64_t y)` takes two parameters of type `uint64_t` (unsigned 64-bit integer):
  - `x`: the number whose modular inverse is being calculated.
  - `y`: the modulus ($x^{-1} \pmod y$).
- **Example:** In `imod(3, 11)`, `3` is the number (`x`) and `11` is the modulus (`y`).

---

### 2. Result
- **Line 21, 30:** Returns a `uint64_t` representing the modular multiplicative inverse ($x^{-1} \pmod y$).

---

### 3. Mutation
- **Lines 21–31:** `imod` does **not** read or modify any global variables. All variables (`aux`, `itr`) are local to the stack frame. It is a completely pure function without side effects.

---

### 4. Dependencies
- **Line 10:** `#include <cassert>` (used for assertions in self-tests).
- **Line 11:** `#include <cstdint>` (provides fixed-width integer types such as `uint64_t`).
- **Line 12:** `#include <iostream>` (used for console output in self-tests).
- **Lines 21, 37, 59:** All functions reside in the global namespace. `test()` uses `std::cout` explicitly.

---

### 5. How It Works
- **Lines 22–30:**
  - Variables `aux = 0` (line 22) and `itr = 0` (line 23) are initialized.
  - The loop iteratively evaluates `aux = y * itr + 1` and increments `itr++` (lines 26–27).
  - Loop condition `while (aux % x)` checks whether `aux` divides evenly by `x` (line 28).
  - When `aux % x == 0`, the loop terminates and returns `aux / x` (line 30).
  - Because `(aux / x) * x = aux = y * (itr - 1) + 1`, we have $((\text{aux}/x) \cdot x) \equiv 1 \pmod y$, which satisfies the definition of the modular inverse.

---

### 6. A Limit That Matters
- **Lines 25–28:** The loop terminates only when `(y * itr + 1) % x == 0`.
- If $x$ and $y$ share a common factor $g = \gcd(x, y) > 1$ (for example, $\text{imod}(2, 4)$ or $\text{imod}(6, 26)$), then $g$ divides both $x$ and $y$. Consequently, $g$ divides $y \cdot \text{itr}$, but cannot divide $y \cdot \text{itr} + 1$. Thus, `(y * itr + 1) % x` can never be 0.
- As a result, the loop never terminates (infinite loop) or experiences integer overflow.
- **Contract:** Inputs where $\gcd(x, y) \ne 1$ are unsupported. The function assumes $\gcd(x, y) = 1$. The tests must never invoke `imod` with non-coprime arguments, and no rejection code should be introduced.

---

### 7. Source Lines
- **Line 21:** `uint64_t imod(uint64_t x, uint64_t y)` marks the start of the `imod` function.
- **Line 37:** `static void test()` marks the start of the `test()` self-test implementation.


---

### 8. Step 3: Neighboring Input Calculation

- **Anchor input:** `imod(3, 11) == 4` (since $3 \times 4 = 12 \equiv 1 \pmod{11}$).
- **Chosen neighboring input:** `imod(4, 11)`
- **Hand Calculation:**
  - We seek an integer $r \in \{1, 2, \dots, 10\}$ such that:
    $$4 \times r \equiv 1 \pmod{11} \iff 4r = 11k + 1 \quad (k \in \mathbb{Z}_{\ge 0})$$
  - Testing $k = 0$: $4r = 1 \implies$ no integer solution.
  - Testing $k = 1$: $4r = 11(1) + 1 = 12 \implies r = 12 / 4 = 3$.
  - Check: $4 \times 3 = 12 = 11 \times 1 + 1 \equiv 1 \pmod{11}$.
  - Therefore:
    $$\text{imod}(4, 11) = 3$$

---

### 9. Step 4: Expected-Results Table (Independently Calculated by Hand)

This table covers all values $a \in \{1, \dots, m - 1\}$ for three moduli $m \in \{7, 11, 26\}$.
Values with $\gcd(a, m) = 1$ have a valid unique modular multiplicative inverse.
Values where $\gcd(a, m) > 1$ have no inverse and are marked with `0` (unsupported inputs, never called in tests).

#### Modulus $m = 7$ (Prime, 6 supported inputs)
All $a \in \{1, \dots, 6\}$ are coprime to 7:
| $a$ | Inverse ($a^{-1} \pmod 7$) | Verification: $a \times r = 7k + 1$ |
| :---: | :---: | :--- |
| **1** | **1** | $1 \times 1 = 1 = 7(0) + 1$ |
| **2** | **4** | $2 \times 4 = 8 = 7(1) + 1$ |
| **3** | **5** | $3 \times 5 = 15 = 7(2) + 1$ |
| **4** | **2** | $4 \times 2 = 8 = 7(1) + 1$ |
| **5** | **3** | $5 \times 3 = 15 = 7(2) + 1$ |
| **6** | **6** | $6 \times 6 = 36 = 7(5) + 1$ |

Sequence for $m = 7$: `1, 4, 5, 2, 3, 6` (6 supported inputs).

---

#### Modulus $m = 11$ (Prime, 10 supported inputs)
All $a \in \{1, \dots, 10\}$ are coprime to 11:
| $a$ | Inverse ($a^{-1} \pmod{11}$) | Verification: $a \times r = 11k + 1$ |
| :---: | :---: | :--- |
| **1** | **1** | $1 \times 1 = 1 = 11(0) + 1$ |
| **2** | **6** | $2 \times 6 = 12 = 11(1) + 1$ |
| **3** | **4** | $3 \times 4 = 12 = 11(1) + 1$ |
| **4** | **3** | $4 \times 3 = 12 = 11(1) + 1$ |
| **5** | **9** | $5 \times 9 = 45 = 11(4) + 1$ |
| **6** | **2** | $6 \times 2 = 12 = 11(1) + 1$ |
| **7** | **8** | $7 \times 8 = 56 = 11(5) + 1$ |
| **8** | **7** | $8 \times 7 = 56 = 11(5) + 1$ |
| **9** | **5** | $9 \times 5 = 45 = 11(4) + 1$ |
| **10** | **10** | $10 \times 10 = 100 = 11(9) + 1$ |

Sequence for $m = 11$: `1, 6, 4, 3, 9, 2, 8, 7, 5, 10` (10 supported inputs).

---

#### Modulus $m = 26$ (Composite $2 \times 13$, 12 supported inputs)
Values sharing factors 2 or 13 with 26 have no modular inverse (`0`).
The 12 coprime values $\gcd(a, 26) = 1$ are:
| $a$ | Inverse ($a^{-1} \pmod{26}$) | Verification: $a \times r = 26k + 1$ |
| :---: | :---: | :--- |
| **1** | **1** | $1 \times 1 = 1 = 26(0) + 1$ |
| 2 | 0 | $\gcd(2, 26) = 2 > 1$ (Unsupported) |
| **3** | **9** | $3 \times 9 = 27 = 26(1) + 1$ |
| 4 | 0 | $\gcd(4, 26) = 2 > 1$ (Unsupported) |
| **5** | **21** | $5 \times 21 = 105 = 26(4) + 1$ |
| 6 | 0 | $\gcd(6, 26) = 2 > 1$ (Unsupported) |
| **7** | **15** | $7 \times 15 = 105 = 26(4) + 1$ |
| 8 | 0 | $\gcd(8, 26) = 2 > 1$ (Unsupported) |
| **9** | **3** | $9 \times 3 = 27 = 26(1) + 1$ |
| 10 | 0 | $\gcd(10, 26) = 2 > 1$ (Unsupported) |
| **11** | **19** | $11 \times 19 = 209 = 26(8) + 1$ |
| 12 | 0 | $\gcd(12, 26) = 2 > 1$ (Unsupported) |
| 13 | 0 | $\gcd(13, 26) = 13 > 1$ (Unsupported) |
| 14 | 0 | $\gcd(14, 26) = 2 > 1$ (Unsupported) |
| **15** | **7** | $15 \times 7 = 105 = 26(4) + 1$ |
| 16 | 0 | $\gcd(16, 26) = 2 > 1$ (Unsupported) |
| **17** | **23** | $17 \times 23 = 391 = 26(15) + 1$ |
| 18 | 0 | $\gcd(18, 26) = 2 > 1$ (Unsupported) |
| **19** | **11** | $19 \times 11 = 209 = 26(8) + 1$ |
| 20 | 0 | $\gcd(20, 26) = 2 > 1$ (Unsupported) |
| **21** | **5** | $21 \times 5 = 105 = 26(4) + 1$ |
| 22 | 0 | $\gcd(22, 26) = 2 > 1$ (Unsupported) |
| **23** | **17** | $23 \times 17 = 391 = 26(15) + 1$ |
| 24 | 0 | $\gcd(24, 26) = 2 > 1$ (Unsupported) |
| **25** | **25** | $25 \times 25 = 625 = 26(24) + 1$ |

Sequence for $m = 26$: `1, 0, 9, 0, 21, 0, 15, 0, 3, 0, 19, 0, 0, 0, 7, 0, 23, 0, 11, 0, 5, 0, 17, 0, 25` (12 supported inputs).

---

#### Summary of Supported Inputs
- $m = 7$: 6 supported inputs
- $m = 11$: 10 supported inputs
- $m = 26$: 12 supported inputs
- **Total supported inputs:** $6 + 10 + 12 = 28$ supported test inputs ($\ge 20$ required).
