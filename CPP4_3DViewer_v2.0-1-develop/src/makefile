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

#      ██╗ ██████╗  █████╗ ███╗   ██╗███╗   ██╗███████╗██████╗ ███████╗
#      ██║██╔═══██╗██╔══██╗████╗  ██║████╗  ██║██╔════╝██╔══██╗██╔════╝
#      ██║██║   ██║███████║██╔██╗ ██║██╔██╗ ██║█████╗  ██║  ██║█████╗  
# ██   ██║██║   ██║██╔══██║██║╚██╗██║██║╚██╗██║██╔══╝  ██║  ██║██╔══╝  
# ╚█████╔╝╚██████╔╝██║  ██║██║ ╚████║██║ ╚████║███████╗██████╔╝███████╗
#  ╚════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═══╝╚══════╝╚═════╝ ╚══════╝

.PHONY: all library debug deep_debug valgrind_debug test valgrind_test gcov_report clang_n clang_i clean

PROJECT_NAME := 3DViewer_v2

#* BUILD
CMAKE_GENERATOR := Unix Makefiles
CMAKE_COMPILATOR := -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
BUILD_RELEASE_DIR := build/Release
BUILD_DEBUG_DIR := build/Debug
# CMAKE_BUILD_DEBUG := cmake -B ${BUILD_DIR} --preset conan-release -DCMAKE_BUILD_TYPE=Release
CMAKE_BUILD_RELEASE := cmake -B ${BUILD_RELEASE_DIR} -DCMAKE_BUILD_TYPE=Release
CMAKE_BUILD_RELEASE_TARGET := cmake --build ${BUILD_RELEASE_DIR} --target
# CMAKE_BUILD_DEBUG := cmake -B ${BUILD_DIR} --preset conan-debug -DCMAKE_BUILD_TYPE=Debug
CMAKE_BUILD_DEBUG := cmake -B ${BUILD_DEBUG_DIR} -DCMAKE_BUILD_TYPE=Debug
CMAKE_BUILD_DEBUG_TARGET := cmake --build ${BUILD_DEBUG_DIR} --target



#* TARGET
RELEASE_TARGET := ${PROJECT_NAME}
RELEASE_EXE := ./${BUILD_RELEASE_DIR}/${RELEASE_TARGET}

DEBUG_TARGET := ${PROJECT_NAME}
DEBUG_EXE := ./${BUILD_DEBUG_DIR}/${DEBUG_TARGET}

TEST_TARGET := test
TEST_DIR := ${BUILD_DEBUG_DIR}
TEST_EXE := ./${TEST_DIR}/test/${TEST_TARGET}


#* INSTALL 
INSTALL_DIR := ~/${PROJECT_NAME}
INSTALL_FILES := ${BUILD_RELEASE_DIR}/${PROJECT_NAME} ${BUILD_RELEASE_DIR}/*.so


#* TEST
TRF ?= default
CMAKE_TEST_RUN := ctest --rerun-failed --output-on-failure --test-dir ${TEST_DIR} 


#* VALGRIND
# --track-fds=yes
FLAG_VALGRIND := --trace-children=yes --tool=memcheck --leak-check=yes  --track-origins=yes -s


#* LCOV 
gcda_dirs=$(shell find .  -type f -name "*.gcda" -exec dirname {} \; | sort | uniq)
lcov_dirs=$(shell for dir in $(gcda_dirs); do echo --directory $$dir; done | tr '\n' ' ')
COVERAGE_INFO := coverage.info
COVERAGE_REPORT := coverage_report


#* CLANG
FIND_DIR := .
FIND := find $(FIND_DIR) -regextype posix-extended -regex ".*\.(cpp|c|cc|h|hpp|inl)$$"
CLANG := clang-format -style=Google


all: ${PROJECT_NAME}

install: build 
	${CMAKE_BUILD_RELEASE_TARGET} ${RELEASE_TARGET}
	mkdir -p ${INSTALL_DIR}
#* конструкция "2>/dev/null || true" копирует только те файлы которые существуют
	cp ${INSTALL_FILES} ${INSTALL_DIR} 2>/dev/null || true
#	mkdir -p ${INSTALL_DIR}/generators/
#	cp ${BUILD_DIR}/generators/qt.conf ${INSTALL_DIR}/generators
	echo "Game installed"

uninstall:
	rm -rf ${INSTALL_DIR}

dist:
	make install INSTALL_DIR="dist/${PROJECT_NAME}"
	tar cf ${PROJECT_NAME}.tar -C dist .

dvi:
	doxygen

build:
	${CMAKE_BUILD_RELEASE}

build_debug:
	${CMAKE_BUILD_DEBUG}

${PROJECT_NAME}: build
	${CMAKE_BUILD_RELEASE_TARGET} ${RELEASE_TARGET}
	${RELEASE_EXE}

debug: build_debug
	${CMAKE_BUILD_DEBUG_TARGET} ${DEBUG_TARGET}
	${DEBUG_EXE}

debug_build: 
	${CMAKE_BUILD_DEBUG_TARGET} ${DEBUG_TARGET}
	${DEBUG_EXE}

valgrind_debug: build_debug
	${CMAKE_BUILD_DEBUG_TARGET} ${DEBUG_TARGET}
	valgrind $(FLAG_VALGRIND) ${DEBUG_EXE}

tests: build_debug
	rm -rf ${COVERAGE_REPORT} ${COVERAGE_INFO}
	${CMAKE_BUILD_DEBUG_TARGET} ${TEST_TARGET}
ifeq (${TRF}, default)
		${TEST_EXE}
else 
		${CMAKE_TEST_RUN}
endif

valgrind_test: build_debug
	${CMAKE_BUILD_DEBUG_TARGET} ${TEST_TARGET}
	valgrind $(FLAG_VALGRIND) ${TEST_EXE}

gcov_report: test
	lcov --gcov-tool gcov --capture ${lcov_dirs} --output-file ${COVERAGE_INFO} --base-directory . --no-external --rc lcov_branch_coverage=2 --include '*/src/*' --debug
	genhtml ${COVERAGE_INFO} --output-directory ${COVERAGE_REPORT}

clang_check:
	@${FIND} -exec ${CLANG} -n {} \;

clang_format:
	@${FIND} -exec ${CLANG} -i {} \;

clean:
	rm -rf build ${BUILD_DIR} ${COVERAGE_REPORT} ${COVERAGE_INFO} doxygen dist s21_BrickGame.tar include db.sqlite CMakeUserPresets.json

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
