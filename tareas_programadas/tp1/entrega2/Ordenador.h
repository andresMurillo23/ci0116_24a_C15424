#ifndef Ordenador_h
#define Ordenador_h
#include <string>
#include <algorithm>
#include <cmath>

class Ordenador{
	private:
  // Defina aqui los metodos auxiliares de los algoritmos de ordenamiento solamente.
  // Puede definir cuantos metodos quiera.
	void merge(int *A, int p, int q, int r);
  void mergeSortAux(int *A, int p, int r);


  void maxHeapify(int *A, int i, int n);
  void buildMaxHeap(int *A, int n);

  void quickSortAux(int *A, int p, int r);
  int partition(int *A, int p, int r);
  void countSort(int *A, int n, int exp, int base);
  void radixSortAux(int *A, int n);

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
  std::string ImprimirDatosDeTarea() const;
};
#endif

std::string Ordenador::ImprimirDatosDeTarea() const {
  // Retorna una cadena con los detalles de la tarea.
  return "c15424 Tarea 1 Etapa 2.";
}

void Ordenador::insercion(int *A, int n) {
  // Algoritmo de inserción: Ordena los elementos uno por uno.
  // key: elemento actual a ser insertado en la parte ordenada del arreglo.
  int key;
  int i;
  for (int j = 1; j < n; j++) {
    key = A[j];
    i = j - 1;
    // Mueve los elementos de A[0..i-1], que son mayores que key,
    // a una posición adelante de su posición actual.
    while (i >= 0 && A[i] > key) {
      A[i + 1] = A[i];
      i = i - 1;
    }
    A[i + 1] = key;
  }
}

void Ordenador::seleccion(int *A, int n) {
  // Algoritmo de selección: Encuentra el mínimo y lo coloca al principio.
  int m;
  for (int i = 0; i < n - 1; i++){
    m = i;
    for (int j = i + 1 ; j < n; j++){
      if (A[j] < A[m]) {
        m=j;
      }
    }
    std::swap(A[i], A[m]); // Intercambia el mínimo con el primer elemento.
  }
}

void Ordenador::merge(int *A, int p, int q, int r) {
  // Crea arrays temporales L[] y R[] para almacenar las mitades.
  int n1 = q - p + 1;
  int n2 = r - q;
  int L[n1], R[n2];

  for (int i = 0; i < n1; i++)
    L[i] = A[p + i];
  for (int j = 0; j < n2; j++)
    R[j] = A[q + 1 + j];

  // Fusiona los arrays temporales de nuevo en A[p..r].
  int i = 0, j = 0, k = p;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      A[k++] = L[i++];
    } else {
      A[k++] = R[j++];
    }
  }

  // Copia los elementos restantes de L[], si hay alguno.
  while (i < n1) {
    A[k++] = L[i++];
  }

  // Copia los elementos restantes de R[], si hay alguno.
  while (j < n2) {
    A[k++] = R[j++];
  }
}

void Ordenador::mergeSortAux(int *A, int p, int r) {
  if (p < r) {
    // Encuentra el punto medio para dividir el arreglo en dos mitades.
    int q = (p + r) / 2;
    // Llama a mergeSortAux para las primeras y segundas mitades.
    mergeSortAux(A, p, q);
    mergeSortAux(A, q + 1, r);
    // Combina las mitades ordenadas.
    merge(A, p, q, r);
  }
}

void Ordenador::mergesort(int *A, int n) {
  // Función pública que inicia el proceso de ordenamiento por mezcla.
  mergeSortAux(A, 0, n - 1);
}

void Ordenador::maxHeapify(int *A, int i, int n) {
  int largest = i;  // Inicia con la raíz actual como el mayor
  int l = 2 * i + 1;  // Índice del hijo izquierdo
  int r = 2 * i + 2;  // Índice del hijo derecho

  // Si el hijo izquierdo es mayor que la raíz
  if (l < n && A[l] > A[largest]) {
    largest = l;
  }

  // Si el hijo derecho es mayor que el mayor hasta ahora
  if (r < n && A[r] > A[largest]) {
    largest = r;
  }

  // Si el mayor no es la raíz, intercambia y continua heapifying
  if (largest != i) {
    std::swap(A[i], A[largest]);
    maxHeapify(A, largest, n);  // Recursivamente asegura la propiedad de max-heap
  }
}

void Ordenador::buildMaxHeap(int *A, int n) {
  int startIdx = (n / 2) - 1;  // Último índice no hoja

  // Construye el heap desde el último nodo no hoja
  for (int i = startIdx; i >= 0; i--) {
    maxHeapify(A, i, n);
  }
}

void Ordenador::heapsort(int *A, int n) {
  buildMaxHeap(A, n);  // Primero construye un max-heap
  // Uno por uno extrae elementos del heap
  for (int i = n - 1; i >= 0; i--) {
    std::swap(A[0], A[i]);   // Mueve la raíz actual al final
    maxHeapify(A, 0, i);   // Reduce el heap y vuelve a heapify
  }
}

void Ordenador::quickSortAux(int *A, int p, int r) {
  if (p < r) {
    int q = partition(A, p, r);   // Particiona y encuentra el índice del pivote
    quickSortAux(A, p, q - 1);   // Ordena la sublista izquierda
    quickSortAux(A, q + 1, r);   // Ordena la sublista derecha
  }
}

int Ordenador::partition(int *A, int p, int r) {
  int x = A[r];  // Elige el último elemento como pivote
  int i = p - 1;  // Indica la posición del último elemento menor que el pivote

  // Reordena los elementos alrededor del pivote
  for (int j = p; j < r; j++) {
    if (A[j] <= x) {
      i++;
      std::swap(A[i], A[j]);
    }
  }
  std::swap(A[i + 1], A[r]);  // Coloca el pivote en la posición correcta
  return i + 1;
}

void Ordenador::quicksort(int *A, int n) {
  quickSortAux(A, 0, n - 1);  // Inicia el quicksort desde el primer hasta el último elemento
}

// Método para realizar Counting Sort como parte del Radix Sort
void Ordenador::countSort(int *A, int n, int exp, int base) {
  std::vector<int> output(n);  // Vector de salida ordenada
  std::vector<int> count(base, 0);  // Vector de conteo

  // Cuenta las ocurrencias de cada dígito
  for (int i = 0; i < n; i++) {
    int index = (A[i] / exp) % base;
    count[index]++;
  }

  // Acumula los conteos para obtener las posiciones finales
  for (int i = 1; i < base; i++) {
    count[i] += count[i - 1];
  }

  // Construye el array de salida
  for (int i = n - 1; i >= 0; i--) {
    int index = (A[i] / exp) % base;
    output[count[index] - 1] = A[i];
    count[index]--;
  }

  // Copia el resultado ordenado de vuelta al array original
  for (int i = 0; i < n; i++) {
    A[i] = output[i];
  }
}

// Método auxiliar para preparar y ejecutar el Radix Sort
void Ordenador::radixSortAux(int *A, int n) {
  int m = *std::max_element(A, A + n);   // Encuentra el elemento máximo
  int base = std::pow(2, std::ceil(std::log2(n)));   // Calcula la base

  // Realiza Counting Sort para cada dígito
  for (int exp = 1; m / exp > 0; exp *= base) {
    countSort(A, n, exp, base);
  }
}

// Método para iniciar el proceso de Radix Sort
void Ordenador::radixsort(int *A, int n) {
  radixSortAux(A, n);   // Llama al método auxiliar
}
