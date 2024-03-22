#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void refreshScene(QGraphicsScene *scene); // Declaration of the refreshScene function
    void onButtonClicked(QGraphicsScene *scene);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
