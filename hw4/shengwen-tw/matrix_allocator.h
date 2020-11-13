#include <cinttypes>
#include <limits>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

template <class T>
class MatrixDataAllocator
{
public:
    using value_type = T;

    template <class U>
    struct rebind
    {
        using other = MatrixDataAllocator<U>;
    };

    MatrixDataAllocator() = default;
    ~MatrixDataAllocator() = default;

    T* allocate(size_t n)
    {
        return static_cast<T*>(operator new(sizeof(T) * n));
    }

    T* allocate(size_t n, const T * hint)
    {

        return allocate(n);
    }

    void deallocate(T* p, size_t n)
    {
        operator delete(p);
    }

    size_t max_size() const
    {
        return std::numeric_limits<size_t>::max();
    }
};
