#include "mainwindow.h"
#include <QtWidgets>
MainWindow::MainWindow(const QStringList& tipos) {
    setWindowTitle("Agenda academica | Laboratorio 09"); resize(1040, 820);
    auto* central = new QWidget; auto* layout = new QVBoxLayout(central); layout->setContentsMargins(28, 24, 28, 24); layout->setSpacing(16);
    auto* titulo = new QLabel("Agenda academica"); titulo->setStyleSheet("font-size:28px; font-weight:700; color:#173457;"); layout->addWidget(titulo);
    layout->addWidget(new QLabel("Organiza tus tareas, examenes y proyectos en un solo lugar."));
    auto* grupo = new QGroupBox("Nueva actividad"); auto* formulario = new QFormLayout(grupo);
    auto* tipo = new QComboBox; tipo->addItems(tipos);
    auto* nombre = new QLineEdit; nombre->setMaxLength(120); nombre->setPlaceholderText("Ej. Informe de patrones de diseno");
    auto* curso = new QLineEdit; curso->setMaxLength(80); curso->setPlaceholderText("Ej. Tecnologia de Objetos");
    auto* fecha = new QDateEdit(QDate::currentDate()); fecha->setCalendarPopup(true); fecha->setDisplayFormat("dd/MM/yyyy");
    formulario->addRow("Tipo", tipo); formulario->addRow("Titulo", nombre); formulario->addRow("Curso", curso); formulario->addRow("Fecha", fecha);
    auto* crear = new QPushButton("Crear actividad"); formulario->addRow(crear); layout->addWidget(grupo);
    auto* acciones = new QHBoxLayout; auto* importar = new QPushButton("Importar CSV heredado"); auto* listar = new QPushButton("Actualizar listado"); acciones->addWidget(importar); acciones->addWidget(listar); acciones->addStretch(); layout->addLayout(acciones);
    tabla_ = new QTableWidget(0, 4); tabla_->setMinimumHeight(240); tabla_->setHorizontalHeaderLabels({"Tipo", "Titulo", "Curso", "Fecha"}); tabla_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); tabla_->setEditTriggers(QAbstractItemView::NoEditTriggers); tabla_->setAlternatingRowColors(true); layout->addWidget(tabla_, 1);
    estado_ = new QLabel("Listo. Los datos se conservan durante esta sesion."); estado_->setWordWrap(true); estado_->setTextFormat(Qt::PlainText); layout->addWidget(estado_);
    auto* autores = new QLabel("German Arturo Chipana Jeronimo  /  Leonardo Baca Calsin"); autores->setStyleSheet("color:#62758a; font-size:11px;"); layout->addWidget(autores);
    setCentralWidget(central);
    setStyleSheet("QMainWindow{background:#f3f6fa;} QGroupBox{font-weight:bold;} QLineEdit,QComboBox,QDateEdit{padding:6px;} QPushButton{padding:9px 16px;background:#205b91;color:white;border-radius:5px;} QPushButton:hover{background:#164571;} QTableWidget{background:white; gridline-color:#dde4ee;}");
    connect(crear, &QPushButton::clicked, this, [=, this] { emit crearSolicitado(tipo->currentText(), nombre->text(), curso->text(), fecha->date()); });
    connect(listar, &QPushButton::clicked, this, &MainWindow::listarSolicitado);
    connect(importar, &QPushButton::clicked, this, [this] { const auto ruta = QFileDialog::getOpenFileName(this, "Seleccionar CSV", {}, "CSV (*.csv)"); if (!ruta.isEmpty()) emit cargarSolicitado(ruta); });
}
void MainWindow::mostrar(const Filas& filas) {
    tabla_->setRowCount(filas.size());
    for (qsizetype i = 0; i < filas.size(); ++i) {
        const auto& f = filas[i]; const QStringList valores{f.tipo, f.titulo, f.curso, f.fecha};
        for (int j = 0; j < 4; ++j) tabla_->setItem(i, j, new QTableWidgetItem(valores[j]));
    }
}
void MainWindow::notificar(const QString& texto, bool error) { estado_->setText(texto); estado_->setStyleSheet(error ? "color:#9b2525;" : "color:#176341;"); }
