#ifndef H_GUARD_ACTIONWIDGETHELPER
#define H_GUARD_ACTIONWIDGETHELPER
#include <QWidgetAction>
template <class T>
class ActionWidgetHelper : public QWidgetAction {
  using Type = T;
  T* rootWidget;

 public:
  ActionWidgetHelper() { rootWidget = new T; }
  T* getRootWidget();
};
#endif
