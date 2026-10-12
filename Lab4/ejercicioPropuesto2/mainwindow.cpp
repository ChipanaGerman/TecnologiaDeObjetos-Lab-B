#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Asegurar que el contenedor tenga un layout vertical para apilar las tareas
    if (!ui->tasksContainer->layout()) {
        QVBoxLayout *layout = new QVBoxLayout(ui->tasksContainer);
        ui->tasksContainer->setLayout(layout);
    }

    // Conexión del botón "Agregar tarea" a su slot correspondiente
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask()
{
    bool ok;
    // Cuadro de diálogo para ingresar el nombre de la tarea
    QString nombre = QInputDialog::getText(this, "Nueva Tarea",
                                           "Descripción de la tarea:",
                                           QLineEdit::Normal,
                                           QString("Tarea %1").arg(mTasks.size() + 1),
                                           &ok);

    if (ok && !nombre.isEmpty()) {
        // 1. Instanciamos dinámicamente la tarea asignando 'this' como padre de memoria
        Task *nuevaTarea = new Task(nombre, this);

        // 2. CONEXIÓN CLAVE ENTRE AMBOS FORMULARIOS:
        // Conecta la señal del widget hijo (Task) al slot receptor del padre (MainWindow)
        connect(nuevaTarea, &Task::statusChanged, this, &MainWindow::onTaskStatusChanged);

        // 3. Añadimos la tarea a la lista lógica y a la interfaz gráfica
        mTasks.append(nuevaTarea);
        ui->tasksContainer->layout()->addWidget(nuevaTarea);

        actualizarStatus();
    }
}

// Este slot se ejecuta automáticamente cada vez que se marca/desmarca un checkbox en Task.ui
void MainWindow::onTaskStatusChanged(Task *tarea, bool completada)
{
    qDebug() << "Evento recibido de:" << tarea->getNombre()
    << "Estado completado:" << completada;

    actualizarStatus();
}

void MainWindow::actualizarStatus()
{
    int total = mTasks.size();
    int completadas = 0;

    for (Task *t : mTasks) {
        if (t->isCompleted()) {
            completadas++;
        }
    }

    // Actualizamos el statusLabel del MainWindow.ui con la información recibida
    ui->statusLabel->setText(QString("Status: %1 de %2 tareas hechas")
                                 .arg(completadas)
                                 .arg(total));
}