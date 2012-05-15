CGAL-Mesh
=========

Prototype work on a polyhedral mesh object API using CGAL

INSTALLING CGAL:
---------------

Clone the CGAL repository using:

$ git clone git@github.com:ooici-dm/CGAL-Mesh.git

(or if that does not work, try $ git clone https://github.com/ooici-dm/CGAL-Mesh )

Alternatively, you can go to the website to download the source code (Note: A form has to be filled. But this form
is just for information, and submitting the form will immediately lead to the downloadable source) 

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
$ ./file_name_for_executable

For example, if you are in CGAL-4.0/examples/Polyhedron and you have run the above two make commands, for every .cpp file there
an executable will be generated. So if there is a file, polyhedron_prog_incr_builder.cpp, it will also generate an 
executable, polyhedron_prog_incr_builder, and you can run this executable with the following command:

$ ./polyhedron_prog_incr_builder

And viola! you will see the output spilling on the console.

Now as you start writing your own code, you will make your own .cpp files. In that case, you need to
include them in the CMakeLists.txt in the same directory as the .cpp files you just wrote so that they are compiled too 
when you use cmake.

To do the above, open CMakeLists.txt. You will see several lines like the following:

create_single_source_cgal_program( "polyhedron_prog_incr_builder.cpp" )

If you have created a new file, you need to add a line to CMakeLists.txt for that file. For example:

create_single_source_cgal_program( "my_new_file.cpp" )

Now you can use, cmake ., and make, in succession in order to generate the executables as usual.

REFERENCES:
----------

1. CGAL FAQs: http://www.cgal.org/FAQ.html

I found these FAQs very informative. It lists all the concerns that several users had about how
CGAL could fit their own projects, and the answers from the CGAL team were very honest, direct and
illuminating.

2. CGAL Source files: https://gforge.inria.fr/frs/?group_id=52&release_id=6970

3. Tutorials: http://www.cgal.org/Tutorials/

4. Package Overview : http://www.cgal.org/Manual/latest/doc_html/cgal_manual/packages.html#part_II 

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


