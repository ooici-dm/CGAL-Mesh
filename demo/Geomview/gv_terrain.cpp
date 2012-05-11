// Copyright (c) 2000, 2001, 2004  
// Utrecht University (The Netherlands),
// ETH Zurich (Switzerland),
// INRIA Sophia-Antipolis (France),
// Max-Planck-Institute Saarbruecken (Germany),
// and Tel-Aviv University (Israel).  All rights reserved. 
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 3 of the License,
// or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/next/Geomview/demo/Geomview/gv_terrain.cpp $
// $Id: gv_terrain.cpp 67093 2012-01-13 11:22:39Z lrineau $
//
//
// Author(s)     : Sylvain Pion

#include <CGAL/Cartesian.h>
#include <iostream>

#ifndef CGAL_USE_GEOMVIEW
int main()
{
  std::cout << "Geomview doesn't work on Windows, so..." << std::endl;
  return 0;
}
#else

#include <fstream>
#include <unistd.h> // for sleep()

#include <CGAL/Triangulation_euclidean_traits_xy_3.h>

#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Delaunay_triangulation_3.h>

#include <CGAL/IO/Geomview_stream.h>
#include <CGAL/IO/Triangulation_geomview_ostream_2.h>
#include <CGAL/IO/Triangulation_geomview_ostream_3.h>

#include <CGAL/intersections.h>

typedef CGAL::Cartesian<double>  K;

typedef K::Point_2 Point2;
typedef CGAL::Triangulation_euclidean_traits_xy_3<K> Gt3;
typedef Gt3::Point Point3;

typedef CGAL::Delaunay_triangulation_2<K>   Delaunay;
typedef CGAL::Delaunay_triangulation_2<Gt3> Terrain;

typedef CGAL::Delaunay_triangulation_3<K>   Delaunay3d;

int main()
{
  CGAL::Geomview_stream gv(CGAL::Bbox_3(-100, -100, -100, 600, 600, 600));
  gv.set_line_width(4);
  // gv.set_trace(true);
  gv.set_bg_color(CGAL::Color(0, 200, 200));
  // gv.clear();

  Delaunay D;
  Delaunay3d D3d;
  Terrain T;
  std::ifstream iFile("data/points3", std::ios::in);
  Point3 p;

  while ( iFile >> p )
  {
      D.insert( Point2(p.x(), p.y()) );
      D3d.insert( p );
      T.insert( p );
  }

  // use different colors, and put a few sleeps/clear.

  gv << CGAL::BLUE;
  std::cout << "Drawing 2D Delaunay triangulation in wired mode.\n";
  gv.set_wired(true);
  gv << D;

#if 1 // It's too slow !  Needs to use OFF for that.
  gv << CGAL::RED;
  std::cout << "Drawing its Voronoi diagram.\n";
  gv.set_wired(true);
  D.draw_dual(gv);
#endif

  sleep(5);
  gv.clear();

  std::cout << "Drawing 2D Delaunay triangulation in non-wired mode.\n";
  gv.set_wired(false);
  gv << D;
  sleep(5);
  gv.clear();

  std::cout << "Drawing 3D Delaunay triangulation in wired mode.\n";
  gv.set_wired(true);
  gv << D3d;
  sleep(5);
  gv.clear();
  std::cout << "Drawing 3D Delaunay triangulation in non-wired mode.\n";
  gv.set_wired(false);
  gv << D3d;
  sleep(5);
  gv.clear();

  std::cout << "Drawing Terrain in wired mode.\n";
  gv.set_wired(true);
  gv << T;
  sleep(5);
  gv.clear();
  std::cout << "Drawing Terrain in non-wired mode.\n";
  gv.set_wired(false);
  gv << T;

  std::cout << "Enter a key to finish" << std::endl;
  char ch;
  std::cin >> ch;

  return 0;
}
#endif
