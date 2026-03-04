# Reference（引用）速记

> 直觉：`T&` 是 **T 的别名**（alias）。
> - 必须在声明时绑定到某个对象
> - 之后 **不能改绑**（不能“重新代表”别的对象）

---

## 1) 指针 vs 引用（最核心区别）

```cpp
int x = 0;
int* p = &x;   // p 保存 x 的地址（可以改指向、可以为 nullptr）
int& r = x;    // r 是 x 的别名（必须绑定、不能为 null、不能改绑）

*r = 10;       // 通过引用改 x
*p = 20;       // 通过指针改 x
```

- **指针**：是一个“值”（地址），可以改、可以空。
- **引用**：更像“另一个名字”，用起来像变量本身。

---

## 2) 引用不能改绑（你这段理解是对的）

```cpp
int x = 0;
int& r = x;   // r 代表 x

int x2 = 5;
r = x2;       // ❗不是改绑：这是“赋值”给 x（所以 x 变成 5）
// 现在 x == 5, r == 5

int& r2 = r;  // r2 也是 x 的别名
```

> 记法：`r = x2` 永远是“给 r 绑定的那个对象赋值”，不是“让 r 去绑定 x2”。

---

## 3) 引用最常见用途：参数与返回值

### 3.1 作为参数（避免拷贝 + 调用端写法自然）

下面三种写法在“调用端”的差异：

```cpp
struct Cls { void xxx() {} };

void func1(Cls* pobj) { pobj->xxx(); }  // 指针参数：调用端要传 &obj，函数内要写 ->
void func2(Cls  obj ) { obj.xxx();  }   // 值传递：会拷贝（大对象开销大）
void func3(Cls& obj ) { obj.xxx();  }   // 引用参数：不拷贝，调用端像值传递一样写

Cls obj;
func1(&obj);  // 指针：调用端要取地址
func2(obj);   // 值：会拷贝
func3(obj);   // 引用：调用端写法和 func2 一样，但不拷贝 ✅
```

经验法则：
- 只读参数：`const T&`（最常用）
- 需要修改参数：`T&`
- 需要“可空/可改指向”：`T*`

### 3.2 作为返回值（返回“某个对象本身”而不是副本）

典型用法：返回左值引用以支持链式调用：

```cpp
class A {
public:
    A& set(int v) { x = v; return *this; }
private:
    int x = 0;
};

A a;
a.set(1).set(2); // 链式调用
```

---

## 4) 关于“signature / same signature / ambiguity”

### 4.1 顶层 const（top-level const）不是函数签名的一部分

下面两个**被当作同一个签名**，不能同时存在：

```cpp
double imag(double im);
double imag(const double im); // ❌ 和上面一样（顶层 const 会被忽略）
```

### 4.2 值传递 vs `const&`：可以写成重载，但很容易产生二义性

```cpp
double imag(double im);
double imag(const double& im);

int x = 3;
// imag(x);  // ⚠️ 对很多类型/场景会出现“二义性(ambiguity)”风险
```

实际建议：
- 小型标量（`int/double` 等）通常只写：`T`（值传递）
- 大对象（`std::string`、容器、自定义大类）通常写：`const T&`
- 不要为了“看起来更高级”给标量也写 `const T&` 重载（容易把重载搞出歧义）

---

## 5) 一句话总结
- `T&` 是别名：**绑定一次，终身不改绑**
- `r = other` 是赋值，不是改绑
- 引用最常见用于：**参数（减少拷贝）**、**返回值（链式/返回对象本身）**