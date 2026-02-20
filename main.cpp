#include <iostream>
#include "TreeSet.h"

int main() {
    TreeSet<int> tset = TreeSet<int>();
    for (int i = 0; i < 12; i++) {
        tset.insert(i);
    }
    tset.print();
    
    std::cout << "size: " << tset.size() << "\nhight: " <<tset.height() << "\n";
}