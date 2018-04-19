#ifndef ICON_H
#define ICON_H
#include <QMenu>
#include <QWidget>
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;      \
  void operator=(const TypeName&) = delete;
class Cross : public QWidget {
  Q_OBJECT
  DISALLOW_COPY_AND_ASSIGN(Cross)

  int m_keyCode_l;
  int _alpha;
  QColor _bcolor;
  QMenu menu;
  int _borderSize;
  int si = 2;
  bool _bDrawPoint = false;

  bool isPressMouse = false;
  QPoint coord;

  void saveSetting();
  void loadSetting();
  void createMenu();
  void windowDecor();

 public:
  Cross(int h = -1,
        int borderSize = -1,
        const QColor& color = {},
        QWidget* parent = nullptr);

 protected:
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;

 public slots:
  void setColor(QColor c);
  void setOpt(int i);
  void drawPoint(int b);

 signals:

 public:
  int getSi() const;
  void setSi(int value);
  bool isDrawPoint();
  QColor getColor() { return _bcolor; }
  int borderSize() { return _borderSize; }
  ~Cross() override;
};

#endif  // ICON_H
