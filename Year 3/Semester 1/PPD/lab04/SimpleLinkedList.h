//
// Created by Diana-Elena Stancu on 05.12.2023.
//

#ifndef LAB4_PPD_SIMPLELINKEDLIST_H
#define LAB4_PPD_SIMPLELINKEDLIST_H
#include <string>
#include <vector>
using namespace std;

struct Node {
    int id, score;
    Node* prev;
    Node* next;

    Node(int _id, int _score) {
        id = _id;
        score = _score;
        next = nullptr;
        prev = nullptr;
    }

    Node() {
        id = score = 0;
        next = nullptr;
        prev = nullptr;
    }
};

class SimpleLinkedList {
private:
    Node* root = nullptr;
public:
    SimpleLinkedList()= default;

    Node* find(const int id) {
        Node* node = root;
        while(node != nullptr && node->id != id) {
            node = node->next;
        }
        return node;
    }

    Node* remove(const int id) {
        Node* node = find(id);
        if (node == root) {
            root = node->next;
            return root;
        }

        if (node != nullptr) {
            Node* prev = node->prev;
            Node* next = node->next;

            prev->next = next;
            if (next != nullptr) {
                next->prev = prev;
            }
        }
        return node;
    }

    Node* add(const int id, int score = 0) {
        if (find(id) != nullptr) {
            Node* node = find(id);
            remove(id);
            score = node->score + score;
        }

        Node* node = new Node(id, score);
        if (root == nullptr) {
            root = node;
        } else {
            // 100 30 si adaug 20
            if (root->score < score) {
                node->next = root;
                root->prev = node;
                root = node;
                return node;
            }
            Node* curr_node = root;
            while(curr_node->next != nullptr && curr_node->next->score > score) {
                curr_node = curr_node->next;
            }
            if (curr_node->next == nullptr) {
                curr_node->next = node;
                node->prev = curr_node;
            } else {
                //curr_node > y >= curr_node->next
                node->next = curr_node->next;
                node->prev = curr_node;
                curr_node->next->prev = node;
                curr_node->next = node;
            }
        }
        return node;
    }

    friend ostream &operator<<(ostream &os, const SimpleLinkedList &list) {
        Node* node = list.root;
        while(node != nullptr) {
            os <<  node->id << ' ' << node->score << endl;
            node = node->next;
        }
        os << endl;
        return os;
    }
};

vector<string> input_files(int t, int p) {
    vector<string> in_f;
    for (int ti = 1; ti <= 5; ti++) {
        for (int pi = 1; pi <= 10; pi++) {
            string fisier = "../data/RezultateC" + to_string(ti) + "_P" + to_string(pi) + ".txt";
            in_f.push_back(fisier);
        }
    }
    return in_f;
}

#endif //LAB4_PPD_SIMPLELINKEDLIST_H
