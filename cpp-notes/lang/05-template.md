# 05 - template（模板）

模板（template）= **让代码对“类型”参数化**。你写一份通用代码，使用时把类型（如 `int` / `double` / `std::string`）代入，编译器会在**编译期**生成对应版本。

---

## 1) class template（类模板）

写法：
```cpp
template <typename T>
class Box {
public:
    Box(T v) : value(v) {}
    T get() const { return value; }

private:
    T value;
};
```

用法：
```cpp
Box<int> a(10);
Box<std::string> b("hi");

int x = a.get();
std::string s = b.get();
```

---

## 2) function template（函数模板）

写法：
```cpp
template <typename T>
T myMax(T a, T b) {
    return (a > b) ? a : b;
}
```

用法（编译器会自动推导 `T`）：
```cpp
int m1 = myMax(3, 7);           // T = int
double m2 = myMax(2.5, 1.2);    // T = double
```

---

## 3) `template<typename T>` vs `template<class T>`

- 在模板参数列表里：`typename` 和 `class` **等价**。
- 个人习惯用哪个都行。

---

## 4) member template（成员模板）

成员模板（member template）= **类里的某个“成员（通常是构造函数/成员函数）”本身也是模板**。

你可以把它理解成：
- 类模板解决的是：`Box<T>` 这整个类对不同 `T` 都能用。
- 成员模板解决的是：在 `Box<T>` 里面，某个成员还想对 **更多类型 `U`** 都能用。

最常见的用途有两个：

### 4.1 跨类型构造（A<T> 从 A<U> 构造）

比如你想让 `Box<int>` 可以从 `Box<double>` 构造（只要能把 `double` 转成 `int`）：

```cpp
template <typename T>
class Box {
public:
    Box(T v) : value(v) {}

    // 成员模板：允许 Box<T> 从 Box<U> 构造
    template <typename U>
    Box(const Box<U>& other) : value(static_cast<T>(other.get())) {}

    T get() const { return value; }

private:
    T value;
};
```

使用：
```cpp
Box<double> bd(3.14);
Box<int> bi = bd;   // 调用成员模板构造：U=double, T=int
// bi.get() == 3
```

关键点：
- `Box` 本身仍然是一个类模板（`Box<T>`）。
- 里面的这个构造函数 **又引入了一个新的模板参数 `U`**，所以叫“成员模板”。

> 直觉：让“不同 T 的 Box”之间也能互相转换/构造。

---

### 4.2 像智能指针那样的“父子类型”转换

真实的 `shared_ptr` / `unique_ptr` 会用成员模板支持这种场景：
- `shared_ptr<Derived>` 能用来构造 `shared_ptr<Base>`（因为 `Derived*` 可以隐式转成 `Base*`）

下面是极简示意（只看思路，不要照抄当成生产级智能指针）：

```cpp
template <typename T>
class Ptr {
public:
    explicit Ptr(T* p = nullptr) : px(p) {}

    // 成员模板：允许 Ptr<U> -> Ptr<T>（只要 U* 能转成 T*）
    template <typename U>
    Ptr(const Ptr<U>& other) : px(other.get()) {}

    T* get() const { return px; }
    T& operator*() const { return *px; }
    T* operator->() const { return px; }

private:
    T* px;
};

struct Base { virtual ~Base() = default; };
struct Derived : Base { void f() {} };
```

使用：
```cpp
Ptr<Derived> pd(new Derived());
Ptr<Base> pb = pd;     // ✅ 通过成员模板构造（U=Derived, T=Base）
```

关键点：
- 如果没有这个成员模板，`Ptr<Base>` 默认只认识 `Ptr<Base>`，不一定能从 `Ptr<Derived>` 构造。
- 有了成员模板，就能把“兼容指针类型”的转换写进类里。

---

### 4.3 成员模板 vs 普通重载（为什么不用写一堆重载）

如果不用成员模板，你可能要为很多 `U` 手写很多构造/函数重载。
成员模板的价值是：
- **写一次，支持一大类类型 U**（只要满足可转换/可用的条件）。

---

## 5) 一句话总结
- **类模板**：生成“不同类型版本的类”
- **函数模板**：生成“不同类型版本的函数”
- **成员模板**：让“类的某个成员”也能对更多类型泛化（常用于跨类型构造/智能指针/迭代器构造等）

---
## 6) specialization（模板特化）

你问“特化是不是给一个类写多个版本？”——**基本是这个意思**：
- 先有一个**主模板（通用版本）**
- 再为某些类型/类型形状提供**更合适的专用版本**

但要区分：**全特化** vs **偏特化**。

### 6.1 主模板（primary template）

```cpp
template <typename Key>
struct Hash {
    size_t operator()(const Key& k) const {
        // 通用写法（示意）：真实 hash 会更复杂
        return 0;
    }
};
```

### 6.2 全特化（full specialization）：为某个具体类型写专用版本

```cpp
// ✅ 全特化：Key = char
template <>
struct Hash<char> {
    size_t operator()(char x) const { return static_cast<size_t>(x); }
};

// ✅ 全特化：Key = int
template <>
struct Hash<int> {
    size_t operator()(int x) const { return static_cast<size_t>(x); }
};
```

使用：
```cpp
Hash<int> h1;
size_t v1 = h1(1000);

Hash<char> h2;
size_t v2 = h2('a');
```

直觉：
- 你图里的 `hash<char> / hash<int> / hash<long>` 就是典型的**全特化**：给“具体类型”单独写一个实现。

### 6.3 偏特化（partial specialization）：为“一类类型形状”写版本（类模板才有）

偏特化不是某个具体类型，而是某种“类型模式”，例如：指针 `T*`、`Box<T*>`、`vector<T>` 等。

例子 1：对指针类型 `T*` 给一个版本：

```cpp
// 主模板
template <typename T>
struct TypeName {
    static const char* name() { return "value"; }
};

// ✅ 偏特化：T* 这类
template <typename T>
struct TypeName<T*> {
    static const char* name() { return "pointer"; }
};

// 用法（只看效果）
// TypeName<int>::name()   -> "value"
// TypeName<int*>::name()  -> "pointer"
```

例子 2：对 `Box<T*>` 这种“形状”单独处理：

```cpp
template <typename T>
class Box {
public:
    Box(T v) : value(v) {}
    T get() const { return value; }
private:
    T value;
};

// ✅ 偏特化：当 T 是指针时
template <typename T>
class Box<T*> {
public:
    Box(T* p) : ptr(p) {}
    T* get() const { return ptr; }
private:
    T* ptr;
};

Box<int> a(3);
Box<int*> b(nullptr);
```

要点：
- **偏特化只存在于“类模板/结构体模板”**。
- **函数模板没有偏特化**（函数一般用“重载”来实现类似效果）。

---

## 7) 什么时候需要特化？

常见动机：
- 某些类型需要更快/更正确的实现（例如不同类型 `hash` 的实现不同）。
- 需要对某种“类型形状”做统一处理（指针、数组、容器等）。

---

## 8) template template parameter（模板的模板参数）❓（先留坑，之后二刷）

### 8.1 一句话直觉
把“**一个类模板**”当作参数传进去。
- 传的不是 `int / double` 这种“类型”
- 而是 `std::vector / std::list` 这种“**模板**”（更准确：类模板）

### 8.2 为什么需要它
有时你想写一段代码，能同时适配：
- `std::vector<T>`
- `std::list<T>`
- `std::deque<T>`
它们本质都是“`容器模板 + 元素类型T`”。

### 8.3 典型写法（先认脸）

最常见（推荐记这个）：
```cpp
// C 是一个“模板”，它能接收若干类型参数（比如 vector<T, Alloc>）
template <template <typename...> class C>
struct UseContainerTemplate { };
```

如果你确定只接收“一个类型参数”的模板（很多时候不够用）：
```cpp
template <template <typename> class C>
struct UseContainerTemplate { };
```

### 8.4 极简示例（只求看懂）

```cpp
#include <vector>
#include <list>

// C 是容器模板，T 是元素类型
template <template <typename...> class C, typename T>
void demo(const C<T>&) {
    // 这里只演示“能接住 vector<T> / list<T>”
}

int main() {
    std::vector<int> v;
    std::list<int> l;

    demo(v);
    demo(l);
}
```

### 8.5 你原来写的那句为什么不对（简单说）
你写的是：
```cpp
template<typename T, template<typename T> class Container>
```
问题：
- 模板模板参数内部一般写“参数名”，不是再用 `typename T` 这种形式
- 而且容器模板通常不止一个模板参数（比如 `vector<T, Alloc>`），所以常用 `typename...`

### 8.6 现在先记住什么
- `template <template <typename...> class C>` 这个长相，看到不慌
- 它的目的：**把 vector/list 这种“模板”当参数传入**

（等你 STL 用熟、模板概念更稳，再回来补：allocator、多个模板参数、为何需要 `...`）
