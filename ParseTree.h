/*
    Take input token and make parse tree
*/

#pragma once
#include <iostream>
#include <cstring>


using namespace std;

struct Token {
    const char* type;
    const char* value;
    Token* next;

    Token(const char* t, const char* v) : type(t), value(v), next(nullptr) {}
};

struct TreeNode {
    const char* symbol;
    TreeNode* firstChild;
    TreeNode* nextSibling;

    TreeNode(const char* sym) : symbol(sym), firstChild(nullptr), nextSibling(nullptr) {}
};

class ParseTree

{
private:
    TreeNode* root;

    void addNode(TreeNode*& parent, const char* symbol)
    {
        TreeNode* newNode = new TreeNode(symbol);

        if (parent == nullptr) {
            parent = newNode;

        }
        else {
            TreeNode* sibling = parent;
            while (sibling->nextSibling != nullptr)
            {
                sibling = sibling->nextSibling;
            }
            sibling->nextSibling = newNode;
        }
    }

    void printTree(TreeNode* node, int depth = 0)

    {
        if (node == nullptr) return;

        for (int i = 0; i < depth; ++i) cout << "  ";
        cout << node->symbol << endl;

        printTree(node->firstChild, depth + 1);
        printTree(node->nextSibling, depth);
    }

public:
    ParseTree() : root(nullptr)
    {
    }

    void buildTree(Token* tokenList)
    {
        TreeNode* currentNode = nullptr;
        TreeNode* lastNode = nullptr;

        Token* currentToken = tokenList;


        while (currentToken != nullptr)
        {
            TreeNode* newNode = new TreeNode(currentToken->value);

            if (root == nullptr)
            {
                root = newNode;

                currentNode = root;
            }
            else
            {
                if (lastNode != nullptr)
                {
                    lastNode->nextSibling = newNode;
                }
                else {
                    currentNode->firstChild = newNode;
                }
            }

            lastNode = newNode;
            currentToken = currentToken->next;
        }
    }

    void print()
    {

        printTree(root);
    }
};