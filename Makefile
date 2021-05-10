#CC := arm-bcm2708-linux-gnueabi-gcc
#CXX:= arm-bcm2708-linux-gnueabi-g++
#LINK := arm-bcm2708-linux-gnueabi-gcc
#AR := arm-bcm2708-linux-gnueabi-gcc-ar
#STRIP := arm-bcm2708-linux-gnueabi-strip

NAME := app

SRCDIR := .
SRC += $(wildcard $(SRCDIR)/*.c)

INCDIR =-I. \
	-I$(APIROOT)/include \
	-I$(APIROOT)/include/wiring

DYN_LINKS_WITH += -L$(APIROOT)/libs/ -lwiringPi

CFLAGS+= -Wall -fPIC -g

# c++文件后缀
CCSUFIX= cpp

# 删除命令
RM= rm -f

#debug or not
ifeq ($(DBG), y)
CFLAGS += -g
else
CFLAGS += -O2
endif

#print compile message or not
Q_ := @

ifeq ($(PRINT_COMPILER), y)
Q_ :=
endif

TARGET := $(NAME)

CFLAGS += $(INCDIR)

BINDIR += $(PWD)

####################################################################

OBJ += $(patsubst %.c,%.o,$(patsubst %.$(CCSUFIX),%.o,$(SRC))) 

BIN := $(BINDIR)/$(TARGET)

.PHONY:	all clean veryclean tags deps release $(DEPS_TARGET)

all:  deps  $(DEPS_TARGET) $(BIN) 

deps: .depend

.depend: $(SRC)
	@echo 'generating depend file ...'
	$(Q_)$(CC) -MM $(CPPFLAGS)  $^ 1>.depend

#重定义隐含规则
%.o: %.c
	@echo '<$(CC)>[$(DBG)] Compiling object file "$@" ...'
	$(Q_)${CC} $(CFLAGS) -c $< -o $@

%.o: %.$(CCSUFIX)
	@echo '<$(CXX)>[$(DBG)] Compiling object file "$@" ...'
	$(Q_)${CXX} $(CFLAGS) -c $< -o $@


clean:
	@echo remove all objects
	$(RM) $(OBJ) $(BIN) $(CLEAN_OBJ) .depend

veryclean:
	@echo remove all objects and deps
	$(RM) $(OBJ) $(BIN) $(CLEAN_OBJ)  .depend 

#rebuild
re: veryclean all

$(BIN): $(OBJ) 
	@echo '<$(CC)>creating binary "$(BIN)"'
	$(Q_)$(CC)  $(LINKFLAGS) $(OBJ) $(STATIC_LINKS_WITH) $(DYN_LINKS_WITH)  -o $(BIN) && chmod a+x $(BIN)
	@echo '... done'

