#include <sstream>
#include <pybind11/pybind11.h>

#include "vector.h"
#include "Matrix-Neu-using_expressions.h"
#include "matexpression.h"

using namespace ASC_bla;
namespace py = pybind11;


PYBIND11_MODULE(bla, m) {
    m.doc() = "Basic linear algebra module"; // optional module docstring
    
    py::class_<Vector<double>> (m, "Vector")
      .def(py::init<size_t>(),
           py::arg("size"), "create vector of given size")
      .def("__len__", &Vector<double>::Size,
           "return size of vector")
      
      .def("__setitem__", [](Vector<double> & self, int i, double v) {
        if (i < 0) i += self.Size();
        if (i < 0 || i >= self.Size()) throw py::index_error("vector index out of range");
        self(i) = v;
      })
      .def("__getitem__", [](Vector<double> & self, int i) { return self(i); })
      
      .def("__setitem__", [](Vector<double> & self, py::slice inds, double val)
      {
        size_t start, stop, step, n;
        if (!inds.compute(self.Size(), &start, &stop, &step, &n))
          throw py::error_already_set();
        self.Range(start, stop).Slice(0,step) = val;
      })
      
      .def("__add__", [](Vector<double> & self, Vector<double> & other)
      { return Vector<double> (self+other); })

      .def("__rmul__", [](Vector<double> & self, double scal)
      { return Vector<double> (scal*self); })
      
      .def("__str__", [](const Vector<double> & self)
      {
        std::stringstream str;
        str << self;
        return str.str();
      })

     .def(py::pickle(
        [](Vector<double> & self) { // __getstate__
            /* return a tuple that fully encodes the state of the object */
          return py::make_tuple(self.Size(),
                                py::bytes((char*)(void*)&self(0), self.Size()*sizeof(double)));
        },
        [](py::tuple t) { // __setstate__
          if (t.size() != 2)
            throw std::runtime_error("should be a 2-tuple!");

          Vector<double> v(t[0].cast<size_t>());
          py::bytes mem = t[1].cast<py::bytes>();
          std::memcpy(&v(0), PYBIND11_BYTES_AS_STRING(mem.ptr()), v.Size()*sizeof(double));
          return v;
        }))
    ;
    py::class_<Matrix<double,ORDERING::RowMajor>> (m, "Matrix")
    .def(py::init<size_t,size_t>(),
         py::arg("height"), py::arg("width"),
         "create matrix of height times width" )
    .def("__width__", &Matrix<double,ORDERING::RowMajor>::Get_width,
         "return with of Matrix")
    .def("__height__", &Matrix<double, ORDERING::RowMajor>::Get_height,
        "return height of Matrix")
    .def("__size__", &Matrix<double,ORDERING::RowMajor>::Size,
        "return size of Matrix")
    .def("__dist__", &Matrix<double,ORDERING::RowMajor>::Dist,
        "return dist of Matrix")

    .def("__getitem__",
      [](Matrix<double, RowMajor> self, std::tuple<int, int> ind) {
           return self(std::get<0>(ind), std::get<1>(ind));
      })
    .def("__setitem__",
      [](Matrix<double,RowMajor> self, std::tuple<int,int> ind, double val) {
            self(std::get<0>(ind), std::get<1>(ind)) = val;
      })
    .def_property_readonly("shape",
      [](const Matrix<double, RowMajor>& self) {
           return std::tuple(self.Get_width(), self.Get_height());
      })

    .def("__add__", [](Matrix<double,ORDERING::RowMajor> & self, Matrix<double,ORDERING::RowMajor> & other)
    { return (Matrix<double,ORDERING::RowMajor> (self) + Matrix<double,ORDERING::RowMajor> (other)); })

    .def("__sub__",[](Matrix<double,ORDERING::RowMajor> & self, Matrix<double,ORDERING::RowMajor> & other)
    { return (Matrix<double,ORDERING::RowMajor> (self) - Matrix<double,ORDERING::RowMajor> (other)); })

    .def("__matmul__", [](Matrix<double,ORDERING::RowMajor> & self, Matrix<double,ORDERING::RowMajor> & other)
    { return (Matrix<double,ORDERING::RowMajor> (self) * Matrix<double,ORDERING::RowMajor> (other)); })
    
    .def("__scalmul__", [](double scal, Matrix<double,ORDERING::RowMajor> & other)
    { return (scal * Matrix<double,ORDERING::RowMajor> (other)); })   
    ;
}
