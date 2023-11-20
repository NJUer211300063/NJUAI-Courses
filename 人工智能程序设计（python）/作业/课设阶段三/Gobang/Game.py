# -*-coding:utf-8 -*-
import tkinter
import tkinter.messagebox
from tkinter import *
from Evaluate import *
from Players import *


class GoBang:
    BLACK = 0  # 黑棋人类玩家
    WHITE = 1  # 白棋AI

    def __init__(self):
        self.is_startgame = False  # 开始标志
        self.chess_len = 15
        self.is_draw = self.chess_len * self.chess_len  # 用来判断是否平局
        self.cur_palyer = None  # 当前棋子的颜色
        self.winner = None
        self.cur_chess1 = None
        self.cur_chess2 = None  # 指向最新一个棋子对象，用来悔棋
        self.color = ['black', 'white']
        self.time = 5
        self.cur_pos1 = [None, None]
        self.cur_pos2 = [None, None]
        self.chess_list = [[3 for i in range(16)] for j in range(16)]
        self.white_info = []
        self.black_info = []
        self.score_list = [7, 35, 800, 15000, 800000, 15, 400, 8000, 100000, 0]
        self.white_type_num = {'LIVE_FIVE': 0, 'LIVE_FOUR': 0, 'CHONG_FOUR': 0, 'LIVE_THREE': 0,
                               'SLEEP_THREE': 0, 'LIVE_TWO ': 0, 'SLEEP_TWO': 0, 'None': 0}
        self.black_type_num = {'LIVE_FIVE': 0, 'LIVE_FOUR': 0, 'CHONG_FOUR': 0, 'LIVE_THREE': 0,
                               'SLEEP_THREE': 0, 'LIVE_TWO ': 0, 'SLEEP_TWO': 0, 'None': 0}
        self.pos_score = [[(7 - max(abs(x - 7), abs(y - 7))) for x in range(self.chess_len)] for y in
                          range(self.chess_len)]
        self.evaluate = Evaluate(self.chess_list)
        self.human = Human()
        self.ai = AI()
        # --------------------------------------------------------------------------------
        # --------------------------------------------------------------------------------
        self.root = tkinter.Tk()
        self.root.title("FIVE-CHESS BY ZYJ")
        self.root.geometry("700x510+100+100")
        self.cv = tkinter.Canvas(self.root, width=510, height=510, background="#DEB887")  # 画布
        self.cv.place(x=0, y=0)
        self.cv1 = tkinter.Canvas(self.root, width=190, height=510, background='WHITE')  # 画布1
        self.cv1.place(x=510, y=0)
        self.start_button = tkinter.Button(self.root, text="开始游戏", font=("微软雅黑", 20), width=10,
                                           command=self.startgame, relief=RIDGE, background="#DEB887")  # 开始游戏按钮
        self.start_button.place(x=520, y=30)
        self.huiqi_button = tkinter.Button(self.root, text="悔棋", font=("微软雅黑", 20), width=10,
                                           command=self.huiqi, relief=RIDGE, background="#DEB887")  # 悔棋按钮
        self.huiqi_button.place(x=520, y=110)
        self.restart_button = tkinter.Button(self.root, text="重新开始", font=("微软雅黑", 20), width=10,
                                             command=self.restart, relief=RIDGE, background="#DEB887")  # 重新开始按钮
        self.restart_button.place(x=520, y=190)
        self.create_map()
        self.root.mainloop()

    def create_map(self):
        """"绘制棋盘"""
        for num in range(1, 17):
            self.cv.create_line(num * 30, 30, num * 30, 480, width=2)
        for num in range(1, 17):
            self.cv.create_line(30, num * 30, 480, num * 30, width=2)

    def startgame(self):
        self.is_startgame = True
        self.cv.bind("<Button-1>", self.gaming)
        self.cur_palyer = GoBang.BLACK

    def restart(self):
        self.winner = None
        self.cur_palyer = GoBang.BLACK
        self.is_draw = 16 * 16
        for i in range(len(self.chess_list)):
            for j in range(len(self.chess_list)):
                self.chess_list[i][j] = 3
        self.time = 5
        self.black_info = []
        self.white_info = []
        self.cv.delete("all")
        self.create_map()

    def huiqi(self):
        if self.time > 0 and self.cur_chess1 and self.cur_chess2:
            self.cv.delete(self.cur_chess1)
            self.cur_chess1 = None
            self.cv.delete(self.cur_chess2)
            self.cur_chess2 = None
            # print(self.cur_chess1, self.cur_chess2)
            self.chess_list[self.cur_pos1[0]][self.cur_pos1[1]] = 3
            self.chess_list[self.cur_pos2[0]][self.cur_pos2[1]] = 3
            self.black_info.pop()
            self.white_info.pop()
            self.is_draw += 2
            self.winner = None
            # self.cur_palyer = (self.cur_palyer + 1) % 2
            self.time -= 1
            tkinter.messagebox.showinfo("Tips:", "You have %d more chances to\n take back!" % self.time)
        elif self.time <= 0:
            tkinter.messagebox.showinfo("Tips", "You can't take back any more!")
        else:
            return

    def draw_chess(self, x, y):
        if self.chess_list[x // 30 - 1][y // 30 - 1] == 3:
            self.cur_pos1 = self.cur_pos2
            self.cur_pos2 = [x // 30 - 1, y // 30 - 1]
            self.cur_chess1 = self.cur_chess2
            self.cur_chess2 = self.cv.create_oval(x - 15, y - 15, x + 15, y + 15,
                                                  fill=self.color[self.cur_palyer])  # 在鼠标点击处下棋
            self.chess_list[x // 30 - 1][y // 30 - 1] = self.cur_palyer
            if self.cur_palyer == GoBang.BLACK:
                self.black_info.append([x // 30 - 1, y // 30 - 1])

            else:
                self.white_info.append([x // 30 - 1, y // 30 - 1])
            self.cur_palyer = (self.cur_palyer + 1) % 2  # 更新棋子颜色
            self.is_draw -= 1
            self.judge_winner(x // 30 - 1, y // 30 - 1)  # 判断是否有人已经胜利
        else:
            self.cur_palyer = (self.cur_palyer + 1) % 2

    def get_pos(self, x, y):
        if 30 <= x <= 480 and 30 <= y <= 480:
            if x % 30 >= 15:
                x = x + 30 - (x % 30)
            else:
                x = x - (x % 30)
            if y % 30 >= 15:
                y = y + 30 - (y % 30)
            else:
                y = y - (y % 30)
            return x, y
        else:
            return None

    def gaming(self, event):
        if self.is_startgame and not self.winner and self.is_draw:
            x, y = self.get_pos(event.x, event.y)
            if self.chess_list[x // 30 - 1][y // 30 - 1] == 3:
                # x, y = self.get_pos(event.x, event.y)
                self.draw_chess(x, y)
                self.AI_play()
            else:
                return

    def judge_winner(self, xx, yy):
        if not self.is_draw:
            self.winner = 'None'
            tkinter.messagebox.showinfo("I LOVE IU", "Game over, the game has drawn!")
        count = 0
        for i in range(xx + 1, 16):
            if self.chess_list[i][yy] == self.chess_list[xx][yy]:
                count += 1
            else:
                break
        for i in range(xx, -1, -1):
            if self.chess_list[i][yy] == self.chess_list[xx][yy]:
                count += 1
            else:
                break
        if count == 5:
            self.winner = self.color[self.chess_list[xx][yy]]
            tkinter.messagebox.showinfo("I LOVE IU", "Game over,winner is %s!" % self.color[self.chess_list[xx][yy]])
        count = 0
        for i in range(yy + 1, 16):
            if self.chess_list[xx][i] == self.chess_list[xx][yy]:
                count += 1
            else:
                break
        for i in range(yy, -1, -1):
            if self.chess_list[xx][i] == self.chess_list[xx][yy]:
                count += 1
            else:
                break
        if count == 5:
            self.winner = self.color[self.chess_list[xx][yy]]
            tkinter.messagebox.showinfo("I LOVE IU", "Game over,winner is %s!" % self.color[self.chess_list[xx][yy]])
        count = 0
        for i, j in zip(range(xx, -1, -1), range(yy, -1, -1)):
            if self.chess_list[i][j] == self.chess_list[xx][yy]:
                count += 1
            else:
                break
        for i, j in zip(range(xx + 1, 16), range(yy + 1, 16)):
            if self.chess_list[i][j] == self.chess_list[xx][yy]:
                count += 1
            else:
                break
        if count == 5:
            self.winner = self.color[self.chess_list[xx][yy]]
            tkinter.messagebox.showinfo("I LOVE IU", "Game over,winner is %s!" % self.color[self.chess_list[xx][yy]])
        count = 0
        for i, j in zip(range(xx, -1, -1), range(yy, 16)):
            if self.chess_list[i][j] == self.chess_list[xx][yy]:
                count += 1
            else:
                break
        for i, j in zip(range(xx + 1, 16), range(yy - 1, -1, -1)):
            # print(self.chess_list[i][j],self.chess_list[xx][yy])
            if self.chess_list[i][j] == self.chess_list[xx][yy]:
                count += 1
            else:
                break
        if count == 5:
            self.winner = self.color[self.chess_list[xx][yy]]
            tkinter.messagebox.showinfo("I LOVE IU", "Game over,winner is %s!" % self.color[self.chess_list[xx][yy]])
        count = 0

    # ---------------------------------------------------------------------------------------------------------

    def AI_play(self):
        if not self.winner and self.is_draw and self.is_startgame:
            x, y = self.min_max(self.chess_list, 1)
            self.draw_chess((x + 1) * 30, (y + 1) * 30)

    def genmove(self, board):
        """获取所有可以下棋的的点，并给出初始得分"""

        moves = []
        for x in range(self.chess_len):
            for y in range(self.chess_len):
                if board[x][y] == 3:
                    score = self.pos_score[x][y]
                    moves.append((score, x, y))

        moves.sort(reverse=True)
        return moves

    def min_max(self, board, turn):
        """获取评分最大的点"""
        score_lst = []
        moves = self.genmove(board)
        # bestmove = None
        for score, x, y in moves:
            board[x][y] = turn
            score_lst.append([score + self.board_message(board, turn), x, y])
            # print(x,y)
            board[x][y] = 3
        score_lst.sort(reverse=True)
        # print(score_lst[0][1], score_lst[0][2], score_lst[0][0], score_lst[1][1], score_lst[1][2], score_lst[1][0])
        return score_lst[0][1], score_lst[0][2]

    def board_message(self, board, turn):
        white_type = {'LIVE_FIVE': 0, 'LIVE_FOUR': 0, 'CHONG_FOUR': 0, 'LIVE_THREE': 0,
                      'SLEEP_THREE': 0, 'LIVE_TWO': 0, 'SLEEP_TWO': 0, 'None': 0}
        black_type = {'LIVE_FIVE': 0, 'LIVE_FOUR': 0, 'CHONG_FOUR': 0, 'LIVE_THREE': 0,
                      'SLEEP_THREE': 0, 'LIVE_TWO': 0, 'SLEEP_TWO': 0, 'None': 0}
        for line1 in self.get_line1(board=board):
            self.analy_line(line=line1, white_type_num=white_type, black_type_num=black_type)
        for line2 in self.get_line2(board=board):
            self.analy_line(line=line2, white_type_num=white_type, black_type_num=black_type)
        for line3 in self.get_line3(board=board):
            self.analy_line(line=line3, white_type_num=white_type, black_type_num=black_type)
        for line4 in self.get_line4(board=board):
            self.analy_line(line=line4, white_type_num=white_type, black_type_num=black_type)
        if turn == 1:
            x = self.get_score(my=white_type, oppo=black_type)
            # print(white_type, black_type)
            # print(x[0],x[1])
            return x[0] - x[1]
        else:
            x = self.get_score(my=black_type, oppo=white_type)
            # print(white_type, black_type)
            return x[1] - x[0]

    def get_line1(self, board):
        """获得水平直线(一共15条)"""
        linelst = []

        for i in range(self.chess_len):
            line = ''
            for j in range(self.chess_len):
                line += str(board[i][j])
            linelst.append(line)

        return linelst

    def get_line2(self, board):
        """获得竖直直线(一共15条)"""
        linelst = []

        for i in range(self.chess_len):
            line = ''
            for j in range(self.chess_len):
                line += str(board[j][i])
            linelst.append(line)

        return linelst

    def get_line3(self, board):
        """获得左上到右下\的斜线(一共21条)"""
        linelst = []
        dir = [1, 1]
        for j in range(self.chess_len - 4):
            x, y = 0, j
            line = str(board[x][y])
            for _ in range(self.chess_len - j - 1):
                x += dir[0]
                y += dir[1]
                line += str(board[x][y])
            linelst.append(line)

        for i in range(1, self.chess_len - 4):
            x, y = i, 0
            line = str(board[x][y])
            for _ in range(self.chess_len - i - 1):
                x += dir[0]
                y += dir[1]
                line += str(board[x][y])
            linelst.append(line)

        return linelst

    def get_line4(self, board):
        """获得右上到左下'/'的斜线(一共21条)"""
        linelst = []
        dir = [1, -1]
        for j in range(4, self.chess_len):
            x, y = 0, j
            line = str(board[x][y])
            for _ in range(j):
                x += dir[0]
                y += dir[1]
                line += str(board[x][y])
            linelst.append(line)

        for i in range(1, self.chess_len - 4):
            x, y = i, self.chess_len - 1
            line = str(board[x][y])
            for _ in range(self.chess_len - i - 1):
                x += dir[0]
                y += dir[1]
                line += str(board[x][y])
            linelst.append(line)

        return linelst

    def analy_line(self, line, white_type_num, black_type_num):
        """统计每一条线上形成的棋形"""
        white_type_num['LIVE_FIVE'] += line.count('11111')
        black_type_num['LIVE_FIVE'] += line.count('00000')
        white_type_num['LIVE_FOUR'] += line.count('311113')
        black_type_num['LIVE_FOUR'] += line.count('300003')
        white_type_num['CHONG_FOUR'] = white_type_num['CHONG_FOUR'] + line.count('13111') + line.count(
            '11131') + line.count('11311') \
                                       + line.count('311110') + line.count('011113')
        black_type_num['CHONG_FOUR'] = black_type_num['CHONG_FOUR'] + line.count('03000') + line.count('00030') \
                                       + line.count('00300') + line.count('300001') + line.count('100003')
        white_type_num['LIVE_THREE'] = white_type_num['LIVE_THREE'] + line.count('311133') + line.count(
            '331113') + line.count('313113') + line.count('311313')
        black_type_num['LIVE_THREE'] = black_type_num['LIVE_THREE'] + line.count('300033') + line.count(
            '330003') + line.count('303003') + line.count('300303')
        white_type_num['SLEEP_THREE'] = white_type_num['SLEEP_THREE'] + line.count('0311130') + line.count(
            '013113') + line.count('313110') \
                                        + line.count('011313') + line.count('311310')
        black_type_num['SLEEP_THREE'] = black_type_num['SLEEP_THREE'] + line.count('1300031') + line.count(
            '103003') + line.count('303001') \
                                        + line.count('100303') + line.count('300301')
        white_type_num['LIVE_TWO'] = white_type_num['LIVE_TWO'] + line.count('3113') + line.count('31313') + line.count(
            '313313')
        black_type_num['LIVE_TWO'] = black_type_num['LIVE_TWO'] + line.count('3003') + line.count('30303') + line.count(
            '303303')
        white_type_num['SLEEP_TWO'] = white_type_num['SLEEP_TWO'] + line.count('0113') + line.count(
            '3110') + line.count('01313') + line.count('31310')
        black_type_num['SLEEP_TWO'] = black_type_num['SLEEP_TWO'] + line.count('1003') + line.count(
            '3001') + line.count('10303') + line.count('30301')

    def get_score(self, my, oppo):
        """统计传入的棋形数据并计算评分,返回ai得分,玩家得分"""
        mscore, oscore = 0, 0
        if my['LIVE_FIVE'] > 0:
            return (10000, 0)
        if oppo['LIVE_FIVE'] > 0:
            return (0, 10000)

        if my['CHONG_FOUR'] >= 2:
            my['LIVE_FOUR'] += 1

        if oppo['LIVE_FOUR'] > 0:
            return (0, 9050)
        if oppo['CHONG_FOUR'] > 0:
            return (0, 9040)

        if my['LIVE_FOUR'] > 0:
            return (9030, 0)
        if my['CHONG_FOUR'] > 0 and my['LIVE_THREE'] > 0:
            return (9020, 0)

        if oppo['LIVE_THREE'] > 0 and my['CHONG_FOUR'] == 0:
            return (0, 9010)

        if my['LIVE_THREE'] > 1 and oppo['LIVE_THREE'] == 0 and oppo['SLEEP_THREE'] == 0:
            return (9000, 0)

        if my['CHONG_FOUR'] > 0:
            mscore += 2000

        if my['LIVE_THREE'] > 1:
            mscore += 500
        elif my['LIVE_THREE'] > 0:
            mscore += 100

        if oppo['LIVE_THREE'] > 1:
            oscore += 2000
        elif oppo['LIVE_THREE'] > 0:
            oscore += 400

        if my['SLEEP_THREE'] > 0:
            mscore += my['SLEEP_THREE'] * 10
        if oppo['SLEEP_THREE'] > 0:
            oscore += oppo['SLEEP_THREE'] * 10

        if my['LIVE_TWO'] > 0:
            mscore += my['LIVE_TWO'] * 4
        if oppo['LIVE_TWO'] > 0:
            oscore += oppo['LIVE_TWO'] * 4

        if my['SLEEP_TWO'] > 0:
            mscore += my['SLEEP_TWO'] * 4
        if oppo['SLEEP_TWO'] > 0:
            oscore += oppo['SLEEP_TWO'] * 4
        # print(mscore,oscore)
        return (mscore, oscore)

    def alpha_beta(self, board, turn, depth, alpha, beta):
        # 如果深度小于等于0，直接返回
        if depth <= 0:
            score = self.min_max(board, turn)
            return score
        score = self.min_max(board, turn)
        # 产生必胜情况，直接返回
        if abs(score) >= 9999 and depth < self.max_depth:
            return score
        moves = self.genmove(board)
        bestmove = None
        for score, row, col in moves:
            board[row][col] = turn
            nturn = (turn + 1) % 2
            score = - self.alpha_beta(board, nturn, depth - 1, -beta, -alpha)
            board[row][col] = 3
            if score > alpha:
                alpha = score
                bestmove = (row, col)
                if alpha >= beta:
                    break
        # 保存得分最好的走法
        if depth == self.maxdepth and bestmove:
            self.move = bestmove
        return alpha

    def get_bestmove(self, board, turn, depth=4):
        self.max_depth = depth
        self.move = None
        score = self.alpha_beta(board, turn, depth=4, alpha=-0x7fffffff, beta=0x7fffffff)
        if abs(score) > 8000:
            self.maxdepth = depth
            score = self.alpha_beta(board, turn, depth=4, alpha=-0x7fffffff, beta=0x7fffffff)
        return self.move[0], self.move[1]
