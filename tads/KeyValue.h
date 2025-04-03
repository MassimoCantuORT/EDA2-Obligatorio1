#ifndef KV_H
#define KV_H

template <class K, class V>
struct KeyValue {
    K key;
    V value;
    
    KeyValue(K k, V v) : key(k), value(v) {}
    //Usar este constructor solo para comparaciones
    KeyValue(K k) : key(k) {}

    void setValue(K newValue) { this->value = newValue; }

    bool operator==(KeyValue other) { return this->key == other.key; }
    bool operator==(K otherK) { return this->key == otherK; }
};

#endif