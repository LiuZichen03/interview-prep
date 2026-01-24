# interview-prep (C++ + DSA)

> 目标：C++（深入/面试） + DSA（刷题/基础）系统训练  
> 勾选规则：每完成一个模块/小点就打勾；所有代码/笔记沉淀到仓库目录中。

## 仓库结构
- cpp-notes/：语言与机制笔记（短、可复习）
- dsa-implementations/：手写数据结构/算法模板（可复用）
- leetcode/：刷题题解（题号 + 思路 + 复杂度）
- src/：可运行 demo / 验证代码
- resources/：外部资料（例如 CIU 原作者仓库）

## 原作者 DSA 计划（原文）
- [ ] 已引入原作者 CIU 资料（resources/ 下）
- [ ] 阅读与执行： [Coding Interview University](resources/coding-interview-university/README.md)

---

# DSA 学习模块清单（按 CIU 思路整理，便于勾选）

## Big-O 与复杂度
- [x] 时间复杂度基本规则（常见增长阶）
- [ ] 空间复杂度基本规则
- [ ] 递归复杂度直觉（递推/树形展开）
- [ ] 摊还分析直觉（数组扩容/栈操作）

## 数据结构 Data Structures
### 线性结构
- [ ] 数组 / 动态数组（vector）& 复杂度
- [ ] 链表（单/双）核心操作
- [ ] 栈 / 队列（含单调栈/单调队列）
- [ ] 哈希表（unordered_map/set）常见用法与坑

### 树与堆
- [ ] 二叉树遍历（递归/迭代/层序）
- [ ] 二叉搜索树（BST）性质与操作
- [ ] 堆 / priority_queue（TopK、流式）
- [ ] Trie（前缀树）基本实现与使用

### 图与集合结构
- [ ] 图表示（邻接表/矩阵）
- [ ] BFS / DFS（网格/连通块）
- [ ] 并查集（Union-Find）
- [ ] 拓扑排序（有向无环图）

## 算法 Algorithms
- [ ] 二分（边界模板、答案二分）
- [ ] 排序（快排/归并/堆排思想）
- [ ] 双指针 & 滑动窗口
- [ ] 分治（归并思想）
- [ ] 贪心（常见套路：排序 + 选择）
- [ ] 回溯（组合/排列/剪枝）
- [ ] 动态规划（线性/背包/区间/状态压缩）
- [ ] 图算法（最短路：BFS/Dijkstra 直觉；最小生成树：Kruskal 直觉）

## CS 基础（面试常问）
- [ ] 操作系统：进程/线程、内存、锁、死锁
- [ ] 网络：TCP/HTTP/HTTPS 基础
- [ ] 数据库：索引/事务/隔离级别（了解）

## 刷题与复盘输出
- [ ] 题解模板统一（思路/复杂度/边界/代码）
- [ ] 错题本机制（cpp-notes/ 里维护）
- [ ] 每个数据结构至少沉淀 1 份可复用实现（dsa-implementations/）

---

# C++ 深度学习模块清单（面试向）

## C++ 基础强化（写题不卡）
- [ ] 常用类型/表达式/控制流
- [ ] 函数：传值 vs 引用 vs const 引用
- [ ] 头文件与编译单元：include / ODR 直觉
- [ ] const / constexpr（知道边界）

## 内存模型与资源管理（C++ 核心）
- [ ] 栈/堆、对象生命周期、作用域
- [ ] 指针与引用：空指针、悬垂、别名问题
- [ ] new/delete 与 RAII 思想
- [ ] 智能指针：unique_ptr / shared_ptr / weak_ptr
- [ ] 异常安全基本直觉（RAII 为什么能兜底）

## 类与对象（侯捷这块重点）
- [ ] 构造/析构、初始化列表
- [ ] 拷贝构造/拷贝赋值（rule of 3）
- [ ] 移动构造/移动赋值（rule of 5，理解“为什么需要”）
- [ ] 组合优于继承（工程直觉）
- [ ] 多态：virtual / override / vtable 直觉（会讲清）

## STL 深入（刷题 + 工程）
- [ ] vector/string：扩容、迭代器失效
- [ ] unordered_map：hash、rehash、operator[] 插入副作用
- [ ] map/set：红黑树直觉与适用场景
- [ ] algorithm：sort/lower_bound/upper_bound + 自定义比较器
- [ ] lambda：捕获、比较器写法

## 模板与泛型（够用即可）
- [ ] 函数模板/类模板基本写法
- [ ] typename / template 基本语法
- [ ] 常用泛型工具：iterator、traits（了解级）

## 并发基础（面试加分）
- [ ] std::thread 基本使用
- [ ] mutex / lock_guard / unique_lock
- [ ] condition_variable（生产者消费者直觉）
- [ ] atomic（知道用途与边界）

## 构建与调试（你仓库已搭好）
- [ ] CMake：configure/build/run 流程熟练
- [ ] Debug / Release 概念
- [ ] Sanitizers：ASan/UBSan（抓越界/野指针）
- [ ] gdb/lldb：断点、栈回溯、变量查看

## 代码规范与表达（经营 GitHub）
- [ ] clang-format 配置并统一风格
- [ ] Google C++ Style Guide（了解并实践）
- [ ] README 输出：模块进度 + 关键笔记索引

---

# 运行方式（CMake）
- Configure: `cmake -S . -B build`
- Build: `cmake --build build`
- Run: `./build/main`

- DSA（原作者 README 摘取原文）：[README_DSA.md](README_DSA.md)