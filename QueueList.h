#ifndef QUEUELIST_H
#define QUEUELIST_H

#include <algorithm>
#include <iostream>

class QueueList
{
    struct Node
    {
        Node(int in) : next_(nullptr), data_(in) { }
        Node* next_;
        int data_;
    };

public:
    QueueList();
    QueueList(std::initializer_list<int> list);
    QueueList(const QueueList& other);
    ~QueueList();

    QueueList& operator=(QueueList other) noexcept;
    void Swap(QueueList& other) noexcept;

    void Enqueue(int data);
    void Dequeue();

    int Front() const;
    int Back() const;

    int Size() const;
    bool IsEmpty() const;
    friend std::ostream& operator<<(std::ostream& ostream, const QueueList& rhs);

private:
    Node* head_;
    Node* tail_;
};


void swap(QueueList& lhs, QueueList& rhs) noexcept
{
    lhs.Swap(rhs);
}


std::ostream& operator<<(std::ostream& ostream, const QueueList& rhs)
{
    QueueList::Node* curr_node = rhs.head_;
    while (curr_node != nullptr)
    {
        ostream << curr_node->data_ << " -> ";
        curr_node = curr_node->next_;
    }
    return ostream << "\n";
}



QueueList::QueueList() :
    head_(nullptr),
    tail_(nullptr)
{
}



QueueList::QueueList(std::initializer_list<int> list)
    : head_(nullptr),
      tail_(nullptr)
{
    std::initializer_list<int>::iterator it = list.end();
    for (it = list.begin(); it != list.end(); it++)
        Enqueue(*it);
}



QueueList::QueueList(const QueueList& other) :
    head_(nullptr),
    tail_(nullptr)
{
    Node* curr = other.head_;
    while (curr != nullptr)
    {
        Node* new_node = new Node(curr->data_);
        if (tail_ != nullptr)
        {
            tail_->next_ = new_node;
            tail_ = tail_->next_;
        }
        else
        {
            head_ = new_node;
            tail_ = new_node;
        }

        curr = curr->next_;
    }
}



QueueList::~QueueList()
{
    Node* curr = head_;
    while (curr != nullptr)
    {
        Node* temp = curr->next_;
        delete curr;
        curr = temp;
    }
}



QueueList& QueueList::operator=(QueueList other) noexcept
{
    other.Swap(*this);
    return *this;
}



void QueueList::Swap(QueueList& other) noexcept
{
    using std::swap;
    swap(head_, other.head_);
    swap(tail_, other.tail_);
}



void QueueList::Enqueue(int data)
{
    Node* new_node = new Node(data);
    if (tail_ == nullptr)
        head_ = new_node;
    else
        tail_->next_ = new_node;

    tail_ = new_node;
}



void QueueList::Dequeue()
{
    if (head_ == nullptr)
    {
        std::cout << "The queue is empty\n";
    }
    else
    {
        Node* temp = head_->next_;
        delete head_;
        head_ = temp;
        if (head_ == nullptr)
            tail_ = nullptr;
    }
}



int QueueList::Front() const
{
    if (head_ != nullptr)
    {
        return head_->data_;
    }
    else
    {
        std::cout << "The queue is empty\n";
        return INT_MIN;
    }
}



int QueueList::Back() const
{
    if (tail_ != nullptr)
    {
        return tail_->data_;
    }
    else
    {
        std::cout << "The queue is empty\n";
        return INT_MIN;
    }
}



int QueueList::Size() const
{
    int size = 0;
    Node* curr = head_;
    while (curr != nullptr) {
        size++;
        curr = curr->next_;
    }
    return size;
}



bool QueueList::IsEmpty() const
{
    return (head_ == nullptr);
}









void TestQueueList()
{
    using std::cout;
    QueueList queue = {1, 8};
    cout << "Queue (array):\n" << queue;
    cout << "Size = " << queue.Size() << "\n";
    cout << "Front = {" << queue.Front() << "}\n";
    cout << "Back = {" << queue.Back() << "}\n\n";

    cout << "Enqueue {22}:\n";
    queue.Enqueue(22);
    cout << queue << "\n";

    cout << "Is empty = " << (queue.IsEmpty() ? "true" : "false") << "\n\n";

    cout << "Dequeued:\n";
    queue.Dequeue();
    cout << queue << "\n";

    cout << "Size = " << queue.Size() << "\n";
    cout << "Front = {" << queue.Front() << "}\n";
    cout << "Back = {" << queue.Back() << "}\n\n";

    cout << "Dequeued:\n";
    queue.Dequeue();
    cout << queue << "\n";

    cout << "Size = " << queue.Size() << "\n";
    cout << "Front = {" << queue.Front() << "}\n";
    cout << "Back = {" << queue.Back() << "}\n\n";

    cout << "Dequeued:\n";
    queue.Dequeue();
    cout << queue;

    cout << "Size = " << queue.Size() << "\n";
    cout << "Is empty = " << (queue.IsEmpty() ? "true" : "false") << "\n";

    cout << "Enqueue {33}:\n";
    queue.Enqueue(33);
    cout << queue << "\n";

    cout << "Enqueue {44}:\n";
    queue.Enqueue(44);
    cout << queue << "\n";

    QueueList queue2;
    queue.Enqueue(123);
    queue2.Enqueue(345);
    swap(queue, queue2);
    cout << queue << "\n";
    cout << queue2 << "\n";
}
#endif // QUEUELIST_H
