    #include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Ejercicio 3 - Informacion de Paises");

    cargarPaises();

    // Conexion con Signal y Slot usando lambda
    connect(ui->listPaises, &QListWidget::itemClicked, this, [this](QListWidgetItem *item) {
        onPaisSeleccionado(item);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cargarPaises()
{
    mPaises = {
        {"Peru", {"Lima", "Espanol"}},
        {"Argentina", {"Buenos Aires", "Espanol"}},
        {"Brasil", {"Brasilia", "Portugues"}},
        {"Chile", {"Santiago", "Espanol"}},
        {"Colombia", {"Bogota", "Espanol"}},
        {"Francia", {"Paris", "Frances"}},
        {"Alemania", {"Berlin", "Aleman"}},
        {"Italia", {"Roma", "Italiano"}},
        {"Japon", {"Tokio", "Japones"}},
        {"Canada", {"Ottawa", "Ingles y Frances"}}
    };

    for (auto it = mPaises.begin(); it != mPaises.end(); ++it) {
        ui->listPaises->addItem(it.key());
    }
}

void MainWindow::onPaisSeleccionado(QListWidgetItem *item)
{
    if (!item) return;

    QString nombrePais = item->text();
    if (mPaises.contains(nombrePais)) {
        InfoPais info = mPaises[nombrePais];
        ui->lblPais->setText("Pais: " + nombrePais);
        ui->lblCapital->setText("Capital: " + info.capital);
        ui->lblIdioma->setText("Idioma: " + info.idioma);
    }
}
