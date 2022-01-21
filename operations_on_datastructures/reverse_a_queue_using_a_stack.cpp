#include <queue> 
#include <stack>


template <typename T>
std::queue<T> reverseQueue (std::queue<T> input) {
    // temp stack to store values from queue in
    std::stack<T> st;

    while (!input.empty()) {
        st.push() = input.front();
        input.pop();
    }

    while(!st.empty()) {
        input.push() = st.top();
        st.pop();
    }
    return input;

}