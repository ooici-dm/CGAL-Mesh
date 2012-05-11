#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/Polyhedron_3.h>
#include <iostream>
#include <CGAL/IO/Polyhedron_iostream.h>

// A modifier creating a triangle with the incremental builder.
template <class HDS>
class Build_triangle : public CGAL::Modifier_base<HDS> {
public:
    Build_triangle() {}
    void operator()( HDS& hds) {
        // Postcondition: `hds' is a valid polyhedral surface.
        CGAL::Polyhedron_incremental_builder_3<HDS> B( hds, true);
        B.begin_surface( 4, 2, 12);
        typedef typename HDS::Vertex   Vertex;
        typedef typename Vertex::Point Point;
        B.add_vertex( Point( 0, 0, 0));
        B.add_vertex( Point( 1, 0, 0));
        B.add_vertex( Point( 0, 1, 0));
        B.add_vertex( Point( 1, 1, 1));

        B.begin_facet();
        B.add_vertex_to_facet( 0);
        B.add_vertex_to_facet( 1);
        B.add_vertex_to_facet( 3); // for unknown reason, there is a segmentation fault when vertex 2 is added instead of 3
        B.end_facet();

        B.begin_facet();
		B.add_vertex_to_facet( 1);
		B.add_vertex_to_facet( 2);
		B.add_vertex_to_facet( 3);
		B.end_facet();

        B.end_surface();
    }
};
//
//// A modifier adding a point that will be a part of a second triangle with the incremental builder.
//template <class HDS>
//class Add_point_to_triangle_mesh : public CGAL::Modifier_base<HDS> {
//public:
//	Add_point_to_triangle_mesh() {}
//    void operator()( HDS& hds) {
//        // Postcondition: `hds' is a valid polyhedral surface.
//        CGAL::Polyhedron_incremental_builder_3<HDS> B( hds, true);
//        B.begin_surface( 3, 1, 6);
//        typedef typename HDS::Vertex   Vertex;
//        typedef typename Vertex::Point Point;
//
//
//        B.begin_facet();
//        B.add_vertex_to_facet( 1);
//        B.add_vertex_to_facet( 2);
//        B.end_facet();
//
//        B.end_surface();
//    }
//};


typedef CGAL::Simple_cartesian<double>     Kernel;
typedef CGAL::Polyhedron_3<Kernel>         Polyhedron;
typedef Polyhedron::HalfedgeDS             HalfedgeDS;

int main() {
    Polyhedron P;
    Build_triangle<HalfedgeDS> triangle;
    P.delegate( triangle);
    CGAL_assertion( P.is_triangle( P.halfedges_begin()));
    
    CGAL::set_pretty_mode(std::cout);
    
    std::cout << "Success creating two triangles: "
                  << std::endl;
    
    std::cout << "The polyhedron created at this stage" << P << std::endl;
    

    return 0;
}
