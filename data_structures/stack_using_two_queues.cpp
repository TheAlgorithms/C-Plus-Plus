/**
 * @file
 * @brief Implementation of stack using two queues
 * @author [Gopal-Dahale](https://github.com/Gopal-Dahale)
 * @details
 * In this alogrithm, stack is implemented by making the pop operation costly.
 * push(x) operation enqueues x to q1.
 * pop() operation puts the first n-1 elements from q1 to q2 and then dequeue
 * the last element from q1. Finally the names q1 and q2 are swapped. The time
 * Complexity of the algorithm is \f$O(n)\f$ for pop() and \f$O(1)\f$ for
 * push().
 */

#include <cassert>
#include <iostream>
#include <queue>
#include <string>

/**
 * @namespace data_structures
 * @brief Data Structures algorithms
 */
namespace data_structures
{
    template <typename T>
    class Stack
    {
    private:
        std::queue<T> q1, q2;

    public:
        /**
         * Pushes the given element to top of stack
         */
        void push(T data) { q1.push(data); }

        /**
         * Pops the topmost element of stack
         */
        void pop()
        {
            // push first n-1 elements from q1 to q2
            // pop the last element from q1
            // swap q1 and q2
            if (q1.size() == 0)
            {
                return;
            }

            while (q1.size() > 1)
            {
                q2.push(q1.front());
                q1.pop();
            }
            // pops the last element from q1;
            q1.pop();

            // swaps q1 with q2
            q1.swap(q2);
        }

        /**
         * Returns the topmost element of stack.
         * Returns -1 if stack is empty
         */
        T top()
        {
            if (q1.size() == 0)
            {
                return T();
            }

            while (q1.size() > 1)
            {
                q2.push(q1.front());
                q1.pop();
            }

            T top_element = q1.front();
            q2.push(q1.front());
            q1.pop();

            // swaps q1 with q2
            q1.swap(q2);

            return top_element;
        }

        /**
         * Returns the size of stack
         */
        int size() { return q1.size() + q2.size(); }

        /**
         * Returns true if stack is empty, otherwise false
         */
        bool empty() { return (q1.size() == 0); }
    };

} // namespace data_structures

/**
 * class Book with book name and it's price
 */
class Book
{
private:
    std::string book_name{std::string()};
    double book_price{double()};

public:
    /**
     * default constructor
     */
    Book()
    {
    }

    /**
     * parameterized constructor
     */
    Book(std::string book_name, double book_price)
        : book_name{std::move(book_name)}, book_price{std::move(book_price)}
    {
    }

    /**
     * Returns name of the book
     */
    std::string get_book_name() const
    {
        return this->book_name;
    }

    /**
     * Returns price of the book
     */
    double get_book_price() const
    {
        return this->book_price;
    }

    /**
     * comparison of two books
     */
    bool operator==(const Book &b) const
    {
        return ((b.get_book_name() == this->book_name) && (b.get_book_price() == this->book_price));
    }
};

/**
 * overloading operator<< to print book details
 */
std::ostream &operator<<(std::ostream &os, const Book &book)
{
    os << book.get_book_name() << ", " << book.get_book_price() << "\n";
    return os;
}

/**
 * utility function to print stack
 */
template <typename T>
void print(data_structures::Stack<T> s)
{
    while (!s.empty())
    {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << "\n";
}

/**
 * Testing function
 */
void test()
{
    // stack of integers
    data_structures::Stack<int> s;

    // push
    for (int i = 0; i < 10; i++)
    {
        s.push(i);
    }

    // iterating over stack
    print(s);

    assert(s.top() == 9);
    std::cout << s.top() << "\n";

    // size of stack
    assert(s.size() == 10);
    std::cout << "Stack contains " << s.size() << " elements\n";

    // emptying the stack
    while (!s.empty())
    {
        s.pop();
    }

    assert(s.empty() == true);
    assert(s.top() == int());
    std::cout << "Stack is empty: " << s.empty() << "\n";
    std::cout << "Topmost element is: " << s.top() << "\n";

    // stack of books
    data_structures::Stack<Book> books;

    books.push(Book("The Philosophy of Prayer", 1122.99));
    books.push(Book("Mahatma Gandhi Autobiography", 114.98));
    books.push(Book("Wings of Fire", 349.86));
    books.push(Book("My Gita", 209.95));
    books.push(Book("The Blue Umbrella", 61.32));

    print(books);

    assert(books.top() == Book("The Blue Umbrella", 61.32));
    std::cout << books.top() << "\n";

    // size of stack
    assert(books.size() == 5);
    std::cout << "Stack contains " << books.size() << " books\n";

    // emptying the stack
    while (!books.empty())
    {
        books.pop();
    }

    assert(books.empty() == true);
    assert(books.top() == Book());
    std::cout << "Stack is empty: " << books.empty() << "\n";
    std::cout << "Topmost element is: " << books.top() << "\n";
}

int main()
{
    test();
    return 0;
}
