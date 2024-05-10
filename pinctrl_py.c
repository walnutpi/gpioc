#include <Python.h>

#include "pinctrl.h"

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
    gpio_set_mode(gpio_num, mode);
    Py_RETURN_NONE;
}

static const char moduledocstring[] = "GPIO functionality";

PyMethodDef pinctrl_methods[] = {
    {"write", py_write, METH_VARARGS, "write value to gpio"},
    {"read", py_read, METH_VARARGS, "read value from gpio"},
    {"set_pullUpDn", py_set_PullUpDn, METH_VARARGS, "set the gpio with pullup or pulldown"},
    {"set_mode", py_set_mode, METH_VARARGS, "set the gpio mode with in or out"},
    {NULL, NULL, 0, NULL},
};
static struct PyModuleDef module_pinctrl = {
    PyModuleDef_HEAD_INIT,
    "gpioc._pinctrl",      // name of module
    moduledocstring, // module documentation, may be NULL
    -1,              // size of per-interpreter state of the module, or -1 if the module keeps state in global variables.
    pinctrl_methods};

// 在import时会被调出来执行
PyMODINIT_FUNC PyInit__pinctrl(void)
{
    PyObject *module = NULL;

    if ((module = PyModule_Create(&module_pinctrl)) == NULL)
        return NULL;
    
    return module;
}
