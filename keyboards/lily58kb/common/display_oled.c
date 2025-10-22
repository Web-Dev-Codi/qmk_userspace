// Copyright 2025 Dasky (@daskygit)
// Copyright 2025 Web-Dev-Codi (https://github.com/web-dev-codi)
// SPDX-License-Identifier: GPL-2.0-or-later
// Modified code from 2025 Dasky (@daskygit) keyboards/mechboards/lily58/pro/display_oled.c

/*
 * This file is part of QMK.
 *
 * QMK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * QMK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QMK.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "timer.h"

static uint16_t current_keycode = 0xFF;

enum layers {
    _QWERTZ,
    _LOWER,
    _RAISE,
    _ADJUST,
};

static const char *depad_str(const char *depad_str, char depad_char) {
    while (*depad_str == depad_char)
        ++depad_str;
    return depad_str;
}

static void render_spacer(uint8_t char_length) {
    static const char PROGMEM spacer_char[] = {8, 8, 8, 8, 8, 8, 8};
    if (char_length > 5) {
        char_length = 5;
    }
    for (uint8_t i = 0; i < char_length; i++) {
        oled_write_raw_P(spacer_char, sizeof(spacer_char));
        oled_advance_char();
    }
}

static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0, 64,192, 64, 64,192,128,128,128,  0,  0,128,224,112, 60, 14,  6, 14, 60,112,224,128,  0,  0,192,192,  0,192,192,  0,192,192,  0,  0,  0,  0,  0,  0,  0,192,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,128,  0,  0,  0,128,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,192,192,192,192,192,192,192,192,128,  0,  0,  0,  0,  0,  0,128,128,192,192,192,192,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0, 63,252,192,128,128,128,129,131,131,  7,  7, 12, 24,112,224,128,  0,  0,  1,255,252,128,182,182,128,176,176,  0, 54, 54,  0,  0,  0,  0,  0,  0,  0,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,240,241,  0,  0,  0,  0,255,255,  0,  0,  0, 48,240,240,128,  0,  0,  0,  0,  0,128,240,240, 48,  0,  0,127,255,255,225,113,113,241,241,225,193,129,  0,  0,  0,  0, 12, 63,255,243,225,193,193,129,129,195,255,127, 28,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        32,112,120,220,204,134,  6,  3,  3,  1,  1,  1,  1,  1,  1,  1,  1,  3,  2,  6,132,225,251, 56, 28, 12,  2,  1,  1,  1,  1,  1,  1,  1,  3,  3,  6,134,204,220,120,112, 32,  0,255,255,128,128,128,128,128,128,128,128,128,  0,  0,255,255,  0,  0,  0,  0,255,255,128,  0,  0,  0,  0,  3, 31,126,248,224,240,126, 31,  3,  0,  0,  0,  0,224,224,192,192,128,128,128,192,225,255,127, 63,  0,  0,  0, 62,255,255,193,192,128,129,129,195,195,255,254, 60,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  1,  1,  3,  3,  6,  6,  6,  4,  4,  4,  4,  6,  6,  2,  3,  1,  1,  0,  1,  1,  3,  2,  6,  6,  4,  4,  4,  4,  6,  6,  6,  3,  3,  1,  1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  1,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0, 96, 96,112, 56, 31, 15,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static void render_lily58_logo(void) {
    static const char PROGMEM lily58_logo[] = {
       0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
    0
    };
     oled_write_P(lily58_logo, false);
  oled_write_P(PSTR("---------------RP2040"), false);
}


oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return OLED_ROTATION_0;
}

char basic_codes_to_name[57] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/'};

const char *keycode_string(uint16_t keycode) {
    char       *keycode_str;
    static char key;
    switch (keycode) {
        case 0 ... 56:
            key = pgm_read_byte(&basic_codes_to_name[keycode]);
            return &key;
        case KC_CAPS:
            keycode_str = "Caps\0";
            break;
        case KC_SCRL:
            keycode_str = "Scrl\0";
            break;
        case KC_PAUS:
            keycode_str = "Pause\0";
            break;
        case KC_DEL:
            keycode_str = "Del\0";
            break;
        case KC_NUM:
            keycode_str = "Num\0";
            break;
        case KC_MUTE:
            keycode_str = "Mute\0";
            break;
        case KC_VOLU:
            keycode_str = "VolUp\0";
            break;
        case KC_VOLD:
            keycode_str = "VolD\0";
            break;
        case KC_MNXT:
            keycode_str = "Next\0";
            break;
        case KC_MPRV:
            keycode_str = "Prev\0";
            break;
        case KC_MSTP:
            keycode_str = "Stop\0";
            break;
        case KC_MPLY:
            keycode_str = "Play\0";
            break;
        case QK_MODS ... QK_MODS_MAX:
            keycode_str = "MOD()\0";
            break;
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            keycode_str = "MT()\0";
            break;
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            keycode_str = "LT()\0";
            break;
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
            keycode_str = "LM()\0";
            break;
        case QK_TO ... QK_TO_MAX:
            keycode_str = "TO()\0";
            break;
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            keycode_str = "MO()\0";
            break;
        case QK_PROGRAMMABLE_BUTTON ... QK_PROGRAMMABLE_BUTTON_MAX:
            keycode_str = "Prog\0";
            break;
        case QK_AUDIO ... QK_AUDIO_MAX:
            keycode_str = "Audio\0";
            break;
        case QK_STENO ... QK_STENO_MAX:
            keycode_str = "Steno\0";
            break;
        case QK_MACRO ... QK_MACRO_MAX:
            keycode_str = "Macro\0";
            break;
        case QK_CONNECTION ... QK_CONNECTION_MAX:
            keycode_str = "Conn\0";
            break;
        case QK_LIGHTING ... QK_LIGHTING_MAX:
            keycode_str = "Light\0";
            break;
        default:
            keycode_str = "Undef\0";
            break;
    }

    return keycode_str;
}

const char *layer_string(uint32_t layer) {
    char *layer_str;
    switch (layer) {
        case 0:
            layer_str = "QWRTZ\0";
            break;
        case 1:
            layer_str = "LOWER\0";
            break;
        case 2:
            layer_str = "RAISE\0";
            break;
        case 3:
            layer_str = "ADJST\0";
            break;
        default:
            return get_u16_str(layer, ' ');
    }

    return layer_str;
}

bool process_detected_host_os_kb(os_variant_t detected_os) {
    static const char PROGMEM tux_logo[] = {
        153,154,10,
        185,186,0
    };

    static const char PROGMEM win_logo[] = {
        151,152,10,
        183,184,0
    };

    static const char PROGMEM apple_logo[] = {
        149,150,10,
        181,182,0
    };

    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }

    oled_set_cursor(0, 10);
    switch (detected_os) {
        case OS_MACOS:
            oled_write_P(apple_logo, false);
            break;
        case OS_IOS:
            oled_write_P(apple_logo, false);
            break;
        case OS_WINDOWS:
            oled_write_P(win_logo, false);
            break;
        case OS_LINUX:
            oled_write_P(tux_logo, false);
            break;
        case OS_UNSURE:
            oled_write_ln("Unkno", false);
            break;
    }

    return true;
}

void keyboard_pre_task_kb(void) {
    // Check for power state changes that might cause phantom keypresses
    static uint16_t power_state_timer = 0;
    static bool power_state_checked = false;

    // During power state transitions (like shutdown), USB communication becomes unstable
    // This can cause phantom keypresses, especially on RP2040 controllers
    if (!power_state_checked) {
        power_state_timer = timer_read();
        power_state_checked = true;
    } else if (timer_elapsed(power_state_timer) > 1000) {
        // Reset the matrix state periodically to prevent phantom keypresses
        // This is especially helpful during shutdown sequences
        clear_keyboard();
        power_state_timer = timer_read();
    }
}

void keyboard_post_init_kb(void) {
    if (!is_keyboard_master()) {
        render_logo();
    } else {
        oled_set_cursor(0, 0);
        oled_write("Layer", false);
        render_spacer(5);
        oled_write_ln(layer_string(get_highest_layer(layer_state)), false);

        oled_set_cursor(0, 4);
        oled_write_ln("Key", false);
        render_spacer(3);
        oled_advance_page(false);
        oled_write_ln("None", false);

        oled_set_cursor(0, 8);
        oled_write_ln("OS", false);
        render_spacer(2);
        oled_advance_page(false);
        oled_write_ln("Wait", false);

        oled_set_cursor(0, 12);
        oled_write_ln("WPM", false);
        render_spacer(3);
        oled_advance_page(false);
        oled_write_ln(depad_str(get_u16_str(get_current_wpm(), ' '), ' '), false);
    }
    keyboard_post_init_user();
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    oled_set_cursor(0, 2);
    oled_write_ln(layer_string(get_highest_layer(state)), false);
    return state;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    current_keycode = keycode;
    return process_record_user(keycode, record);
};

void housekeeping_task_kb(void) {
    if (is_oled_on() && last_input_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
    }
}

void oled_reinit_slave(void) {
    oled_init(OLED_ROTATION_270);
    oled_clear();
    oled_set_cursor(0, 0);
    render_lily58_logo();
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    static uint16_t last_keycode         = 0xFF;
    static bool     oled_slave_init_done = false;

    if (is_keyboard_master()) {
        if (last_keycode != current_keycode) {
            oled_set_cursor(0, 6);
            if (current_keycode < ARRAY_SIZE(basic_codes_to_name)) {
                oled_write_char(basic_codes_to_name[current_keycode], false);
                oled_advance_page(true);
            } else {
                oled_write_ln(keycode_string(current_keycode), false);
            }
            last_keycode = current_keycode;
        }

        // Add WPM display on master OLED
        static uint16_t last_wpm = 0;
        if (last_wpm != get_current_wpm()) {
            last_wpm = get_current_wpm();
            oled_set_cursor(0, 14);
            oled_write_ln(depad_str(get_u16_str(last_wpm, ' '), ' '), false);
        }
    } else {
        if (!oled_slave_init_done) {
            if (timer_elapsed32(0) > 5000) {
                oled_slave_init_done = true;
                oled_reinit_slave();
            }
        }
    }

    return false;
}
