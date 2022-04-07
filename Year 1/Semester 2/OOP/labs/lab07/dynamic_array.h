#pragma once
#include "domain.h"
#include "exceptions.h"
#include <memory>
#include <vector>


#define INITIAL_CAPACITY 2
#define RM 2
#define RC 2
//#define ElemType Activitate

using std::unique_ptr;
using std::vector;

template<typename ElemType>
class DynamicArray
{
private:
    unique_ptr<ElemType[]> Array;
    unsigned int Capacity;
    unsigned int Size;

    /**
    * Function that expands the size of the array if necessary
    *
    * @params: -
    *
    * @return: -
    */
    void holdUp() {
        if (this->Capacity == this->Size) {
            auto newArray = std::make_unique<ElemType[]>(this->Size * RC);
            for (unsigned int i = 0; i < this->Size; ++i) {
                newArray[i] = Array[i];
            }
            Array.swap(newArray);

            this->Capacity = this->Capacity * RC;
        }
    }

    /**
    * Function that compress the size of the array if necessary
    *
    * @params: -
    *
    * @return: -
    */
    void holdDown() {
        if (this->Capacity != INITIAL_CAPACITY && this->Capacity / this->Size >= RM) {
            auto newArray = std::make_unique<ElemType[]>(this->Capacity / RM);
            for (unsigned int i = 0; i < this->Size; ++i) {
                newArray[i] = Array[i];
            }
            Array.swap(newArray);

            this->Capacity = this->Capacity / RM;
        }
    };

public:

    class IteratorDynamicArray {
    private:
        const DynamicArray<ElemType>& cont;
        unsigned int position;

    public:
        explicit IteratorDynamicArray(const DynamicArray<ElemType>& cont) noexcept : cont{ cont }, position{ 0 } {};
        IteratorDynamicArray(const DynamicArray<ElemType>& cont, unsigned int position) noexcept : cont{ cont }, position{ position } {};

        IteratorDynamicArray(const IteratorDynamicArray& ot) noexcept : cont{ ot.cont }{};

        /**
        * Function that checks if the iterator is valid
        *
        * @params: -
        *
        * @return: true if the iterator is valid and false otherwise
        */
        bool valid() const noexcept {
            return (this->position < cont.Size);
        }

        /**
        * Funcion that returns the current element in iteration
        *
        * @preconditions: the iterator needs to valid
        *
        * @params: -
        *
        * @return: a reference to the current element
        *
        * @exceptions: OutOfRangeException with text "Iterator out of range!\n" if the iterator is not valid
        */
        ElemType& element() const {
            if (!valid()) {
                throw OutOfRangeException("Iterator out of range!\n");
            }

            return cont.Array[position];
        }

        /**
        * Function that moves the iterator
        *
        * @preconditions: the iterator needs to valid
        *
        * @params: -
        *
        * @return: -
        *
        * @exceptions: OutOfRangeException with text "Iterator out of range!\n" if the iterator is not valid
        */
        void next() {
            if (!valid()) {
                throw OutOfRangeException("Iterator out of range!\n");
            }

            position = position + 1;
        }

        /**
        * Funcion that returns the current element in iteration
        *
        * @preconditions: the iterator needs to valid
        *
        * @params: -
        *
        * @return: a reference to the current element
        *
        * @exceptions: OutOfRangeException with text "Iterator out of range!\n" if the iterator is not valid
        */
        ElemType& operator*() {
            return element();
        }

        /**
        * Function that moves the iterator
        *
        * @preconditions: the iterator needs to valid
        *
        * @params: -
        *
        * @return: a reference to an iterator
        *
        * @exceptions: OutOfRangeException with text "Iterator out of range!\n" if the iterator is not valid
        */
        IteratorDynamicArray& operator++() {
            next();
            return *this;
        }

        /**
        * Function checks if the iterators refers the same element
        *
        * @params: a reference to an another iterator
        *
        * @return: true if the iterators refers the same element and false otherwise
        */
        bool operator==(const IteratorDynamicArray& ot) const noexcept {
            return this->position == ot.position;
        }

        /**
        * Function checks if the iterators does not refer the same element
        *
        * @params: a reference to an another iterator
        *
        * @return: true if the iterators does not refer the same element and false otherwise
        */
        bool operator!=(const IteratorDynamicArray& ot) const noexcept {
            return this->position != ot.position;
        }
    };

    DynamicArray() noexcept : Size{ 0 }, Capacity{ INITIAL_CAPACITY }, Array{ std::make_unique<ElemType[]>(INITIAL_CAPACITY) }{
    };

    DynamicArray(const DynamicArray& ot) : Array{ std::make_unique<ElemType[]>(INITIAL_CAPACITY) }, Size{ 0 }, Capacity{ INITIAL_CAPACITY }{
        for (const auto& elem : ot) {
            (*this).push_back(elem);
        }
    }

    /**
    * Function that appends to the end of the array the given element
    *
    * @params: T - ElemType object
    *
    * @return: -
    */
    void push_back(const ElemType& T) {
        this->holdUp();
        this->Array[this->Size] = T;
        this->Size = this->Size + 1;
    }

    /**
    * Function that erases the element from the given position
    *
    * @params: position - integer
    *
    * @return: -
    *
    * @exceptions: OutOfRangeException with text "Index out of range!\n" if the given position is not a valid one
    */
    void erase(unsigned int position) {
        if (position >= this->Size) {
            throw OutOfRangeException("Index out of range!\n");
        }

        for (unsigned int i = position; i < Size - 1; ++i) {
            Array[i] = Array[i + 1];
        }
        Size = Size - 1;

        this->holdDown();
    }

    /**
    * Function the returns the number of elements in the array
    *
    * @params: -
    *
    * @return: integer
    */
    unsigned int const size() const noexcept {
        return this->Size;
    }

    /**
    * Function that clears the array
    *
    * @params: -
    *
    * @return: -
    */
    void clear() {
        auto newArray = std::make_unique<ElemType[]>(2);

        Array.swap(newArray);
        this->Size = 0;
        this->Capacity = INITIAL_CAPACITY;
    }

    /**
    * Function that returns the element on the given position
    *
    * @params: position - integer
    *
    * @return: a reference to an element
    *
    * @exceptions: OutOfRangeException with text "Index out of range!\n" if the position is outsite of the range of the array
    */
    ElemType& at(unsigned int position) const {
        if (position >= this->Size) {
            throw OutOfRangeException("Index out of range!\n");
        }

        return this->Array[position];
    }

    const DynamicArray& operator=(const DynamicArray& ot) {
        (*this).clear();
        for (const auto& elem : ot) {
            (*this).push_back(elem);
        }

        return (*this);
    }


    /**
    * Function that returns an iterator on the array that reference the fist item
    *
    * @params: -
    *
    * @return: an iterator on the array
    */
    IteratorDynamicArray begin() const noexcept {
        return IteratorDynamicArray(*this);
    }

    /**
    * Function that returns an iterator on the array that reference the last item
    *
    * @params: -
    *
    * @return: an iterator on the array
    */
    IteratorDynamicArray end() const noexcept {
        return IteratorDynamicArray(*this, Size);
    }


    /**
    * Function that converts an DynamicArray to a vector
    *
    * @params: -
    *
    * @return: a vector that contains the same objects as the array
    */
    vector<ElemType> toStdVector() const {
        vector<ElemType> result;

        for (const auto& elem : *this) {
            result.push_back(elem);
        }

        return result;
    }

    ~DynamicArray() = default;
};
