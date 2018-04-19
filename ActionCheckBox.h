#ifndef H_GUARD_CHECKBOX
#define H_GUARD_CHECKBOX
#include <QCheckBox>
#include <QWidgetAction>

class ActionCheckBox : public QWidgetAction {
  QCheckBox* rootWidget;

 public:
  ActionCheckBox(QString name);
  QCheckBox* getRootWidget();
};
#endif
