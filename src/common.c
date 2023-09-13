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

int detect()
{
    FILE *fp;
    char buffer[1024];
    char *compatible;
    int i;

    fp = fopen("/proc/device-tree/compatible", "r");
    if (fp == NULL)
    {
        printf("Failed to open /proc/device-tree/compatible \n");
        return -1;
    }

    fgets(buffer, 100, fp);
    fclose(fp);

    compatible = strtok(buffer, "\n");

    for (i = 0; i < (int)sizeof(chips_compatible); i++)
    {
        if (strcmp(compatible, chips_compatible[i]) == 0)
        {
            return i;
        }
    }
    return -1;
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

