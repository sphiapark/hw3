
#ifndef HEAP_H
#define HEAP_H

#include <functional>
#include <stdexcept>
#include <vector>
#include <algorithm>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
    Heap(int m = 2, PComparator c = PComparator());
    ~Heap();

    void push(const T& item);
    const T& top() const;
    void pop();
    bool empty() const;
    size_t size() const;

private:
    std::vector<T> data_;
    int m_;
    PComparator comp_;
};

// Constructor
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c)
    : m_(m), comp_(c)
{
    if (m < 2) {
        throw std::invalid_argument("m must be at least 2");
    }
}

// Destructor
template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap()
{
}

// Check if empty
template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const
{
    return data_.empty();
}

// Return size
template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const
{
    return data_.size();
}

// Return highest priority item
template <typename T, typename PComparator>
const T& Heap<T, PComparator>::top() const
{
    if (empty()) {
        throw std::underflow_error("Heap is empty");
    }

    return data_[0];
}

// Add an item
template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item)
{
    data_.push_back(item);

    size_t index = data_.size() - 1;

    while (index > 0) {
        size_t parent = (index - 1) / m_;

        if (!comp_(data_[index], data_[parent])) {
            break;
        }

        std::swap(data_[index], data_[parent]);
        index = parent;
    }
}

// Remove highest priority item
template <typename T, typename PComparator>
void Heap<T, PComparator>::pop()
{
    if (empty()) {
        throw std::underflow_error("Heap is empty");
    }

    data_[0] = data_.back();
    data_.pop_back();

    size_t index = 0;

    while (index < data_.size()) {
        size_t best = index;

        for (int i = 1; i <= m_; i++) {
            size_t child = index * m_ + i;

            if (child < data_.size() &&
                comp_(data_[child], data_[best])) {
                best = child;
            }
        }

        if (best == index) {
            break;
        }

        std::swap(data_[index], data_[best]);
        index = best;
    }
}

#endif
