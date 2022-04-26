from enum import Enum

class chartype(Enum):
    NULL = 0
    DIGIT = 1,
    ALPHA = 2,
    OPERATOR = 3,
    BOUNDARY = 4

keywords = [
    "begin",
    "call",
    "do",
    "end",
    "if",
    "odd",
    "procedure",
    "read",
    "then",
    "var",
    "while",
    "write"
]

operatorsym = {
    "+": "plus",
    "-": "minus",
    "*": "times",
    "/": "over",
    "=": "eql",
    "<": "lss",
    "<=": "leq",
    ">": "gtr",
    ">=": "geq",
    "#": "neq",
    ":=": "assign"
}

boundarysym = {
    "(": "lparen",
    ")": "rparen",
    ";": "semicolon",
    ",": "comma",
    ".": "period"
}