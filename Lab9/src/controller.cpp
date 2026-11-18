#include "controller.h"
#include <algorithm>
#include <stdexcept>
ActividadController::ActividadController(IRepositorio& r, Catalogo c, QObject* p)
    : QObject(p), repositorio_(r), catalogo_(std::move(c)) {}
QStringList ActividadController::tipos() const {
    QStringList resultado; for (const auto& c : catalogo_) resultado << c.nombre; return resultado;
}
void ActividadController::crear(const QString& tipo, const QString& titulo, const QString& curso, const QDate& fecha) {
    try {
        auto it = std::find_if(catalogo_.begin(), catalogo_.end(), [&](const auto& c) { return c.nombre == tipo; });
        if (it == catalogo_.end()) throw std::invalid_argument("Tipo desconocido.");
        repositorio_.agregar(it->creador->crear({titulo, curso, fecha}));
        listar(); emit mensaje("Actividad creada correctamente.", false);
    } catch (const std::exception& e) { emit mensaje(QString::fromUtf8(e.what()), true); }
}
void ActividadController::listar() {
    Filas filas;
    for (const auto& a : repositorio_.listar()) filas.push_back({a->tipo(), a->datos().titulo, a->datos().curso, a->datos().fecha.toString("yyyy-MM-dd")});
    emit listadoActualizado(filas);
}
void ActividadController::cargar(const QString& ruta) {
    try {
        const auto r = repositorio_.cargar(ruta); listar();
        emit mensaje(QString("Importadas: %1 | Rechazadas: %2").arg(r.aceptados).arg(r.errores.size()) +
            (r.errores.isEmpty() ? QString() : "\n" + r.errores.join('\n')), !r.errores.isEmpty());
    } catch (const std::exception& e) { emit mensaje(QString::fromUtf8(e.what()), true); }
}
