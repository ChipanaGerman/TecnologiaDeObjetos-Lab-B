"""Cuenta dependencias concretas explicitas de la vista; ejecutar desde cualquier ruta."""
from pathlib import Path
import json
import re
raiz = Path(__file__).resolve().parents[1]
concretos = ['Tarea', 'Examen', 'Proyecto', 'RepositorioActividades', 'FuenteCsvHeredada']
def medir(rutas):
    texto = '\n'.join(p.read_text(encoding='utf-8') for p in rutas)
    texto = re.sub(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"', '', texto, flags=re.S)
    return [tipo for tipo in concretos if re.search(r'\b' + tipo + r'\b', texto)]
salida = {
    'metrica': 'Tipos concretos de dominio/almacenamiento referenciados explicitamente en la vista (no Qt ni DTO)',
    'antes': medir([raiz/'comparacion/antes.cpp']),
    'despues': medir([raiz/'src/mainwindow.h', raiz/'src/mainwindow.cpp']),
    'limite': 'Medicion lexica de referencias directas; no mide complejidad total ni dependencias transitivas.'
}
salida['cantidad_antes'] = len(salida['antes'])
salida['cantidad_despues'] = len(salida['despues'])
destino = raiz/'evidencias/metricas.json'
destino.write_text(json.dumps(salida, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
print(json.dumps(salida, ensure_ascii=False, indent=2))
