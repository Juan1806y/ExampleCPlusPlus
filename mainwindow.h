#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include "SistemaAcademico.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_cmdAgregarEstudiante_clicked();

    void on_cboEstudiantes_currentIndexChanged(int index);

    void on_cmdEliminarEstudiante_clicked();

    void on_cboEntregas_currentIndexChanged(int index);

    void on_cmdAgregarTarea_clicked();

    void on_cmdEliminarDepartamento_clicked();

private:
    Ui::MainWindow *ui;
    void actualizarTablaEstudiantes(const std::vector<Estudiante>& estudiantes);
    void actualizarTablaEntregas(const std::vector<Entrega>& entregas);
    void actualizarComboBox(const std::vector<Estudiante>& estudiantes);
    SistemaAcademico sistemaAcademico;
    QStandardItemModel *tableModel;
    QStandardItemModel *tableModel2;
};
#endif // MAINWINDOW_H
