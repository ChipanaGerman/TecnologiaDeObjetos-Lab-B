#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Ejercicio 1 - Selector de Colores");

    cargarColores();

    // Conexión por Signals y Slots
    connect(ui->listColores, &QListWidget::itemClicked,
            this, &MainWindow::onColorSeleccionado);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cargarColores()
{
    QStringList colores = {
        "Rojo",
        "Azul",
        "Verde",
        "Amarillo",
        "Naranja",
        "Morado",
        "Cian",
        "Magenta",
        "Negro"
    };

    ui->listColores->addItems(colores);
}

void MainWindow::onColorSeleccionado(QListWidgetItem *item)
{
    if (!item) return;

    QString colorNombre = item->text();

    // Actualización del texto del QLabel
    ui->lblColorSeleccionado->setText("Color seleccionado: " + colorNombre);

    // Mapeo para estilizado visual del contenedor
    static const QMap<QString, QString> mapaColores = {
        {"Rojo", "#e74c3c"},
        {"Azul", "#2980b9"},
        {"Verde", "#27ae60"},
        {"Amarillo", "#d4ac0d"},
        {"Naranja", "#e67e22"},
        {"Morado", "#8e44ad"},
        {"Cian", "#16a085"},
        {"Magenta", "#d81b60"},
        {"Negro", "#2c3e50"}
    };

    QString colorHex = mapaColores.value(colorNombre, "#7f8c8d");

    ui->lblColorSeleccionado->setStyleSheet(
        QString("background-color: %1; color: #ffffff; padding: 12px; font-size: 14px; font-weight: bold; border-radius: 6px;")
        .arg(colorHex)
    );
}
