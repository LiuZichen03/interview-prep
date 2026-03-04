

# 08 - const（图解笔记）

> 这章对应课件那张「const object × const/non-const member function」表格。

---

## 1) 两个维度：对象是否 const × 成员函数是否 const

### 1.1 const object / non-const object
- **const object**：对象被声明为 `const`，它的 **data members 不允许被修改**。
  ```cpp
  const String s("hello");
  ```
- **non-const object**：普通对象，**可以修改** data members。
  ```cpp
  String s("hello");
  ```

### 1.2 const member function / non-const member function
- **const member function**：成员函数末尾带 `const`。
  ```cpp
  void print() const;
  ```
  含义：此函数承诺「逻辑上不修改对象状态」。
- **non-const member function**：末尾不带 `const`。
  ```cpp
  void set(int x);
  ```
  含义：可能会修改对象状态。

---

## 2) 表格规则（✅/❌）

结论一句话：
- **const object 只能调用 const member function**
- **non-const object 两种都能调用**

对应四格：

| 对象 \ 成员函数 | const member function | non-const member function |
|---|---|---|
| **const object** | ✅ 可以调用 | ❌ 不可调用 |
| **non-const object** | ✅ 可以调用 | ✅ 可以调用 |

---

## 3) 为什么会这样（抓住 this）

- 在 **const 成员函数**里，`this` 的类型会被视为：
  ```cpp
  const ClassName* const this
  ```
  所以你无法通过 `this` 去改 data members，也无法调用 non-const 成员函数（它们需要 `ClassName*`）。

---

## 4) 图里那段例子的含义

```cpp
const String str("hello world");
str.print();
```

- 如果 `print()` 没写成 `const`：
  ```cpp
  void print(); // non-const
  ```
  那么 `const String` 就 **不能调用**，编译器会报错。

- 正确（常见）写法：
  ```cpp
  void print() const;
  ```

---

## 5) 经典：operator[] 的 const / non-const 两个版本

目的：
- 非 const 对象：`[]` 允许修改元素
- const 对象：`[]` 只能读

```cpp
class String {
public:
    char& operator[](size_t i) { return m_data[i]; }              // 可写
    const char& operator[](size_t i) const { return m_data[i]; } // 只读
private:
    char* m_data;
};

String s("hi");
s[0] = 'H';              // ✅ ok

const String cs("hi");
// cs[0] = 'H';         // ❌ 不允许（只读）
char c = cs[0];          // ✅ ok
```

---

## 6) 额外补充（常见坑）

### 6.1 non-const 可以调用 const，但反过来不行
- non-const 对象调用 const 成员函数：没问题（更“严格”的承诺当然能满足）。
- const 对象调用 non-const 成员函数：不行（可能修改对象）。

### 6.2 const 是函数签名的一部分（成员函数）
同名同参时：
```cpp
void f();
void f() const; // ✅ 这是另一个重载版本
```

### 6.3 想在 const 函数里改「缓存」怎么办（mutable）
```cpp
mutable int cached = 0;
int get() const { cached = 1; return cached; } // ✅ 允许改 mutable 成员
```

---

## 7) 一句记忆法
- **对象 const**：我这个对象“不许改”。
- **函数 const**：我这函数“保证不改对象”。
- **const 对象只能调用保证不改的函数（const member function）。**