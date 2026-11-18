# Verificación de la entrega

Fecha: 18/11/2026. Entorno local Windows, Qt 6.12.0, CMake 3.30.5, GCC 13.1.0.

| Criterio de la guía | Evidencia disponible | Estado |
|---|---|---|
| MVC (5 puntos) | Modelo sin Qt Widgets; vista solo conoce DTO; conexiones en main.cpp; pruebas del controlador sin GUI | Implementado y compilado |
| Patrones (5 puntos) | CreadorActividad/fabricar y tres creadores; AdaptadorCsv integra FuenteCsvHeredada con IRepositorio | Implementados y probados |
| Beneficio (5 puntos) | Clases y tres secuencias; baseline compilable; medición 5 a 0; análisis de impacto sin reducción artificial de archivos | Documentado y medición ejecutada |
| Producto/documentación (5 puntos) | Aplicación, CSV, README, informe PDF, respuestas, capturas y video | Disponibles localmente; publicación pendiente |

Resultados: compilación de aplicación y pruebas correcta; baseline compilado con el target baseline; CTest 1/1 suite aprobada; Qt Test 13 casos aprobados, 0 fallidos. El registro completo es pruebas.txt. Los SVG y PNG de PlantUML se generaron sin errores de sintaxis; el PDF se revisó mediante renderizado de sus 11 páginas. El MP4 tiene 400 cuadros a 10 fps (40 segundos) y se pudo abrir con OpenCV.

La demostración usa renderizado offscreen de Qt y no verifica el diálogo nativo de selección en un escritorio interactivo. El guion GUIA_DEMO.md incluye esa comprobación para la sustentación. Las capturas fueron inspeccionadas visualmente; se corrigió la carga de fuente para evitar glifos ausentes en offscreen.

El kit emite avisos de licencia al no poder escribir un lock en AppData; no impidieron generar los archivos MOC ni completar la compilación. No se modificó la instalación de Qt ni se desactivaron sus controles. CMake también informa que no encuentra headers Vulkan; esta aplicación Widgets no los requiere y la configuración concluye correctamente.

publicar.ps1 pasó el análisis sintáctico de PowerShell; su ejecución completa no pudo verificarse porque .git es de solo lectura para este entorno. El intento real de git add/commit fue rechazado al crear .git/index.lock. No hay commits de esta entrega ni push. El script crea los commits con las dos identidades solicitadas, agrega únicamente Lab9 y registra la URL real en ENTREGA.md al ejecutarse en una terminal con acceso al repositorio.

La nota depende de la evaluación docente y de completar la publicación y la sustentación. Esta tabla documenta evidencias; no certifica una calificación obtenida.
