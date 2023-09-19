#include <Python.h>

// #include "h616.h"
// #include "common_py.h"
#include "gpioc.h"

void define_commons(PyObject *module)
{
    PyModule_AddObject(module, "CHIP_H616", Py_BuildValue("i", CHIP_H616));

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

static PyObject *py_write(PyObject *self, PyObject *args)
{
    int ret;
    int gpio_num, value;
    ret = PyArg_ParseTuple(args, "ii", &gpio_num, &value);

    // printf("ret=%d\r\n", ret);
    // printf("gpio_num=%d\r\n", gpio_num);
    // printf("value=%d\r\n", value);

    gpio_write(gpio_num, value);

    Py_RETURN_NONE;
}
static PyObject *py_read(PyObject *self, PyObject *args)
{
    int ret;
    int gpio_num;
    ret = PyArg_ParseTuple(args, "i", &gpio_num);

    return Py_BuildValue("i", gpio_read(gpio_num));
}
static PyObject *py_set_PullUpDn(PyObject *self, PyObject *args)
{
    int ret;
    int gpio_num, pud;
    ret = PyArg_ParseTuple(args, "ii", &gpio_num, &pud);

    gpio_set_pullUpDn(gpio_num, pud);

    Py_RETURN_NONE;
}
static PyObject *py_set_mode(PyObject *self, PyObject *args)
{
    int ret;
    int gpio_num, mode;
    ret = PyArg_ParseTuple(args, "ii", &gpio_num, &mode);
    gpio_set_Mode(gpio_num, mode);
    Py_RETURN_NONE;
}
static PyObject *py_set_alt(PyObject *self, PyObject *args)
{
    int ret;
    int gpio_num, mode;
    ret = PyArg_ParseTuple(args, "ii", &gpio_num, &mode);
    gpio_set_Alt(gpio_num, mode);
    Py_RETURN_NONE;
}
static PyObject *py_get_alt(PyObject *self, PyObject *args)
{
    int ret;
    int gpio_num;
    ret = PyArg_ParseTuple(args, "i", &gpio_num);

    return Py_BuildValue("i", gpio_get_Alt(gpio_num));
}

static const char moduledocstring[] = "GPIO functionality of allwinner h616";

PyMethodDef gpioc_methods[] = {
    {"detect", py_detect, METH_VARARGS, "detect now chip by device-tree"},
    {"write", py_write, METH_VARARGS, "write value to gpio"},
    {"read", py_read, METH_VARARGS, "read value from gpio"},
    {"set_pullUpDn", py_set_PullUpDn, METH_VARARGS, "set the gpio with pullup or pulldown"},
    {"set_mode", py_set_mode, METH_VARARGS, "set the gpio mode with in or out"},
    {"set_alt", py_set_alt, METH_VARARGS, "set the pin mode functiont"},
    {"get_alt", py_get_alt, METH_VARARGS, "get the pin mode functiont"},
    {NULL, NULL, 0, NULL},
};
static struct PyModuleDef gpiocmodule = {
    PyModuleDef_HEAD_INIT,
    "gpioc._gpioc",  // name of module
    moduledocstring, // module documentation, may be NULL
    -1,              // size of per-interpreter state of the module, or -1 if the module keeps state in global variables.
    gpioc_methods};

// 在import时会被调出来执行
PyMODINIT_FUNC PyInit__gpioc(void)
{
    // printf("PyInit__h616\r\n");
    PyObject *module = NULL;

    if ((module = PyModule_Create(&gpiocmodule)) == NULL)
        return NULL;

    define_commons(module);

    return module;
}
