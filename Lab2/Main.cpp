#include <iostream>
#include <string>
#include <vector>

// 1. HERENCIA: Clase Base
// Usamos protected o private según corresponda, y getters/setters.
// Se recomienda usar std::string para cadenas y virtual destructors en clases base.
class Persona {
private:
    std::string nombre;
    int edad;

public:
    Persona() : nombre(""), edad(0) {}
    Persona(const std::string& nombre, int edad) : nombre(nombre), edad(edad) {}
    virtual ~Persona() = default; // Destructor virtual para correcta destrucción de derivadas

    std::string getNombre() const { return nombre; }
    void setNombre(const std::string& n) { nombre = n; }

    int getEdad() const { return edad; }
    void setEdad(int e) { edad = e; }

    // Método virtual para permitir override, simulando el comportamiento de Java toString().
    virtual std::string toString() const {
        return "Persona [nombre=" + nombre + ", edad=" + std::to_string(edad) + "]";
    }
};

// 1. HERENCIA: Clases Hijas
class Profesor : public Persona {
private:
    std::string especialidad;

public:
    Profesor() : Persona(), especialidad("") {}
    Profesor(const std::string& nombre, int edad, const std::string& especialidad)
        : Persona(nombre, edad), especialidad(especialidad) {}

    std::string getEspecialidad() const { return especialidad; }
    void setEspecialidad(const std::string& esp) { especialidad = esp; }

    std::string toString() const override {
        return "Profesor [" + Persona::toString() + ", especialidad=" + especialidad + "]";
    }
};

class Estudiante : public Persona {
private:
    std::string codigoEstudiante;

public:
    Estudiante() : Persona(), codigoEstudiante("") {}
    Estudiante(const std::string& nombre, int edad, const std::string& codigo)
        : Persona(nombre, edad), codigoEstudiante(codigo) {}

    std::string getCodigoEstudiante() const { return codigoEstudiante; }
    void setCodigoEstudiante(const std::string& cod) { codigoEstudiante = cod; }

    std::string toString() const override {
        return "Estudiante [" + Persona::toString() + ", codigo=" + codigoEstudiante + "]";
    }
};

// 2. COMPOSICIÓN: Horario es parte vital de Curso
class Horario {
private:
    std::string dias;
    std::string horas;

public:
    Horario() : dias(""), horas("") {}
    Horario(const std::string& dias, const std::string& horas) : dias(dias), horas(horas) {}

    std::string getDias() const { return dias; }
    void setDias(const std::string& d) { dias = d; }

    std::string getHoras() const { return horas; }
    void setHoras(const std::string& h) { horas = h; }

    std::string toString() const {
        return "Horario [dias=" + dias + ", horas=" + horas + "]";
    }
};

class Curso {
private:
    std::string nombre;
    // Composición: Horario pertenece enteramente a Curso.
    // En C++ esto se representa usando objetos como miembros por valor en vez de punteros.
    Horario horario;

public:
    Curso(const std::string& nombre, const std::string& dias, const std::string& horas)
        : nombre(nombre), horario(dias, horas) {} // Se instancia junto con el Curso

    std::string getNombre() const { return nombre; }
    void setNombre(const std::string& n) { nombre = n; }

    Horario getHorario() const { return horario; }
    void setHorario(const Horario& h) { horario = h; }

    std::string toString() const {
        return "Curso [nombre=" + nombre + ", " + horario.toString() + "]";
    }
};

// 3. AGREGACIÓN: Universidad contiene Cursos independientes
class Universidad {
private:
    std::string nombre;
    // Agregación: La universidad conoce los cursos pero no es dueña absoluta de su ciclo de vida.
    // Para simplificar y emular el comportamiento de Java (referencias), usamos punteros crudos observadores.
    std::vector<Curso*> listaCursos;

public:
    Universidad() : nombre("") {}
    Universidad(const std::string& nombre) : nombre(nombre) {}

    std::string getNombre() const { return nombre; }
    void setNombre(const std::string& n) { nombre = n; }

    const std::vector<Curso*>& getListaCursos() const { return listaCursos; }

    // Agregación: Se recibe un puntero al curso que existe fuera de este objeto.
    void agregarCurso(Curso* curso) {
        listaCursos.push_back(curso);
    }

    std::string toString() const {
        return "Universidad [nombre=" + nombre + ", cantidadCursos=" + std::to_string(listaCursos.size()) + "]";
    }
};

// 4. DEPENDENCIA: Reporte usa temporalmente a Estudiante
class Reporte {
public:
    Reporte() = default;

    // Dependencia: Pasamos una referencia constante para evitar copias y marcar que solo la "usamos"
    void generarReporteEstudiante(const Estudiante& estudiante) const {
        std::cout << "==========================================\n";
        std::cout << "       REPORTE ACADÉMICO DE ESTUDIANTE    \n";
        std::cout << "==========================================\n";
        std::cout << "Nombre: " << estudiante.getNombre() << "\n";
        std::cout << "Edad:   " << estudiante.getEdad() << " años\n";
        std::cout << "Código: " << estudiante.getCodigoEstudiante() << "\n";
        std::cout << "Estado: ACTIVO REGULAR\n";
        std::cout << "==========================================\n\n";
    }

    std::string toString() const {
        return "Reporte [modulo=Generador de reportes temporales]";
    }
};

// PROGRAMA PRINCIPAL (Main)
int main() {
    std::cout << "        SISTEMA DE GESTIÓN UNIVERSITARIA          \n\n\n";

    // 1. Creación de 2 profesores (Herencia)
    Profesor prof1("Dr. Carlos Ruiz", 48, "Sistemas Distribuidos");
    Profesor prof2("MSc. Ana Paredes", 39, "Arquitectura de Software");

    std::cout << "--- Profesores Registrados ---\n";
    std::cout << prof1.toString() << "\n";
    std::cout << prof2.toString() << "\n\n";

    // 2. Creación de 3 estudiantes (Herencia)
    Estudiante est1("Juan Perez", 20, "20220101");
    Estudiante est2("Maria Lopez", 22, "20210452");
    Estudiante est3("Luis Quispe", 21, "20221189");

    std::cout << "--- Estudiantes Registrados ---\n";
    std::cout << est1.toString() << "\n";
    std::cout << est2.toString() << "\n";
    std::cout << est3.toString() << "\n\n";

    // 3. Creación de 2 cursos (Composición con Horario)
    Curso curso1("Tecnologia de Objetos", "Lunes y Miercoles", "08:00 - 10:00");
    Curso curso2("Bases de Datos Avanzadas", "Martes y Jueves", "14:00 - 16:00");

    std::cout << "--- Cursos Creados (con Horario por Composición) ---\n";
    std::cout << curso1.toString() << "\n";
    std::cout << curso2.toString() << "\n\n";

    // 4. Agregar cursos a la Universidad (Agregación)
    Universidad uni("Universidad Nacional Tecnológica");
    uni.agregarCurso(&curso1); // Pasamos puntero del curso
    uni.agregarCurso(&curso2);

    std::cout << "--- Universidad y Cursos Agregados ---\n";
    std::cout << uni.toString() << "\n";
    for (const auto& c : uni.getListaCursos()) {
        std::cout << " -> " << c->toString() << "\n";
    }
    std::cout << "\n";

    // 5. Generar reporte de un estudiante (Dependencia)
    Reporte reporte;
    reporte.generarReporteEstudiante(est1);

    return 0;
}
