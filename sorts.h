// sorts.h
// Andrea Medina Rico
// 07.09.23

#ifndef SORTS_H_
#define SORTS_H_

#include <vector>
 
template <class T>
class Sorts {
    private:
        void swap(std::vector<T> &, int, int);
        // Merge 
        void copiaArray(std::vector<T> &, std::vector<T> &, int, int);
        void mergeArray(std::vector<T> &, std::vector<T> &, int, int, int);
        void mergeSplit(std::vector<T> &, std::vector<T> &, int, int);

    public:
        void ordenaSeleccion(std::vector<T> &);
        void ordenaBurbuja(std::vector<T> &);
        void ordenaMerge(std::vector<T> &);
        // Regresa un índice
        int busqSecuencial(const std::vector<T> &, int);
        int busqBinaria(const std::vector<T> &, int);
};

//     ** PRIVATE **
template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
    T aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

// Copiar datos YA ORDENADOS
template <class T> 
void Sorts<T>::copiaArray(std::vector<T> &A, std::vector<T> &B, int low, int high) {
    for (int i = low; i <= high; i++) {
        A[i] = B[i];
    }
}

// Une dos arreglos a uno ORDENADOS de menor a mayor
template <class T> 
void Sorts<T>::mergeArray(std::vector<T> &A, std::vector<T> &B, int low, int mid, int high) {
    int i = low;
    int j = mid + 1;
    int k = low;

    // Compara mitades de A y las ordena en B
    // Mientras no haya llegado a un límite
    while (i <= mid && j <= high) {     
        if (A[i] < A[j]) {
            B[k] = A[i];
            i++;
        } else {
            B[k] = A[j];
            j++;
        }
        k++;
    }
    // Si llega un límite, agregar los que faltan de la otra mitad
    if (i > mid) {
        for (j; j <= high; j++) {
            B[k++] = A[j];
        }
    } else {
        for (i; i <= mid; i++) {
            B[k++] = A[i];
        }
    }
}

// Divide en mitades, usa mergeArray para ordenar y copia A en B
template <class T>
void Sorts<T>::mergeSplit(std::vector<T> &A, std::vector<T> &B, int low, int high) {
    int mid;

    // Condición de paro
    if ( (high - low) < 1) {
        return;
    }
    mid = (high + low) / 2;
    mergeSplit(A, B, low, mid);
    mergeSplit(A, B, mid + 1, high);
    mergeArray(A, B, low, mid, high);
    copiaArray(A, B, low, high);
}

//    ** PUBLIC **

// Busca elemento más pequeño y lo lleva al inicio
template <class T>
void Sorts<T>::ordenaSeleccion(std::vector<T> &base) {
    
    int pos;

	for (int i = base.size() - 1; i > 0; i--) {
		pos = 0;
		for (int j = 1; j <= i; j++) {
			if (base[j] > base[pos]) {
				pos = j;
			}
		}

		if (pos != i) {
			swap(base, i, pos);
		}
	}
}

// Por cada elemento, recorre cada lugar comparándolo con el siguiente
// Arrastra el más grande al final, se repite pero no se considera el útimo
template <class T>
void Sorts<T>::ordenaBurbuja(std::vector<T> &base) {

    for (int i = base.size() - 1; i > 0; i--) {

        for (int j = 0; j < i; j++) {
            if (base[j] > base[j + 1]) {
                swap(base, j, j + 1);
            }
        }

    }
}

template <class T>
void Sorts<T>::ordenaMerge(std::vector<T> &base) {
    std::vector<T> temp(base.size());

    mergeSplit(base, temp, 0, base.size() - 1);
}

template <class T>
int Sorts<T>::busqSecuencial(const std::vector<T> & base, int val) {
    for (int i = 0; i < base.size(); i++) {
        if (base[i] == val) {
            return i;
        }
    }
    // No se encontró
    return -1;
}

template <class T>
int Sorts<T>::busqBinaria(const std::vector<T> & base, int val) {
    int mid;
	int low = 0;
	int high = base.size() - 1;

	while (low - high) {
		mid = (low + high) / 2;
		// Condiciones para los tres casos
		if (val == base[mid]) {
			return mid;
		} else if (val < base[mid]) {
			high = mid -1;
		} else if (val > base[mid]) {
			low = mid + 1;
		}
	}

    if (low == val) {
        return low;
    } else {
        return -1;
    }
}

#endif 