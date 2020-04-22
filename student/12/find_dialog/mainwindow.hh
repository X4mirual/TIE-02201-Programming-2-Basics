#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <fstream>
#include <QDebug>
#include <algorithm>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_fileLineEdit_textChanged(const QString &arg1);

    void on_keyLineEdit_textChanged(const QString &arg1);

    void on_findPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString file_name;
    QString find_what;
};

#endif // MAINWINDOW_HH
