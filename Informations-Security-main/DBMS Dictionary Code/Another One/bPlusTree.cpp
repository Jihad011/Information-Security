#include<bits/stdc++.h>
using namespace std;

// Constants to define B+ tree parameters
const int n = 100;  // Number of children
const int mx = n;

// Structure to represent a node in the B+ tree
struct mystruct {
    int currentNode;       // Number of elements in the node
    mystruct* parent;      // Pointer to the parent node
    mystruct* next;        // Pointer to the next node (for leaf nodes)
    string* english;       // Array to store English words
    string* meaning;       // Array to store corresponding meaning
    bool lf;               // Flag to indicate whether it's a leaf node
    mystruct** point;      // Array of pointers to child nodes
};

// Global variables for the B+ tree
mystruct* root;
mystruct* firstLeaf;

// Function to create a new node in the B+ tree
mystruct* createNode() {
    mystruct* m = new mystruct();

    m->point = new mystruct * [n + 1];
    m->english = new string[n];
    m->meaning = new string[n];

    m->currentNode = 0;
    m->parent = nullptr;
    m->next = nullptr;
    m->lf = true;
    return m;
}

// Function to find the leaf node for a given English word
mystruct* findLeaf(mystruct* tempRt, string english) {
    while (tempRt->lf == false) {
        int i;
        for (i = 0; i < tempRt->currentNode; i++)
            if (english < tempRt->english[i]) break;
        tempRt = tempRt->point[i];
    }
    return tempRt;
}

// Function to insert a value and pointer into a node
void insertValueAndPoint(mystruct* parent, string value, mystruct* right) {
    int i = parent->currentNode - 1;
    for (; i >= 0; i--) {
        if (parent->english[i] <= value) break;
        else {
            parent->english[i + 1] = parent->english[i];
            parent->point[i + 2] = parent->point[i + 1];
        }
    }
    parent->english[i + 1] = value;
    parent->point[i + 2] = right;
    parent->currentNode++;
}

// Function to insert a value into the middle of a node
void insertMiddle(mystruct* parent, string value, mystruct* left, mystruct* right) {
    if (parent == nullptr) {
        parent = createNode();
        parent->english[0] = value;
        parent->point[0] = left;
        parent->point[1] = right;
        parent->currentNode++;
        parent->lf = false;
        root = parent;
        left->parent = parent;
        right->parent = parent;
        return;
    }
    right->parent = parent;
    insertValueAndPoint(parent, value, right);
    if (parent->currentNode == mx) {
        mystruct* splitNode = createNode();
        splitNode->lf = false;
        int j = 0;
        for (int i = parent->currentNode - (n - 1) / 2; i < mx; i++) {
            splitNode->english[j] = parent->english[i];
            if (j == 0) {
                splitNode->point[0] = parent->point[i];
                splitNode->point[0]->parent = splitNode;
            }
            splitNode->point[j + 1] = parent->point[i + 1];
            splitNode->point[j + 1]->parent = splitNode;
            j++;
        }
        parent->currentNode -= (n - 1) / 2 + 1;
        splitNode->currentNode = (n - 1) / 2;
        insertMiddle(parent->parent, parent->english[parent->currentNode], parent, splitNode);
    }
}

// Function to insert a leaf node with English with its meaning word pairs
void insertLeaf(string english, string meaning) {
    mystruct* leaf = findLeaf(root, english);
    int i = leaf->currentNode - 1;
    if (i > -1) {
        for (; i >= 0; i--) {
            if (english < leaf->english[i]) {
                leaf->english[i + 1] = leaf->english[i];
                leaf->meaning[i + 1] = leaf->meaning[i];
            }
            else break;
        }
    }
    leaf->english[i + 1] = english;
    leaf->meaning[i + 1] = meaning;
    leaf->currentNode++;

    if (leaf->currentNode == mx) {
        mystruct* splitNode = createNode();
        int j = 0;
        for (int i = leaf->currentNode - n / 2; i < mx; i++) {
            splitNode->english[j] = leaf->english[i];
            splitNode->meaning[j] = leaf->meaning[i];
            j++;
        }
        leaf->currentNode -= n / 2;
        splitNode->currentNode = n / 2;
        splitNode->next = leaf->next;
        leaf->next = splitNode;
        insertMiddle(leaf->parent, splitNode->english[0], leaf, splitNode);
    }
}

int main() {
    root = createNode();
    mystruct* leaf;
    int i = 0;
    string english, meaning, searchEnglish;
    ifstream ifile;
    ifile.open("words.txt");
    if (!ifile) cout << "file khuje pawa jayni";
    else {
        while (ifile >> english) {
            getline(ifile, meaning);
            insertLeaf(english, meaning);
        }
        cout << "Enter text to search (X to terminate): ";
        while (cin >> searchEnglish) {
            if (searchEnglish == "x" || searchEnglish == "X") {
                break;
            }
            leaf = findLeaf(root, searchEnglish);
            for (i = 0; i < leaf->currentNode; i++) if (searchEnglish == leaf->english[i]) break;
            if (i == leaf->currentNode) cout << "No word found\n";
            else cout << searchEnglish << ": " << leaf->meaning[i] << endl;
            cout << "Enter text to search: ";
        }
    }
    return 0;
}
