#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <algorithm>

// Max heap
class Heap
{
public:
    Heap() = delete;
    explicit Heap(int capaciy);
    Heap(int* arr, int size);
    Heap(const Heap& other);
    Heap& operator=(Heap other) noexcept;
    ~Heap();

    void Insert(int data);
    int GetMax() const;
    int ExtractMax();
    void HeapifyMax(int index);
    void IncreaseKey(int index, int data);
    void DeleteKey(int index);

    static int Parent(int i);
    static int Left(int i);
    static int Right(int i);
    static bool IsPowerOfTwo(int i);

    void Swap(Heap& other) noexcept;
    friend std::ostream& operator<<(std::ostream& ostream, const Heap& rhs);

private:
    int capacity_;
    int size_;
    int* arr_;
};


void swap(Heap& lhs, Heap& rhs) noexcept
{
    lhs.Swap(rhs);
}


std::ostream& operator<<(std::ostream& ostream, const Heap& rhs)
{
    for (int i = 0; i < rhs.size_; i++)
    {
        ostream << rhs.arr_[i] << " ";
        if (Heap::IsPowerOfTwo(i + 2))
            ostream << "\n";
    }
    return ostream << "\n";
}



Heap::Heap(int capacity) :
    capacity_(capacity),
    size_(0),
    arr_(new int[capacity])
{
}



Heap::Heap(int* arr, int size) :
    capacity_(size),
    size_(size),
    arr_(new int[capacity_])
{
    std::copy(arr, arr + size_, arr_);

    for (int i = size / 2 - 1; i >= 0; i--)
        HeapifyMax(i);
}



Heap::Heap(const Heap& other) :
    capacity_(other.capacity_),
    size_(other.size_),
    arr_(new int[capacity_])
{
    std::copy(other.arr_, other.arr_ + size_, arr_);
}



Heap& Heap::operator=(Heap other) noexcept
{
    other.Swap(*this);
    return *this;
}



Heap::~Heap()
{
    delete[] arr_;
}



void Heap::Insert(int data)
{
    if (size_ >= capacity_)
    {
        std::cout << "The heap is full\n";
        return;
    }

    int i = size_;
    arr_[i] = data;
    size_++;

    while(Parent(i) >= 0 && arr_[i] > arr_[Parent(i)])
    {
        std::swap(arr_[i], arr_[Parent(i)]);
        i = Parent(i);
    }
}



int Heap::GetMax() const
{
    return arr_[0];
}



int Heap::ExtractMax()
{
    if (size_ <= 0)
    {
        std::cout << "The heap is empty\n";
        return INT_MIN;
    }
    else if (size_ == 1)
    {
        size_--;
        return arr_[0];
    }


    int min_val = arr_[0];
    arr_[0] = arr_[size_ - 1];
    size_--;

    HeapifyMax(0);

    return min_val;
}



void Heap::HeapifyMax(int index)
{
    int greater_ind = index;
    if (Left(index) < size_ && arr_[Left(index)] > arr_[greater_ind])
        greater_ind = Left(index);

    if (Right(index) < size_ && arr_[Right(index)] > arr_[greater_ind])
        greater_ind = Right(index);

    if (greater_ind != index)
    {
        std::swap(arr_[index], arr_[greater_ind]);
        HeapifyMax(greater_ind);
    }
}



void Heap::IncreaseKey(int index, int data)
{
    if (index >= size_ || data <= arr_[index])
        return;

    arr_[index] = data;
    while (Parent(index) >= 0 && arr_[Parent(index)] < arr_[index])
    {
        std::swap(arr_[index], arr_[Parent(index)]);
        index = Parent(index);
    }
}



void Heap::DeleteKey(int index)
{
    if (index < 0 || index >= size_)
        return;

    IncreaseKey(index, INT_MAX);
    ExtractMax();
}



int Heap::Parent(int i)
{
    return (i - 1) / 2;
}

int Heap::Left(int i)
{
    return (i * 2) + 1;
}

int Heap::Right(int i)
{
    return (i * 2) + 2;
}

bool Heap::IsPowerOfTwo(int value)
{
    if (value <= 0)
        return false;

    while ((value % 2) == 0)
    {
        value /= 2;
        if (value == 1)
            return true;
    }

    return false;
}



void Heap::Swap(Heap& other) noexcept
{
    using std::swap;
    swap(capacity_, other.capacity_);
    swap(size_, other.size_);
    swap(arr_, other.arr_);
}









void TestHeap()
{
    int arr[] = {5, 1, 7, 4, 9, 3, 2, 6, 8};
    Heap heap(arr, sizeof(arr) / sizeof(arr[0]));
    std::cout << "Heap:\n" << heap << "\n";

    std::cout << "Max = {" << heap.GetMax() << "}\n";

    std::cout << "Insert {13}:\n";
    heap.Insert(13);
    std::cout << heap << "\n";

    std::cout << "Extruct max = {" << heap.ExtractMax() << "}\n";
    std::cout << heap << "\n";

    std::cout << "Delete at index [3]\n";
    heap.DeleteKey(3);
    std::cout << heap << "\n";

    std::cout << "Increase to {77} at index [5]\n";
    heap.IncreaseKey(5, 77);
    std::cout << heap << "\n";

    std::cout << "Insert {13}:\n";
    heap.Insert(13);
    std::cout << heap << "\n";

}
#endif // HEAP_H
