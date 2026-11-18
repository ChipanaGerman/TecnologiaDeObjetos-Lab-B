#include "model.h"
#include <QFile>
#include <QTextStream>
#include <stdexcept>
#include <algorithm>

static void fallo(const QString& mensaje) { throw std::invalid_argument(mensaje.toStdString()); }
std::shared_ptr<const Actividad> CreadorActividad::crear(DatosActividad datos) const {
    datos.titulo = datos.titulo.trimmed(); datos.curso = datos.curso.trimmed();
    if (datos.titulo.isEmpty() || datos.titulo.size() > 120) fallo("Titulo obligatorio (maximo 120 caracteres).");
    if (datos.curso.isEmpty() || datos.curso.size() > 80) fallo("Curso obligatorio (maximo 80 caracteres).");
    if (!datos.fecha.isValid()) fallo("Fecha invalida.");
    return fabricar(std::move(datos));
}
std::shared_ptr<const Actividad> CreadorTarea::fabricar(DatosActividad d) const { return std::make_shared<Tarea>(std::move(d)); }
std::shared_ptr<const Actividad> CreadorExamen::fabricar(DatosActividad d) const { return std::make_shared<Examen>(std::move(d)); }
std::shared_ptr<const Actividad> CreadorProyecto::fabricar(DatosActividad d) const { return std::make_shared<Proyecto>(std::move(d)); }
void RepositorioActividades::agregar(std::shared_ptr<const Actividad> a) {
    if (!a) fallo("Actividad nula.");
    for (const auto& actual : actividades_) {
        if (actual->tipo() == a->tipo() && actual->datos().titulo == a->datos().titulo &&
            actual->datos().curso == a->datos().curso && actual->datos().fecha == a->datos().fecha)
            fallo("Actividad duplicada.");
    }
    actividades_.push_back(std::move(a));
}
std::vector<std::shared_ptr<const Actividad>> RepositorioActividades::listar() const { return actividades_; }
ResultadoCarga RepositorioActividades::cargar(const QString&) { fallo("Este repositorio requiere un adaptador para importar CSV."); return {}; }
QStringList FuenteCsvHeredada::leerLineas(const QString& ruta) const {
    QFile archivo(ruta);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) fallo("No se pudo abrir el archivo CSV.");
    QTextStream entrada(&archivo);
    return entrada.readAll().split('\n');
}
AdaptadorCsv::AdaptadorCsv(IRepositorio& d, const FuenteCsvHeredada& f, Catalogo c)
    : destino_(d), fuente_(f), catalogo_(std::move(c)) {}
void AdaptadorCsv::agregar(std::shared_ptr<const Actividad> a) { destino_.agregar(std::move(a)); }
std::vector<std::shared_ptr<const Actividad>> AdaptadorCsv::listar() const { return destino_.listar(); }
ResultadoCarga AdaptadorCsv::cargar(const QString& ruta) {
    const auto lineas = fuente_.leerLineas(ruta);
    if (lineas.isEmpty() || lineas.first().trimmed() != "codigo;asignatura;descripcion;vencimiento")
        fallo("Cabecera CSV incompatible.");
    ResultadoCarga resultado;
    for (qsizetype i = 1; i < lineas.size(); ++i) {
        if (lineas[i].trimmed().isEmpty()) continue;
        try {
            const auto campos = lineas[i].trimmed().split(';');
            if (campos.size() != 4) fallo("Se requieren cuatro columnas sin punto y coma interno.");
            const QString codigo = campos[0].trimmed();
            const QString nombre = codigo == "T" ? "Tarea" : codigo == "E" ? "Examen" : codigo == "P" ? "Proyecto" : QString();
            auto it = std::find_if(catalogo_.begin(), catalogo_.end(), [&](const auto& c) { return c.nombre == nombre; });
            if (it == catalogo_.end()) fallo("Codigo de actividad desconocido.");
            const auto fechaTexto = campos[3].trimmed();
            const auto fecha = QDate::fromString(fechaTexto, "dd/MM/yyyy");
            if (!fecha.isValid() || fecha.toString("dd/MM/yyyy") != fechaTexto) fallo("Fecha debe usar dd/MM/yyyy.");
            agregar(it->creador->crear({campos[2], campos[1], fecha}));
            ++resultado.aceptados;
        } catch (const std::exception& e) {
            resultado.errores << QString("Linea %1: %2").arg(i + 1).arg(QString::fromUtf8(e.what()));
        }
    }
    return resultado;
}
