#include <iostream>
#include <string>
#include <vector>

// --- 1. HERENCIA ---
// Clase Base
class Persona {
private:
    std::string nombre;
    int edad;

public:
    Persona() : nombre(""), edad(0) {}
    Persona(const std::string& nombre, int edad) : nombre(nombre), edad(edad) {}
    
    // Destructor virtual, buena práctica cuando hay herencia
    virtual ~Persona() = default; 

    std::string getNombre() const { return nombre; }
    void setNombre(const std::string& n) { nombre = n; }

    int getEdad() const { return edad; }
    void setEdad(int e) { edad = e; }

    // Usamos virtual para poder sobreescribirlo en las hijas (como el toString en Java)
    virtual std::string toString() const {
        return "Persona [nombre=" + nombre + ", edad=" + std::to_string(edad) + "]";
    }
};

// Clases Hijas
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

// --- 2. COMPOSICIÓN ---
// El Horario le pertenece completamente al Curso
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
    // Composición: el Horario nace y muere junto con el Curso
    Horario horario;

public:
    Curso(const std::string& nombre, const std::string& dias, const std::string& horas)
        : nombre(nombre), horario(dias, horas) {} 

    std::string getNombre() const { return nombre; }
    void setNombre(const std::string& n) { nombre = n; }

    Horario getHorario() const { return horario; }
    void setHorario(const Horario& h) { horario = h; }

    std::string toString() const {
        return "Curso [nombre=" + nombre + ", " + horario.toString() + "]";
    }
};

// --- 3. AGREGACIÓN ---
// La Universidad tiene cursos, pero no es dueña exclusiva de ellos
class Universidad {
private:
    std::string nombre;
    // Agregación: Usamos punteros porque los cursos ya existen por fuera
    std::vector<Curso*> listaCursos;

public:
    Universidad() : nombre("") {}
    Universidad(const std::string& nombre) : nombre(nombre) {}

    std::string getNombre() const { return nombre; }
    void setNombre(const std::string& n) { nombre = n; }

    const std::vector<Curso*>& getListaCursos() const { return listaCursos; }

    // Recibimos la dirección de memoria del curso para guardarlo en la lista
    void agregarCurso(Curso* curso) {
        listaCursos.push_back(curso);
    }

    std::string toString() const {
        return "Universidad [nombre=" + nombre + ", cantidadCursos=" + std::to_string(listaCursos.size()) + "]";
    }
};

// --- 4. DEPENDENCIA ---
// Reporte solo necesita leer los datos del estudiante un momento
class Reporte {
public:
    Reporte() = default;

    // Dependencia: Pasamos una referencia constante para solo leer los datos sin copiarlos
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

// --- PROGRAMA PRINCIPAL ---
int main() {
    std::cout << "        SISTEMA DE GESTIÓN UNIVERSITARIA          \n\n\n";

    // 1. Herencia: Instanciando a los profes y estudiantes
    Profesor prof1("Dr. Carlos Ruiz", 48, "Sistemas Distribuidos");
    Profesor prof2("MSc. Ana Paredes", 39, "Arquitectura de Software");

    std::cout << "--- Profesores Registrados ---\n";
    std::cout << prof1.toString() << "\n";
    std::cout << prof2.toString() << "\n\n";

    Estudiante est1("Juan Perez", 20, "20220101");
    Estudiante est2("Maria Lopez", 22, "20210452");
    Estudiante est3("Luis Quispe", 21, "20221189");

    std::cout << "--- Estudiantes Registrados ---\n";
    std::cout << est1.toString() << "\n";
    std::cout << est2.toString() << "\n";
    std::cout << est3.toString() << "\n\n";

    // 2. Composición: Se crea el curso y su horario implícitamente
    Curso curso1("Tecnologia de Objetos", "Lunes y Miercoles", "08:00 - 10:00");
    Curso curso2("Bases de Datos Avanzadas", "Martes y Jueves", "14:00 - 16:00");

    std::cout << "--- Cursos Creados (con Horario por Composición) ---\n";
    std::cout << curso1.toString() << "\n";
    std::cout << curso2.toString() << "\n\n";

    // 3. Agregación: Pasamos las direcciones de los cursos a la universidad
    Universidad uni("Universidad Nacional Tecnológica");
    uni.agregarCurso(&curso1); 
    uni.agregarCurso(&curso2);

    std::cout << "--- Universidad y Cursos Agregados ---\n";
    std::cout << uni.toString() << "\n";
    for (const auto& c : uni.getListaCursos()) {
        std::cout << " -> " << c->toString() << "\n";
    }
    std::cout << "\n";

    // 4. Dependencia: Pasamos el estudiante para sacar el reporte
    Reporte reporte;
    reporte.generarReporteEstudiante(est1);

    return 0;
}
