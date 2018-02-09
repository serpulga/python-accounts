#include "accounts.h"


static PyObject * get_sessions(PyObject * mos, PyObject * args)
{
    return Py_BuildValue("s", "PyCon Medellin 2018");
}

PyMODINIT_FUNC PyInit_accounts(void)
{
    PyObject *m;

    m = PyModule_Create(&accountsmodule);
    if (m == NULL)
        return NULL;

    PyDateTime_IMPORT;
    return m;
}

static PyMethodDef AccountsMethods[] = {
    {
        "get_sessions",
        get_sessions,
        METH_VARARGS,
        "Retrieves current sessions."
    },
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef accountsmodule = {
    PyModuleDef_HEAD_INIT,
    "accounts",        /* name of module */
    NULL,              /* module documentation, may be NULL */
    -1,                /* size of per-interpreter state of the module,
                          or -1 if the module keeps state in
                          global variables. */
    AccountsMethods
};
