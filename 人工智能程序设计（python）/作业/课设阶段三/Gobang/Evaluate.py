class Evaluate:
    def __init__(self, board):
        self.board = board
        self.chess_len = len(self.board)
        self.white_type_num = {'LIVE_FIVE': 0, 'LIVE_FOUR': 0, 'CHONG_FOUR': 0, 'LIVE_THREE': 0,
                               'SLEEP_THREE': 0, 'LIVE_TWO ': 0, 'SLEEP_TWO': 0, 'None': 0}
        self.black_type_num = {'LIVE_FIVE': 0, 'LIVE_FOUR': 0, 'CHONG_FOUR': 0, 'LIVE_THREE': 0,
                               'SLEEP_THREE': 0, 'LIVE_TWO ': 0, 'SLEEP_TWO': 0, 'None': 0}



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
        white_type_num['CHONG_FOUR'] = white_type_num['CHONG_FOUR'] + line.count('13111') + line.count('11131') + line.count('11311') \
                                       + line.count('311110') + line.count('011113')
        black_type_num['CHONG_FOUR'] = black_type_num['CHONG_FOUR'] + line.count('03000') + line.count('00030') \
                                       + line.count('00300') + line.count('300001') + line.count('100003')
        white_type_num['LIVE_THREE'] = white_type_num['LIVE_THREE'] + line.count('311133') + line.count('331113') + line.count('313113') + line.count('311313')
        black_type_num['LIVE_THREE'] = black_type_num['LIVE_THREE'] + line.count('300033') + line.count('330003') + line.count('303003') + line.count('300303')
        white_type_num['SLEEP_THREE'] = white_type_num['SLEEP_THREE']  + line.count('0311130') + line.count('013113') + line.count('313110') \
                                        + line.count('011313') + line.count('311310')
        black_type_num['SLEEP_THREE'] = black_type_num['SLEEP_THREE'] + line.count('1300031') + line.count('103003') + line.count('303001') \
                                        + line.count('100303') + line.count('300301')
        white_type_num['LIVE_TWO'] = white_type_num['LIVE_TWO'] + line.count('3113') + line.count('31313') + line.count('313313')
        black_type_num['LIVE_TWO'] = black_type_num['LIVE_TWO'] + line.count('3003') + line.count('30303') + line.count('303303')
        white_type_num['SLEEP_TWO'] = white_type_num['SLEEP_TWO'] + line.count('0113') + line.count('3110')+ line.count('01313') + line.count('31310')
        black_type_num['SLEEP_TWO'] = black_type_num['SLEEP_TWO'] + line.count('1003') + line.count('3001') + line.count('10303') + line.count('30301')


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

