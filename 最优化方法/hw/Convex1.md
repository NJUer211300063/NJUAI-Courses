# 第一次作业
# 张运吉 211300063
--------------

## Problem1
证：
a)由Cauchy-Schwarz inequality：$|x^\top{y}| \leq \|x\|\|y\|$, 得：
$$x^\top{y}+y^\top{x}\leq 2\|x\|\|y\|$$$$x^\top{x}+x^\top{y}+y^\top{x}+y^\top{y}\leq x^\top{x}+y^\top{y}+2{(x^\top{x})}^{\frac{1}{2}}{(y^\top{y})}^{\frac{1}{2}}$$$$(x+y)^\top(x+y)\leq[(x^\top x)^{\frac{1}{2}}+(y^\top y)^{\frac{1}{2}}]^2$$开根号，得到：$$\|x+y\|\leq\|x\|+\|y\|$$
得证。
b) 欲证$$\|x+y\|^2\leq(1+\epsilon)\|x\|^2+(1+\frac{1}{\epsilon})\|y\|^2$$只需证$$x^\top{x}+y^\top{y}+x^\top{y}+y^\top{x}\leq \|x\|^2+\epsilon\|x\|^2 + \|y\|^2+\frac{1}{\epsilon}\|y\|^2$$即$$x^\top{y}+y^\top{x}\leq \epsilon\|x\|^2 + +\frac{1}{\epsilon}\|y\|^2$$因为$$\epsilon\|x\|^2 + \frac{1}{\epsilon}\|y\|^2\geq2(\epsilon\|x\|^2 \frac{1}{\epsilon}\|y\|^2)^\frac{1}{2}=2\|x\|\|y\|\geq x^\top{y}+y^\top{x}$$所以成立，证毕。
## Problem2
a) 是凸集，证：

$\forall x_1, x_2 \in \{(x,y)\in \mathbb{R}^2_{++}|x/y\leq 1\}$, $x_{11} \leq y_{12}, x_{21} \leq y_{22}$, 

设 $\theta x_1 + (1 - \theta)x_2 = (x , y)$, 则
$$\frac{x}{y} = \frac{\theta x_{11} + (1-\theta)x_{21}}{\theta y_{12} + (1-\theta)y_{22}} \leq \frac{\theta y_{12} + (1-\theta)y_{22}}{\theta y_{12} + (1-\theta)y_{22}} = 1$$
所以$$\theta x_1 + (1 - \theta)x_2 \in \{(x,y)\in \mathbb{R}^2_{++}|x/y\leq 1\}$$ 证毕。

b) 是凸集， 证:

$\forall x_1, x_2 \in \{(x,y)\in \mathbb{R}^2_{++}|x/y\geq 1\}$, $x_{11} \geq y_{12}, x_{21} \geq y_{22}$, 

设 $\theta x_1 + (1 - \theta)x_2 = (x , y)$, 则
$$\frac{x}{y} = \frac{\theta x_{11} + (1-\theta)x_{21}}{\theta y_{12} + (1-\theta)y_{22}} \geq \frac{\theta y_{12} + (1-\theta)y_{22}}{\theta y_{12} + (1-\theta)y_{22}} = 1$$
所以$$\theta x_1 + (1 - \theta)x_2 \in \{(x,y)\in \mathbb{R}^2_{++}|x/y\geq 1\}$$ 证毕。

c) 不是凸集， 反例：

令$x_1 = (\frac{1}{2}, 2), y_1 = (2,\frac{1}{2}), \theta = \frac{1}{2}$,

则 $\theta x_1 + (1-\theta) x_2 = (\frac{5}{4}, \frac{5}{4}) \notin \{(x,y)\in \mathbb{R}^2_{++}|xy\leq 1\}$

d)是凸集， 证：

$\forall (x_1, y_1), (x_2, y_2) \in \{(x,y)\in \mathbb{R}^2_{++}|xy\geq 1\}, x_1y_1 \geq 1,x_2y_2\geq 1$

$\forall 0<\theta<1$， 设$(x_3, y_3) = \theta (x_1, y_1) + (1-\theta)(x_2, y_2)$, 则$$x_3y_3 = [ \theta x_1 + (1-\theta)x_2][ \theta y_1 + (1-\theta)y_2] = \theta^2x_1y_1 + (1-\theta)x_2y_2 + \theta(1-\theta)x_1y_2 + \theta(1-\theta)x_2y_1$$$$\geq \theta^2 + (1-\theta)^2 + 2\sqrt{\theta(1-\theta)x_1y_2  \theta(1-\theta)x_2y_1} = \theta^2 + (1-\theta)^2 + 2\theta(1-\theta) = 1$$所以$(x_3, y_3) \in \{(x,y)\in \mathbb{R}^2_{++}|xy\geq 1\}$
证毕。

e) 不是凸集。反例：
## Problem3
a)证：

$\forall x_1,x_2 \in P$,有 $Ax_1\leqslant b$ 和 $Ax_2\leqslant b$.

$\forall 0 \leq \theta \leq 1, A(\theta x_1+(1-\theta)x_2)=\theta Ax_1+(1-\theta)Ax_2\leqslant \theta b+(1-\theta)b=b$

所以 $ \theta x_1+(1-\theta)x_2\in P$

所以 $P$ 是一个凸集.

b) 证：

$\because S$ 是凸集.

$\therefore \forall x_1, x_2\in S, 0\leqslant \theta\leqslant 1$,  $\theta x_1+(1-\theta)x_2\in S$

$\therefore \forall Ax_1, Ax_2\in A(S), 0\leqslant \theta\leqslant 1$, $A(\theta x_1+(1-\theta)x_2)=\theta Ax_1+(1-\theta)Ax_2\in A(S)$

由于$x_1, x_2$的任意性我们知道，$Ax_1, Ax_2$也是$A(S)$中的任意元素，所以相当于

$\forall y_1, y_2\in A(S), 0\leqslant \theta\leqslant 1$,  $\theta y_1+(1-\theta)y_2\in S$

$\therefore A(S)$ 是凸集.

证毕。

c). 证：

$\because S$ 是凸集.

$\therefore \forall x_1, x_2\in S, 0\leqslant \theta\leqslant 1$, 我们有 $\theta x_1+(1-\theta)x_2\in S$

令 $x_1=Ay_1, x_2=Ay_2$，$\therefore y_1,y_2 \in A^{-1}(S)$

$\forall Ay_1, Ay_2\in S, 0\leqslant \theta\leqslant 1$,  $\theta Ay_1+(1-\theta)Ay_2=A(\theta y_1+(1-\theta)y_2)\in S$

$\therefore \forall y_1, y_2\in A^{-1}(S), 0\leqslant \theta\leqslant 1$,  $\theta y_1+(1-\theta)y_2\in A^{-1}(S)$

证毕。
## Problem4
a). 证：
$\because \displaystyle K^*=\{y|x^{T}y\geqslant 0, \forall x\in K\}$

$\therefore \forall y_1, y_2\in S$, $x^{T}y_1\geqslant 0, x^{T}y_2\geqslant 0$,  $\forall x\in K$

$\therefore \forall 0\leqslant \theta\leqslant 1$, $\theta x^{T}y_1+(1-\theta)x^{T}y_2=x^{T}(\theta y_1+(1-\theta)y_2)\geqslant 0$

$\therefore \theta y_1+(1-\theta)y_2\in K^*$

$\therefore K^*$ 是一个凸锥.

b) 证：

欲证此结论，只需证明$\forall y \in V^*$,只有$x^Ty = 0, \forall x \in V$，不可能出现$x^Ty > 0, \forall x \in V$的情况。

若是$x^Ty > 0, \forall x \in V$，则$ -x \in V$(因为V是子空间)，$y^T(-x) = -y^Tx < 0$

这与$V^*$的定义矛盾

所以$V^* = V^+ = \{ y| y^\top v = 0, \forall v \in V\}$

证毕。

c) 非负象限的对偶锥就是它本身。

证：记非负象限为$A$, $A^* = \{y | x^Ty \geq 0, \forall x \in A\}$,

$\forall y \in A^*, 取 x_i = (0, 0, ..., 1, ... ,0) \in A, i = 1, 2, ..., n$($x_i$的第i位为1，其余为0)

由$x_i^Ty \geq 0$, 得$y_i \geq 0 (y_i是y的第i个分量)$

所以$A^*$就是非负象限。
## Problem5
a). 证：
$\because \displaystyle K^*=\{y|x^{T}y\geqslant 0, \forall x\in K\}$

$\therefore \forall y_1, y_2\in S$, $x^{T}y_1\geqslant 0, x^{T}y_2\geqslant 0$,  $\forall x\in K$

$\therefore \forall 0\leqslant \theta\leqslant 1$, $\theta x^{T}y_1+(1-\theta)x^{T}y_2=x^{T}(\theta y_1+(1-\theta)y_2)\geqslant 0$

$\therefore \theta y_1+(1-\theta)y_2\in K^*$

$\therefore K^*$ 是一个凸锥.

b). 证：
$\forall y \in K^*_2, x^Ty_ \geq 0, \forall x \in K_2$

$\because K_1 \subseteq K_2 \therefore \forall x \in K_1, x \in K_2$

$\therefore \forall x \in K_1, x^Ty_ \geq 0(y是第一行中的y)$

即$\forall y \in K^*_2, y \in K^*_1$

$\therefore K^*_2 \subseteq K^*_1$

证毕。
