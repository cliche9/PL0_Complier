# 山东大学编译原理实验 2022 春季学期
## 实验1：PL/0词法分析器
> 把**关键字、算符、界符**称为语言固有的单词；
>
> **标识符、常量**称为用户自定义的单词。
>
> 为此设置两个全程量：NAME，SYM 。
>
> SYM：存放每个单词的类别。
>
> NAME：存放单词值。

### 实验任务

1. 滤掉单词间的空格。
2. **识别关键字**，用查关键字表的方法识别。当单词是关键字时，将对应的类别放在SYM中。如IF的类别为IFSYM，THEN的类别为THENSYM。
3. **识别标识符**，标识符的类别为IDENT，IDENT放在SYM中，标识符本身的值放在NAME中。
4. 拼数，将数的类别NUMBER放在SYM中，数本身的值放在NAME中。
5. **拼由两个字符组成的运算符**，如：>=、<=等等，识别后将类别存放在SYM中。
6. 打印源程序，边读入字符边打印。

**注意：由于一个单词是由一个或多个字符组成的，所以需实现一个读字符过程。**

### 实验步骤

1. 构建NAME - SYM映射表：存储到`symbol.h`中，用于快速将读取的单词转化为对应的符号标识，以及对应的文本表示形式

  ![image-20220610172125165](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610172125165.png)![image-20220610172159207](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610172159207.png)![image-20220610172218974](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610172218974.png)

2. 构建符号数据结构存储读取符号

  ![image-20220610200519714](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610200519714.png)

3. 逐个读入字符，采用**超前搜索方式**，根据读到的下一个字符进行相应处理；

  * 读到"\n"和空格直接跳过；

  * 读到数字：

    持续读入数字，直到读到其他类型字符时，保存当前数字；
    
  * 读到字母：

    持续读入数字或字母，直到读到其他字符时，保存当前读取的标识符；
    
  * 读到运算符或界符：**运算符长度限定为1或2**

    验证是否为":="，">="之类的运算符，是的话读入下个字符然后保存，不是的话直接保存当前符号，通过str2tag获取其类型；

### 实验结果

PL0_code0.in对应的词法分析输出如下：

```python
(const, SYM_CONST)
(a, SYM_IDENT)
(=, SYM_EQL)
(10, SYM_NUMBER)
(;, SYM_SEMICOLON)
(var, SYM_VAR)
(d, SYM_IDENT)
(,, SYM_COMMA)
(e, SYM_IDENT)
(,, SYM_COMMA)
(f, SYM_IDENT)
(;, SYM_SEMICOLON)
(procedure, SYM_PROC)
(p, SYM_IDENT)
(;, SYM_SEMICOLON)
(var, SYM_VAR)
(g, SYM_IDENT)
(;, SYM_SEMICOLON)
...
```

## 实验2：PL/0语义分析和中间代码生成

> 词法分析器会向语法分析器提供词语流。你需要以合适的方式对词语流进行分析，进行语法，语义分析即中间代码的生成。输出：四元式

### 实验任务

1. 说明语句的处理：对每个过程（包括主程序，可以看成是一个主过程）的说明对象造名字表和四元式；
   * 所造的表放在全程量一维数组TABLE中，数组表项格式为`[NAME, KIND, LEVEL, VALUE]`；
   * 所生成的四元式放在全程量QUADS中，四元式格式为`(op, arg1, arg2, result)`；
2. 执行语句的处理：对语句逐句分析，语法正确则生成目标四元式，表示语句的执行过程；

### 实验步骤

1. 构建说明语句类型映射：

   ![image-20220610200647139](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610200647139.png)

2. 构建标识符数据结构用于存储解析的说明语句

   ![image-20220610200819879](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610200819879.png)

   **其中红色框存储目标代码（实验3）情况下的指令地址，蓝色框存储四元式情况下四元式的地址；**

3. 从**词法分析器**读取符号，解析符号，执行对应的语句处理函数

   * 符号读取辅助函数：

     ![image-20220610201041647](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610201041647.png)

   * 语句处理函数：

     ![image-20220610201102218](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610201102218.png)

     ==具体各类语句的处理逻辑在各个函数中定义==

   整体处理流程如下：

   ![image-20220610202735296](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610202735296.png)

   对于`expr()`的细分如下：

   ![image-20220610203127236](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610203127236.png)

   对于`cond()`的戏份如下：

   ![image-20220610203418484](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610203418484.png)

4. 在说明语句`declares()`中生成标识符表；

   标识符生成函数`enter()`如下

   ![image-20220610203656231](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610203656231.png)

   标识符相关结构和函数如下

   ![image-20220610210753547](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610210753547.png)

5. 在说明语句`declares()`和执行语句`statements()`中生成四元式结构；

   四元式生成函数`generate`如下

   ![image-20220610203735716](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610203735716.png)

   四元式相关结构和函数如下

   ![image-20220610210726882](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610210726882.png)

> **特别注意：需要对符号表、四元式表地址进行回填**
>
> * block()：回填过程起始/结束地址
>
> ![image-20220610211202487](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610211202487.png)
>
> * condition()：回填跳转指令的目标地址
>
>   ![image-20220610211406479](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610211406479.png)
>
> * whiledo()：回填while指令的结束/语句开始地址
>
>   ![image-20220610211617256](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610211617256.png)

### 实验结果

* PL0_code0.in对应的语法分析得到的标识符表如下：

  ```python
  # 对于CONSTANT, 只有NAME, KIND, VAL字段有效
  TX0 ->
  NAME: a         KIND: CONSTANT  VAL: 10        LEVEL: -1        ADR: -1        
  # 对于VAR, 只有NAME, KIND, LEVEL, ADR有效
  NAME: d         KIND: VARIABLE  VAL: 0         LEVEL: 0         ADR: 3         
  NAME: e         KIND: VARIABLE  VAL: 0         LEVEL: 0         ADR: 4         
  NAME: f         KIND: VARIABLE  VAL: 0         LEVEL: 0         ADR: 5         
  # 对于PROC, 只有NAME, KIND, LEVEL, ADR有效
  NAME: p         KIND: PROCEDURE VAL: -1        LEVEL: 0         ADR: 1         
  TX1 ->
  NAME: g         KIND: VARIABLE  VAL: 0         LEVEL: 1         ADR: 3         
  ```

* PL0_code0.in对应的语法分析得到的四元式表如下：

  ```python
  (j, -, -, 17)									# 无条件跳转到17
  (const, 10, -, a)							# const a = 10
  (var, -, -, d)								# var d
  (var, -, -, e)
  (var, -, -, f)
  (proc, -, -, p)								# procedure p
  (var, -, -, g)
  (init, -, -, 4)								# 初始化过程栈区, 大小为4
  (*, a, 2, $T0)								# T0 = a * 2
  (:=, $T0, -, d)								# d := T0
  (/, a, 3, $T1)
  (:=, $T1, -, e)
  (<=, d, e, $T2)
  (jz, $T2, -, 16)
  (+, d, e, $T3)
  (:=, $T3, -, f)
  (j, -, -, 0)
  (init, -, -, 6)
  (read, -, -, e)								# e = read()
  (read, -, -, f)
  (write, -, -, e)							# write(e)
  (write, -, -, f)
  (write, -, -, d)
  (call, -, -, 7)								# call, 无条件跳转到7
  (odd, d, -, $T4)							# T4 = odd d
  (jz, $T4, -, 30)							# T4 = False时跳转到30
  (uminus, e, -, $T5)						# T5 = -e
  (+, $T5, 1, $T6)
  (:=, $T6, -, e)
  (j, -, -, 24)
  (j, -, -, 0)
  ```

## 实验3：实现解释执行目标程序

> 对语句逐句分析，生成目标代码，解释执行目标代码得到运行结果

### 实验任务

1. 逐句分析语句，生成目标代码，目标代码格式如下

   ![image-20220610205509089](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610205509089.png)

   其中f代表功能码，l代表层次差，a代表位移量；

2. 利用目标代码和数据栈执行目标代码，得到运行结果

### 实验步骤

#### 目标代码生成

1. 构建目标代码类型映射

   ![image-20220610210355255](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610210355255.png)

   ![image-20220610210429719](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610210429719.png)

   构建运算类型映射

   ![image-20220610210457005](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610210457005.png)![image-20220610210506331](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610210506331.png)

2. 构建目标代码数据结构

   ![image-20220610210548590](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610210548590.png)

3. 通过语法分析器生成目标代码

   目标代码相关结构和函数如下：

   ![image-20220610210908539](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610210908539.png)

   ![image-20220610210937781](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610210937781.png)

   **==目标代码生成的基本流程与四元式基本相同，根据目标指令在处理语句中生成合适的指令即可==**

   > 目标指令有8条：
   >
   > ① LIT：将常数a放到栈顶。
   >
   > ② LOD：将变量放到栈顶。a域为变量在所说明层中的相对位置，l为调用层与说明层的层差值。
   >
   > ③ STO：将栈顶的内容送到某变量单元中。a，l域的含义与LOD的相同。
   >
   > ④ CAL：调用过程的指令。a为被调用过程的目标程序的入中地址，l为层差。
   >
   > ⑤ INT：为被调用的过程（或主程序）在运行栈中开辟数据区。a域为开辟的个数。
   >
   > ⑥ JMP：无条件转移指令，a为转向地址。
   >
   > ⑦ JPC：条件转移指令，当栈顶的布尔值为非真时，转向a域的地址，否则顺序执行。
   >
   > ⑧ OPR：关系和算术运算。具体操作由a域给出。运算对象为栈顶和次顶的内容进行运算，结果存放在次顶。a域为0时是退出数据区。

#### 执行目标程序

1. 建立虚拟机的寄存器和栈区

   > 虚拟机有4个寄存器
   >
   > ① I：指令寄存器，存放当前正在解释的一条目标指令；
   >
   > ② PC寄存器：指向下一条要执行的目标指令（相当于CODE数组的下标）；
   >
   > ③ SP栈顶寄存器：指向虚拟栈的栈顶，程序中用`vector.back()`替代；
   >
   > ④ BP数据基址寄存器：存储过程栈数据区的起始地址；

   ![image-20220610211948953](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610211948953.png)

   > 虚拟机的栈区组成
   >
   > ![PL0栈区指针](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-PL0%E6%A0%88%E5%8C%BA%E6%8C%87%E9%92%88.svg)
   >
   > * RA存储当前过程的返回地址，即上一层过程的下一条指令的地址；
   >
   > * DL存储上一层过程的数据段的基地址BP；
   >
   > * SL存储定义当前过程的直接外过程运行时数据段的基地址BP；
   >
   >   **==因此我们递归查询上一层符号表是需要使用SL进行递归查询==**
   >
   > * 过程数据区存储该过程声明的变量；
   >
   > * 临时数据区存储该过程进出栈的临时变量；
   >
   > 对于栈区的操作
   >
   > * INT  0 a：a为局部量个数
   > * OPR 0 0：恢复上一层过程（或主程序）的数据段的基地址寄存器的值，恢复栈顶寄存器SP的值，并将返回地址送到PC寄存器中；
   > * CAL l a：a为被调用过程的目标程序的入口，送入PC寄存器中；CAL指令还完成填写静态链，动态链，返回地址，利用l递归查找被调用过程的基地址值，送入基址寄存器BP中；

2. 建立解释器数据结构

   ![image-20220610214842001](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610214842001.png)

3. 从目标代码寄存器读取指令，利用数据栈执行相应指令

   ![image-20220610213608290](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610213608290.png)

   PC持续自增取指，然后调用`oneInstruction()`执行指令；

   ![image-20220610213711566](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610213711566.png)

   `oneInstruction()`根据取得指令的不同执行不同的指令操作，关键操作位于`opr()`，其包含了诸多运算函数，详细逻辑如下

   ![image-20220610214913572](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610214913572.png)

   其中单目运算符处理函数：

   ![image-20220610214942573](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610214942573.png)

   双目运算符处理函数：

   ![image-20220610214957197](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610214957197.png)

4. 特别注意CAL指令，需要递归查找被调用过程的基地址

   具体查找函数如下

   ![image-20220610215246463](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610215246463.png)

### 实验结果

PL0_code0.in对应的运行过程PC、BP、指令、栈区的具体信息如下：

```python
PC: 0
BP: 0
Instruction: ( JMP, 0, 19 )
=== Stack ===
	0: 0
	1: 0
	2: 0

PC: 19
BP: 0
Instruction: ( INT, 0, 6 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 0
	4: 0
	5: 0

PC: 20
BP: 0
Instruction: ( OPR, 0, READ )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 0
	4: 0
	5: 0
	6: 1

PC: 21
BP: 0
Instruction: ( STO, 0, 4 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 0
	4: 1
	5: 0

PC: 22
BP: 0
Instruction: ( OPR, 0, READ )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 0
	4: 1
	5: 0
	6: 5

PC: 23
BP: 0
Instruction: ( STO, 0, 5 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 0
	4: 1
	5: 5

PC: 24
BP: 0
Instruction: ( LOD, 0, 4 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 0
	4: 1
	5: 5
	6: 1

PC: 25
BP: 0
Instruction: ( OPR, 0, WRITE )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 0
	4: 1
	5: 5

PC: 26
BP: 0
Instruction: ( LOD, 0, 5 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 0
	4: 1
	5: 5
	6: 5

PC: 27
BP: 0
Instruction: ( OPR, 0, WRITE )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 0
	4: 1
	5: 5

PC: 28
BP: 0
Instruction: ( LOD, 0, 3 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 0
	4: 1
	5: 5
	6: 0

PC: 29
BP: 0
Instruction: ( OPR, 0, WRITE )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 0
	4: 1
	5: 5

PC: 30
BP: 0
Instruction: ( CAL, 0, 1 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 0
	4: 1
	5: 5
	6: 31
	7: 0
	8: 0

PC: 1
BP: 6
Instruction: ( INT, 0, 4 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 0
	4: 1
	5: 5
	6: 31
	7: 0
	8: 0
	9: 0

PC: 2
BP: 6
Instruction: ( LIT, 0, 10 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 0
	4: 1
	5: 5
	6: 31
	7: 0
	8: 0
	9: 0
	10: 10

PC: 3
BP: 6
Instruction: ( LIT, 0, 2 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 0
	4: 1
	5: 5
	6: 31
	7: 0
	8: 0
	9: 0
	10: 10
	11: 2

PC: 4
BP: 6
Instruction: ( OPR, 0, MUL )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 0
	4: 1
	5: 5
	6: 31
	7: 0
	8: 0
	9: 0
	10: 20

PC: 5
BP: 6
Instruction: ( STO, 1, 3 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 20
	4: 1
	5: 5
	6: 31
	7: 0
	8: 0
	9: 0

PC: 6
BP: 6
Instruction: ( LIT, 0, 10 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 20
	4: 1
	5: 5
	6: 31
	7: 0
	8: 0
	9: 0
	10: 10

PC: 7
BP: 6
Instruction: ( LIT, 0, 3 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 20
	4: 1
	5: 5
	6: 31
	7: 0
	8: 0
	9: 0
	10: 10
	11: 3

PC: 8
BP: 6
Instruction: ( OPR, 0, DIV )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 20
	4: 1
	5: 5
	6: 31
	7: 0
	8: 0
	9: 0
	10: 3

PC: 9
BP: 6
Instruction: ( STO, 1, 4 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 20
	4: 3
	5: 5
	6: 31
	7: 0
	8: 0
	9: 0

PC: 10
BP: 6
Instruction: ( LOD, 1, 3 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 20
	4: 3
	5: 5
	6: 31
	7: 0
	8: 0
	9: 0
	10: 20

PC: 11
BP: 6
Instruction: ( LOD, 1, 4 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 20
	4: 3
	5: 5
	6: 31
	7: 0
	8: 0
	9: 0
	10: 20
	11: 3

PC: 12
BP: 6
Instruction: ( OPR, 0, LEQ )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 20
	4: 3
	5: 5
	6: 31
	7: 0
	8: 0
	9: 0
	10: 0

PC: 13
BP: 6
Instruction: ( JPC, 0, 18 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 20
	4: 3
	5: 5
	6: 31
	7: 0
	8: 0
	9: 0

PC: 18
BP: 6
Instruction: ( OPR, 0, END )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 20
	4: 3
	5: 5

PC: 31
BP: 0
Instruction: ( LOD, 0, 3 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 20
	4: 3
	5: 5
	6: 20

PC: 32
BP: 0
Instruction: ( OPR, 0, ODD )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 20
	4: 3
	5: 5
	6: 0

PC: 33
BP: 0
Instruction: ( JPC, 0, 40 )
=== Stack ===
	0: 0
	1: 0
	2: 0
	3: 20
	4: 3
	5: 5
```

