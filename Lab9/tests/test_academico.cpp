#include "controller.h"
#include <QtTest>
#include <QTemporaryFile>
#include <stdexcept>

class Pruebas : public QObject {
    Q_OBJECT
    Catalogo catalogo() { return {{"Tarea", std::make_shared<CreadorTarea>()}, {"Examen", std::make_shared<CreadorExamen>()}, {"Proyecto", std::make_shared<CreadorProyecto>()}}; }
    DatosActividad datos() { return {"  Laboratorio 09  ", " Tecnologia de Objetos ", QDate(2026, 11, 20)}; }
    QString escribir(QTemporaryFile& archivo, const QByteArray& contenido) {
        if (!archivo.open()) qFatal("No se puede crear CSV temporal");
        archivo.write(contenido); archivo.close(); return archivo.fileName();
    }
private slots:
    void productosYNormalizacion() {
        for (const auto& c : catalogo()) {
            const auto a = c.creador->crear(datos());
            QCOMPARE(a->tipo(), c.nombre); QCOMPARE(a->datos().titulo, QString("Laboratorio 09"));
            QCOMPARE(a->datos().curso, QString("Tecnologia de Objetos"));
        }
    }
    void validacion_data() {
        QTest::addColumn<QString>("titulo"); QTest::addColumn<QString>("curso"); QTest::addColumn<QDate>("fecha");
        QTest::newRow("titulo vacio") << "   " << "Curso" << QDate(2026, 11, 20);
        QTest::newRow("curso vacio") << "Titulo" << "   " << QDate(2026, 11, 20);
        QTest::newRow("fecha invalida") << "Titulo" << "Curso" << QDate();
        QTest::newRow("titulo largo") << QString(121, 'a') << "Curso" << QDate(2026, 11, 20);
        QTest::newRow("curso largo") << "Titulo" << QString(81, 'a') << QDate(2026, 11, 20);
    }
    void validacion() {
        QFETCH(QString, titulo); QFETCH(QString, curso); QFETCH(QDate, fecha);
        CreadorTarea c; QVERIFY_EXCEPTION_THROWN(c.crear({titulo, curso, fecha}), std::invalid_argument);
    }
    void repositorioProtegeEstado() {
        RepositorioActividades r; CreadorTarea c; r.agregar(c.crear(datos()));
        QVERIFY_EXCEPTION_THROWN(r.agregar(c.crear(datos())), std::invalid_argument);
        QVERIFY_EXCEPTION_THROWN(r.agregar(nullptr), std::invalid_argument);
        auto copia = r.listar(); copia.clear(); QCOMPARE(r.listar().size(), size_t(1));
    }
    void csvMixtoYDuplicados() {
        RepositorioActividades r; FuenteCsvHeredada f; AdaptadorCsv a(r, f, catalogo()); QTemporaryFile csv;
        const auto ruta = escribir(csv, "codigo;asignatura;descripcion;vencimiento\nT;Curso;Uno;20/11/2026\nE;Curso;Dos;21/11/2026\nP;Curso;Tres;22/11/2026\nX;Curso;Error;20/11/2026\nT;Curso;Fecha;31/02/2026\nP;;Vacio;20/11/2026\nT;Solo\n");
        auto resultado = a.cargar(ruta); QCOMPARE(resultado.aceptados, 3); QCOMPARE(resultado.errores.size(), 4);
        QVERIFY(resultado.errores.first().startsWith("Linea 5:")); QCOMPARE(a.listar().size(), size_t(3));
        resultado = a.cargar(ruta); QCOMPARE(resultado.aceptados, 0); QCOMPARE(resultado.errores.size(), 7);
        QCOMPARE(r.listar().size(), size_t(3));
    }
    void csvInaccesibleOCabeceraIncorrecta() {
        RepositorioActividades r; FuenteCsvHeredada f; AdaptadorCsv a(r, f, catalogo());
        QVERIFY_EXCEPTION_THROWN(a.cargar("/archivo/inexistente.csv"), std::invalid_argument);
        QTemporaryFile csv; const auto ruta = escribir(csv, "tipo,titulo\nT,Uno\n");
        QVERIFY_EXCEPTION_THROWN(a.cargar(ruta), std::invalid_argument); QVERIFY(r.listar().empty());
    }
    void controladorCreaListaYRechaza() {
        RepositorioActividades r; ActividadController c(r, catalogo());
        QSignalSpy lista(&c, &ActividadController::listadoActualizado), mensajes(&c, &ActividadController::mensaje);
        c.crear("Examen", "Parcial", "Redes", QDate(2026, 11, 24));
        QCOMPARE(lista.count(), 1); QCOMPARE(r.listar().size(), size_t(1));
        const auto filas = qvariant_cast<Filas>(lista.first().first()); QCOMPARE(filas.first().tipo, QString("Examen"));
        QCOMPARE(mensajes.last()[1].toBool(), false);
        c.crear("Desconocido", "Algo", "Curso", QDate(2026, 11, 24));
        c.crear("Tarea", " ", "Curso", QDate(2026, 11, 24));
        QCOMPARE(mensajes.last()[1].toBool(), true); QCOMPARE(lista.count(), 1); QCOMPARE(r.listar().size(), size_t(1));
    }
    void controladorCargaYErrores() {
        RepositorioActividades r; FuenteCsvHeredada f; AdaptadorCsv a(r, f, catalogo()); ActividadController c(a, catalogo());
        QSignalSpy lista(&c, &ActividadController::listadoActualizado), mensajes(&c, &ActividadController::mensaje);
        QTemporaryFile csv; auto ruta = escribir(csv, "codigo;asignatura;descripcion;vencimiento\nP;Curso;Proyecto;30/11/2026\nX;Curso;Error;20/11/2026\n");
        c.cargar(ruta); QCOMPARE(lista.count(), 1); QCOMPARE(r.listar().size(), size_t(1));
        QVERIFY(mensajes.last()[0].toString().contains("Importadas: 1 | Rechazadas: 1")); QVERIFY(mensajes.last()[1].toBool());
        c.cargar("/inexistente.csv"); QCOMPARE(lista.count(), 1); QVERIFY(mensajes.last()[1].toBool());
    }
};
QTEST_GUILESS_MAIN(Pruebas)
#include "test_academico.moc"
