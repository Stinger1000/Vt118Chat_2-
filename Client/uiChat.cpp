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
    connect(m_main_controller, &MainController::StatusSocket, this, &MainWindow::SetStatusSocket, Qt::QueuedConnection);
    connect(this, &MainWindow::Registration, m_main_controller, &MainController::Registration, Qt::QueuedConnection);
    connect(this, &MainWindow::Loging, m_main_controller, &MainController::Loging, Qt::QueuedConnection);
    connect(this, &MainWindow::SendMesDefault, m_main_controller, &MainController::SendMes, Qt::QueuedConnection);
    connect(this, &MainWindow::SetIP, m_main_controller, &MainController::SetIP, Qt::QueuedConnection);

    connect(m_main_controller, &MainController::ResponseRegLog, this, &MainWindow::ResponseRegLog, Qt::QueuedConnection);
    connect(m_main_controller, &MainController::NewMesChat, this, &MainWindow::AddMes, Qt::QueuedConnection);
    connect(m_main_controller, &MainController::ClientsList, this, &MainWindow::UpdateUsers, Qt::QueuedConnection);
    //
    m_thread->start();

    QRegExp ipRegEx("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
                    "(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    auto*   ipValid = new QRegExpValidator(ipRegEx, this);
    ui->lneIP->setValidator(ipValid);
}

MainWindow::~MainWindow()
{
    m_thread->quit();
    m_thread->wait();
    delete m_thread;
    //delete m_main_controller;

    delete ui;
}

/**
 * @brief Correction size widget
 */
void MainWindow::CorrectWid()
{
    ui->grbUsers->setMaximumWidth(200);
}

/**
 * @brief Add message in window
 * @param name - name
 * @param mes - message from user
 */
void MainWindow::AddMes(const QString& name, const QString& mes)
{
    if (ui->lstMes->count() > 200)
        ui->lstMes->removeItemWidget(ui->lstMes->item(ui->lstMes->count() - 1));
    ui->lstMes->addItem(QString(name + ": " + mes));
}

/**
 * @brief Update list users
 * @param users - list users
 */
void MainWindow::UpdateUsers(const QStringList& users)
{
    ui->lstUsers->clear();
    for (auto i : users)
        ui->lstUsers->addItem(i);
}

/**
 * @brief Set my login
 * @param name - my login
 */
void MainWindow::SetName(const QString& name)
{
    ui->lblName->setText(name);
}

/**
 * @brief Set Status socket
 * @param status - status socket
 */
void MainWindow::SetStatusSocket(const bool status)
{
    if (status) {
        ui->lblStatus->setText("Online");
    } else {
        ui->lblStatus->setText("Offline");
    }
}

/**
 * @brief Response server on registration or loging
 * @param reg_or_log - registation or loging(1 - loging)
 * @param status - status(0 - succesfully)
 */
void MainWindow::ResponseRegLog(const uint8_t reg_or_log, const bool status)
{
    if (reg_or_log) {
        //Логирование
        if (!status) {
            SetName(m_my_name);
            QMessageBox::information(this, "Успешно", "Успешный вход в систему");
        } else {
            QMessageBox::warning(this, "Ошибка", "Неудачный вход в систему(возможно вы уже вошли в систему или вы ввели некорректные данные)");
        }
    } else {
        //Регистрация
        if (!status) {
            SetName(m_my_name);
            QMessageBox::information(this, "Успешно", "Успешная регистрация");
        } else {
            QMessageBox::warning(this, "Ошибка", "Неудачная регистрация(возможно вы уже вошли в систему или вы ввели некорректные данные)");
        }
    }
}

void MainWindow::on_btnRegistration_clicked()
{
    auto login = QStingToQByteArray(ui->lneLogin->text());
    auto pass  = QStingToQByteArray(ui->lnePass->text());

    if (login.isEmpty() || pass.isEmpty()) {
        QMessageBox::information(this, QObject::tr("Error"),
            "Некорректные данные, "
            "пожалуйста введите заново");
        return;
    }

    emit Registration(login, pass);

    m_my_name = ui->lneLogin->text();
}

void MainWindow::on_btnInAc_clicked()
{
    auto login = QStingToQByteArray(ui->lneLogin->text());
    auto pass  = QStingToQByteArray(ui->lnePass->text());

    if (login.isEmpty() || pass.isEmpty()) {
        QMessageBox::information(this, QObject::tr("Error"),
            "Некорректные данные, "
            "пожалуйста введите заново");
        return;
    }

    emit Loging(login, pass);

    m_my_name = ui->lneLogin->text();
}

void MainWindow::on_btnSendText_clicked()
{
    auto data = QStingToQByteArray(ui->lneUserText->text());
    emit SendMesDefault(data);
    ui->lneUserText->clear();
}

void MainWindow::on_btnSetIP_clicked()
{
    if ((ui->lneIP->text().count('.') != 3)
        || (ui->lneIP->text().right(1) == ".")) {
        QMessageBox::information(this, QObject::tr("Error"),
            "Некорректные данные, "
            "пожалуйста введите заново");
        return;
    }
    emit SetIP(ui->lneIP->text());
}
