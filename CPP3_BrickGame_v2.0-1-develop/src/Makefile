# Отче наш, иже еси на АйБиЭм ПиСи, код наш насущный дай нам!
# Помилуй нас от пэйпер джэма и фатал эрора! 
# Дай нам MD-ков неубываемых и паролей на них.
# Искупи нам десницей Своей комплектующих для Апгрейда ненасытного, ибо душит нас Жаба великая
# и страдаем мы от недостатка ресурсов системных. 
# Не допусти выполнения недопустимой операции и скрой сведения от очей наших.
# Не дай нам впасть во искушение новыми релизами, ибо лукав Нуралиев-искуситель сотоварищи. 
# Удержи нас грешных от эф-диска и формата. Да минуют нас бэд-блоки и вирусы. 
# Умерь гордыню нашу, ибо не зашарим и крохи малой ближнему своему.
# Избавь нас от Юзера глупого, ибо продвинут он стал и имя ему БУХ. 
# Выправи программы наши кривые, ибо клинит башни нам от конфигураторов и отладчиков Открой нам знание, ибо истинно говоришь Ты нам, где тру и фолс. 
# Откомментируй код наш многомегабайтный, ибо погрязли мы в MD-шниках своих

# Укроти ламеров, имя Твое всуе поминающих, ибо не ведают, что творят. Упаси нас от Галактик и Бэстов. Да приидет царствие одинэса. 
# Не заставь нас нырять в мануалы бездонные и хэлпы путанные, ибо ересь в них, а дай нам уразуметь ридмя крошечные,
# ибо в них слово Господне.

# Инкапсулируй объекты наши, ибо полиморфны они и наследуют Царствие Твое. Выведи нас из цикла бесконечного, 
# ибо на переход Твой безусловный уповаем. Укажи нам путь верный, ибо блуждаем мы средь интерфейсов и парадигм и несть им числа.
# Не пронеси мимо чашу сию неупиваемую, ибо пива
# жаждем мы и коннекта алкаем.

# Молим Тебя и ниц перед Тобой падаем со серверами нашими. Отныне и присно, энд лайфтайм, бэкап!


# ██████╗  ██████╗ ███████╗███████╗██╗   ██╗██████╗ ███████╗██████╗ 
# ██╔══██╗██╔═══██╗██╔════╝██╔════╝╚██╗ ██╔╝██╔══██╗██╔════╝██╔══██╗
# ██████╔╝██║   ██║███████╗█████╗   ╚████╔╝ ██████╔╝█████╗  ██████╔╝
# ██╔══██╗██║   ██║╚════██║██╔══╝    ╚██╔╝  ██╔═══╝ ██╔══╝  ██╔═══╝ 
# ██║  ██║╚██████╔╝███████║███████╗   ██║   ██║     ███████╗██║     
# ╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝   ╚═╝   ╚═╝     ╚══════╝╚═╝     



CC=g++
CFLAGS=-Wall -Wextra -Werror -g
DIR=build
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
CHECK = -lgtest -lsubunit -lm -lrt -lpthread 

# ifeq ($(shell uname), Linux)
#     LDFLAGS = -lm -lncurses  -lm -lrt -lpthread
# endif
# ifeq ($(shell uname), Darwin)
#     LDFLAGS = -lm -lncurses
# endif

all:
	make brickgame

brickgame:
	$(CC) $(CFLAGS) Game/main.cpp -lncurses -o brickgame && ./brickgame && rm -rf brickgame

snake_cli:
	$(CC) $(CFLAGS) -D CLI -D SNAKE Game/cli.cpp brick_game/snake/s21_snake.cpp -lncurses -o snake_cli && ./snake_cli && rm -rf snake_cli

tetris_cli:
	$(CC) $(CFLAGS) -D CLI -D TETRIS Game/cli.cpp brick_game/tetris/s21_tetris.cpp -lncurses -o tetris_cli && ./tetris_cli && rm -rf tetris_cli

tetris_desktop:
	mkdir -p build && cd build && cmake -DDESKTOP=ON -DTETRIS=ON .. && make && ./CC && cd .. && rm -rf build

snake_desktop:
	mkdir -p build && cd build && cmake -DDESKTOP=ON -DSNAKE=ON .. && make && ./CC && cd .. && rm -rf build


install:
	mkdir -p build
	make lib_snake.a


unistall:
	rm -rf build

dvi:
	cat KA.txt

clean:
	rm -rf report *.info  *.gcda *.gcno testing lib_snake.a testing.info lib_tetris.a

dist:
	mkdir -p res
	cp -a brick_game res
	cp -a gui res
	cp -a opisanie.txt res
	tar -czf Snake.tar.gz res
	rm -rf res	


format:
	clang-format -style=google -i */*/*.cpp */*.cpp

style:
	clang-format -style=google -n */*/*.cpp */*.cpp 

CXX = g++
CXFLAGS = -Wall -g  -fprofile-arcs -ftest-coverage
LDFLAGS = -L. -lsubunit -lgtest -lgtest_main -pthread


lib_snake.a:
	$(CXX) $(CXFLAGS) -D CLI -c brick_game/snake/s21_snake.cpp
	ar rc lib_snake.a *.o
	rm -rf *.o

lib_tetris.a:
	$(CXX) $(CXFLAGS) -D CLI -c brick_game/tetris/s21_tetris.cpp
	ar rc lib_tetris.a *.o
	rm -rf *.o

test: lib_snake.a lib_tetris.a
	$(CXX) $(CXFLAGS) test/*.cpp  -L. lib_snake.a -L. lib_tetris.a -lsubunit -lgtest -lgtest_main -pthread -o testing 

run_tests: test
	./testing

gcov_report: run_tests
	lcov -t "testing" -o testing.info -c -d . --ignore-errors mismatch
	genhtml -o report testing.info

# /**
#  *                             _ooOoo_
#  *                            o8888888o
#  *                            88" . "88
#  *                            (| -_- |)
#  *                            O\  =  /O
#  *                         ____/`---'\____
#  *                       .'  \\|     |//  `.
#  *                      /  \\|||  :  |||//  \
#  *                     /  _||||| -:- |||||-  \
#  *                     |   | \\\  -  /// |   |
#  *                     | \_|  ''\---/''  |   |
#  *                     \  .-\__  `-`  ___/-. /
#  *                   ___`. .'  /--.--\  `. . __
#  *                ."" '<  `.___\_<|>_/___.'  >'"".
#  *               | | :  `- \`.;`\ _ /`;.`/ - ` : | |
#  *               \  \ `-.   \_ __\ /__ _/   .-` /  /
#  *          ======`-.____`-.___\_____/___.-`____.-'======
#  *                             `=---='
#  *          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#  *                     佛祖保佑        永无BUG
#  *            佛曰:
#  *                   写字楼里写字间，写字间里程序员；
#  *                   程序人员写程序，又拿程序换酒钱。
#  *                   酒醒只在网上坐，酒醉还来网下眠；
#  *                   酒醉酒醒日复日，网上网下年复年。
#  *                   但愿老死电脑间，不愿鞠躬老板前；
#  *                   奔驰宝马贵者趣，公交自行程序员。
#  *                   别人笑我忒疯癫，我笑自己命太贱；
#  *                   不见满街漂亮妹，哪个归得程序员？
#  */
