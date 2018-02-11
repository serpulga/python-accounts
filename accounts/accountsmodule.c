#include "accounts.h"


static PyObject * get_sessions(PyObject * mos, PyObject * args)
{
    struct utmpx *ut;
    PyObject * sessions = PyList_New(0);

    setutxent();
    while ((ut = getutxent()) != NULL) {
        double ts_unix;
        const char * session_type;
        PyObject * user;
        PyObject * timestamp;
        PyObject * ts_args;
        PyObject * date;
        PyObject * type;
        PyObject * pid;
        PyObject * host;
        PyObject * id;
        PyObject * line;
        PyObject * session = PyDict_New();

        user = PyUnicode_FromString(ut->ut_user);
        PyDict_SetItemString(session, "user", user);
        Py_DECREF(user);

        ts_unix = (double)ut->ut_tv.tv_sec + (double)ut->ut_tv.tv_usec / 1e6;
        timestamp = Py_BuildValue("f", ts_unix);
        ts_args = Py_BuildValue("(O)", timestamp);
        date = PyDateTime_FromTimestamp(ts_args);
        PyDict_SetItemString(session, "date_created", date);
        Py_DECREF(timestamp);
        Py_DECREF(ts_args);
        Py_DECREF(date);

        session_type = (ut->ut_type == EMPTY) ?         "EMPTY" :
                       (ut->ut_type == RUN_LVL) ?       "RUN_LVL" :
                       (ut->ut_type == BOOT_TIME) ?     "BOOT_TIME" :
                       (ut->ut_type == NEW_TIME) ?      "NEW_TIME" :
                       (ut->ut_type == OLD_TIME) ?      "OLD_TIME" :
                       (ut->ut_type == INIT_PROCESS) ?  "INIT_PR" :
                       (ut->ut_type == LOGIN_PROCESS) ? "LOGIN_PR" :
                       (ut->ut_type == USER_PROCESS) ?  "USER_PR" :
                       (ut->ut_type == DEAD_PROCESS) ?  "DEAD_PR" : "???";
        type = PyUnicode_FromString(session_type);
        PyDict_SetItemString(session, "session_type", type);
        Py_DECREF(type);

        pid = Py_BuildValue("l", ut->ut_pid);
        PyDict_SetItemString(session, "pid", pid);
        Py_DECREF(pid);

        host = PyUnicode_FromString(ut->ut_host);
        PyDict_SetItemString(session, "host", host);
        Py_DECREF(host);

        id = Py_BuildValue("l", ut->ut_id);
        PyDict_SetItemString(session, "id", id);
        Py_DECREF(id);

        line = PyUnicode_FromString(ut->ut_line);
        PyDict_SetItemString(session, "line", line);
        Py_DECREF(line);

        PyList_Append(sessions, session);
        Py_DECREF(session);
    }

    endutxent();

    return sessions;
}

static PyObject * get_lastlogin(PyObject * mos, PyObject * args)
{
    struct lastlogx * llog = NULL;
    const char * name;
    double ts_unix;

    if (!PyArg_ParseTuple(args, "s", &name))
        return NULL;

    setutxent();
    llog = getlastlogxbyname(name, llog);
    if (llog == NULL) {
        endutxent();
        return NULL;
    }

    ts_unix = (double)llog->ll_tv.tv_sec + (double)llog->ll_tv.tv_usec / 1e6;
    PyObject * timestamp = Py_BuildValue("f", ts_unix);
    PyObject * ts_args = Py_BuildValue("(O)", timestamp);
    PyObject * date = PyDateTime_FromTimestamp(ts_args);
    Py_DECREF(timestamp);
    Py_DECREF(ts_args);
    free(llog);

    endutxent();

    return date;
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
    {
        "get_lastlogin",
        get_lastlogin,
        METH_VARARGS,
        "Retrieves the last login date time for a given user."
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
