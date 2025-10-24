// Copyright 2025
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "timer.h"
#include "split_util.h"
#include "os_detection.h"

#ifndef is_keyboard_left
#    define is_keyboard_left() is_keyboard_master()
#endif

static uint16_t current_keycode = 0xFFFF;
static uint16_t dog_anim_timer = 0;
static uint8_t  dog_anim_frame = 0;

static const char PROGMEM dog_frame_1[] =
    "  /\\_/\\\n"
    " ( o o )\n"
    "  >  ^ <\n";

static const char PROGMEM dog_frame_2[] =
    "  /\\_/\\\n"
    " ( o o )\n"
    "  >  v <\n";

static const char *dog_frames[] = {dog_frame_1, dog_frame_2};

static char basic_codes_to_name[57] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/'};

static const char *keycode_string(uint16_t keycode) {
    char *keycode_str;
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

static const char *layer_string(uint32_t layer) {
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

static void render_dog(uint8_t frame) {
    oled_set_cursor(0, 2);
    oled_write_P(dog_frames[frame], false);
}

static const char PROGMEM tux_logo[]   = {153, 154, 10, 185, 186, 0};
static const char PROGMEM win_logo[]   = {151, 152, 10, 183, 184, 0};
static const char PROGMEM apple_logo[] = {149, 150, 10, 181, 182, 0};

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    if (is_keyboard_left()) {
        static uint8_t  last_layer = 0xFF;
        static uint16_t last_key   = 0xFFFF;
        static os_variant_t last_os = OS_UNSURE;

        uint8_t       layer = get_highest_layer(layer_state);
        os_variant_t  os    = detected_host_os();
        bool          changed = false;

        if (layer != last_layer) { last_layer = layer; changed = true; }
        if (last_key != current_keycode) { last_key = current_keycode; changed = true; }
        if (os != last_os) { last_os = os; changed = true; }

        if (changed) {
            oled_clear();
            oled_set_cursor(0, 0);
            oled_write("Layer ", false);
            oled_write_ln(layer_string(layer), false);

            oled_write("Key   ", false);
            if (current_keycode < ARRAY_SIZE(basic_codes_to_name)) {
                oled_write_char(basic_codes_to_name[current_keycode], false);
                oled_write_ln("", false);
            } else {
                oled_write_ln(keycode_string(current_keycode), false);
            }

            oled_write("OS    ", false);
            switch (os) {
                case OS_MACOS:
                case OS_IOS:
                    oled_write_P(apple_logo, false);
                    break;
                case OS_WINDOWS:
                    oled_write_P(win_logo, false);
                    break;
                case OS_LINUX:
                    oled_write_P(tux_logo, false);
                    break;
                default:
                    oled_write_ln("Unk", false);
                    break;
            }
        }
    } else {
        if (timer_elapsed(dog_anim_timer) > 200) {
            dog_anim_timer = timer_read();
            dog_anim_frame = (dog_anim_frame + 1) % 2;
            oled_clear();
            oled_set_cursor(0, 0);
            oled_write("WPM ", false);
            uint16_t wpm = get_current_wpm();
            oled_write_ln(get_u16_str(wpm, ' '), false);
            render_dog(dog_anim_frame);
        }
    }

    return true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    current_keycode = keycode;
    return process_record_user(keycode, record);
}
