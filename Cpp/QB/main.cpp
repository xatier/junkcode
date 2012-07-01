#include <cstdio>
#include <Qt>
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QPalette>
#include <QBrush>
#include <QBitmap>
#include <QKeyEvent>
#include <QtDebug>
#include <unistd.h>

#define N 3
#define SPEED 200000

class QB : public QWidget {
public:
    QB (QWidget *parent = NULL);
    int dir;
    int df;
    int dfx;

protected:
    void paintEvent (QPaintEvent *event);
    void mouseEvent (QMouseEvent *event);
    void keyPressEvent (QKeyEvent *event);

private:
    void change(void);
    void erase(void);
    void calcXY(int &, int &);
};

QB::QB (QWidget *parent) : QWidget(parent) {
    df = 1;
    dfx = N;
    dir = 1;
    setGeometry(500, 200, 335, 335);
    activateWindow();
    setWindowFlags(this->windowFlags() | Qt::SplashScreen);
}

void QB::paintEvent (QPaintEvent *event) {
    this->dfx = this->df;
    this->df++;
    if (this->df > N)
      this->df = 1;

    this->change();
    this->update();
}

void QB::calcXY (int &x, int &y) {
  x += -this->dir*3;
  y += this->dir*3;
}

void QB::erase (void)
{
    QPainter painter(this);
    painter.setBrush(QBrush(this->backgroundRole()));
    painter.drawRect(0, 0, this->width(), this->height());
}
/*
void QB::change (void) {
    this->clearMask();
    char filename[50];
    std::sprintf(filename, "./SRC/img/shime%d.png", this->df);
    QPixmap pixImg(filename);
    char filenameX[50];
    std::sprintf(filenameX, "./SRC/img/shime%d.png", 10 - this->df);
    QPixmap pixImgX(filenameX);
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(pixImg));
    this->setPalette(palette);
    this->setFixedSize(pixImg.size());
    this->setMask(pixImgX.mask());
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixImg);

    int x = this->x(), y = this->y();
    this->calcXY(x, y);
    this->move(x, y);

    this->update();
    this->activateWindow();
    usleep(700000);
}
*/

void QB::change (void) {
    //this->clearMask();

    char filename[50];
    std::sprintf(filename, "./SRC/img/shime%d.png", this->df);
    QPixmap pixImg(filename);

    char filenameX[50];
    std::sprintf(filenameX, "./SRC/img/shime%d.png", this->dfx);
    QPixmap pixImgX(filenameX);

    QPalette palette;
    QPainter painter(this);

    palette.setBrush(this->backgroundRole(), QBrush(pixImg));
    this->setPalette(palette);
    this->setFixedSize( pixImgX.size() );
    this->erase();
    this->setMask(pixImg.mask());
    painter.setBackgroundMode(Qt::TransparentMode);
    painter.drawPixmap(0, 0, pixImg);

    int x = this->x(), y = this->y();
    this->calcXY(x, y);
    this->move(x, y);
    this->update();
    this->activateWindow();
    usleep(SPEED);
}

/*
void QB::mouseEvent (QMouseEvent *event) {
    setMouseTracking(true);
    if (event->buttons() == Qt::LeftButton) {
      qDebug() << "Right ";
            this->change();
    }
}
*/

void QB::keyPressEvent (QKeyEvent *event) {
    int k = event->key();
    if (k == Qt::Key_Space) {
      this->~QB();
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QB qb;
    qb.show();
    return app.exec();
}
