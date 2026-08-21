// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

static uint16_t last_keycode = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌──────┬──────┬──────┐
     * │ PREV │ PLAY │ NEXT │
     * ├──────┼──────┼──────┤
     * │  F13 │  F14 │ LOCK │
     * └──────┴──────┴──────┘
     */
    [0] = LAYOUT_ortho_2x3(
        KC_MPRV,    KC_MPLY,    KC_MNXT,
        KC_F13,    KC_F14,    LGUI(KC_L)
    )
};

#if defined(ENCODER_ENABLE)
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        last_keycode = keycode;
    }
    return true;
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_write_P(PSTR("Nokira Hackpad\n"), false);
    oled_write_P(PSTR("--------------\n"), false);
    oled_write_P(PSTR("Status: Operative\n"), false);
    char buf[22];
    snprintf(buf, sizeof(buf), "Key: 0x%04X    \n", last_keycode);
    oled_write(buf, false);

    return false;
}
#endif
