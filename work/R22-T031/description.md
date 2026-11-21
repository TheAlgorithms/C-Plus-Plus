# Pull Request / Task Description: Regression Tests for `add` in `mo.cpp`

## Summary of Changes
This pull request adds Doxygen documentation and self-tests for the `add(int index)` function in [range_queries/mo.cpp](file:///Users/prishi/C-Plus-Plus/range_queries/mo.cpp#L16-L27) in accordance with the repository's test conventions and CMake standards.

---

## What Was Tested
The `add(int index)` function updates the sliding window state in Mo's algorithm by incrementing the frequency of `a[index]` in the global `cnt` array and incrementing the count of distinct elements `ans` when an element enters the window for the first time:

```cpp
void add(int index) {
    cnt[a[index]]++;
    if (cnt[a[index]] == 1)
        ans++;
}
```

The tests cover the following separate behaviors and boundary conditions:

1. **Return Value Behavior (`test_return_value`):**
   - Verifies that `add(int index)` has a `void` return type and returns nothing.
2. **State Mutation - Smallest Input (`test_mutation_smallest_input`):**
   - Input: `index = 0`, `a[0] = 0` with initial `ans = 0` and `cnt[0] = 0`.
   - Verified that `cnt[0]` increments to `1` and `ans` increments to `1`.
3. **State Mutation - Ordinary Input (`test_mutation_ordinary_input`):**
   - Input: `index = 1`, `a[1] = 7` with initial `ans = 1` and `cnt[7] = 0`.
   - Verified that `cnt[7]` increments to `1` and `ans` increments to `2`.
4. **State Mutation - Repeated Value (`test_mutation_repeated_value`):**
   - Input: `index = 2`, `a[2] = 7` with initial `ans = 2` and `cnt[7] = 1`.
   - Verified that `cnt[7]` increments to `2` and `ans` remains unchanged at `2` (since the element is already present in the active window).

All assertions use literal expected values (e.g., `assert(cnt[0] == 1);`) and log expected vs. actual values to `std::cerr` on failure.

---

## Test Results
- **Self-Test Execution:** All 4 tests ran and passed cleanly when built with the repository's CMake compiler options (`-std=c++17 -Wall -Wextra -Wno-register -Werror=vla`).
- **Automated Runner Output:** Running `python3 work/R22-T031/check.py` returned code `0`:
  ```
  [Execution] Running compiled test binary...
  All tests have successfully passed!
  [Tests Ran] 4 tests executed successfully:
    - test_return_value
    - test_mutation_smallest_input
    - test_mutation_ordinary_input
    - test_mutation_repeated_value
  Status: ALL CHECKS PASSED
  ```
- **Deliberate Failure Validation:** Changing an assertion to `assert(cnt[0] == 999);` caused the runner to fail with a non-zero exit code (`250`) and print `Mutation check failed (smallest input): expected cnt[0] == 999, got 1`, confirming error reporting works as expected.

---

## Links to Check & Evidence Files
- **Test Runner Script:** [work/R22-T031/check.py](file:///Users/prishi/C-Plus-Plus/work/R22-T031/check.py)
- **Detailed Evidence & Tool Versions:** [work/R22-T031/evidence.md](file:///Users/prishi/C-Plus-Plus/work/R22-T031/evidence.md)
- **Raw Execution Log:** [work/R22-T031/results.txt](file:///Users/prishi/C-Plus-Plus/work/R22-T031/results.txt)
- **Analysis & Precondition Notes:** [range_queries/notes.md](file:///Users/prishi/C-Plus-Plus/range_queries/notes.md)
- **Source Code with Tests:** [range_queries/mo.cpp](file:///Users/prishi/C-Plus-Plus/range_queries/mo.cpp)
