#ifndef MIN_PRIO_QUEUE
#define MIN_PRIO_QUEUE

#include "KeyValue.h"
#include "PriorityQueue.h"

template <class E, class P>
class MinPriorityQueue : public PriorityQueue<E, P>
{
private:
    KeyValue<E, P>** array;
    int arrSize;
    int count;
    
    bool isAGreaterThanB(int a, int b){
        return this->array[a]->value > this->array[b]->value;
    }

    //Float
    void siftUp(int index){
        if (index == 1) return;
        int parentIndex = index / 2;
        if (isAGreaterThanB(parentIndex, index)){
            swap(index, parentIndex);
            siftUp(parentIndex);
        }
        
    }

    //Sink
    void siftDown(int index){
        int childLeftIndex = index * 2;
        int childRightIndex = index * 2 + 1;

        int minIndex = index;
    
        if (childLeftIndex <= count && isAGreaterThanB(minIndex, childLeftIndex))
            minIndex = childLeftIndex;
        if (childRightIndex <= count && isAGreaterThanB(minIndex, childRightIndex))
            minIndex = childRightIndex;

        if (minIndex != index)
        {
            swap(index, minIndex);
            siftDown(minIndex);
        }
    }

    void swap(int indexFirst, int indexSecond){
        KeyValue<E, P>* aux = this->array[indexFirst];
        this->array[indexFirst] = this->array[indexSecond];
        this->array[indexSecond] = aux;
    }

public:
    MinPriorityQueue (int initialSize){
        this->arrSize = initialSize + 1;
        this->array = new KeyValue<E, P>*[this->arrSize];
    }

    void enqueue (E elem, P prio) override {
        this->count++;
        if (this->count >= this->arrSize) {
            int newSize = arrSize * 2;
            KeyValue<E, P>** newArray = new KeyValue<E,P>*[newSize];
            for (int i=1; i<this->arrSize; i++){
                newArray[i] = array[i];
            }
            this->arrSize = newSize;
            delete[] array;
            this->array = newArray;
        }
        this->array[count] = new KeyValue<E,P>(elem, prio);
        siftUp(count);
    }

    E dequeue() override {
        E top = this->peek();
        swap(1, count);
        count--;
        siftDown(1);
        return top;
    }

    E peek() override {
        assert(this->count > 0);
        return array[1]->key;
    }

    P peekPriority() override {
        assert(this->count > 0);
        return array[1]->value;
    }
    
    int getCount() override {
        return this->count;
    }

    bool isEmpty() override {
        return this->count == 0;
    }

};

#endif