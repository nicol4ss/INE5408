// Copyright [2021] Nicolas Elias
#ifndef STRUCTURES_BINARY_THREE_H
#define STRUCTURES_BINARY_THREE_H
#include "array_list.h"

namespace structures {

template<typename T>
class BinaryTree {
public:
    BinaryTree() = default;

    ~BinaryTree() {
        delete root;
        size_ = 0;
    }

    void insert(const T& data) {
        if (empty()) {
            root = new Node(data);
        } else {
            root->insert(data);
        }
        size_++;
    }

    void remove(const T& data) {
        if (!empty()) {
            size_--;
            root->remove(data);
        }
    }

    //  Nao entendi essa parte
    bool contains(const T& data) const {
        bool temp = false;
        if (!empty())
            temp = root->contains(data);
        return temp;
    }

    bool empty() const {
        return (size_ == 0);
    }

    std::size_t size() const {
        return(size_);
    }

    // Jogando pra uma lista pra q?
    ArrayList<T> pre_order() const {
        ArrayList<T> v{size_};
        if (!empty()) {
            root->pre_order(v);
        }
        return v;
    }

    ArrayList<T> in_order() const {
        ArrayList<T> v{size_};
        if (!empty()) {
            root->in_order(v);
        }
        return v;
    }

    ArrayList<T> post_order() const {
        ArrayList<T> v{size_};
        if (!empty()) {
            root->post_order(v);
        }
        return v;
    }

private:
    struct Node {
        explicit Node(const T& data) : data{data}, left{nullptr}, right{nullptr}
        {}

        T data;
        Node* left;
        Node* right;

        void insert(const T& data_) {
            Node* new_node;
            if (data_ < this->data) {
                if (this->left == nullptr) {
                    new_node = new Node(data_);
                    new_node->left = nullptr;
                    new_node->right = nullptr;
                    this->left = new_node;
                } else {
                    left->insert(data_);
                }
            } else {
                if (this->right == nullptr) {
                    new_node = new Node(data_);
                    new_node->left = nullptr;
                    new_node->right = nullptr;
                    this->right = new_node;
                } else {
                    right->insert(data_);
                }
            }
        }
        
        // metodo remover errado arrumar
        bool remove(const T& data_) {
            if (data_ == this->data) {
                if ((this->left != nullptr) && (this->right != nullptr)) {
                    Node *temp = this->right;
                    while (temp->left != nullptr) {
                        temp = temp->left;
                    }
                    this->data = temp->data;
                    return right->remove(this->data);
                } else {
                    if (this->right != nullptr) {
                        this->data = left->data;
                        return left->remove(this->data);
                    } else {
                        delete this;
                        return true;
                    }
                }
            } else {
                if (this->right != nullptr && this->data < data_) {
                    return right->remove(data_);
                } else if (this->left != nullptr && this->data > data_) {
                    return left->remove(data_);
                }
            }
            return false;
        }

        bool contains(const T& data_) const {
            if (data_ == this->data) {
                return true;
            } else {
                if ((this->left != nullptr) && (data_ < this->data)) {
                    return left->contains(data_);
                } else if ((this->right != nullptr) && (data_ > this->data)) {
                    return right->contains(data_);
                }
            }
            return false;
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(this->data);
            if (this->left != nullptr)
                left->pre_order(v);
            if (this->right != nullptr)
                right->pre_order(v);
        }

        void in_order(ArrayList<T>& v) const {
            if (this->left != nullptr)
                left->in_order(v);
            v.push_back(this->data);
            if (this->right != nullptr)
                right->in_order(v);
        }

        void post_order(ArrayList<T>& v) const {
            if (this->left != nullptr)
                left->post_order(v);
            if (this->right != nullptr)
                right->post_order(v);
            v.push_back(this->data);
        }
    };

    Node* root{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif
