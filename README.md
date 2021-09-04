lpaggreg
======

__License__

This library is a C++ implementation of several algorithms that enable
to aggregate sets of data according: an ordered dimension (OLP), a
hierarchy (NLP), or both (DLP). 

(C) Copyright (February 28th 2013) Damien Dosimont. All rights reserved.

Damien Dosimont <damien.dosimont@gmail.com>

This library is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 3.0 of the License, or
(at your option) any later version.

This library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
USA.

__Dependancies__

*cmake*

__Generate makefile__

    $ mkdir build
    $ cd build
    $ cmake ..

You may want to install lpaggreg in a custom location:

    $ cmake -DCMAKE_INSTALL_PREFIX=/your/installation/directory/ ..

__Compile__

    $ make
		

__Install__

    # make install
		
__Clean__
		
    $ make clean

__Uninstall__
		
    # make uninstall
