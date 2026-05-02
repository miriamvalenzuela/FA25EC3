//
// Created by Manju Muralidharan on 11/22/25.
//

#ifndef FA25EC3_TREE_H
#define FA25EC3_TREE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
   TEMPLATE TREE CLASS
   Multiple parents may point to the same child.

   Design note (simple + safe approach):
   - Will store every dynamically allocated node pointer in a vector (allNodes).
   - That way, the destructor can delete each node exactly once.
   - Parents store child pointers, so children can appear under multiple parents.
*/

template <typename U>
class Node {
public:
    string id;
    U data;
    vector<Node<U>*> children;

    Node(const string& nodeID, const U& value) {
        id = nodeID;
        data = value;
    }
};

template <typename T>
class Tree {
private:
    Node<T>* root;
    vector<Node<T>*> allNodes;

public:
    Tree() {
        root = nullptr;
    }

    // Create the root node (called once at the start)
    void createRoot(const string& id, const T& value) {
        if (root != nullptr) {
            cout << "Root already exists. createRoot ignored." << endl;
            return;
        }

        root = new Node<T>(id, value);
        allNodes.push_back(root);
    }

    void addNode(const string& parentID, const string& childID, const T& value);

    // Find a node by ID (returns nullptr if not found)
    Node<T>* findNode(const string& id) {
        for (int i = 0; i < static_cast<int>(allNodes.size()); i++) {
            if (allNodes[i]->id == id) {
                return allNodes[i];
            }
        }
        return nullptr;
    }

    void printAll();

    ~Tree() {
        // Placeholder so the project links successfully.
        // Will implement real cleanup later once nodes are allocated.
    }
};

#endif //FA25EC3_TREE_H