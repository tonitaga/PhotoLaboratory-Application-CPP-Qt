#include <QApplication>

#include "view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  PhotoLaboratoryView w;
  w.show();
  return a.exec();
}
