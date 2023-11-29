class Funciones {
    public:
        Funciones(){};

        int sumaIterativa(int n);
        int sumaRecursiva(int n);
        int sumaDirecta(int n);    
};

int Funciones::sumaIterativa(int n) {
    // Debe ser positivo
    if (n <= 0) {
        return 0;
    }

    int acum = 0;
    for (int i = 1; i <= n; i++) {
        acum += i;
    }
    return acum;
}

int Funciones::sumaRecursiva(int n) {
    if (n <= 0) {
        return 0;
    } else {
        return ( n + sumaRecursiva(n - 1) );
    }
}

// Se usa FÓRMULA MATEMÁTICA existente para evitar los ciclos
int Funciones::sumaDirecta(int n) {
    return ( n * (n + 1) / 2);
}