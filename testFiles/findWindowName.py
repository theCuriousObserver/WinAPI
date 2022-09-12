# Reference: https://www.codegrepper.com/code-examples/python/python+get+list+of+all+open+windows

import win32gui


def winEnumHandler(hwnd, ctx):
    if win32gui.IsWindowVisible(hwnd):
        print(hex(hwnd), win32gui.GetWindowText(hwnd))


win32gui.EnumWindows(winEnumHandler, None)
