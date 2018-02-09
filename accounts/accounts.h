#ifndef ACCOUNTS_ACCOUNTS_H
#define ACCOUNTS_ACCOUNTS_H

#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <time.h>
#include <utmpx.h>
#include <paths.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <datetime.h>


static PyObject * get_accounts(PyObject *, PyObject*);

static struct PyModuleDef accountsmodule;

PyMODINIT_FUNC PyInit_accounts(void);

#endif // ACCOUNTS_ACCOUNTS_H
