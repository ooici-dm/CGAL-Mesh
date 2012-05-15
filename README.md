CGAL-Mesh
=========

Prototype work on a polyhedral mesh object API using CGAL:
---------------------------------------------------------

The following modules were added or modified:

1. Added polyhedron_prog_incr_builder_sw_1.cpp - This module creates two triangles on the same polyhedron. It makes an include
                                         call to a cgal header file, specific to polyhedra, which enables printing
                                         the polyhedron objects in "pretty mode", so that one can easily visualize
                                         the objects that are created. In this module the polyhedron object is
                                         printed on the console after creating one triangle and then again after creating
                                         anothe one. A lot of valuable information can be gleaned from the output.
                                    
2. Added polyhedron_prog_incr_builder_sw_triangle.cpp - This module creates two triangles on a polyhedron and then implements
                                                      a method which runs within loops the iterators for the different 
                                                      entities in the polyhedron. The three kinds of iterators used in this 
                                                      example are vertex iterators, edge iterators and facet iterators. 
                                              
3. Modified polyhedron_prog_incr_builder.cpp - The modified module creates a quadrilateral and implements two
                                             methods. The first method implements iterator loops that run over the whole 
                                             polyhedron. The second method implements iterator loops that run over quads
                                             defined over the polyhedron.

4. Added polyhedron_prog_incr_builder_backup.cpp - This module is just a backup copy of the original polyhedron_prog_incr_builder.cpp
                                                 - that comes with the source code from the cgal website.

INSTALLING CGAL:
---------------

Clone the CGAL repository using:

$ git clone git@github.com:ooici-dm/CGAL-Mesh.git

(or if that does not work, try $ git clone https://github.com/ooici-dm/CGAL-Mesh )

Alternatively, you can download the source code:

https://gforge.inria.fr/frs/?group_id=52&release_id=6970

After you have the repository in a directory of your choosing (let us say you have called it CGAL-4.0), you need to set 
the environment variable, CGAL_DIR, so that CGAL can find its files in order to run:
$ export CGAL_DIR=/path/to/CGAL-4.0

Now you are in the business of compiling and running CGAL. 

Go to any directory (or subdirectory) of your interest. If there are any .cpp files there which you might like to compile,
run the following commands in the same directory where the .cpp files are:

$ cmake .

$ make

This will compile all the .cpp files in that directory (actually it will compile all the .cpp files mentioned in the 
CMakeLists.txt file in that same directory, but I will come to that piece next).

The executables are going to be generated in the same folder. To run the executable, 
$ ./file_name

For example, if you are in CGAL-4.0/examples/Polyhedron and you have already run the above two make commands, then for every .cpp file,
an executable would have been generated. Therefore if there was a .cpp file, polyhedron_prog_incr_builder.cpp, it would
have also generated an executable, polyhedron_prog_incr_builder. You can now run this executable using the following 
command:

$ ./polyhedron_prog_incr_builder

And viola! you will see the output spilling on the console.

Now as you start writing your own code, you need to include them in the CMakeLists.txt that is already there in the same directory 
so that they are compiled too  when you use cmake.

To do the above, open CMakeLists.txt. You will see several lines like the following:

create_single_source_cgal_program( "polyhedron_prog_incr_builder.cpp" )

If you have created a new file, you need to add a line to CMakeLists.txt for that file. For example:

create_single_source_cgal_program( "my_new_file.cpp" )

Now you can use, cmake ., and make, in succession in order to generate the executables as usual.

REFERENCES:
----------

1. CGAL FAQs: I found the FAQs below very informative. They list all the concerns that several users had about how CGAL could fit their own 
projects, and the answers from the CGAL team were honest, direct and very illuminating.

http://www.cgal.org/FAQ.html


2. CGAL Source files: 

https://gforge.inria.fr/frs/?group_id=52&release_id=6970

3. Tutorials: 

http://www.cgal.org/Tutorials/

4. Package Overview : 

http://www.cgal.org/Manual/latest/doc_html/cgal_manual/packages.html#part_II 

5. Installation Guide: 

http://www.cgal.org/Manual/latest/doc_html/installation_manual/Chapter_installation_manual.html#Section_1

6. CGAL-Python bindings:  The CGAL team does not maintain the project anymore. They recommend that if programmers want
to write python binding for the cgal code, they could use SWIG.

http://cgal-python.gforge.inria.fr/

7. CGAL Polyhedron class: 

http://graphics.stanford.edu/courses/cs368-00-spring/TA/manuals/CGAL/ref-manual2/Polyhedron/Polyhedron_3.html

http://www.cgal.org/Manual/latest/doc_html/cgal_manual/Polyhedron_ref/Class_Polyhedron_3-Traits---Halfedge.html

8. CGAL half edge:

http://graphics.stanford.edu/courses/cs368-00-spring/TA/manuals/CGAL/ref-manual2/Polyhedron/Halfedge.html#Cross_link_anchor_2

9. CGAL Vertex:

http://graphics.stanford.edu/courses/cs368-00-spring/TA/manuals/CGAL/ref-manual2/Polyhedron/Vertex.html#Cross_link_anchor_1

10. CGAL Facet:

http://graphics.stanford.edu/courses/cs368-00-spring/TA/manuals/CGAL/ref-manual2/Polyhedron/Facet.html#Cross_link_anchor_3


