// Copyright (c) 2009 GeometryFactory  All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/next/Stream_support/include/CGAL/IO/File_header_gocad.h $
// $Id: File_header_gocad.h 67093 2012-01-13 11:22:39Z lrineau $
// 
//
// Author(s)     : Andreas Fabri


#ifndef CGAL_IO_FILE_HEADER_GOCAD_H
#define CGAL_IO_FILE_HEADER_GOCAD_H 1

#include <iostream>
#include <string>

namespace CGAL {

class File_header_gocad {
private:
  std::string m_fname;
  std::string m_color;
public:
explicit File_header_gocad(std::string fname, std::string color) : m_fname(fname), m_color(color) {}

  std::string fname() const
  {
    return m_fname;
  }

  std::string color() const
 {
   return m_color;
 }
  

};

// Write header.
inline std::ostream& operator<<( std::ostream& out, const File_header_gocad& h){

  return out << "GOCAD TSurf 1\n"
    "HEADER {\n"
    "name:" << h.fname() << "\n"
    "*solid*color:" << h.color() << "\n"
    "}\n"
    "TFACE\n";
}

} //namespace CGAL
#endif // CGAL_IO_FILE_HEADER_GOCAD_H
