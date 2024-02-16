//
// Created by Andrei Bejan on 12/19/2023.
//

#ifndef LAB5_SYNCEDLINKEDLIST_H
#define LAB5_SYNCEDLINKEDLIST_H

#include "FinalResult.h"
#include <mutex>
#include <iostream>
#include <vector>


class SyncedLinkedList {
private:
    struct Node {
        Node *next;
        FinalResult score;
        std::mutex nodeMutex;
    };
    Node *root, *tail;


    Node* find(int id) {
        Node* currentNode = root;
        currentNode->nodeMutex.lock();
        Node* nextNode = root->next;
        nextNode->nodeMutex.lock();

        while(nextNode->score.getId() != id && nextNode->score.getId() != -1) {
            nextNode->next->nodeMutex.lock();
            currentNode->nodeMutex.unlock();
            currentNode = nextNode;
            nextNode = nextNode->next;
        }
        return currentNode;
    }

    void insert(FinalResult score, Node* currentNode) {
        Node* newNode = new Node();
        newNode->score = score;

        newNode->next = currentNode->next;
        currentNode->next = newNode;
    }

public:
    SyncedLinkedList() {
        root = new Node();
        root->score = FinalResult(-1, -1, -1);
        tail = new Node();
        tail->score = FinalResult(-1, -1, -1);
        root->next = tail;
    }

    void update(FinalResult score) {
        Node* currentNode = find(score.getId());
        Node* nextNode = currentNode->next;
        if(nextNode->score.getId() != score.getId()) {
            insert(score, currentNode);
        }
        else {
            FinalResult newFinalResult(
                    score.getId(),
                    score.getScore() + nextNode->score.getScore(),
                    score.getCountryId()
                    );
            nextNode->score = newFinalResult;
        }
        currentNode->nodeMutex.unlock();
        nextNode->nodeMutex.unlock();
    }

    void remove(int id) {
        Node* currentNode = find(id);
        Node* nextNode = currentNode->next;

        if(nextNode->score.getId() == id) {
            currentNode->next = nextNode->next;
            nextNode->nodeMutex.unlock();
            delete nextNode;
            currentNode->nodeMutex.unlock();
        }
        else {
            currentNode->nodeMutex.unlock();
            nextNode->nodeMutex.unlock();
        }
    }

    void refresh() {
        root->next = tail;
    }

    std::vector<FinalResult> getAll() {
        std::vector<FinalResult> results;

        Node* currentNode = root;
        currentNode->nodeMutex.lock();
        
        Node* nextNode = root->next;
        nextNode->nodeMutex.lock();

        while(nextNode->score.getId() != -1) {
            results.push_back(nextNode->score);
            nextNode->next->nodeMutex.lock();
            currentNode->nodeMutex.unlock();
            currentNode = nextNode;
            nextNode = nextNode->next;
        }

        currentNode->nodeMutex.unlock();
        nextNode->nodeMutex.unlock(); 

        return results;
    }
};


#endif //LAB5_SYNCEDLINKEDLIST_H
