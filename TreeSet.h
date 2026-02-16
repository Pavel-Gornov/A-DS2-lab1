#ifndef TREESET_H
#define TREESET_H

#include <ostream>

template<typename T> 
class TreeSet {
private:
    struct TreeNode {
        TreeNode(T value): left(nullptr), value(value), right(nullptr) {};
        TreeNode* left;
        T value;
        TreeNode* right;
    };
public:
    TreeSet(): root_(nullptr), size_(0) {};

    TreeSet(const TreeSet<T>& tset);
    TreeSet<T>& operator=(const TreeSet<T>& tset);
    ~TreeSet();

    void print() const; // По заданию нужно -_-
    bool insert(T key);
    bool contains(T key) const;
    bool erase(T key);
    bool strictly_balanced() const;

private:
    TreeNode* root_ = nullptr;
    size_t size_ = 0;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const TreeSet<T>&);

#endif /* TREESET_H */ 