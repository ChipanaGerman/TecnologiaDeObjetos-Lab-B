#include <QCoreApplication>
#include <QVector>
#include <QList>
#include <QDebug>

struct TareaSimple {
    int id;
    QString nombre;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "=== DEMOSTRACION: QVector vs QList ===" << Qt::endl;

    // 1. USO DE QVector (Ideal para datos continuos y recorridos rapidos)
    QVector<int> vectorNumeros;
    vectorNumeros << 10 << 20 << 30 << 40 << 50;

    qDebug() << "Elementos en QVector:";
    for (int num : vectorNumeros) {
        qDebug() << "  Valor:" << num;
    }

    // 2. USO DE QList (El contenedor estandar utilizado por Qt)
    QList<TareaSimple> listaTareas;
    listaTareas.append({1, "Estudiar Qt"});
    listaTareas.append({2, "Completar laboratorio"});
    listaTareas.prepend({0, "Configurar entorno"}); // prepend inserta al inicio

    qDebug() << Qt::endl << "Elementos en QList:";
    for (const TareaSimple &t : listaTareas) {
        qDebug() << "  ID:" << t.id << " - Descripcion:" << t.nombre;
    }

    // 3. Verificacion de compatibilidad con memoria contigua
    qDebug() << Qt::endl << "Tamano de QVector:" << vectorNumeros.size();
    qDebug() << "Tamano de QList:" << listaTareas.size();

    return 0;
}