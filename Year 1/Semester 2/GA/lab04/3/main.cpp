//
// Created by Diana-Elena Stancu on 20/05/2022.
//

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

#define pr std::pair<unsigned int, char>
#define fr first
#define chr second

class Node {
private:
    Node* left;
    Node* right;
    pr info;

    const char minChar(Node* node) const {
        if (node == NULL) {
            return 127;
        }

        char minLeft = minChar(node->left);
        char minRight = minChar(node->right);

        return std::min(node->info.chr, std::min(minLeft, minRight));
    }

public:
    Node(pr info) : left{ NULL }, right{ NULL }, info{ info } {};
    Node(Node* left, Node* right, pr info) : left{ left }, right{ right }, info{ info }{};

    bool operator<(const Node& ot) {
        if (this->info.fr != ot.info.fr) {
            return this->info.fr < ot.info.fr;
        }

        return this->minimChar() < ot.minimChar();
    }


    const char minimChar() const {
        return std::min(this->info.chr, std::min(minChar(this->left), minChar(this->right)));
    }
    
    friend class Huffman;
};

class Huffman {
private:
    string inf;
    string outf;
    string message;
    map<char, int> diagram;
    multiset<Node *, bool(*)(Node*, Node*)> huff;
    map<char, string> encoding;

    void read() {
        ifstream in(inf);

        if (in.fail()) {
            return;
        }

        std::getline(in, message);
        //cout << message;

        for (const auto& c : message) {
            if (diagram.count(c)) {
                diagram[c]++;
            }
            else {
                diagram[c] = 1;
            }
        }

        for (const auto& c : diagram) {
            huff.insert(new Node(std::make_pair(c.second, c.first)));
        }

        in.close();
    }

    Node* createTree() {
        Node* node;
        int n = diagram.size();

        for (int i = 1; i <= n - 1; ++i) {
            Node* left = *huff.begin();
            huff.erase(huff.begin());
            Node* right = *huff.begin();
            huff.erase(huff.begin());

            node = new Node(left, right, std::make_pair(left->info.fr + right->info.fr, 127));
            huff.insert(node);
        }

        return node;
    }

    void createEncoding(Node* node, string encode) {
        if (node == NULL) {
            return;
        }
        if (node->left == NULL && node->right == NULL) {
            encoding[node->info.chr] = encode;
            return;
        }
        createEncoding(node->left, encode + "0");
        createEncoding(node->right, encode + "1");
    }

    void solve() {
        read();
        Node* root = createTree();
        createEncoding(root, "");
    }

public:
    Huffman(const string& inf, const string& outf) : inf{ inf }, outf{ outf }, huff([](Node* node1, Node* node2) {
        return *node1 < *node2;
    }){};

    void print() {
        solve();

        ofstream out(outf);

        if (out.fail()) {
            return;
        }

        out << diagram.size() << '\n';
        for (const auto& c : diagram) {
            out << c.fr << " " << c.chr << '\n';
        }

        for (const auto& c : message) {
            out << encoding[c];
        }

        out.close();
    }
};

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Argumente insuficiente\n";
        return 0;
    }

    Huffman huff{ argv[1], argv[2] };
    huff.print();

    return 0;
}