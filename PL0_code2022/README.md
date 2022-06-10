## Input

* PL0_code.in：

  1. 乘法 $x \times y$ 得积
  2. 除法 $x \div y$ 得商和余数
  3. 最大公约数 $gcd(x, y)$
  4. 阶乘 $!x$

* PL0_code0.in：

  没什么逻辑，在$a = 10$的情况下，输入$x, y$，输出$x, y, 0$

* PL0_code1.in：

  对于非零数$b$，输出$(b + 10) \times 2$

  ![image-20220604220117499](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-04-image-20220604220117499.png)

* PL0_code2.in：

  存在语法错误，行14缺少乘法符号

  ![image-20220610171834072](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610171834072.png)

* PL0_code3.in：

  存在语法错误，行18缺少乘法符号

  ![image-20220610171933728](https://fastly.jsdelivr.net/gh/cliche9/PicBeds/images/2022-06-10-image-20220610171933728.png)

## Output

* lever_output：记录词法分析的输出，输出格式为（标识符，类型）
* parser_output：记录语法分析的输出
  * 符号表_symbol：格式为[NAME, KIND, LEVEL, VALUE]
  * 四元式_quad：格式为（op，arg1，arg2，result）
  * 目标代码_code：格式为（f，l，a），f为功能码，l为层次差，a为位移量
* interpreter_output：记录程序执行的日志