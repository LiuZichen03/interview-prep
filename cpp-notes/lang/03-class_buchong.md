# 03 - class 补充笔记

## 1) static（静态成员）

- **static 成员函数没有 `this` 指针**（因为它不属于某个对象，而属于类本身）。
- static 成员变量 / 成员函数的调用方式：
  - `对象.静态成员()`（不推荐，容易误导）
  - `类名::静态成员()`（推荐）

示例：
```cpp
class Account {
public:
    static double m_rate; // 声明
};

// 定义（通常放在 .cpp）
double Account::m_rate = 0.0;
```

---

## 2) 构造函数放在 private：Singleton（单例）

- 构造函数设为 `private`：外部不能 `A a;` 或 `new A`。
- 通过 `getInstance()` 返回唯一对象的引用。
- 禁止拷贝与拷贝赋值，避免产生第二份对象。

```cpp
class A {
public:
    static A& getInstance() {
        static A a; // 只构造一次
        return a;
    }

    void setup();

private:
    A() = default;
    A(const A&) = delete;
    A& operator=(const A&) = delete;
};
```

---

## 3) namespace / using

- `using namespace std;`：**using directive**（把整个命名空间引入当前作用域，容易污染命名）
- `using std::cout;`：**using declaration**（只引入一个名字，更推荐）

---

## 4) 面向对象编程的三种关系：复合 / 继承 / 委托

### 4.1 复合（Composition：has-a）
- 一个类 **包含** 另一个类（成员对象）。
- 构造/析构顺序：
  - **构造：由内而外**（先成员对象，后外层对象）
  - **析构：由外而内**（先外层对象，后成员对象）

> 成员对象的生命周期与外层对象绑定（“生死一起”）。

### 4.2 委托（Delegation / Composition by reference）
- 外层对象不直接包含成员对象，而是通过 **指针/引用** 指向实现体。
- 常用于：共享实现、隐藏细节、可替换实现等。

示例（String 指向 StringRep）：
```cpp
class StringRep {
    // ...
};

class String {
public:
    // ...

private:
    StringRep* rep; // 指向实现体
};
```

> 你这里提到的 “共享 / copy-on-write” 属于一种实现策略：多个对象共享同一份数据，写入时再复制。

### 4.3 继承（Inheritance：is-a）
- 子类继承父类接口与实现（`public` 继承）。
- 构造/析构顺序：
  - **构造：由内而外**（先父类，再子类）
  - **析构：由外而内**（先子类，再父类）

```cpp
class A {
    // ...
};

class B : public A {
    // ...
};
```

### 4.4 虚函数（virtual）与多态（polymorphism）
- 在基类中把函数声明为 `virtual`，并在派生类中 **override**（重写），可以通过 **基类指针/引用** 调用到派生类实现。
- 纯虚函数 `= 0` 表示抽象接口：该类通常不能被实例化。

```cpp
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;                 // pure virtual
    virtual void error(const char* msg) { /*...*/ } // virtual
};

class Circle : public Shape {
public:
    void draw() const override { /*...*/ }
};
```

> 记法：基类提供“接口/默认行为”，子类用 `override` 给出具体实现。

---

### 4.5 Template Method（模板方法）模式（理解即可）
- 基类定义一个**固定流程**（骨架），流程中调用若干 `virtual` 钩子（hook）。
- 子类只需要重写这些钩子，就能改变流程中的某些步骤。

伪代码：
```cpp
class Document {
public:
    void onFileOpen() {
        // ... 固定流程
        serialize();
        // ... 固定流程
    }

protected:
    virtual void serialize() { /* default */ }
};

class MyDoc : public Document {
protected:
    void serialize() override { /* custom */ }
};
```

---

### 4.6 Inheritance + Composition（继承 + 复合）下的构造/析构顺序
- **构造（ctor）顺序**：先父类（base）→ 再成员对象（members，按声明顺序）→ 最后子类本体。
- **析构（dtor）顺序**：反过来：先子类本体 → 再成员对象（声明顺序逆序）→ 最后父类。

---

### 4.7 Delegation + Inheritance（委托 + 继承）
- **Inheritance（继承）解决“对外接口统一”**：对外暴露同一套基类接口，调用端用 `Base* / Base&` 形成多态。
- **Delegation（委托）解决“对内实现复用/可替换”**：对象内部把具体工作交给另一个对象（实现体）。
- 组合使用时的直觉：
  - **对外看：同一类对象**（同接口、可替换）
  - **对内看：可换引擎**（换实现体就换行为）

一句话：**继承管接口，多态；委托管实现，可替换。**
---
delegation inheritance
## 5) template（模板）与容器适配

示例：queue 使用底层容器 `deque<T>` 来完成全部操作。

```cpp
template <class T>
class queue {
protected:
    std::deque<T> c; // 底层容器

public:
    // 下面的接口通常完全复用 c 的操作来实现
};
```

---

---

## 6) vptr / vtbl + 向上转型（upcasting）

### 6.1 vptr / vtbl 是什么
- **vtbl（virtual table）**：虚函数表，本质是一组“虚函数入口”的函数指针（按槽位 n 排列）。
- **vptr（virtual pointer）**：虚表指针，通常藏在**对象内部**，指向该对象“动态类型”的 vtbl。
- 一般来说：类里出现 `virtual` 才会有这套机制（具体内存布局属于实现细节）。

### 6.2 虚调用（virtual dispatch）怎么发生
当你写：

```cpp
Base* p = new Derived;
p->vfunc();   // vfunc 是 virtual
```

运行时大致等价于：

```cpp
(*p->vptr[n])(p);  // n 是 vfunc 在 vtbl 的槽位
```

因此：**调用哪个实现由 p 指向对象的动态类型决定**（这里会调用 `Derived::vfunc`）。

### 6.3 向上转型（upcasting）是什么
向上转型 = **把 Derived 当成 Base 用**（通常是指针/引用形式）：

```cpp
Derived d;
Base* pb = &d;   // ✅ upcasting：Derived* -> Base*
Base& rb = d;    // ✅ upcasting：Derived  -> Base&
```

直觉：子类对象里“包含父类那部分”，所以当成父类看是安全的。

### 6.4 ⚠️ 对象形式会切片（object slicing，不推荐）

```cpp
Derived d;
Base b = d; // ❗切片：只剩 Base 部分，Derived 额外部分丢失
```

所以多态一般用 `Base*` / `Base&`，不用 `Base` 去接 `Derived`。

### 6.5 别混淆：成员指针不是向上转型

```cpp
class Engine {};
class Car {
    Engine* e; // 这是 has-a / delegation：Car 内部指向另一个对象
};
```

- `Engine*` 是“成员指针”，表达的是 **Car 有一个 Engine（或指向实现体）**。
- **只有** `Base* pb = &derived_obj;` / `Base& rb = derived_obj;` 才叫向上转型。

---
