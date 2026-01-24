# 基于对象（Object-Based）—— class

面向对象（继承、多态等）在此之前，先掌握 **class / object 的基础机制**。

---

## 一、class / struct 基本概念
- class / struct = **数据成员（data members）+ 成员函数（member functions）**
- class 的实例称为 **object**

---

## 二、示例：不含指针成员的 complex 类
> 本例中的 complex **不包含指针成员**（class 本身完全可以有指针）

### 1. 模板类（class template）
```cpp
template<typename T>
class complex {
private:
    T re, im;

public:
    complex(T r = 0, T i = 0) : re(r), im(i) {}
};
```

使用示例：
```cpp
complex<double> c1(2.5, 1.5);
complex<int>    c2(1, 2);
```

---

### 2. inline 成员函数
- **在 class body 内定义完成的成员函数**
- 会自动成为 **inline 候选函数**
- 是否真正 inline 由编译器决定

---

### 3. 访问级别（access level）
- public：对外接口
- private：内部实现细节（默认）

---

## 三、构造函数（Constructor）

### 1. 初始化列表（Initialization List）
```cpp
complex(double r = 0, double i = 0)
    : re(r), im(i) {}
```
- **只有构造函数**可以使用初始化列表
- 推荐用初始化列表而不是在函数体内赋值

---

### 2. 构造函数重载与二义性
```cpp
complex(double r = 0, double i = 0);
complex();
```
❌ 以上两者 **不能同时存在**

原因：
- 调用 `complex()` 时会产生 **二义性（ambiguous）**
- 编译器无法判断该调用哪个构造函数

---

### 3. 私有构造函数
- 将构造函数设为 private
- 外界无法随意创建对象
- 常用于 **Singleton（单例）设计模式**

---

## 四、const 成员函数（const member function）
```cpp
double real() const { return re; }
```
- const 成员函数承诺 **不修改成员数据**
- **const 对象只能调用 const 成员函数**
- 若遗漏 const，const 对象调用时会编译报错

---

## 五、参数传递（Parameter Passing）

### 1. 值传递 vs 引用传递
- pass by value：会产生拷贝，成本较高
- pass by reference：不拷贝，更高效

**经验法则：**
> 能用 `const T&`，就不用 `T`

---

### 2. 返回值传递
- 可以返回值（value）
- 可以返回引用（reference）

⚠️ 注意：
> **不能返回局部对象的引用**  
> 函数结束后局部对象已被销毁

---

## 六、friend（友元）

### 1. 友元函数
```cpp
class complex {
    friend complex& _doapl(complex*, const complex& r);
};
```
- friend 可以访问 private 成员
- 破坏封装，但在必要时很有用

---

### 2. 同类对象互为友元
- 同一个 class 的不同 objects
- 可以互相访问彼此的 private 成员

```cpp
class A {
private:
    int x;

public:
    int func(const A& a) {
        return a.x;
    }
};
```

---

传输者无需知道接受者是以reference形式接受
## 七、操作符重载，成员函数 -> class内函数
### this（所有成员函数都有this）

## 八、操作符重载，非成员函数 -> 没有this
typename()->临时对象

带指针的class
->含有拷贝构造->类含有指针时候
->记得做动态分配内存
->必须要有拷贝构造和拷贝负值->防止浅拷贝