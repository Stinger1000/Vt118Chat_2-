#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MainController.h"
#include "Protocol.h"

#include <QMainWindow>
#include <QString>
#include <QThread>
#include <QValidator>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void CorrectWid();
    void SetName(const QString& name);

signals:
    void Registration(const QByteArray& login, const QByteArray& pass);
    void Loging(const QByteArray& login, const QByteArray& pass);
    void SendMesDefault(const QByteArray& data);
    void SetIP(const QString& ip);

public slots:
    void AddMes(const QString& name, const QString& mes);
    void UpdateUsers(const QStringList& users);
    void SetStatusSocket(const bool status);
    void ResponseRegLog(const uint8_t reg_or_log, const bool status);

private slots:
    void on_btnRegistration_clicked();

    void on_btnInAc_clicked();

    void on_btnSendText_clicked();

    void on_btnSetIP_clicked();

private:
    Ui::MainWindow* ui;

    QString m_my_name;

    QThread*        m_thread { nullptr };
    MainController* m_main_controller { nullptr };
};
#endif // MAINWINDOW_H
