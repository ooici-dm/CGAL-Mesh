CGAL-Mesh
=========

Prototype work on a polyhedral mesh object API using CGAL

Installing CGAL:

Clone the CGAL repository using,
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

This will compile all the cpp files in that directory (actually it will compile all the .cpp files mentioned in the 
CMakeLists.txt file in that same directory, but I will come to that piece next).

The executables are going to be generated in the same folder. To run the executable, 
$ ./file_name_for_executable

For example, if you are in CGAL-4.0/examples/Polyhedron, and you have run the above two make commands, if there is a file, 
polyhedron_prog_incr_builder.cpp, it will generate an executable, polyhedron_prog_incr_builder, and to run this 
executable, do the following:
$ ./polyhedron_prog_incr_builder

And viola! you will see the output spilling on the console.

Now as you start writing your own code, you will make your own .cpp files. In that case, you need to
include them in the CMakeLists.txt in the same directory as the .cpp files so that they are compiled too when you run 
cmake.

To do the above, open CMakeLists.txt. You will see several lines like the following:

create_single_source_cgal_program( "polyhedron_prog_incr_builder.cpp" )

If you have created a new file, you need to add a line to CMakeLists.txt for that file. For example:
create_single_source_cgal_program( "my_new_file.cpp" )

Now you can use, cmake ., and make, in succession in order to generate the executables as usual.
