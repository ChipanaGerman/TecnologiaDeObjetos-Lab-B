import java.util.ArrayList;
import java.util.List;

// 1. HERENCIA: Clase Base
class Persona {
    private String nombre;
    private int edad;

    public Persona() {}

    public Persona(String nombre, int edad) {
        this.nombre = nombre;
        this.edad = edad;
    }

    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public int getEdad() {
        return edad;
    }

    public void setEdad(int edad) {
        this.edad = edad;
    }

    @Override
    public String toString() {
        return "Persona [nombre=" + nombre + ", edad=" + edad + "]";
    }
}

// 1. HERENCIA: Clases Hijas
class Profesor extends Persona {
    private String especialidad;

    public Profesor() {
        super();
    }

    public Profesor(String nombre, int edad, String especialidad) {
        super(nombre, edad);
        this.especialidad = especialidad;
    }

    public String getEspecialidad() {
        return especialidad;
    }

    public void setEspecialidad(String especialidad) {
        this.especialidad = especialidad;
    }

    @Override
    public String toString() {
        return "Profesor [" + super.toString() + ", especialidad=" + especialidad + "]";
    }
}

class Estudiante extends Persona {
    private String codigoEstudiante;

    public Estudiante() {
        super();
    }

    public Estudiante(String nombre, int edad, String codigoEstudiante) {
        super(nombre, edad);
        this.codigoEstudiante = codigoEstudiante;
    }

    public String getCodigoEstudiante() {
        return codigoEstudiante;
    }

    public void setCodigoEstudiante(String codigoEstudiante) {
        this.codigoEstudiante = codigoEstudiante;
    }

    @Override
    public String toString() {
        return "Estudiante [" + super.toString() + ", codigo=" + codigoEstudiante + "]";
    }
}

// 2. COMPOSICIÓN: Horario es parte vital de Curso
class Horario {
    private String dias;
    private String horas;

    public Horario() {}

    public Horario(String dias, String horas) {
        this.dias = dias;
        this.horas = horas;
    }

    public String getDias() {
        return dias;
    }

    public void setDias(String dias) {
        this.dias = dias;
    }

    public String getHoras() {
        return horas;
    }

    public void setHoras(String horas) {
        this.horas = horas;
    }

    @Override
    public String toString() {
        return "Horario [dias=" + dias + ", horas=" + horas + "]";
    }
}

class Curso {
    private String nombre;
    // Composición: el Horario nace y está íntimamente ligado al Curso
    private Horario horario;

    public Curso(String nombre, String dias, String horas) {
        this.nombre = nombre;
        // Se instancia directamente para evidenciar la composición fuerte
        this.horario = new Horario(dias, horas);
    }

    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public Horario getHorario() {
        return horario;
    }

    public void setHorario(Horario horario) {
        this.horario = horario;
    }

    @Override
    public String toString() {
        return "Curso [nombre=" + nombre + ", " + horario.toString() + "]";
    }
}

// 3. AGREGACIÓN: Universidad contiene Cursos independientes
class Universidad {
    private String nombre;
    private List<Curso> listaCursos;

    public Universidad() {
        this.listaCursos = new ArrayList<>();
    }

    public Universidad(String nombre) {
        this.nombre = nombre;
        this.listaCursos = new ArrayList<>();
    }

    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public List<Curso> getListaCursos() {
        return listaCursos;
    }

    // Agregación: Recibe cursos ya existentes exteriormente
    public void agregarCurso(Curso curso) {
        this.listaCursos.add(curso);
    }

    @Override
    public String toString() {
        return "Universidad [nombre=" + nombre + ", cantidadCursos=" + listaCursos.size() + "]";
    }
}

// 4. DEPENDENCIA: Reporte usa temporalmente a Estudiante
class Reporte {
    public Reporte() {}

    // Dependencia: Estudiante pasa como parámetro temporal para la operación
    public void generarReporteEstudiante(Estudiante estudiante) {
        System.out.println("==========================================");
        System.out.println("       REPORTE ACADÉMICO DE ESTUDIANTE    ");
        System.out.println("==========================================");
        System.out.println("Nombre: " + estudiante.getNombre());
        System.out.println("Edad:   " + estudiante.getEdad() + " años");
        System.out.println("Código: " + estudiante.getCodigoEstudiante());
        System.out.println("Estado: ACTIVO REGULAR");
        System.out.println("==========================================\n");
    }

    @Override
    public String toString() {
        return "Reporte [modulo=Generador de reportes temporales]";
    }
}

// PROGRAMA PRINCIPAL (Main)
public class Main {
    public static void main(String[] args) {
        System.out.println("        SISTEMA DE GESTIÓN UNIVERSITARIA          ");
        System.out.println("\n");

        // 1. Creación de 2 profesores (Herencia)
        Profesor prof1 = new Profesor("Dr. Carlos Ruiz", 48, "Sistemas Distribuidos");
        Profesor prof2 = new Profesor("MSc. Ana Paredes", 39, "Arquitectura de Software");

        System.out.println("--- Profesores Registrados ---");
        System.out.println(prof1);
        System.out.println(prof2);
        System.out.println();

        // 2. Creación de 3 estudiantes (Herencia)
        Estudiante est1 = new Estudiante("Juan Perez", 20, "20220101");
        Estudiante est2 = new Estudiante("Maria Lopez", 22, "20210452");
        Estudiante est3 = new Estudiante("Luis Quispe", 21, "20221189");

        System.out.println("--- Estudiantes Registrados ---");
        System.out.println(est1);
        System.out.println(est2);
        System.out.println(est3);
        System.out.println();

        // 3. Creación de 2 cursos (Composición con Horario)
        Curso curso1 = new Curso("Tecnologia de Objetos", "Lunes y Miercoles", "08:00 - 10:00");
        Curso curso2 = new Curso("Bases de Datos Avanzadas", "Martes y Jueves", "14:00 - 16:00");

        System.out.println("--- Cursos Creados (con Horario por Composición) ---");
        System.out.println(curso1);
        System.out.println(curso2);
        System.out.println();

        // 4. Agregar cursos a la Universidad (Agregación)
        Universidad uni = new Universidad("Universidad Nacional Tecnológica");
        uni.agregarCurso(curso1);
        uni.agregarCurso(curso2);

        System.out.println("--- Universidad y Cursos Agregados ---");
        System.out.println(uni);
        for (Curso c : uni.getListaCursos()) {
            System.out.println(" -> " + c);
        }
        System.out.println();

        // 5. Generar reporte de un estudiante (Dependencia)
        Reporte reporte = new Reporte();
        reporte.generarReporteEstudiante(est1);
    }
}