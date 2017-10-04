#ifndef HASHMAP_H
#define HASHMAP_H

#include "HashEntry.h"

template<class K, class T>
class HashMap {
private:

    HashEntry<K, T> **tabla;
    unsigned int size;

    static unsigned int hashFunc(K clave);

    unsigned int (*hashFuncP)(K clave);


public:
    HashMap(unsigned int size);

    HashMap(unsigned int size, unsigned int (*hashFuncP)(K clave));

    T get(K clave);

    void put(K clave, T valor);

    void remove(K clave);

    ~HashMap();

    bool esVacio();

};

template<class K, class T>
HashMap<K, T>::HashMap(unsigned int size) {

    tabla = new HashEntry<K, T> *[size];
    this->size = size;
    for(int i = 0; i < size; i++){
        tabla[i] = NULL;
    }
    hashFuncP = hashFunc;

}

template<class K, class T>
HashMap<K, T>::~HashMap() {

    for(int i = 0; i < size; i++){
        if(tabla[i] != NULL)
            delete tabla[i];
    }

}

template<class K, class T>
T HashMap<K, T>::get(K clave) {

    unsigned int pos = hashFuncP(clave) % size;
    if(NULL == tabla[pos])
        throw 2;
    return tabla[pos]->getDato();

}

template<class K, class T>
void HashMap<K, T>::put(K clave, T valor) {

    unsigned int pos = hashFuncP(clave) % size;
    if(tabla[pos] != NULL)
        throw 1;

    tabla[pos] = new HashEntry<K, T>(clave, valor);

}

template<class K, class T>
void HashMap<K, T>::remove(K clave) {

    unsigned int pos = hashFuncP(clave) % size;
    if(tabla[pos] != NULL){
        delete tabla[pos];
        tabla[pos] = NULL;
    }

}

template<class K, class T>
bool HashMap<K, T>::esVacio() {

    for(int i = 0; i < size; i++){
        if(tabla[i] != NULL)
            return false;
    }

    return true;
}

template<class K, class T>
unsigned int HashMap<K, T>::hashFunc(K clave) {

    return (unsigned int) clave;
}

template<class K, class T>
HashMap<K, T>::HashMap(unsigned int size, unsigned int (*fp)(K)) {

    tabla = new HashEntry<K, T>*[size];
    this->size = size;
    for(int i = 0; i < size; i++){
        tabla[i] = NULL;
    }
    this->hashFuncP = fp;

}


#endif //HASHMAP_H