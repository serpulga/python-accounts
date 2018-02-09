import unittest
import getpass
from datetime import datetime

import accounts


class AccountsTestCase(unittest.TestCase):

    def test_get_sessions(self):
        sessions = accounts.get_sessions()
        # If we got to this point it means no memory issues happended
        # inside the extension: segfault, etc.

        # Asserts at least one active session present,
        # which is argualy safe to asume.
        self.assertTrue(len(sessions) > 0)

        for s in sessions:
            # Asserting that each expected dictionary attribute has the correct
            # typing. This is a fair way to test for the overall correctness
            # of the extension since mocking up these low lever system values
            # is difficult.

            self.assertIn('user', s)
            self.assertTrue(issubclass(s['user'].__class__, (str, bytes,)))

            self.assertIn('date_created', s)
            self.assertTrue(issubclass(s['date_created'].__class__, datetime))

            self.assertIn('host', s)
            self.assertTrue(issubclass(s['host'].__class__, (str, bytes,)))

            self.assertIn('pid', s)
            self.assertTrue(issubclass(s['pid'].__class__, int))

            self.assertIn('id', s)
            self.assertTrue(issubclass(s['id'].__class__, int))

            self.assertIn('line', s)
            self.assertTrue(issubclass(s['line'].__class__, (str, bytes,)))

            self.assertIn('session_type', s)
            self.assertTrue(
                issubclass(s['session_type'].__class__, (str, bytes,)))


if __name__ == '__main__':
    unittest.main()
