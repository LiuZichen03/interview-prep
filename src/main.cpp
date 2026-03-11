#include <iostream>
#include "dynamic_array.h"

void print(const array& a)
{
    for(int i = 0; i < a.Size(); i++)
        std::cout << a.at(i) << " ";
    std::cout << "(size=" << a.Size() << ", cap=" << a.Capacity() << ")\n";
}

int main()
{
    array a;

    // push_back
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    std::cout << "push 1~4:    "; print(a);

    // prepend
    a.prepend(0);
    std::cout << "prepend 0:   "; print(a);

    // insert
    a.insert(3, 99);
    std::cout << "insert(3,99):"; print(a);

    // erase
    a.erase(3);
    std::cout << "erase(3):    "; print(a);

    // find
    std::cout << "find(3) = " << a.find(3) << "\n";
    std::cout << "find(9) = " << a.find(9) << "\n";

    // remove
    a.push_back(2);
    a.push_back(2);
    std::cout << "add two 2s:  "; print(a);
    a.remove(2);
    std::cout << "remove(2):   "; print(a);

    // pop_back
    a.pop_back();
    std::cout << "pop_back:    "; print(a);
}
