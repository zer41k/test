#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include <stack>
#include <queue>

class BSTree
{
    struct Node
    {
        int data_;
        Node* left_;
        Node* right_;
    };

public:
    BSTree();
    BSTree(std::initializer_list<int> list);
    BSTree(const BSTree& other);
    BSTree& operator=(BSTree other) noexcept;
    ~BSTree();

    void AddLeaf(int data);
    void RemoveNode(int data);

    int Height() const;

    void PrintInOrderRecursive() const;
    void PrintPreOrderRecursive() const;
    void PrintPostOrderRecursive() const;
    void PrintLevelOrderRecursive() const;

    void PrintInOrderIterative() const;
    void PrintPreOrderIterative() const;
    void PrintPostOrderIterative() const;
    void PrintLevelOrderIterative() const;

    void Swap(BSTree& other) noexcept;

private:
    Node* NewNode(int data) const;
    void AddLeafPrivate(int data, Node* root);
    Node* RemoveNodePrivate(int data, Node* root);
    int HeightPrivate(Node* root) const;
    Node* CopySubtree(const Node* other) const;
    void DeleteSubtree(Node* root);

    void PrintInOrderRecursivePrivate(Node* root) const;
    void PrintPreOrderRecursivePrivate(Node* root) const;
    void PrintPostOrderRecursivePrivate(Node* root) const;
    void PrintLevelOrderRecursivePrivate(Node* root, int level) const;

private:
    Node* root_;
};


void swap(BSTree& lhs, BSTree& rhs) noexcept
{
    lhs.Swap(rhs);
}



BSTree::BSTree() :
    root_(nullptr)
{
}



BSTree::BSTree(std::initializer_list<int> list)
    : root_(nullptr)
{
    std::initializer_list<int>::iterator it;
    for (it = list.begin(); it != list.end(); it++)
        AddLeaf(*it);
}



BSTree::BSTree(const BSTree& other) :
    root_(nullptr)
{
    root_ = CopySubtree(other.root_);
}



BSTree& BSTree::operator=(BSTree other) noexcept
{
    other.Swap(*this);
    return *this;
}



BSTree::~BSTree()
{
    DeleteSubtree(root_);
}



void BSTree::AddLeaf(int data)
{
    AddLeafPrivate(data, root_);
}



void BSTree::RemoveNode(int data)
{
    RemoveNodePrivate(data, root_);
}



int BSTree::Height() const
{
    if (root_ == nullptr)
        return 0;

    return HeightPrivate(root_);
}



void BSTree::PrintInOrderRecursive() const
{
    PrintInOrderRecursivePrivate(root_);
}



void BSTree::PrintPreOrderRecursive() const
{
    PrintPreOrderRecursivePrivate(root_);
}



void BSTree::PrintPostOrderRecursive() const
{
    PrintPostOrderRecursivePrivate(root_);
}



void BSTree::PrintLevelOrderRecursive() const
{
    if (root_ == nullptr)
    {
        std::cout << "Tree is empty.\n";
        return;
    }

    int height = Height();

    for (int i = 1; i <= height; i++)
    {
        PrintLevelOrderRecursivePrivate(root_, i);
    }
}



void BSTree::PrintInOrderIterative() const
{
    if (root_ == nullptr)
    {
        std::cout << "Tree is empty.\n";
        return;
    }

    std::stack<Node*> nodes_stack;
    Node* curr_node = root_;
    while (nodes_stack.empty() == false || curr_node != nullptr)
    {
        while (curr_node != nullptr)
        {
            nodes_stack.push(curr_node);
            curr_node = curr_node->left_;
        }

        curr_node = nodes_stack.top();
        nodes_stack.pop();
        std::cout << curr_node->data_ << " ";

        curr_node = curr_node->right_;
    }
}



void BSTree::PrintPreOrderIterative() const
{
    if (root_ == nullptr)
    {
        std::cout << "Tree is empty.\n";
        return;
    }

    std::stack<Node*> nodes_stack;
    nodes_stack.push(root_);

    while (nodes_stack.empty() == false)
    {
        Node* curr_node = nodes_stack.top();
        nodes_stack.pop();
        std::cout << curr_node->data_ << " ";

        if (curr_node->right_ != nullptr)
            nodes_stack.push(curr_node->right_);

        if (curr_node->left_ != nullptr)
            nodes_stack.push(curr_node->left_);
    }
}



void BSTree::PrintPostOrderIterative() const
{
    if (root_ == nullptr)
    {
        std::cout << "Tree is empty.\n";
        return;
    }

    std::stack<Node*> result_stack;
    std::stack<Node*> nodes_stack;
    nodes_stack.push(root_);

    while (nodes_stack.empty() == false)
    {
        Node* curr_node = nodes_stack.top();
        nodes_stack.pop();

        result_stack.push(curr_node);

        if (curr_node->left_ != nullptr)
            nodes_stack.push(curr_node->left_);

        if (curr_node->right_ != nullptr)
            nodes_stack.push(curr_node->right_);
    }

    while (result_stack.empty() == false)
    {
        std::cout << result_stack.top()->data_ << " ";
        result_stack.pop();
    }
}



void BSTree::PrintLevelOrderIterative() const
{
    if (root_ == nullptr)
    {
        std::cout << "Tree is empty.\n";
        return;
    }

    std::queue<Node*> nodes_queue;
    nodes_queue.push(root_);

    while (nodes_queue.empty() == false)
    {
        Node* curr_node = nodes_queue.front();
        nodes_queue.pop();
        std::cout << curr_node->data_ << " ";

        if (curr_node->left_ != nullptr)
            nodes_queue.push(curr_node->left_);

        if (curr_node->right_ != nullptr)
            nodes_queue.push(curr_node->right_);
    }
}



void BSTree::Swap(BSTree& other) noexcept
{
    using std::swap;
    swap(root_, other.root_);
}



BSTree::Node* BSTree::NewNode(int data_) const
{
    Node* node = new Node;
    node->data_ = data_;
    node->left_ = nullptr;
    node->right_ = nullptr;
    return node;
}



void BSTree::AddLeafPrivate(int data, Node* root)
{
    if (root == nullptr)
    {
        root_ = NewNode(data);
    }
    else if (data < root->data_)
    {
        if (root->left_ != nullptr)
            AddLeafPrivate(data, root->left_);
        else
            root->left_ = NewNode(data);
    }
    else if (data > root->data_)
    {
        if (root->right_ != nullptr)
            AddLeafPrivate(data, root->right_);
        else
            root->right_ = NewNode(data);
    }
    else {
        std::cout << "The data_" << data << "has been already added to the tree\n";
    }
}



BSTree::Node* BSTree::RemoveNodePrivate(int data, Node* root)
{
    if (root == nullptr)
    {
        return root;
    }
    else if (root->data_ < data)
    {
        root->right_ = RemoveNodePrivate(data, root->right_);
    }
    else if (root->data_ > data)
    {
        root->left_ = RemoveNodePrivate(data, root->left_);
    }
    else
    {
        if (root->left_ == nullptr && root->right_ == nullptr)
        {
            if (root == root_)
                root_ = nullptr;
            delete root;
            return nullptr;
        }
        else if (root->left_ != nullptr && root->right_ == nullptr)
        {
            Node* child = root->left_;
            delete root;
            if (root == root_)
                root_ = child;
            return child;
        }
        else if (root->left_ == nullptr && root->right_ != nullptr)
        {
            Node* child = root->right_;
            delete root;
            if (root == root_)
                root_ = child;
            return child;
        }
        else
        {
            // inorder successor
            Node* successor = root->right_;
            Node* parent_successor = successor;

            while (successor->left_ != nullptr)
            {
                parent_successor = successor;
                successor = successor->left_;
            }

            if (parent_successor != successor)
            {
                root->data_ = successor->data_;
                parent_successor->left_ = successor->right_;
                delete successor;
                return root;
            }
            else
            {
                root->data_ = successor->data_;
                root->right_ = successor->right_;
                delete successor;
                return root;
            }
        }
    }
    return root;
}



int BSTree::HeightPrivate(Node* root) const
{
    if (root == nullptr)
        return 0;

    int left_height = HeightPrivate(root->left_);
    int right_height = HeightPrivate(root->right_);
    return std::max(left_height, right_height) + 1;
}



BSTree::Node* BSTree::CopySubtree(const Node* other) const
{
    Node* new_node = nullptr;
    if (other != nullptr)
    {
        new_node = NewNode(other->data_);
        new_node->left_ = CopySubtree(other->left_);
        new_node->right_ = CopySubtree(other->right_);
    }
    return new_node;
}



void BSTree::DeleteSubtree(Node* root)
{
    if (root != nullptr)
    {
        DeleteSubtree(root->left_);
        DeleteSubtree(root->right_);
        delete root;
    }
}



void BSTree::PrintInOrderRecursivePrivate(Node* root) const
{
    if (root == nullptr)
        return;

    PrintInOrderRecursivePrivate(root->left_);
    std::cout << root->data_ << " ";
    PrintInOrderRecursivePrivate(root->right_);
}



void BSTree::PrintPreOrderRecursivePrivate(Node* root) const
{
    if (root == nullptr)
        return;

    std::cout << root->data_ << " ";
    PrintPreOrderRecursivePrivate(root->left_);
    PrintPreOrderRecursivePrivate(root->right_);
}



void BSTree::PrintPostOrderRecursivePrivate(Node* root) const
{
    if (root == nullptr)
        return;

    PrintPostOrderRecursivePrivate(root->left_);
    PrintPostOrderRecursivePrivate(root->right_);
    std::cout << root->data_ << " ";
}



void BSTree::PrintLevelOrderRecursivePrivate(Node* root, int level) const
{
    if (root == nullptr)
        return;

    if (level == 1)
    {
        std::cout << root->data_ << " ";
    }
    else
    {
        PrintLevelOrderRecursivePrivate(root->left_, level - 1);
        PrintLevelOrderRecursivePrivate(root->right_, level - 1);
    }
}









void TestBSTree()
{
    using std::cout;
    BSTree tree = {8, 5, 2, 1, 0, 6, 4, 7, 9, 3};
    cout << "Binary search tree:\n";

    cout << "   InOrder (iterative): ";
    tree.PrintInOrderIterative();
    cout << "\n   InOrder (recursive): ";
    tree.PrintInOrderRecursive();
    cout << "\n  PreOrder (iterative): ";
    tree.PrintPreOrderIterative();
    cout << "\n  PreOrder (recursive): ";
    tree.PrintPreOrderRecursive();
    cout << "\n PostOrder (iterative): ";
    tree.PrintPostOrderIterative();
    cout << "\n PostOrder (recursive): ";
    tree.PrintPostOrderRecursive();
    cout << "\nLevelOrder (iterative): ";
    tree.PrintLevelOrderIterative();
    cout << "\nLevelOrder (recursive): ";
    tree.PrintLevelOrderRecursive();

    cout << "\n\nHeaight = " << tree.Height();

    cout << "\n\nRemove {0} (leaf):\n";
    tree.RemoveNode(0);

    cout << "   InOrder: ";
    tree.PrintInOrderIterative();
    cout << "\n  PreOrder: ";
    tree.PrintPreOrderIterative();
    cout << "\n PostOrder: ";
    tree.PrintPostOrderIterative();
    cout << "\nLevelOrder: ";
    tree.PrintLevelOrderIterative();

    cout << "\n\nHeaight = " << tree.Height();

    cout << "\n\nRemove {6} (one child):\n";
    tree.RemoveNode(6);

    cout << "   InOrder: ";
    tree.PrintInOrderIterative();
    cout << "\n  PreOrder: ";
    tree.PrintPreOrderIterative();
    cout << "\n PostOrder: ";
    tree.PrintPostOrderIterative();
    cout << "\nLevelOrder: ";
    tree.PrintLevelOrderIterative();

    cout << "\n\nHeaight = " << tree.Height();

    cout << "\n\nRemove {2} (two children):\n";
    tree.RemoveNode(2);

    cout << "   InOrder: ";
    tree.PrintInOrderIterative();
    cout << "\n  PreOrder: ";
    tree.PrintPreOrderIterative();
    cout << "\n PostOrder: ";
    tree.PrintPostOrderIterative();
    cout << "\nLevelOrder: ";
    tree.PrintLevelOrderIterative();

    cout << "\n\nHeaight = " << tree.Height();

    cout << "\n\nAdd {2}:\n";
    tree.AddLeaf(2);

    cout << "   InOrder: ";
    tree.PrintInOrderIterative();
    cout << "\n  PreOrder: ";
    tree.PrintPreOrderIterative();
    cout << "\n PostOrder: ";
    tree.PrintPostOrderIterative();
    cout << "\nLevelOrder: ";
    tree.PrintLevelOrderIterative();

    cout << "\n\nHeaight = " << tree.Height();
}
#endif // BSTREE_H
