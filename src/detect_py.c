#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

#include "detect.h"

static PyObject *py_detect(PyObject *self, PyObject *args)
{
    return Py_BuildValue("i", detect());
}

static const char moduledocstring[] = "GPIO functionality of allwinner chips ";

PyMethodDef methods[] = {
    {"detect", py_detect, METH_VARARGS, "detect now chip by device-tree"},
    {NULL, NULL, 0, NULL},
};
static struct PyModuleDef gpiocmodule = {
    PyModuleDef_HEAD_INIT,
    "gpioc._detect", // name of module
    moduledocstring, // module documentation, may be NULL
    -1,              // size of per-interpreter state of the module, or -1 if the module keeps state in global variables.
    methods};

// 在import时会被调出来执行
PyMODINIT_FUNC PyInit__detect(void)
{
    PyObject *module = NULL;

    if ((module = PyModule_Create(&gpiocmodule)) == NULL)
        return NULL;

    return module;
}