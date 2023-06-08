#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdlib.h>

#include <QColor>
#include <QColorDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QSettings>
#include <QTimer>
#include <cstring>

#include "glwidget.h"

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
      void xTranslateTextEdit();
      void yTranslateTextEdit();
      void zTranslateTextEdit();

      void xRotateTextEdit();
      void yRotateTextEdit();
      void zRotateTextEdit();

      void scaleTextEdit();

      void xTranslateSliderValueChanged(int value);
      void yTranslateSliderValueChanged(int value);
      void zTranslateSliderValueChanged(int value);

      void xRotateValueChanged(int value);
      void yRotateValueChanged(int value);
      void zRotateValueChanged(int value);

      void scaleSliderValueChanged(int value);


      void action_triggered();

      void on_bmp_button_clicked();

      void oneGif();
      void createScreenshot();

     private:
      Ui::MainWindow *ui;
      QString settingFile;
      QTimer *timer;
      const int GifFps = 10, GifLength = 5;
      int startTime, tmpTime;
      QImage *gifImage;
      int gifTime = 0;
      void connectSetup();
      void sliderSetup();
      int counter = 1;
      void createGif();
      void defaultSliders();
      QString pathProject = QDir::homePath() + "/3D-Viewer/";
    };
#endif // MAINWINDOW_H
