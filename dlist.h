/*
* dlist.h
* By: Andrea Medina
* 25.09.23
*/

#ifndef DLIST_H_
#define DLIST_H_

template <class T> class DList;

template <class T>
class DLink {
    private:
        DLink(T);
        DLink(T, DLink<T>*, DLink<T>*);     // constructor with previous and next
        DLink(const DLink<T>&);
        T value;
        DLink<T> *previous;
        DLink<T> *next;

        friend class DList<T>;
};

template <class T>
DLink<T>::DLink(T val): value(val), previous(0), next(0) {};

template <class T>
DLink<T>::DLink(T val, DLink<T> *prev, DLink<T> *nxt): value(val), previous(prev), next(nxt) {};

template <class T>
DLink<T>::DLink(const DLink<T> &source): value(source.val), previous(source.previous), next(source.next) {};


template <class T>
class DList {
    private:
        DLink<T> *head;
        DLink<T> *tail;
        int size;
    
    public:
        DList();
        DList(const DList<T> &);
        ~DList();

        void clear();
        bool empty();
        std::string toStringForward() const;
        std::string toStringBackward() const; 

        void insertion(T);
        int search(int);
        void update(int, T);
        T deleteAt(int);        
};

template <class T>
DList<T>::DList(): head(0), tail(0), size(0) {};

template <class T>
DList<T>::~DList() {
    clear();
}

template <class T> 
void DList<T>::clear() {
    DLink<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	size = 0;
}

template <class T>
bool DList<T>::empty() {
    return (head == 0 || tail == 0);
}

template <class T>
std::string DList<T>::toStringForward() const {
    std::stringstream aux;
    DLink<T> *p;

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
std::string DList<T>::toStringBackward() const {
    std::stringstream aux;
    DLink<T> *p;

    p = tail;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->previous != 0) {
            aux << ", ";
        }
        p = p->previous;
    }
    aux << "]";
    return aux.str();
}

template <class T>
void DList<T>::insertion(T val) {
    DLink<T> *newLink;
    newLink = new DLink<T>(val);

    // Basic error conditions
    if (newLink == 0) {
        std::cout << "Error";
    }
    if (empty()) {
        head = newLink;
        tail = newLink;
    } else {
        tail->next = newLink;
        newLink->previous = tail;
        tail = newLink;
    }   
    size++;
}

template <class T> 
int DList<T>::search(int val) {
    DLink<T> *p, *q;
    int posI = 0;
    int posF = size - 1;

    if (empty()) {
        std::cout << "Error";
        return -1;
    } else {
        p = head;
        q = tail;

        while (p != 0 || q != 0) {
            if (p->value == val) {
                return posI;
            } else if (q->value == val) {
                return posF;
            } else {
                p = p->next;
                q = q->previous;
                posI++;
                posF++;
            }
        }
    }
    return -1;
}

template <class T>
void DList<T>::update(int index, T val) {
    DLink<T> *p;
    int pos;

    // Getting to the position
    if (index <= (size / 2)) {
        p = head;
        pos = 0;
        while( pos != index) {
            p = p->next;
            pos++;
        }
    } else {
        p =  tail;
        pos = size - 1;
        while (pos != index) {
            p = p->previous;
            pos--;
        }
    }

    p->value = val;
}

template <class T>
T DList<T>::deleteAt(int index) {
    T val;
    DLink<T> *p, *q;
    int pos = 0;

    p = head;

    if (empty()) {
        std::cout << "Error";
    }

    //Delete first 
    if (index == 0) {
        head = p->next;
        p->next->previous = 0;
    
    // Delete last
    } else if (index == size - 1) {
        p = tail;
        tail = p->previous;
        p->previous->next = 0;
    
    // Other position
    } else {
        while (pos != index) {
            p = p->next;
            pos++;
        }
        p->previous->next = p->next;
        p->next->previous = p->previous;
    }
    val = p->value;
    delete p;
    size--;
    return val;
}

#endif