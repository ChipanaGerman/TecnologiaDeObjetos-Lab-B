# Laboratorio 09 — Seguimiento académico con Qt

**Tecnología de Objetos · UNSA · 18/11/2026**

| Integrante | Correo |
|---|---|
| Leonardo Baca Calsin | lbacac@unsa.edu.pe |
| German Arturo Chipana Jeronimo | gchipanaj@unsa.edu.pe |

Repositorio: https://github.com/ChipanaGerman/TecnologiaDeObjetos-Lab-B

La solución permanece en `Lab9/` por decisión del equipo. Esta es la única adaptación a la convención `teo/lab09/` de la guía.

## Construcción y pruebas

Requisitos: Qt 6 con Widgets y Test, compilador compatible con C++20, CMake >= 3.21 y Ninja. En Qt Creator, abrir `Lab9/CMakeLists.txt`, seleccionar un kit Qt 6 y una carpeta build fuera de `src/`.

PowerShell, desde la raíz del repositorio, con el kit instalado en esta máquina:

```powershell
$env:PATH = 'C:\Qt\Tools\mingw1310_64\bin;C:\Qt\Tools\Ninja;C:\Qt\6.12.0\mingw_64\bin;' + $env:PATH
& C:\Qt\Tools\CMake_64\bin\cmake.exe -S Lab9 -B Lab9/build -G Ninja -DCMAKE_PREFIX_PATH=C:/Qt/6.12.0/mingw_64 -DCMAKE_BUILD_TYPE=Debug
& C:\Qt\Tools\CMake_64\bin\cmake.exe --build Lab9/build
& C:\Qt\Tools\CMake_64\bin\ctest.exe --test-dir Lab9/build --output-on-failure
& .\Lab9\build\lab09.exe
```

En otras máquinas ajustar las rutas al kit propio. No mezclar las DLL de otros kits MinGW/MSVC. Las pruebas usan QCoreApplication; no abren ventanas ni requieren QApplication.

## Uso

1. Crear una Tarea, Examen o Proyecto con título, curso y fecha.
2. Actualizar el listado; la tabla no permite modificar el modelo.
3. Importar `datos/actividades.csv`: se añaden tres tipos de actividades.
4. Importar `datos/con_errores.csv`: una fila aceptada y cuatro rechazadas con número de línea.
5. Repetir una importación: los duplicados se rechazan sin alterar las actividades existentes.

El almacenamiento es **en memoria durante la sesión**. Cerrar la aplicación descarta los datos. La guía permite Adapter o Facade; se elige Adapter para el CSV heredado y no se incorpora persistencia adicional.

## Contrato CSV heredado

UTF-8; cabecera exacta `codigo;asignatura;descripcion;vencimiento`; códigos T/E/P; fecha estricta `dd/MM/yyyy`. Se permiten CRLF, LF y líneas vacías. Es un formato delimitado sencillo: no admite comillas de escape, saltos dentro de un campo ni punto y coma interno. Los errores de archivo/cabecera abortan sin cambios; los errores por fila producen una importación parcial explícita. Una actividad es duplicada si coinciden tipo, título normalizado, curso normalizado y fecha. No se prohíben fechas pasadas: permiten cargar historial académico.

## Organización y evidencias

- `src/`: modelo, Factory Method, Adapter, controlador, vista y composición de dependencias.
- `tests/`: pruebas de reglas, CSV, duplicados, señales y estado del controlador.
- `datos/`: ejemplos reproducibles.
- `diagramas/`: clases y secuencias crear/listar/cargar en PlantUML y SVG.
- `comparacion/`: baseline didáctico y medición reproducible.
- `INFORME.md`: análisis, decisiones, respuestas y límites.
- `evidencias/`: resultados reales de verificación y demostración.

Regenerar diagramas: `java -jar RUTA/plantuml.jar -tsvg Lab9/diagramas/*.puml`.
Consultar el commit evaluado con `git log -1 --format=%H -- Lab9` y abrir `https://github.com/ChipanaGerman/TecnologiaDeObjetos-Lab-B/commit/<hash>`.

## Entrega y publicación

Informe listo para leer: [INFORME_LAB09_Chipana_Baca.pdf](INFORME_LAB09_Chipana_Baca.pdf). Video de 40 segundos: [demostracion.mp4](evidencias/demostracion.mp4). Guion y alcance de la demostración: [GUIA_DEMO.md](evidencias/GUIA_DEMO.md).

Este entorno no permite escribir en `.git`; los commits y el push están pendientes. En una terminal PowerShell normal, ejecutar `./Lab9/publicar.ps1`. El script crea un commit de implementación con `gchipanaj@unsa.edu.pe`, otro de documentación y evidencias con `lbacac@unsa.edu.pe`, registra el commit evaluado en `ENTREGA.md` y publica mediante push normal. No cambia la configuración global de Git ni agrega archivos de otros laboratorios. Requiere Git autenticado con permiso de escritura en el repositorio y rechaza un índice que ya tenga archivos preparados.
