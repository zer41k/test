#ifndef QUEUEARRAY_H
#define QUEUEARRAY_H

#include <algorithm>
#include <iostream>

class QueueArray
{
public:
    QueueArray() = delete;
    explicit QueueArray(int size);
    QueueArray(std::initializer_list<int> list);
    QueueArray(const QueueArray& other);
    ~QueueArray();

    QueueArray& operator=(QueueArray other) noexcept;
    void Swap(QueueArray& other) noexcept;

    void Enqueue(int data);
    void Dequeue();

    int Front() const;
    int Back() const;

    int Size() const;
    bool IsFull() const;
    bool IsEmpty() const;
    friend std::ostream& operator<<(std::ostream& ostream, const QueueArray& rhs);

private:   
    int size_;
    int front_;
    int rear_;
    int* arr_;
};


void swap(QueueArray& lhs, QueueArray& rhs) noexcept
{
    lhs.Swap(rhs);
}


std::ostream& operator<<(std::ostream& ostream, const QueueArray& rhs)
{
    if (rhs.front_ != -1)
        for (int i = rhs.front_; i <= rhs.rear_ % rhs.size_; i++)
            ostream << rhs.arr_[i % rhs.size_] << " -> ";
    return ostream << "\n";
}



QueueArray::QueueArray(int size) :    
    size_(size),
    front_(-1),
    rear_(-1),
    arr_(new int[size])
{
}



QueueArray::QueueArray(const QueueArray& other) :
    size_(other.size_),
    front_(other.front_),
    rear_(other.rear_),
    arr_(new int[other.size_])
{
    std::copy(other.arr_, other.arr_ + other.size_, arr_);
}



QueueArray::QueueArray(std::initializer_list<int> list) :
    size_(list.size()),
    front_(0),
    rear_(size_ - 1),
    arr_(new int[size_])
{
    std::copy(list.begin(), list.end(), arr_);
}



QueueArray::~QueueArray()
{
    delete[] arr_;
}



QueueArray& QueueArray::operator=(QueueArray other) noexcept
{
    other.Swap(*this);
    return *this;
}



void QueueArray::Swap(QueueArray& other) noexcept
{
    using std::swap;    
    swap(size_, other.size_);
    swap(front_, other.front_);
    swap(rear_, other.rear_);
    swap(arr_, other.arr_);
}



void QueueArray::Enqueue(int data)
{
    if (IsFull())
    {
        std::cout << "The queue is full\n";
    }
    else
    {
        if (IsEmpty())
        {
            rear_ = 0;
            front_ = 0;
        }
        else
        {
            rear_ = (rear_ + 1) % size_;
        }
        arr_[rear_] = data;
    }
}



void QueueArray::Dequeue()
{
    if (IsEmpty())
    {
       std::cout << "The queue is empty\n";
    }
    else
    {
        if (front_ == rear_)
        {
            front_ = -1;
            rear_ = -1;
        }
        else
        {
            front_ = (front_ + 1) % size_;
        }
    }
}



int QueueArray::Front() const
{
    if (IsEmpty())
    {
       std::cout << "The queue is empty\n";
       return INT_MIN;
    }
    else
    {
        return arr_[front_];
    }
}



int QueueArray::Back() const
{
    if (IsEmpty())
    {
       std::cout << "The queue is empty\n";
       return INT_MIN;
    }
    else
    {
        return arr_[rear_];
    }
}



int QueueArray::Size() const
{
    if (front_ == -1)
    {
        return 0;
    }
    else
    {
        if (front_ <= rear_)
            return rear_ - front_ + 1;
        else
            return rear_ + size_ - front_ + 1;
    }
}



bool QueueArray::IsFull() const
{
    return ((rear_ + 1) % size_ == front_);
}



bool QueueArray::IsEmpty() const
{
    return (front_ == -1 && rear_ == -1);
}









void TestQueueAray()
{
    using std::cout;
    QueueArray queue = {1, 8, 2};
    cout << "Queue (array):\n" << queue;
    cout << "Size = " << queue.Size() << "\n";
    cout << "Front = {" << queue.Front() << "}\n";
    cout << "Back = {" << queue.Back() << "}\n\n";

    cout << "Enqueue {22}:\n";
    queue.Enqueue(22);
    cout << queue << "\n";

    cout << "Is empty = " << (queue.IsEmpty() ? "true" : "false") << "\n";
    cout << "Is full = " << (queue.IsFull() ? "true" : "false") << "\n\n";

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
    cout << "Back = {" << queue.Back() << "}\n";

    cout << "Dequeued:\n";
    queue.Dequeue();
    cout << queue << "\n";

    cout << "Size = " << queue.Size() << "\n";

    cout << "Is empty = " << (queue.IsEmpty() ? "true" : "false") << "\n";
    cout << "Is full = " << (queue.IsFull() ? "true" : "false") << "\n\n";

    cout << "Enqueue {33}:\n";
    queue.Enqueue(33);
    cout << queue << "\n";

    cout << "Enqueue {44}:\n";
    queue.Enqueue(44);
    cout << queue << "\n";

    QueueArray queue2(5);
    swap(queue2, queue);

    queue.Enqueue(123);
    queue2.Enqueue(345);
    cout << queue << "\n";
    cout << queue2 << "\n";
}
#endif // QUEUEARRAY_H

