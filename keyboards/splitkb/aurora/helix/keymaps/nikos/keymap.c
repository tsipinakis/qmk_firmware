#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
            KC_GRV,          KC_1,  KC_2,    KC_3,    KC_4,  KC_5,                    KC_6,   KC_7,    KC_8,    KC_9,   KC_0,    KC_DEL,
            KC_TAB,          KC_Q,  KC_W,    KC_E,    KC_R,  KC_T,                    KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPC,
            LCTL_T(KC_CAPS), KC_A,  KC_S,    KC_D,    KC_F,  KC_G,                    KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
            KC_LSFT,         KC_Z,  KC_X,    KC_C,    KC_V,  KC_B,  KC_LBRC, KC_RBRC, KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
            MO(3),           KC_RCTL, DF(4), KC_LALT, KC_LGUI, KC_SPC, MO(1),  MO(2), KC_SPC, KC_RGUI, KC_DOWN, KC_UP, KC_LEFT, KC_RGHT
        ),
	[1] = LAYOUT(
            _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, KC_PSCR,
            KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
            _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
            _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_LPRN, KC_RPRN,  KC_F12,  _______, KC_PGUP, KC_PGDN, KC_END, _______,
            _______, _______, _______, _______, _______, _______, _______, _______,  MO(3),   _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
        ),
	[2] = LAYOUT(
            _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
            KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
            _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
            _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, _______, _______,   KC_F12,  _______, KC_END,  KC_HOME, _______, _______,
            _______, _______, _______, _______, _______, MO(3),  _______, _______,   _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
        ),
	[3] = LAYOUT(
            KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
            _______, QK_BOOT, _______, EE_CLR,  _______, _______,                    _______, _______, _______, _______, _______, KC_DEL,
            _______, _______, _______, _______, _______, AG_NORM,                    AG_SWAP, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______,  _______, RGB_SPI, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
            _______, _______, _______, _______, _______, _______, _______, _______,  _______, RGB_SPD, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD
        ),
    [4] = LAYOUT(
            KC_GRV,          KC_1,  KC_2,    KC_3,    KC_4,  KC_5,                    KC_6,  KC_7,  KC_8,    KC_9,   KC_0,    KC_DEL,
            KC_TAB,          KC_Q,  KC_W,    KC_F,    KC_P,  KC_B,                    KC_J,  KC_L,  KC_U,    KC_Y,   KC_SCLN, KC_BSPC,
            LCTL_T(KC_CAPS), KC_A,  KC_R,    KC_S,    KC_T,  KC_G,                    KC_M,  KC_N,  KC_E,    KC_I,   KC_O,    KC_QUOT,
            KC_LSFT,         KC_Z,  KC_X,    KC_C,    KC_D,  KC_V,  KC_LBRC, KC_RBRC, KC_K,  KC_H,  KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
            MO(3),           KC_RCTL, DF(0), KC_LALT, KC_LGUI, KC_SPC, MO(1),  MO(2), KC_SPC, KC_NO, KC_DOWN, KC_UP, KC_LEFT, KC_RGHT
        )
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

void keyboard_post_init_user(void) {
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (get_highest_layer(layer_state) > 0 && get_highest_layer(layer_state) != 4) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_BLUE);
                }
            }
        }
    } else if (host_keyboard_led_state().scroll_lock) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(0, (keypos_t){col,row}) == KC_RCTL) {
                    rgb_matrix_set_color(index, RGB_RED);
                }
            }
        }
    }
    return false;
}
