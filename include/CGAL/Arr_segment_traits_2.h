// Copyright (c) 2006,2007,2009,2010,2011 Tel-Aviv University (Israel).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/next/Arrangement_on_surface_2/include/CGAL/Arr_segment_traits_2.h $
// $Id: Arr_segment_traits_2.h 67117 2012-01-13 18:14:48Z lrineau $
// 
//
// Author(s)     : Ron Wein          <wein@post.tau.ac.il>
//                 Efi Fogel         <efif@post.tau.ac.il>

#ifndef CGAL_ARR_SEGMENT_TRAITS_2_H
#define CGAL_ARR_SEGMENT_TRAITS_2_H

/*! \file
 * The segment traits-class for the arrangement package.
 */

#include <CGAL/tags.h>
#include <CGAL/intersections.h>
#include <CGAL/Arr_tags.h>
#include <CGAL/Arr_geometry_traits/Segment_assertions.h>
#include <fstream>

namespace CGAL {

template <class Kernel_> class Arr_segment_2;

/*!
 * \class A traits class for maintaining an arrangement of segments, aoviding
 * cascading of computations as much as possible.
 *
 * The class is derived from the parameterized kernel to extend the traits
 * with all the types and operations supported by the kernel. This makes it
 * possible to use the traits class for data structures that extends the
 * Arrangement_2 type and require objects and operations supported by the
 * kernel, but not defined in this derived class.
 */
template <class Kernel_>
class Arr_segment_traits_2 : public Kernel_
{
  friend class Arr_segment_2<Kernel_>;

public:

  typedef Kernel_                         Kernel;
  typedef typename Kernel::FT             FT;

  typedef typename Algebraic_structure_traits<FT>::Is_exact 
                                          Has_exact_division;

  // Category tags:
  typedef Tag_true                        Has_left_category;
  typedef Tag_true                        Has_merge_category;
  typedef Tag_false                       Has_do_intersect_category;
  
  typedef Arr_oblivious_side_tag          Left_side_category;
  typedef Arr_oblivious_side_tag          Bottom_side_category;
  typedef Arr_oblivious_side_tag          Top_side_category;
  typedef Arr_oblivious_side_tag          Right_side_category;
 
  typedef typename Kernel::Line_2         Line_2;
  typedef CGAL::Segment_assertions<Arr_segment_traits_2<Kernel> >
                                          Segment_assertions;

  /*!
   * \class Representation of a segement with cached data.
   */
  class _Segment_cached_2
  {
  public:

    typedef typename Kernel::Line_2                Line_2;
    typedef typename Kernel::Segment_2             Segment_2;
    typedef typename Kernel::Point_2               Point_2;

  protected:

    Line_2    l;                // The line that supports the segment.
    Point_2   ps;               // The source point of the segment.
    Point_2   pt;               // The target point of the segment.
    bool      is_pt_max;        // Is the target (lexicographically) larger
                                // than the source.
    bool      is_vert;          // Is this a vertical segment.
    bool      is_degen;         // Is the segment degenerate (a single point).

  public:

    /*!
     * Default constructor.
     */
    _Segment_cached_2 () :
      is_vert(false),
      is_degen(true)
    {}

    /*!
     * Constructor from a segment.
     * \param seg The segment.
     * \pre The segment is not degenerate.
     */
    _Segment_cached_2 (const Segment_2& seg)
    {
      Kernel   kernel;

      typename Kernel_::Construct_vertex_2
        construct_vertex = kernel.construct_vertex_2_object();

      ps = construct_vertex(seg, 0);
      pt = construct_vertex(seg, 1);

      Comparison_result  res = kernel.compare_xy_2_object()(ps, pt);
      is_degen = (res == EQUAL);
      is_pt_max = (res == SMALLER);

      CGAL_precondition_msg (! is_degen,
                             "Cannot contruct a degenerate segment.");

      l = kernel.construct_line_2_object()(seg);
      is_vert = kernel.is_vertical_2_object()(seg);
    }

    /*!
     * Construct a segment from two end-points.
     * \param source The source point.
     * \param target The target point.
     * \param The two points must not be equal.
     */
    _Segment_cached_2 (const Point_2& source, const Point_2& target) :
      ps (source),
      pt (target)
    {
      Kernel   kernel;

      Comparison_result  res = kernel.compare_xy_2_object()(ps, pt);
      is_degen = (res == EQUAL);
      is_pt_max = (res == SMALLER);

      CGAL_precondition_msg (! is_degen,
                             "Cannot contruct a degenerate segment.");

      l = kernel.construct_line_2_object()(source, target);
      is_vert = kernel.is_vertical_2_object()(l);
    }

    /*!
     * Construct a segment from two end-points on a supporting line.
     * \param supp_line The supporting line.
     * \param source The source point.
     * \param target The target point.
     * \pre The two endpoints are not the same and both lie on the given line.
     */
    _Segment_cached_2 (const Line_2& supp_line,
                       const Point_2& source, const Point_2& target) :
      l (supp_line),
      ps (source),
      pt (target)
    {
      Kernel   kernel;

      CGAL_precondition(
        Segment_assertions::_assert_is_point_on(source, l,
                                                Has_exact_division()) &&
        Segment_assertions::_assert_is_point_on(target,l,
                                                Has_exact_division())
        );

      is_vert = kernel.is_vertical_2_object()(l);

      Comparison_result  res = kernel.compare_xy_2_object()(ps, pt);
      is_degen = (res == EQUAL);
      is_pt_max = (res == SMALLER);

      CGAL_precondition_msg (! is_degen,
                             "Cannot contruct a degenerate segment.");
    }

    /*!
     * Assignment operator.
     * \param seg the source segment to copy from
     * \pre The segment is not degenerate.
     */
    const _Segment_cached_2& operator= (const Segment_2& seg)
    {
      Kernel   kernel;

      typename Kernel_::Construct_vertex_2
        construct_vertex = kernel.construct_vertex_2_object();

      ps = construct_vertex(seg, 0);
      pt = construct_vertex(seg, 1);

      Comparison_result  res = kernel.compare_xy_2_object()(ps, pt);
      is_degen = (res == EQUAL);
      is_pt_max = (res == SMALLER);

      CGAL_precondition_msg (! is_degen,
                             "Cannot contruct a degenerate segment.");

      l = kernel.construct_line_2_object()(seg);
      is_vert = kernel.is_vertical_2_object()(seg);

      return (*this);
    }

    /*!
     * Get the (lexicographically) left endpoint.
     */
    const Point_2& left () const
    {
      return (is_pt_max ? ps : pt);
    }

    /*!
     * Set the (lexicographically) left endpoint.
     * \param p The point to set.
     * \pre p lies on the supporting line to the left of the right endpoint.
     */
    void set_left (const Point_2& p)
    {
      CGAL_precondition (! is_degen);
      CGAL_precondition_code (
        Kernel    kernel;
      );
      CGAL_precondition 
        (Segment_assertions::_assert_is_point_on (p, l, 
                                                  Has_exact_division()) &&
         kernel.compare_xy_2_object() (p, right()) == SMALLER);

      if (is_pt_max)
        ps = p;
      else
        pt = p;
    }

    /*!
     * Get the (lexicographically) right endpoint.
     */
    const Point_2& right () const
    {
      return (is_pt_max ? pt : ps);
    }

    /*!
     * Set the (lexicographically) right endpoint.
     * \param p The point to set.
     * \pre p lies on the supporting line to the right of the left endpoint.
     */
    void set_right (const Point_2& p)
    {
      CGAL_precondition (! is_degen);
      CGAL_precondition_code (
        Kernel    kernel;
      );
      CGAL_precondition 
        (Segment_assertions::_assert_is_point_on (p, l, 
                                                  Has_exact_division()) &&
         kernel.compare_xy_2_object() (p, left()) == LARGER);

      if (is_pt_max)
        pt = p;
      else
        ps = p;
    }

    /*!
     * Get the supporting line.
     */
    const Line_2& line () const
    {
      CGAL_precondition (! is_degen);
      return (l);
    }

    /*!
     * Check if the curve is vertical.
     */
    bool is_vertical () const
    {
      CGAL_precondition (! is_degen);
      return (is_vert);
    }

    /*!
     * Check if the curve is directed lexicographic from left to right
     */
    bool is_directed_right () const
    {
      return (is_pt_max);
    }

    /*!
     * Check if the given point is in the x-range of the segment.
     * \param p The query point.
     * \return (true) is in the x-range of the segment; (false) if it is not.
     */
    bool is_in_x_range (const Point_2& p) const
    {
      Kernel                          kernel;
      typename Kernel_::Compare_x_2   compare_x = kernel.compare_x_2_object();
      const Comparison_result         res1 = compare_x (p, left());

      if (res1 == SMALLER)
        return (false);
      else if (res1 == EQUAL)
        return (true);

      const Comparison_result         res2 = compare_x (p, right());

      return (res2 != LARGER);
    }

    /*!
     * Check if the given point is in the y-range of the segment.
     * \param p The query point.
     * \return (true) is in the y-range of the segment; (false) if it is not.
     */
    bool is_in_y_range (const Point_2& p) const
    {
      Kernel                          kernel;
      typename Kernel_::Compare_y_2   compare_y = kernel.compare_y_2_object();
      const Comparison_result         res1 = compare_y (p, left());

      if (res1 == SMALLER)
        return (false);
      else if (res1 == EQUAL)
        return (true);

      const Comparison_result         res2 = compare_y (p, right());

      return (res2 != LARGER);
    }
  };

public:

  // Traits objects
  typedef typename Kernel::Point_2        Point_2;
  typedef Arr_segment_2<Kernel>           X_monotone_curve_2;
  typedef Arr_segment_2<Kernel>           Curve_2;
  typedef unsigned int                    Multiplicity;

public:

  /*!
   * Default constructor.
   */
  Arr_segment_traits_2 ()
  {}

  /// \name Basic functor definitions.
  //@{

  class Compare_x_2
  {
  public:
    /*!
     * Compare the x-coordinates of two points.
     * \param p1 The first point.
     * \param p2 The second point.
     * \return LARGER if x(p1) > x(p2);
     *         SMALLER if x(p1) < x(p2);
     *         EQUAL if x(p1) = x(p2).
     */
    Comparison_result operator() (const Point_2& p1, const Point_2& p2) const
    {
      Kernel    kernel;

      return (kernel.compare_x_2_object()(p1, p2));
    }
  };

  /*! Get a Compare_x_2 functor object. */
  Compare_x_2 compare_x_2_object () const
  {
    return Compare_x_2();
  }

  class Compare_xy_2
  {
  public:
    /*!
     * Compare two points lexigoraphically: by x, then by y.
     * \param p1 The first point.
     * \param p2 The second point.
     * \return LARGER if x(p1) > x(p2), or if x(p1) = x(p2) and y(p1) > y(p2);
     *         SMALLER if x(p1) < x(p2), or if x(p1) = x(p2) and y(p1) < y(p2);
     *         EQUAL if the two points are equal.
     */
    Comparison_result operator() (const Point_2& p1, const Point_2& p2) const
    {
      Kernel    kernel;
      return (kernel.compare_xy_2_object()(p1, p2));
    }
  };

  /*! Get a Compare_xy_2 functor object. */
  Compare_xy_2 compare_xy_2_object () const
  {
    return Compare_xy_2();
  }

  class Construct_min_vertex_2
  {
  public:
    /*!
     * Get the left endpoint of the x-monotone curve (segment).
     * \param cv The curve.
     * \return The left endpoint.
     */
    const Point_2& operator() (const X_monotone_curve_2& cv) const
    {
      return (cv.left());
    }
  };

  /*! Get a Construct_min_vertex_2 functor object. */
  Construct_min_vertex_2 construct_min_vertex_2_object () const
  {
    return Construct_min_vertex_2();
  }

  class Construct_max_vertex_2
  {
  public:
    /*!
     * Get the right endpoint of the x-monotone curve (segment).
     * \param cv The curve.
     * \return The right endpoint.
     */
    const Point_2& operator() (const X_monotone_curve_2& cv) const
    {
      return (cv.right());
    }
  };

  /*! Get a Construct_max_vertex_2 functor object. */
  Construct_max_vertex_2 construct_max_vertex_2_object () const
  {
    return Construct_max_vertex_2();
  }

  class Is_vertical_2
  {
  public:
    /*!
     * Check whether the given x-monotone curve is a vertical segment.
     * \param cv The curve.
     * \return (true) if the curve is a vertical segment; (false) otherwise.
     */
    bool operator() (const X_monotone_curve_2& cv) const
    {
      return (cv.is_vertical());
    }
  };

  /*! Get an Is_vertical_2 functor object. */
  Is_vertical_2 is_vertical_2_object () const
  {
    return Is_vertical_2();
  }

  class Compare_y_at_x_2
  {
  public:
    /*!
     * Return the location of the given point with respect to the input curve.
     * \param cv The curve.
     * \param p The point.
     * \pre p is in the x-range of cv.
     * \return SMALLER if y(p) < cv(x(p)), i.e. the point is below the curve;
     *         LARGER if y(p) > cv(x(p)), i.e. the point is above the curve;
     *         EQUAL if p lies on the curve.
     */
    Comparison_result operator() (const Point_2& p,
                                  const X_monotone_curve_2& cv) const
    {
      CGAL_precondition (cv.is_in_x_range (p));

      Kernel    kernel;

      if (! cv.is_vertical())
      {
        // Compare p with the segment's supporting line.
        return (kernel.compare_y_at_x_2_object()(p, cv.line()));
      }
      else
      {
        // Compare with the vertical segment's end-points.
        typename Kernel::Compare_y_2  compare_y = kernel.compare_y_2_object();
        Comparison_result res1 = compare_y (p, cv.left());
        Comparison_result res2 = compare_y (p, cv.right());

        if (res1 == res2)
          return (res1);
        else
          return (EQUAL);
      }
    }
  };

  /*! Get a Compare_y_at_x_2 functor object. */
  Compare_y_at_x_2 compare_y_at_x_2_object () const
  {
    return Compare_y_at_x_2();
  }

  class Compare_y_at_x_left_2
  {
  public:
    /*!
     * Compare the y value of two x-monotone curves immediately to the left
     * of their intersection point.
     * \param cv1 The first curve.
     * \param cv2 The second curve.
     * \param p The intersection point.
     * \pre The point p lies on both curves, and both of them must be also be
     *      defined (lexicographically) to its left.
     * \return The relative position of cv1 with respect to cv2 immdiately to
     *         the left of p: SMALLER, LARGER or EQUAL.
     */
    Comparison_result operator() (const X_monotone_curve_2& cv1,
                                  const X_monotone_curve_2& cv2,
                                  const Point_2& p) const
    {
      Kernel                        kernel;

      // Make sure that p lies on both curves, and that both are defined to its
      // left (so their left endpoint is lexicographically smaller than p).
      CGAL_precondition_code (
        typename Kernel::Compare_xy_2 compare_xy = 
                                                  kernel.compare_xy_2_object();
      );

      CGAL_precondition 
        (Segment_assertions::_assert_is_point_on (p, cv1, 
                                                  Has_exact_division()) &&
         Segment_assertions::_assert_is_point_on (p, cv2,
                                                  Has_exact_division()));

      CGAL_precondition (compare_xy(cv1.left(), p) == SMALLER &&
                         compare_xy(cv2.left(), p) == SMALLER);

      // Compare the slopes of the two segments to determine thir relative
      // position immediately to the left of q.
      // Notice we use the supporting lines in order to compare the slopes,
      // and that we swap the order of the curves in order to obtain the
      // correct result to the left of p.
      return (kernel.compare_slope_2_object()(cv2.line(), cv1.line()));
    }
  };

  /*! Get a Compare_y_at_x_left_2 functor object. */
  Compare_y_at_x_left_2 compare_y_at_x_left_2_object () const
  {
    return Compare_y_at_x_left_2();
  }

  class Compare_y_at_x_right_2
  {
  public:
    /*!
     * Compare the y value of two x-monotone curves immediately to the right
     * of their intersection point.
     * \param cv1 The first curve.
     * \param cv2 The second curve.
     * \param p The intersection point.
     * \pre The point p lies on both curves, and both of them must be also be
     *      defined (lexicographically) to its right.
     * \return The relative position of cv1 with respect to cv2 immdiately to
     *         the right of p: SMALLER, LARGER or EQUAL.
     */
    Comparison_result operator() (const X_monotone_curve_2& cv1,
                                  const X_monotone_curve_2& cv2,
                                  const Point_2& p) const
    {
      Kernel                        kernel;

      // Make sure that p lies on both curves, and that both are defined to its
      // right (so their right endpoint is lexicographically larger than p).
      CGAL_precondition_code (
        typename Kernel::Compare_xy_2 compare_xy = 
                                                 kernel.compare_xy_2_object();
      );

      CGAL_precondition
        (Segment_assertions::_assert_is_point_on (p, cv1, 
                                                  Has_exact_division()) &&
         Segment_assertions::_assert_is_point_on (p, cv2,
                                                  Has_exact_division()));

      CGAL_precondition (compare_xy(cv1.right(), p) == LARGER &&
                         compare_xy(cv2.right(), p) == LARGER);

      // Compare the slopes of the two segments to determine thir relative
      // position immediately to the left of q.
      // Notice we use the supporting lines in order to compare the slopes.
      return (kernel.compare_slope_2_object()(cv1.line(), cv2.line()));
    }
  };

  /*! Get a Compare_y_at_x_right_2 functor object. */
  Compare_y_at_x_right_2 compare_y_at_x_right_2_object () const
  {
    return Compare_y_at_x_right_2();
  }

  class Equal_2
  {
  public:
    /*!
     * Check if the two x-monotone curves are the same (have the same graph).
     * \param cv1 The first curve.
     * \param cv2 The second curve.
     * \return (true) if the two curves are the same; (false) otherwise.
     */
    bool operator() (const X_monotone_curve_2& cv1,
                     const X_monotone_curve_2& cv2) const
    {
      Kernel                    kernel;
      typename Kernel::Equal_2  equal = kernel.equal_2_object();

      return (equal(cv1.left(), cv2.left()) &&
              equal(cv1.right(), cv2.right()));
    }

    /*!
     * Check if the two points are the same.
     * \param p1 The first point.
     * \param p2 The second point.
     * \return (true) if the two point are the same; (false) otherwise.
     */
    bool operator() (const Point_2& p1, const Point_2& p2) const
    {
      Kernel    kernel;
      return (kernel.equal_2_object()(p1, p2));
    }
  };

  /*! Get an Equal_2 functor object. */
  Equal_2 equal_2_object () const
  {
    return Equal_2();
  }
  //@}

  /// \name Functor definitions for supporting intersections.
  //@{

  class Make_x_monotone_2
  {
  public:
    /*!
     * Cut the given curve into x-monotone subcurves and insert them into the
     * given output iterator. As segments are always x_monotone, only one
     * object will be contained in the iterator.
     * \param cv The curve.
     * \param oi The output iterator, whose value-type is Object.
     * \return The past-the-end iterator.
     */
    template<class OutputIterator>
    OutputIterator operator() (const Curve_2& cv, OutputIterator oi) const
    {
      // Wrap the segment with an object.
      *oi = make_object (cv);
      ++oi;
      return (oi);
    }
  };

  /*! Get a Make_x_monotone_2 functor object. */
  Make_x_monotone_2 make_x_monotone_2_object () const
  {
    return Make_x_monotone_2();
  }

  class Split_2
  {
  public:
    /*!
     * Split a given x-monotone curve at a given point into two sub-curves.
     * \param cv The curve to split
     * \param p The split point.
     * \param c1 Output: The left resulting subcurve (p is its right endpoint).
     * \param c2 Output: The right resulting subcurve (p is its left endpoint).
     * \pre p lies on cv but is not one of its end-points.
     */
    void operator() (const X_monotone_curve_2& cv, const Point_2& p,
                     X_monotone_curve_2& c1, X_monotone_curve_2& c2) const
    {
      // Make sure that p lies on the interior of the curve.
      CGAL_precondition_code (
        Kernel                        kernel;
        typename Kernel::Compare_xy_2 compare_xy = 
                                                 kernel.compare_xy_2_object();
      );

      CGAL_precondition
        (Segment_assertions::_assert_is_point_on (p, cv,
                                                  Has_exact_division()) &&
         compare_xy(cv.left(), p) == SMALLER &&
         compare_xy(cv.right(), p) == LARGER);

      // Perform the split.
      c1 = cv;
      c1.set_right (p);

      c2 = cv;
      c2.set_left (p);

      return;
    }
  };

  /*! Get a Split_2 functor object. */
  Split_2 split_2_object () const
  {
    return Split_2();
  }

  class Intersect_2
  {
  public:
    /*!
     * Find the intersections of the two given curves and insert them into the
     * given output iterator. As two segments may itersect only once, only a
     * single intersection will be contained in the iterator.
     * \param cv1 The first curve.
     * \param cv2 The second curve.
     * \param oi The output iterator.
     * \return The past-the-end iterator.
     */
    template<class OutputIterator>
    OutputIterator operator() (const X_monotone_curve_2& cv1,
                               const X_monotone_curve_2& cv2,
                               OutputIterator oi) const
    {
      // Intersect the two supporting lines.
      Kernel       kernel;
      CGAL::Object obj = kernel.intersect_2_object()(cv1.line(), cv2.line());

      if (obj.is_empty())
      {
        // The supporting line are parallel lines and do not intersect:
        return (oi);
      }

      // Check if we have a single intersection point.
      const Point_2  *ip = object_cast<Point_2> (&obj);
      
      if (ip != NULL)
      {
        // Check if the intersection point ip lies on both segments.
        const bool    ip_on_cv1 = cv1.is_vertical() ? cv1.is_in_y_range(*ip) :
                                                      cv1.is_in_x_range(*ip);

        if (ip_on_cv1)
        {
          const bool  ip_on_cv2 = cv2.is_vertical() ? cv2.is_in_y_range(*ip) :
                                                      cv2.is_in_x_range(*ip);

          if (ip_on_cv2)
          {
            // Create a pair representing the point with its multiplicity,
            // which is always 1 for line segments.
            std::pair<Point_2, Multiplicity>   ip_mult (*ip, 1);
            *oi = make_object (ip_mult);
            oi++;
          }
        }
        return (oi);
      }

      // In this case, the two supporting lines overlap.
      // The overlapping segment is therefore [p_l,p_r], where p_l is the
      // rightmost of the two left endpoints and p_r is the leftmost of the
      // two right endpoints.
      typename Kernel::Compare_xy_2  compare_xy = kernel.compare_xy_2_object();
      Point_2                        p_l, p_r;

      if (compare_xy (cv1.left(), cv2.left()) == SMALLER)
        p_l = cv2.left();
      else
        p_l = cv1.left();

      if (compare_xy (cv1.right(), cv2.right()) == SMALLER)
        p_r = cv1.right();
      else
        p_r = cv2.right();

      // Examine the resulting segment.
      const Comparison_result        res = compare_xy (p_l, p_r);

      if (res == SMALLER)
      {
        // We have discovered an overlapping segment:
        if(cv1.is_directed_right() == cv2.is_directed_right())
        {
          // cv1 and cv2 have the same directions, maintain this direction
          // in the overlap segment
          if(cv1.is_directed_right())
          {
            X_monotone_curve_2  overlap_seg (cv1.line(), p_l, p_r);
            *oi = make_object (overlap_seg);
            oi++;
          }
          else
          {
            X_monotone_curve_2  overlap_seg (cv1.line(), p_r, p_l);
            *oi = make_object (overlap_seg);
            oi++;
          }
        }
        else
        {
          // cv1 and cv2 have opposite directions, the overlap segment
          // will be directed from left to right
          X_monotone_curve_2  overlap_seg (cv1.line(), p_l, p_r);
          *oi = make_object (overlap_seg);
          oi++;
        }
      }
      else if (res == EQUAL)
      {
        // The two segment have the same supporting line, but they just share
        // a common endpoint. Thus we have an intersection point, but we leave
        // the multiplicity of this point undefined.
        std::pair<Point_2, Multiplicity>   ip_mult (p_r, 0);
        *oi = make_object (ip_mult);
        oi++;
      }

      return (oi);
    }
  };

  /*! Get an Intersect_2 functor object. */
  Intersect_2 intersect_2_object () const
  {
    return Intersect_2();
  }

  class Are_mergeable_2 {
  protected:
    typedef Arr_segment_traits_2<Kernel>        Traits;

    /*! The traits (in case it has state) */
    const Traits* m_traits;
    
    /*! Constructor
     * \param traits the traits (in case it has state)
     */
    Are_mergeable_2(const Traits* traits) : m_traits(traits) {}

    friend class Arr_segment_traits_2<Kernel>;
    
  public:
    /*!
     * Check whether it is possible to merge two given x-monotone curves.
     * \param cv1 The first curve.
     * \param cv2 The second curve.
     * \return (true) if the two curves are mergeable, that is, if they are
     *         supported by the same line; (false) otherwise.
     * \pre cv1 and cv2 share a common endpoint.
     */
    bool operator() (const X_monotone_curve_2& cv1,
                     const X_monotone_curve_2& cv2) const
    {
      if (!m_traits->equal_2_object()(cv1.right(), cv2.left()) &&
          !m_traits->equal_2_object()(cv2.right(), cv1.left()))
        return false;
      
      // Check whether the two curves have the same supporting line.
      const Kernel* kernel = m_traits;
      typename Kernel::Equal_2 equal = kernel->equal_2_object();
      return (equal(cv1.line(), cv2.line()) || 
              equal(cv1.line(), 
                    kernel->construct_opposite_line_2_object()(cv2.line())));
    }
  };

  /*! Get an Are_mergeable_2 functor object. */
  Are_mergeable_2 are_mergeable_2_object() const
  { return Are_mergeable_2(this); }

  /*! \class Merge_2
   * A functor that merges two x-monotone arcs into one.
   */
  class Merge_2 {
  protected:
    typedef Arr_segment_traits_2<Kernel>        Traits;

    /*! The traits (in case it has state) */
    const Traits* m_traits;
    
    /*! Constructor
     * \param traits the traits (in case it has state)
     */
    Merge_2(const Traits* traits) : m_traits(traits) {}

    friend class Arr_segment_traits_2<Kernel>;
    
  public:
    /*!
     * Merge two given x-monotone curves into a single curve (segment).
     * \param cv1 The first curve.
     * \param cv2 The second curve.
     * \param c Output: The merged curve.
     * \pre The two curves are mergeable.
     */
    void operator()(const X_monotone_curve_2& cv1,
                    const X_monotone_curve_2& cv2,
                    X_monotone_curve_2& c) const
    {
      CGAL_precondition(m_traits->are_mergeable_2_object()(cv1, cv2));

      Equal_2 equal = m_traits->equal_2_object();
      
      // Check which curve extends to the right of the other.
      if (equal(cv1.right(), cv2.left())) {
        // cv2 extends cv1 to the right.
        c = cv1;
        c.set_right(cv2.right());
      }
      else {
        CGAL_precondition(equal(cv2.right(), cv1.left()));

        // cv1 extends cv2 to the right.
        c = cv2;
        c.set_right(cv1.right());
      }
    }
  };

  /*! Get a Merge_2 functor object. */
  Merge_2 merge_2_object () const { return Merge_2(this); }
  //@}

  /// \name Functor definitions for the landmarks point-location strategy.
  //@{
  typedef double                          Approximate_number_type;

  class Approximate_2
  {
  public:

    /*!
     * Return an approximation of a point coordinate.
     * \param p The exact point.
     * \param i The coordinate index (either 0 or 1).
     * \pre i is either 0 or 1.
     * \return An approximation of p's x-coordinate (if i == 0), or an 
     *         approximation of p's y-coordinate (if i == 1).
     */
    Approximate_number_type operator() (const Point_2& p,
                                        int i) const
    {
      CGAL_precondition (i == 0 || i == 1);
      return (i == 0) ? (CGAL::to_double(p.x())) : (CGAL::to_double(p.y()));
    }
  };

  /*! Get an Approximate_2 functor object. */
  Approximate_2 approximate_2_object () const
  {
    return Approximate_2();
  }

  class Construct_x_monotone_curve_2
  {
  public:

    /*!
     * Return an x-monotone curve connecting the two given endpoints.
     * \param p The first point.
     * \param q The second point.
     * \pre p and q must not be the same.
     * \return A segment connecting p and q.
     */
    X_monotone_curve_2 operator() (const Point_2& p,
                                   const Point_2& q) const
    {
      return (X_monotone_curve_2 (p, q));
    }
  };

  /*! Get a Construct_x_monotone_curve_2 functor object. */
  Construct_x_monotone_curve_2 construct_x_monotone_curve_2_object () const
  {
    return Construct_x_monotone_curve_2();
  }
  //@}


  /// \name Functor definitions for the Boolean set-operation traits.
  //@{
 
  class Compare_endpoints_xy_2
  {
  public:

    /*!
     * Compare the endpoints of an $x$-monotone curve lexicographically.
     * (assuming the curve has a designated source and target points).
     * \param cv The curve.
     * \return SMALLER if the curve is directed right;
     *         LARGER if the curve is directed left.
     */
    Comparison_result operator() (const X_monotone_curve_2& cv) const
    {
      return (cv.is_directed_right()) ? (SMALLER) : (LARGER);
    }
  };

  /*! Get a Compare_endpoints_xy_2 functor object. */
  Compare_endpoints_xy_2 compare_endpoints_xy_2_object() const
  {
    return Compare_endpoints_xy_2();
  }

  class Construct_opposite_2
  {
  public:

    /*!
     * Construct an opposite x-monotone (with swapped source and target).
     * \param cv The curve.
     * \return The opposite curve.
     */
    X_monotone_curve_2 operator() (const X_monotone_curve_2& cv) const
    {
      return (cv.flip());
    }
  };

  /*! Get a Construct_opposite_2 functor object. */
  Construct_opposite_2 construct_opposite_2_object() const
  {
    return Construct_opposite_2();
  }
  //@}
};

/*!
 * \class A representation of a segment, as used by the Arr_segment_traits_2
 * traits-class.
 */
template <class Kernel_>
class Arr_segment_2 :
    public Arr_segment_traits_2<Kernel_>::_Segment_cached_2
{
  typedef Kernel_                                                  Kernel;
  typedef typename Arr_segment_traits_2<Kernel>::_Segment_cached_2 Base;
  typedef typename Kernel::Segment_2                               Segment_2;
  typedef typename Kernel::Point_2                                 Point_2;
  typedef typename Kernel::Line_2                                  Line_2;

public:

  /*!
   * Default constructor.
   */
  Arr_segment_2 () :
    Base()
  {}
    
  /*!
   * Constructor from a "kernel" segment.
   * \param seg The segment.
   * \pre The segment is not degenerate.
   */
  Arr_segment_2 (const Segment_2& seg) :
    Base(seg)
  {}

  /*!
   * Construct a segment from two end-points.
   * \param source The source point.
   * \param target The target point.
   * \pre The two points are not the same.
   */
  Arr_segment_2 (const Point_2& source, const Point_2& target) :
    Base(source,target)
  {}

  /*!
   * Construct a segment from a line and two end-points.
   * \param line The supporting line.
   * \param source The source point.
   * \param target The target point.
   * \pre Both source and target must be on the supporting line.
   * \pre The two points are not the same.
   */
  Arr_segment_2 (const Line_2& line,
                 const Point_2& source, const Point_2& target) :
    Base(line,source,target)
  {}

  /*!
   * Cast to a segment.
   */
  operator Segment_2 () const
  {
    Kernel     kernel;
    Segment_2  seg = kernel.construct_segment_2_object() (this->ps, this->pt);
    return (seg);
  }

  /*!
   * Create a bounding box for the segment.
   */
  Bbox_2 bbox() const
  {
    Kernel     kernel;
    Segment_2  seg = kernel.construct_segment_2_object() (this->ps, this->pt);
    return (kernel.construct_bbox_2_object() (seg));
  }

  /*!
   * Get the segment source.
   */
  const Point_2& source() const
  { 
    return (this->ps);
  }

  /*!
   * Get the segment target.
   */
  const Point_2& target() const
  {
    return (this->pt);
  }

  /*! Flip the segment (swap its source and target). */
  Arr_segment_2 flip () const
  {
    Arr_segment_2   opp;
    opp.l = this->l;
    opp.ps = this->pt;
    opp.pt = this->ps;
    opp.is_pt_max = !(this->is_pt_max);
    opp.is_vert = this->is_vert;
    opp.is_degen = this->is_degen;
    
    return (opp);
  }
};

/*!
 * Exporter for the segment class used by the traits-class.
 */
template <class Kernel, class OutputStream>
OutputStream& operator<< (OutputStream& os, const Arr_segment_2<Kernel>& seg)
{
  os << static_cast<typename Kernel::Segment_2>(seg);
  return (os);
}

/*!
 * Importer for the segment class used by the traits-class.
 */
template <class Kernel, class InputStream>
InputStream& operator>> (InputStream& is, Arr_segment_2<Kernel>& seg)
{
  typename Kernel::Segment_2   kernel_seg;
  is >> kernel_seg;
  seg = kernel_seg;
  return (is);
}

} //namespace CGAL

#endif
