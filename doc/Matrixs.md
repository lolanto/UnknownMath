# 关于矩阵及其与图形API的关系

---

## 行/列矩阵

此处讨论的行/列矩阵，默认为内存存储方式上的行/列矩阵。若某一矩阵其数学表达式为

```
ABCD
EFGH
IJKL
MNOP
```

则，行矩阵的内存结构为：ABCDEFGHIJKLMNOP，而列矩阵为：AEIMBFJNCGKODHLP

矩阵的存储方式不应该影响其数学运算逻辑

## 矩阵在DirectX中

DirectX的矩阵默认是以列矩阵的方式存储，在hlsl中使用mul函数进行矩阵乘法。当`mul(matrix, vector)`时，向量以列向量处理，当`mul(vector, matrix)`时，向量以行向量处理。[mul in hlsl](https://docs.microsoft.com/en-us/windows/desktop/direct3dhlsl/dx-graphics-hlsl-mul)

## 矩阵在OpenGL中