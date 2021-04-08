#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MainController.h"
#include <QMainWindow>
#include <QThread>

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
    void GetAccess();

public slots:
    void AddMes(const QString& name, const QString& mes);
    void UpdateUsers(const QVector<QString>& users);
    void SetName(const QString& name);
    void SetStatusSocket(const bool status);

private:
    Ui::MainWindow* ui;

    QThread*        m_thread { nullptr };
    MainController* m_main_controller { nullptr };
};
#endif // MAINWINDOW_H
