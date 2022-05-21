//
// Created by Diana-Elena Stancu on 20/05/2022.
//

#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <map>
#include <sstream>

#define thing std::pair<int, char>
#define freq first
#define character second

using std::ifstream;
using std::ofstream;
using std::string;
using std::unordered_map;
using std::cout;
using std::unique_ptr;
using std::multiset;
using std::map;

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
    string result;
    map<char, int> diagram;
    multiset<Node*, bool(*)(Node*, Node*)> huff;
    map<char, string> encoding;
    int n;
    Node* root;

    friend class Node;

    void read() {
        ifstream in(input_file);

        if (in.fail()) {
            return;
        }

        in >> n;
        map<char, int> diagram;

        string line;
        getline(in, line);
        cout << line;

        char x;
        int y;
        for (int i = 1; i <= n; ++i) {
            getline(in, line);
            x = line[0];
            std::istringstream in1(line.substr(2));
            in1 >> y;
            diagram[x] = y;
        }

        getline(in, message);
        //cout << message;
        in.close();

        for (const auto& p : diagram) {
            //cout << p.second << " " << p.first << '\n';
            huff.insert(new Node(std::make_pair(p.second, p.first)));
        }
    }

    Node* createTree() {
        Node* node;

        for (int i = 1; i <= n - 1; ++i) {
            Node* left = *huff.begin();
            huff.erase(huff.begin());
            Node* right = *huff.begin();
            huff.erase(huff.begin());

            node = new Node(left, right, std::make_pair(left->info.freq + right->info.freq, 127));
            huff.insert(node);
        }

        return node;
    }

    void createMessage() {
        result = "";
        Node* node = this->root;

        for (int i = 0; i <= message.length(); ++i) {
            if (node->left == NULL && node->right == NULL) {
                result += (char)node->info.character;
                node = this->root;

                if (i == message.length()) {
                    break;
                }
            }
            if (message[i] == '0') {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
    }

    void solve() {
        read();
        this->root = createTree();
        createMessage();
    }

    void deleteRecurssion(const Node* node) {
        if (node == NULL) {
            return;
        }
        deleteRecurssion(node->left);
        deleteRecurssion(node->right);

        delete(node);
    }

public:
    Huffman() = delete;
    Huffman(const string& input_file, const string& output_file) : input_file{ input_file }, output_file{ output_file }, root{ NULL }, huff([](Node* node1, Node* node2) {
        //if (node1->info.freq != node2->info.freq) {
        //	return node1->info.freq < node2->info.freq;
        //}

        //char min1 = node1->minimChar();
        //char min2 = node2->minimChar();

        //return min1 <= min2;
        return *node1 < *node2;
    }){};

    ~Huffman() {
        deleteRecurssion(root);
    }

    void print() {
        solve();

        ofstream out(output_file);
        if (out.fail()) {
            return;
        }

        out << result;

        out.close();
    }
};

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Numar incorect de argumente!\n";
        return 0;
    }

    Huffman huf{ argv[1], argv[2] };
    huf.print();

    return 0;
}