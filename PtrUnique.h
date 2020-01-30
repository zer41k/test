#ifndef PTRUNIQUE_H
#define PTRUNIQUE_H

#include "TestClass.h"
#include <algorithm>
#include <iostream>

template<class T>
class PtrUnique
{
public:
    PtrUnique();
    explicit PtrUnique(T*);
    PtrUnique(const PtrUnique&) = delete;
    PtrUnique(PtrUnique&&) noexcept;
    template<class U> PtrUnique(PtrUnique<U>&&) noexcept;

    PtrUnique& operator=(const PtrUnique&) = delete;
    template<class U> PtrUnique& operator=(PtrUnique<U>&&) noexcept;
    PtrUnique& operator=(PtrUnique&&) noexcept;


    ~PtrUnique();

    T* operator->() const;
    T& operator*() const;
    T* Get() const;

    T* Release();
    void Reset();

    void Swap(PtrUnique&) noexcept;
    explicit operator bool() const;

private:
    T* data_;
};


template <class T>
void swap(PtrUnique<T>& lhs, PtrUnique<T>& rhs) noexcept
{
    lhs.Swap(rhs);
}


template <class T>
bool operator==(const PtrUnique<T>& lhs, const PtrUnique<T>& rhs)
{
    return lhs.Get() == rhs.Get();
}


template <class T>
bool operator!=(const PtrUnique<T>& lhs, const PtrUnique<T>& rhs)
{
    return !(lhs.Get() == rhs.Get());
}


template<class T>
std::ostream& operator<<(std::ostream& ostream, const PtrUnique<T>& rhs)
{
    return ostream << rhs.Get();
}



template<class T>
PtrUnique<T>::PtrUnique() :
    data_(nullptr)
{
}



template<class T>
PtrUnique<T>::PtrUnique(T* in) :
    data_(in)
{
}


template<class T>
PtrUnique<T>::PtrUnique(PtrUnique<T>&& in) noexcept :
     data_(nullptr)
{
    in.Swap(*this);
}



template<class T>
template<class U>
PtrUnique<T>::PtrUnique(PtrUnique<U>&& in) noexcept :
    data_(nullptr)

{
    PtrUnique<T> temp(in.Release());
    temp.Swap(*this);
}



template<class T>
PtrUnique<T>& PtrUnique<T>::operator=(PtrUnique<T>&& in) noexcept
{
    in.Swap(*this);
    return *this;
}



template<class T>
template<class U>
PtrUnique<T>& PtrUnique<T>::operator=(PtrUnique<U>&& in) noexcept
{
    PtrUnique<T> temp(in.Release());
    temp.Swap(*this);
    return *this;
}



template<class T>
PtrUnique<T>::~PtrUnique<T>()
{
    delete data_;
}



template<class T>
T* PtrUnique<T>::operator->() const
{
    return this->data_;
}



template<class T>
T& PtrUnique<T>::operator*() const
{
    return *this->data_;
}



template<class T>
T* PtrUnique<T>::Get() const
{
    return data_;
}



template<class T>
T* PtrUnique<T>::Release()
{
    T* temp = this->data_;
    this->data_ = nullptr;
    return temp;
}



template<class T>
void PtrUnique<T>::Reset()
{
    T* temp = Release();
    delete temp;
}



template<class T>
void PtrUnique<T>::Swap(PtrUnique<T>& in) noexcept
{
    std::swap(this->data_, in.data_);
}



template<class T>
PtrUnique<T>::operator bool() const
{
    return data_;
}









PtrUnique<derived> GetUniqueDerived()
{
    return PtrUnique<derived>(new derived(13));
}

void TestPtrUnique()
{
    std::cout << "Unique pointer\n\n";
    {
        std::cout << "\nScope 1 start ->\n\n";
        PtrUnique<base> ptr22(new derived(22));
        ptr22->virtualPrint();
        (*ptr22).virtualPrint();
        ptr22.Get()->virtualPrint();
        std::cout << "\nScope 1 end ->\n\n";
    }

    {
        std::cout << "\n\nScope 2 start ->\n\n";
        PtrUnique<base> ptr33(new base(33));
        PtrUnique<base> ptr44(new base(44));
        swap(ptr33, ptr44);

        std::cout << (ptr33 == ptr44 ? "equal" : "different") << "\n";
        std::cout << (ptr33 != ptr44 ? "different" : "equal") << "\n";
        std::cout << "\nScope 2 end ->\n\n";
    }

    {
        std::cout << "\n\nScope 3 start ->\n\n";
        PtrUnique<base> ptr55(GetUniqueDerived());
        std::cout << ptr55 << "\n";
        ptr55.Reset();
        std::cout << ptr55 << "\n";
        std::cout << "\nScope 3 end ->\n\n";
    }
}



#endif // PTRUNIQUE_H


