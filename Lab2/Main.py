import typing
from typing import List

# --- 1. HERENCIA ---
# Clase Base
class Persona:
    def __init__(self, nombre: str = "", edad: int = 0) -> None:
        # Usamos un guion bajo para simular el 'private' de Java
        self._nombre: str = nombre
        self._edad: int = edad

    def get_nombre(self) -> str:
        return self._nombre

    def set_nombre(self, nombre: str) -> None:
        self._nombre = nombre

    def get_edad(self) -> int:
        return self._edad

    def set_edad(self, edad: int) -> None:
        self._edad = edad

    # Equivalente al toString()
    def __str__(self) -> str:
        return f"Persona [nombre={self._nombre}, edad={self._edad}]"

# Clases Hijas que heredan de Persona
class Profesor(Persona):
    def __init__(self, nombre: str = "", edad: int = 0, especialidad: str = "") -> None:
        # Llamamos al constructor de la clase padre
        super().__init__(nombre, edad)
        self._especialidad: str = especialidad

    def get_especialidad(self) -> str:
        return self._especialidad

    def set_especialidad(self, especialidad: str) -> None:
        self._especialidad = especialidad

    def __str__(self) -> str:
        return f"Profesor [{super().__str__()}, especialidad={self._especialidad}]"

class Estudiante(Persona):
    def __init__(self, nombre: str = "", edad: int = 0, codigo_estudiante: str = "") -> None:
        super().__init__(nombre, edad)
        self._codigo_estudiante: str = codigo_estudiante

    def get_codigo_estudiante(self) -> str:
        return self._codigo_estudiante

    def set_codigo_estudiante(self, codigo_estudiante: str) -> None:
        self._codigo_estudiante = codigo_estudiante

    def __str__(self) -> str:
        return f"Estudiante [{super().__str__()}, codigo={self._codigo_estudiante}]"

# --- 2. COMPOSICIÓN ---
# El Horario no tiene sentido sin un Curso
class Horario:
    def __init__(self, dias: str = "", horas: str = "") -> None:
        self._dias: str = dias
        self._horas: str = horas

    def get_dias(self) -> str:
        return self._dias

    def set_dias(self, dias: str) -> None:
        self._dias = dias

    def get_horas(self) -> str:
        return self._horas

    def set_horas(self, horas: str) -> None:
        self._horas = horas

    def __str__(self) -> str:
        return f"Horario [dias={self._dias}, horas={self._horas}]"

class Curso:
    def __init__(self, nombre: str, dias: str, horas: str) -> None:
        self._nombre: str = nombre
        # Aquí se ve la composición: instanciamos el Horario dentro del Curso
        self._horario: Horario = Horario(dias, horas)

    def get_nombre(self) -> str:
        return self._nombre

    def set_nombre(self, nombre: str) -> None:
        self._nombre = nombre

    def get_horario(self) -> Horario:
        return self._horario

    def set_horario(self, horario: Horario) -> None:
        self._horario = horario

    def __str__(self) -> str:
        return f"Curso [nombre={self._nombre}, {self._horario.__str__()}]"

# --- 3. AGREGACIÓN ---
# La Universidad agrupa Cursos, pero los cursos existen por su cuenta
class Universidad:
    def __init__(self, nombre: str = "") -> None:
        self._nombre: str = nombre
        self._lista_cursos: List[Curso] = []

    def get_nombre(self) -> str:
        return self._nombre

    def set_nombre(self, nombre: str) -> None:
        self._nombre = nombre

    def get_lista_cursos(self) -> List[Curso]:
        return self._lista_cursos

    # Recibimos el curso desde afuera y lo agregamos a la lista
    def agregar_curso(self, curso: Curso) -> None:
        self._lista_cursos.append(curso)

    def __str__(self) -> str:
        return f"Universidad [nombre={self._nombre}, cantidadCursos={len(self._lista_cursos)}]"

# --- 4. DEPENDENCIA ---
# El Reporte solo usa al Estudiante un rato para imprimir sus datos
class Reporte:
    def __init__(self) -> None:
        pass

    # Pasamos al estudiante como parámetro, lo usamos y ya
    def generar_reporte_estudiante(self, estudiante: Estudiante) -> None:
        print("==========================================")
        print("       REPORTE ACADÉMICO DE ESTUDIANTE    ")
        print("==========================================")
        print(f"Nombre: {estudiante.get_nombre()}")
        print(f"Edad:   {estudiante.get_edad()} años")
        print(f"Código: {estudiante.get_codigo_estudiante()}")
        print("Estado: ACTIVO REGULAR")
        print("==========================================\n")

    def __str__(self) -> str:
        return "Reporte [modulo=Generador de reportes temporales]"

# --- PROGRAMA PRINCIPAL ---
def main() -> None:
    print("        SISTEMA DE GESTIÓN UNIVERSITARIA          ")
    print("\n")

    # 1. Herencia: Creando profesores y estudiantes
    prof1: Profesor = Profesor("Dr. Carlos Ruiz", 48, "Sistemas Distribuidos")
    prof2: Profesor = Profesor("MSc. Ana Paredes", 39, "Arquitectura de Software")

    print("--- Profesores Registrados ---")
    print(prof1)
    print(prof2)
    print()

    est1: Estudiante = Estudiante("Juan Perez", 20, "20220101")
    est2: Estudiante = Estudiante("Maria Lopez", 22, "20210452")
    est3: Estudiante = Estudiante("Luis Quispe", 21, "20221189")

    print("--- Estudiantes Registrados ---")
    print(est1)
    print(est2)
    print(est3)
    print()

    # 2. Composición: Al crear el curso, internamente nace su horario
    curso1: Curso = Curso("Tecnologia de Objetos", "Lunes y Miercoles", "08:00 - 10:00")
    curso2: Curso = Curso("Bases de Datos Avanzadas", "Martes y Jueves", "14:00 - 16:00")

    print("--- Cursos Creados (con Horario por Composición) ---")
    print(curso1)
    print(curso2)
    print()

    # 3. Agregación: Metemos los cursos ya creados a la universidad
    uni: Universidad = Universidad("Universidad Nacional Tecnológica")
    uni.agregar_curso(curso1)
    uni.agregar_curso(curso2)

    print("--- Universidad y Cursos Agregados ---")
    print(uni)
    for c in uni.get_lista_cursos():
        print(f" -> {c}")
    print()

    # 4. Dependencia: Generamos el reporte de un alumno
    reporte: Reporte = Reporte()
    reporte.generar_reporte_estudiante(est1)

if __name__ == "__main__":
    main()
