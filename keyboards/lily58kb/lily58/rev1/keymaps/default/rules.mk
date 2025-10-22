# # Configuration settings for Lily58KB with RP2040 MCU
WS2812_DRIVER = vendor
SERIAL_DRIVER = vendor

# # Split keyboard settings
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
# NKRO_ENABLE = yes            # Enable NKRO
SPLIT_KEYBOARD = yes        # Split keyboard support
AUTO_SHIFT_ENABLE = yes
# SPLIT_WATCHDOG_ENABLE=yes
# SPLIT_WATCHDOG_TIMEOUT=2000
AUTOCORRECT_ENABLE = yes
# BOARD = GENERIC_RP_RP2040

# # Define correct I2C pins for RP2040
# I2C1_SDA_PIN = GP2
# I2C1_SCL_PIN = GP3

# OPT_DEFS += -DHAL_USE_I2C=TRUE
