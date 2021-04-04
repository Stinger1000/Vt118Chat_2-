#include "uiChat.h"
#include "ui_uiChat.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_thread(new QThread(this))
    , m_main_controller(new MainController(nullptr))

{
    ui->setupUi(this);
    setWindowTitle(QString("VT-118 Chat"));
    CorrectWid();

    m_main_controller->moveToThread(m_thread);
    connect(m_thread, &QThread::finished, m_main_controller,
        &MainController::deleteLater);
    // connections to main
    connect(m_main_controller, &MainController::NewMes, this, &MainWindow::AddMes, Qt::QueuedConnection);
    //
    m_thread->start();
}

MainWindow::~MainWindow()
{
    m_thread->quit();
    m_thread->wait();
    delete m_thread;
    //delete m_main_controller;

    delete ui;
}

void MainWindow::CorrectWid()
{
    ui->grbUsers->setMaximumWidth(200);
}

void MainWindow::AddMes(const QString& name, const QString& mes)
{
    if (ui->lstMes->count() > 200)
        ui->lstMes->removeItemWidget(ui->lstMes->item(ui->lstMes->count() - 1));
    ui->lstMes->addItem(name + ": " + mes);
}

void MainWindow::UpdateUsers(const QVector<QString>& users)
{
    ui->lstUsers->clear();
    for (auto i : users)
        ui->lstUsers->addItem(i);
}

void MainWindow::SetName(const QString& name)
{
    ui->lblName->setText(name);
}
