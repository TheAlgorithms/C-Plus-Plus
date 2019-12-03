# CONTRIBUTION GUIDELINES

## Before contributing
Welcome to [TheAlgorithms/c-plus-plus](https://github.com/TheAlgorithms/C-Plus-Plus)! Before sending your pull requests, make sure that you **read the whole guidelines**. If you have any doubt on the contribution guide, please feel free to state it clearly in [an issues](https://github.com/TheAlgorithms/C-Plus-Plus/issues/new/choose).

## Contributing
### Contributor 
We are very happy that you consider implementing algorithms and data structure for others! This repository is referenced and used by learners from all over the globe. Being one of our contributors, you agree and confirm that:

- You did your work.
    - No plagiarism allowed. Any plagiarized work  will not be merged.
- Your work will be distributed under [MIT License](License) Once your pull request is merged.
- You submitted work fulfils or mostly fulfils our styles and standards.

**New implementation** New implementation are welcome! 
**Improving comments** and **Adding test cases** are also highly welcome.

### Making Changes

#### Code
- Use the directory structure of the repository.
- File extension for code should be *.h *.cpp.
- Don't use **bits/stdc++.h** because this is quite Linux specific and slows down the compiler process.
- Avoid using **struct**. Instead use the **class** keyword.
- You can suggest any change in present algorithms(if needed).
- Strictly use snake_case (underscore_separated) in your file names, later to be used by a script.
- If you have modified/added code work, make sure the code compiles before submitting.
- **Be consistent in use of there guidelines when submitting**

#### New File Name guidelines
- Use lowercase words with ``"_"`` as separator
- For instance 
```
MyNewCppClass.CPP       is incorrect
my_new_cpp_class.cpp    is correct format
```
- It will be used to dynamically create a directory of files and implementation.
- File name validation will run on docker to ensure the validity.

#### New Directory guidelines 
- We recommend adding files to existing directories as much as possible.
- Use lowercase words with ``"_"`` as separator ( no spaces or ```"-"``` allowed )
- For instance
```
SomeNew Fancy-Category          is incorrect
some_new_fancy_category         is correct

- It will be used to dynamically create a directory of files and implementation.
- File name validation will run on docker to ensure the validity.

#### Commit Guidelines
- It is recommended to keep your changes grouped logically within individual commits. Contributors find it easier to review changes that are split across multiple commits.
```
git add file_xyz.cpp
git commit -m "your message"
```
Examples of commit messages with semantic prefixes:
```
fix: xyz algorithm bug
feat: add xyx algorithm, class xyz
test: add test for xyz algorithm
docs: add comments and explanation to xyz algorithm
```
Common prefixes:
- fix: A bug fix
- feat: A new feature
- docs: Documentation changes
- test: Adding missing tests or correcting existing tests

#### Documentation
- Make sure you put comments in your code.
- Please avoid creating a new directories if at all possible. Try to fit your work into existing directory structure. If you want to create one, please check if the same category has been recently suggested or created by another pull request. 
- If you have modified/added documentation work, ensure your language is concise and contains no grammar errors.
- Do not update the README.md along with other changes, first create an issue and link that issue with the pull request to suggest specific changes to README.md

#### Test
- Make sure you add test cases and examples in the main-function.
- If you find any algorithm or document without tests please feel free to create issue of suggest changes.

### Pull Requests
- Checkout our [pull request template](https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/.github/pull_request_template.md)

- Most importantly,
    - Happy coding!
