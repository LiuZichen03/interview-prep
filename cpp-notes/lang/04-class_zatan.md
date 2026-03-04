# 04 - class 杂谈：转换、explicit、pointer-like（迭代器 / 智能指针）

## 1) 转换函数（conversion function / conversion operator）

当你希望“对象可以被当成某个类型使用”时，可以写转换函数：

```cpp
class Fraction {
public:
    Fraction(int num, int den = 1)
        : m_numerator(num), m_denominator(den) {}

    // 转换函数：把 Fraction 转成 double（函数头不写返回类型）
    operator double() const {
        return static_cast<double>(m_numerator) / m_denominator;
    }

private:
    int m_numerator;
    int m_denominator;
};
```

要点：
- 写法固定：`operator 目标类型() const`。
- **别写成 `m_numerator/m_denominator` 再转 double**，那会先发生整除导致精度丢失。

---

## 2) 非 explicit 的单参构造（non-explicit one-argument ctor）

只要构造函数“等价于一个参数”（其余参数有默认值），且没写 `explicit`，它就能触发**隐式类型转换**。

```cpp
class Fraction {
public:
    Fraction(int num, int den = 1)
        : m_numerator(num), m_denominator(den) {}

private:
    int m_numerator;
    int m_denominator;
};

Fraction f(1, 2);
// 这里的 4 会被隐式转换为 Fraction(4, 1)
// 使得表达式可以写成：f + 4
```

一句话：
- **conversion function**：`Fraction -> double`
- **non-explicit one-arg ctor**：`int -> Fraction`

---

## 3) conversion function vs. non-explicit one-arg ctor：为什么有时会报错

当两边都“能自动转”时，编译器可能不知道该选哪条路（歧义），就会报错。

典型冲突：
- 有 `operator double()`（Fraction 能转 double）
- 同时又允许 `int -> Fraction`（构造函数非 explicit）

在某些表达式里，编译器可能既可以：
- 把 `Fraction` 转成 `double` 去算
- 也可以把 `int` 转成 `Fraction` 去算

两条路都“看起来可行”→ 歧义 → 编译错误。

解决思路（常用）：
- 把构造函数加 `explicit`，减少隐式转换；
- 或者避免写“太聪明”的隐式转换，改成显式：`static_cast<double>(f)` / `Fraction{4}`。

---

## 4) explicit：禁止隐式构造

```cpp
class Fraction {
public:
    explicit Fraction(int num, int den = 1)
        : m_numerator(num), m_denominator(den) {}

private:
    int m_numerator;
    int m_denominator;
};

Fraction a = 4;      // ❌ 不允许（隐式）
Fraction b(4);       // ✅ 允许（显式）
Fraction c{4};       // ✅ 允许（显式）
```

> 注意：是 `explicit`，不是 `explict`。

---

## 5) pointer-like classes（像指针一样用的类）：迭代器 / 智能指针

核心：通过重载 `operator*` / `operator->`，让对象“用起来像指针”。

- `operator*()`：解引用（像 `*p`）
- `operator->()`：成员访问（像 `p->method()`）

示意：
```cpp
T& operator*() const;   // 返回 *px
T* operator->() const;  // 返回  px
```

应用：
- **迭代器**：`*it` 取元素，`it->member` 访问元素成员。
- **智能指针**：内部持有裸指针，离开作用域自动释放资源（RAII）。
  - `unique_ptr`：独占所有权
  - `shared_ptr`：共享所有权（引用计数）

---

## 6) function-like classes（函数对象 / 仿函数，functor）

函数对象：**定义了 `operator()` 的对象**，因此“用起来像函数”。

```cpp
struct Add {
    int operator()(int a, int b) const { return a + b; }
};

Add add;
int x = add(1, 2); // 像调用函数一样
```

为什么常用：
- 可以**携带状态**（相比普通函数更灵活）
- 常作为 STL 算法/容器的“策略参数”（如比较器、谓词）

> 备注：C++ 标准库里有很多函数对象（如 `std::less<T>`、`std::greater<T>`）。有些旧式实现会带一些“base classes”（例如用于兼容/萃取类型），你只要把它们理解成“给算法传进去的一种可调用对象”即可。

---

## 7) namespace：经验谈（尽量隔开）

- 尽量避免在头文件里写 `using namespace std;`（容易污染命名空间）。
- 更推荐：
  - 需要谁引入谁：`using std::cout;` / `using std::string;`
  - 或者直接写全名：`std::vector<int>`

---