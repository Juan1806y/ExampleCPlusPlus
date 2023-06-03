#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tableModel = new QStandardItemModel(this);
    ui->tableTareas->setModel(tableModel);

    tableModel2 = new QStandardItemModel(this);
    ui->tableEntregas->setModel(tableModel2);

    ui->cboEntregas->addItem("Tarea");
    ui->cboEntregas->addItem("Quiz");
    ui->cboEntregas->addItem("Parcial");
    ui->cboEntregas->addItem("Otro");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cmdAgregarEstudiante_clicked()
{
    int codigo = ui->txtCodigoEstudiante->text().toInt();
    QString nombre = ui->txtNombreEstudiante->text();
    QString codigoStr = ui->txtCodigoEstudiante->text();
    if (codigoStr.isEmpty()) {
        QMessageBox::critical(this, "Error", "Por favor ingresa el código del estudiante.");
            return;
    }

    if (codigo <= 0) {
        QMessageBox::critical(this, "Error", "El código debe ser un número válido.");
        return;
    }

    if (nombre.isEmpty()) {
        QMessageBox::critical(this, "Error", "Por favor ingresa el nombre del estudiante.");
        return;
    }

    QRegularExpression regex("[0-9]");
    if (regex.match(nombre).hasMatch()) {
        QMessageBox::critical(this, "Error", "El nombre del estudiante no puede contener números.");
            return;
    }

    if (sistemaAcademico.agregarEstudiante(codigo, nombre.toStdString())){

    actualizarTablaEstudiantes(sistemaAcademico.getEstudiantes());
    actualizarComboBox(sistemaAcademico.getEstudiantes());

    QMessageBox::information(this, "Éxito", "Estudiante agregado exitosamente.");
    }
    else{
    QMessageBox::information(this, "Error","No agregue estudiantes repetidos");
    }
}


void MainWindow::actualizarTablaEstudiantes(const std::vector<Estudiante>& estudiantes)
{
    tableModel->clear();

    tableModel->setHorizontalHeaderLabels({"Código", "Nombre"});

        for (auto& estudiante : estudiantes)
    {
        QList<QStandardItem*> rowItems;
        rowItems.append(new QStandardItem(QString::number(estudiante.getCodigo())));
        rowItems.append(new QStandardItem(QString::fromStdString(estudiante.getNombre())));
        tableModel->appendRow(rowItems);
    }
    ui->tableTareas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::actualizarTablaEntregas(const std::vector<Entrega>& entregas)
{
    tableModel2->clear();
    tableModel2->setHorizontalHeaderLabels({"Nombre Actividad", "Nota", "Porcentaje %"});

    for (auto& entrega : entregas) {
        QList<QStandardItem*> rowItems;
        QStandardItem* nombreItem = new QStandardItem(QString::fromStdString(entrega.getNombre()));
        QStandardItem* notaItem = new QStandardItem(QString::number(entrega.getNota()));
        QStandardItem* porcentajeItem = new QStandardItem(QString::number(entrega.getPorcentaje()));

        rowItems.append(nombreItem);
        rowItems.append(notaItem);
        rowItems.append(porcentajeItem);

        tableModel2->appendRow(rowItems);
    }
    ui->tableEntregas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


void MainWindow::actualizarComboBox(const std::vector<Estudiante>& estudiantes)
{
    ui->cboEstudiantes->clear();

    for (auto& estudiante : estudiantes)
    {
        ui->cboEstudiantes->addItem(QString::fromStdString(estudiante.getNombre()));
    }
}

void MainWindow::on_cboEstudiantes_currentIndexChanged(int index)
{
    int tamanio = sistemaAcademico.getEstudiantes().size();
    if (index >= 0 && index < tamanio) {
        actualizarTablaEntregas(sistemaAcademico.getEstudiantes()[index].getEntregas());

    }
    else{
        tableModel2->clear();
    }
}

void MainWindow::on_cmdEliminarEstudiante_clicked()
{
    QModelIndexList selectedIndexes = ui->tableTareas->selectionModel()->selectedIndexes();

    if (!selectedIndexes.isEmpty())
    {
        int rowIndex = selectedIndexes.first().row();

        Estudiante estudiante = sistemaAcademico.getEstudiantes()[rowIndex];

        sistemaAcademico.eliminarEstudiante(estudiante);

        actualizarTablaEstudiantes(sistemaAcademico.getEstudiantes());
        actualizarComboBox(sistemaAcademico.getEstudiantes());

        QMessageBox::information(this, "Éxito", "Estudiante eliminado exitosamente.");
    }
}


void MainWindow::on_cboEntregas_currentIndexChanged(int index)
{
    if (index == 0){
        ui->txtPorcentaje->setText("10");
        ui->txtPorcentaje->setEnabled(false);
    } else if (index == 1){
        ui->txtPorcentaje->setText("15");
        ui->txtPorcentaje->setEnabled(false);
    } else if (index == 2){
        ui->txtPorcentaje->setText("30");
        ui->txtPorcentaje->setEnabled(false);
    } else{
        ui->txtPorcentaje->setText("");
        ui->txtPorcentaje->setEnabled(true);
    }
}

void MainWindow::on_cmdAgregarTarea_clicked()
{
    int posicion = ui->cboEstudiantes->currentIndex();

    QString nombre = ui->txtNombreTarea->text();
    QString notaStr = ui->txtNota->text();
    double nota = ui->txtNota->text().toDouble();
    double porcentaje = ui->txtPorcentaje->text().toDouble();
    int tipoEntrega = ui->cboEntregas->currentIndex();

    if (posicion < 0) {
        QMessageBox::critical(this, "Error", "Por favor selecciona un estudiante.");
        return;
    }

    if (nombre.isEmpty()) {
        QMessageBox::critical(this, "Error", "Por favor ingresa el nombre de la tarea.");
        return;
    }

    QRegularExpression regex("[0-9]");
    if (regex.match(nombre).hasMatch()) {
        QMessageBox::critical(this, "Error", "El nombre de la tarea no puede contener números.");
            return;
    }

    if (notaStr.isEmpty()) {
        QMessageBox::critical(this, "Error", "Por favor ingresa la nota.");
        return;
    }

    if (nota < 0 || nota > 5) {
        QMessageBox::critical(this, "Error", "Por favor ingresa una nota válida (entre 0 y 5).");
            return;
    }

    if (tipoEntrega == 3 && (porcentaje <= 0 || porcentaje > 100)) {
        QMessageBox::critical(this, "Error", "Por favor ingresa un porcentaje válido (entre 0 y 100) para la entrega 'Otro'.");
            return;
    }

    if(sistemaAcademico.getEstudiantes()[posicion].agregarEntrega(nombre.toStdString(), nota, tipoEntrega)){
    if (tipoEntrega == 3 && !sistemaAcademico.getEstudiantes()[posicion].getEntregas().empty()) {
        sistemaAcademico.getEstudiantes()[posicion].getEntregas().back().setPorcentaje(porcentaje);
    }

    actualizarTablaEntregas(sistemaAcademico.getEstudiantes()[posicion].getEntregas());

    QMessageBox::information(this, "Éxito", "Tarea agregada exitosamente.");
    }
    else{
    QMessageBox::information(this, "Error","No agregue entregas repetidas");
    }
}

void MainWindow::on_cmdEliminarEntrega_clicked()
{
    int estudianteIndex = ui->cboEstudiantes->currentIndex();
    int entregaIndex = ui->tableEntregas->currentIndex().row();

    if (estudianteIndex >= 0 && entregaIndex >= 0)
    {
        if (estudianteIndex < sistemaAcademico.getEstudiantes().size())
        {
            if (entregaIndex < sistemaAcademico.getEstudiantes()[estudianteIndex].getEntregas().size())
            {
                Entrega entrega = sistemaAcademico.getEstudiantes()[estudianteIndex].getEntregas()[entregaIndex];
                sistemaAcademico.getEstudiantes()[estudianteIndex].eliminarEntrega(entrega);

                actualizarTablaEntregas(sistemaAcademico.getEstudiantes()[estudianteIndex].getEntregas());

                QMessageBox::information(this, "Éxito", "Entrega eliminada exitosamente.");
            }
        }
    }
}
