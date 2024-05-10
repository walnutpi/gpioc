#include <Python.h>




static PyObject *py_set_duty_cycle(PyObject *self, PyObject *args)
{
    int ret;
    int gpio_num, dutycycle;
    ret = PyArg_ParseTuple(args, "ii", &gpio_num, &dutycycle);
    pwm_set_duty_cycle(gpio_num, dutycycle);
    Py_RETURN_NONE;
}
static PyObject *py_set_frequency(PyObject *self, PyObject *args)
{
    int ret;
    int gpio_num, freq;
    ret = PyArg_ParseTuple(args, "ii", &gpio_num, &freq);
    pwm_set_frequency(gpio_num, freq);
    Py_RETURN_NONE;
}

static PyObject *py_get_duty_cycle(PyObject *self, PyObject *args)
{
    int ret;
    int gpio_num;
    ret = PyArg_ParseTuple(args, "i", &gpio_num);
    return Py_BuildValue("i", pwm_get_duty_cycle(gpio_num));
}

static PyObject *py_get_frequency(PyObject *self, PyObject *args)
{
    int ret;
    int gpio_num;
    ret = PyArg_ParseTuple(args, "i", &gpio_num);
    return Py_BuildValue("i", pwm_get_frequency(gpio_num));
}




static PyObject *py_start(PyObject *self, PyObject *args)
{
    int ret;
    int gpio_num;
    ret = PyArg_ParseTuple(args, "i", &gpio_num);
    pwm_start(gpio_num);
    Py_RETURN_NONE;
}
static PyObject *py_stop(PyObject *self, PyObject *args)
{
    int ret;
    int gpio_num;
    ret = PyArg_ParseTuple(args, "i", &gpio_num);
    pwm_stop(gpio_num);
    Py_RETURN_NONE;
}
static PyObject *py_exists(PyObject *self, PyObject *args)
{
    int ret;
    int gpio_num;
    ret = PyArg_ParseTuple(args, "i", &gpio_num);
    pwm_exists(gpio_num);
    Py_RETURN_NONE;
}

static const char moduledocstring[] = "soft pwm";

PyMethodDef pwm_methods[] = {
    {"get_duty_cycle", py_get_duty_cycle, METH_VARARGS, "get_duty_cycle with gpio num"},
    {"get_frequency", py_get_frequency, METH_VARARGS, "get_frequency with gpio num"},
    {"set_duty_cycle", py_set_duty_cycle, METH_VARARGS, "set_duty_cycle with gpio num"},
    {"set_frequency", py_set_frequency, METH_VARARGS, "set_frequency with gpio num"},
    {"start", py_start, METH_VARARGS, "start pwm output"},
    {"stop", py_stop, METH_VARARGS, "stop pwm"},
    {"exists", py_exists, METH_VARARGS, "exists"},

};
static struct PyModuleDef module_pinctrl = {
    PyModuleDef_HEAD_INIT,
    "gpioc._pwm",      // name of module
    moduledocstring, // module documentation, may be NULL
    -1,              // size of per-interpreter state of the module, or -1 if the module keeps state in global variables.
    pwm_methods};

// 在import时会被调出来执行
PyMODINIT_FUNC PyInit__softpwm(void)
{
    PyObject *module = NULL;

    if ((module = PyModule_Create(&module_pinctrl)) == NULL)
        return NULL;

    return module;
}
