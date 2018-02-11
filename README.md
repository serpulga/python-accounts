# Python Accounts

Access login and session information directly from Python.


### Usage


1. `accounts.get_sessions`: Get information about each current active session:
    - `"user"`: User owner of the session
    - `"date_created"` : Date when the session was created
    - `"host"`: Host of the session
    - `"pid"`: PID of the session
    - `"id"`: ID of the session
    - `"line"`: Line of the session [`"tty1"`, `"tty2"`, ...]
    - `"session_type"`: Type of the session:

        `"EMPTY"` `"RUN_LVL"` `"BOOT_TIME"` `"NEW_TIME"` `"OLD_TIME"`

        `"INIT_PR"` `"LOGIN_PR"` `"USER_PR"` `"DEAD_PR"`

2. `accounts.get_lastlogin`: Get last login of the user given in the argument.

```python
import accounts

sessions = accounts.get_sessions()
lastlogin = accounts.get_lastlogin('theuser')
```
