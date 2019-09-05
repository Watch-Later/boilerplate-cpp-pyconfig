#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>
#include <fstream>
#include <iostream>
#include <string>


class PythonEnvironment
{
    boost::python::object global_ns_;

public:
    PythonEnvironment()
    {
        Py_Initialize();
        global_ns_ = boost::python::import("__main__").attr("__dict__");
    }


    ~PythonEnvironment()
    { }


    boost::python::object& global_ns() { return global_ns_; }
};


int main(int argc, char* argv[])
{
    std::ifstream ifs(argv[1]);
    std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    PythonEnvironment env;
    try
    {
        boost::python::exec(str.c_str(), env.global_ns(), env.global_ns());

        std::cout << "global_integer = " << boost::python::extract<int>(env.global_ns()["global_integer"]) << "\n";
        std::cout << "global_double = " << boost::python::extract<double>(env.global_ns()["global_double"]) << "\n";
        std::cout << "global_bool = " << boost::python::extract<bool>(env.global_ns()["global_bool"]) << "\n";
        std::cout << "global_string = " << boost::python::extract<char*>(env.global_ns()["global_string"]) << "\n";
    }
    catch (...)
    {
        PyErr_Print();
    }
    

    
    return 0;
}
