#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char** argv)
{
  QApplication application(argc,argv);

  application.setOrganizationDomain("geometryfactory.com");
  application.setOrganizationName("GeometryFactory");
  application.setApplicationName("Surface mesher Qt4 demo");

  MainWindow w;

  if(argc>1)
    w.surface_open(argv[1]);

  w.show();

  return application.exec();
  std::cerr << "Exit\n";
}
