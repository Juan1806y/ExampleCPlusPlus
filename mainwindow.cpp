#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    sistemaAcademico.agregarEstudiante(codigo, nombre.toStdString());

    actualizarTablaEstudiantes(sistemaAcademico.getEstudiantes());
    actualizarComboBox(sistemaAcademico.getEstudiantes());
}


void MainWindow::actualizarTablaEstudiantes(const std::vector<Estudiante>& estudiantes)
{
    tableModel->clear();

    tableModel->setHorizontalHeaderLabels({"Código", "Nombre"});

        for (const auto& estudiante : estudiantes)
    {
        QList<QStandardItem*> rowItems;
        rowItems.append(new QStandardItem(QString::number(estudiante.getCodigo())));
        rowItems.append(new QStandardItem(QString::fromStdString(estudiante.getNombre())));
        tableModel->appendRow(rowItems);
    }
}

void MainWindow::actualizarTablaEntregas(const std::vector<Entrega>& entregas){
    tableModel2->clear();
    tableModel2->setHorizontalHeaderLabels({"Nombre Actividad", "Nota", "Porcentaje %"});

    for (const auto& entrega : entregas) {
        QList<QStandardItem*> rowItems;
        QStandardItem* nombreItem = new QStandardItem(QString::fromStdString(entrega.getNombre()));
        QStandardItem* notaItem = new QStandardItem(QString::number(entrega.getNota()));
        QStandardItem* porcentajeItem = new QStandardItem(QString::number(entrega.getPorcentaje()));

        rowItems.append(nombreItem);
        rowItems.append(notaItem);
        rowItems.append(porcentajeItem);

        tableModel2->appendRow(rowItems);
    }
}


void MainWindow::actualizarComboBox(const std::vector<Estudiante>& estudiantes)
{
    ui->cboEstudiantes->clear();

    for (const auto& estudiante : estudiantes)
    {
        ui->cboEstudiantes->addItem(QString::fromStdString(estudiante.getNombre()));
    }
}

void MainWindow::on_cboEstudiantes_currentIndexChanged(int index)
{
    const std::vector<Estudiante>& estudiantes = sistemaAcademico.getEstudiantes();
    if (index >= 0 && index < estudiantes.size()) {
        actualizarTablaEntregas(estudiantes[index].getEntregas());
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
    }

}


void MainWindow::on_cboEntregas_currentIndexChanged(int index)
{
    if(index == 0){
        ui->txtPorcentaje->setText("10");
        ui->txtPorcentaje->setEnabled(false);
    }else if(index == 1){
        ui->txtPorcentaje->setText("15");
        ui->txtPorcentaje->setEnabled(false);
    }else if(index == 2){
        ui->txtPorcentaje->setText("30");
        ui->txtPorcentaje->setEnabled(false);
    }else{
        ui->txtPorcentaje->setText("");
        ui->txtPorcentaje->setEnabled(true);
    }

}

void MainWindow::on_cmdAgregarTarea_clicked()
{
    QString nombre = ui->txtNombreTarea->text();
    double nota = ui->txtNota->text().toDouble();
    double porcentaje = ui->txtPorcentaje->text().toDouble();

    const std::vector<Estudiante>& estudiantes = sistemaAcademico.getEstudiantes();
    const Estudiante& estudiante = estudiantes[ui->cboEstudiantes->currentIndex()];

    int tipoEntrega = ui->cboEntregas->currentIndex();
    estudiante.agregarEntrega(nombre.toStdString(), nota, tipoEntrega);
    const std::vector<Entrega>& entregasEstudiante = estudiante.getEntregas();

    if (tipoEntrega == 3) {
        const Entrega& entrega = entregasEstudiante.back();
        entrega.setPorcentaje(porcentaje);
    }

    actualizarTablaEntregas(entregasEstudiante);
}


void MainWindow::on_cmdEliminarDepartamento_clicked()
{

}

