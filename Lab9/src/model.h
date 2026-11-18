#pragma once
#include <QString>
#include <QDate>
#include <QVector>
#include <memory>
#include <vector>

struct DatosActividad {
    QString titulo;
    QString curso;
    QDate fecha;
};

class Actividad {
public:
    explicit Actividad(DatosActividad datos) : datos_(std::move(datos)) {}
    virtual ~Actividad() = default;
    virtual QString tipo() const = 0;
    const DatosActividad& datos() const { return datos_; }
private:
    DatosActividad datos_;
};
class Tarea final : public Actividad {
public: using Actividad::Actividad; QString tipo() const override { return "Tarea"; }
};
class Examen final : public Actividad {
public: using Actividad::Actividad; QString tipo() const override { return "Examen"; }
};
class Proyecto final : public Actividad {
public: using Actividad::Actividad; QString tipo() const override { return "Proyecto"; }
};

// Creator: la operacion comun valida y delega la instanciacion al Factory Method.
class CreadorActividad {
public:
    virtual ~CreadorActividad() = default;
    std::shared_ptr<const Actividad> crear(DatosActividad datos) const;
protected:
    virtual std::shared_ptr<const Actividad> fabricar(DatosActividad datos) const = 0;
};
class CreadorTarea final : public CreadorActividad {
protected: std::shared_ptr<const Actividad> fabricar(DatosActividad datos) const override;
};
class CreadorExamen final : public CreadorActividad {
protected: std::shared_ptr<const Actividad> fabricar(DatosActividad datos) const override;
};
class CreadorProyecto final : public CreadorActividad {
protected: std::shared_ptr<const Actividad> fabricar(DatosActividad datos) const override;
};

struct CatalogoEntrada { QString nombre; std::shared_ptr<CreadorActividad> creador; };
using Catalogo = QVector<CatalogoEntrada>;
struct ResultadoCarga { int aceptados = 0; QStringList errores; };
class IRepositorio {
public:
    virtual ~IRepositorio() = default;
    virtual void agregar(std::shared_ptr<const Actividad> actividad) = 0;
    virtual std::vector<std::shared_ptr<const Actividad>> listar() const = 0;
    virtual ResultadoCarga cargar(const QString& ruta) = 0;
};
class RepositorioActividades final : public IRepositorio {
public:
    void agregar(std::shared_ptr<const Actividad> actividad) override;
    std::vector<std::shared_ptr<const Actividad>> listar() const override;
    ResultadoCarga cargar(const QString& ruta) override;
private:
    std::vector<std::shared_ptr<const Actividad>> actividades_;
};

// Adaptee: entrega lineas de un formato legado, sin conocer IRepositorio.
class FuenteCsvHeredada {
public:
    QStringList leerLineas(const QString& archivo) const;
};
// Adapter: traduce codigo;asignatura;descripcion;vencimiento (dd/MM/yyyy).
class AdaptadorCsv final : public IRepositorio {
public:
    AdaptadorCsv(IRepositorio& destino, const FuenteCsvHeredada& fuente, Catalogo catalogo);
    void agregar(std::shared_ptr<const Actividad> actividad) override;
    std::vector<std::shared_ptr<const Actividad>> listar() const override;
    ResultadoCarga cargar(const QString& ruta) override;
private:
    IRepositorio& destino_;
    const FuenteCsvHeredada& fuente_;
    Catalogo catalogo_;
};
