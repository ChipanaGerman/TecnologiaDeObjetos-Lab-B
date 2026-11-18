// Baseline didactico compilable (g++ -std=c++20 -fsyntax-only antes.cpp).
// Expone deliberadamente los problemas del enunciado; no pertenece a la app final.
#include "../src/model.h"
#include <stdexcept>
class VistaAntes {
    RepositorioActividades repositorio;
    FuenteCsvHeredada fuente;
public:
    void crear(const QString& tipo, DatosActividad datos) {
        if (datos.titulo.trimmed().isEmpty() || datos.curso.trimmed().isEmpty() || !datos.fecha.isValid())
            throw std::invalid_argument("Datos invalidos");
        if (tipo == "Tarea") repositorio.agregar(std::make_shared<Tarea>(datos));
        else if (tipo == "Examen") repositorio.agregar(std::make_shared<Examen>(datos));
        else if (tipo == "Proyecto") repositorio.agregar(std::make_shared<Proyecto>(datos));
        else throw std::invalid_argument("Tipo desconocido");
    }
    auto listar() { return repositorio.listar(); }
    void cargar(const QString& ruta) {
        const auto lineas = fuente.leerLineas(ruta);
        for (qsizetype i = 1; i < lineas.size(); ++i) {
            const auto c = lineas[i].trimmed().split(';');
            if (c.size() != 4) continue;
            const auto tipo = c[0] == "T" ? "Tarea" : c[0] == "E" ? "Examen" : "Proyecto";
            crear(tipo, {c[2], c[1], QDate::fromString(c[3], "dd/MM/yyyy")});
        }
    }
};
