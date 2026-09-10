import typing
from typing import List

# 1. HERENCIA: Clase Base
# En Python, todas las clases heredan implícitamente de `object`.
# Usamos tipado estático para definir los atributos en el método __init__.
class Persona:
    def __init__(self, nombre: str = "", edad: int = 0) -> None:
        # En Python, el encapsulamiento se simula convencionalmente con un guion bajo 
        # (para "protected") o dos (para "private"). Usamos getters y setters
        # con decoradores @property o métodos explícitos para mantener la paridad lógica con Java.
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

    # Adaptación de toString() de Java a __str__() en Python.
    def __str__(self) -> str:
        return f"Persona [nombre={self._nombre}, edad={self._edad}]"

# 1. HERENCIA: Clases Hijas
# En Python, la herencia se indica pasando la clase padre como parámetro en la definición de la clase.
class Profesor(Persona):
    def __init__(self, nombre: str = "", edad: int = 0, especialidad: str = "") -> None:
        # super().__init__() llama al constructor de la clase base, equivalente a super() en Java.
        super().__init__(nombre, edad)
        self._especialidad: str = especialidad

    def get_especialidad(self) -> str:
        return self._especialidad

    def set_especialidad(self, especialidad: str) -> None:
        self._especialidad = especialidad

    def __str__(self) -> str:
        # Llamar a super().__str__() es equivalente a super().toString() en Java.
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

# 2. COMPOSICIÓN: Horario es parte vital de Curso
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
        # Composición: el Horario nace y está íntimamente ligado al Curso
        # Al igual que en Java, lo instanciamos internamente.
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

# 3. AGREGACIÓN: Universidad contiene Cursos independientes
class Universidad:
    def __init__(self, nombre: str = "") -> None:
        self._nombre: str = nombre
        # Tipado para indicar que la lista contiene objetos de tipo Curso
        self._lista_cursos: List[Curso] = []

    def get_nombre(self) -> str:
        return self._nombre

    def set_nombre(self, nombre: str) -> None:
        self._nombre = nombre

    def get_lista_cursos(self) -> List[Curso]:
        return self._lista_cursos

    # Agregación: Recibe cursos ya existentes exteriormente
    def agregar_curso(self, curso: Curso) -> None:
        self._lista_cursos.append(curso)

    def __str__(self) -> str:
        return f"Universidad [nombre={self._nombre}, cantidadCursos={len(self._lista_cursos)}]"

# 4. DEPENDENCIA: Reporte usa temporalmente a Estudiante
class Reporte:
    def __init__(self) -> None:
        pass

    # Dependencia: Estudiante pasa como parámetro temporal para la operación
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

# PROGRAMA PRINCIPAL (Main)
# Este bloque if __name__ == "__main__": simula el método public static void main(String[] args)
def main() -> None:
    print("        SISTEMA DE GESTIÓN UNIVERSITARIA          ")
    print("\n")

    # 1. Creación de 2 profesores (Herencia)
    prof1: Profesor = Profesor("Dr. Carlos Ruiz", 48, "Sistemas Distribuidos")
    prof2: Profesor = Profesor("MSc. Ana Paredes", 39, "Arquitectura de Software")

    print("--- Profesores Registrados ---")
    print(prof1)
    print(prof2)
    print()

    # 2. Creación de 3 estudiantes (Herencia)
    est1: Estudiante = Estudiante("Juan Perez", 20, "20220101")
    est2: Estudiante = Estudiante("Maria Lopez", 22, "20210452")
    est3: Estudiante = Estudiante("Luis Quispe", 21, "20221189")

    print("--- Estudiantes Registrados ---")
    print(est1)
    print(est2)
    print(est3)
    print()

    # 3. Creación de 2 cursos (Composición con Horario)
    curso1: Curso = Curso("Tecnologia de Objetos", "Lunes y Miercoles", "08:00 - 10:00")
    curso2: Curso = Curso("Bases de Datos Avanzadas", "Martes y Jueves", "14:00 - 16:00")

    print("--- Cursos Creados (con Horario por Composición) ---")
    print(curso1)
    print(curso2)
    print()

    # 4. Agregar cursos a la Universidad (Agregación)
    uni: Universidad = Universidad("Universidad Nacional Tecnológica")
    uni.agregar_curso(curso1)
    uni.agregar_curso(curso2)

    print("--- Universidad y Cursos Agregados ---")
    print(uni)
    for c in uni.get_lista_cursos():
        print(f" -> {c}")
    print()

    # 5. Generar reporte de un estudiante (Dependencia)
    reporte: Reporte = Reporte()
    reporte.generar_reporte_estudiante(est1)

if __name__ == "__main__":
    main()
