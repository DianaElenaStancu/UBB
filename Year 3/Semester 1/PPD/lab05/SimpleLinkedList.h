//
// Created by Diana-Elena Stancu on 17.12.2023.
//

#ifndef LAB5_PPD_SIMPLELINKEDLIST_H
#define LAB5_PPD_SIMPLELINKEDLIST_H

#include <string>
#include <vector>
#include <iostream>
#include <mutex>
#include <fstream>
#include <thread>
#include <set>
#include <map>
using namespace std;

struct Node {
    int id, score;
    Node* prev;
    Node* next;
    mutex mtx;

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
    Node* tail = nullptr;
    mutex mx_map;
    mutex participants[101];
    int black_list[101];

    void unlock_node(Node* n) {
        if(n != nullptr) {
            n->mtx.unlock();
        }
    }

    Node* lock_node(Node* n) {
        if(n != nullptr) {
            n->mtx.lock();
        }
        return n;
    }
public:
    SimpleLinkedList(){
        root = new Node();
        tail = new Node();
        root->next = tail;
        root->score = 1000000;
        tail->prev = root;
        tail->score = -1;

        // we assume that all participants are not disqualified
        for (int i = 0; i < 101; i++) {
            black_list[i] = 0;
        }
    };

    void remove(const int id) {
        Node* node = lock_node(root);
        Node* next = lock_node(node->next);
        Node* next_next = lock_node(next->next);
        while(next_next != nullptr) {
            if (next->id == id) {
                // node->next->next_next => node->next_next
                node->next = next_next;
                next_next->prev = node;
                delete next;

                unlock_node(node);
                unlock_node(next_next);
                return;
            }
            unlock_node(node);
            node = next;
            next = next_next;
            next_next = lock_node(next->next);
        }
        unlock_node(node);
        unlock_node(next);
    }

    void update(const int id, int score = 0) {
        lock_guard<mutex> lock_id(participants[id]);

        if(score == 0) {
            return;
        }

        if(black_list[id] == 1) {
            return;
        }

        if (score == -1) {
            // remove from list and add to set
            // printf("removed %d\n", id);
            black_list[id] = 1;
            remove(id);
            return;
        }

        Node* node = lock_node(root);
        Node* next = lock_node(node->next);
        Node* next_next = lock_node(next->next);
        while(next_next != nullptr) {
            if (next->id == id) {
                // node->next->next_next, we need to update next
                next->score += score;

                unlock_node(node);
                unlock_node(next);
                unlock_node(next_next);
                return;
            }
            unlock_node(node);
            node = next;
            next = next_next;
            next_next = lock_node(next->next);
        }

        Node* new_node = new Node(id, score);
        new_node->prev = node;
        new_node->next = next;
        node->next = new_node;
        next->prev = new_node;

        unlock_node(next);
        unlock_node(node);
    }

    void sort() {
        merge_sort(&root);
    }

    void merge_sort(Node** head_ref) {
        Node* head = *head_ref;
        Node* a;
        Node* b;

        if (head == nullptr || head->next == nullptr) {
            return;
        }

        front_back_split(head, &a, &b);

        merge_sort(&a);
        merge_sort(&b);

        *head_ref = merge_sort_recursive(a, b);
    }

    Node* merge_sort_recursive(Node* a, Node* b) {
        Node* result = nullptr;

        if (a == nullptr) {
            return b;
        }
        if (b == nullptr) {
            return a;
        }

        if (a->score > b->score || (a->score == b->score && a->id > b->id)) {
            result = a;
            result->next = merge_sort_recursive(a->next, b);
        } else {
            result = b;
            result->next = merge_sort_recursive(a, b->next);
        }
        return result;
    }

    void front_back_split(Node* head, Node** first_list, Node** second_list) {
        Node* fast = head->next;
        Node* slow = head;
        while(fast != nullptr) {
            fast = fast->next;
            if (fast != nullptr) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        *first_list = head;
        *second_list = slow->next;

        slow->next = nullptr;
    }

    friend ostream &operator<<(ostream &os, const SimpleLinkedList &list) {
        Node* node = list.root->next;
        while(node != nullptr && node != list.tail) {
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
void up(SimpleLinkedList* sll) {
    sll->update(1, 100);
    sll->update(2, -1);

}

void test() {
    SimpleLinkedList* sll = new SimpleLinkedList();

    vector<thread> th;
    for (int i = 0; i < 10; i++) {
        th.emplace_back(up, sll);
    }
    for (int i = 0; i < 10; i++) {
        th[i].join();

    }

    cout << *sll;
}



#endif //LAB5_PPD_SIMPLELINKEDLIST_H
