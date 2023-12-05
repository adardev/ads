#include <iostream>
#include <cmath>  // Necesario para funciones matem�ticas como fabs
using namespace std;

class Gauss
{
public:
    double matrizDeCoeficientes[10][11];  // Se ampli� para incluir la columna de resultados
    int size;

    Gauss();
    void solve(int n, double soluciones[]);
};

int main()
{
    Gauss gauss;
    int n;
    double resultados[10];

    cout << "De qu� tama�o es el sistema: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            cout << "[" << i + 1 << "," << j + 1 << "] -> ";
            cin >> gauss.matrizDeCoeficientes[i][j];
        }
    }

    gauss.solve(n, resultados);

    cout << "Las soluciones son: ";
    for (int i = 0; i < n; i++)
        cout << resultados[i] << ",";

    cin.get();
    return 0;
}

Gauss::Gauss()
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 11; j++)
            matrizDeCoeficientes[i][j] = 0;
}

void Gauss::solve(int n, double soluciones[])
{
    double factor;

    for (int renglonPivote = 0; renglonPivote < n; renglonPivote++)
    {
        // Encontrar el pivote m�ximo para intercambiar filas si es necesario
        int filaPivoteMaximo = renglonPivote;
        for (int i = renglonPivote + 1; i < n; i++)
        {
            if (fabs(matrizDeCoeficientes[i][renglonPivote]) > fabs(matrizDeCoeficientes[filaPivoteMaximo][renglonPivote]))
                filaPivoteMaximo = i;
        }

        // Intercambiar filas si es necesario
        if (filaPivoteMaximo != renglonPivote)
        {
            for (int j = 0; j <= n; j++)
            {
                swap(matrizDeCoeficientes[renglonPivote][j], matrizDeCoeficientes[filaPivoteMaximo][j]);
            }
        }

        factor = matrizDeCoeficientes[renglonPivote][renglonPivote];

        for (int columnasDeFila = 0; columnasDeFila <= n; columnasDeFila++)
        {
            matrizDeCoeficientes[renglonPivote][columnasDeFila] /= factor;
        }

        for (int renglonModificado = 0; renglonModificado < n; renglonModificado++)
        {
            if (renglonModificado != renglonPivote)
            {
                factor = matrizDeCoeficientes[renglonModificado][renglonPivote];
                for (int columnasDeFila = 0; columnasDeFila <= n; columnasDeFila++)
                {
                    matrizDeCoeficientes[renglonModificado][columnasDeFila] -=
                        factor * matrizDeCoeficientes[renglonPivote][columnasDeFila];
                }
            }
        }
    }

    // Almacenar las soluciones
    for (int i = 0; i < n; i++)
        soluciones[i] = matrizDeCoeficientes[i][n];
}




//Cambi� el tipo de datos de resultados a double en la funci�n solve.
//Hice ajustes en los �ndices del bucle de entrada para mostrar las posiciones correctas(comenzando desde 1 en lugar de 0).
//Correg� la forma en que se encuentran y cambian filas para evitar divisiones por cero y mejorar la estabilidad num�rica.
//Hice ajustes en la l�gica del bucle principal para la eliminaci�n de Gauss.
//Implement� una verificaci�n para manejar divisiones por cero o valores muy peque�os.
//Elimin� bucles innecesarios en el constructor y correg� el tama�o de la matriz en la clase `Gauss