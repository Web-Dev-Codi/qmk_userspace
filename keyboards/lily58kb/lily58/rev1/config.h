// SPDX-License-Identifier: GPL-2.0-or-later
// Modified by: Web-Dev-Codi (https://www.github.com/Web-Dev-Codi) 2025

#pragma once


#define USB_POLLING_INTERVAL_MS 10


#define SPLIT_USB_DETECT
#define RGB_MATRIX_SLEEP     // turn off effects when suspended
#define SPLIT_TRANSPORT_MIRROR             // If LED_MATRIX_KEYPRESSES or LED_MATRIX_KEYRELEASES is enabled, you also will want to enable SPLIT_TRANSPORT_MIRROR
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255  // limits maximum brightness of LEDs (max 255). Higher may cause the controller to crash.

#define AUTO_SHIFT_TIMEOUT 400
#define NO_AUTO_SHIFT_SPECIAL
#define AUTO_SHIFT_ALPHA KC_A ... KC_Z

#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLIGHT_SLEEP
