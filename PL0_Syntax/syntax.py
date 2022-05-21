import sys, os
sys.path.append("..");
from common.exception import LexerError, SyntaxError
from PL0_Lexer.lexer import lexer

class syntax(object):
    def __init__(self) -> None:
        pass

if __name__ == "__main__":
    # 初始化PL0词法分析器
    lexer = lexer()
    # 初始化PL0语法分析器
    syntax = syntax();
    # 输出重定向
    dir_path = '../PL0_code2022'
    for file in os.listdir(os.path.join(dir_path, 'input')):
        infile = os.path.join(dir_path, 'input', file)
        outfile = os.path.join(dir_path, 'test_out', file.split('.')[0] + '.out')
        oldstdout = sys.stdout
        out = open(outfile, 'w')
        sys.stdout = out

        try:
            with open(infile) as f:
                while True:
                    c = f.read(1)
                    if not c:
                        break
                    lexer.deal_with(c)
                lexer.clean_up()
        except LexerError as e:
            print(f"LexerError: {e.message}")
        finally:
            # 还原标准输出
            sys.out = oldstdout
            out.close()