#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "Task.h" // Inclusión indispensable para reconocer la clase Task

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void addTask(); // Slot para instanciar una nueva tarea
    void onTaskStatusChanged(Task *tarea, bool completada); // Slot receptor de Task.ui

private:
    Ui::MainWindow *ui;
    QVector<Task*> mTasks; // Vector que almacena las tareas creadas
    void actualizarStatus(); // Función que actualiza el texto del statusLabel
};

#endif // MAINWINDOW_H