// Copyright (c) 2002  Max-Planck-Institute Saarbruecken (Germany)
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
// You can redistribute it and/or modify it under the terms of the GNU
// General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/next/Nef_3/demo/Nef_3/nef_3_extended.cpp $
// $Id: nef_3_extended.cpp 67117 2012-01-13 18:14:48Z lrineau $
// 
//
// Author(s)     : Lutz Kettner
//                 Peter Hachenberger
//
// Demo program maintaining a stack of Nef polyhedra in the space and
// a manipulation language for stack ops, file loading and saving, etc.
// ============================================================================
#include <CGAL/basic.h>

#ifdef CGAL_USE_LEDA
  #include <CGAL/leda_integer.h>
  typedef leda_integer NT;
#else
  #include <CGAL/Gmpz.h>
  typedef CGAL::Gmpz NT;
#endif

#include <CGAL/Extended_homogeneous.h>
typedef CGAL::Extended_homogeneous<NT> Kernel;

#include <CGAL/Nef_3/demo_stack.h>

int main(  int argc, char* argv[]) {    

  CGAL::demo_stack<Kernel> ds;
  if ( argc < 2
       || strcmp( argv[1], "-h") == 0
       || strcmp( argv[1], "-help") == 0 )
    {
      ds.help_message( cerr);
      exit(1);
    }
  CGAL::set_pretty_mode(std::cerr);
  
  return ds.eval( argc-1, argv+1);
}
