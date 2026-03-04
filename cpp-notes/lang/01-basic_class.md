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

## 七、参数传递：调用者与 reference

> 传输者无需知道接受者是以 reference 形式接受

- 调用者只负责“传入参数”
- 是否以 reference 接收，由**函数签名**（参数类型 / 返回类型）决定
- 调用者不需要关心接收方式，也无法从调用处看出来

---

## 八、操作符重载（成员函数形式）

- 定义在 **class 内**
- 属于成员函数，因此**有 this**
- 常见：`operator=`, `operator+=`, `operator[]`, `operator()`

### this（所有成员函数都有 this）
- `this` 是**指向当前对象的指针**
- 在成员函数中可用 `this->member` 访问成员

---

## 九、操作符重载（非成员函数形式）

- 定义在 **class 外**
- **没有 this**
- 常见：`operator+`, `operator<<`（通常更适合写成非成员）

- 返回值通常是 **临时对象**
  - `typename()` 表示构造一个临时对象（temporary object）

---

## 十、带指针成员的 class（拷贝语义）

当 class **包含指针成员**时：

- 需要进行**动态分配内存**
- 默认的拷贝行为可能导致**浅拷贝**

因此通常必须实现：
- 拷贝构造函数（copy ctor）
- 拷贝赋值运算符（copy assignment）
- （以及析构函数，用于释放资源）

目的：
- 防止浅拷贝导致多个对象共享同一块内存，引发重复释放/数据错误

---

## 十一、注意：默认参数不能重复赋值

- 默认参数（default argument）**只能在声明处给一次**
- 不能在声明和定义中重复写默认值（否则编译报错）

---