#ifndef LIST_H
#define LIST_H

#include "Iterator.h"

template <class T>
class List : public Iterable<T>
{
public:
    // pre:
    // post: the element is inserted at the end of the list
    virtual void insert(T element) = 0;

    // pre: the index is valid (0 <= index < size)
    // post: the element is inserted at the given index
    virtual void insertAt(int index, T element) = 0;

    // pre: -
    // post: remove the first element that is equal to the given element
    virtual bool remove(T element) = 0;

    // pre: the index is valid (0 <= index < size)
    // post: the element is removed at the given index
    virtual void removeAt(int index) = 0;

    // pre: -
    // post: returns if the list is empty
    virtual bool isEmpty() = 0;

    // pre: the index is valid (0 <= index < size)
    // post: returns the element at the given index
    virtual T get(int index) = 0;

    // pre: -
    // post: returns the size of the list
    virtual int getSize() = 0;

    // EXTENSION
    // pre: -
    // post: returns the first element that is equal to the given element
    virtual T getElement(T element) = 0;

    // EXTENSION
    // pre: -
    // post: returns whether an element exists that equals the given element
    virtual bool contains(T element) = 0;

    virtual void insertAll(Iterator<T>* iter) = 0;
};

#endif