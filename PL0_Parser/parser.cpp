#include "../common/exception.h"
#include "parser.h"

Parser::Parser(Lexer *lexer): lexer(lexer), symbol(NULL), level(0) {
    for (int i = 0; i < RECURSIVE_DEPTH; i++)
        addr[i] = 0;
}

void Parser::program() {
    block();
    getSymbol();
    if (symbol->getSymbolTag() != SYM_PERIOD)
        throw ParserException("Program: Expected PERIOD at End!");
    cout << "Parser Done!\n";
}

void Parser::getSymbol() {
    if (symbol) {
        delete symbol;
        symbol = NULL;
    }
    symbol = lexer->getSymbol();
}

void Parser::revoke() {
    lexer->prependSymbol(symbol);
    symbol = NULL;
}

Identifier *Parser::findIdentifier(string name) {
    for (int lev = level; lev >= 0; lev--)
        for (int i = 0; i < table[lev].size(); i++)
            if (table[lev][i].name == name)
                return &table[lev][i];

    return NULL;
}

void Parser::block() {
    if (level >= RECURSIVE_DEPTH)
        throw ParserException("Block: Too Many Recursions!");
    declares();
    statements();
}

void Parser::declares() {
    while (true) {
        // 读取一个符号, 读取后需将其放回
        // 该读取为试探性的, 读取的符号不一定为Declaration
        getSymbol();
        switch (symbol->getSymbolTag()) {
            case SYM_CONST:
                revoke();
                constDeclare();     // 常量声明
                break;
            case SYM_VAR:
                revoke();
                varDeclare();       // 变量声明
                break;
            case SYM_PROC:
                revoke();
                procDeclare();      // 过程声明
                break;
            default:
                revoke();
                return;
        }
    }
}

/* === 以下是真正的声明过程Declaration ===*/
/* === const a = 10, b = 5; ==== */
void Parser::constDeclare() {
    // 1. 读取 const 关键词
    getSymbol();
    if (symbol->getSymbolTag() != SYM_CONST)
        throw ParserException("Const: Declaration Error!");
    
    while (true) {
        // 2. 读取 const 名称
        getSymbol();
        if (symbol->getSymbolTag() != SYM_IDENT)
            throw ParserException("Const: Invalid Name!");
        if (nameSet.count(symbol->getValue()))
            throw ParserException("Const: Redeclaration!");
        string constName = symbol->getValue();
        // 3. 读取 "="
        getSymbol();
        if (symbol->getSymbolTag() != SYM_EQL)
            throw ParserException("Const: Assignment Error!");
        // 4. 读取 const 值
        getSymbol();
        if (symbol->getSymbolTag() != SYM_NUMBER)
            throw ParserException("Const: Value is not Number!");
        
        // 5. 读取完毕, 将读取的值放入Table
        table[level].emplace_back(constName, KIND::CONST, stoi(symbol->getValue()), -1, -1);
        // 6. 读取分界符
        getSymbol();
        switch (symbol->getSymbolTag()) {
            case SYM_COMMA:
                break;
            case SYM_SEMICOLON:
                return;
            default:
                throw ParserException("Const: Invalid Bound Symbol!");
        }
    }
}

/* === var a, b, c, d; ========= */
void Parser::varDeclare() {
    // 1. 读取 var 关键词
    getSymbol();
    if (symbol->getSymbolTag() != SYM_VAR) 
        throw ParserException("Var: Declaration Error!");
    
    while (true) {
        // 2. 读取 var 名称
        getSymbol();
        if (symbol->getSymbolTag() != SYM_IDENT)
            throw ParserException("Var: Invalid Name!");
        // 3. 将 var 加入Table, 初始值为0
        table[level].emplace_back(symbol->getValue(), KIND::VAR, 0, level, addr[level]++); 
        // 4. 读取分界符
        getSymbol();
        switch (symbol->getSymbolTag()) {
            case SYM_COMMA:
                break;
            case SYM_SEMICOLON:
                return;
            default:
                throw ParserException("Var: Invalid Bound Symbol!");
        }
    }
}

/* === procedure p; ============ */
void Parser::procDeclare() {
    while (true) {
        // 1. 读取 proc 关键词
        getSymbol();
        if (symbol->getSymbolTag() != SYM_PROC)
            throw ParserException("Proc: Declaration Error!");
        // 2. 读取 proc 名称
        getSymbol();
        if (symbol->getSymbolTag() != SYM_IDENT)
            throw ParserException("Proc: Invalid Name!");
        // 3. 将 proc 加入table
        table[level].emplace_back(symbol->getValue(), KIND::PROC, -1, level, addr[level]++);
        // 4. 读取分界符
        getSymbol();
        if (symbol->getSymbolTag() != SYM_SEMICOLON)
            throw ParserException("Proc: Invalid Bound Symbol!");
        // 5. 更新level和addr
        ++level;
        block();        // 进入子 proc
        --level;
        // 6. ";": 结束该 proc
        getSymbol();
        if(symbol->getSymbolTag() != SYM_SEMICOLON)
            throw ParserException("Proc: Expected Semicolon At End!");
        // 7. 预读取下一个符号, 看是否还有Proc
        getSymbol();
        if (symbol == NULL)
            // 代码读取完毕
            return;
        if (symbol->getSymbolTag() != SYM_PROC) {
            // 后续无连续 proc
            revoke();
            break;
        }
        // 预读取不管是否为Proc, 都需要将其放回lexer
        revoke();
    }
}

void Parser::statements() {
    getSymbol();
    switch (symbol->getSymbolTag()) {
        case SYM_IDENT:
            revoke();
            assign();               // 赋值语句
            break;
        case SYM_BEGIN:
            revoke();
            compound();             // begin-end型
            break;
        case SYM_IF:
            revoke();
            condition();            // 条件语句
            break;
        case SYM_CALL:
            revoke();
            call();                 // 调用语句
            break;
        case SYM_WHILE:
            revoke();
            whiledo();              // 循环语句
            break;
        case SYM_READ:
            revoke();
            read();                 // 读语句
            break;
        case SYM_WRITE:
            revoke();
            write();                // 写语句
            break;
        default:
            revoke();
            break;
    }
}

/* === 以下是真正的执行语句Statement ===*/
/* === a := x; ==== */
void Parser::assign() {
    // 1. 读取左边符号
    getSymbol();
    if (symbol->getSymbolTag() != SYM_IDENT)
        throw ParserException("Assign: Invalid Name!");
    // 2. 在Table表中查找对应符号的表项Identifier
    Identifier *identifier = findIdentifier(symbol->getValue());
    if (identifier == NULL || identifier->kind != VAR)
        throw ParserException("Assign: Invalid Identifier!");
    // 3. 读取赋值 ":=" 符号
    getSymbol();
    if (symbol->getSymbolTag() != SYM_ASSIGN)
        throw ParserException("Assign: Invalid Assign Symbol!");
    // 4. 调用expr()读取表达式作为右边值
    expr();
}

void Parser::compound() {
    // 1. 读取BEGIN
    getSymbol();
    if (symbol->getSymbolTag() != SYM_BEGIN)
        throw ParserException("COMPOUND: Expected BEGIN Here!");
    // 2. 循环执行语句
    while(true) {
        statements();
        // 3. 读取分界符
        getSymbol();
        switch (symbol->getSymbolTag()) {
            case SYM_SEMICOLON:     // ";": 继续执行
                break;
            case SYM_END:           // "END": 结束compound执行
                return;
            default:
                throw ParserException("COMPOUND: Invalid Bound Symbol!");
        }
    }
}

/* === if w <= r then; ==== */
void Parser::condition() {
    // 1. 读取IF
    getSymbol();
    if (symbol->getSymbolTag() != SYM_IF)
        throw ParserException("Condition: Expected IF Here!");
    // 2. 执行条件语句判断
    cond();
    // 3. 读取THEN
    getSymbol();
    if (symbol->getSymbolTag() != SYM_THEN)
        throw ParserException("Condition: Expected THEN Here!");
    // 4. 执行后续语句
    statements();
}

void Parser::call() {
    // 1. 读取CALL
    getSymbol();
    if (symbol->getSymbolTag() != SYM_CALL)
        throw ParserException("Call: Expected CALL Here!");
    // 2. 读取 Procedure 的 Identifier
    getSymbol();
    if (symbol->getSymbolTag() != SYM_IDENT)
        throw ParserException("Call: Expected Proc Identifier Here!");
    // 3. 在Table中寻找相应的 Identifier
    Identifier *identifier = findIdentifier(symbol->getValue());
    if (identifier == NULL || identifier->kind != PROC)
        throw ParserException("Call: Invalid Identifier!");
}

void Parser::whiledo() {
    // 1. 读取WHILE
    getSymbol();
    if (symbol->getSymbolTag() != SYM_WHILE)
        throw ParserException("WHILEDO: Expected WHILE Here!");
    // 2. 执行条件语句判断
    cond();
    // 3. 读取DO
    getSymbol();
    if (symbol->getSymbolTag() != SYM_DO)
        throw ParserException("WHILEDO: Expected DO Here!");
    // 4. 执行while循环内的语句
    statements();
}

void Parser::read() {
    // 1. 读取READ
    getSymbol();
    if (symbol->getSymbolTag() != SYM_READ)
        throw ParserException("READ: Expected READ Here!");
    // 2. read一定有括号, 读取左括号
    getSymbol();
    if (symbol->getSymbolTag() != SYM_LPAREN)
        throw ParserException("READ: Expected LPAREN Here!");
    // 3. 循环READ, read()支持多个参数, 以","分隔
    while (true) {
        // 处理当前read
        getSymbol();
        if (symbol->getSymbolTag() != SYM_IDENT)
            throw ParserException("READ: Expected Identifier Here!");
        Identifier *identifier = findIdentifier(symbol->getValue());
        if (identifier == NULL)
            throw ParserException("READ: Undefined Identifier!");
        if (identifier->kind != VAR && identifier->kind != CONST)
            throw ParserException("READ: Invalid Identifier!");
        // 读取分界符, 看是否继续循环
        getSymbol();
        switch (symbol->getSymbolTag()) {
            case SYM_COMMA:
                break;
            case SYM_RPAREN:
                return;
            default:
                throw ParserException("READ: Invalid Bound Symbol!");
        }
    }
}

void Parser::write() {
    // 1. 读取WRITE
    getSymbol();
    if (symbol->getSymbolTag() != SYM_WRITE)
        throw ParserException("WRITE: Expected WRITE Here!");
    // 2. write一定有括号, 读取左括号
    getSymbol();
    if (symbol->getSymbolTag() != SYM_LPAREN)
        throw ParserException("WRITE: Expected LPAREN Here!");
    // 3. 循环WRITE, write()支持多个参数, 以","分隔
    while (true) {
        // 处理当前write
        expr();
        /** write参数支持expr
        getSymbol();
        if (symbol->getSymbolTag() != SYM_IDENT)
            throw ParserException("WRITE: Expected Identifier Here!");
        int tokenIndex = findIdentifier(symbol->getValue());
        Identifier token = table[level][tokenIndex];
        if (tokenIndex == -1 || token.kind != VAR || token.kind != CONST)
            throw ParserException("WRITE: Invalid Identifier!");
        */
        // 读取分界符, 看是否继续循环
        getSymbol();
        switch (symbol->getSymbolTag()) {
            case SYM_COMMA:
                break;
            case SYM_RPAREN:
                return;
            default:
                throw ParserException("WRITE: Invalid Bound Symbol!");
        }
    }
}

/* ===  === */
void Parser::cond() {
    getSymbol();
    // odd指令, 判断是否为奇数, 只需读取一个expr即可
    if (symbol->getSymbolTag() == SYM_ODD) {
        expr();
        return;
    }
    // 其他指令
    // 格式: expr 比较运算符 expr
    revoke();
    expr();
    getSymbol();
    switch (symbol->getSymbolTag()) {
        case SYM_EQL:
        case SYM_NEQ:
        case SYM_LSS:
        case SYM_LEQ:
        case SYM_GTR:
        case SYM_GEQ:
            break;
        default:
            throw ParserException("Cond: Invalid Symbol Tag!");
    }
    expr();
}

/* === 读取一个expr, expr由多个term通过+/-运算组合而成, 如 a * b + c === */
void Parser::expr() {
    // 单独读取一次, 以处理+/-表示正负数
    getSymbol();
    if (symbol->getSymbolTag() != SYM_PLUS && symbol->getSymbolTag() != SYM_MINUS)
        revoke();
    while (true) {
        term();
        getSymbol();
        switch (symbol->getSymbolTag()) {
            // 处理正负号, +/-是expr的运算组成单元
            case SYM_PLUS:
            case SYM_MINUS:
                break;
            // 其他的符号交由term()处理
            default:
                revoke();
                return;
        }
    }
}

/* === 读取一个term, term由多个factor通过x/÷运算组成, 如 2 * x, w / 2 === */
void Parser::term() {
    // 用于处理首个标识符号
    factor();
    while (true) {
        getSymbol();
        switch (symbol->getSymbolTag()) {
            case SYM_MUL: 
            case SYM_DIV:                
                break;
            default:
                revoke();
                return;
        }
        factor();
    }
}

/* === 读取一个因子, 括号包裹的也算因子, 如a, (a * x + b) === */
void Parser::factor() {
    getSymbol();
    Identifier *identifier = NULL;
    switch (symbol->getSymbolTag()) {
        // 数字/标识符, 直接读取
        case SYM_IDENT:
            identifier = findIdentifier(symbol->getValue());
            if (identifier == NULL)
                throw ParserException("Factor: Undefined Identifier!");
            if (identifier->kind != VAR && identifier->kind != CONST)
                throw ParserException("Factor: Invalid Identifier!");
        case SYM_NUMBER:
            break;
        // 左括号
        case SYM_LPAREN:
            expr();         // 读取括号内语句
            getSymbol();    // 读取右括号
            if (symbol->getSymbolTag() != SYM_RPAREN)
                throw ParserException("Factor: Missing Right Bracket!");
            break;
        default:
            throw ParserException("Factor: Invalid Symbol!");
    }
}