#include <cassert>    /// for assert
#include <iostream>   /// for std::cout
#include <stdexcept>  /// std::invalid_argument
#include <vector>     /// for std::vector

#include "./stack.hpp"

template <typename T>
void testConstructedStackIsEmpty() {
    const stack<T> curStack;
    assert(curStack.isEmptyStack());
}

void testPush() {
    using valueType = int;
    stack<valueType> curStack;
    curStack.push(10);
    curStack.push(20);
    curStack.push(30);
    curStack.push(40);
    const auto expectedData = std::vector<valueType>({40, 30, 20, 10});
    assert(curStack.toVector() == expectedData);
}

void testTop() {
    using valueType = unsigned;
    stack<valueType> curStack;
    curStack.push(1);
    curStack.push(2);
    curStack.push(3);
    curStack.push(4);
    assert(curStack.top() == static_cast<valueType>(4));
}

void testPop() {
    using valueType = int;
    stack<valueType> curStack;
    curStack.push(100);
    curStack.push(200);
    curStack.push(300);

    assert(curStack.top() == static_cast<valueType>(300));
    curStack.pop();
    assert(curStack.top() == static_cast<valueType>(200));
    curStack.pop();
    assert(curStack.top() == static_cast<valueType>(100));
    curStack.pop();
    assert(curStack.isEmptyStack());
}

void testClear() {
    stack<int> curStack;
    curStack.push(1000);
    curStack.push(2000);
    curStack.clear();
    assert(curStack.isEmptyStack());
}

void testCopyOfStackHasSameData() {
    stack<int> stackA;
    stackA.push(10);
    stackA.push(200);
    stackA.push(3000);
    const auto stackB(stackA);
    assert(stackA.toVector() == stackB.toVector());
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

    assert(stackA.toVector() == expectedDataA);
    assert(stackB.toVector() == expectedDataB);
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

    assert(stackA.toVector() == expectedDataA);
    assert(stackB.toVector() == expectedDataB);
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

    assert(stackA.toVector() == expectedDataA);
    assert(stackB.toVector() == expectedDataB);
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

    assert(stackA.toVector() == expectedDataA);
    assert(stackB.toVector() == expectedDataB);
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

    assert(stackA.toVector() == expectedDataA);
    assert(stackB.toVector() == expectedDataB);

    stackB = stackA;
    stackA.pop();
    stackB.push(5);
    stackB.push(6);

    const auto otherExpectedDataA = std::vector<valueType>({10});
    const auto otherExpectedDataB = std::vector<valueType>({6, 5, 20, 10});

    assert(stackA.toVector() == otherExpectedDataA);
    assert(stackB.toVector() == otherExpectedDataB);
}

void testTopThrowsAnInvalidArgumentWhenStackEmpty() {
    const stack<long double> curStack;
    bool wasException = false;
    try {
        curStack.top();
    } catch (const std::invalid_argument&) {
        wasException = true;
    }
    assert(wasException);
}

void testPopThrowsAnInvalidArgumentWhenStackEmpty() {
    stack<bool> curStack;
    bool wasException = false;
    try {
        curStack.pop();
    } catch (const std::invalid_argument&) {
        wasException = true;
    }
    assert(wasException);
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

    testTopThrowsAnInvalidArgumentWhenStackEmpty();
    testPopThrowsAnInvalidArgumentWhenStackEmpty();

    std::cout << "All tests pass!\n";
    return 0;
}
