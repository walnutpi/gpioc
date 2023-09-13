#include <Python.h>
#include "common.h"



static const char moduledocstring[] = "common pravite";

PyMethodDef common_methods[] = {
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
   // printf("PyInit__h616\r\n");
   PyObject *module = NULL;

   if ((module = PyModule_Create(&gpiocmodule)) == NULL)
      return NULL;

   PyModule_AddObject(module, "CHIP_H616", Py_BuildValue("i", CHIP_H616));

   return module;
}
