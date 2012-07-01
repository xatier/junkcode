#!/usr/bin/python
import ctypes
libc = ctypes.LoadLibrary("kerker.so")
libc.func(19)

