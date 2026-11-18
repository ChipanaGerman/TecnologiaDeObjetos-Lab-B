# Laboratorio 09: Patrones de diseño y arquitectura MVC con Qt

Universidad Nacional de San Agustín de Arequipa · Escuela Profesional de Ingeniería de Sistemas

Asignatura: Tecnología de Objetos. Fecha: 18 de noviembre de 2026.

Integrantes: Leonardo Baca Calsin (lbacac@unsa.edu.pe) y German Arturo Chipana Jeronimo (gchipanaj@unsa.edu.pe).

Repositorio: https://github.com/ChipanaGerman/TecnologiaDeObjetos-Lab-B

## 1. Objetivo y problema

Diseñar una aplicación académica con responsabilidades MVC comprobables, Factory Method para crear Tarea, Examen y Proyecto, y Adapter para integrar una fuente CSV heredada. El problema inicial concentra creación concreta, lectura y traducción del almacenamiento en la GUI. El objetivo es reducir esas dependencias, manteniendo un producto pequeño y reproducible.

## 2. Herramientas y estructura

C++20, Qt 6.12.0 Widgets y Test, CMake 3.30.5, Ninja y MinGW GCC 13.1.0. Qt Test identifica la biblioteca Qt instalada como compilada con GCC 15.1.0; el kit usado para este proyecto compiló, enlazó y ejecutó correctamente las pruebas. Los diagramas se escriben en PlantUML y se entregan también en SVG. La compilación se realiza en Lab9/build, excluida del control de versiones.

La carpeta Lab9 se conserva por instrucción del equipo, en lugar de la ruta teo/lab09 propuesta por la guía. La aplicación no requiere red ni base de datos. Los registros permanecen durante la sesión; no se promete persistencia entre ejecuciones.

## 3. Arquitectura y responsabilidades

El Modelo contiene Actividad, sus productos concretos, creadores, IRepositorio y RepositorioActividades. Valida título, curso y fecha, y evita duplicados. No incluye QWidget, MainWindow, QFileDialog ni QApplication. Emplear tipos de Qt Core como QString y QDate no introduce dependencia de la GUI.

MainWindow recoge datos, emite solicitudes y representa una tabla no editable. Solo incluye presentation.h, que declara el DTO FilaActividad. No instancia actividades ni accede al repositorio. ActividadController recibe IRepositorio y un catálogo de creadores por inyección, coordina operaciones y convierte actividades en filas de presentación. main.cpp construye y conecta los componentes; es la raíz de composición.

Las señales crearSolicitado, listarSolicitado y cargarSolicitado conectan la vista con los slots del controlador. listadoActualizado y mensaje comunican resultados. El repositorio devuelve una copia de la colección con punteros compartidos a actividades const: modificar la colección recibida no altera el estado interno.

## 4. Factory Method

Creator: CreadorActividad. Su operación crear normaliza y valida los datos antes de invocar fabricar, el método fábrica virtual. Concrete Creators: CreadorTarea, CreadorExamen y CreadorProyecto. Product: Actividad. Concrete Products: Tarea, Examen y Proyecto.

El controlador obtiene un creador del catálogo y llama crear sin instanciar productos concretos. La selección del creador es una búsqueda en un catálogo; la construcción polimórfica ocurre en fabricar. Por ello no se reduce a una fábrica simple basada en switch. Para añadir otro producto se agrega su creador y se registra en main.cpp; ni la vista ni el controlador necesitan conocer su clase concreta.

El beneficio es localizar la construcción y aplicar una validación común. El costo son más clases y una llamada virtual. Para tres productos con estructura similar el costo es visible; se justifica aquí por el requisito de extensión y por reutilizar la creación validada desde GUI e importación. Las diferencias funcionales de los productos se limitan a su tipo; no se inventan reglas académicas no solicitadas.

## 5. Adapter y contrato del CSV

Target: IRepositorio. Adapter: AdaptadorCsv. Adaptee: FuenteCsvHeredada, cuya operación leerLineas entrega texto sin conocer el dominio. El adaptador traduce codigo/asignatura/descripcion/vencimiento a tipo/curso/titulo/fecha y delega el almacenamiento a otro IRepositorio. El controlador usa la misma interfaz para crear, listar y cargar.

Se elige Adapter porque el enunciado requiere integrar un formato antiguo. Evita modificar la interfaz heredada o repartir sus detalles por la GUI. Su costo es una capa adicional y un contrato de conversión que debe mantenerse y probarse. El método cargar del repositorio en memoria informa que requiere adaptador: es una limitación explícita de la interfaz unificada escogida para el laboratorio; en un sistema mayor convendría separar la capacidad de importación de la de almacenamiento.

El CSV usa UTF-8, delimitador punto y coma, cuatro columnas y fecha dd/MM/yyyy. No admite delimitadores ni saltos de línea dentro de los campos. Un archivo inaccesible o una cabecera incorrecta aborta antes de modificar el repositorio. Una fila inválida se rechaza y las demás se procesan, con un resumen y motivos por línea. Los duplicados se detectan por tipo, título, curso y fecha. Se permiten fechas pasadas para conservar historial.

## 6. Validación y evidencias

Qt Test ejecuta 13 casos contando inicio y cierre: productos y normalización; cinco variantes de datos inválidos; protección del repositorio; CSV mixto y duplicados; archivo inaccesible y cabecera; creación/listado/rechazo del controlador; e importación/errores del controlador. Resultado inicial: 13 aprobados, 0 fallidos, 0 omitidos. El registro final está en evidencias/pruebas.txt. CTest integra la suite como una prueba registrada.

QTEST_GUILESS_MAIN utiliza QCoreApplication. QSignalSpy comprueba emisiones y se verifican tanto los datos como la conservación del estado tras errores. La prueba de CSV mixto verifica los tres tipos, cuatro rechazos y la reimportación sin duplicados. No se afirma cobertura total del código ni se sustituye la inspección de la GUI por estas pruebas.

El modo --demo representa la ventana real de Qt en plataforma offscreen, acciona el botón de creación y ejecuta los slots de carga con los CSV suministrados. Guarda capturas de inicio, creación, importación, errores y duplicados. El video es una presentación de estas capturas reales con rótulos; no es una grabación de interacción manual ni incluye audio. El diálogo nativo de selección de archivos requiere comprobación interactiva adicional.

## 7. Comparación antes y después

comparacion/antes.cpp es un baseline didáctico que reproduce el defecto descrito; no representa una versión histórica recuperada del repositorio. Contiene una vista con referencias explícitas a Tarea, Examen, Proyecto, RepositorioActividades y FuenteCsvHeredada. La vista final no referencia ninguno de esos cinco tipos. medir.py reproduce el conteo léxico y guarda metricas.json: 5 antes y 0 después. Se cuentan tipos distintos, no ocurrencias, líneas ni todas las dependencias de Qt.

La separación añade clases y archivos. Reducir referencias de la vista no implica reducir automáticamente el tamaño total ni mejorar el rendimiento. El beneficio demostrado es localizar las decisiones de dominio y formato y permitir probar el controlador sin GUI.

Escenario A: cambiar el formato de fecha legado. Antes se modifica la lógica de VistaAntes; después la conversión de AdaptadorCsv. En ambos casos cambia un archivo de producción, pero después no se toca la vista. Las pruebas del adaptador también deben actualizarse.

Escenario B: añadir el producto Seminario. Antes se modifica la vista y se añade la declaración del producto al modelo. Después se añade producto/creador al modelo y se registra en main.cpp: no cambia la vista ni el controlador. En la organización actual son dos archivos de producción modificados en ambos diseños; no se reclama una reducción artificial. Si además el CSV admite un código nuevo, debe actualizarse el mapeo del adaptador y sus pruebas.

Estos escenarios son un análisis de impacto sobre el código entregado, no experimentos de extensiones implementadas. Las pruebas aportan evidencia ejecutada de la funcionalidad existente.

## 8. Respuestas a las preguntas de análisis

¿Qué problema concreto justifica Factory Method? La GUI y el importador necesitan crear distintos productos con una política de validación común. Los creadores encapsulan la construcción concreta y permiten coordinarla a través de una abstracción.

¿Cuándo Adapter es preferible a modificar el componente heredado? Cuando su interfaz es estable, pertenece a terceros o tiene otros clientes que no deben migrar. Aquí FuenteCsvHeredada conserva leerLineas y el adaptador asume la traducción y los errores del contrato.

¿Qué dependencias no debe tener el Modelo en MVC? Ventanas, widgets, diálogos, controlador y decisiones de presentación. Las reglas del modelo deben poder ejecutarse y verificarse sin una GUI. La dependencia de Qt Core se acepta explícitamente; no se pretende independencia completa del framework.

¿Qué costo introduce cada patrón y cómo se verificó su beneficio? Factory Method agrega jerarquía y despacho virtual; Adapter agrega traducción y una capa de delegación. Se verifican con diagramas, pruebas de creación e importación, pruebas del controlador sin GUI y el conteo de dependencias concretas de la vista. La comparación reconoce los casos en que el número total de archivos modificados no disminuye.

## 9. Conclusiones

La solución separa presentación, coordinación y reglas del dominio. Factory Method permite reutilizar creación validada y Adapter aísla el contrato del CSV. Los errores son observables y las operaciones rechazadas no agregan actividades inválidas. La principal mejora verificable es que la vista deja de conocer cinco tipos concretos del dominio y almacenamiento.

Para la sustentación se deben mostrar los flujos crear, listar y cargar, explicar la validación parcial del CSV y ejecutar CTest. El equipo debe poder identificar cada participante de los patrones en el código y reconocer los límites del almacenamiento en memoria y del formato heredado.

## 10. Referencias

Guía de práctica de laboratorio N.° 09, Tecnología de Objetos, UNSA, páginas 29-31 (archivo suministrado en Lab9).

Gamma, E., Helm, R., Johnson, R. y Vlissides, J. (1994). Design Patterns: Elements of Reusable Object-Oriented Software. Addison-Wesley.

Fowler, M. (2002). Patterns of Enterprise Application Architecture. Addison-Wesley.

Documentación de Qt 6 y Signals & Slots: https://doc.qt.io/qt-6/ y https://doc.qt.io/qt-6/signalsandslots.html (referencias incluidas en la guía; no se declara una revisión web adicional).

## 11. Identificación de la entrega

La escritura de .git/index.lock fue denegada: los commits y el push están pendientes. publicar.ps1 utiliza ambos correos indicados y registra la URL real del commit evaluado en ENTREGA.md. Los commits no tendrán firma criptográfica.
