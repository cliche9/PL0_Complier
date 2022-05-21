"""
PL0 编译器本体
"""

import os, sys
from symtable import SymbolTable
from exception import LexerError, SyntaxError
from py_backup.lexer import lexer

if __name__ == "__main__":
    lexer = lexer()

    # 输出重定向
    dir_path = 'PL0_code2022'
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
            print(f"LexicalError: {e.message}")
        except SyntaxError as e:
            print(f"SyntaxError: {e.message}")
        finally:
            # 还原标准输出
            sys.out = oldstdout
            out.close()
