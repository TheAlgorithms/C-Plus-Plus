# Test and Validation Evidence - Task R22-T031

## 1. Tool Versions
- **Compiler:** Apple clang version 21.0.0 (`clang-2100.1.1.101`, Target: `arm64-apple-darwin27.2.0`)
- **CMake:** Project requires CMake minimum `3.22` (defined in [CMakeLists.txt](file:///Users/prishi/C-Plus-Plus/CMakeLists.txt#L1))
- **Python:** Python 3.9.6

---

## 2. Compilation Details
- **Source File:** [range_queries/mo.cpp](file:///Users/prishi/C-Plus-Plus/range_queries/mo.cpp)
- **Compiler Settings / Flags:**
  ```bash
  clang++ -std=c++17 -Wall -Wextra -Wno-register -Werror=vla range_queries/mo.cpp -o work/R22-T031/mo_test_bin
  ```

---

## 3. Preconditions (from Step 2 Notes)
- **Line 6:** `const int N = 1e6 + 5;` — Upper bound size $N$ for array allocations.
- **Line 7:** `int a[N], bucket[N], cnt[N];` — Global arrays; requires $0 \le \text{index} < N$, $0 \le a[\text{index}] < N$, and `cnt` zero-initialized.
- **Line 12:** `int ans = 0;` — Global distinct-element counter initialized to 0.

---

## 4. Test Inputs, Expected Results vs. Actual Results

| Test | Input Conditions | Expected Results | Actual Results | Status |
| :--- | :--- | :--- | :--- | :--- |
| `test_return_value` | Call `add(0)` | Returns `void` (no return value) | Returns `void` | **PASSED** |
| `test_mutation_smallest_input` | `index = 0`, `a[0] = 0`, initial `ans = 0`, `cnt[0] = 0` | `cnt[0] == 1`, `ans == 1` | `cnt[0] = 1`, `ans = 1` | **PASSED** |
| `test_mutation_ordinary_input` | `index = 1`, `a[1] = 7`, initial `ans = 1`, `cnt[7] = 0` | `cnt[7] == 1`, `ans == 2` | `cnt[7] = 1`, `ans = 2` | **PASSED** |
| `test_mutation_repeated_value` | `index = 2`, `a[2] = 7`, initial `ans = 2`, `cnt[7] = 1` | `cnt[7] == 2`, `ans == 2` | `cnt[7] = 2`, `ans = 2` | **PASSED** |

Total tests executed: **4** (all passed).

---

## 5. Deliberate Failure Verification
To verify that the runner detects failures and exits with a non-zero status code:
1. Temporarily changed the assertion in `test_mutation_smallest_input` to `assert(cnt[0] == 999);`.
2. Executed `python3 work/R22-T031/check.py`.
3. Output caught error:
   ```
   Mutation check failed (smallest input): expected cnt[0] == 999, got 1
   Assertion failed: (cnt[0] == 999), function test_mutation_smallest_input, file mo.cpp, line 63.
   [Execution Error] Test binary exited with failure code: -6
   ```
   Process exited with non-zero exit code (`250`).
4. Restored the assertion back to `assert(cnt[0] == 1);`.
5. Re-ran `python3 work/R22-T031/check.py`, which exited with code `0` and confirmed all checks passed.
