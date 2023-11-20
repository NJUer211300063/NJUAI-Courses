import math


# (0,1)上的均匀分布
class UniformDistribution:
    def __init__(self, x0, a=630360016, c=7, m=2 ** 31 - 1):
        self.a = a
        self.m = m
        self.c = c
        self.x0 = x0

    # 随机数生成器
    def generate(self):
        tmp = (self.a * self.x0 + self.c) % self.m
        self.x0 = tmp
        return float(tmp) / self.m


# 伯努利分布
class BernoulliDistribution:
    def __init__(self, p):
        self.p = p
        self.unirnd = UniformDistribution(1)

    def generate(self):
        tmp = self.unirnd.generate()
        if tmp <= (1 - self.p):
            return 0
        return 1


# 二项分布
class BinomialDistribution:
    def __init__(self, n, p):
        self.n = n
        self.p = p
        self.func = self.getDisFunc()
        self.unirnd = UniformDistribution(1)

    # 因为二项分布的取值有限，所以我直接把分布函数存在一个列表[f(1), f(2), ..., f(n)]
    def getDisFunc(self):
        func = []
        sum = 0
        for k in range(self.n + 1):
            sum += math.factorial(self.n) / (math.factorial(k) * math.factorial(self.n - k)) * (self.p ** k) * (
                    (1 - self.p) ** (self.n - k))
            func.append(sum)
        return func

    def generate(self):
        x = self.unirnd.generate()
        if x <= self.func[0]:
            return 0
        else:
            for i in range(1, self.n + 1):
                if self.func[i - 1] < x <= self.func[i]:
                    return i


# 泊松分布
class PoissonDistribution:
    def __init__(self, randa):
        self.randa = randa
        self.unirnd = UniformDistribution(1)

    def compute(self, k):
        return (math.e ** (-self.randa)) * (self.randa ** k) / math.factorial(k)

    def generate(self):
        x = self.unirnd.generate()
        sum = 0
        k = 0
        while True:
            sum += self.compute(k)
            if x <= sum:
                return k
            k += 1


# 几何分布
class GeometryDistribution:
    def __init__(self, p):
        self.p = p
        self.unirnd = UniformDistribution(1)

    def compute(self, k):
        return ((1 - self.p) ** (k - 1)) * self.p

    def generate(self):
        x = self.unirnd.generate()
        sum = 0
        k = 1
        while True:
            sum += self.compute(k)
            if x <= sum:
                return k
            k += 1


# 指数分布
class ExponentsDistribution:
    def __init__(self, randa):
        self.randa = randa
        self.unirnd = UniformDistribution(1)

    def generate(self):
        x = self.unirnd.generate()
        return -math.log(1 - x) / self.randa


# 正态分布
class NormalDistribution:
    def __init__(self, miu, kexi2):
        self.miu = miu
        self.kexi2 = kexi2
        self.unirnd1 = UniformDistribution(1)
        self.unirnd2 = UniformDistribution(2)

    def generateN(self):
        x1 = self.unirnd1.generate()
        x2 = self.unirnd2.generate()
        return (-2 * math.log(x1)) ** 0.5 * math.cos(2 * math.pi * x2)

    def generate(self):
        x = self.generateN()
        return self.kexi2 ** 0.5 * x + self.miu


# 验证(0，1)上的均匀分布
def validationUni():
    print("验证(0，1)上的均匀分布")
    tmp1, tmp2 = 0, 0
    avg, var = 0.5, 1.0 / 12
    seed = input("请输入随机种子：")
    uniRnd = UniformDistribution(int(seed))
    for i in range(100000):
        tmp = uniRnd.generate()
        print(tmp)
        tmp1 += tmp
        tmp2 += (tmp - 0.5) ** 2
    print("----------------")
    print("伪平均值：%f, 伪方差：%f" % (tmp1 / 100000, tmp2 / 100000))
    print("真平均值：%f, 真方差：%f" % (avg, var))


def validationBer():
    print("验证伯努利分布")
    tmp1, tmp2 = 0, 0
    p = eval(input("请输入伯努利分布的参数p："))
    ber = BernoulliDistribution(p)
    avg, var = p, p * (1 - p)
    for i in range(100000):
        tmp = ber.generate()
        print(tmp)
        tmp1 += tmp
        tmp2 += (tmp - avg) ** 2
    print("----------------")
    print("伪平均值：%f, 伪方差：%f" % (tmp1 / 100000, tmp2 / 100000))
    print("真平均值：%f, 真方差：%f" % (avg, var))


def validationBin():
    print("验证二项分布")
    tmp1, tmp2 = 0, 0
    n = eval(input("请输入二项分布的参数n："))
    p = eval(input("请输入二项分布的参数p："))
    bin = BinomialDistribution(n, p)
    avg, var = n * p, n * p * (1 - p)
    for i in range(100000):
        tmp = bin.generate()
        print(tmp)
        tmp1 += tmp
        tmp2 += (tmp - avg) ** 2
    print("----------------")
    print("伪平均值：%f, 伪方差：%f" % (tmp1 / 100000, tmp2 / 100000))
    print("真平均值：%f, 真方差：%f" % (avg, var))


def validationPoi():
    print("验证泊松分布")
    tmp1, tmp2 = 0, 0
    n = eval(input("请输入泊松分布的参数："))
    poi = PoissonDistribution(n)
    avg, var = n, n
    for i in range(100000):
        tmp = poi.generate()
        print(tmp)
        tmp1 += tmp
        tmp2 += (tmp - avg) ** 2
    print("----------------")
    print("伪平均值：%f, 伪方差：%f" % (tmp1 / 100000, tmp2 / 100000))
    print("真平均值：%f, 真方差：%f" % (avg, var))


def validationGeo():
    print("验证几何分布")
    tmp1, tmp2 = 0, 0
    p = eval(input("请输入几何分布的参数："))
    poi = GeometryDistribution(p)
    avg, var = 1.0 / p, (1.0 - p) / (p ** 2)
    for i in range(100000):
        tmp = poi.generate()
        print(tmp)
        tmp1 += tmp
        tmp2 += (tmp - avg) ** 2
    print("----------------")
    print("伪平均值：%f, 伪方差：%f" % (tmp1 / 100000, tmp2 / 100000))
    print("真平均值：%f, 真方差：%f" % (avg, var))


def validationExp():
    print("验证指数分布")
    tmp1, tmp2 = 0, 0
    p = eval(input("请输入指数分布的参数："))
    poi = ExponentsDistribution(p)
    avg, var = 1.0 / p, 1.0 / (p ** 2)
    for i in range(100000):
        tmp = poi.generate()
        print(tmp)
        tmp1 += tmp
        tmp2 += (tmp - avg) ** 2
    print("----------------")
    print("伪平均值：%f, 伪方差：%f" % (tmp1 / 100000, tmp2 / 100000))
    print("真平均值：%f, 真方差：%f" % (avg, var))


def validationNor():
    print("验证正态分布")
    tmp1, tmp2 = 0, 0
    miu = float(input("请输入正太分布的参数miu："))
    kexi2 = float(input("请输入正太分布的参数kexi^2："))
    poi = NormalDistribution(miu, kexi2)
    avg, var = miu, kexi2
    for i in range(100000):
        tmp = poi.generate()
        print(tmp)
        tmp1 += tmp
        tmp2 += (tmp - avg) ** 2
    print("----------------")
    print("伪平均值：%f, 伪方差：%f" % (tmp1 / 100000, tmp2 / 100000))
    print("真平均值：%f, 真方差：%f" % (avg, var))


if __name__ == "__main__":
    validationUni()
    validationBer()
    validationBin()
    validationPoi()
    validationGeo()
    validationExp()
    validationNor()
