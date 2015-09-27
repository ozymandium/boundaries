#ifndef BOUNDARIES_PYTHON_CPP
#define BOUNDARIES_PYTHON_CPP


#include "boundaries.hpp"

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/object.hpp>
#include <boost/python/self.hpp>
#include <boost/python/str.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/args.hpp>
#include <boost/python/return_internal_reference.hpp>


namespace py = boost::python;

const char* docstring = "Represent a two-sided boundary class with two possible end conditions";

typedef Boundary<py::object, py::object> BoundaryPython;

// std::string Boundary__str__(const BoundaryPython & self) {
//   return self.toString();
// }

// BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(Boundary_check_overloads, check, 1, 2)


BOOST_PYTHON_MODULE(boundaries)
{
  py::class_<BoundaryPython>("Boundary", docstring)
    .def(py::init<>())
    .def(py::init<py::object, py::object>())
    .def(py::init<std::string>())
    .def(py::init<py::object, py::object, std::string>())
    .def("get_lower", &BoundaryPython::getLower)
    .def("get_upper", &BoundaryPython::getUpper)
    .def("get_rule",  &BoundaryPython::getRule)
    .def("check",     &BoundaryPython::check<py::object>)
    // .def("__str__",   &BoundaryPython::toString)
    .def(py::self_ns::str(py::self_ns::self))
  ;
}


#endif