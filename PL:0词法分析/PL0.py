"""
需要进一步优化:
1. 冗余代码过多
2. 无法正确处理负号
3. 需要按照NDF来写
"""

# 关键词 word - sym 映射表
keywords = ["begin", "call", "do", "end", "if", "odd", "procedure", "read",  "then", "var", "while", "write"]
wordsym = { keyword: keyword + "sys" for keyword in keywords }
# 运算符
operatorsym = {
    # 运算符
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

# 用于保存识别内容
NAME = []
SYM = []

# 识别关键词/标识符 --- 字符
def identifyWord(word):
    if (len(word) == 0):
        return
    if word in keywords:
        # 关键字
        print(f"({word}, {wordsym[word]})")
        NAME.append(word)
        SYM.append(wordsym[word])
    else:
        # 标识符
        print(f"(ident, {word})")
        NAME.append(word)
        SYM.append("ident")
# 识别数字
def identifyNumber(number):
    if (len(number) == 0):
        return
    print(f"(number, {number})")
    NAME.append(number)
    SYM.append("number")
# 识别运算符
def identifyOperator(operator):
    if (len(operator) == 0):
        return
    print(f"({operator}, {operatorsym[operator]})")
    NAME.append(operator)
    SYM.append(operatorsym[operator])
# 识别界符
def identifyBoundary(boundary):
    if (len(boundary) == 0):
        return
    print(f"({boundary}, {boundarysym[boundary]})")
    NAME.append(boundary)
    SYM.append(boundarysym[boundary])

from enum import Enum
import sys

class chartype(Enum):
    NULL = 0
    DIGIT = 1,
    ALPHA = 2,
    OPERATOR = 3,
    BOUNDARY = 4

def redirect(outfile):
    with open(outfile, 'w') as f:
        oldstdout = sys.stdout
        sys.stdout = f
        try:
            help(__import__)
        finally:
            sys.stdout = oldstdout

if __name__ == "__main__":
    infile = "PL:0词法分析/PL0_code2022/PL0_code3.in"
    outfile = "PL:0词法分析/PL0_code2022/PL0_code3.out"
    # 当前读取字符类型
    # 0: digit, 1: alpha
    current_char_type = chartype.NULL
    number = ''
    word = ''
    operator = ''
    boundary = ''
    
    # 输出重定向
    oldstdout = sys.stdout
    out = open(outfile, 'w')
    sys.stdout = out
    # 读取文件输入
    with open(infile) as f:
        while True:
            c = f.read(1)
            if not c:
                break
            # 读取到空格和换行符
            if c in ['\n', ' ', '\t']:
                # 将number/word/operator的内容保存并打印出来(若存在内容)
                identifyNumber(number)
                number = ''
                identifyWord(word)
                word = ''
                identifyOperator(operator)
                operator = ''
                identifyBoundary(boundary)
                boundary = ''
                current_char_type = chartype.NULL
                continue
            
            if c.isdigit():
                # ======== 识别到数字 ========
                if current_char_type == chartype.DIGIT:
                    # 上一个字符为数字, 当前继续读入数字
                    number += c
                elif current_char_type == chartype.ALPHA:
                    # 上一个字符为字母, 当前仍然识别字符串, 继续读入
                    word += c
                elif current_char_type == chartype.OPERATOR:
                    # 上一个字符为运算符, 保存运算符, 读入当前数字
                    identifyOperator(operator)
                    operator = ''
                    current_char_type = chartype.DIGIT
                    number = c
                elif current_char_type == chartype.BOUNDARY:
                    identifyBoundary(boundary)
                    boundary = ''
                    current_char_type = chartype.DIGIT
                    number = c
                else:
                    # 上一个字符为空, 读入数字首位
                    current_char_type = chartype.DIGIT
                    number = c

            elif c.isalpha():
                # ======== 识别到字母 ========
                if current_char_type == chartype.DIGIT:
                    # 上一个为数字, 当前读入字母, 说明数字读取结束
                    # 保存读取的数字
                    identifyNumber(number)
                    number = ''
                    # 读入当前字母
                    current_char_type = chartype.ALPHA
                    word = c
                elif current_char_type == chartype.ALPHA:
                    word += c
                elif current_char_type == chartype.OPERATOR:
                    identifyOperator(operator)
                    operator = ''
                    current_char_type = chartype.ALPHA
                    word = c
                elif current_char_type == chartype.BOUNDARY:
                    identifyBoundary(boundary)
                    boundary = ''
                    current_char_type = chartype.ALPHA
                    word = c
                else:
                    current_char_type = chartype.ALPHA
                    word = c

            elif c not in boundarysym.keys():
                # ======== 识别到运算符 ========
                if current_char_type == chartype.ALPHA:
                    identifyWord(word)
                    word = ''
                    current_char_type = chartype.OPERATOR
                    operator = c
                elif current_char_type == chartype.DIGIT:
                    identifyNumber(number)
                    number = ''
                    current_char_type = chartype.OPERATOR
                    operator = c
                elif current_char_type == chartype.OPERATOR:
                    operator += c
                elif current_char_type == chartype.BOUNDARY:
                    identifyBoundary(boundary)
                    boundary = ''
                    current_char_type = chartype.OPERATOR
                    operator = c
                else:
                    current_char_type = chartype.OPERATOR
                    operator = c
            
            else:
                # ======== 识别到界符 ========
                if current_char_type == chartype.ALPHA:
                    identifyWord(word)
                    word = ''
                    current_char_type = chartype.BOUNDARY
                    boundary = c
                elif current_char_type == chartype.DIGIT:
                    identifyNumber(number)
                    number = ''
                    current_char_type = chartype.BOUNDARY
                    boundary = c
                elif current_char_type == chartype.OPERATOR:
                    identifyOperator(operator)
                    operator = ''
                    current_char_type = chartype.BOUNDARY
                    boundary = c
                elif current_char_type == chartype.BOUNDARY:
                    identifyBoundary(boundary)
                    boundary = ''
                    current_char_type = chartype.BOUNDARY
                    boundary = c
                else:
                    current_char_type = chartype.BOUNDARY
                    boundary = c
            
        # 将最后的number/word/operator的内容保存并打印出来(若存在内容)
        identifyNumber(number)
        number = ''
        identifyWord(word)
        word = ''
        identifyOperator(operator)
        operator = ''
        identifyBoundary(boundary)
        boundary = ''
        current_char_type = chartype.NULL

    # 还原标准输出
    sys.out = oldstdout
    out.close()