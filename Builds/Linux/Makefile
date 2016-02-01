# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

#CC  = gcc-4.9
#CXX = g++-4.9
#LD  = g++-4.9

AUDIO := 1
MP3 := 1

LUA_V :=

ifndef CONFIG
  CONFIG=Release
endif

ifeq ($(CONFIG),Release)
	OBJ_CONFIG := Release
else
	OBJ_CONFIG := Debug
endif
OUTDIR := build$(LUA_V)
OBJDIR := $(OUTDIR)/intermediate/$(OBJ_CONFIG)

ifeq ($(TARGET_ARCH),)
  TARGET_ARCH := -march=native
endif

CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.1" -D "JUCE_APP_VERSION_HEX=0x100" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -std=c++11 -I../../Luce -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0
ifeq ($(LUA_V),52)
	CFLAGS += -DLUA52 -I/usr/include/lua5.2
else
ifeq ($(LUA_V),53)
	CFLAGS += -DLUA53 -I/usr/include/lua5.3
else
	CFLAGS += -DLUA51 -I/usr/include/lua5.1
endif
endif

ifeq ($(CONFIG),Release)
	CPPFLAGS += -D "NDEBUG=1"
	TARGET := core.so
  ifeq ($(SMALL),1)
  	CFLAGS += -Os
  else
  	CFLAGS += -O3
  endif
else
	CPPFLAGS += -D "DEBUG=1" -D "_DEBUG=1" 
	CFLAGS += -g -ggdb -O0
	TARGET := core_d.so
endif
CFLAGS += -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
ifeq ($(AUDIO),1)
  CFLAGS  += -DLUCE_AUDIO=1
  ifeq ($(MP3),1)
  	CFLAGS += -DJUCE_USE_MP3AUDIOFORMAT
  endif
  LDFLAGS += -lasound
endif

CXXFLAGS += $(CFLAGS) -std=c++11
LDFLAGS += $(TARGET_ARCH) -L$(OUTDIR) -fvisibility=hidden -fvisibility-inlines-hidden
LDFLAGS += -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama
LDFLAGS += -ldl -lfreetype -lpthread -lrt

ifneq ($(NOCURL),1)
CPPFLAGS += -DJUCE_USE_CURL
LDFLAGS += -lcurl
endif

LDFLAGS += -std=c++11 -fPIC -shared
LDDEPS :=
RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.1" -D "JUCE_APP_VERSION_HEX=0x100" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)

OBJECTS := \
  $(OBJDIR)/juce_core_aff681cc.o \
  $(OBJDIR)/juce_data_structures_bdd6d488.o \
  $(OBJDIR)/juce_events_79b2840.o \
  $(OBJDIR)/juce_graphics_c8f1e7a4.o \
  $(OBJDIR)/juce_gui_basics_a630dd20.o \
  $(OBJDIR)/juce_gui_extra_7767d6a8.o \
  $(OBJDIR)/juce_opengl_c7e3506c.o \
  $(OBJDIR)/luce_core_4af9a860.o

OBJECTS += $(OBJDIR)/luce_3c70ee94.o
ifeq ($(AUDIO),1)
  OBJECTS += $(OBJDIR)/juce_audio_basics_2442e4ea.o \
  	$(OBJDIR)/juce_audio_devices_a4c8a728.o \
  	$(OBJDIR)/juce_audio_formats_d349f0c8.o \
  	$(OBJDIR)/juce_audio_processors_44a134a2.o \
  	$(OBJDIR)/juce_audio_utils_f63b12e8.o \
  	$(OBJDIR)/juce_video_184321c8.o \
  	$(OBJDIR)/luce_core_audio.o \
  	$(OBJDIR)/luce_audio.o
endif

OBJECTS += $(OBJDIR)/luce_main.o

.PHONY: clean

-include Makefile.static

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking luce
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning luce
	@$(CLEANCMD)

strip:
	@echo Stripping luce
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/luce_core_4af9a860.o: ../../Luce/modules/luce_core/luce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling luce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/luce_core_audio.o: ../../Luce/modules/luce_audio/luce_audio.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling luce_core_audio.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_2442e4ea.o: ../../JuceLibraryCode/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_a4c8a728.o: ../../JuceLibraryCode/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_d349f0c8.o: ../../JuceLibraryCode/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_44a134a2.o: ../../JuceLibraryCode/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_utils_f63b12e8.o: ../../JuceLibraryCode/modules/juce_audio_utils/juce_audio_utils.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_utils.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_video_184321c8.o: ../../JuceLibraryCode/modules/juce_video/juce_video.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_video.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/luce_audio.o: ../../Source/luce_audio.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling luce_audio.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/luce_3c70ee94.o: ../../Source/luce.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling luce.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/luce_main.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling luce_main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_aff681cc.o: ../../JuceLibraryCode/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_bdd6d488.o: ../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_79b2840.o: ../../JuceLibraryCode/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_c8f1e7a4.o: ../../JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_a630dd20.o: ../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_7767d6a8.o: ../../JuceLibraryCode/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_opengl_c7e3506c.o: ../../JuceLibraryCode/modules/juce_opengl/juce_opengl.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_opengl.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
