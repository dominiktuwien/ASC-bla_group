.. ASC-bla_group documentation master file, created by
   sphinx-quickstart on Thu Nov  9 10:56:49 2023.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to ASC-bla_group's documentation!
=========================================
This is a C++ library for basic linear algebra operations, derived from the ASC-bla library,
and augmented by Daniel, Dominik, Felix and Sebastian.
The library provides template classes **Vector** and **Matrix**.

Installation is via git-clone:

..  code-block::
    
    git clone https://github.com/dominiktuwien/ASC-bla_group.git


To configure and build some tests do

..  code-block::

    cd ASC-bla
    mkdir build
    cd build
    cmake ..
    make
    

To use ASC-bla in your code, set the compiler include path properly, and include the header files

..  code-block::

    #include <vector.h>
    #include <matrix.h>

All objects are implemented in the namespace ASC_bla. To use them with less typing, you can set

..  code-block::
    
    namespace bla = ASC_bla;

There are different opperatons possible including matrix multiplication, matrix-vector multiplications and
other basic operations.

.. toctree::
   :maxdepth: 2
   :caption: Contents:



Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
