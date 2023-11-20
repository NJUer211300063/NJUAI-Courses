# 同步&死锁
1. 竞争条件: 两个或多个进程读写某些共享数据, 而最后的结果取决于进程运行的精确时序, 称为竞争条件.
2. 临界区: 我们把共享内存进行访问时的程序片段称作临界区.
    * Mutual Exclusion / Safety: 任何两个进程不能同时处于其临界区.
    * 不应该对 CPU 速度和数量做任何假设.
    * Progress / Liveness：临界区外运行的进程不得阻塞其他进程.
    * Bounded Waiting / Fairness: 不得使进程无期限等待进入临界区.
    * Performance： The overhead of entering and exiting the critical section is small with respect to the work being done within it.
3. 互斥
    * 忙等待: 连续测试一个变量直到某个值出现为止, 称为忙等待. 用于忙等待的锁, 称为自旋锁.
    * 皮特森算法: 只需要两个全局变量 `turn` 和 `interested` 来分别指示轮到的进程 (其实感觉更应该说是轮到谁等待) 和对临界区感兴趣的进程.
        ```c
        void enter_region(int process) {
            int other = 1 - process;
            interested[process] = TRUE;
            turn = process;
            while (turn == process && interested[other] == TRUE);
        }

        void leave_region(int process) {
            interested[process] = FALSE;
        }
        ```
    * TSL 指令: 测试并加锁, `TSL RX, LOCK` 可以原子地将 `LOCK` 读到 `RX` 寄存器中, 并在 `LOCK` 处写一个非零值. 类似地还有原子地交换两个位置内容的指令 XCHG.
    * 优先级反转: 由于低优先级进程 L 占据了临界区, 导致高优先级进程 H 一直在临界区外忙等待, 让 L 不能被调度, 也就不能出临界区. 这种情况有时候称为优先级反转. 
4. 条件变量(同步)
    * 生产者消费者问题:
        ```c
        pthread_mutex_lock(&mutex);
        while (buffer ?= 0) pthread_cond_wait(&cond, &mutex);
        buffer = ?;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
5. 信号量
    * PV操作题目的解题思路：
        - 关系分析。找出题目中描述的各个进程，分析它们之间的同步、互斥关系。
        - 整理思路。根据各进程的操作流程确定PV操作的大致顺序。
        - 设置信号量。设置需要的信号量，并根据题目条件确定信号量初值。ps：互斥信号量一般设置为1，同步信号量的初始值要看对应资源的初始值是多少。
    * **注意**：实现互斥的P操作一定要在实现同步的P操作之后，否则可能会引起“死锁”。
    * 生产者-消费者问题(同步)
        [视频链接](https://www.bilibili.com/video/BV1YE411D7nH?p=32&vd_source=755189cff4a0b01d067d0e0ed39fb415)
    * 读者-写者问题(互斥)
        [视频链接](https://www.bilibili.com/video/BV1YE411D7nH?p=35&vd_source=755189cff4a0b01d067d0e0ed39fb415)
    * 哲学家就餐问题(互斥)
        [视频链接](https://www.bilibili.com/video/BV1YE411D7nH/?p=36&spm_id_from=333.1007.top_right_bar_window_history.content.click&vd_source=755189cff4a0b01d067d0e0ed39fb415)
6. 管程
    1. 定义: 一个管程是一个由过程、变量以及数据结构等组成的一个集合, 且任一时刻管程中只能有一个活跃进程. (可以简单理解为由编译器管理的互斥量或二元信号量).
    2. 自身阻塞: 引入条件变量和两个相关操作 `wait` 和 `signal`. 而 `signal` 后对进程的处理, 则引出了三种不同的语义.
    3. Hoare: 让新唤醒进程运行, 挂起发信号进程. 因此需要三个队列 `signal_queue`, `wait_queue` 和 `ready_queue`, 因此是实现起来最复杂的.
    4. Hansen: 执行 `signal` 的进程必须立刻退出管程, 即 `signal` 是管程的最后一条语句. 因为 Hansen 语义为简单, 只需要 `wait_queue` 和 `ready_queue`.
    5. Mesa: 让发信号进程继续运行, 直到发信号进程退出管程后, 才允许等待的进程开始运行. 类似 Hansen 语义, 只不过没有了 `signal` 是末尾语句的限制, 也只需要 `wait_queue` 和 `ready_queue`, 因此被广泛地实现. 但是因此也要注意一个问题, 线程被唤醒时, 必须检查 `condition` 是否满足, 也就是要使用 `while` 而不是 `if`.
8. 屏障
7. Read-Copy-Update (RCU)
    1. RCU 主要针对的数据对象是链表, 目的是提高遍历读取数据的效率, 为了达到目的使用 RCU 机制读取数据的时候不对链表进行耗时的加锁操作. 这样在同一时间可以有多个线程同时读取该链表, 并且允许一个线程对链表进行修改 (修改的时候, 需要加锁).
    2. 保证读取链表的完整性. 新增或者删除一个节点, 不至于导致遍历一个链表从中间断开. 但是 RCU 并不保证一定能读到新增的节点或者不读到要被删除的节点. 
    3. 订阅-发布机制: 在读取过程中, 另外一个线程插入了一个新节点, 而读线程读到了这个节点, 那么需要保证读到的这个节点是完整的. 这里涉及到了发布-订阅机制 (Publish-Subscribe Mechanism).
        ```c
        // 发布
        rcu_assign_pointer(&NodeA->Next, NodeC);
        // 订阅
        read = rcu_dereference(&Node->Next);
        ```
    4. 宽限期: 在读取过程中, 另外一个线程删除了一个节点. 删除线程可以把这个节点从链表中移除, 但它不能直接销毁这个节点, 必须等到所有的读取线程读取完成以后, 才进行销毁操作. RCU 中把这个过程称为宽限期(Grace period).
        ```c
        // 用来保持一个读者的 RCU 临界区
        rcu_read_lock()
        rcu_read_unlock()

        // RCU 的核心所在, 它挂起写线程, 等待读者都退出后释放老的数据
        synchronize_rcu()
        ```


