# iris
一个使用 cpp 编写的简单脚本。

构建项目：

```shell
mkdir build

cd /build

cmake ..

make
```



```shell
\iris\build>.\main_cmake
Welcome to iris!

>>> int a = 10;
--- output ---
<- 10

>>> int b = a * 10 + (1 + 3) * (2);
--- output ---
<- 108

>>> a + b;
--- output ---
<- 118

>>> exit();
good bye!
```

使用 `-v` 可以查看当前脚本的 AST

```shell
\iris\build>.\main_cmake -v
verbose mode
Welcome to iris!

>>> int a = 10 + 20;
 pwc
         a
                 +
                         10
                         20
--- output ---
<- 30

>>> a;
 pwc
         a
--- output ---
<- 30
```
