#ifndef PTRSHARED_H
#define PTRSHARED_H

#include "TestClass.h"
#include <algorithm>
#include <iostream>

class RefCounter
{
public:
    RefCounter() : counter_(0) {}
    void AcquireRef() { ++counter_; }
    void ReleaseRef() { --counter_; }
    int GetRefNum() {return counter_; }
private:
    int counter_;
};


template<class T>
class PtrShared
{
public:
    explicit PtrShared(T* in = nullptr);
    PtrShared(std::nullptr_t);
    PtrShared(const PtrShared&);
    template <class U> PtrShared(const PtrShared<U>&);
    PtrShared(PtrShared&&) noexcept;
    template <class U> PtrShared(PtrShared<U>&&) noexcept;

    PtrShared& operator=(PtrShared) noexcept;
    template <class U> PtrShared& operator=(PtrShared<U>) noexcept;

    ~PtrShared();

    T* operator->() const;
    T& operator*() const;
    T* Get() const;
    RefCounter* GetRefCounter() const {return ref_counter_;}
    int GetRefNumber() const;

    void Swap(PtrShared& in) noexcept;
    explicit operator bool() const;

private:
    T* data_;
    RefCounter* ref_counter_;
};


template<class T>
void swap(PtrShared<T>& lhs, PtrShared<T>& rhs)
{
    lhs.Swap(rhs);
}


template <class T>
bool operator==(const PtrShared<T>& lhs, const PtrShared<T>& rhs)
{

    return lhs.Get() == rhs.Get();
}


template <class T>
bool operator!=(const PtrShared<T>& lhs, const PtrShared<T>& rhs)
{
    return !(lhs.Get() == rhs.Get());
}


template <class T>
std::ostream& operator<<(std::ostream& ostream, const PtrShared<T>& rhs)
{
    ostream << "*** object {";
    if (rhs.Get() != nullptr)
        ostream << *rhs.Get();
    else
        ostream << "nullptr";
    return ostream << "} -> ref_num = "<< rhs.GetRefNumber() << "\n";
}



template <class T>
PtrShared<T>::PtrShared(T* in) :
    data_(in),
    ref_counter_(new RefCounter())
{
    ref_counter_->AcquireRef();
}



template <class T>
PtrShared<T>::PtrShared(std::nullptr_t in) :
    data_(in),
    ref_counter_(new RefCounter())
{
    ref_counter_->AcquireRef();
}



template <class T>
PtrShared<T>::PtrShared(const PtrShared<T>& in) :
    data_(in.data_),
    ref_counter_(in.ref_counter_)
{
    ref_counter_->AcquireRef();
}



template <class T>
template <class U>
PtrShared<T>::PtrShared(const PtrShared<U>& in) :
    data_(in.Get()),
    ref_counter_(in.GetRefCounter())
{
    ref_counter_->AcquireRef();
}



template <class T>
PtrShared<T>::PtrShared(PtrShared<T>&& in) noexcept :
    data_(in.data_),
    ref_counter_(in.ref_counter_)
{
    in.Swap(*this);
    ref_counter_->AcquireRef();
}



template <class T>
template <class U>
PtrShared<T>::PtrShared(PtrShared<U>&& in) noexcept:
    data_(in.Get()),
    ref_counter_(in.GetRefCounter())
{
    ref_counter_->AcquireRef();
}



template <class T>
PtrShared<T>& PtrShared<T>::operator=(PtrShared<T> in) noexcept
{
    in.Swap(*this);
    return *this;
}



template <class T>
template <class U>
PtrShared<T>& PtrShared<T>::operator=(PtrShared<U> in) noexcept
{
    T* old_data = data_;
    RefCounter* old_ref_counter = ref_counter_;

    data_ = in.Get();
    ref_counter_ = in.GetRefCounter();
    ref_counter_->AcquireRef();

    old_ref_counter->ReleaseRef();
    if (old_ref_counter->GetRefNum() == 0)
    {
        delete old_data;
        delete old_ref_counter;
    }
    return *this;
}



template <class T>
PtrShared<T>::~PtrShared()
{
    ref_counter_->ReleaseRef();
    if (ref_counter_->GetRefNum() == 0)
    {
        delete data_;
        delete ref_counter_;
    }

}



template<class T>
T* PtrShared<T>::operator->() const
{
    return this->data_;
}



template<class T>
T& PtrShared<T>::operator*() const
{
    return *this->data_;
}



template<class T>
T* PtrShared<T>::Get() const
{
    return data_;
}



template<class T>
int PtrShared<T>::GetRefNumber() const
{
    return ref_counter_->GetRefNum();
}



template <class T>
void PtrShared<T>::Swap(PtrShared<T>& in) noexcept
{
    using std::swap;
    swap(data_, in.data_);
    swap(ref_counter_, in.ref_counter_);
}



template<class T>
PtrShared<T>::operator bool() const
{
    return data_;
}









PtrShared<derived> GetSharedDerived()
{
    return PtrShared<derived>(new derived(14));
}

void TestPtrShared()
{
    std::cout << "Shared pointer\n\n";

    {
        std::cout << "\nScope 1 start ->\n\n";
        PtrShared<base> ptr1(new derived(22));
        ptr1->virtualPrint();
        (*ptr1).virtualPrint();
        ptr1.Get()->virtualPrint();
        std::cout << "\n";
        std::cout << ptr1;

        PtrShared<base> ptr2(ptr1);
        std::cout << ptr2 << "\n";

        PtrShared<base> ptr3(new base(11));
        std::cout << ptr3 << "\n";
        ptr3 = ptr2;
        std::cout << ptr3 << "\n";

        std::cout << "\nScope 1 end ->\n\n";
    }

    {
        std::cout << "\n\nScope 2 start ->\n\n";

        PtrShared<base> ptr1(GetSharedDerived());
        std::cout << ptr1 << "\n";
        PtrShared<base> ptr2 = ptr1;
        std::cout << ptr1 << "\n";
        ptr2 = nullptr;
        ptr2 = PtrShared<base>(new base(88));
        std::cout << ptr1;
        std::cout << ptr2 << "\n";

        swap(ptr1, ptr2);

        std::cout << ptr1;
        std::cout << ptr2 << "\n";

        std::cout << (ptr1 == ptr2 ? "equal" : "different") << "\n";
        std::cout << (ptr1 != ptr2 ? "different" : "equal") << "\n";

        std::cout << "\nScope 2 end ->\n\n";
    }


}
#endif // PTRSHARED_H
