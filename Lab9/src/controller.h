#pragma once
#include "model.h"
#include "presentation.h"
#include <QObject>
class ActividadController final : public QObject {
    Q_OBJECT
public:
    ActividadController(IRepositorio& repositorio, Catalogo catalogo, QObject* padre = nullptr);
    QStringList tipos() const;
public slots:
    void crear(const QString& tipo, const QString& titulo, const QString& curso, const QDate& fecha);
    void listar();
    void cargar(const QString& ruta);
signals:
    void listadoActualizado(const Filas& filas);
    void mensaje(const QString& texto, bool error);
private:
    IRepositorio& repositorio_;
    Catalogo catalogo_;
};
