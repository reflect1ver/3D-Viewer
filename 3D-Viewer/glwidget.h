#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QOpenGLWidget>
#include <QObject>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPushButton>
#include <algorithm>
#include <cstring>

extern "C" {
    #include "../3D_Viewer.h"
}

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT

private:
      float hwidth, hheight;
      double max_coord;
      QPoint mPos;
      double xS = 1;
      double yS = 1;
      double zS = 1;
      QPoint mPos_old;
      double xRot_old;
      double yRot_old;

      double x_pos_old;
      double y_pos_old;
      double z_pos_old;

      double x_rot_old;
      double y_rot_old;
      double z_rot_old;

      double scale_old;

      double lineWidth;
      double vertex_size;
      int line_type;
      int vertex_type;
      int projection_type;

      double scaleFactorX, scaleFactorY, scaleFactorZ, scaleVal;
      double xMov, yMov, zMov;
      double xRot, yRot, zRot;

      double rColor, gColor, bColor;
      double rBackColor, gBackColor, bBackColor;
      double vertex_color_red, vertex_color_green, vertex_color_blue;

      double x_min, x_max;
      bool mouse_released_flag;

public slots:
    void setXTranslate(int step);
    void setYTranslate(int step);
    void setZTranslate(int step);

    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    void setScale(int scale);
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();
    void initializeGL() override;
    void paintGL() override;
    void pointDrawing(int c);
    void setupPerspective();
    void lineDrawing();
    void mousePressEvent(QMouseEvent* mouse) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent* mouse) override;
      void wheelEvent(QWheelEvent *) override;
    void resizeGL(int w, int h) override;
    data_t data;
};

#endif // GLWIDGET_H
