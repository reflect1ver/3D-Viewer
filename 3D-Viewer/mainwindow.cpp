#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../gif/gif.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    sliderSetup();
    connectSetup();
}





MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sliderSetup() {
  // Rotate
  ui->horizontalSlider_rotate_x->setRange(0, 360 * 16);
  ui->horizontalSlider_rotate_x->setSingleStep(16);
  ui->horizontalSlider_rotate_x->setPageStep(15 * 16);

  ui->horizontalSlider_rotate_y->setRange(0, 360 * 16);
  ui->horizontalSlider_rotate_y->setSingleStep(16);
  ui->horizontalSlider_rotate_y->setPageStep(15 * 16);

  ui->horizontalSlider_rotate_z->setRange(0, 360 * 16);
  ui->horizontalSlider_rotate_z->setSingleStep(16);
  ui->horizontalSlider_rotate_z->setPageStep(15 * 16);

  // Translate
  ui->horizontalSlider_moveX->setRange(-50, 50);
  ui->horizontalSlider_moveX->setSingleStep(20);

  ui->horizontalSlider_moveY->setRange(-50, 50);
  ui->horizontalSlider_moveY->setSingleStep(20);

  ui->horizontalSlider_moveZ->setRange(-100, 100);
  ui->horizontalSlider_moveZ->setSingleStep(30);

  // Scale
  ui->horizontalSlider_scale->setRange(1, 100);
  ui->horizontalSlider_scale->setSingleStep(30);
}

void MainWindow::connectSetup() {
  // Translate
  // TranslateX
  connect(ui->horizontalSlider_moveX, &QSlider::valueChanged, ui->OGLWidget,
          &GLWidget::setXTranslate);
  connect(ui->translate_x_num, SIGNAL(editingFinished()), (this),
          SLOT(xTranslateTextEdit()));
  // Translate Y
  connect(ui->horizontalSlider_moveY, &QSlider::valueChanged, ui->OGLWidget,
          &GLWidget::setYTranslate);
  connect(ui->translate_y_num, SIGNAL(editingFinished()), (this),
          SLOT(yTranslateTextEdit()));
  // Translate Z
  connect(ui->horizontalSlider_moveZ, &QSlider::valueChanged, ui->OGLWidget,
          &GLWidget::setZTranslate);
  connect(ui->translate_z_num, SIGNAL(editingFinished()), (this),
          SLOT(zTranslateTextEdit()));

  // Connecting slider translate to text
  connect(ui->horizontalSlider_moveX, &QSlider::valueChanged, (this),
          &MainWindow::xTranslateSliderValueChanged);
  connect(ui->horizontalSlider_moveY, &QSlider::valueChanged, (this),
          &MainWindow::yTranslateSliderValueChanged);
  connect(ui->horizontalSlider_moveZ, &QSlider::valueChanged, (this),
          &MainWindow::zTranslateSliderValueChanged);

  // Rotate
  // Rotate X
  connect(ui->horizontalSlider_rotate_x, &QSlider::valueChanged, ui->OGLWidget,
          &GLWidget::setXRotation);
  connect(ui->rotate_x_num, SIGNAL(editingFinished()), (this),
          SLOT(xRotateTextEdit()));
  // Rotate Y
  connect(ui->horizontalSlider_rotate_y, &QSlider::valueChanged, ui->OGLWidget,
          &GLWidget::setYRotation);
  connect(ui->rotate_y_num, SIGNAL(editingFinished()), (this),
          SLOT(yRotateTextEdit()));
  // Rotate Z
  connect(ui->horizontalSlider_rotate_z, &QSlider::valueChanged, ui->OGLWidget,
          &GLWidget::setZRotation);
  connect(ui->rotate_z_num, SIGNAL(editingFinished()), (this),
          SLOT(zRotateTextEdit()));

  // Connecting slider rotate to text
  connect(ui->horizontalSlider_rotate_x, &QSlider::valueChanged, (this),
          &MainWindow::xRotateValueChanged);
  connect(ui->horizontalSlider_rotate_y, &QSlider::valueChanged, (this),
          &MainWindow::yRotateValueChanged);
  connect(ui->horizontalSlider_rotate_z, &QSlider::valueChanged, (this),
          &MainWindow::zRotateValueChanged);

  // Scale
  connect(ui->horizontalSlider_scale, &QSlider::valueChanged, ui->OGLWidget,
        &GLWidget::setScale);
  connect(ui->scale_text, SIGNAL(editingFinished()), (this),
          SLOT(scaleTextEdit()));
  // Connecting slider scale to text
  connect(ui->horizontalSlider_scale, &QSlider::valueChanged, (this),
          &MainWindow::scaleSliderValueChanged);



  // Open file
  connect(ui->pushButton_openFile, SIGNAL(clicked()), this,
          SLOT(action_triggered()));

  // Создать GIF
    connect(ui->gif_button, SIGNAL(released()), (this),
            SLOT(createScreenshot()));
}


void MainWindow::defaultSliders() {

    ui->horizontalSlider_moveX->setValue(0);
    ui->horizontalSlider_moveY->setValue(0);
    ui->horizontalSlider_moveZ->setValue(0);

  ui->translate_x_num->setText(QString::number(0));
  ui->translate_y_num->setText(QString::number(0));
  ui->translate_z_num->setText(QString::number(0));

  ui->horizontalSlider_rotate_x->setValue(360 * 8);
  ui->horizontalSlider_rotate_y->setValue(360 * 8);
  ui->horizontalSlider_rotate_z->setValue(360 * 8);
  ui->rotate_x_num->setText(QString::number(0));
  ui->rotate_y_num->setText(QString::number(0));
  ui->rotate_z_num->setText(QString::number(0));

  ui->horizontalSlider_scale->setValue(1);
  ui->scale_text->setText(QString::number(1));
}


// Translate
void MainWindow::xTranslateSliderValueChanged(int value) {
  ui->translate_x_num->setText(QString::number(value - 50));
}
void MainWindow::yTranslateSliderValueChanged(int value) {
  ui->translate_y_num->setText(QString::number(value - 50));
}
void MainWindow::zTranslateSliderValueChanged(int value) {
  ui->translate_z_num->setText(QString::number(value - 50));
}
void MainWindow::xTranslateTextEdit() {
  int val = ui->translate_x_num->text().toInt();
  val += 50;
  ui->horizontalSlider_moveX->setValue(val);
}
void MainWindow::yTranslateTextEdit() {
  int val = ui->translate_y_num->text().toInt();
  val += 50;
  ui->horizontalSlider_moveY->setValue(val);
}
void MainWindow::zTranslateTextEdit() {
  int val = ui->translate_z_num->text().toInt();
  val += 50;
  ui->horizontalSlider_moveZ->setValue(val);
}

int valueNormalize(int val) {
  while (val > 180) {
    val -= 360;
  }
  while (val < -180) {
    val += 360;
  }
  return val;
}

void MainWindow::xRotateTextEdit() {
  int val = ui->rotate_x_num->text().toInt();
  val += 180;
  ui->horizontalSlider_rotate_x->setValue(val * 16);
  val = valueNormalize(val);
  ui->OGLWidget->setXRotation(val * 16);
}
void MainWindow::yRotateTextEdit() {
  int val = ui->rotate_y_num->text().toInt();
  val += 180;
  ui->horizontalSlider_rotate_y->setValue(val * 16);
  val = valueNormalize(val);
  ui->OGLWidget->setYRotation(val * 16);
}
void MainWindow::zRotateTextEdit() {
  int val = ui->rotate_z_num->text().toInt();
  val += 180;
  ui->horizontalSlider_rotate_z->setValue(val * 16);
  val = valueNormalize(val);
  ui->OGLWidget->setZRotation(val * 16);
}

// Rotate
void MainWindow::xRotateValueChanged(int value) {
  ui->rotate_x_num->setText(QString::number(-180 + value / 16));
}
void MainWindow::yRotateValueChanged(int value) {
  ui->rotate_y_num->setText(QString::number(-180 + value / 16));
}
void MainWindow::zRotateValueChanged(int value) {
  ui->rotate_z_num->setText(QString::number(-180 + value / 16));
}


void MainWindow::scaleSliderValueChanged(int value) {
  ui->scale_text->setText(QString::number(value));
}
void MainWindow::scaleTextEdit() {
  int val = ui->scale_text->text().toInt();
  ui->horizontalSlider_scale->setValue(val);

}


void MainWindow::action_triggered() {
  QFileDialog *fileDialog = new QFileDialog(this);
  if (fileDialog) {
    fileDialog->setWindowTitle(tr("Choose .obj-file"));
    fileDialog->setNameFilter(tr("(*.obj)"));
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    QStringList fileNames;
    if (fileDialog->exec()) {
      fileNames = fileDialog->selectedFiles();
      if (fileNames.size() > 0) {
        QString fileName = fileNames.at(0);
        QByteArray ba = fileName.toLocal8Bit();
        char *input = ba.data();
        FreeMemory(&ui->OGLWidget->data);
        int a = Parser(&ui->OGLWidget->data, input);
        if (a == 0) {
          printf("ok\n");
          setWindowTitle(fileName);
          ui->statusbar->showMessage("Path: " + fileName);
          ui->edges->setText(
              QString::number(ui->OGLWidget->data.count_of_facets));
          ui->vertices->setText(
              QString::number(ui->OGLWidget->data.count_of_vertex));
          defaultSliders();
        } else {
          printf("error\n");
          FreeMemory(&ui->OGLWidget->data);
        }
      }
    }
    delete fileDialog;
  } else {
    printf("error!\n");
  }

  ui->OGLWidget->update();
}


void MainWindow::on_bmp_button_clicked() {
  QFileDialog dialogPhoto(this);
  QDateTime dateTime = dateTime.currentDateTime();
  QString currentDateTime = dateTime.toString("dd.MM.yy_HH.mm.ss_zzz");
  QString name_photo = dialogPhoto.getSaveFileName(
      this, "Save as...", "Screenshot_" + currentDateTime,
      "BMP (*.bmp);; JPEG (*.jpeg)");
  ui->OGLWidget->grabFramebuffer().save(name_photo);
}



void MainWindow::createScreenshot() {
  QPushButton *btn = (QPushButton *)sender();
  QString butVal = btn->text();

  QDir *pathDir = new QDir();
  pathDir->mkdir(pathProject);
  pathDir->mkdir(pathProject + "/screenshots");

  QDateTime dateTime = dateTime.currentDateTime();
  QString currentDateTime = dateTime.toString("yyyy_MM_dd_HHmmss_zzz");

  if (QString::compare(butVal, "bmp", Qt::CaseInsensitive) == 0) {
    ui->OGLWidget->grab().save(pathProject + "screenshots/" + currentDateTime +
                               ".bmp");
  } else if (QString::compare(butVal, "jpg", Qt::CaseInsensitive) == 0) {
    ui->OGLWidget->grab().save(pathProject + "screenshots/" + currentDateTime +
                               ".jpg");
  } else if (QString::compare(butVal, "gif", Qt::CaseInsensitive) == 0) {
    ui->gif_button->setEnabled(false);
    pathDir->mkdir(pathProject + "/screenshots/gif_obj/");
    startTime = 0, tmpTime = 1000 / GifFps;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(oneGif()));
    timer->start(1000 / GifFps);
  }
}

void MainWindow::oneGif() {
  if (startTime == tmpTime) {
    ui->OGLWidget->grab()
        .scaled(640, 480, Qt::IgnoreAspectRatio)
        .save(pathProject + "/screenshots/gif_obj/" + QString::number(counter) +
              ".bmp");
    counter++;
    tmpTime += 1000 / GifFps;
  }
  if (startTime == 1000 * GifLength) {
    createGif();
    timer->stop();
    counter = 1;
  }
  startTime += 1000 / GifFps;
}

void MainWindow::createGif() {
  QDir pathFile;
  QDateTime dateTime = dateTime.currentDateTime();
  QString currentDateTime = dateTime.toString("yyyy_MM_dd_HHmmss_zzz");
  QString gif_name = pathProject + "/screenshots/" + currentDateTime + ".gif";
  QByteArray ga = gif_name.toLocal8Bit();
  GifWriter writer = {};
  int err = 0;

  if (GifBegin(&writer, ga.data(), 640, 480, 10, 8, false)) {
    for (int i = 1; i <= 50; i++) {
      if (err == 1) {
        break;
      }
      QImage img(pathProject + "/screenshots/gif_obj/" + QString::number(i) +
                 ".bmp");
      if (!img.isNull()) {
        if (GifWriteFrame(&writer,
                          img.convertToFormat(QImage::Format_Indexed8)
                              .convertToFormat(QImage::Format_RGBA8888)
                              .constBits(),
                          640, 480, 10, 8, false)) {
        } else {
          err = 1;
        }
      } else {
        err = 1;
      }
    }
    if (err == 0) {
      GifEnd(&writer);
    }
  } else {
    err = 1;
  }

  if (err == 1) {
    if (QFile::exists(gif_name)) {
      QFile::remove(gif_name);
    }
  }

  pathFile.setPath(pathProject + "/screenshots/gif_obj/");
  pathFile.removeRecursively();
  ui->gif_button->setEnabled(true);
}
