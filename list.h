/*
* list.h
* By: Andrea Medina Rico
* 21.09.23
*/

#ifndef LIST_H_
#define LIST_H_

#include <string>
#include <sstream>

template <class T> class List;

template <class T>
class Link {
    private:
	Link(T);
	// Apuntador para decirle a dónde apuntaría el siguiente
	Link(T, Link<T>*);
	// Copy constructor
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;	// Pointer to next element

	// Both classes need to access to private members
	friend class List<T>;
};

template <class T>
Link<T>::Link(T val): value(val), next(0) {};

template <class T>
Link<T>::Link(T val, Link* nxt): value(val), next(nxt) {};

template <class T> 
Link<T>::Link(const Link<T> &source): value(source.value), next(source.next) {};


template <class T>
class List {
    public:
        // List ALWAYS needs to be created EMPTY
	    List();

        std::string toString() const;
        void insertion(T);
        int search(int);
        void update(int, T);
        T deleteAt(int);
		bool empty();

	private:
		Link<T> *head;
		int size;
};

template <class T>
List<T>::List(): head(0) {};

template <class T>
bool List<T>::empty() {
	return(head ==0 );
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}


template <class T> 
void List<T>::insertion(T val) {
	//Método de insertar
	Link<T> *newLink, *p;

	newLink = new Link<T>(val); 
	if (newLink == 0) {
		std::cout << "Error";
	} 

	if (empty()) {
		newLink->next = head;
		head = newLink;
		size++;
		return;
	}

	p = head;
	while (p->next != 0) {
		p = p->next;
	}
	newLink->next = 0;
	p->next = newLink;
	size++;
}


template<class T>
int List<T>::search(int val) {
	Link<T> *p;
	int pos = 0;

	p = head;
	while (p != 0) {
		if (p->value == val) {
			return pos;
		} else {
			p = p->next;
			pos++;
		}
	}

	return -1;
}

template <class T>
void List<T>::update(int pos, T val) {
	Link<T> *p;
	int i = 0;

	p = head;
	while (i != pos) {
		p = p->next;
		i++;
	}
	
	p->value = val;
}

template <class T>
T List<T>::deleteAt(int pos) {
	T val;
	Link<T> *p, *q;
	int i = 0;

	p = head;
	
	// Delete first
	if (pos == 0) {
		head = p->next;
		val = p->value;
		delete p;
		size--;
		return val;
	}

	while (i != pos) {
		q = p;
		p = p->next;
		i++;
	}

	q->next = p->next;	// Save next link to preserve the list
	val = p->value;	// Save value to return
	delete p;	
	size--;	

	return val;
}

#endif