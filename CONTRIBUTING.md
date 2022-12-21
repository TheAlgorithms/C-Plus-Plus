# CONTRIBUTION GUIDELINES

## Before contributing

Welcome to [TheAlgorithms/C-Plus-Plus](https://github.com/TheAlgorithms/C-Plus-Plus)! Before submitting pull requests, please make sure that you have **read the whole guidelines**. If you have any doubts about this contribution guide, please open [an issue](https://github.com/TheAlgorithms/C-Plus-Plus/issues/new/choose) or ask on our [Discord server](https://the-algorithms.com/discord/), and clearly state your concerns.

## Contributing

### Maintainer/reviewer

**Please check the [reviewer code](https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/REVIEWER_CODE.md) file for maintainers and reviewers.**

### Contributor

Being a contributor at The Algorithms, we request you to follow the points mentioned below:

- You did your own work.
  - No plagiarism is allowed. Any plagiarized work will not be merged.
- Your work will be distributed under the [MIT License](https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/LICENSE) once your pull request has been merged.
- Please follow the repository guidelines and standards mentioned below.

**New implementation** New implementations are welcome!

You can add new algorithms or data structures that are **not present in the repository** or that can **improve** the old implementations (**documentation**, **improving test cases**, removing bugs, or in any other reasonable sense)

**Issues** Please avoid opening issues asking to be "assigned” to a particular algorithm. This merely creates unnecessary noise for maintainers. Instead, please submit your implementation in a pull request, and it will be evaluated by project maintainers.

### Making Changes

#### Code

- Please use the directory structure of the repository.
- Make sure the file extensions are `*.hpp`, `*.h` or `*.cpp`.
- Don't use **`bits/stdc++.h`** because this is quite Linux-specific and slows down the compilation process.
- Organize your code using **`struct`**, **`class`**, and/or **`namespace`** keywords.
- If an implementation of the algorithm already exists, please refer to the [file-name section below](#new-file-name-guidelines).
- You can suggest reasonable changes to existing algorithms.
- Strictly use snake_case (underscore_separated) in filenames.
- If you have added or modified code, please make sure the code compiles before submitting.
- Our automated testing runs [**CMake**](https://cmake.org/) on all the pull requests, so please be sure that your code passes before submitting.
- Please conform to [Doxygen](https://www.doxygen.nl/manual/docblocks.html) standards and document the code as much as possible. This not only facilitates the readers but also generates the correct info on the website.
- **Be consistent in the use of these guidelines.**

#### Documentation

- Make sure you put useful comments in your code. Do not comment on obvious things.
- Please avoid creating new directories if at all possible. Try to fit your work into the existing directory structure. If you want to create a new directory, then please check if a similar category has been recently suggested or created by other pull requests.
- If you have modified/added documentation, please ensure that your language is concise and must not contain grammatical errors.
- Do not update [`README.md`](https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/README.md) along with other changes. First, create an issue and then link to that issue in your pull request to suggest specific changes required to [`README.md`](https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/README.md).
- The repository follows [Doxygen](https://www.doxygen.nl/manual/docblocks.html) standards and auto-generates the [repository website](https://thealgorithms.github.io/C-Plus-Plus). Please ensure the code is documented in this structure. A sample implementation is given below.

#### Test

- Make sure to add examples and test cases in your `main()` function.
- If you find an algorithm or document without tests, please feel free to create a pull request or issue describing suggested changes.
- Please try to add one or more `test()` functions that will invoke the algorithm implementation on random test data with the expected output. Use the `assert()` function to confirm that the tests will pass. Requires including the `cassert` library.

#### Typical structure of a program

```cpp
/**
 * @file
 * @brief Add one line description here. Should contain a Wikipedia
 * link or another source explaining the algorithm/implementation.
 * @details
 * This is a multi-line
 * description containing links, references,
 * math equations, etc.
 * @author [Name](https://github.com/handle)
 * @see related_file.cpp, another_file.cpp
 */

#include <cassert>   /// for assert
#include             /// for `some function here`

/**
 * @namespace <folder name>
 * @brief <namespace description>
 */
namespace name {

/**
 * @brief Class documentation
 */
class class_name {
 private:
    int variable;   ///< short info of this variable
    char *message;  ///< short info

 public:
    // other members should be also documented as below
}

/**
 * @brief Function documentation
 * @tparam T this is a one-line info about T
 * @param param1 on-line info about param1
 * @param param2 on-line info about param2
 * @returns `true` if ...
 * @returns `false` if ...
 */
template<class T>
bool func(int param1, T param2) {
    // function statements here
    if (/*something bad*/) {
        return false;
    }

    return true;
}
}  // namespace name

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    /* descriptions of the following test */
    assert(func(...) == ...); // this ensures that the algorithm works as expected

    // can have multiple checks
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // run self-test implementations
    // code here
    return 0;
}
```

#### File Name guidelines

- Use lowercase words with ``"_"`` as a separator
- For instance

```markdown
MyNewCppClass.CPP       is incorrect
my_new_cpp_class.cpp    is correct format
```

- It will be used to dynamically create a directory of files and implementation.
- File name validation will run on Docker to ensure validity.
- If an implementation of the algorithm already exists and your version is different from that implemented, please use incremental numeric digit as a suffix. For example: if `median_search.cpp` already exists in the `search` folder, and you are contributing a new implementation, the filename should be `median_search2.cpp`. For a third implementation, `median_search3.cpp`, and so on.

#### Directory guidelines

- We recommend adding files to existing directories as much as possible.
- Use lowercase words with ``"_"`` as separator ( no spaces or ```"-"``` allowed )
- For instance

```markdown
SomeNew Fancy-Category          is incorrect
some_new_fancy_category         is correct
```

- Filepaths will be used to dynamically create a directory of our algorithms.
- Filepath validation will run on GitHub Actions to ensure compliance.

##### Integrating CMake in a new directory

In case a new directory is 100% required, `CMakeLists.txt` file in the root directory needs to be updated, and a new `CMakeLists.txt` file needs to be created within the new directory.

An example of how your new `CMakeLists.txt` file should look like. Note that if there are any extra libraries/setup required, you must include that in this file as well.

```cmake
# If necessary, use the RELATIVE flag, otherwise each source file may be listed
# with full pathname. The RELATIVE flag makes it easier to extract an executable's name
# automatically.

file( GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp )
foreach( testsourcefile ${APP_SOURCES} )
    string( REPLACE ".cpp" "" testname ${testsourcefile} ) # File type. Example: `.cpp`
    add_executable( ${testname} ${testsourcefile} )

    set_target_properties(${testname} PROPERTIES LINKER_LANGUAGE CXX)
    if(OpenMP_CXX_FOUND)
        target_link_libraries(${testname} OpenMP::OpenMP_CXX)
    endif()
    install(TARGETS ${testname} DESTINATION "bin/<foldername>") # Folder name. Do NOT include `<>`

endforeach( testsourcefile ${APP_SOURCES} )
```

The `CMakeLists.txt` file in the root directory should be updated to include the new directory.\
Include your new directory after the last subdirectory. Example:

```cmake
...
add_subdirectory(divide_and_conquer)
add_subdirectory(<foldername>)
```

#### Commit Guidelines

- It is recommended to keep your changes grouped logically within individual commits. Maintainers find it easier to understand changes that are logically spilled across multiple commits. Try to modify just one or two files in the same directory. Pull requests that span multiple directories are often rejected.

```bash
git add file_xyz.cpp
git commit -m "your message"
```

Examples of commit messages with semantic prefixes:

```markdown
fix: xyz algorithm bug
feat: add xyx algorithm, class xyz
test: add test for xyz algorithm
docs: add comments and explanation to xyz algorithm/improve contributing guidelines
chore: update Gitpod badge
```

Common prefixes:

- fix: A bug fix
- feat: A new feature
- docs: Documentation changes
- test: Correct existing tests or add new ones
- chore: Miscellaneous changes that do not match any of the above.

### Pull Requests

- Checkout our [pull request template](https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/.github/pull_request_template.md)

#### Building Locally

Before submitting a pull request,
 build the code locally or using the convenient [![Gitpod Ready-to-Code](https://img.shields.io/badge/Gitpod-Ready--to--Code-blue?logo=gitpod)](https://gitpod.io/#https://github.com/TheAlgorithms/C-Plus-Plus) service.

```bash
cmake -B build -S .
```

#### Static Code Analyzer

We use [`clang-tidy`](https://clang.llvm.org/extra/clang-tidy/) as a static code analyzer with a configuration in [`.clang-tidy`](https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/.clang-tidy).

```bash
clang-tidy --fix --quiet -p build subfolder/file_to_check.cpp --
```

#### Code Formatter

[`clang-format`](https://clang.llvm.org/docs/ClangFormat.html) is used for code formatting.

- Installation (only needs to be installed once.)
  - Mac (using home-brew): `brew install clang-format`
  - Mac (using macports): `sudo port install clang-10 +analyzer`
  - Windows (MSYS2 64-bit): `pacman -S mingw-w64-x86_64-clang-tools-extra`
  - Linux (Debian): `sudo apt-get install clang-format-10 clang-tidy-10`
- Running (all platforms): `clang-format -i -style="file" my_file.cpp`

#### GitHub Actions

- Enable GitHub Actions on your fork of the repository.
After enabling, it will execute `clang-tidy` and `clang-format` after every push (not a commit).
  - Click on the tab "Actions", then click on the big green button to enable it.

![GitHub Actions](https://user-images.githubusercontent.com/51391473/94609466-6e925100-0264-11eb-9d6f-3706190eab2b.png)

- The result can create another commit if the actions made any changes on your behalf.
- Hence, it is better to wait and check the results of GitHub Actions after every push.
- Run `git pull` in your local clone if these actions made many changes to avoid merge conflicts.

Most importantly,

- Happy coding!
