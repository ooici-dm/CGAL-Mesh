#!/usr/bin/python

# Copyright (c) 2011  GeometryFactory Sarl (France)
#
# This file is part of CGAL (www.cgal.org); you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation; either version 3 of the License,
# or (at your option) any later version.
#
# Licensees holding a valid commercial license may use this file in
# accordance with the commercial license agreement provided with the software.
#
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
# $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/next/Installation/auxiliary/gdb/test-gdb.py $
# $Id: test-gdb.py 67154 2012-01-16 13:56:46Z lrineau $
#
# Author(s)     : Laurent Rineau


import sys
import os
import gdb

sys.path.insert(0, os.getcwd() + '/python')

import CGAL.printers
