from enum import Enum

# 字符类型
class chartype(Enum):
    NULL = 0
    DIGIT = 1
    ALPHA = 2
    OPERATOR = 3
    BOUNDARY = 4

# 标识符类型
class SymbolKind(Enum):
    CONSTANT = 0
    VARIABLE = 1
    PROCEDURE = 2

# 关键词
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

# 运算符
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

# 界符
boundarysym = {
    "(": "lparen",
    ")": "rparen",
    ";": "semicolon",
    ",": "comma",
    ".": "period"
}