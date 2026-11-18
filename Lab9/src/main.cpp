#include "mainwindow.h"
#include "controller.h"
#include <QApplication>
#include <QTimer>
#include <QDir>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QFontDatabase>
int main(int argc, char** argv) {
    QApplication app(argc, argv);
    const int fuenteId = QFontDatabase::addApplicationFont("C:/Windows/Fonts/segoeui.ttf");
    if (fuenteId >= 0) app.setFont(QFont(QFontDatabase::applicationFontFamilies(fuenteId).first(), 10));
    Catalogo catalogo{{"Tarea", std::make_shared<CreadorTarea>()}, {"Examen", std::make_shared<CreadorExamen>()}, {"Proyecto", std::make_shared<CreadorProyecto>()}};
    RepositorioActividades memoria; FuenteCsvHeredada fuente;
    AdaptadorCsv repositorio(memoria, fuente, catalogo);
    ActividadController controlador(repositorio, catalogo);
    MainWindow vista(controlador.tipos());
    QObject::connect(&vista, &MainWindow::crearSolicitado, &controlador, &ActividadController::crear);
    QObject::connect(&vista, &MainWindow::listarSolicitado, &controlador, &ActividadController::listar);
    QObject::connect(&vista, &MainWindow::cargarSolicitado, &controlador, &ActividadController::cargar);
    QObject::connect(&controlador, &ActividadController::listadoActualizado, &vista, &MainWindow::mostrar);
    QObject::connect(&controlador, &ActividadController::mensaje, &vista, &MainWindow::notificar);
    controlador.listar(); vista.show();
    // Demostracion reproducible: usa los widgets reales y guarda su renderizado.
    const auto args = app.arguments();
    if (args.size() == 4 && args[1] == "--demo") {
        const QString salida = args[2]; const QString datos = args[3]; QDir().mkpath(salida);
        const auto capturar = [&vista, salida](const QString& nombre) { QApplication::processEvents(); vista.grab().save(salida + "/" + nombre + ".png"); };
        QTimer::singleShot(500, &vista, [&, capturar, datos] {
            capturar("01_inicio");
            const auto entradas = vista.findChildren<QLineEdit*>();
            // Las dos entradas preceden al editor interno de QDateEdit.
            entradas[0]->setText("Laboratorio 09 - patrones de diseno"); entradas[1]->setText("Tecnologia de Objetos");
            vista.findChild<QDateEdit*>()->setDate(QDate(2026, 11, 20));
            for (auto* b : vista.findChildren<QPushButton*>()) if (b->text() == "Crear actividad") b->click();
            capturar("02_crear");
            controlador.cargar(datos + "/actividades.csv"); capturar("03_importar");
            controlador.cargar(datos + "/con_errores.csv"); capturar("04_errores");
            controlador.cargar(datos + "/actividades.csv"); capturar("05_duplicados");
            app.quit();
        });
    }
    return app.exec();
}
