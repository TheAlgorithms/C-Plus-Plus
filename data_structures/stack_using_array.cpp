#include <bits/stdc++.h>
using namespace std;


//void pop() {
//    if (stack_idx == 0) {
//        std::cout << "\nUnderflow";
//    } else {
//        std::cout << "\n" << stack[--stack_idx] << " deleted";
//    }
//}
//
//void show() {
//    for (int i = 0; i < stack_idx; i++) {
//        std::cout << stack[i] << "\n";
//    }
//}
//
//void topmost() { std::cout << "\nTopmost element: " << stack[stack_idx - 1]; }
int main() {
    
    stack <int> stk;
    stack <int>s;
    int ch, x;
    do {
        cout << "\n0. Exit";
        cout << "\n1. Push";
        cout << "\n2. Pop";
        cout << "\n3. Print";
        cout << "\n4. Print topmost element:";
        cout << "\nEnter Your Choice : ";
        cin >> ch;
        if (ch == 1) {
            std::cout << "\nInsert : ";
            std::cin >> x;
            stk.push(x);
        } 
		else if (ch == 2) {
            stk.pop();
        } 
		else if (ch == 3) {
            while(!stk.empty()){
            	s.push(stk.top());
            	stk.pop();
			}
			while(!s.empty()){
				cout<<s.top()<<endl;
				stk.push(s.top());
				s.pop();
			}
        } 
		else if (ch == 4) {
            cout<<stk.top();
        }
    } while (ch != 0);

    

    return 0;
}
