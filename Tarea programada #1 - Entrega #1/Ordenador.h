#ifndef Ordenador_h
#define Ordenador_h
#include <algorithm>

class Ordenador{
	private:
    // Defina aqui los metodos auxiliares de los algoritmos de ordenamiento solamente.
    // Puede definir cuantos metodos quiera.
	
	public:
	Ordenador(){};
	~Ordenador(){};
	// Si piensa no implementar algunos de los metodos de ordenamiento, no los borre,
	// simplemente dejelos con el cuerpo vacio para evitar errores de compilacion, ya
	// que se va a ejecutar el mismo main para todas las tareas.
    // Implemente los algoritmos en este archivo  (no en un CPP aparte).
	void seleccion(int *A, int n);
	void insercion(int *A, int n);
	void mergesort(int *A, int n);
	void heapsort(int *A, int n);
	void quicksort(int *A, int n);
	void radixsort(int *A, int n);
};
#endif

void Ordenador::insercion(int *A, int n) {
	int key;
    int i;
    for (int j = 1; j < n; j++) {
        key = A[j];
        i = j - 1;
        while (i >= 0 && A[i] > key) {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = key;
    }
}

// INSERTION-SORT(A)
// 1 for j = 2 to A.length
// 2   key = A[j]
// 3   // Insert A[j] into the sorted sequence A[1..j - 1].
// 4   i = j - 1
// 5   while i > 0 and A[i] > key
// 6       A[i + 1] = A[i]
// 7       i = i - 1
// 8   A[i + 1] = key



void Ordenador::seleccion(int *A, int n) { 
	int m;
	for (int i = 0; i < n - 1; i++){
		m = i;
		for (int j = i + 1 ; j < n; j++){
			if (A[j] < A[m]) {
				m=j;
			}
		}
		std::swap(A[i], A[m]);
	}
}

// SELECTION-SORT(A, n)
// 1 for i = 1 to n - 1
// 2     // Select smallest in A[i..n] and swap it with A[i]
// 3     m = i
// 4     for j = i + 1 to n
// 5         if A[j] < A[m]
// 6             m = j
// 7     swap(A[i], A[m])

// Metodos 
// MERGE(A, p, q, r)

// 1   n1 = q - p + 1
// 2   n2 = r - q
// 3   let L[1..n1 + 1] and R[1..n2 + 1] be new arrays
// 4   for i = 1 to n1
// 5       L[i] = A[p + i - 1]
// 6   for j = 1 to n2
// 7       R[j] = A[q + j]
// 8   L[n1 + 1] = ∞
// 9   R[n2 + 1] = ∞
// 10  i = 1
// 11  j = 1
// 12  for k = p to r
// 13      if L[i] ≤ R[j]
// 14          A[k] = L[i]
// 15          i = i + 1
// 16      else A[k] = R[j]
// 17          j = j + 1


// MERGE-SORT(A, p, r)

// 1 if p < r
// 2   q = [(p + r) / 2]
// 3   MERGE-SORT(A, p, q)
// 4   MERGE-SORT(A, q + 1, r)
// 5   MERGE(A, p, q, r)


