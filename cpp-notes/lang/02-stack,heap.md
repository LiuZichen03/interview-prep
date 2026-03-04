# Stack / Heap / Object Lifetime

本节整理：对象在不同存储区域（stack / heap / global / static）中的**生命周期**、构造/析构时机，以及 `new / delete` 的真实行为。

## 1. Stack objects（栈对象）
- **生命周期**：从定义点开始，到**离开作用域**结束。
- **离开作用域会自动调用析构函数（dtor）**。

```cpp
void f() {
    String s; // stack object
} // scope end -> ~String() 自动执行
```

## 2. Stack local objects（局部栈对象）
- “stack local” 指**函数内部的局部对象**。
- **不是**“直到程序结束”。它和普通栈对象一样：**到作用域结束就销毁**。

## 3. Global / Static objects（全局 / 静态对象）
- **global objects（全局对象）**：定义在所有函数外。
  - 生命周期：**程序开始构造**，**程序结束析构**。
- **static objects（静态对象）**：`static` 修饰的对象（全局/局部）。
  - 生命周期：通常在**第一次到达定义处**后初始化，**程序结束析构**（实现细节可能不同，但结论可这样记）。

> 区分：**作用域（scope）≠ 生命周期（lifetime）**。

## 4. Heap objects（堆对象）
- 通过 `new` 创建。
- **生命周期不受作用域控制**，只有在 `delete` 之后结束。

```cpp
String* p = new String("hello");
// ...
delete p; // 结束对象生命周期
```

## 5. new / delete 的真实顺序（重点）
- `new`：**先分配内存** → **再调用构造函数**。
- `delete`：**先调用析构函数** → **再释放内存**。

## 6. new[] / delete[]（数组形式）
- `new[]` 必须配套 `delete[]`。

```cpp
String* p = new String[3];
delete[] p; // 会调用 3 次 ~String()
```

- 如果误用 `delete p;`：析构次数不匹配，属于**未定义行为（UB）**。

## 7. 内存视角（补充）
- **地址**：对象无论在 stack/heap，本质都是“某段内存 + 类型解释”。指针保存的就是地址。
- **连续性与局部性**：连续内存访问更容易命中 CPU cache；数组/动态数组通常更“快”，链表更“跳”。
- **stack 的特点**：由编译器/运行时管理，分配/回收接近 O(1)，非常快；容量相对小；受调用深度影响。
- **heap 的特点**：由 allocator 管理，分配/回收更灵活但更慢；可能产生碎片；生命周期完全由程序控制。
- **对齐与 padding**：对象大小不一定等于成员大小之和，编译器会为对齐插入 padding（这也是 Debug/Release 看到不同占用的原因之一）。
- **常见内存错误**：
  - 内存泄漏（忘记 delete / delete[]）
  - 悬空指针（delete 后继续用）
  - 重复释放（double free）
  - 越界访问（写爆数组）

> 经验：能用自动对象就别手动 new；必须手动 new 时要明确“谁负责 delete”（所有权）。

## 8. Debug / Release 内存占用（了解）
- Debug（例如 VC 下）往往有额外调试填充/对齐/头部信息，显示出来的占用会更大。
- Release 更接近真实运行时开销。

## 9. 一句话总结
- 栈对象：作用域结束自动析构。
- 堆对象：必须手动 `delete`。
- `new = malloc + ctor`，`delete = dtor + free`。
- `new[]` 必须用 `delete[]`。