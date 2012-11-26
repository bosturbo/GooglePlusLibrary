.PHONY: all clean

CXX:=g++-4.7
SRC_DIR:=../../Src
OBJ_DIR:=.objs
CPPFILES:=$(shell grep -v ^\# cppfiles.txt)
ARFLAGS:=rc

LIB:=libgp.a
TARGET:=gptest
OBJS:=$(patsubst %cpp,$(OBJ_DIR)/%o,$(CPPFILES))

CPPFLAGS:=-std=c++11 -I../../Include -I../../Src -I../../Src/Utility -Iext/lua/include -Iext/luabind/include -Iext/utf8/source
ifeq ($(DEBUG_WITH_HEXDUMP),1)
	CPPFLAGS:=$(CPPFLAGS) -DDEBUG_WITH_HEXDUMP
endif
LDFLAGS:=-L. -Lext/luabind/lib -Lext/lua/lib
LDLIBS:=-lgp ext/luabind/lib/libluabindd.a -llua -lboost_system-mt -lboost_thread-mt -lboost_regex-mt -lboost_filesystem-mt -lboost_date_time-mt -lssl -lcrypto

all: $(TARGET)

lib: $(LIB)

$(LIB): $(OBJS)
	@echo AR
	@$(AR) $(ARFLAGS) $@ $^

$(TARGET).o: $(TARGET).cpp
	@echo CC $@
	@$(CXX) $(CPPFLAGS) -c $< -o $@

$(TARGET): $(TARGET).o $(LIB)
	@echo LD $@
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) $(TARGET).o -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo CC $<
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TARGET).o $(LIB)
