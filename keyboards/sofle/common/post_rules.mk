ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += keyboards/sofle/common/display_oled.c
endif
