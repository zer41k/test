#ifndef LISTSINGLY_H
#define LISTSINGLY_H

#include <iostream>

class ListSingly
{
    struct Node
    {
        Node(int in) :
            next_(nullptr),
            data_(in)
        {
        }
        Node* next_;
        int data_;
    };

public:
    ListSingly();
    ListSingly(std::initializer_list<int> list);
    ListSingly(const ListSingly& other);
    ListSingly& operator=(ListSingly other) noexcept;
    ~ListSingly();

    void AppendNode(int new_data);
    void PrependNode(int new_data);
    void InsertAtIndex(int ind, int new_data);
    void RemoveFirstOccurence(int data);
    void RemoveAtIndex(int ind);

    int GetSize() const;
    bool Search(int data) const;
    int At(int ind) const;

    int FindLoopStartIndex() const;
    bool CreateLoopAtIndex(int loop_index);
    bool BreakLoop();

    void Reverse();

    void Swap(ListSingly& other) noexcept;
    friend std::ostream& operator<<(std::ostream& ostream, const ListSingly& rhs);

private:
    Node* head_;
};


void swap(ListSingly& lhs, ListSingly& rhs) noexcept
{
    lhs.Swap(rhs);
}


std::ostream& operator<<(std::ostream& ostream, const ListSingly& rhs)
{
    ListSingly::Node* curr_node = rhs.head_;
    while (curr_node != nullptr)
    {
        ostream << curr_node->data_ << " -> ";
        curr_node = curr_node->next_;
    }
    return ostream << "\n";
}



ListSingly::ListSingly()
    : head_(nullptr)
{
}



ListSingly::ListSingly(std::initializer_list<int> list)
    : head_(nullptr)
{
    std::initializer_list<int>::iterator it = list.end();
    while (it != list.begin())
        PrependNode(*(--it));
}



ListSingly::ListSingly(const ListSingly& other) :
    head_(nullptr)
{
    Node* prev_node = nullptr;
    Node* curr = other.head_;
    while (curr != nullptr)
    {
        Node* new_node = new Node(curr->data_);
        if (head_ != nullptr)
            prev_node->next_ = new_node;
        else
            head_ = new_node;

        prev_node = new_node;
        curr = curr->next_;
    }
}



ListSingly& ListSingly::operator=(ListSingly other) noexcept
{
    other.Swap(*this);
    return *this;
}



ListSingly::~ListSingly()
{
    Node* curr_node = head_;
    while (curr_node != nullptr)
    {
        Node* temp = curr_node;
        curr_node = curr_node->next_;
        delete temp;
    }
}



void ListSingly::AppendNode(int new_data)
{
    Node* new_node = new Node(new_data);
    if (head_ != nullptr)
    {
        Node* curr_node = head_;
        while (curr_node->next_ != nullptr)
        {
            curr_node = curr_node->next_;
        }
        curr_node->next_ = new_node;
    }
    else
    {
        head_ = new_node;
    }
}


void ListSingly::PrependNode(int new_data)
{
    Node* new_node = new Node(new_data);

    if (head_ != nullptr)
        new_node->next_ = head_;        
    else
        head_ = new_node;

    head_ = new_node;
}


void ListSingly::InsertAtIndex(int ind, int new_data)
{
    if (ind == 0)
    {
        PrependNode(new_data);
    }
    else if (ind > 0)
    {
        Node* prev_node = head_;
        for (int i = 0; prev_node != nullptr && i < ind - 1; i++)
            prev_node = prev_node->next_;

        if (prev_node != nullptr) {
            Node* new_node = new Node(new_data);
            new_node->next_ = prev_node->next_;
            prev_node->next_ = new_node;
        }
    }
}


void ListSingly::RemoveFirstOccurence(int data)
{
    Node* prev_node = nullptr;
    Node* curr_node = head_;
    while (curr_node != nullptr)
    {
        if (curr_node->data_ == data)
        {
            if (prev_node == nullptr)
            {
                head_ = curr_node->next_;
            }
            else
            {
                prev_node->next_ = curr_node->next_;
            }
            delete curr_node;
            return;
        }
        prev_node = curr_node;
        curr_node = curr_node->next_;
    }
}


void ListSingly::RemoveAtIndex(int ind)
{
    if (ind == 0)
    {
        if (head_ != nullptr)
        {
            Node* temp = head_;
            head_ = head_->next_;
            delete temp;
        }
    }
    else if (ind > 0)
    {
        Node* prev_node = head_;
        for (int i = 0; prev_node != nullptr && i < ind - 1; i++)
            prev_node = prev_node->next_;

        if (prev_node != nullptr && prev_node->next_ != nullptr)
        {
            Node* temp = prev_node->next_;
            prev_node->next_ = prev_node->next_->next_;
            delete temp;
        }

    }
}


int ListSingly::GetSize() const
{
    int size = 0;
    Node* curr_node = head_;
    while (curr_node != nullptr) {
        size++;
        curr_node = curr_node->next_;
    }
    return size;
}


bool ListSingly::Search(int data) const
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


int ListSingly::At(int ind) const
{
    int ret_data = int{};

    Node* curr_node = head_;
    for (int i = 0; curr_node != nullptr && i < ind; i++)
        curr_node = curr_node->next_;

    if (curr_node != nullptr)
        ret_data = curr_node->data_;

    return ret_data;
}


int ListSingly::FindLoopStartIndex() const // -1 -> no loop
{
    int loop_start_ind = INT_MIN;
    Node* curr_slow = head_;
    Node* curr_fast = head_;

    while (curr_fast != nullptr && curr_fast->next_ != nullptr)
    {
        curr_slow = curr_slow->next_;
        curr_fast = curr_fast->next_->next_;

        if (curr_fast == curr_slow)
        {
            break;
        }
    }

    if (curr_fast == curr_slow && curr_fast != nullptr)
    {
        curr_fast = head_;
        loop_start_ind = 0;
        while (curr_fast != curr_slow)
        {
            curr_slow = curr_slow->next_;
            curr_fast = curr_fast->next_;
            loop_start_ind++;
        }
    }

    return loop_start_ind;
}


bool ListSingly::CreateLoopAtIndex(int loop_index)
{
    bool success = false;
    if (loop_index >= 0)
    {
        Node* loop_node = head_;
        for (int i = 0; loop_node != nullptr && i < loop_index; i++)
            loop_node = loop_node->next_;
        if (loop_node != nullptr)
        {
            Node* last_node = loop_node;
            while (last_node->next_!= nullptr)
            {
                last_node = last_node->next_;
            }

            if (loop_node != last_node) {
                last_node->next_ = loop_node;
                success = true;
            }
        }
    }
    return success;
}


bool ListSingly::BreakLoop()
{
    bool success = false;
    int loop_index = FindLoopStartIndex();
    if (loop_index != -1)
    {
        Node* loop_node = head_;
        for (int i = 0; i < loop_index; i++)
            loop_node = loop_node->next_;

        Node* prev_loop_node = loop_node;
        while (prev_loop_node->next_ != loop_node)
        {
            prev_loop_node = prev_loop_node->next_;
        }
        prev_loop_node->next_ = nullptr;
        success = true;
    }
    return success;
}


void ListSingly::Reverse()
{
    Node* prev_node = nullptr;
    Node* next_node = nullptr;
    Node* curr_node = head_;
    while (curr_node != nullptr)
    {
        next_node = curr_node->next_;
        curr_node->next_ = prev_node;

        prev_node = curr_node;
        curr_node = next_node;
    }
    head_ = prev_node;
}



void ListSingly::Swap(ListSingly& other) noexcept
{
    using std::swap;
    swap(head_, other.head_);
}









void TestListSingly()
{
    using std::cout;
    ListSingly list = {8, 7, 1, 2, 3, 4};

    cout << "Singly linked list:\n" << list << "\n";

    list.AppendNode(5);
    cout << "Appened {5}:\n" << list << "\n";
    list.PrependNode(6);
    cout << "Prepended {6}:\n" << list << "\n";

    list.InsertAtIndex(0, 11);
    cout << "Inserted {11} at index [0]:\n" << list << "\n";
    list.InsertAtIndex(3, 88);
    cout << "Inserted {88} at index [3]:\n" << list << "\n";
    list.InsertAtIndex(10, 66);
    cout << "Inserted {66} at index [10]:\n" << list << "\n";

    list.RemoveFirstOccurence(11);
    cout << "Removed {11}:\n" << list << "\n";
    list.RemoveFirstOccurence(1);
    cout << "Removed {1}:\n" << list << "\n";
    list.RemoveFirstOccurence(66);
    cout << "Removed {66}:\n" << list << "\n";

    list.RemoveAtIndex(0);
    cout << "Removed at index [0]:\n" << list << "\n";
    list.RemoveAtIndex(3);
    cout << "Removed at index [3]:\n" << list << "\n";
    list.RemoveAtIndex(5);
    cout << "Removed at index [5]:\n" << list << "\n";

    list.Reverse();
    cout << "Reversed:\n" << list << "\n";

    cout << "List Size = " << list.GetSize() << "\n";
    cout << "Seach {3} = " << (list.Search(3) ? "found" : "not found") << "\n";
    cout << "Seach {1} = " << (list.Search(1) ? "found" : "not found") << "\n";
    cout << "Value at index {0} = " << list.At(0) << "\n";
    cout << "Value at index {3} = " << list.At(3) << "\n";

    cout << "Create loop at index [2] = " << (list.CreateLoopAtIndex(2) ? "success" : "faild") << "\n";
    cout << "Find loop star index = " << list.FindLoopStartIndex() << "\n";
    cout << "Break loop = " << (list.BreakLoop() ? "success" : "faild") << "\n";

}

#endif // LISTSINGLY_H
