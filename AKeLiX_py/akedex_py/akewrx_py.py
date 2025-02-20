"""
Akai Keisanki Definition eXperiments for Python - Akai Keisanki Wrapper eXperiments for Python
"""

class Wrapper[T](object):
    def __init__(self, x : T) -> None:
        self.obj : T = x
