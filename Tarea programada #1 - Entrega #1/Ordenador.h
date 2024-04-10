#ifndef Ordenador_h
#define Ordenador_h
#include <algorithm>

class Ordenador{
	private:
  // Defina aqui los metodos auxiliares de los algoritmos de ordenamiento solamente.
  // Puede definir cuantos metodos quiera.
	void merge(int *A, int p, int q, int r);
  void mergeSortAux(int *A, int p, int r);
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

void Ordenador::merge(int *A, int p, int q, int r) {
  int n1 = q - p + 1;
  int n2 = r - q;
  int L[n1], R[n2];

  for (int i = 0; i < n1; i++)
    L[i] = A[p + i];
  for (int j = 0; j < n2; j++)
    R[j] = A[q + 1 + j];

  int i = 0, j = 0, k = p;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      A[k++] = L[i++];
    } else {
      A[k++] = R[j++];
    }
  }

  while (i < n1) {
    A[k++] = L[i++];
  }

  while (j < n2) {
    A[k++] = R[j++];
  }
}

void Ordenador::mergeSortAux(int *A, int p, int r) {
  if (p < r) {
    int q = (p + r) / 2;
    mergeSortAux(A, p, q);
    mergeSortAux(A, q + 1, r);
    merge(A, p, q, r);
  }
}

void Ordenador::mergesort(int *A, int n) {
    mergeSortAux(A, 0, n - 1);
}

