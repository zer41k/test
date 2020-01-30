#ifndef LISTDOUBLY_H
#define LISTDOUBLY_H

#include <iostream>

class ListDoubly
{
    struct Node
    {
        Node(int in) :
            prev_(nullptr),
            next_(nullptr),
            data_(in)
        {
        }
        Node* prev_;
        Node* next_;
        int data_;
    };

public:
    ListDoubly();
    ListDoubly(std::initializer_list<int> list);
    ListDoubly(const ListDoubly& other);
    ListDoubly& operator=(ListDoubly other) noexcept;
    ~ListDoubly();

    void PrintReversedList() const;

    void AppendNode(int data);
    void PrependNode(int data);
    void InsertAtIndex(int ind, int data);

    void RemoveFirst();
    void RemoveLast();
    void RemoveFirstOccurence(int data);
    void RemoveAtIndex(int ind);

    int GetSize() const;
    bool Search(int data) const;
    int At(int ind) const;

    void Reverse();

    void Swap(ListDoubly& other) noexcept;
    friend std::ostream& operator<<(std::ostream& ostream, const ListDoubly& rhs);

private:
    Node* head_;
    Node* tail_;
};


void swap(ListDoubly& lhs, ListDoubly& rhs) noexcept
{
    lhs.Swap(rhs);
}


std::ostream& operator<<(std::ostream& ostream, const ListDoubly& rhs)
{
    ListDoubly::Node* curr_node = rhs.head_;
    std::cout << "<-> ";
    while (curr_node != nullptr)
    {
        std::cout << curr_node->data_ << " <-> ";
        curr_node = curr_node->next_;
    }

    return ostream << "\n";
}



ListDoubly::ListDoubly()
    : head_(nullptr),
      tail_(nullptr)
{
}



ListDoubly::ListDoubly(std::initializer_list<int> list)
    : head_(nullptr),
      tail_(nullptr)
{
    std::initializer_list<int>::iterator it;
    for (it = list.begin(); it != list.end(); it++)
        AppendNode(*it);
}



ListDoubly::ListDoubly(const ListDoubly& other) :
    head_(nullptr),
    tail_(nullptr)
{
    Node* curr = other.head_;
    while (curr != nullptr)
    {
        Node* new_node = new Node(curr->data_);
        if (head_ != nullptr) {
            tail_->next_ = new_node;
            new_node->prev_ = tail_;
        }
        else
        {
            head_ = new_node;
        }

        tail_ = new_node;
        curr = curr->next_;
    }
}



ListDoubly& ListDoubly::operator=(ListDoubly other) noexcept
{
    other.Swap(*this);
    return *this;
}


ListDoubly::~ListDoubly()
{
    Node* curr_node = head_;
    while (curr_node != nullptr)
    {
        Node* temp = curr_node;
        curr_node = curr_node->next_;
        delete temp;
    }
}



void ListDoubly::PrintReversedList() const
{
    Node* curr_node = tail_;
    std::cout << "<-> ";
    while (curr_node != nullptr)
    {
        std::cout << curr_node->data_ << " <-> ";
        curr_node = curr_node->prev_;
    }
}



void ListDoubly::AppendNode(int data)
{
    Node* new_node = new Node(data);

    if (tail_ != nullptr)
    {
        tail_->next_ = new_node;
        new_node->prev_ = tail_;
    }
    else
    {
        head_ = new_node;
    }

    tail_ = new_node;
}



void ListDoubly::PrependNode(int data)
{
    Node* new_node = new Node(data);

    if (head_ != nullptr)
    {
        head_->prev_ = new_node;
        new_node->next_ = head_;
    }
    else
    {
        tail_ = new_node;
    }

    head_ = new_node;
}



void ListDoubly::InsertAtIndex(int ind, int data)
{
    if (ind == 0)
    {
        PrependNode(data);
    }
    else if (ind > 0)
    {
        Node* prev_node = head_;
        for (int i = 0; prev_node != nullptr && i < ind - 1; i++)
            prev_node = prev_node->next_;

        if (prev_node != nullptr) {
            Node* new_node = new Node(data);
            new_node->prev_ = prev_node;
            new_node->next_ = prev_node->next_;

            if (prev_node->next_ != nullptr)
                prev_node->next_->prev_ = new_node;
            else
                tail_= new_node;

            prev_node->next_ = new_node;
        }
    }
}



void ListDoubly::RemoveFirst()
{
    if (head_ != nullptr)
    {
        if (head_ != tail_)
        {
            head_ = head_->next_;
            delete head_->prev_;
            head_->prev_ = nullptr;
        }
        else
        {
            delete head_;
            head_ = nullptr;
            tail_ = nullptr;
        }
    }
}



void ListDoubly::RemoveLast()
{
    if (tail_ != nullptr)
    {
        if (tail_ != head_)
        {
            tail_ = tail_->prev_;
            delete tail_->next_;
            tail_->next_ = nullptr;
        }
        else
        {
            delete tail_;
            head_ = nullptr;
            tail_ = nullptr;
        }
    }
}



void ListDoubly::RemoveFirstOccurence(int data)
{
    Node* curr_node = head_;
    while (curr_node != nullptr)
    {
        if (curr_node->data_ == data)
        {
            if (curr_node->prev_ == nullptr)
                head_ = curr_node->next_;
            else
                curr_node->prev_->next_ = curr_node->next_;

            if (curr_node->next_ == nullptr)
                tail_ = curr_node->prev_;
            else
                curr_node->next_->prev_ = curr_node->prev_;

            delete curr_node;
            return;
        }
        curr_node = curr_node->next_;
    }
}



void ListDoubly::RemoveAtIndex(int ind)
{
    if (ind == 0)
    {
        RemoveFirst();
    }
    else if (ind > 0)
    {
        Node* curr_node = head_;
        for (int i = 0; curr_node != nullptr && i < ind; i++)
            curr_node = curr_node->next_;

        if (curr_node != nullptr)
        {
            curr_node->prev_->next_ = curr_node->next_;

            if (curr_node != tail_)
                curr_node->next_->prev_ = curr_node->prev_;
            else
                tail_ = curr_node->prev_;

            delete curr_node;
        }
    }
}



int ListDoubly::GetSize() const
{
    int size{};
    Node* curr_node = head_;
    while (curr_node != nullptr) {
        size++;
        curr_node = curr_node->next_;
    }
    return size;
}



bool ListDoubly::Search(int data) const
{
    Node* curr_node = head_;
    while (curr_node != nullptr)
    {
        if (curr_node->data_ == data)
            return true;

        curr_node = curr_node->next_;
    }
    return false;
}



int ListDoubly::At(int ind) const
{
    int ret_data{};
    Node* curr_node = head_;
    for (int i = 0; curr_node != nullptr && i < ind; i++)
        curr_node = curr_node->next_;

    if (curr_node != nullptr)
        ret_data = curr_node->data_;

    return ret_data;
}



void ListDoubly::Reverse()
{
    Node* curr_node = head_;
    while (curr_node != nullptr)
    {
        std::swap(curr_node->next_, curr_node->prev_);
        curr_node = curr_node->prev_;
    }
    std::swap(head_, tail_);
}



void ListDoubly::Swap(ListDoubly& other) noexcept
{
    using std::swap;
    swap(head_, other.head_);
    swap(tail_, other.tail_);
}









void TestListDoubly()
{
    using std::cout;
    ListDoubly list = {1, 2, 6, 5, 4, 3};
    cout << "Doubly linked list:\n" << list << "\n";

    list.AppendNode(7);
    cout << "Appened {7}:\n" << list << "\n";
    list.PrependNode(8);
    cout << "Prepended {8}:\n" << list << "\n";

    list.InsertAtIndex(0, 11);
    cout << "Inserted {11} at index [0]:\n" << list << "\n";
    list.InsertAtIndex(3, 22);
    cout << "Inserted {22} at index [3]:\n" << list << "\n";
    list.InsertAtIndex(10, 33);
    cout << "Inserted {33} at index [10]:\n" << list << "\n";

    list.RemoveFirst();
    cout << "Removed first:\n" << list << "\n";
    list.RemoveLast();
    cout << "Removed last:\n" << list << "\n";
    list.RemoveAtIndex(3);
    cout << "Removed at index [3]:\n" << list << "\n";
    list.RemoveAtIndex(0);
    cout << "Removed at index [0]:\n" << list << "\n";
    list.RemoveAtIndex(6);
    cout << "Removed at index [6]:\n" << list << "\n";
    list.RemoveFirstOccurence(5);
    cout << "Removed {5}:\n" << list << "\n";

    cout << "Reverse print:\n";
    list.PrintReversedList();
    cout << "\n\n";
    list.Reverse();
    cout << "Reversed:\n" << list << "\n";

    cout << "List Size = " << list.GetSize() << "\n";
    cout << "Seach {3} = " << (list.Search(3) ? "found" : "not found") << "\n";
    cout << "Seach {2} = " << (list.Search(2) ? "found" : "not found") << "\n";
    cout << "Value at index {0} = " << list.At(0) << "\n";
    cout << "Value at index {3} = " << list.At(3) << "\n";
}
#endif // LISTDOUBLY_H
