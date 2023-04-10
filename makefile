#============================================================

# 各項目を設定してください

# ソースファイルの場所 ($make steps コマンドで，ヘッダファイルの行数もカウントする場合は，
# ヘッダファイルのディレクトリも追加する必要があります．また，拡張子を記述してはいけません)
# 例: SRCDIR = *. source/*. source/SubDir1/*.
DIR = *. src/*. src/fw/*. src/fw/fsm/*. src/fw/time/*. src/ConcreteState/*. src/fw/logger/*. src/InitialState/*. src/MissionState/*. src/magic_enum/*.

# 生成ファイル名
TARGET = exe
# 親ディレクトリ名にする場合
# TARGET = $(shell basename `readlink -f .`).exe

# コンパイルオプション
# 例: CFLAGS += -L/home/usr/lib -I/home/usr/include
# 例: CFLAGS += -lssl -lcrypto # OpenSSL
# 例: CFLAGS += -pthread       # thread
# 例: CFLAGS += -std=gnu++0x   # C++11
CFLAGS  = -g -Wall -W -Wextra -Wunused-function -Wunused-parameter -Wunused-variable -Isrc/ -Isrc/fw
CFLAGS += -O3 -std=c++17
#CFLAGS += -std=c++17

#============================================================

SRCDIR   = $(patsubst %., %.cpp, $(DIR))
SRCS     = $(wildcard $(SRCDIR))

HDIR     = $(patsubst %., %.h, $(DIR))
HEADS    = $(wildcard $(HDIR))

HPPDIR   = $(patsubst %., %.hpp, $(DIR))
HEADppS  = $(wildcard $(HPPDIR))

TEMP_DIR = make_temp
OBJS     = $(addprefix $(TEMP_DIR)/, $(patsubst %.cpp, %.o, $(SRCS)))
#OBJS     = $(addprefix $(TEMP_DIR)/, $(SRCS:%.cpp=%.o))#別表記

DEPS  = $(addprefix $(TEMP_DIR)/, $(patsubst %.cpp, %.d, $(SRCS)))
#DEPS  = $(addprefix $(TEMP_DIR)/, $(SRCS:%.cpp=%.d))#別表記


# exe ファイルの生成
$(TARGET): $(OBJS)
	@echo ""
	@echo "============================================================"
	@echo ""

	@echo "SRCS: "
	@echo "$(SRCS)"
	@echo ""

	@echo "OBJS: "
	@echo "$(OBJS)"
	@echo ""

	@echo "CFLAGS: "
	@echo "$(CFLAGS)"
	@echo ""
	@echo "============================================================"
	@echo ""
	$(CXX) -o $(TARGET) $(OBJS) $(CFLAGS)
	@echo ""


# 各ファイルの分割コンパイル
$(TEMP_DIR)/%.o: %.cpp
	@echo ""
	mkdir -p $(dir $@);\
	$(CXX) $< -c -o $@ $(CFLAGS)


# 「-include $(DEPS)」により，必要な部分のみ分割で再コンパイルを行うため，依存関係を記した *.d ファイルに生成する
$(TEMP_DIR)/%.d: %.cpp
	@echo ""
	mkdir -p $(dir $@);\
	$(CXX) $< -MM $(CFLAGS)\
	| sed 's/$(notdir $*)\.o/$(subst /,\/,$(patsubst %.d,%.o,$@) $@)/' > $@;\
	[ -s $@ ] || rm -f $@
#   @echo $*    # for debug
#   @echo $@    # for debug


.PHONY: all
all:
	@(make clean)
	@(make)
#   make clean ; \  #別表記
#   make            #別表記


.PHONY: clean
clean:
	-rm -rf $(TEMP_DIR) $(TARGET)
#   -rm -f $(OBJS) $(DEPS) $(TARGET)


.PHONY: onece
onece:
	$(CXX) -o $(TARGET) $(SRCS) $(CFLAGS)


.PHONY: steps
steps: $(SRCS) $(HEADS) $(HEADppS)
	@echo "$^" | xargs wc -l


#動作未確認[12]
.PHONY: steps2
steps2: $(SRCS) $(HEADS) $(HEADppS)
	@echo "$^" | xargs grep -Ev '^[[:space:]]*((/?\*.*/?)|(//.*))$' | wc -l


-include $(DEPS)