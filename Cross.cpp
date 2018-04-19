#include "Cross.h"
#include <QApplication>
#include <QColor>
#include <QColorDialog>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QSettings>
#include <utility>
#include "ActionCheckBox.h"
#include "ActionSlider.h"
#include "ActionWidgetHelper.h"
int Cross::getSi() const {
  return si;
}

void Cross::setSi(int value) {
  si = value;
}

void Cross::saveSetting() {
  QSettings setting("none", "Cross");
  setting.setValue("Cross/size", height());
  setting.setValue("Cross/borderSize", borderSize());
  setting.setValue("Cross/point", isDrawPoint());
  setting.setValue("Cross/si", getSi());
  setting.setValue("Cross/color", _bcolor);
  setting.setValue("Cross/alpha", _alpha);
}

void Cross::loadSetting() {
  QSettings setting("none", "Cross");
  drawPoint(setting.value("Cross/point", false).toBool());
  setSi(setting.value("Cross/si", false).toInt());
  int he = setting.value("Cross/size", 20).toInt();
  resize(he, he);
  _borderSize = setting.value("Cross/borderSize", 1).toInt();
  _bcolor = setting.value("Cross/color", QColor(Qt::red)).value<QColor>();
  _alpha = setting.value("Cross/alpha", 255).toInt();
}

void Cross::createMenu() {
  // Create color menu
  auto genColor = [this](QString nameColor, Qt::GlobalColor color) {
    auto action = new QAction(nameColor);
    QObject::connect(action, &QAction::triggered,
                     [this, color] { this->setColor(color); });
    return action;
  };
  QMenu* colorMenu = new QMenu("Color");
#define ADDCOLOR(X) colorMenu->addAction(genColor(#X, Qt::X))
  ADDCOLOR(red);
  ADDCOLOR(black);
  ADDCOLOR(white);
  ADDCOLOR(darkGray);
  ADDCOLOR(gray);
  ADDCOLOR(lightGray);
  ADDCOLOR(green);
  ADDCOLOR(blue);
  ADDCOLOR(cyan);
  ADDCOLOR(magenta);
  ADDCOLOR(yellow);
  ADDCOLOR(darkRed);
  ADDCOLOR(darkGreen);
  ADDCOLOR(darkBlue);
  ADDCOLOR(darkCyan);
  ADDCOLOR(darkMagenta);
  ADDCOLOR(darkYellow);
#undef ADDCOLOR
  colorMenu->addAction("*Costum", [this] {
    QColor color = QColorDialog::getColor(this->_bcolor);
    if (color.isValid()) {
      this->_bcolor = color;
      this->update();
    }
  });
  menu.addMenu(colorMenu);

  auto slider = new ActionSlider("Alpha");
  slider->getSlider()->setValue(_alpha);
  connect(slider->getSlider(), SIGNAL(valueChanged(int)), this,
          SLOT(setOpt(int)));
  menu.addAction(slider);
  // Add point

  auto pointAction = new ActionCheckBox("Point");
  pointAction->getRootWidget()->setChecked(isDrawPoint());
  connect(pointAction->getRootWidget(), &QCheckBox::stateChanged, this,
          &Cross::drawPoint);
  menu.addAction(pointAction);
  // Add Exit

  menu.addAction("Quit", [] { qApp->exit(); });
}

void Cross::windowDecor() {
  setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint |
                 Qt::FramelessWindowHint);
  setAttribute(Qt::WA_TranslucentBackground, true);
  setAttribute(Qt::WA_NoSystemBackground);
}

Cross::Cross(int h, int borderSize, const QColor& color, QWidget* parent)
    : QWidget(parent) {
  loadSetting();
  createMenu();
  windowDecor();

  if (h != -1 && h > 0) {
    resize(h, h);
  }
  if (borderSize != -1 && borderSize > 0) {
    _borderSize = borderSize;
  }
  if (color.isValid()) {
    _bcolor = color;
  }

  auto posWin = qApp->desktop()->availableGeometry().center();
  move(posWin.rx() - h / 2, posWin.ry() - h / 2);
}

void Cross::paintEvent(QPaintEvent* /*event*/) {
  QPainter p(this);
  p.setBackgroundMode(Qt::TransparentMode);
  p.setRenderHint(QPainter::Antialiasing);

  p.setPen(QPen(_bcolor, _borderSize, Qt::SolidLine));

  p.drawLine(width() / 2, 0, width() / 2, height() / 2 - si);
  p.drawLine(width() / 2, height() / 2 + si, width() / 2, height());
  p.drawLine(0, height() / 2, width() / 2 - si, height() / 2);
  p.drawLine(width() / 2 + si, height() / 2, width(), height() / 2);
  if (_bDrawPoint) {
    p.drawPoint(width() / 2, height() / 2);
  }
}

bool Cross::isDrawPoint() {
  return _bDrawPoint;
}

void Cross::mousePressEvent(QMouseEvent* event) {
  if (!isPressMouse) {
    if (event->button() == Qt::LeftButton) {
      coord = event->pos();
      isPressMouse = true;
    }
  }
}

void Cross::mouseReleaseEvent(QMouseEvent* event) {
  if (isPressMouse && event->button() == Qt::LeftButton) {
    isPressMouse = false;
  }

  if (event->button() == Qt::RightButton) {
    menu.move(QCursor::pos());
    menu.exec();
  }
}

void Cross::mouseMoveEvent(QMouseEvent* /*event*/) {
  if (isPressMouse) {
    auto globPosCurs = QCursor::pos();
    move(globPosCurs.rx() - coord.rx(), globPosCurs.ry() - coord.ry());
  }
}

void Cross::wheelEvent(QWheelEvent* event) {
  if (event->modifiers() & Qt::CTRL) {
    if (event->angleDelta().ry() > 0) {
      resize(width() + 1, height() + 1);
      update();
      return;
    }
    if (event->angleDelta().ry() < 0) {
      resize(width() - 1, height() - 1);
      update();
      return;
    }
  } else if (event->modifiers() & Qt::SHIFT) {
    if (event->angleDelta().ry() > 0) {
      if (si < height() / 2) {
        si++;
        update();
      }
      return;
    }
    if (event->angleDelta().ry() < 0) {
      if (si > 0) {
        si--;
        update();
      }
      return;
    }
  } else {
    if (event->angleDelta().ry() > 0) {
      if (_borderSize < height()) {
        _borderSize++;
        update();
      }
      return;
    }
    if (event->angleDelta().ry() < 0) {
      if (_borderSize > 0) {
        _borderSize--;
        update();
      }
      return;
    }
  }
}

void Cross::setColor(QColor c) {
  _bcolor = std::move(c);
  _bcolor.setAlpha(_alpha);
  update();
}

void Cross::setOpt(int i) {
  _alpha = i;
  _bcolor.setAlpha(_alpha);
  update();
}

void Cross::drawPoint(int b) {
  _bDrawPoint = b;
  update();
}

Cross::~Cross() {
  saveSetting();
}
