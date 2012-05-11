// Copyright (c) 2005,2006,2007,2009,2010,2011 Tel-Aviv University (Israel).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/next/Arrangement_on_surface_2/include/CGAL/Arr_point_location/Arr_trapezoid_ric_pl_impl.h $
// $Id: Arr_trapezoid_ric_pl_impl.h 67117 2012-01-13 18:14:48Z lrineau $
// 
//
// Author(s)     : Idit Haran   <haranidi@post.tau.ac.il>
#ifndef CGAL_ARR_TRAPEZOID_RIC_POINT_LOCATION_FUNCTIONS_H
#define CGAL_ARR_TRAPEZOID_RIC_POINT_LOCATION_FUNCTIONS_H

/*! \file
* Member-function definitions for the Arr_trapezoid_ric_point_location<Arrangement>
* class.
*/

#define CGAL_TRAP_DEBUG

#ifdef CGAL_TRG_DEBUG
	#define CGAL_TRAP_PRINT_DEBUG(expr)   std::cout << expr << std::endl
#else
	#define CGAL_TRAP_PRINT_DEBUG(expr)
#endif

namespace CGAL {

//-----------------------------------------------------------------------------
// Locate the arrangement feature containing the given point.
//
template <class Arrangement_2>
Object Arr_trapezoid_ric_point_location<Arrangement_2>
::locate (const Point_2& p) const
{
  CGAL_TRAP_PRINT_DEBUG("locate point "<<p);

  //there are different internal compiler errors if we
  // typedef the Locate_type
  typename TD::Locate_type td_lt; 

  const X_curve_plus& cv = td.locate(p,td_lt).top();

  CGAL_TRAP_PRINT_DEBUG("after td.locate");

  // treat special case, where trapezoid is unbounded.
  //	for then get_parent() is not defined
  if (td_lt==TD::UNBOUNDED_TRAPEZOID)
  {
    CGAL_TRAP_PRINT_DEBUG("UNBOUNDED_TRAPEZOID");
    //check isolated vertices
    Face_const_handle ubf = this->arrangement()->unbounded_face();
      Isolated_vertex_const_iterator   iso_verts_it;
      for (iso_verts_it = ubf->isolated_vertices_begin();
           iso_verts_it != ubf->isolated_vertices_end();
           ++iso_verts_it)
      {
        if (m_traits->equal_2_object()(p, iso_verts_it->point()))
        {
          Vertex_const_handle  vh = iso_verts_it;
          return (CGAL::make_object (vh));
        }
      }
    return (CGAL::make_object (ubf));
  }

  Halfedge_const_handle h = cv.get_parent();

  switch(td_lt)
  {
  case TD::POINT:
    {
      CGAL_TRAP_PRINT_DEBUG("POINT");
      if (m_traits->equal_2_object()(h->target()->point(), p))
      {
        Vertex_const_handle vh = h->target();
        return (CGAL::make_object (vh));
      }
      if (m_traits->equal_2_object()(h->source()->point(), p))
      {
        Vertex_const_handle vh = h->source();
        return (CGAL::make_object (vh));
      }
      else
        CGAL_error();
      break;
    }

  case TD::CURVE:
    {
      CGAL_TRAP_PRINT_DEBUG("CURVE");
      if ( m_traits->is_in_x_range_2_object()(cv,p) && 
           m_traits->compare_y_at_x_2_object()(p,cv) == EQUAL)
        return (CGAL::make_object(h));
      else
      {
        //ixx
        std::cerr << "curve is: "<<cv<<" point is: "<<p <<std::endl; 
        CGAL_error();
      }
      break;
    }

  case TD::TRAPEZOID:
    {
      CGAL_TRAP_PRINT_DEBUG("TRAPEZOID");
      if (!(((m_traits->is_in_x_range_2_object()(h->curve(),p)) &&
        (m_traits->compare_y_at_x_2_object()(p, h->curve()) == LARGER)) ==
        (m_traits->compare_x_2_object()(h->source()->point(),
        h->target()->point()) == SMALLER)
        ))
        h = h->twin();
      Face_const_handle fh = h->face();

      //check isolated vertices
      Isolated_vertex_const_iterator   iso_verts_it;
      for (iso_verts_it = fh->isolated_vertices_begin();
          iso_verts_it != fh->isolated_vertices_end(); ++iso_verts_it)
      {
        if (m_traits->equal_2_object()(p, iso_verts_it->point()))
        {
          Vertex_const_handle  vh = iso_verts_it;
          return (CGAL::make_object (vh));
        }
      }

      return (CGAL::make_object(fh));
    }
  default:
    CGAL_TRAP_PRINT_DEBUG("DEFAULT");
    CGAL_error();
    break;
  }

  CGAL_TRAP_PRINT_DEBUG("EMPTY");
  return Object();   
}

//-----------------------------------------------------------------------------
// Locate the arrangement feature which a vertical ray emanating from the
// given point hits, considering isolated vertices.
//
template <class Arrangement>
Object Arr_trapezoid_ric_point_location<Arrangement>
::_vertical_ray_shoot (const Point_2& p, bool shoot_up) const
{
  //trying to workaround internal compiler error
  typename TD::Locate_type td_lt;
  Halfedge_const_handle invalid_he;
 
  X_curve_plus cv = td.vertical_ray_shoot(p, td_lt, shoot_up);

  // treat special case, where trapezoid is unbounded.
  //	for then get_parent() is not defined
  if (td_lt==TD::UNBOUNDED_TRAPEZOID)
  { 
    return (_check_isolated_for_vertical_ray_shoot(invalid_he, p, shoot_up));
  }

  Halfedge_const_handle h = cv.get_parent();

  switch(td_lt)
  {
  case TD::POINT:
    if (m_traits->equal_2_object()(h->target()->point(), p))
    {
      Vertex_const_handle vh = h->target();
      return (CGAL::make_object (vh));
    }
    if (m_traits->equal_2_object()(h->source()->point(), p))
    {
      Vertex_const_handle vh = h->source();
      return (CGAL::make_object (vh));
    }
    else
      CGAL_error();
    break;

 case TD::CURVE:
    if ((shoot_up && h->direction() == ARR_LEFT_TO_RIGHT) ||
        (!shoot_up && h->direction() == ARR_RIGHT_TO_LEFT))
      h=h->twin();

    return (CGAL::make_object(h));

  case TD::TRAPEZOID:
    if (!(((m_traits->is_in_x_range_2_object()(h->curve(),p)) &&
          (m_traits->compare_y_at_x_2_object()(p, h->curve()) == LARGER)) ==
          (m_traits->compare_x_2_object()(h->source()->point(),
                                        h->target()->point()) == SMALLER)
        ))
        h = h->twin();

    return (_check_isolated_for_vertical_ray_shoot(h, p, shoot_up));

  default:
    CGAL_error();
    break;
  }

  return (_check_isolated_for_vertical_ray_shoot(invalid_he, p, shoot_up));
}

//-----------------------------------------------------------------------------
// In vertical ray shoot, when the closest halfedge is found (or unbounded
// face) we check the isolated vertices inside the face to check whether there
// is an isolated vertex right above/below the query point.
// 
template <class Arrangement>
Object Arr_trapezoid_ric_point_location<Arrangement>::
_check_isolated_for_vertical_ray_shoot (Halfedge_const_handle halfedge_found, 
                                        const Point_2& p, 
                                        bool shoot_up) const
{
  const Comparison_result point_above_under = (shoot_up ? SMALLER : LARGER);
  typename Geometry_traits_2::Compare_x_2          compare_x =
    this->arrangement()->traits()->compare_x_2_object();
  typename Geometry_traits_2::Compare_xy_2         compare_xy =
    this->arrangement()->traits()->compare_xy_2_object();
  typename Geometry_traits_2::Compare_y_at_x_2     compare_y_at_x =
    this->arrangement()->traits()->compare_y_at_x_2_object();

  Isolated_vertex_const_iterator   iso_verts_it;
  Vertex_const_handle              closest_iso_v;
  const Vertex_const_handle        invalid_v;
  const Halfedge_const_handle      invalid_he;
  Face_const_handle                face;

  // If the closest feature is a valid halfedge, take its incident face.
  // Otherwise, take the unbounded face.
  if (halfedge_found == invalid_he)
    face = this->arrangement()->unbounded_face();
  else
    face = halfedge_found->face();

  // Go over the isolated vertices in the face.
  for (iso_verts_it = face->isolated_vertices_begin();
       iso_verts_it != face->isolated_vertices_end(); ++iso_verts_it)
  {
    // The current isolated vertex should have the same x-coordinate as the
    // query point in order to be below or above it.
    if (compare_x (p, iso_verts_it->point()) != EQUAL)
      continue;

    // Make sure the isolated vertex is above the query point (if we shoot up)
    // or below it (if we shoot down).
    if (compare_xy (p, iso_verts_it->point()) != point_above_under)
      continue;

    // Check if the current isolated vertex lies closer to the query point than
    // the closest feature so far.
    if (closest_iso_v == invalid_v)
    {
      // Compare the current isolated vertex with the closest halfedge.
      if (halfedge_found == invalid_he ||
          compare_y_at_x (iso_verts_it->point(),
                          halfedge_found->curve()) == point_above_under)
      {
        closest_iso_v = iso_verts_it;
      }
    }
    else if (compare_xy (iso_verts_it->point(),
                         closest_iso_v->point()) == point_above_under)
    {
      closest_iso_v = iso_verts_it;
    }
  }

  // If we found an isolated vertex above (or under) the query point, return
  // a handle to this vertex.
  if (closest_iso_v != invalid_v)
    return (CGAL::make_object (closest_iso_v));

  // If we are inside the unbounded face, return this face.
  if (halfedge_found == invalid_he)
    return (CGAL::make_object (face));

  // Return the halfedge lying above (or below) the query point.
  return (CGAL::make_object (halfedge_found));
}



} //namespace CGAL

#endif
