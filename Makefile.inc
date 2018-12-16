MRUBY_PATH := /Users/yuri/git/mruby-2.0.0

APPL_LIBS += $(MRUBY_PATH)/build/EV3RT/lib/libmruby.a -lm
INCLUDES += -I$(MRUBY_PATH)/include
