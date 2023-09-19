# 定义编译器
CC = gcc

# 定义编译选项
CFLAGS = -Wall -Wextra -fPIC

# 定义链接选项
LDFLAGS = -shared

# 定义源文件目录
SRCDIRS = chips src gpioc

# 找到所有的.c源文件，但跳过文件名中带有_py的文件
SRCS = $(shell find $(SRCDIRS) -name "*.c" ! -name "*_py*")

# 将.c源文件转换为.o目标文件
OBJS = $(SRCS:.c=.o)

# 定义输出库文件名
STATIC_LIBNAME = libproject.a
DYNAMIC_LIBNAME = libproject.so

# 定义库文件的安装路径
LIB_INSTALL_PATH = /lib

all: $(STATIC_LIBNAME) $(DYNAMIC_LIBNAME)

$(STATIC_LIBNAME): $(OBJS)
	ar rcs $@ $^
	ranlib $@

$(DYNAMIC_LIBNAME): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

install: all
	cp $(STATIC_LIBNAME) $(DYNAMIC_LIBNAME) $(LIB_INSTALL_PATH)

clean:
	rm -f $(OBJS) $(STATIC_LIBNAME) $(DYNAMIC_LIBNAME)

.PHONY: all install clean
