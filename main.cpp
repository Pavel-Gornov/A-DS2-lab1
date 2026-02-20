#include <iostream>
#include <chrono>
#include "TreeSet.h"

size_t lcg(){
    static size_t x = 0;
    x = (1021*x+24631) % 116640;
    return x;
}

double benchmark_insert(size_t amount) {
    auto start = std::chrono::steady_clock::now();
    TreeSet<size_t> set = TreeSet<size_t>();
    for (int i = 0; i < amount; i++) {
        set.insert(lcg());
    }
    auto end = std::chrono::steady_clock::now();

    auto elapsed_ns = duration_cast<std::chrono::nanoseconds>(end - start).count();
    double elapsed_ms = (double) elapsed_ns / 1000000;

    std::cout << "benchmark_insert\n";
    std::cout << "time elapsed: " << elapsed_ms << "ms\n";
    return elapsed_ms;
}

double benchmark_full_set(size_t amount) {
    TreeSet<size_t> set = TreeSet<size_t>();
    for (int i = 0; i < amount; i++) {
        set.insert(lcg());
    }
    auto start = std::chrono::steady_clock::now();
    set.insert(lcg());
    auto end = std::chrono::steady_clock::now();

    auto elapsed_ns = duration_cast<std::chrono::nanoseconds>(end - start).count();
    double elapsed_ms = (double) elapsed_ns / 1000000;
    std::cout << "benchmark_full_set (insert)\n";
    std::cout << "time elapsed: " << elapsed_ms << "ms\n";

    start = std::chrono::steady_clock::now();
    set.erase(lcg());
    end = std::chrono::steady_clock::now();
    elapsed_ns = duration_cast<std::chrono::nanoseconds>(end - start).count();
    elapsed_ms = (double) elapsed_ns / 1000000;
    std::cout << "benchmark_full_set (erase)\n";
    std::cout << "time elapsed: " << elapsed_ms << "ms\n";
    return 0;
}

double benchmark_contains(size_t amount) {
    TreeSet<size_t> set = TreeSet<size_t>();
    for (int i = 0; i < amount; i++) {
        set.insert(lcg());
    }
    auto start = std::chrono::steady_clock::now();
    set.contains(lcg());
    auto end = std::chrono::steady_clock::now();

    auto elapsed_ns = duration_cast<std::chrono::nanoseconds>(end - start).count();
    double elapsed_ms = (double) elapsed_ns / 1000000;
    std::cout << "benchmark_contains\n";
    std::cout << "time elapsed: " << elapsed_ms << "ms\n";
    return elapsed_ms;
}

template<typename T>
bool is_subsets(const TreeSet<T>& set1, const TreeSet<T>& set2) {
    if (set1.size() > set2.size()) {
        auto it = set2.begin();
        while (it.has_next()) {
            T el = it.next();
            if (!set1.contains(el)) return false; 
        }
    }
    else {
        auto it = set1.begin();
        while (it.has_next()) {
            T el = it.next();
            if (!set2.contains(el)) return false; 
        }
    }
    return true;
}


int main() {
    // TreeSet<int> tset = TreeSet<int>();
    // for (int i = 0; i < 12; i++) {
    //     tset.insert(i);
    // }
    // tset.print();
    
    // std::cout << "size: " << tset.size() << "\nhight: " <<tset.height() << "\n";

    // tset.erase(7);
    // tset.print();
    // std::cout << "size: " << tset.size() << "\nhight: " <<tset.height() << "\n";
    
    TreeSet<int> set1 = TreeSet<int>();
    TreeSet<int> set2 = TreeSet<int>();

    for (int i = 0; i < 12; i++) {
        set1.insert(i);
    }
    set2.insert(1);
    set2.insert(2);

    std::cout << is_subsets(set1, set2) << "\n";
    //benchmark_full_set(100000);
}