//
// Created by Diana-Elena Stancu on 20/05/2022.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>

using std::cout;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::map;
using std::multiset;

#define thing std::pair<unsigned int, char>
#define freq first
#define character second

class Node {
private:
    Node* left;
    Node* right;
    thing info;

    const char minChar(Node* node) const {
        if (node == NULL) {
            return 127;
        }

        char minLeft = minChar(node->left);
        char minRight = minChar(node->right);

        return std::min(node->info.character, std::min(minLeft, minRight));
    }

public:
    Node(thing info) : left{ NULL }, right{ NULL }, info{ info } {};
    Node(Node* left, Node* right, thing info) : left{ left }, right{ right }, info{ info }{};

    const char minimChar() const {
        return std::min(this->info.character, std::min(minChar(this->left), minChar(this->right)));
    }

    bool operator<(const Node& ot) {
        if (this->info.freq != ot.info.freq) {
            return this->info.freq < ot.info.freq;
        }

        return this->minimChar() < ot.minimChar();
    }

    friend class Huffman;
};

class Huffman {
private:
    string input_file;
    string output_file;
    string message;
    map<char, int> diagram;
    multiset<Node *, bool(*)(Node*, Node*)> huff;
    map<char, string> encoding;

    void read() {
        ifstream in(input_file);

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
            //cout << c.first << " " << c.second << '\n';
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

            cout << left->info.character << " " << left->info.freq << " " << left->minimChar() << " " << right->info.character << " " << right->info.freq << " "<< right->minimChar() << '\n';

            node = new Node(left, right, std::make_pair(left->info.freq + right->info.freq, 127));
            huff.insert(node);
        }

        return node;
    }

    void createEncoding(Node* node, string encode) {
        if (node == NULL) {
            return;
        }
        if (node->left == NULL && node->right == NULL) {
            encoding[node->info.character] = encode;
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
    Huffman(const string& input_file, const string& output_file) : input_file{ input_file }, output_file{ output_file }, huff([](Node* node1, Node* node2) {
        //if (node1->info.freq != node2->info.freq) {
        //	return node1->info.freq < node2->info.freq;
        //}

        //char min1 = node1->minimChar();
        //char min2 = node2->minimChar();

        //return min1 <= min2;
        return *node1 < *node2;
    }){};

    void print() {
        solve();

        ofstream out(output_file);

        if (out.fail()) {
            return;
        }

        out << diagram.size() << '\n';
        for (const auto& c : diagram) {
            out << c.freq << " " << c.character << '\n';
        }

        for (const auto& c : message) {
            out << encoding[c];
        }

        out.close();
    }

    ~Huffman() {

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