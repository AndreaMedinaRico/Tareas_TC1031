/*
 * hash.h
 *
 *  Created on: 20/10/2015
 *      Author: clase
 */

#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <string>
#include <sstream>

using namespace std;

template <class Key, class Value>
class Quadratic {
private:
	unsigned int (*func) (const Key);
	unsigned int size;
	unsigned int count;

	Key *keys;
	Key initialValue;
	Value *values;

	long indexOf(const Key) const;

public:
	Quadratic(unsigned int, Key, unsigned int (*f) (const Key)) ;
	~Quadratic();
	bool full() const;
	void put(Key, Value);
	bool contains(const Key) const;
	Value get(const Key) ;
	void clear();
	std::string toString() const;
};

template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key))  {
	size = sze;

	// VALUES and KEYS are both tables --> need to have SAME SIZE
	values = new Value[size];
	if (values == 0)
		cout << "OutOfMemory";

	keys = new Key[size];
	if (keys == 0)
		cout << "OutOfMemory";

	initialValue = init;        // Initial value is the given key
	// Initialize every element
	for (unsigned int i = 0; i < size; i++)
		keys[i] = init;
	
	for (int i = 0; i < size; i++)
		values[i] = 0;
	
	func = f;
	count = 0;
}

template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
	// delete things with NEW
	delete [] values;
	values = 0;
	delete [] keys;
	keys = 0;
	size = 0;
	count = 0;
	func = 0;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
	return (count > size);
}

// Function takes KEY calculated by HASH FUNCTION and gives it an INDEX
// Calculates index WITH module between the given number from HASH and SIZE
template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
	unsigned int i, start, j;		// i   in case it needs to move from index
    j = 1;
	start = i = func(k) % size;		// start and i BEING in the same 
	 
	do {					// Do while because code need to run AT LEAST ONCE
		if (keys[i] == k) {
            return i;
        }
		i = (i + (j * j)) % size;
        j++;
	} while (start != i);

	return -1;	// Error
}

template <class Key, class Value>
void Quadratic<Key, Value>::put(Key k, Value v) {
	unsigned int i, start, j;
	long pos;
    j = 1;

	if (full())
		cout << "Overflow";
	
	pos = indexOf(k);
	if (pos != -1) {
		values[pos] = v;
        return;
	}

	start = i = func(k) % size;
	do {
		if (keys[i] == initialValue) {
			keys[i] = k;
			values[i] = v;
			count++;
            return;
		}
		i = (i + (j * j) ) % size;
        j++;
        // While condition for quadratic probing
	} while(start != i);
    return;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::contains(const Key k) const {
	long pos;

    pos = indexOf(k);
    return (pos != -1);
}

template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k)  {
	long pos;
    pos = indexOf(k);

    if (pos == -1)
        cout << "Not found";
    return values[pos];
}

template <class Key, class Value>
void Quadratic<Key, Value>::clear() {
    for (unsigned int i = 0; i < size; i++)
        keys[i] = initialValue;
    count = 0;
}

// impresion clase quadratic
template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
	std::stringstream aux;
	for (int i = 0; i < size; i++){
			if (keys[i] != initialValue){
				aux << "(" << i << " ";
			  aux << keys[i] << " : " << values[i] << ") ";
			}
	}
	return aux.str();
}
#endif 
