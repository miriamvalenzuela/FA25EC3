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

    Node<T>* getOrCreateNode(const string& nodeID, const T& value) {
        Node<T>* existing = findNode(nodeID);
        if (existing != nullptr) {
            // If this node was created earlier with empty data, update it
            if (existing->data == T()) {
                existing->data = value;
            }
            return existing;
        }

        Node<T>* created = new Node<T>(nodeID, value);
        allNodes.push_back(created);
        return created;
    }

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

    void addNode(const string& parentID, const string& childID, const T& value) {
        if (root == nullptr) {
            cout << "Tree has no root yet. addNode ignored." << endl;
            return;
        }

        if (childID.empty()) {
            cout << "Child ID is empty. addNode ignored." << endl;
            return;
        }

        Node<T>* parent = findNode(parentID);
        if (parent == nullptr) {
            cout << "Parent not found: " << parentID << endl;
            return;
        }

        Node<T>* child = getOrCreateNode(childID, value);

        // Avoid duplicate child links under the same parent
        for (int i = 0; i < static_cast<int>(parent->children.size()); i++) {
            if (parent->children[i]->id == childID) {
                return; // already linked
            }
        }

        parent->children.push_back(child);
    }

    // Find a node by ID (returns nullptr if not found)
    Node<T>* findNode(const string& id) {
        for (int i = 0; i < static_cast<int>(allNodes.size()); i++) {
            if (allNodes[i]->id == id) {
                return allNodes[i];
            }
        }
        return nullptr;
    }

    void printAll() {
        if (root == nullptr || allNodes.empty()) {
            cout << "Tree is empty." << endl;
            return;
        }

        cout << "\n===== Story Tree =====" << endl;

        for (int i = 0; i < static_cast<int>(allNodes.size()); i++) {
            Node<T>* current = allNodes[i];

            cout << "Node " << current->id << ": " << current->data << endl;

            if (current->children.empty()) {
                cout << "  Child -> (none)" << endl;
            } else {
                for (int j = 0; j < static_cast<int>(current->children.size()); j++) {
                    cout << "  Child -> " << current->children[j]->id << endl;
                }
            }

            cout << endl;
        }

        cout << "======================" << endl;
    }

    ~Tree() {
        // Delete every node exactly once
        for (int i = 0; i < static_cast<int>(allNodes.size()); i++) {
            delete allNodes[i];
            allNodes[i] = nullptr;
        }

        allNodes.clear();
        root = nullptr;
    }
};

#endif //FA25EC3_TREE_H