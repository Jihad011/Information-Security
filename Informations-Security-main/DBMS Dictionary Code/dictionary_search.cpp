#include<bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace chrono;
#define endl       '\n'

/*****Properties of B+ Tree*****/
// 1. All leaves are at the same level.
// 2. Each node except root can have a maximum of m children and at least m/2 children.
// 3. Each node can contain a maximum of m - 1 keys and a minimum of ⌈m/2⌉ - 1 keys.
// 4. Follows Binary Search Tree 
// 5. All data will be stored in leaf nodes


/*****Helper Functions*****/
// order of B+ Tree
int M = 3;       

struct node {
    int size;
    bool leaf;
    node **pointer;
    node *parent, *next;
    string *word, *meaning;

    node(int M) {
        size = 0;
        leaf = true;
        parent = next = NULL;
        word = new string[M];
        meaning = new string[M];
        pointer = new node*[M+1];
        for(int i = 0; i <= M; i++)
            pointer[i] = NULL;
    }
} *root;

// insert key and internal node to parent
void insert_to_parent(node *parent, string word, node *right) {
    int i = parent->size - 1;
    while(i >= 0) {
        if(parent->word[i] <= word)
            break;
        else {
            parent->word[i+1] = parent->word[i];
            parent->pointer[i+2] = parent->pointer[i+1];
        }
        i -= 1;
    }
    parent->word[i+1] = word;
    parent->pointer[i+2] = right;
    parent->size += 1;
}

// find leaf node that stores the key "word"
node *find_leaf_node(string word) {
    node *tmp_root = root;
    while(!tmp_root->leaf) {
        int i = 0;
        for(; i < tmp_root->size; i++) {
            if(word < tmp_root->word[i]) 
                break;
        }
        tmp_root = tmp_root->pointer[i];
    }
    return tmp_root;
}

// update internal node after inserting leaf node, if needed
void insert_internal_node(node *parent, string word, node *left, node *right) {
    // new root should create
    if(parent == NULL) {
        parent = new node(M);
        parent->word[0] = word;
        parent->pointer[0] = left;
        parent->pointer[1] = right;
        parent->size = 1;
        parent->leaf = false;
        root = parent;
        left->parent = parent;
        right->parent = parent;
        return;
    }

    right->parent = parent;
    insert_to_parent(parent, word, right);
    if(parent->size == M) {
        node *new_node = new node(M);
        new_node->leaf = false;

        int i, j = 0;
        for(i = parent->size-(M-1)/2; i < M; i++, j++) {
            new_node->word[j] = parent->word[i];
            if(j == 0) {
                new_node->pointer[0] = parent->pointer[i];
                new_node->pointer[0]->parent = new_node;
            }
            new_node->pointer[j+1] = parent->pointer[i+1];
            new_node->pointer[j+1]->parent = new_node;
        }
        
        parent->size -= ((M-1)/2 + 1);
        new_node->size = (M-1)/2;
        // not new_leaf->word[0]
        insert_internal_node(parent->parent, parent->word[parent->size], parent, new_node);
    }
}

// insert data at leaf node
void insert_leaf_node(string word, string meaning) {
    node *leaf = find_leaf_node(word);

    int i = leaf->size - 1;
    while(i >= 0) {
        if(leaf->word[i] <= word)
            break;
        else {
            leaf->word[i+1] = leaf->word[i];
            leaf->meaning[i+1] = leaf->meaning[i]; 
        }
        i -= 1;
    }

    leaf->word[i+1] = word;
    leaf->meaning[i+1] = meaning;
    leaf->size += 1;

    if(leaf->size == M) {
        node *new_leaf = new node(M);

        int i, j = 0;
        for(i = leaf->size - M/2; i < M; i++, j++) {
            new_leaf->word[j] = leaf->word[i];
            new_leaf->meaning[j] = leaf->meaning[i];
        }

        leaf->size -= M/2;
        new_leaf->size = M/2;
        new_leaf->next = leaf->next;
        leaf->next = new_leaf;
        insert_internal_node(leaf->parent, new_leaf->word[0], leaf, new_leaf);
    }
}

void insert(string word, string meaning) {
    insert_leaf_node(word, meaning);
}

string search(string word) {
    node *leaf = find_leaf_node(word);
    for(int i = 0; i < leaf->size; i++) {
        if(word == leaf->word[i])
            return leaf->meaning[i];
    }
    return "not found!";
}

void assert0(int &M) {
    if(M <= 2)
        M++;
}

/*****main Function*****/
int main() {
    cout << "Order of B+ Tree: ";
    cin >> M;

    assert0(M);
    assert(M >= 3);

    // create root of b+ tree
    root = new node(M);

    // open input file
    ifstream input_file;
    input_file.open("dictionary.txt");

    if(!input_file) {
        cout << "File Not Found!" << endl;
        exit(1);
    }
    
    // build b+ tree
    string word, meaning;
    auto start = high_resolution_clock::now();
    while(input_file >> word) {
        getline(input_file, meaning);
        insert(word, meaning);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Build successful in: " << duration.count() << " micro sec" << endl;

    // close input file
    input_file.close();

    cout << "Enter words: " << endl;
    // freopen("output.txt", "w", stdout);

    while(cin >> word) {
        start = high_resolution_clock::now();
        meaning = search(word);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        cout << word << " -> " << meaning << endl;
        cout << "Search Time: " << duration.count() << " micro sec" << endl;
    }

    return 0;
} 