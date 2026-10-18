#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct InfoPais {
    QString capital;
    QString idioma;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPaisSeleccionado(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QMap<QString, InfoPais> mPaises;

    void cargarPaises();
};

#endif // MAINWINDOW_H
