#include <iostream>

#include "../bitset.h"

int main () {
    Bitset b1(10), b2(0);
    std::cout << b1.as_bytes() << std::endl;

    std::cout << b2.size() << std::endl;
    b2.from_bytes(3, "\0\02");
    std::cout << b2.size() << std::endl;
    for (int i = 0; i < (int)b2.size(); ++i) {
        std::cout << b2.get(i); 
    
    }
    std::cout << std::endl;
    
    std::cout << "До замены:" << b2.get(0) << std::endl;
    b2.set(0, 1);
    std::cout << "После  замены:" << b2.get(0) << std::endl;
    return 0;
}
