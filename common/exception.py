"""
PL0 编译器相关Exception
"""

class Error(Exception):
    """Base class for exceptions for pl0 comlier."""
    pass

class LexerError(Error):
    """Exception raised for errors of Lexer.

    Attributes:
        message -- explanation of the error
    """

    def __init__(self, message):
        self.message = message
    
    def __str__(self):
        return repr(self.message)

class SyntaxError(Error):
    """Exception raised for errors of Syntax.

    Attributes:
        message -- explanation of the error
    """

    def __init__(self, message):
        self.message = message
    
    def __str__(self):
        return repr(self.message)