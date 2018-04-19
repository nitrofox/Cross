#ifndef H_GUARD_ACTIONSLIDER
#define H_GUARD_ACTIONSLIDER
#include <QSlider>
#include <QWidgetAction>

class ActionSlider : public QWidgetAction {
  QString _title;
  QSlider* slider;

 public:
  ActionSlider(QString name);
  QSlider* getSlider();
};
#endif
