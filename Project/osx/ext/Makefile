.PHONY: all clean
.PHONY: liblua libluabind libutf8
.PHONY: cleanlua cleanluabind cleanutf8

BOOST_ROOT:=/usr/local
LUA_VER:=5.1.5
LUA_ARC:=lua-$(LUA_VER).tar.gz
LUA_SRC:=lua-$(LUA_VER)
LUA_DST:=lua
LUABIND_VER:=0.9.1
LUABIND_ARC:=luabind-$(LUABIND_VER).tar.gz
LUABIND_SRC:=luabind-$(LUABIND_VER)
LUABIND_DST:=luabind
UTF8CPP_VER:=2.3.2
UTF8CPP_ARC:=utf8_v$(subst .,_,$(UTF8CPP_VER)).zip
UTF8CPP_DST:=utf8

all: liblua libluabind libutf8

liblua: lua/lib/liblua.a
libluabind: luabind/lib/libluabindd.a
libutf8: utf8/source/utf8.h

$(LUA_ARC):
	wget 'http://www.lua.org/ftp/lua-$(LUA_VER).tar.gz'

$(LUA_SRC): $(LUA_ARC)
	tar xzf $<
	touch $@

lua/lib/liblua.a: $(LUA_SRC)
	$(MAKE) -C $(LUA_SRC) PLAT=macosx INSTALL_TOP=$(shell pwd)/$(LUA_DST)
	$(MAKE) -C $(LUA_SRC) PLAT=macosx INSTALL_TOP=$(shell pwd)/$(LUA_DST) install

$(LUABIND_ARC):
	wget --trust-server-names 'http://sourceforge.net/projects/luabind/files/luabind/$(LUABIND_VER)/luabind-$(LUABIND_VER).tar.gz/download'

$(LUABIND_SRC): $(LUABIND_ARC)
	tar xzf $<
	(cd $@; patch -p0 < ../luabind.patch)

luabind/lib/libluabindd.a: $(LUABIND_SRC)
	(cd $<; LUA_PATH=$(shell pwd)/$(LUA_DST) bjam --prefix=$(shell pwd)/$(LUABIND_DST) link=static install)

$(UTF8CPP_ARC):
	wget --trust-server-names 'http://sourceforge.net/projects/utfcpp/files/utf8cpp_2x/Release%20$(UTF8CPP_VER)/utf8_v$(subst .,_,$(UTF8CPP_VER)).zip/download'

$(UTF8CPP_DST): $(UTF8CPP_ARC)
	mkdir $@
	
utf8/source/utf8.h: $(UTF8CPP_DST)
	(cd $<; unzip -x ../$(UTF8CPP_ARC))
	touch $@

cleanlua:
	rm -rf $(LUA_ARC) $(LUA_SRC) $(LUA_DST)

cleanluabind:
	rm -rf $(LUABIND_ARC) $(LUABIND_SRC) $(LUABIND_DST)

cleanutf8:
	rm -rf $(UTF8CPP_ARC) $(UTF8CPP_DST)

clean: cleanlua cleanluabind cleanutf8
