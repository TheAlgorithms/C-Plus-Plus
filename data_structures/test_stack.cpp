#include <iostream>
#include <vector>

#include "./stack.hpp"

void assertTrue(const bool inValue) {
    if (!inValue) {
        std::cout << "Assertion fails!\n";
        exit(1);
    }
}

template <typename T>
void assertEqual(const T& valA, const T& valB) {
    assertTrue(valA == valB);
}

template <typename T>
void testConstructedStackIsEmpty() {
    stack<T> curStack;
    assertTrue(curStack.isEmptyStack());
}

void testPush() {
    using valueType = int;
    stack<valueType> curStack;
    curStack.push(10);
    curStack.push(20);
    curStack.push(30);
    curStack.push(40);
    const auto expectedData = std::vector<valueType>({40, 30, 20, 10});
    assertEqual(curStack.toVector(), expectedData);
}

void testTop() {
    using valueType = unsigned;
    stack<valueType> curStack;
    curStack.push(1);
    curStack.push(2);
    curStack.push(3);
    curStack.push(4);
    assertEqual(curStack.top(), static_cast<valueType>(4));
}

void testPop() {
    using valueType = int;
    stack<valueType> curStack;
    curStack.push(100);
    curStack.push(200);
    curStack.push(300);

    assertEqual(curStack.top(), static_cast<valueType>(300));
    curStack.pop();
    assertEqual(curStack.top(), static_cast<valueType>(200));
    curStack.pop();
    assertEqual(curStack.top(), static_cast<valueType>(100));
    curStack.pop();
    assertTrue(curStack.isEmptyStack());
}

void testClear() {
    stack<int> curStack;
    curStack.push(1000);
    curStack.push(2000);
    curStack.clear();
    assertTrue(curStack.isEmptyStack());
}

void testCopyOfStackHasSameData() {
    stack<int> stackA;
    stackA.push(10);
    stackA.push(200);
    stackA.push(3000);
    const auto stackB(stackA);
    assertEqual(stackA.toVector(), stackB.toVector());
}

void testPushingToCopyDoesNotChangeOriginal() {
    using valueType = int;
    stack<valueType> stackA;
    stackA.push(10);
    stackA.push(20);
    stackA.push(30);
    auto stackB(stackA);
    stackB.push(40);

    const auto expectedDataA = std::vector<valueType>({30, 20, 10});
    const auto expectedDataB = std::vector<valueType>({40, 30, 20, 10});

    assertEqual(stackA.toVector(), expectedDataA);
    assertEqual(stackB.toVector(), expectedDataB);
}

void testPoppingFromCopyDoesNotChangeOriginal() {
    using valueType = int;
    stack<valueType> stackA;
    stackA.push(10);
    stackA.push(20);
    stackA.push(30);
    auto stackB(stackA);
    stackB.pop();

    const auto expectedDataA = std::vector<valueType>({30, 20, 10});
    const auto expectedDataB = std::vector<valueType>({20, 10});

    assertEqual(stackA.toVector(), expectedDataA);
    assertEqual(stackB.toVector(), expectedDataB);
}

void testPushingToOrginalDoesNotChangeCopy() {
    using valueType = int;
    stack<valueType> stackA;
    stackA.push(10);
    stackA.push(20);
    stackA.push(30);
    const auto stackB(stackA);
    stackA.push(40);

    const auto expectedDataA = std::vector<valueType>({40, 30, 20, 10});
    const auto expectedDataB = std::vector<valueType>({30, 20, 10});

    assertEqual(stackA.toVector(), expectedDataA);
    assertEqual(stackB.toVector(), expectedDataB);
}

void testPoppingFromOrginalDoesNotChangeCopy() {
    using valueType = int;
    stack<valueType> stackA;
    stackA.push(10);
    stackA.push(20);
    stackA.push(30);
    const auto stackB(stackA);
    stackA.pop();

    const auto expectedDataA = std::vector<valueType>({20, 10});
    const auto expectedDataB = std::vector<valueType>({30, 20, 10});

    assertEqual(stackA.toVector(), expectedDataA);
    assertEqual(stackB.toVector(), expectedDataB);
}

void testAssign() {
    using valueType = int;
    stack<valueType> stackA;
    stackA.push(10);
    stackA.push(20);
    stackA.push(30);
    stack<valueType> stackB = stackA;
    stackA.pop();
    stackB.push(40);

    const auto expectedDataA = std::vector<valueType>({20, 10});
    const auto expectedDataB = std::vector<valueType>({40, 30, 20, 10});

    assertEqual(stackA.toVector(), expectedDataA);
    assertEqual(stackB.toVector(), expectedDataB);

    stackB = stackA;
    stackA.pop();
    stackB.push(5);
    stackB.push(6);

    const auto otherExpectedDataA = std::vector<valueType>({10});
    const auto otherExpectedDataB = std::vector<valueType>({6, 5, 20, 10});

    assertEqual(stackA.toVector(), otherExpectedDataA);
    assertEqual(stackB.toVector(), otherExpectedDataB);
}

int main() {
    testConstructedStackIsEmpty<int>();
    testConstructedStackIsEmpty<char>();

    testPush();
    testPop();
    testClear();

    testCopyOfStackHasSameData();
    testPushingToCopyDoesNotChangeOriginal();
    testPoppingFromCopyDoesNotChangeOriginal();
    testPushingToOrginalDoesNotChangeCopy();
    testPoppingFromOrginalDoesNotChangeCopy();

    testAssign();

    std::cout << "All tests pass!\n";
    return 0;
}
