#pragma once
#include "presentation.h"
#include <QDate>
#include <QMainWindow>
class QTableWidget;
class QLabel;
class MainWindow final : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(const QStringList& tipos);
    void mostrar(const Filas& filas);
    void notificar(const QString& texto, bool error);
signals:
    void crearSolicitado(const QString& tipo, const QString& titulo, const QString& curso, const QDate& fecha);
    void listarSolicitado();
    void cargarSolicitado(const QString& ruta);
private:
    QTableWidget* tabla_;
    QLabel* estado_;
};
