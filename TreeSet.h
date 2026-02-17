#ifndef TREESET_H
#define TREESET_H

#include <ostream>

template<typename T>
class TreeSet {
private:
    struct TreeNode {
        TreeNode(T value): left(nullptr), value(value), right(nullptr), height_(1) {};
        TreeNode* left;
        T value;
        TreeNode* right;
        unsigned int height_;
    };
public:
    TreeSet(): root_(nullptr), size_(0) {};

    TreeSet(const TreeSet<T>& tset) = delete;
    TreeSet<T>& operator=(const TreeSet<T>& tset) = delete;
    ~TreeSet() = delete;

    //void print() const; // По заданию нужно -_-
    bool insert(T key) {
        if (!root_) {
            root_ = new TreeNode<T>(key);
            size_ = 1;
            return true;
        }
        TreeNode* cur = root_;
        //TODO: Доделать
        
        return true;
    };

    bool contains(T key) const;
    bool erase(T key);
    bool strictly_balanced() const;

private:
    TreeNode* root_ = nullptr;
    size_t size_ = 0;

    static unsigned int height(const TreeNode* node) {
        return (node ? node->height_: 0)
    }

    static unsigned int bfactor(const TreeNode* node) {
        return height(node->right)-height(node->left);
    }

    void fix_height_(TreeNode* node) {
        unsigned int hl = height(node->left);
        unsigned int hr = height(node->right);
        node->height_ = (hl > hr? hl: hr) + 1;
    }

    void rotate_left_(TreeNode* node) {
        TreeNode* r = node->right;
        node->right = r->left;
        r->left = node;
        // TODO: Работа с высотами
    }

    void rotate_right_(TreeNode* node) {
        TreeNode* l = node->left;
        node->left = l->right;
        l->right = node;
        // TODO: Работа с высотами
    }

    void big_rotate_left_(TreeNode<T>* node) {
        rotate_right_(node->right);
        rotate_left_(node);
    }

    void big_rotate_right_(TreeNode<T>* node) {
        rotate_left(node->right);
        rotate_right_(node);
    }

    void balance_tree_() {};
};

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const TreeSet<T>&);

#endif /* TREESET_H */ 