#include <utility>

#include <QHBoxLayout>
#include <QLabel>
#include "ActionSlider.h"
ActionSlider::ActionSlider(QString name)
    : _title(std::move(name)), QWidgetAction(nullptr) {
  QWidget* widget = new QWidget;
  auto layout = new QHBoxLayout;
  auto label = new QLabel(_title);
  slider = new QSlider(Qt::Horizontal);
  slider->setRange(1, 255);
  layout->addWidget(label);
  layout->addWidget(slider);
  widget->setLayout(layout);

  setDefaultWidget(widget);
}

QSlider* ActionSlider::getSlider() {
  return slider;
}
