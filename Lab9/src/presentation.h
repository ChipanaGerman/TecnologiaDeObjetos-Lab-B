#pragma once
#include <QString>
#include <QVector>
#include <QMetaType>
struct FilaActividad { QString tipo, titulo, curso, fecha; };
using Filas = QVector<FilaActividad>;
Q_DECLARE_METATYPE(Filas)
