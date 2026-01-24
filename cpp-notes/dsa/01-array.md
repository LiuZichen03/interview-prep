> 关键词：Interface/ADT（API 规格） vs Data Structure（实现）

## 1. Interface = API / ADT（规格说明）
- **接口/ADT 解决的是“问题”**：
  - 能存什么数据（what data can store）
  - 支持哪些操作 & 这些操作的语义（what operations are supported & what they mean）
- **数据结构解决的是“实现方案”**：
  - 数据如何在内存中组织
  - 为接口操作提供算法与复杂度保证

---

## 2. Static Sequence Interface（静态序列：长度固定）
> 典型实现：C/C++ 内置数组、`std::array<T, N>`

### Operations
- `build(x)`：用输入 `x` 初始化/填充序列
- `len()`：返回长度
- `iter_seq()`：按顺序遍历
- `get_at(i)`：读取第 `i` 个元素
- `set_at(i, x)`：将第 `i` 个元素写为 `x`

### Complexity（Θ）
- Θ(1)：`len`, `get_at`, `set_at`
- Θ(n)：`build`, `iter_seq`

### Memory intuition（连续内存）
- 数组是**连续内存块**
- 下标访问是地址运算：
  - `a[i]` 等价于 `*(a + i)`
  - 地址：`base + i * sizeof(T)`

---

## 3. Dynamic Sequence Interface（动态序列：长度可变）
> 可以支持插入/删除（长度变化）。常见实现：**动态数组**（`std::vector` / Python `list`）或链表。

### Operations（常见）
- `insert_at(i, x)`：在位置 `i` 插入
- `delete_at(i)`：删除位置 `i`
- `insert_last(x)` / `push_back(x)`：末尾追加

### Complexity（以动态数组实现为例）
- `insert_at/delete_at`：通常 Θ(n)
  - 主要原因：需要**搬移一段元素**（i 之后的元素整体右移/左移）
  - 另外可能触发扩容（见下）
- `insert_last/push_back`：**摊还 Θ(1)**（amortized）
  - 单次最坏 Θ(n)（触发扩容需要复制）

---

## 4. Dynamic Array（动态数组 / vector）核心机制
> 用两个量描述：
- `n = size`：当前元素个数
- `m = capacity`：底层数组容量（可容纳的元素个数）

### 扩容规则（常见：倍增）
- 当 `n == m` 时：申请新数组容量 `m' = 2m`，把旧元素复制过去，再插入新元素。

### Resize cost（一次扩容的成本）
- 复制 `n` 个元素：Θ(n)

### Amortization（摊还分析）
板书含义：
- 若任意连续 `k` 次操作总耗时 ≤ `k · T(n)`，则称该操作的**摊还时间**为 `T(n)`。

应用到 `push_back`：
- 扩容发生在容量达到 1,2,4,8,... 时
- 前 `n` 次 `push_back` 的总复制次数是 Θ(n)（等比求和，总量被常数倍 n 限制）
- 所以 `push_back` 的**摊还时间**为 Θ(1)

---

## 5. 一句话总结（面试口播）
- 静态数组：连续内存，随机访问 Θ(1)，长度固定。
- 动态数组（vector/list 思想）：连续内存 + 倍增扩容，`push_back` 摊还 Θ(1)，中间插入/删除通常 Θ(n)。