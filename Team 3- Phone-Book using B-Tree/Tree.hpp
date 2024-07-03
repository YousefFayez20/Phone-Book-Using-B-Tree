#pragma once
#ifndef  Tree.hpp
#define Tree
#include <iostream>
#include <array>
#include <vector>
using namespace std;
vector< string > arr;

class BTreeNode {
    string* phone_numbers; // An array of phone numbers
    string* names; // An array of names
    int t; // Minimum degree (defines the range for number of keys)
    BTreeNode** C; // An array of child pointers
    int n; // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false


public:
    BTreeNode(int _t, bool _leaf);
    void traverse();
    string search2(string phone_number);
    //string search3(string name);
    int findKey(string phone_number);
    void insertNonFull(string phone_number, string name);
    void splitChild(int i, BTreeNode* y);
    void deletion(string phone_number);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    string getPredecessor(int idx);
    string getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
    string getNodeName(string phone_num);
    //string getNodePhone(string name1);
    friend class BTree;
};

class BTree {
    BTreeNode* root;
    int t;// min degree

public:
    BTree(int _t) {
        root = NULL;
        t = _t;
    }

    void traverse() {
        if (root != NULL)
            root->traverse();
    }
    void insertion(string phone_number, string name);
    string search(string phone_number) {
        return (root == NULL) ? "" : root->search2(phone_number);
    }
    //string search4(string name) {
    //    return (root == NULL) ? "" : root->search3(name);
    //}
    void deletion(string phone_number);
};
string BTreeNode::getNodeName(string phone_num) {
    for (int i = 0; i < n; i++) {
        if (phone_numbers[i] == phone_num) {
            return names[i];
        }
    }
    return ""; // return an empty string if the phone number is not found
}
/*string BTreeNode::getNodePhone(string name1) {
    for (int i = 0; i < n; i++) {
        if (names[i] == name1) {
            return phone_numbers[i];
        }
    }
    return ""; // return an empty string if the phone number is not found
}*/
BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;

    C = new BTreeNode * [2 * t]; // Allocate memory for child pointers
    phone_numbers = new string[2 * t - 1];
    names = new string[2 * t - 1];
    n = 0;
}
int BTreeNode::findKey(string phone_number) {
    int idx = 0;
    while (idx < n && phone_numbers[idx] < phone_number)
        ++idx;
    return idx;
}
string BTreeNode::search2(string phone_number) {
    int i = 0;
    while (i < n && atoi(phone_number.c_str()) > atoi(phone_numbers[i].c_str()))
        i++;

    if (phone_numbers[i] == phone_number)
        return this->getNodeName(phone_number);

    if (leaf == true)
        return "";

    return C[i]->search2(phone_number);
}
/*string BTreeNode::search3(string name) {
    int i;
    int x;
    for (i = 0; i < n; i++) {
        if (leaf == false)
            C[i]->search3(name);
        if (names[i] == name) {
            x = atoi(this->phone_numbers[i].c_str());
            i = n;
            leaf = true;
            return this->phone_numbers[i];
        }
    }
        if (leaf == false)
            C[i]->search3(name);
        if (x == NULL) {
            return "";
        }
}*/
void BTreeNode::deletion(string phone_number) {
    int idx = findKey(phone_number);
    if (idx < n && phone_numbers[idx] == phone_number) {
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else {
        if (leaf) {
            cout << "The phone number " << phone_number << " does not exist in the phone book\n";
            return;
        }
        bool flag = ((idx == n) ? true : false);

        if (C[idx]->n < t)
            fill(idx);

        if (flag && idx > n)
            C[idx - 1]->deletion(phone_number);
        else
            C[idx]->deletion(phone_number);
    }
    return;
}
void BTreeNode::removeFromLeaf(int idx) {
    // Move all the keys after the idx-th pos one place backward
    for (int i = idx + 1; i < n; ++i) {
        phone_numbers[i - 1] = phone_numbers[i];
        names[i - 1] = names[i];
    }

    n--;

    return;
}
// Delete from non leaf node
void BTreeNode::removeFromNonLeaf(int idx) {
    string k = phone_numbers[idx];
    if (C[idx]->n >= t) {
        string pred = getPredecessor(idx);
        phone_numbers[idx] = pred;
        names[idx] = getNodeName(pred);
        C[idx]->deletion(pred);
    }

    else if (C[idx + 1]->n >= t) {
        string succ = getSuccessor(idx);
        phone_numbers[idx] = succ;
        names[idx] = getNodeName(succ);
        C[idx + 1]->deletion(succ);
    }

    // If both C[idx] and C[idx+1] has less than t keys,
    // merge C[idx+1] with C[idx] and remove k from C[idx]
    else {
        merge(idx);
        C[idx]->deletion(k);
    }
    return;
    // If the child C[idx] has less that t keys, examine C[idx+1].
       // If C[idx+1] has atleast t keys, find the successor 'succ' of k in
       // the subtree rooted at C[idx+1]
       // Replace k by succ
       // Recursively delete succ in C[idx+1]

}
string BTreeNode::getPredecessor(int idx) {
    BTreeNode* cur = C[idx];
    while (!cur->leaf)  // Keep moving to the right most node until we reach a leaf
        cur = cur->C[cur->n];

    return cur->phone_numbers[cur->n - 1];
}
string BTreeNode::getSuccessor(int idx) {
    BTreeNode* cur = C[idx + 1];
    while (!cur->leaf)// Keep moving the left most node starting from C[idx+1] until we reach a leaf
        cur = cur->C[0];

    return cur->phone_numbers[0];
}
void BTreeNode::fill(int idx) {
    if (idx != 0 && C[idx - 1]->n >= t)
        borrowFromPrev(idx);// If the previous child(C[idx-1]) has more than t-1 keys, borrow a key from that child

    else if (idx != n && C[idx + 1]->n >= t)  // If the next child(C[idx+1]) has more than t-1 keys, borrow a key
      // from that child
        borrowFromNext(idx);

    else {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
    return;
}
void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx - 1];

    for (int i = child->n - 1; i >= 0; --i) {
        child->phone_numbers[i + 1] = child->phone_numbers[i];
        child->names[i + 1] = child->names[i];
    }

    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

    child->phone_numbers[0] = sibling->phone_numbers[sibling->n - 1];
    child->names[0] = sibling->names[sibling->n - 1];

    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    child->n += 1;
    sibling->n -= 1;

    return;
}
void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx + 1];

    child->phone_numbers[child->n] = phone_numbers[idx];
    child->names[child->n] = names[idx];

    if (!(child->leaf))
        child->C[(child->n) + 1] = sibling->C[0];

    phone_numbers[idx] = sibling->phone_numbers[0];
    names[idx] = sibling->names[0];

    for (int i = 1; i < sibling->n; ++i) {
        sibling->phone_numbers[i - 1] = sibling->phone_numbers[i];
        sibling->names[i - 1] = sibling->names[i];
    }

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }

    ++child->n;
    --sibling->n;

    return;
}
void BTreeNode::merge(int idx) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx + 1];

    child->phone_numbers[t - 1] = phone_numbers[idx];
    child->names[t - 1] = names[idx];

    for (int i = 0; i < sibling->n; ++i) {
        child->phone_numbers[i + t] = sibling->phone_numbers[i];
        child->names[i + t] = sibling->names[i];
    }

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + t] = sibling->C[i];
    }

    for (int i = idx + 1; i < n; ++i) {
        phone_numbers[i - 1] = phone_numbers[i];
        names[i - 1] = names[i];
    }

    for (int i = idx + 2; i <= n; ++i)
        C[i - 1] = C[i];

    child->n += sibling->n + 1;
    n--;

    delete (sibling);
    return;
}
void BTree::insertion(string phone_number, string name) {
    bool x;
    if (!name.empty()) {
        if (!phone_number.empty()) {
            if (root == NULL) {
                root = new BTreeNode(t, true);
                root->phone_numbers[0] = phone_number;
                root->names[0] = name;
                root->n = 1;
            }
            else {
                if (root->n == 2 * t - 1) {
                    BTreeNode* s = new BTreeNode(t, false);

                    s->C[0] = root;

                    s->splitChild(0, root);

                    int i = 0;
                    char x = toupper(name[0]);
                    name[0] = x;
                    if (atoi(s->phone_numbers[0].c_str()) < atoi(phone_number.c_str()))
                        i++;
                    s->C[i]->insertNonFull(phone_number, name);

                    root = s;
                }
                else
                    root->insertNonFull(phone_number, name);
            }
        }
    }
    else {}
}
void BTreeNode::insertNonFull(string phone_number, string name) {
    int i = n - 1;
    if (leaf == true) {
        char x = toupper(name[0]);
        name[0] = x;
        while (atoi(phone_numbers[i].c_str()) > atoi(phone_number.c_str())) {
            phone_numbers[i + 1] = phone_numbers[i];
            names[i + 1] = names[i];
            i--;
        }
        phone_numbers[i + 1] = phone_number;
        names[i + 1] = name;
        n++;
    }
    else {
        char x = toupper(name[0]);
        name[0] = x;
        while (i >= 0 && atoi(phone_numbers[i].c_str()) > atoi(phone_number.c_str()))
            i--;
        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);
            char x = toupper(name[0]);
            name[0] = x;
            if (atoi(phone_numbers[i + 1].c_str()) < atoi(phone_number.c_str()))
                i++;
        }
        C[i + 1]->insertNonFull(phone_number, name);
    }
}
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++) {
        z->phone_numbers[j] = y->phone_numbers[j + t];
        z->names[j] = y->names[j + t];
    }

    if (y->leaf == false) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--) {
        phone_numbers[j + 1] = phone_numbers[j];
        names[j + 1] = names[j];
    }

    phone_numbers[i] = y->phone_numbers[t - 1];
    names[i] = y->names[t - 1];

    n = n + 1;
}
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (leaf == false)
            C[i]->traverse();
        arr.push_back(names[i]); arr.push_back(phone_numbers[i]);
    }

    if (leaf == false)
        C[i]->traverse();
}
void BTree::deletion(string phone_number) {
    if (!root) {
        cout << "The tree is empty\n";
        return;
    }

    root->deletion(phone_number);

    if (root->n == 0) {
        BTreeNode* tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];

        delete tmp;
    }
    return;
}
#endif
