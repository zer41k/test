#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <iostream>

class base
{
public:
    explicit base(int in) : data_(in)
    {
        std::cout << data_ << " is Constructed [base]\n";
    }

    virtual void virtualPrint()
    {
        std::cout << "Print base " << data_ << "\n";
    }

    virtual ~base()
    {
        std::cout << data_ << " is Destructed [base]!\n";
    }

    int data_;
};


std::ostream& operator<<(std::ostream& os, const base& in)
{
    return os << in.data_;
}


class derived : public base
{
public:
    explicit derived(int in) : base(in)
    {
        std::cout << in << " is Constructed [derived]\n";
    }

    void virtualPrint() override
    {
        std::cout << "Print derived " << data_ << "\n";
    }

    ~derived() override
    {
        std::cout << data_ << " is Destructed [derived]!\n";
    }
};


#endif // TESTCLASS_H
