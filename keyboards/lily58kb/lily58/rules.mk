WS2812_DRIVER = vendor
SERIAL_DRIVER = vendor
# Bootloader selection
BOOTLOADER = rp2040

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = yes         # Commands for debug and configuration
NKRO_ENABLE = yes           # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
SPLIT_KEYBOARD = yes        # Split keyboard support
SPLIT_WATCHDOG_ENABLE=yes
SPLIT_WATCHDOG_TIMEOUT=2000
UART_DRIVER_REQUIRED = no
BOARD = GENERIC_RP_RP2040

I2C_DRIVER_REQUIRED = yes
