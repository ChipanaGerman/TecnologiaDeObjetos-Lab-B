#include "Task.h"
#include "ui_Task.h"

Task::Task(const QString &nombreTarea, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);

    // Se asigna el texto recibido al control visual Mitext
    ui->Mitext->setText(nombreTarea);

    // Se conecta el clic del checkbox interno a nuestro slot privado
    connect(ui->checkbox, &QCheckBox::toggled, this, &Task::onCheckboxToggled);
}

Task::~Task()
{
    delete ui;
}

QString Task::getNombre() const
{
    return ui->Mitext->text();
}

bool Task::isCompleted() const
{
    return ui->checkbox->isChecked();
}

void Task::onCheckboxToggled(bool checked)
{
    // EMISIÓN: Se dispara la señal enviando el puntero de esta tarea y su estado
    emit statusChanged(this, checked);
}