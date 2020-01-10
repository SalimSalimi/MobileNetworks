#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGui>
#include <QtCore>
#include <hexagone.h>
#include <vector>
using namespace std;
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   void  RemplirPaire();
       void RemplirImpaire();
        void RemplirPolygonesPaire();
       void RemplirPolygonesImpaire();

private:
    Ui::MainWindow *ui;

protected:
//   void paintEvent(QPaintEvent *e);

};
#endif // MAINWINDOW_H
