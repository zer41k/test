#ifndef STACKLIST_H
#define STACKLIST_H

#include <algorithm>
#include <iostream>

class StackList
{
    struct Node
    {
        Node(int in) : next_(nullptr), data_(in) { }
        Node* next_;
        int data_;
    };

public:
    StackList();
    StackList(std::initializer_list<int> list);
    StackList(const StackList& other);
    StackList& operator=(StackList other) noexcept;
    ~StackList();

    void Push(int data);
    void Pop();
    int Top() const;

    int Size() const;
    bool IsEmpty() const;

    void Swap(StackList& other) noexcept;
    friend std::ostream& operator<<(std::ostream& ostream, const StackList& rhs);

private:
    Node* head_;
};


void swap(StackList& lhs, StackList& rhs) noexcept
{
    lhs.Swap(rhs);
}


std::ostream& operator<<(std::ostream& ostream, const StackList& rhs)
{
    StackList::Node* curr_node = rhs.head_;
    while (curr_node != nullptr)
    {
        ostream << curr_node->data_ << " -> ";
        curr_node = curr_node->next_;
    }
    return ostream << "\n";
}



StackList::StackList() :
    head_(nullptr)
{
}



StackList::StackList(std::initializer_list<int> list)
    : head_(nullptr)
{
    std::initializer_list<int>::iterator it = list.end();
    while (it != list.begin())
    {
        Push(*(--it));
    }
}



StackList::StackList(const StackList& other) :
    head_(nullptr)
{
    Node* prev_node = nullptr;
    Node* curr = other.head_;
    while (curr != nullptr)
    {
        Node* new_node = new Node(curr->data_);

        if (head_ != nullptr)
        {
            prev_node->next_ = new_node;
        }
        else
        {
            head_ = new_node;
        }
        prev_node = new_node;
        curr = curr->next_;
    }
}



StackList& StackList::operator=(StackList other) noexcept
{
    other.Swap(*this);
    return *this;
}



StackList::~StackList()
{
    Node* curr = head_;
    while (curr != nullptr)
    {
        Node* temp = curr->next_;
        delete curr;
        curr = temp;
    }
}



void StackList::Swap(StackList& other) noexcept
{
    using std::swap;
    swap(head_, other.head_);
}



void StackList::Push(int data)
{
    Node* new_node = new Node(data);
    new_node->next_ = head_;
    head_ = new_node;
}



void StackList::Pop()
{
    if (head_ != nullptr) {
        Node* temp = head_;
        head_ = head_->next_;
        delete temp;
    }
    else
    {
        std::cout << "The stack is empty\n";
    }
}



int StackList::Top() const
{
    if (head_ != nullptr)
    {
        return head_->data_;
    }
    else
    {
        std::cout << "The stack is empty\n";
        return INT_MIN;
    }
}



int StackList::Size() const
{
    int size = 0;
    Node* curr = head_;
    while (curr != nullptr) {
        size++;
        curr = curr->next_;
    }
    return size;
}



bool StackList::IsEmpty() const
{
    return (head_ == nullptr);
}









void TestStackList()
{
    using std::cout;
    StackList stack = {1, 8};
    cout << "Stack (list):\n" << stack;
    cout << "Size = " << stack.Size() << "\n\n";

    cout << "Push {7}:\n";
    stack.Push(7);
    cout << stack << "\n";
    cout << "Is empty = " << (stack.IsEmpty() ? "true" : "false") << "\n";
    cout << "Top = {" << stack.Top() << "}\n\n";

    stack.Pop();
    cout << "Popped:\n" << stack << "\n";

    cout << "Size = " << stack.Size() << "\n";
    cout << "Top = {" << stack.Top() << "}\n\n";

    stack.Pop();
    cout << "Popped:\n" << stack << "\n";
    cout << "Size = " << stack.Size() << "\n";
    cout << "Top = {" << stack.Top() << "}\n\n";

    stack.Pop();
    cout << "Popped:\n" << stack;
    cout << "Size = " << stack.Size() << "\n";
    cout << "Is empty = " << (stack.IsEmpty() ? "true" : "false") << "\n";

    cout << "Push {11}:\n";
    stack.Push(11);
    cout << stack << "\n";

    cout << "Push {12}:\n";
    stack.Push(12);
    cout << stack << "\n";
}

#endif // STACKLIST_H
