# -*-coding:utf-8 -*-
from random import random
from copy import deepcopy
import tkinter
import random
import tkinter.messagebox
from tkinter import *
from Game import *

chess_color = 0  # 奇数代表黑(人类玩家)，偶数代表白(AI机器人)
chess_list = [[3 for i in range(17)] for j in range(17)]  # 用来记录棋盘信息的矩阵
COLOR_WINNER = ["Black", "While"]
time = 5  # 允许悔棋的次数
r1 = 0  # 指向棋子的对象
now_x, now_y = -1, -1  # 最新落下的棋子的坐标
flag_to_huiqi = 0  # 是否允许悔棋的标志


def main():
    mygame = GoBang()


main()
