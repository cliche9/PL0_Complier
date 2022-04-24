"""
需要进一步优化:
1. 冗余代码过多 √
2. 无法正确处理负号 √
3. 需要按照NDF来写 ?
"""
from enum import Enum
import sys
import os
import json

class chartype(Enum):
    NULL = 0
    DIGIT = 1,
    ALPHA = 2,
    OPERATOR = 3,
    BOUNDARY = 4

class PL0_analyser(object):
    def __init__(self, keywords, operatorsym, boundarysym) -> None:
        self.keywords = keywords
        self.wordsym = { keyword: keyword + "sys" for keyword in keywords }
        self.operatorsym = operatorsym
        self.boundarysym = boundarysym
        # 用于保存识别内容
        self.NAME = []
        self.SYM = []
        # 临时保存变量内容
        self.current_words = ''
        # 当前读取字符类型
        self.current_chartype = chartype.NULL

    def identifyWord(self, word):
        # 识别关键词/标识符 --- 单词字符
        if (len(word) == 0):
            return
        if word in self.keywords:
            # 关键字
            print(f"({word}, {self.wordsym[word]})")
            self.NAME.append(word)
            self.SYM.append(self.wordsym[word])
        else:
            # 标识符
            print(f"({word}, ident)")
            self.NAME.append(word)
            self.SYM.append("ident")
    
    def identifyNumber(self, number):
        # 识别数字
        if (len(number) == 0):
            return
        print(f"(number, {number})")
        self.NAME.append(number)
        self.SYM.append("number")

        
    def identifyOperator(self, operator):
        # 识别运算符
        if (len(operator) == 0):
            return
        print(f"({operator}, {self.operatorsym[operator]})")
        self.NAME.append(operator)
        self.SYM.append(self.operatorsym[operator])

    
    def identifyBoundary(self, boundary):
        # 识别界符
        if (len(boundary) == 0):
            return
        print(f"({boundary}, {self.boundarysym[boundary]})")
        self.NAME.append(boundary)
        self.SYM.append(self.boundarysym[boundary])

    def deal_with(self, char):
        # 读取到空格和换行符
        if char in ['\n', ' ', '\t']:
            # 将number/word/operator/boundary的内容保存并打印出来(若存在内容)
            if self.current_chartype == chartype.DIGIT:
                self.identifyNumber(self.current_words)
            elif self.current_chartype == chartype.ALPHA:
                self.identifyWord(self.current_words)
            elif self.current_chartype == chartype.OPERATOR:
                self.identifyOperator(self.current_words)
            elif self.current_chartype == chartype.BOUNDARY:
                self.identifyBoundary(self.current_words)
            # 设置chartype
            self.current_words = ''
            self.current_chartype = chartype.NULL
            return
        # ======== 识别到数字 ========
        if char.isdigit():
            if self.current_chartype == chartype.DIGIT or self.current_chartype == chartype.ALPHA:
                # 上一个字符为数字/字母, 当前继续读入
                self.current_words += char
                return
            elif self.current_chartype == chartype.OPERATOR:
                # 上一个字符为运算符, 保存运算符
                self.identifyOperator(self.current_words)
            elif self.current_chartype == chartype.BOUNDARY:
                # 上一个字符为界符, 保存界符
                self.identifyBoundary(self.current_words)
            # 读入当前数字, 设置chartype
            self.current_chartype = chartype.DIGIT
            self.current_words = char
        # ======== 识别到字母 ========
        elif char.isalpha():
            if self.current_chartype == chartype.ALPHA:
                # 上一个字符为字母, 继续读入
                self.current_words += char
                return
            elif self.current_chartype == chartype.DIGIT:
                # 上一个字符为数字, 保存数字
                self.identifyNumber(self.current_words)
            elif self.current_chartype == chartype.OPERATOR:
                # 上一个字符为运算符, 保存运算符
                self.identifyOperator(self.current_words)
            elif self.current_chartype == chartype.BOUNDARY:
                # 上一个字符为界符, 保存界符
                self.identifyBoundary(self.current_words)
            # 读入当前字母, 设置chartype
            self.current_chartype = chartype.ALPHA
            self.current_words = char
        # ======== 识别到运算符 ========
        elif char not in self.boundarysym.keys():
            # 运算符长度限定为1/2
            if self.current_chartype == chartype.OPERATOR:
                if len(self.current_words) < 2:
                    self.current_words += char
                    return
                else:
                    self.identifyOperator(self.current_words)
            elif self.current_chartype == chartype.DIGIT:
                self.identifyNumber(self.current_words)
            elif self.current_chartype == chartype.ALPHA:
                self.identifyWord(self.current_words)
            elif self.current_chartype == chartype.BOUNDARY:
                self.identifyBoundary(self.current_words)
            # 读入当前运算符, 设置chartype
            self.current_chartype = chartype.OPERATOR
            self.current_words = char
        # ======== 识别到界符 ========
        else:
            # 界符长度限定为1
            if self.current_chartype == chartype.BOUNDARY:
                self.identifyBoundary(self.current_words)
            elif self.current_chartype == chartype.DIGIT:
                self.identifyNumber(self.current_words)
            elif self.current_chartype == chartype.ALPHA:
                self.identifyWord(self.current_words)
            elif self.current_chartype == chartype.OPERATOR:
                self.identifyOperator(self.current_words)
            # 读入当前界符, 设置chartype
            self.current_chartype = chartype.BOUNDARY
            self.current_words = char

    def clean_up(self):
        # 将最后self.current_words的内容保存并打印出来(若存在内容)
        if len(self.current_words) == 0:
            return
        if self.current_chartype == chartype.DIGIT:
            self.identifyNumber(self.current_words)
        elif self.current_chartype == chartype.ALPHA:
            self.identifyWord(self.current_words)
        elif self.current_chartype == chartype.OPERATOR:
            self.identifyOperator(self.current_words)
        elif self.current_chartype == chartype.BOUNDARY:
            self.identifyBoundary(self.current_words)
        self.current_words = ''
        self.current_chartype = chartype.NULL

if __name__ == "__main__":
    with open("PL:0词法分析/symbols.json", "r") as f:
        symbols = json.load(f)
    # 初始化PL0词法分析器
    analyser = PL0_analyser(symbols['keywords'], symbols['operator'], symbols['boundary'])
    # 输出重定向
    dir_path = 'PL:0词法分析/PL0_code2022'
    for file in os.listdir(os.path.join(dir_path, 'input')):
        infile = os.path.join(dir_path, 'input', file)
        outfile = os.path.join(dir_path, 'output', file.split('.')[0] + '.out')
        oldstdout = sys.stdout
        out = open(outfile, 'w')
        sys.stdout = out

        with open(infile) as f:
            while True:
                c = f.read(1)
                if not c:
                    break
                analyser.deal_with(c)
            analyser.clean_up()

        # 还原标准输出
        sys.out = oldstdout
        out.close()