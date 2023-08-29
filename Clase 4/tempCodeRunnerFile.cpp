/* Santos Alejandro Arellano Olarte A01643742
17/Ago/2023
 Actividad 1.1 - Funciones Iterativas, Recursivas y su análisis de complejidad.
   Programa CPP individual - Calcular la sumatoria de 1 hasta n utilizando tres funciones.
   
   sumaIterativa(n): Calcula la sumatoria de 1 hasta n mediante un bucle iterativo.
   
   sumaRecursiva(n): Calcula la sumatoria de 1 hasta n utilizando recursión.
   
   sumaDirecta(n): Calcula la sumatoria de 1 hasta n utilizando un método matemático directo.
   
   Documentación y análisis de complejidad:
   - La suma iterativa requiere de un bucle para sumar los números, lo que la hace menos eficiente.
   - Complejidad temporal: O(n) debido al bucle que recorre n veces.
   
   - La suma recursiva es más eficiente que la iterativa, ya que utiliza recursión para sumar los números.
   - Complejidad temporal: O(n) debido a la recursión que realiza n llamadas.
   
   - La suma directa es la más eficiente, ya que calcula la sumatoria de forma matemática.
   - Complejidad temporal: O(1) debido a que la fórmula se evalúa directamente.
*/

#include <iostream>
using namespace std;

// Calcula la sumatoria de 1 hasta n utilizando un bucle iterativo.
int sumaIterativa(int n) { 
    int suma = 0;
    for(int i = 1; i <= n; i++) { //aqui se hace el bucle para sumar los numeros 
        suma += i; //aqui se hace la suma de los numeros 
    }
    return suma;
}

// Calcula la sumatoria de 1 hasta n utilizando recursión.
int sumaRecursiva(int n) {
    if(n == 1) {
        return 1;
    } else {
        return n + sumaRecursiva(n - 1);
    }
}

// Calcula la sumatoria de 1 hasta n utilizando un método  directo.
int sumaDirecta(int n) {
    return (n * (n + 1)) / 2;
}

int main() {
    int n;
    cout << "Dame un número para n: ";
    cin >> n;
    
    // Llamada a la función sumaIterativa y muestra el resultado.
    cout << "La suma iterativa es: " << sumaIterativa(n) << endl;
    
    // Llamada a la función sumaRecursiva y muestra el resultado.
    cout << "La suma recursiva es: " << sumaRecursiva(n) << endl;
    
    // Llamada a la función sumaDirecta y muestra el resultado.
    cout << "La suma directa es: " << sumaDirecta(n) << endl;
    
    return 0;
}
m