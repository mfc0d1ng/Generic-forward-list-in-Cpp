#include <iostream>
#include "include/mfpkg.h"
#include <forward_list>
int main(void)
{
    // Examples
    
    std::puts(""); 

    mfpkg::forward_list<int> test {0, 1, 2, 3, 4};
    
    std::printf("%s", " list test:  ");
    for (auto x : test)
    {
        std::cout << x << " -> ";
    }
    puts("null\n");

    mfpkg::forward_list<float> test1 {};

    for (int i = 0; i < 5; i++)
    {
        test1.push_back(i+0.5);
    }
    
    std::printf("%s", " list test1: ");
    for (auto x : test1)
    {
        std::cout << x << " -> ";
    }
    puts("null\n");

    mfpkg::forward_list<std::string> test2;

    for (int i = 0; i < 3; i++)
    {
        switch (i)
        {
        case 0:
            test2.push_back("World");
            break;
        case 1:
            test2.push_front("Hello");
            break;
        case 2:
            test2.push_back("2024");
            break;        
        default:
            break;
        }
    }
    
    std::printf("%s", " list test2: ");
    for (auto x : test2)
    {
        std::cout << x << " -> ";
    }
    puts("null");

    return 0;
}
