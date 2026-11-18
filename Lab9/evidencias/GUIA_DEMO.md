# Demostración y sustentación

`demostracion.mp4` presenta capturas reales del renderizado Qt offscreen. Es una demostración visual por etapas, sin audio ni simulación de clics en un escritorio. La creación sí acciona el botón real; las cargas llaman al controlador. Para mostrar la interacción completa, seguir este guion en la ventana normal:

1. Presentar a ambos integrantes y el objetivo MVC + Factory Method + Adapter.
2. Crear una tarea; mostrar cómo crearSolicitado llega al controlador y al creador concreto.
3. Cambiar el tipo a Examen y Proyecto; mostrar el método fabricar de cada creador.
4. Actualizar el listado. Explicar que la tabla solo recibe DTO y no modifica el modelo.
5. Abrir el selector CSV y elegir datos/actividades.csv: tres importaciones.
6. Importar datos/con_errores.csv: una aceptada y cuatro errores por línea.
7. Repetir actividades.csv: tres duplicados rechazados.
8. Ejecutar CTest y abrir pruebas.txt. Mostrar 13 casos aprobados, incluidas validaciones parametrizadas e inicio/cierre.
9. Abrir clases.svg y metricas.json. Explicar el conteo 5 -> 0 y el costo de introducir clases.
10. Indicar que los datos se conservan en memoria y que el formato legado no admite campos con punto y coma interno.

Regenerar capturas, desde la raíz y con el kit Qt en PATH:

```powershell
& .\Lab9\build\lab09.exe -platform offscreen --demo Lab9/evidencias Lab9/datos
python Lab9/comparacion/medir.py
python Lab9/evidencias/generar_entregables.py
```

El último comando requiere Python con reportlab, Pillow y opencv-python. Los binarios y la carpeta build no se versionan.
