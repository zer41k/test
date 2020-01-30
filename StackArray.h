#ifndef STACKARRAY_H
#define STACKARRAY_H

#include <algorithm>
#include <iostream>

class StackArray
{
public:
    StackArray() = delete;
    explicit StackArray(int size);
    StackArray(std::initializer_list<int> list);
    StackArray(const StackArray& other);
    StackArray& operator=(StackArray other) noexcept;
    ~StackArray();

    void Push(int data);
    void Pop();
    int Top() const;

    int Size() const;
    bool IsEmpty() const;
    bool IsFull() const;

    void Swap(StackArray& other) noexcept;
    friend std::ostream& operator<<(std::ostream& ostream, const StackArray& rhs);

private:
    int size_;
    int top_;
    int* arr_;
};


void swap(StackArray& lhs, StackArray& rhs) noexcept
{
    lhs.Swap(rhs);
}


std::ostream& operator<<(std::ostream& ostream, const StackArray& rhs)
{
    for (int i = rhs.top_; i >= 0; i--)
        ostream << rhs.arr_[i] << " -> ";
    return ostream << "\n";
}



StackArray::StackArray(int size) :
    size_(size),
    top_(-1),
    arr_(new int[size_])
{

}



StackArray::StackArray(std::initializer_list<int> list) :
    size_(list.size()),
    top_(size_ - 1),
    arr_(new int[size_])
{
    std::reverse_copy(list.begin(), list.end(), arr_);
}

StackArray::StackArray(const StackArray& other) :
    size_(other.size_),
    top_(other.top_),
    arr_(new int[other.size_])
{
    std::copy(other.arr_, other.arr_ + other.size_, arr_);
}



StackArray& StackArray::operator=(StackArray other) noexcept
{
    other.Swap(*this);
    return *this;
}



StackArray::~StackArray()
{
    delete[] arr_;
}



void StackArray::Push(int value)
{
    if (top_ == size_ - 1)
    {
        std::cout << "The stack is full\n";
    }
    else
    {
        ++top_;
        arr_[top_] = value;
    }
}



void StackArray::Pop()
{
    if (top_ == -1)
    {
        std::cout << "The stack is empty\n";
    }
    else
    {
        --top_;
    }
}



int StackArray::Top() const
{
    if (top_ == -1)
    {
        std::cout << "The stack is empty\n";
        return INT_MIN;
    }
    else
    {
        return arr_[top_];
    }
}



int StackArray::Size() const
{
    return top_ + 1;
}



bool StackArray::IsEmpty() const
{
    return top_ == -1;
}



bool StackArray::IsFull() const
{
    return top_ == size_ - 1;
}



void StackArray::Swap(StackArray& other) noexcept
{
    using std::swap;
    swap(arr_, other.arr_);
    swap(top_, other.top_);
    swap(size_, other.size_);
}









void TestStackArray()
{
    using std::cout;
    StackArray stack = {1, 4, 8};
    cout << "Stack (array):\n" << stack;
    cout << "Size = " << stack.Size() << "\n\n";

    cout << "Push {7}:\n";
    stack.Push(7);
    cout << stack << "\n";
    cout << "Is empty = " << (stack.IsEmpty() ? "true" : "false") << "\n";
    cout << "Is full = " << (stack.IsFull() ? "true" : "false") << "\n";
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
    cout << "Is full = " << (stack.IsFull() ? "true" : "false") << "\n";

    cout << "Push {11}:\n";
    stack.Push(11);
    cout << stack << "\n";

    cout << "Push {12}:\n";
    stack.Push(12);
    cout << stack << "\n";
}

#endif // STACKARRAY_H
