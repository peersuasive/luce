
VERSION = $(shell git describe)
OUT 	= distrib

TARGETS_ = Linux64/core.so \
		   Linux64-5.2/core.so \
		   Win32/core.dll \
		   Win32-5.2/core.dll \
		   MacOSX64/core.so \
		   iOS6.1/libcore.a \
		   Android4.4/libluce_jni.so

#MacOSX64-5.2/core.so \


TARGETS := $(foreach obj,$(TARGETS_),$(OUT)/$(VERSION)/$(obj))

all:
	echo "It's $$(date)"

distrib: $(TARGETS)

$(OUT)/$(VERSION)/Linux64/core.so: Linux
	@echo Building for Linux64
	@mkdir -p $(shell dirname $(@))
	@cd $< && make -j5 #&& make -j5 CONFIG=Debug
	@ln -f $</build/libluce.a $@
	@cd $(shell dirname $(@)) && zip -q -9 ../luce.$(VERSION).linux64-5.1.zip core.so

$(OUT)/$(VERSION)/Linux64-5.2/core.so: Linux-lua5.2
	@echo Building for Linux64-5.2
	@mkdir -p $(shell dirname $(@))
	@cd $< && make -j6 #&& make -j5 CONFIG=Debug
	@ln -f $</build/core.so $@
	@cd $(shell dirname $(@)) && zip -q -9 ../luce.$(VERSION).linux64-5.2.zip core.so

$(OUT)/$(VERSION)/Win32/core.dll: MingW
	@echo Building for Win32
	@mkdir -p $(shell dirname $(@))
	@cd $< && ./wrapper #&& ./wrapper debug
	@ln -f $</build/core.dll $@
	@cd $(shell dirname $(@)) && zip -q -9 ../luce.$(VERSION).win32-5.1.zip core.dll

$(OUT)/$(VERSION)/Win32-5.2/core.dll: MingW
	@echo Building for Win32
	@mkdir -p $(shell dirname $(@))
	@cd $< && ./wrapper-lua52 #&& ./wrapper-lua52 debug
	@ln -f $</build/core.dll $@
	@cd $(shell dirname $(@)) && zip -q -9 ../luce.$(VERSION).win32-5.2.zip core.dll

$(OUT)/$(VERSION)/MacOSX64/core.so: MacOSX-cross
	@echo Building for MacOSX64 $@
	@mkdir -p $(shell dirname $(@))
	@cd $< && ./wrapper-osx #&& ./wrapper-osx debug
	@ln -f $</build/core.so $@
	@cd $(shell dirname $(@)) && zip -q -9 ../luce.$(VERSION).osx64-5.1.zip core.so

$(OUT)/$(VERSION)/MacOSX64-5.2/core.so: MacOSX-cross
	@echo Building for MacOSX64 $@
	@mkdir -p $(shell dirname $(@))
	@cd $< && ./wrapper-osx-52 #&& ./wrapper-osx-52 debug
	@ln -f $</build/core.so $@
	@cd $(shell dirname $(@)) && zip -q -9 ../luce.$(VERSION).osx64-5.2.zip core.so

$(OUT)/$(VERSION)/iOS6.1/libcore.a: iOS
	@echo Building for iOS6.1
	@mkdir -p $(shell dirname $(@))
	@cd $< && ./xmake
	@ln -f $</build/intermediate/Release/libcore_ios.a $@
	@cd $(shell dirname $(@)) && zip -q -9 ../luce.$(VERSION).ios61.zip libcore.a

$(OUT)/$(VERSION)/Android4.4/libluce_jni.so: Android
	@echo Building for Android4.4
	@mkdir -p $(shell dirname $(@))
	@cd $< && ant release
	@ln -f $</libs/armeabi-v7a/libluce_jni.so $@
	@cd $(shell dirname $(@)) && zip -q -9 ../luce.$(VERSION).android44.zip libluce_jni.so


