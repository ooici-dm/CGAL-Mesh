#include "config.h"
#include "Point_set_scene_item.h"
#include "Polyhedron_demo_plugin_helper.h"
#include "Polyhedron_demo_plugin_interface.h"

#include <CGAL/pca_estimate_normals.h>
#include <CGAL/jet_estimate_normals.h>
#include <CGAL/mst_orient_normals.h>
#include <CGAL/Timer.h>
#include <CGAL/Memory_sizer.h>

#include <QObject>
#include <QAction>
#include <QMainWindow>
#include <QApplication>
#include <QtPlugin>
#include <QInputDialog>
#include <QMessageBox>

#include "ui_PS_demo_normal_estimation_plugin.h"

class PS_demo_normal_estimation_plugin :
  public QObject,
  public Polyhedron_demo_plugin_helper
{
  Q_OBJECT
  Q_INTERFACES(Polyhedron_demo_plugin_interface)
  QAction* actionNormalEstimation;
  QAction* actionNormalInversion;

public:
  void init(QMainWindow* mainWindow, Scene_interface* scene_interface) {
    this->scene = scene_interface;
    this->mw = mainWindow;
    actionNormalEstimation = this->getActionFromMainWindow(mw, "actionNormalEstimation");
    if(actionNormalEstimation) {
      connect(actionNormalEstimation, SIGNAL(triggered()),
              this, SLOT(on_actionNormalEstimation_triggered()));
    }

    actionNormalInversion = this->getActionFromMainWindow(mw, "actionNormalInversion");
    if(actionNormalInversion) {
      connect(actionNormalInversion, SIGNAL(triggered()),
              this, SLOT(on_actionNormalInversion_triggered()));
    }
  }

  QList<QAction*> actions() const {
    return QList<QAction*>() << actionNormalEstimation << actionNormalInversion;
  }

public slots:
  void on_actionNormalEstimation_triggered();
  void on_actionNormalInversion_triggered();

}; // end PS_demo_smoothing_plugin

class Point_set_demo_normal_estimation_dialog : public QDialog, private Ui::NormalEstimationDialog
{
  Q_OBJECT
  public:
    Point_set_demo_normal_estimation_dialog(QWidget *parent = 0)
    {
      setupUi(this);
    }

    QString directionMethod() const { return m_inputDirection->currentText(); }
    int directionNbNeighbors() const { return m_inputNbNeighborsDirection->value(); }

    QString orientationMethod() const { return m_inputOrientation->currentText(); }
    int orientationNbNeighbors() const { return m_inputNbNeighborsOrientation->value(); }
};


void PS_demo_normal_estimation_plugin::on_actionNormalInversion_triggered()
{
  const Scene_interface::Item_id index = scene->mainSelectionIndex();

  Point_set_scene_item* item =
    qobject_cast<Point_set_scene_item*>(scene->item(index));

  if(item)
  {
    // Gets point set
    Point_set* points = item->point_set();
    if(points == NULL)
        return;
  
    for(Point_set::iterator it = points->begin(); it != points->end(); ++it){
      it->normal() = -1 * it->normal();
    }
  }
}

void PS_demo_normal_estimation_plugin::on_actionNormalEstimation_triggered()
{
  const Scene_interface::Item_id index = scene->mainSelectionIndex();

  Point_set_scene_item* item =
    qobject_cast<Point_set_scene_item*>(scene->item(index));

  if(item)
  {
    // Gets point set
    Point_set* points = item->point_set();
    if(points == NULL)
        return;

    // Gets options
    Point_set_demo_normal_estimation_dialog dialog;
    if(!dialog.exec())
      return;
      
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // First point to delete
    Point_set::iterator first_unoriented_point = points->end();

    //***************************************
    // normal estimation
    //***************************************

    if (dialog.directionMethod() == "plane")
    {
      CGAL::Timer task_timer; task_timer.start();
      std::cerr << "Estimates normal direction by PCA (k=" << dialog.directionNbNeighbors() <<")...\n";

      // Estimates normals direction.
      CGAL::pca_estimate_normals(points->begin(), points->end(),
                                CGAL::make_normal_of_point_with_normal_pmap(points->begin()),
                                dialog.directionNbNeighbors());

      // Mark all normals as unoriented
      first_unoriented_point = points->begin();

      long memory = CGAL::Memory_sizer().virtual_size();
      std::cerr << "Estimates normal direction: " << task_timer.time() << " seconds, "
                                                  << (memory>>20) << " Mb allocated"
                                                  << std::endl;
    }
    else if (dialog.directionMethod() == "quadric")
    {
      CGAL::Timer task_timer; task_timer.start();
      std::cerr << "Estimates normal direction by Jet Fitting (k=" << dialog.directionNbNeighbors() <<")...\n";

      // Estimates normals direction.
      CGAL::jet_estimate_normals(points->begin(), points->end(),
                                CGAL::make_normal_of_point_with_normal_pmap(points->begin()),
                                dialog.directionNbNeighbors());

      // Mark all normals as unoriented
      first_unoriented_point = points->begin();

      long memory = CGAL::Memory_sizer().virtual_size();
      std::cerr << "Estimates normal direction: " << task_timer.time() << " seconds, "
                                                  << (memory>>20) << " Mb allocated"
                                                  << std::endl;
    }

    //***************************************
    // normal orientation
    //***************************************

    CGAL::Timer task_timer; task_timer.start();
    std::cerr << "Orient normals with a Minimum Spanning Tree (k=" << dialog.orientationNbNeighbors() << ")...\n";

    // Tries to orient normals
    first_unoriented_point =
      CGAL::mst_orient_normals(points->begin(), points->end(),
                              CGAL::make_normal_of_point_with_normal_pmap(points->begin()),
                              dialog.orientationNbNeighbors());

    int nb_unoriented_normals = std::distance(first_unoriented_point, points->end());
    long memory = CGAL::Memory_sizer().virtual_size();
    std::cerr << "Orient normals: " << nb_unoriented_normals << " point(s) with an unoriented normal are selected ("
                                    << task_timer.time() << " seconds, "
                                    << (memory>>20) << " Mb allocated)"
                                    << std::endl;

    // Selects points with an unoriented normal
    points->select(points->begin(), points->end(), false);
    points->select(first_unoriented_point, points->end(), true);

    // Updates scene
    scene->itemChanged(index);

    QApplication::restoreOverrideCursor();

    // Warns user
    if (nb_unoriented_normals > 0)
    {
      QMessageBox::information(NULL,
                               tr("Points with an unoriented normal"),
                               tr("%1 point(s) with an unoriented normal are selected.\nPlease orient them or remove them before running Poisson reconstruction.")
                               .arg(nb_unoriented_normals));
    }
  }
}

Q_EXPORT_PLUGIN2(PS_demo_normal_estimation_plugin, PS_demo_normal_estimation_plugin)

#include "PS_demo_normal_estimation_plugin.moc"
