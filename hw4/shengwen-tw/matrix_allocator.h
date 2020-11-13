#include <cinttypes>
#include <limits>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <atomic>

using namespace std;

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

    template<class U>
    bool operator!= (const MatrixDataAllocator<U> &rhs) {
        return false;
    }

    T* allocate(size_t n)
    {
        size_t n_byte = sizeof(T) * n;

        n_allocated += n_byte;

        cout << "[debug] address of allocator = " << this << endl;
        cout << "[debug] allocated bytes = " << n_byte << endl;

        return static_cast<T*>(operator new(n_byte));
    }

    T* allocate(size_t n, const T * hint)
    {

        return allocate(n);
    }

    void deallocate(T* p, size_t n)
    {
        size_t n_byte = sizeof(T) * n;

        n_deallocated += n_byte;

        cout << "[debug] deallocated bytes = " << n_byte << endl;

        operator delete(p);
    }

    size_t max_size() const
    {
        return std::numeric_limits<size_t>::max();
    }

    std::size_t bytes() const {
        return n_allocated - n_deallocated;
    }

    std::size_t allocated() const {
        return n_allocated;
    }

    std::size_t deallocated() const {
        return n_deallocated;
    }

private:
    std::size_t n_allocated = 0;
    std::size_t n_deallocated = 0;
};
