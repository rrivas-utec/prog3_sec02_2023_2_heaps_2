#include <iostream>
#include "heap.h"

void ejemplo_1() {
    utec::heap<int> h1;
    h1.push(10);
    h1.push(30);
    h1.push(20);
    h1.push(50);
    h1.push(15);
    while (!h1.empty()) {
        cout << h1.top() << " ";
        h1.pop();
    }
}

void ejemplo_2() {
    utec::heap<double> h1(std::vector<double>{10.0, 30.5, 20.4, 50.3, 15.1});
    while (!h1.empty()) {
        cout << h1.top() << " ";
        h1.pop();
    }
}

void ejemplo_3() {
    utec::heap<double, vector, greater<>> h1(std::vector<double>{10.0, 30.5, 20.4, 50.3, 15.1});
    while (!h1.empty()) {
        cout << h1.top() << " ";
        h1.pop();
    }
}

void ejemplo_4() {
    utec::heap<double, vector, greater<>> h1(std::vector<double>{10.0, 30.5, 20.4, 50.3, 15.1}, greater<>{});
    while (!h1.empty()) {
        cout << h1.top() << " ";
        h1.pop();
    }
}

int main() {
    ejemplo_1();
    cout << endl;
    ejemplo_2();
    cout << endl;
    ejemplo_3();
    cout << endl;
    ejemplo_4();
    return 0;
}
