#include <QApplication>
#include "Cross.h"
int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  Cross rbox;
  rbox.show();
  return a.exec();
}
