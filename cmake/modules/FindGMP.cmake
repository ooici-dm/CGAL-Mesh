# Try to find the GMP libraries
# GMP_FOUND - system has GMP lib
# GMP_INCLUDE_DIR - the GMP include directory
# GMP_LIBRARIES_DIR - Directory where the GMP libraries are located
# GMP_LIBRARIES - the GMP libraries
# GMP_IN_CGAL_AUXILIARY - TRUE if the GMP found is the one distributed with CGAL in the auxiliary folder

# TODO: support MacOSX

include(CGAL_FindPackageHandleStandardArgs)
include(CGAL_GeneratorSpecificSettings)

if(GMP_INCLUDE_DIR)
  set(GMP_in_cache TRUE)
else()
  set(GMP_in_cache FALSE)
endif()
if(NOT GMP_LIBRARIES)
  set(GMP_in_cache FALSE)
endif()

# Is it already configured?
if (GMP_in_cache)
   
  set(GMP_FOUND TRUE)
  
else()  

  find_path(GMP_INCLUDE_DIR 
            NAMES gmp.h 
            PATHS ENV GMP_INC_DIR
                  ${CGAL_INSTALLATION_PACKAGE_DIR}/auxiliary/gmp/include
  	        DOC "The directory containing the GMP header files"
           )

  if ( GMP_INCLUDE_DIR STREQUAL "${CGAL_INSTALLATION_PACKAGE_DIR}/auxiliary/gmp/include" )
    cache_set( GMP_IN_CGAL_AUXILIARY TRUE )
  endif()
  
  find_library(GMP_LIBRARIES NAMES gmp libgmp-10
    PATHS ENV GMP_LIB_DIR
    ${CGAL_INSTALLATION_PACKAGE_DIR}/auxiliary/gmp/lib
    DOC "Path to the GMP library"
    )
  
  if ( GMP_LIBRARIES ) 
    get_filename_component(GMP_LIBRARIES_DIR ${GMP_LIBRARIES} PATH CACHE )
  endif()
    
  # Attempt to load a user-defined configuration for GMP if couldn't be found
  if ( NOT GMP_INCLUDE_DIR OR NOT GMP_LIBRARIES_DIR )
    include( GMPConfig OPTIONAL )
  endif()
  
  find_package_handle_standard_args(GMP "DEFAULT_MSG" GMP_LIBRARIES GMP_INCLUDE_DIR)
  
endif()
