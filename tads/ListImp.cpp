#ifndef LIST_IMP
#define LIST_IMP

#include "List.h"
#include <cassert>
#include <iostream>

template <class T>
class ListImp : public List<T>
{
private:
    // define a inner class (Node) to be used by the double linked list
    class Node
    {
    public:
        T element;
        Node *next;
        Node *previous;
        Node(T element, Node *next, Node *previous) : element(element), next(next), previous(previous) {}
    };

    Node *head;
    Node *tail;
    int size;

public:
    ListImp() : head(nullptr), size(0) {}

    void insert(T element)
    {
        Node *newNode = new Node(element, nullptr, this->tail);
        if (isEmpty())
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void insertAt(int index, T element)
    {
        assert(index >= 0 && index < size);
        Node *newNode = new Node(element, nullptr, nullptr);
        if (index == 0)
        {
            newNode->next = head;
            head->previous = newNode;
            head = newNode;
        }
        else if (index == size)
        {
            tail->next = newNode;
            newNode->previous = tail;
            tail = newNode;
        }
        else
        {
            Node *current = head;
            for (int i = 0; i < index; i++)
            {
                current = current->next;
            }
            newNode->next = current;
            newNode->previous = current->previous;
            current->previous->next = newNode;
            current->previous = newNode;
        }
        size++;
    }

    bool remove(T element)
    {
        Node *current = head;
        while (current != nullptr)
        {
            // note: that the elment should implement == operator
            if (current->element == element)
            {
                if (current == head)
                {
                    head = current->next;
                    if (head != nullptr)
                    {
                        head->previous = nullptr;
                    }
                }
                else if (current == tail)
                {
                    tail = current->previous;
                    if (tail != nullptr)
                    {
                        tail->next = nullptr;
                    }
                }
                else
                {
                    current->previous->next = current->next;
                    current->next->previous = current->previous;
                }
                delete current;
                size--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void removeAt(int index)
    {
        assert(index >= 0 && index < size);
        Node *current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        if (current == head)
        {
            head = current->next;
            if (head != nullptr)
            {
                head->previous = nullptr;
            }
        }
        else if (current == tail)
        {
            tail = current->previous;
            if (tail != nullptr)
            {
                tail->next = nullptr;
            }
        }
        else
        {
            current->previous->next = current->next;
            current->next->previous = current->previous;
        }
        delete current;
        size--;
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    T get(int index)
    {
        assert(index >= 0 && index < size);
        Node *current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->element;
    }

    T getElement(T element)
    {
        Node *current = head;
        while (current != nullptr)
        {
            // note: that the elment should implement == operator
            if (current->element == element)
            {
                return current->element;
            }
            current = current->next;
        }
        assert(false); //element did not exist
    }

    bool contains(T element)
    {
        Node *current = head;
        while (current != nullptr)
        {
            
            // note: that the elment should implement == operator
            if (current->element == element)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int getSize()
    {
        return size;
    }
};

#endif