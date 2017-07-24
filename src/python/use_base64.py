#!/usr/bin/env python3

import base64

def safe_base64_decode(s):
    d=[s]
    m=len(s)%4
    for i in range(m):
        d.append(b'=')
    return base64.b64decode(b''.join(d))

assert b'abcd' == safe_base64_decode(b'YWJjZA=='), safe_base64_decode('YWJjZA==')
assert b'abcd' == safe_base64_decode(b'YWJjZA'), safe_base64_decode('YWJjZA')
print('Pass')

