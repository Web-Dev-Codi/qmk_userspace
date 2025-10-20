
#include QMK_KEYBOARD_H
#include "sendstring_german.h"

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTZ,
    _GERMAN,
    _LOWER,
    _RAISE,
    _ADJUST,
};


#define KC_QWERTZ PDF(_QWERTZ)
#define KC_GERMAN PDF(_GERMAN)
// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERTZ
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  ESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  +   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Z  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LSFT |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  ""  |
 * |------+------+------+------+------+------|  MUTE |    | PAUSE |------+------+------+------+------+------|
 * | LCTL |   Y  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RSFT  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LALT | LGUI | LCMD | LALT | /SPACE  /       \ENTER \  | RALT | RCMD | RGUI | RCTL |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */

 [_QWERTZ] = LAYOUT(
    KC_ESC,  KC_1, KC_2, KC_3,  KC_4,    KC_5,                           KC_6 ,    KC_7, KC_8   , KC_9  , KC_0   , KC_PLUS,
    KC_TAB,  KC_Q, KC_W, KC_E,  KC_R,    KC_T,                           KC_Z ,    KC_U, KC_I   , KC_O  , KC_P   , KC_MINS,
    KC_LSFT, KC_A, KC_S, KC_D,  KC_F,    KC_G,                           KC_H ,    KC_J, KC_K   , KC_L  , KC_SCLN, KC_QUOT,
    KC_LCTL, KC_Y, KC_X, KC_C,  KC_V,    KC_B,  KC_MUTE,          KC_NO, KC_N ,   KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                KC_LALT, LGUI(KC_LSFT), KC_LGUI, TL_LOWR, KC_SPC ,    KC_ENT, TL_UPPR, KC_BSPC, KC_RGUI, KC_RCTL
  ),

/*
 * GERMAN (with DE_ keycodes for US OS layout)
 * Uses sendstring_german.h to produce German characters on US OS keyboard layout
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  ß   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Z  |   U  |   I  |   O  |   P  |  Ü   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LSFT  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ö  |  Ä   |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |LCTL  |   Y  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   -  |RSFT  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LALT |  UP  | LGUI |LOWER | /Space  /       \Enter \  |RAISE | Bspc | RGUI | RCTL |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */

 [_GERMAN] = LAYOUT(
    KC_ESC,  DE_1,    DE_2,    DE_3,    DE_4,    DE_5,                         DE_6,    DE_7,    DE_8,    DE_9,    DE_0,    DE_SS,
    KC_TAB,  DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,                         DE_Z,    DE_U,    DE_I,    DE_O,    DE_P,    DE_UDIA,
    KC_LSFT, DE_A,    DE_S,    DE_D,    DE_F,    DE_G,                         DE_H,    DE_J,    DE_K,    DE_L,    DE_ODIA, DE_ADIA,
    KC_LCTL, DE_Y,    DE_X,    DE_C,    DE_V,    DE_B,     KC_MUTE,       KC_NO,   DE_N,    DE_M,    DE_COMM, DE_DOT,  DE_MINS, KC_RSFT,
                      KC_LALT, KC_UP,   KC_LGUI, TL_LOWR,   KC_SPC,      KC_ENT,  TL_UPPR,   KC_BSPC, KC_RGUI, KC_RCTL
),


  /* LOWER                                                                Music Controls
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |VOLUP |VOLDWN|  PRV | NEXT | STOP | PLAY |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | `    |  !   |  @   |  #   |  $   |  %   |-------.    ,-------|  ^   |  &   |   *  |  (   |  )   |  _   |
 * |------+------+------+------+------+------|  MUTE |    | PAUSE |------+------+------+------+------+------|
 * |      |      |      |      |      |   B  |-------|    |-------|  MUTE |  _  |   +  |   {  |   }  |  |   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LALT | LGUI | LCMD | LALT | /SPACE  /       \ENTER \   | RALT | RCMD | RGUI | RCTL  |
 *            |      |      |      |      |/       /         \      \  |      |      |      |       |
 *            `----------------------------------'            '------''-----------------------------'
   */

  [_LOWER] = LAYOUT(
    KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO , KC_NO  ,                       KC_VOLU, KC_VOLD, KC_MRWD, KC_MFFD, KC_MSTP, KC_MPLY,
    KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5 , KC_F6  ,                       KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
    KC_GRV , KC_EXLM, KC_AT  , KC_HASH, KC_DLR, KC_PERC,                     KC_CIRC  , KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
    KC_LCTL, KC_NO  , KC_NO  , KC_NO  , KC_NO , KC_NO  ,KC_MUTE,     KC_NO , KC_APP   , KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_NO  ,
                    KC_LALT, KC_LCTL, KC_LGUI,TL_LOWR , KC_SPC ,     KC_ENT, KC_UP, KC_DOWN, KC_LEFT, KC_RGHT
  ),

  /* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |   1   |   2   |   3   | PRSC |  UP |DEL |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |   4   |   5   |   6   | LEFT |     |RIGT|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|   7   |   8   |   9   |      | DOWN|    |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|   +   |   0   |  =    |   {  |   } |    |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /SPACE  /       \ENTER \  |      |      |      |       |
 *            |      |      |      |      |/       /         \      \ |      |      |      |       |
 *            `----------------------------------'           '------''-----------------------------'
   */


  [_RAISE] = LAYOUT(
    LALT(KC_RALT)	, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                                              KC_1   , KC_2, KC_3   , KC_PSCR, KC_UP  , KC_DEL ,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                                                         KC_4   , KC_5, KC_6   , KC_LEFT, KC_NO  , KC_RGHT,
    LSFT(LGUI(KC_1)),LSFT(LGUI(KC_2)),LSFT(LGUI(KC_3)),LSFT(LGUI(KC_4)),LSFT(LGUI(KC_5)),LSFT(LGUI(KC_6)),            KC_7   , KC_8, KC_9   , KC_NO  , KC_DOWN, KC_NO  ,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,                                                         KC_NO , KC_PLUS, KC_0, KC_PEQL, KC_LBRC, KC_RBRC, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_SPC,                                                                     KC_ENT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  /* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  ESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  +   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Z  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LSFT |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  ""  |
 * |------+------+------+------+------+------|  MUTE |    | PAUSE |------+------+------+------+------+------|
 * | LCTL |   Y  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RSFT  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LALT | LGUI | LCMD | LALT | /SPACE  /       \ENTER \   | RALT | RCMD | RGUI | RCTL |
 *            |      |      |      |      |/       /         \      \  |      |      |      |      |
 *            `----------------------------------'           '------''-----------------------------'
   */

     [_ADJUST] = LAYOUT(
        QK_BOOT, QK_RBT, DB_TOGG  , KC_NO  , KC_TRNS, KC_TRNS,                              KC_COPY, KC_PSTE, KC_PSCR, KC_INS , KC_HOME, KC_PGUP,
        KC_TRNS, KC_NO , KC_QWERTZ,KC_GERMAN, KC_NO  , KC_NO  ,                          KC_UNDO, KC_CUT , KC_FIND, KC_DEL , KC_END , KC_PGDN,
        KC_TRNS, KC_NO , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                              KC_AGIN, KC_NO  , UG_TOGG, UG_HUEU, UG_SATU, UG_VALU,
        KC_TRNS, KC_NO , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,KC_TRNS,         KC_TRNS, KC_NO  , UG_PREV, UG_NEXT, UG_HUED, UG_SATD, UG_VALD,
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                 KC_TRNS, KC_TRNS, KC_PSCR, KC_TRNS, KC_TRNS
    ),

};

/* TEMPLATE FOR NEW LAYOUT
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LCTL | LGUI | LCMD | LALT | /SPACE  /       \ENTER \  | RALT | RCMD | RGUI | RCTL |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''-----------------------------'
*/

/*
    [_LAYOUT_NAME] = LAYOUT(
    _______,   _______,   _______,   _______,   _______,   _______,                        _______,   _______,   _______,   _______,   _______,   _______,
    _______,   _______,   _______,   _______,   _______,   _______,                        _______,   _______,   _______,   _______,   _______,   _______,
    _______,   _______,   _______,   _______,   _______,   _______,                        _______,   _______,   _______,   _______,   _______,   _______,
    _______,   _______,   _______,   _______,   _______,   _______,  _______,    _______,  _______,   _______,   _______,   _______,   _______,   _______,
                            _______,   _______,   _______,   _______,    _______,   _______,   _______,   _______
);

*/


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTZ] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_GERMAN] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_LOWER]  = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_RAISE]  = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_ADJUST] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
};
#endif
