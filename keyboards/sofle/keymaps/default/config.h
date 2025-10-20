// Copyright 2024 Santosh Kumar (@santosh)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#define SPLIT_USB_DETECT

#define RGB_MATRIX_SLEEP     // turn off effects when suspended
#define SPLIT_TRANSPORT_MIRROR             // If LED_MATRIX_KEYPRESSES or LED_MATRIX_KEYRELEASES is enabled, you also will want to enable SPLIT_TRANSPORT_MIRROR
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255  // limits maximum brightness of LEDs (max 255). Higher may cause the controller to crash.
#define AUTO_SHIFT_TIMEOUT 400
#define NO_AUTO_SHIFT_SPECIAL
#define AUTO_SHIFT_ALPHA KC_A ... KC_Z
#define TRI_LAYER_LOWER_LAYER 2
#define TRI_LAYER_UPPER_LAYER 3
#define TRI_LAYER_ADJUST_LAYER 4
