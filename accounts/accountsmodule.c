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

        ts_unix = (double)ut->ut_tv.tv_sec + (double)ut->ut_tv.tv_usec / 1e6;
        timestamp = Py_BuildValue("f", ts_unix);
        ts_args = Py_BuildValue("(O)", timestamp);
        date = PyDateTime_FromTimestamp(ts_args);
        PyDict_SetItemString(session, "date_created", date);

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

        pid = Py_BuildValue("l", ut->ut_pid);
        PyDict_SetItemString(session, "pid", pid);

        host = PyUnicode_FromString(ut->ut_host);
        PyDict_SetItemString(session, "host", host);

        id = Py_BuildValue("l", ut->ut_id);
        PyDict_SetItemString(session, "id", id);

        line = PyUnicode_FromString(ut->ut_line);
        PyDict_SetItemString(session, "line", line);

        PyList_Append(sessions, session);
    }

    endutxent();

    return sessions;
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
