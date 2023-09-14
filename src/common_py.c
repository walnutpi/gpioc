#include "common.h"
#include "common_py.h"


void define_commons(PyObject *module)
{

   PyModule_AddObject(module, "f_INPUT", Py_BuildValue("i", INPUT));
   PyModule_AddObject(module, "f_OUTPUT", Py_BuildValue("i", OUTPUT));

   PyModule_AddObject(module, "f_pull_OFF", Py_BuildValue("i", PUD_OFF));
   PyModule_AddObject(module, "f_pullDown", Py_BuildValue("i", PUD_DOWN));
   PyModule_AddObject(module, "f_pullUp", Py_BuildValue("i", PUD_UP));
}

static PyObject *py_detect(PyObject *self, PyObject *args)
{
    return Py_BuildValue("i", detect());
}

static const char moduledocstring[] = "common pravite";

PyMethodDef common_methods[] = {
   {"detect", py_detect, METH_VARARGS, "detect now chip by device-tree"},
    {NULL, NULL, 0, NULL},
};
static struct PyModuleDef gpiocmodule = {
    PyModuleDef_HEAD_INIT,
    "gpioc._common",      // name of module
    moduledocstring, // module documentation, may be NULL
    -1,              // size of per-interpreter state of the module, or -1 if the module keeps state in global variables.
    common_methods};

// 在import时会被调出来执行
PyMODINIT_FUNC PyInit__common(void)
{
   PyObject *module = NULL;

   if ((module = PyModule_Create(&gpiocmodule)) == NULL)
      return NULL;

   PyModule_AddObject(module, "CHIP_H616", Py_BuildValue("i", CHIP_H616));

   return module;
}

