#include <QCoreApplication>
#include <QVector>
#include <QRandomGenerator>
#include <QDebug>
#include <algorithm>

/**
 * ============================================================================
 * UNIVERSIDAD NACIONAL DE SAN AGUSTÍN DE AREQUIPA
 * ESCUELA PROFESIONAL DE INGENIERÍA DE SISTEMAS
 * ASIGNATURA: TECNOLOGÍA DE OBJETOS
 * LABORATORIO 05 - EJERCICIO 1 (VERSIÓN QT NATIVE)
 * ============================================================================
 * 
 * Implementación utilizando contenedores y utilidades nativas de Qt:
 * - QVector<int>
 * - QRandomGenerator
 * - qDebug()
 * - std::count_if con expresión Lambda
 * ============================================================================
 */

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    qDebug() << "========================================================";
    qDebug() << "  UNSA - EPIS | TECNOLOGIA DE OBJETOS - LAB 05";
    qDebug() << "  EJERCICIO 1: Conteo con std::count_if y Lambda (Qt)";
    qDebug() << "========================================================\n";

    const int TAMANIO = 25;
    QVector<int> numeros;
    numeros.reserve(TAMANIO);

    // Generación de números aleatorios con QRandomGenerator (entre 1 y 50)
    for (int i = 0; i < TAMANIO; ++i) {
        numeros.append(QRandomGenerator::global()->bounded(1, 51));
    }

    // Mostrar el vector mediante std::for_each y lambda
    qDebug() << ">>> Vector de" << TAMANIO << "enteros generados:";
    qDebug() << numeros;

    // Predicado unario Lambda: impar y menor que 20
    auto esImparYMenorQue20 = [](int num) -> bool {
        return (num < 20) && (num % 2 != 0);
    };

    // Aplicar std::count_if sobre el contenedor Qt
    int totalCumplen = std::count_if(numeros.begin(), numeros.end(), esImparYMenorQue20);

    // Filtrar elementos que cumplen
    QVector<int> filtrados;
    std::for_each(numeros.begin(), numeros.end(), [&filtrados, &esImparYMenorQue20](int num) {
        if (esImparYMenorQue20(num)) {
            filtrados.append(num);
        }
    });

    qDebug() << "\n>>> Elementos que cumplen (impares < 20):";
    qDebug() << filtrados;

    qDebug() << "\n--------------------------------------------------------";
    qDebug() << "  RESULTADO FINAL:";
    qDebug() << "  Total de numeros impares y menores a 20:" << totalCumplen;
    qDebug() << "--------------------------------------------------------\n";

    return 0;
}
