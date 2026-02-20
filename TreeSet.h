#ifndef TREESET_H
#define TREESET_H

#include <iostream>

template<typename T>
class TreeSet {
private:
    struct TreeNode {
        TreeNode(T value): left(nullptr), value(value), right(nullptr), height_(1) {};
        ~TreeNode() {std::cout << value << " deleted ";}
        TreeNode* left;
        T value;
        TreeNode* right;
        unsigned int height_;
    };
public:
    TreeSet(): root_(nullptr), size_(0) {};

    TreeSet(const TreeSet<T>& tset) = delete;
    TreeSet<T>& operator=(const TreeSet<T>& tset) = delete;
    ~TreeSet() {
        destroy_(root_);
    }

    size_t size() const { return size_; }
    size_t height() const { return height(root_);}

    void print() const {
        print_(root_);
        std::cout << "\n";
    }

    bool insert(T key) {
        if (this->contains(key)) return false;

        root_ = insert_(root_, key);
        // if (!root_) {
        //     root_ = new TreeNode(key);
        //     size_ = 1;
        //     return true;
        // }
        // TreeNode* cur = root_;
        // while (cur) {
        //     if (cur->value == key) return false;
        //     if (!cur->left && !cur->right) break;

        //     if (cur->value > key && cur->left) {
        //         cur = cur->left; continue;
        //     }
        //     if (cur->value < key && cur->right) {
        //         cur = cur->right; continue;
        //     }
        //     break;
        // }

        // if (cur->value > key) cur->left = new TreeNode(key);
        // else cur->right = new TreeNode(key);
 
        size_++;
        return true;
    };

    bool contains(T key) const {
        const TreeNode* cur = root_;
        while (cur) {
            if (cur->value == key) return true;

            if (cur->value > key) cur = cur->left;
            else cur = cur->right;
        }
        return false;
    }

    // bool erase(T key);
    // bool strictly_balanced() const;

private:
    TreeNode* root_ = nullptr;
    size_t size_ = 0;

    static unsigned int height(const TreeNode* node) {
        return (node ? node->height_: 0);
    }

    static unsigned int bfactor(const TreeNode* node) {
        return height(node->right) - height(node->left);
    }

    static void fix_height(TreeNode* node) {
        unsigned int hl = height(node->left);
        unsigned int hr = height(node->right);
        node->height_ = (hl > hr? hl: hr) + 1;
    }

    static TreeNode* rotate_left(TreeNode* node) {
        TreeNode* r = node->right;
        node->right = r->left;
        r->left = node;

        fix_height(r);
        fix_height(node);
        return r;
    }

    static TreeNode* rotate_right(TreeNode* node) {
        TreeNode* l = node->left;
        node->left = l->right;
        l->right = node;

        fix_height(l);
        fix_height(node);
        return l;
    }

    static TreeNode* balance_node(TreeNode* node) {
        fix_height(node);
        if (bfactor(node) == 2) {
            if (bfactor(node->right) < 0)
                node->right = rotate_right(node->right);
            return rotate_left(node);
        }
        if (bfactor(node) == -2) {
            if (bfactor(node->left) > 0)
                node->left = rotate_left(node->left);
            return rotate_right(node);
        }
        return node;
    };

    // void big_rotate_left_(TreeNode* node) {
    //     rotate_right_(node->right);
    //     rotate_left_(node);
    // }

    // void big_rotate_right_(TreeNode* node) {
    //     rotate_left(node->right);
    //     rotate_right_(node);
    // }

    static TreeNode* insert_(TreeNode* node, T key) {
        if (!node) return new TreeNode(key);
        if (node->value > key)
            node->left = insert_(node->left, key);
        else
            node->right = insert_(node->right, key);
        return balance_node(node);
    }

    static void destroy_(const TreeNode* root) {
        if (!root) return;
        destroy_(root->left);
        destroy_(root->right);
        delete root;
    };

    static void print_(const TreeNode* node) { // TODO: Сделать нагляднее
        if (!node) return;
        std::cout << "(" << node->value << ")";
        if (node->left) {
            std::cout << " <";
            print_(node->left);
            std::cout << ">, ";
        }
        if (node->right) {
            std::cout << " [";
            print_(node->right);
            std::cout << "]";
        }
    }
};

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const TreeSet<T>&);

#endif /* TREESET_H */ 