# Analysis and Notes: `show` in `others/tower_of_hanoi.cpp`

Based on lines 18–33 of [others/tower_of_hanoi.cpp](file:///Users/prishi/C-Plus-Plus/others/tower_of_hanoi.cpp#L18-L33):

```cpp
18: /** Display the towers */
19: void show(const struct tower *const F, const struct tower *const T,
20:           const struct tower *const U) {
21:     std::cout << "\n\n\tF : ";
22:     for (int i = 0; i < F->top; i++) {
23:         std::cout << F->values[i] << "\t";
24:     }
25:     std::cout << "\n\tU : ";
26:     for (int i = 0; i < U->top; i++) {
27:         std::cout << U->values[i] << "\t";
28:     }
29:     std::cout << "\n\tT : ";
30:     for (int i = 0; i < T->top; i++) {
31:         std::cout << T->values[i] << "\t";
32:     }
33: }
```

---

### 1. Inputs
- **Line 19–20:** `show` takes three parameters:
  - `const struct tower *const F`
  - `const struct tower *const T`
  - `const struct tower *const U`
- **Line 19–20:** Each parameter is a constant pointer to a `const struct tower`.
- **Line 11–16, 19–20:** `show` does **not** read any global variables; the towers are local to the caller (e.g., declared in `main` on line 66: `struct tower F, U, T;`) and passed explicitly as pointers.

---

### 2. Result
- **Line 19:** Return type is `void` (preceding `show`), so it returns **nothing**.
- **Line 21–32:** It only prints formatted text to standard output (`std::cout`).
- **Exact text printed:**
  - **Line 21:** Starts with two newlines, a tab, the label `"F : "`: `"\n\n\tF : "`
  - **Lines 22–24:** Loops `for (int i = 0; i < F->top; i++)` and prints `F->values[i] << "\t"` (each element followed by a tab `\t`).
  - **Line 25:** Prints a newline, a tab, and the label `"U : "`: `"\n\tU : "`
  - **Lines 26–28:** Loops `for (int i = 0; i < U->top; i++)` and prints `U->values[i] << "\t"` (each element followed by a tab `\t`).
  - **Line 29:** Prints a newline, a tab, and the label `"T : "`: `"\n\tT : "`
  - **Lines 30–32:** Loops `for (int i = 0; i < T->top; i++)` and prints `T->values[i] << "\t"` (each element followed by a tab `\t`).

---

### 3. Mutation
- **Line 19–20:** `show` does **not** change anything. All tower pointers are declared as `const struct tower *const`, enforcing read-only access by the compiler.
- **Lines 22–32:** The function only reads `top` and `values[i]`. No member variables or global states are modified. A test should verify that `F->top`, `T->top`, `U->top`, and all array elements in `values` are identical before and after calling `show`.

---

### 4. Dependencies
- **Line 6:** Header `#include <iostream>` is required for `std::cout`.
- **Line 21, 23, 25, 27, 29, 31:** Uses the `std` namespace via explicit namespace qualification (`std::cout`). The function itself resides in the global namespace.
- **Lines 11–16:** Depends on user-defined type `struct tower`.

---

### 5. Limits
- **Line 11–16:** The `struct tower` is defined with a fixed-size array:
  - **Line 13:** `int values[10];` — fixed capacity of 10 integers.
  - **Line 15:** `int top;` — counter indicating the current number of disks on the tower.
- **Capacity boundary:** The maximum number of disks a tower can hold is **10** (indices 0 through 9). If `top > 10`, loops at lines 22, 26, and 30 will read past the array boundary, resulting in undefined behavior.

---

### 6. Preconditions
- **Line 19–20:** Pointers `F`, `T`, and `U` must be non-null and point to valid `struct tower` instances.
- **Line 13, 15:** Top counters must be within valid array bounds: $0 \le \text{top} \le 10$.
  - In `main`, these are explicitly initialized to zero:
    - **Line 68:** `F.top = 0;`
    - **Line 69:** `U.top = 0;`
    - **Line 70:** `T.top = 0;`
- **Lines 22–24, 26–28, 30–32:** For each tower, the first `top` elements (`values[0]` to `values[top - 1]`) must contain initialized integer values. In `main`, disks are loaded into `F` before calling `show`:
  - **Lines 77–79:** `for (int i = no; i > 0; i--) { F.values[F.top++] = i; }`

---

### 7. Input Partitioning (Three Input Groups)

| Group | Meaning | Example (adapted to real code) | Source Line Justification |
| :--- | :--- | :--- | :--- |
| **Valid boundary (smallest)** | The least the code supports | All three towers empty: `F.top = 0`, `U.top = 0`, `T.top = 0` | **Lines 15, 22, 26, 30:** `top = 0` causes loops `i < top` to perform 0 iterations; **Lines 68–70:** Towers are initialized to `top = 0`. |
| **Valid interior (ordinary)** | A normal case | A few discs on one or more towers: e.g., `F.top = 3` with `values = {3, 2, 1}`, `U.top = 0`, `T.top = 0` | **Line 13:** `int values[10];` holds up to 10 disks; **Lines 77–79:** Regular gameplay fills $1 \le \text{no} < 10$ disks into `F`. |
| **Valid boundary (largest)** | The most the code supports | Tower full to its maximum capacity: `F.top = 10` with `values = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}`, `U.top = 0`, `T.top = 0` | **Line 13:** Array size is fixed at `10`; **Lines 22, 26, 30:** Loop condition `i < top` accesses up to `values[9]` safely without exceeding bound. |
| **Unsupported** | Outside the limit, such as more discs than the array holds | `top > 10` (e.g., `top = 11`), negative `top` (`top < 0`), or null pointer (`nullptr`) | **Line 13:** Fixed size `values[10]` means reading `values[10]` or higher is undefined behavior; **Lines 19–20:** Pointers dereferenced without null checks. |


---

### 8. Character-by-Character Output Calculation

The function `show(F, T, U)` prints sequentially:
1. `"\n\n\tF : "`
2. For each element $0 \le i < F\text{->top}$: `F->values[i] << "\t"`
3. `"\n\tU : "`
4. For each element $0 \le i < U\text{->top}$: `U->values[i] << "\t"`
5. `"\n\tT : "`
6. For each element $0 \le i < T\text{->top}$: `T->values[i] << "\t"`

#### Case 1: Smallest (All Towers Empty)
- **Input State:**
  - `F.top = 0`
  - `U.top = 0`
  - `T.top = 0`
- **Output Breakdown:**
  - `"\n\n\tF : "`
  - (No discs on F: 0 iterations)
  - `"\n\tU : "`
  - (No discs on U: 0 iterations)
  - `"\n\tT : "`
  - (No discs on T: 0 iterations)
- **Exact Literal String:**
  ```
  "\n\n\tF : \n\tU : \n\tT : "
  ```

#### Case 2: Ordinary (Discs 2 and 1 on Tower F, Others Empty)
- **Input State:**
  - `F.top = 2`, `F.values[0] = 2`, `F.values[1] = 1`
  - `U.top = 0`
  - `T.top = 0`
- **Output Breakdown:**
  - `"\n\n\tF : "`
  - Discs on F: `2` + `\t` + `1` + `\t` -> `"2\t1\t"`
  - `"\n\tU : "`
  - (No discs on U: 0 iterations)
  - `"\n\tT : "`
  - (No discs on T: 0 iterations)
- **Exact Literal String:**
  ```
  "\n\n\tF : 2\t1\t\n\tU : \n\tT : "
  ```

#### Case 3: Largest (Tower F Full to Capacity 10, Others Empty)
- **Input State:**
  - `F.top = 10`, `F.values = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}`
  - `U.top = 0`
  - `T.top = 0`
- **Output Breakdown:**
  - `"\n\n\tF : "`
  - Discs on F: `10\t9\t8\t7\t6\t5\t4\t3\t2\t1\t`
  - `"\n\tU : "`
  - (No discs on U: 0 iterations)
  - `"\n\tT : "`
  - (No discs on T: 0 iterations)
- **Exact Literal String:**
  ```
  "\n\n\tF : 10\t9\t8\t7\t6\t5\t4\t3\t2\t1\t\n\tU : \n\tT : "
  ```

#### Case 4: Repeated Call (Mutation Invariance)
- **Input State:**
  - Set up any initial configuration (e.g., `F.top = 2`, `values = {2, 1}`, `U.top = 0`, `T.top = 0`).
  - Capture output of first call: `output1 = capture_show(&F, &T, &U)`.
  - Capture output of second call: `output2 = capture_show(&F, &T, &U)`.
- **Expected Result:**
  - `output1 == output2` (both equal `"\n\n\tF : 2\t1\t\n\tU : \n\tT : "`).
  - Pre- and post-state verification: `F.top == 2`, `F.values[0] == 2`, `F.values[1] == 1`, `U.top == 0`, `T.top == 0`.
  - Proves that `show` does not mutate the towers.
