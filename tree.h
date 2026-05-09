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
   - Store every dynamically allocated node pointer in a vector (allNodes).
   - Destructor deletes each node exactly once.
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

    // Find a node by ID (returns nullptr if not found)
    Node<T>* findNode(const string& id) {
        for (int i = 0; i < static_cast<int>(allNodes.size()); i++) {
            if (allNodes[i]->id == id) {
                return allNodes[i];
            }
        }
        return nullptr;
    }

    // Create the node if missing, if it exists but has empty data, update it
    Node<T>* getOrCreateNode(const string& nodeID, const T& value) {
        if (nodeID.empty()) {
            return nullptr;
        }

        Node<T>* existing = findNode(nodeID);
        if (existing != nullptr) {
            // Update data only if it was empty before and we now have real data
            if (existing->data == T() && value != T()) {
                existing->data = value;
            }
            return existing;
        }

        Node<T>* created = new Node<T>(nodeID, value);
        allNodes.push_back(created);
        return created;
    }

    void linkParentChild(Node<T>* parent, Node<T>* child) {
        if (parent == nullptr || child == nullptr) {
            return;
        }

        // Avoid duplicate child links
        for (int i = 0; i < static_cast<int>(parent->children.size()); i++) {
            if (parent->children[i]->id == child->id) {
                return; // already linked
            }
        }

        parent->children.push_back(child);
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

    // Public helper: make sure a node exists (not using linking)
    void ensureNodeExists(const string& id, const T& value) {
        getOrCreateNode(id, value);
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
        linkParentChild(parent, child);
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

    void playGame() {
        if (root == nullptr) {
            cout << "Tree is empty. Nothing to play." << endl;
            return;
        }

        Node<T>* current = root;

        cout << "\n===== Begin Adventure =====\n" << endl;

        while (true) {
            cout << current->data << endl;

            if (current->children.empty()) {
                cout << "\nThere are no further paths." << endl;
                cout << "Your journey ends here.\n" << endl;
                break;
            }

            cout << "\nChoose your next action:" << endl;
            for (int i = 0; i < static_cast<int>(current->children.size()); i++) {
                Node<T>* child = current->children[i];

                if (child->data == T()) {
                    cout << (i + 1) << ". Go to node " << child->id << endl;
                } else {
                    cout << (i + 1) << ". " << child->data << endl;
                }
            }

            cout << "Selection: ";
            int choice;
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Please enter a number.\n" << endl;
                continue;
            }

            if (choice < 1 || choice > static_cast<int>(current->children.size())) {
                cout << "Invalid choice. Try again.\n" << endl;
                continue;
            }

            current = current->children[choice - 1];
            cout << endl;
        }

        cout << "===== Adventure Complete =====" << endl;
    }

    ~Tree() {
        for (int i = 0; i < static_cast<int>(allNodes.size()); i++) {
            delete allNodes[i];
            allNodes[i] = nullptr;
        }

        allNodes.clear();
        root = nullptr;
    }
};

#endif //FA25EC3_TREE_H