/*
* heap.h
* By: Andrea Medina Rico
* 10.19.23
*/

#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <sstream>

template <class T>
class Heap {
    private:
        T *data;
        unsigned int Size;
        unsigned int count;

        unsigned int parent(unsigned int) const;
	    unsigned int left(unsigned int) const;
	    unsigned int right(unsigned int) const;
        void swap(unsigned int, unsigned int);
	    void heapify(unsigned int);

    public: 
        Heap(unsigned int) ;
	    ~Heap();
        void clear();
	    bool full() const;

        void push(int);
        void pop();
        T top() const;
        bool empty() const;
        unsigned int size() const;

        std::string toString() const;
};

template <class T>
Heap<T>::Heap(unsigned int sze) {
    Size = sze;
	data = new T[Size];
    if (data == 0) {
		std::cout << "Error: OutOfMemory";
	}
	count = 0;
}

template <class T>
Heap<T>::~Heap() {
	clear();
}

template <class T>
void Heap<T>::clear() {
	delete [] data;
	data = 0;
	Size = 0;
	count = 0;
}

template <class T>
bool Heap<T>::full() const {
	return (count == Size);
}

// ***** BASIC *****
template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
    return ((pos - 1)/ 2);
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
    return ((pos * 2) + 1);
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
    return ((pos * 2) + 2);
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
    T aux = data[i];
    data[i]= data[j];
    data[j] = aux;
}

template <class T>
void Heap<T>::heapify(unsigned int pos) {
    unsigned int le = left(pos);    // Temporary left & right 
    unsigned int ri = right(pos);
    unsigned int min = pos;         // Temporaty minimun

    if (le <= count && data[le] < data[min]) {
        min = le;                   // Now left is minimum value
    }
    if (ri <= count && data[ri] < data[min]) {
        min = ri;
    }
    if (min != pos) {					// If MIN is no longer parent
		swap(pos, min);					// Swap positions
		heapify(min);					// Verify again with NEW MIN
	}
}

// ********* HOMEWORK *********
template <class T>
void Heap<T>::push(int val) {
    unsigned int pos;

    if (full()) {
        std::cout << "Error: Overflow";
        
        return;
    }

    // pos = count + 1   ????
    pos = count;        // Position placed where count is
    count++;            // Count increases due to addition

    // Cicle to verify that PARENT is smaller than CHILD 
	while (pos > 0 && val < data[parent(pos)]) {
		data[pos] = data[parent(pos)];			// Move PARENT to CHILD
		pos = parent(pos);						// Addition POS has now the preview parent position
		// NOTE: Val hasn't been added to array
	}
	// Once parent is smaller, add val
	data[pos] = val;
}

template <class T>
void Heap<T>::pop() {
    if (empty()) {
        std::cout << "Error: No such element";
    }
	// --count --> first rest, then we use it
	data[0] = data[--count];	// Last value is now first
	heapify(0);					// Verify FIRST PARENT is smaller than children
}

template <class T>
T Heap<T>::top() const {
    return data[0];
}

template <class T>
bool Heap<T>::empty() const {
	return (count == 0);
}

template <class T>
unsigned int Heap<T>::size() const {
    return count;
}

template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}

#endif 