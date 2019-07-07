#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actiondakai_triggered();

    void on_actionbaocun_triggered();

    void on_actionxinjian_triggered();

    void on_actiontuichu_triggered();

    void on_actionchexiao_triggered();

    void on_actionfuzhi_triggered();

    void on_actionzhantie_triggered();

    void on_actionjianqie_triggered();

    void saveFile(const char * file, const char * buf);

    void on_actionbianji_triggered();

    void on_actionlingcunwei_triggered();

    void on_actionguanyu_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
