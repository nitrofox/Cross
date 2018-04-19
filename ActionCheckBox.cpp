#include <utility>

#include <QHBoxLayout>
#include <QLabel>
#include "ActionCheckBox.h"
ActionCheckBox::ActionCheckBox(QString name) : QWidgetAction(nullptr) {
  rootWidget = new QCheckBox(name);

  setDefaultWidget(rootWidget);
}

QCheckBox* ActionCheckBox::getRootWidget() {
  return rootWidget;
}
