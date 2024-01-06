

def is_empty(board):
    for i in board:
        for k in i:
            if k != " ":
                return False
    return True


def is_bounded(board, y_end, x_end, length, d_y, d_x):

    x_start = x_end - ((length-1)*d_x)
    y_start = y_end - ((length-1)*d_y)
    left_bound = None
    right_bound = None
    if y_start - d_y >= -1 and x_start - d_x >= -1 and y_end + d_y <= len(board) and x_end + d_x <= len(board) and x_end + d_x >= 0 and y_end + d_y >= 0:
        if x_start == 0 or y_start == 0 or board[y_start - d_y][x_start - abs(d_x)]!= " ":
            left_bound = "yes"
        else:
            left_bound = "no"
        if x_end + d_x >= len(board) or y_end + d_y >= len(board) or board[y_end + d_y][x_end + d_x] != " ":
            right_bound = "yes"
        else:
            right_bound = "no"
        if left_bound == "yes" and right_bound == "yes":
            return "CLOSED"
        elif (left_bound == "no" and right_bound == "yes") or (left_bound == "yes" and right_bound == "no"):
            return "SEMIOPEN"
        elif left_bound == "no" and right_bound == "no":
            return "OPEN"



def detect_row(board, col, y_start, x_start, length, d_y, d_x):
    counter = 0
    open_seq_count = 0
    semi_open_seq_count = 0
    counter_length = 0

    if y_start > 0:
        counter = y_start
    elif x_start > 0:
        counter = x_start

    for i in range(0, len(board)-length+1):
        if counter + i < len(board) - 1 and board[y_start + d_y*i][x_start + d_x*i] == col:
            counter_length = 0
            while counter_length <= length and counter_length != 1000:
                for k in range(length):
                    if (y_start + d_y*i + d_y*k) < len(board) and (x_start + d_x*i + d_x*k) < len(board) and (y_start + d_y*i + d_y*k) >= 0 and (x_start + d_x*i + d_x*k) >= 0:
                        if counter_length == length:# MIGHT HAVE TO CHECK WHERE SEQUENCE IS LONGER THAN LENGTH
                            analyse_func = is_bounded(board, (y_start + d_y*i + d_y*k - 1), (x_start + d_x*i + d_x*k - 1), length, d_y, d_x)
        #maybe absolute value needed
                            if analyse_func == "OPEN":
                                open_seq_count += 1
                            elif analyse_func == "SEMIOPEN":
                                semi_open_seq_count += 1
                            counter_length = 1000
                            break
                        elif board[y_start + d_y*i + d_y*k][x_start + d_x*i + d_x*k] == col:
                            counter_length += 1
                        elif board[y_start + d_y*i + d_y*k][x_start + d_x*i + d_x*k] != col:
                            counter_length = length
                            break
                    else:
                        counter_length += 1


    return open_seq_count, semi_open_seq_count





# and ((x_start + d_x*i + d_x*k) < len(board) or (y_start + d_y*i + d_y*k) < len(board)):
# and ((x_start + d_x*i + d_x*k) < len(board) or (y_start + d_y*i + d_y*k) < len(board)):

def detect_rows(board, col, length):
    # if col == b:
    #     col = "b"
    # elif col == w:
    #     col = "w"
    open_seq_count, semi_open_seq_count = 0, 0

    for i in range(len(board)):
        if i == 0:
            s = detect_row(board, col, 0, i, length, 1, 0)
            open_seq_count += s[0]
            semi_open_seq_count += s[1]

            s = detect_row(board, col, 0, i, length, 0, 1)
            open_seq_count += s[0]
            semi_open_seq_count += s[1]

            s = detect_row(board, col, 0, i, length, 1, 1)
            open_seq_count += s[0]
            semi_open_seq_count += s[1]

            s = detect_row(board, col, 0, i, length, 1, -1)
            open_seq_count += s[0]
            semi_open_seq_count += s[1]

        else:
            s = detect_row(board, col, 0, i, length, 0, 1)
            open_seq_count += s[0]
            semi_open_seq_count += s[1]


            s = detect_row(board, col, 0, i, length, 1, 1)
            open_seq_count += s[0]
            semi_open_seq_count += s[1]

            s = detect_row(board, col, 0, i, length, 1, -1)
            open_seq_count += s[0]
            semi_open_seq_count += s[1]


    for k in range(1, len(board)):
        s = detect_row(board, col, k, 0, length, 1, 0)
        open_seq_count += s[0]
        semi_open_seq_count += s[1]

        s = detect_row(board, col, k, 0, length, 1, 1)
        open_seq_count += s[0]
        semi_open_seq_count += s[1]

        s = detect_row(board, col, k, 0, length, 1, -1)
        open_seq_count += s[0]
        semi_open_seq_count += s[1]

    return (open_seq_count, semi_open_seq_count)


def score(board):
    MAX_SCORE = 100000

    open_b = {}
    semi_open_b = {}
    open_w = {}
    semi_open_w = {}

    for i in range(2, 6):
        open_b[i], semi_open_b[i] = detect_rows(board, "b", i)
        open_w[i], semi_open_w[i] = detect_rows(board, "w", i)


    if open_b[5] >= 1 or semi_open_b[5] >= 1:
        return MAX_SCORE

    elif open_w[5] >= 1 or semi_open_w[5] >= 1:
        return -MAX_SCORE

    return (-10000 * (open_w[4] + semi_open_w[4])+
            500  * open_b[4]                     +
            50   * semi_open_b[4]                +
            -100  * open_w[3]                    +
            -30   * semi_open_w[3]               +
            50   * open_b[3]                     +
            10   * semi_open_b[3]                +
            open_b[2] + semi_open_b[2] - open_w[2] - semi_open_w[2])



# for range in y and range in x find the score of putting something there and then find the max score from that look at nov 16 lecture
def search_max(board):
    board_test = board
    i_max = 0
    k_max = 0
    max_score = 0
    for i in range(len(board)):
        for k in range(len(board)):
            board_test = board
            if board_test[i][k] == " ":
                board_test[i][k] == "b"
                score_t = score(board_test)
                if score_t > max_score:
                    max_score = score_t
                    i_max = i
                    k_max = k
    move_y = i_max
    move_x = k_max
    return move_y, move_x

def is_win(board):
    full = "maybe"
    for i in range(len(board)):
        for k in range(len(board)):
            if board[i][k] == " ":
                full = "not draw"

    if full == "maybe":
        return "Draw"
    s = detect_rows(board, "b", 5)
    if (s[0] or s[1]) > 0:
        return "Black won"
    s = detect_rows(board, "w", 5)
    if (s[0] or s[1]) > 0:
        return "White won"
    else:
        return "Continue playing"





def print_board(board):

    s = "*"
    for i in range(len(board[0])-1):
        s += str(i%10) + "|"
    s += str((len(board[0])-1)%10)
    s += "*\n"

    for i in range(len(board)):
        s += str(i%10)
        for j in range(len(board[0])-1):
            s += str(board[i][j]) + "|"
        s += str(board[i][len(board[0])-1])

        s += "*\n"
    s += (len(board[0])*2 + 1)*"*"

    print(s)


def make_empty_board(sz):
    board = []
    for i in range(sz):
        board.append([" "]*sz)
    return board



def analysis(board):
    for c, full_name in [["b", "Black"], ["w", "White"]]:
        print("%s stones" % (full_name))
        for i in range(2, 6):
            open, semi_open = detect_rows(board, c, i);
            print("Open rows of length %d: %d" % (i, open))
            print("Semi-open rows of length %d: %d" % (i, semi_open))






def play_gomoku(board_size):
    board = make_empty_board(board_size)
    board_height = len(board)
    board_width = len(board[0])

    while True:
        print_board(board)
        if is_empty(board):
            move_y = board_height // 2
            move_x = board_width // 2
        else:
            move_y, move_x = search_max(board)

        print("Computer move: (%d, %d)" % (move_y, move_x))
        board[move_y][move_x] = "b"
        print_board(board)
        analysis(board)

        game_res = is_win(board)
        if game_res in ["White won", "Black won", "Draw"]:
            return game_res





        print("Your move:")
        move_y = int(input("y coord: "))
        move_x = int(input("x coord: "))
        board[move_y][move_x] = "w"
        print_board(board)
        analysis(board)

        game_res = is_win(board)
        if game_res in ["White won", "Black won", "Draw"]:
            return game_res



def put_seq_on_board(board, y, x, d_y, d_x, length, col):
    for i in range(length):
        board[y][x] = col
        y += d_y
        x += d_x


def test_is_empty():
    board  = make_empty_board(8)
    if is_empty(board):
        print("TEST CASE for is_empty PASSED")
    else:
        print("TEST CASE for is_empty FAILED")

def test_is_bounded():
    board = make_empty_board(8)
    x = 5; y = 1; d_x = 0; d_y = 1; length = 3
    put_seq_on_board(board, y, x, d_y, d_x, length, "w")
    print_board(board)

    y_end = 3
    x_end = 5

    if is_bounded(board, y_end, x_end, length, d_y, d_x) == 'OPEN':
        print("TEST CASE for is_bounded PASSED")
    else:
        print("TEST CASE for is_bounded FAILED")


def test_detect_row():
    board = make_empty_board(8)
    x = 5; y = 1; d_x = 0; d_y = 1; length = 3
    put_seq_on_board(board, y, x, d_y, d_x, length, "w")
    print_board(board)
    if detect_row(board, "w", 0,x,length,d_y,d_x) == (1,0):
        print("TEST CASE for detect_row PASSED")
    else:
        print("TEST CASE for detect_row FAILED")

def test_detect_rows():
    board = make_empty_board(8)
    x = 5; y = 1; d_x = 0; d_y = 1; length = 3; col = 'w'
    put_seq_on_board(board, y, x, d_y, d_x, length, "w")
    print_board(board)
    if detect_rows(board, col,length) == (1,0):
        print("TEST CASE for detect_rows PASSED")
    else:
        print("TEST CASE for detect_rows FAILED")

def test_search_max():
    board = make_empty_board(8)
    x = 5; y = 0; d_x = 0; d_y = 1; length = 4; col = 'w'
    put_seq_on_board(board, y, x, d_y, d_x, length, col)
    x = 6; y = 0; d_x = 0; d_y = 1; length = 4; col = 'b'
    put_seq_on_board(board, y, x, d_y, d_x, length, col)
    print_board(board)
    if search_max(board) == (4,6):
        print("TEST CASE for search_max PASSED")
    else:
        print("TEST CASE for search_max FAILED")

def easy_testset_for_main_functions():
    test_is_empty()
    test_is_bounded()
    test_detect_row()
    test_detect_rows()
    test_search_max()

def some_tests():
    board = make_empty_board(8)

    board[0][5] = "w"
    board[0][6] = "b"
    y = 5; x = 2; d_x = 0; d_y = 1; length = 3
    put_seq_on_board(board, y, x, d_y, d_x, length, "w")
    print_board(board)
    analysis(board)

if __name__ == "__main__":


    board =[["b","b","b"," ","b","w","w","w"],
            [" ","w","b","b"," ","b"," ","b"],
            [" ","w","w"," ","b","w"," ","b"],
            ["w"," ","b","w"," "," "," ","b"],
            ["w","w","b","b","b"," ","w","b"],
            ["b"," ","w"," "," ","w"," ","w"],
            ["w"," ","b","b"," "," "," "," "],
            ["b","b","b"," "," "," "," "," "]]


    # print(is_bounded(board, 1, 3, 2, 0, 1))
    # detect_row(board, "b", 1, 0, 2, 0, 1)
    print(detect_rows(board, "b", 2))



    # is_bounded(board, 2, 1, 2, 0, 1)
    # detect_row(board, "b", 2, 0, 2, 0, 1)
