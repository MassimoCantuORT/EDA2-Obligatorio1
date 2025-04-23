#ifndef PQ_H
#define PQ_H

template <class E, class P>
class PriorityQueue
{
public:
    virtual void enqueue (E elem, P prio) = 0;
    virtual E dequeue() = 0;
    virtual E peek() = 0;
    virtual P peekPriority() = 0;
    virtual int getCount() = 0;
    virtual bool isEmpty() = 0;
};

#endif