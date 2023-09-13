#include <Python.h>
#include "common.h"


void define_commons(PyObject *module)
{

   PyModule_AddObject(module, "f_INPUT", Py_BuildValue("i", INPUT));
   PyModule_AddObject(module, "f_OUTPUT", Py_BuildValue("i", OUTPUT));

   PyModule_AddObject(module, "f_pull_OFF", Py_BuildValue("i", PUD_OFF));
   PyModule_AddObject(module, "f_pullDown", Py_BuildValue("i", PUD_DOWN));
   PyModule_AddObject(module, "f_pullUp", Py_BuildValue("i", PUD_UP));
}