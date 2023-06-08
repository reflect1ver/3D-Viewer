#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    xS = 1;
    yS = 1;
    zS = 1;
    xMov = 0;
    yMov = 0;
    zMov = 0;
    xRot = 0;
    yRot = 0;
    zRot = 0;
    mouse_released_flag = 0;
    xRot_old = 0;
    yRot_old = 0;
    x_pos_old = 0;
    y_pos_old = 0;
    z_pos_old = 0;

    x_rot_old = 0;
    y_rot_old = 0;
    z_rot_old = 0;

    scale_old = 1;
}

GLWidget::~GLWidget() { FreeMemory(&data); }

void GLWidget::initializeGL()
{
    glClearColor(0.2, 0.5, 0.2, 1);
    glEnable(GL_DEPTH_TEST);
}

void GLWidget::paintGL()
{
    if (data.array) {
            double *massiv = data.array;
            glClearColor(1, 1, 1, 0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_PROJECTION);  // Инициализация матрицы проекции
            glLoadIdentity();  // Сброс матрицы проекции
            glOrtho(-1 *data.max_coord, 1 * data.max_coord, -1 * data.max_coord, 1 * data.max_coord,
                        -1 * data.max_coord,
                        1 * data.max_coord);
            glScaled(xS, yS, zS);
            glTranslated(xMov, yMov, zMov);

            glRotated(xRot, 1, 0, 0);
            glRotated(yRot, 0, 1, 0);  // от этих функций зависит кручение-верчение объектовю
            glRotated(zRot, 0, 0, 1);

            glMatrixMode(GL_MODELVIEW);  // Инициализация матрицы модели
            glLoadIdentity();  // Сброс матрицы вида модели

            glVertexPointer(3, GL_DOUBLE, 0, massiv);
            glEnableClientState(GL_VERTEX_ARRAY);
            pointDrawing(data.count_of_vertex);
            lineDrawing();
            glDisableClientState(GL_VERTEX_ARRAY);
    }
}

void GLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
}

void GLWidget::pointDrawing(int c) {
    glColor3d(0, 0, 0);
    glPointSize(1);
    glDrawArrays(GL_POINTS, 1, c);
}

void GLWidget::lineDrawing() {
  glColor3d(1, 0, 0);
  glLineWidth(2);
  int* i;
  for (int k = 1; k <= data.count_of_facets; k++) {
    i = data.doubled_polygons[k].vertexes;
    glDrawElements(GL_LINES, data.doubled_polygons[k].number_of_vertexes_in_facets, GL_UNSIGNED_INT, i);
  }
}

void GLWidget::mousePressEvent(QMouseEvent* mouse) { mPos = mouse->pos(); }

void GLWidget::mouseReleaseEvent(QMouseEvent*) {
  mPos_old = mPos;
  mouse_released_flag = 1;
  xRot_old = xRot;
  yRot_old = yRot;
}

void GLWidget::mouseMoveEvent(QMouseEvent* mouse) {
  if (!mouse_released_flag) {
    xRot = 1 / M_PI * (mouse->pos().y() - mPos.y()) + xRot_old;
    yRot = 1 / M_PI * (mouse->pos().x() - mPos.x()) + yRot_old;
    xRot_old = 0;
    yRot_old = 0;
    update();
  } else {
    mPos.setY(mouse->pos().y());
    mPos.setX(mouse->pos().x());
    mouse_released_flag = 0;
  }
}

void GLWidget::wheelEvent(QWheelEvent* event) {
  if (event->angleDelta().y() > 0) {
    xS *= 0.9;
    yS *= 0.9;
    zS *= 0.9;
  } else {
    xS *= 1.1;
    yS *= 1.1;
    zS *= 1.1;
  }

  update();
}
void GLWidget::setXTranslate(int step) {
  if (step != xMov) {
    xMov = step;
    Move_X(&data.matrix_3d, 0.05 * (50 - xMov));
    x_pos_old = xMov;
    update();
  }
}
void GLWidget::setYTranslate(int step) {
  if (step != yMov) {
    yMov = step;
    Move_Y(&data.matrix_3d, 0.05 * (50 - yMov));
    y_pos_old = yMov;
    update();
  }
}
void GLWidget::setZTranslate(int step) {
  if (step != zMov) {
    zMov = step;
    Move_Z(&data.matrix_3d, 0.05 * (50 - zMov));
    z_pos_old = zMov;
    update();
  }
}

static void qNormalizeAngle(int &angle) {
  while (angle < 0) angle += 360 * 16;
  while (angle > 360 * 16) angle -= 360 * 16;
}
void GLWidget::setXRotation(int angle) {
  qNormalizeAngle(angle);
  if (angle != xRot) {
    xRot = angle;
    Rotate_By_Ox(&data.matrix_3d, -(180.0 - xRot / 16.0));
    x_rot_old = xRot;
    update();
  }
}
void GLWidget::setYRotation(int angle) {
  qNormalizeAngle(angle);
  if (angle != yRot) {
    yRot = angle;
    Rotate_By_Oy(&data.matrix_3d, -(180.0 - yRot / 16.0));
    y_rot_old = yRot;
    update();
  }
}
void GLWidget::setZRotation(int angle) {
  qNormalizeAngle(angle);
  if (angle != zRot) {
    zRot = angle;
    Rotate_By_Oz(&data.matrix_3d, -(180.0 - zRot / 16.0));
    z_rot_old = zRot;
    update();
  }
}
void GLWidget::setScale(int scale) {
  if (scale != scaleVal) {
    scaleVal = scale;
    Scale(&data.matrix_3d, fabs(scale / 1000.0f));
    scale_old = scaleVal;
    xS = scale;
    yS = scale;
    zS = scale;
    update();
  }
}
