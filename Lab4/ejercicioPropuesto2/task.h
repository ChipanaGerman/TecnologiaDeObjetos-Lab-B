#ifndef TASK_H
#define TASK_H

#include <QWidget>

namespace Ui {
class Task;
}

class Task : public QWidget
{
    Q_OBJECT

public:
    explicit Task(const QString &nombreTarea, QWidget *parent = nullptr);
    ~Task();

    QString getNombre() const;
    bool isCompleted() const;

signals:
    // SEÑAL PERSONALIZADA: Notifica hacia el exterior que esta tarea cambió
    void statusChanged(Task *tarea, bool completada);

private slots:
    // SLOT PRIVADO: Reacciona cuando el usuario marca o desmarca el checkbox interno
    void onCheckboxToggled(bool checked);

private:
    Ui::Task *ui;
};

#endif // TASK_H