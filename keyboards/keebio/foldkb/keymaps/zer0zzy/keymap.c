/* Copyright 2021 Danny Nguyen <danny@keeb.io>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "encoder.h"
#include QMK_KEYBOARD_H

#define ENC_UNDO LCTL(KC_Z)
#define ENC_REDO LCTL(KC_Y)

#define LCG(kc) (QK_LCTL | QK_LGUI | (kc))

#define _BASE 0
#define _NUM 1
#define _NAV 2
#define _FN 3
#define _MEDIA 4
#define _BASE2 5
#define _NAV2 6


#define xxxxxx KC_NO

enum custom_keycodes {
  TOG_GAME = SAFE_RANGE,
  TOG_NORMAL = SAFE_RANGE + 1,
  CLR_MODS = SAFE_RANGE + 2,
  MX_URL_REGEX

};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;
tap_dance_action_t *action;

enum tap_dance_codes {
  DANCE_0,
  DANCE_1,
  DANCE_2,
  SCLN_RALT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_MUTE,            KC_ESC,             _______,            _______,            _______,            _______,            _______,            _______,                                _______,            _______,            _______,            _______,            _______,            _______,            xxxxxx,             _______,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_HOME,                                _______,            TD(DANCE_2),        KC_W,               KC_E,               KC_R,               KC_T,                                   KC_Y,               KC_U,               KC_I,               KC_O,               KC_P,               _______,            _______,            _______,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_END,                                 _______,            LALT_T(KC_A),       LGUI_T(KC_S),       LCTL_T(KC_D),       LSFT_T(KC_F),       KC_G,                                   KC_H,               LSFT_T(KC_J),       RCTL_T(KC_K),       RGUI_T(KC_L),       TD(SCLN_RALT),      _______,            _______,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_PGUP,                                _______,            KC_Z,               KC_X,               KC_C,               KC_V,               KC_B,                                   KC_N,               KC_M,               KC_COMMA,           KC_DOT,             KC_SLSH,            _______,            xxxxxx,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_PGDN,                                _______,            KC_NO,              KC_NO,              KC_BSPC,            xxxxxx,             LT(_NUM,KC_TAB),                        LT(_NAV,KC_SPACE),  MEH_T(KC_ENTER),    KC_NO,              KC_NO,              KC_NO,              TOG_GAME
    ),
    [_NUM] = LAYOUT(
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        _______,            KC_ESC,             _______,            _______,            _______,            _______,            _______,            _______,                                _______,            _______,            _______,            _______,            _______,            _______,            xxxxxx,             _______,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        _______,                                _______,            KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,                                  _______,            KC_7,               KC_8,               KC_9,               KC_EQUAL,           _______,            _______,            _______,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        _______,                                _______,            KC_NO,              KC_NO,              KC_NO,              MX_URL_REGEX,       KC_NO,                                  KC_BSLS,            KC_4,               KC_5,               KC_6,               KC_SCLN,            _______,            _______,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        _______,                                _______,            KC_NO,              KC_ESC,             KC_NO,              KC_NO,              KC_NO,                                  _______,            KC_1,               KC_2,               KC_3,               KC_DOT,             _______,            xxxxxx,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        _______,                                _______,            _______,            _______,            _______,            xxxxxx,             _______,                                _______,            KC_0,               _______,            _______,            _______,            _______
    ),
    [_NAV] = LAYOUT(
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_SCRL,            KC_ESC,             _______,            _______,            _______,            _______,            _______,            _______,                                _______,            _______,            _______,            _______,            _______,            _______,            xxxxxx,             _______,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        _______,                                _______,            KC_ESC,             KC_GRAVE,           KC_LPRN,            KC_RPRN,            KC_NO,                                  KC_NO,              KC_PAGE_UP,         KC_UP,              KC_DEL,             KC_INS,             _______,             _______,            _______,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        _______,                                _______,            KC_QUOTE,           KC_MINUS,           KC_LBRC,            KC_RBRC,            KC_NO,                                  KC_HOME,            KC_LEFT,            KC_DOWN,            KC_RIGHT,           KC_END,             _______,            _______,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        _______,                                _______,            KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,                                  _______,            KC_PAGE_DOWN,       KC_NO,              KC_ESC,             KC_DOT,             _______,            xxxxxx,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        _______,                                _______,            _______,            _______,            _______,            xxxxxx,             _______,                                _______,            _______,            _______,            _______,            _______,            _______
    ),
    [_FN] = LAYOUT(
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        _______,            CLR_MODS,           _______,            _______,            _______,            _______,            _______,            _______,                                _______,            _______,            _______,            _______,            _______,            _______,            _______,            _______,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        _______,                                _______,            KC_F24,             KC_F23,             KC_F22,             KC_F21,             _______,                                _______,            KC_F9,              KC_F10,             KC_F11,             KC_F12,             _______,            _______,            _______,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        _______,                                _______,            KC_F20,             KC_F19,             KC_F18,             KC_F17,             _______,                                _______,            KC_F5,              KC_F6,              KC_F7,              KC_F8,              _______,            _______,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        _______,                                _______,            KC_F16,             KC_F15,             KC_F14,             KC_F13,             _______,                                _______,            KC_F1,              KC_F2,              KC_F3,              KC_F4,              _______,            _______,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        _______,                                _______,            _______,            _______,            _______,            xxxxxx,             _______,                                _______,            _______,            _______,            _______,            _______,            _______
    ),
    [_MEDIA] = LAYOUT(
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_MUTE,            KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,                                  KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              xxxxxx,             KC_NO,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        BL_STEP,                                KC_NO,              QK_BOOT,            KC_NO,              TD(DANCE_0),        KC_AUDIO_VOL_UP,    KC_NO,                                  KC_NO,              KC_BRIGHTNESS_UP,   KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        RGB_MOD,                                KC_NO,              KC_NO,              KC_NO,              KC_MEDIA_PLAY_PAUSE,KC_AUDIO_MUTE,      KC_NO,                                  KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_VOLU,                                KC_NO,              KC_NO,              KC_NO,              TD(DANCE_1),        KC_AUDIO_VOL_DOWN,  KC_NO,                                  KC_NO,              KC_BRIGHTNESS_DOWN, KC_NO,              KC_NO,              KC_NO,              KC_NO,              xxxxxx,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_VOLD,                                KC_NO,              KC_NO,              KC_NO,              KC_NO,              xxxxxx,             KC_NO,                                  KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              _______
    ),
    [_BASE2] = LAYOUT(
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_MUTE,            KC_ESC,             KC_1,               KC_2,               KC_3,               KC_4,               KC_5,               KC_6,                                   KC_7,               KC_8,               KC_9,               KC_0,               KC_MINS,            KC_EQL,             xxxxxx,             KC_BSPC,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_HOME,                                KC_TAB,             KC_Q,               KC_W,               KC_E,               KC_R,               KC_T,                                   KC_Y,               KC_U,               KC_I,               KC_O,               KC_P,               KC_LBRC,            KC_RBRC,            KC_BSLS,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_END,                                 MO(_NAV2),          KC_A,               KC_S,               KC_D,               KC_F,               KC_G,                                   KC_H,               KC_J,               KC_K,               KC_L,               KC_SCLN,            KC_QUOT,            KC_ENT,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_PGUP,                                KC_LSFT,            KC_Z,               KC_X,               KC_C,               KC_V,               KC_B,                                   KC_N,               KC_M,               KC_COMM,            KC_DOT,             KC_SLSH,            KC_RSFT,            xxxxxx,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_PGDN,                                KC_LCTL,            KC_LGUI,            KC_LALT,            KC_SPC,             xxxxxx,             KC_SPC,                                 KC_SPC,             KC_SPC,             KC_RALT,            KC_RGUI,            KC_RCTL,            TOG_NORMAL
    ),
    [_NAV2] = LAYOUT(
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_MUTE,            KC_GRAVE,           KC_F1,              KC_F2,              KC_F3,              KC_F4,              KC_F5,              KC_F6,                                  KC_F7,              KC_F8,              KC_F9,              KC_F10,             KC_F11,             KC_F12,             xxxxxx,             KC_BSPC,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_INS,                                 KC_CAPS,            KC_Q,               KC_UP,              KC_E,               KC_R,               KC_T,                                   KC_Y,               KC_7,               KC_8,               KC_9,               KC_EQUAL,           KC_LBRC,            KC_RBRC,            KC_BSLS,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_DEL,                                 MO(_NAV2),          KC_LEFT,            KC_DOWN,            KC_RIGHT,           KC_F,               KC_G,                                   KC_BSLS,            KC_4,               KC_5,               KC_6,               KC_SCLN,            KC_QUOT,            KC_ENT,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_PGUP,                                KC_LSFT,            KC_Z,               KC_X,               KC_C,               KC_V,               KC_B,                                   KC_N,               KC_1,               KC_2,               KC_3,               KC_DOT,             KC_RSFT,            xxxxxx,
    // |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|                   |-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|-------------------|
        KC_PGDN,                                KC_LCTL,            KC_LGUI,            KC_LALT,            KC_SPC,             xxxxxx,             KC_SPC,                                 KC_SPC,             KC_0,               KC_RALT,            KC_RGUI,            KC_RCTL,            TOG_NORMAL
    ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]  = { ENCODER_CCW_CW(ENC_UNDO, ENC_REDO) },
    [_NUM]   = {},
    [_NAV]   = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_FN]    = {},
    [_MEDIA] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_BASE2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_NAV2]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif

const uint16_t PROGMEM combo0[] = { MT(MOD_LSFT, KC_F), MT(MOD_LSFT, KC_J), COMBO_END};
const uint16_t PROGMEM combo1[] = { LT(_NAV,KC_SPACE), MEH_T(KC_ENTER), COMBO_END};
const uint16_t PROGMEM combo2[] = { LCTL_T(KC_D), RCTL_T(KC_K), COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, KC_CAPS),
    COMBO(combo1, TT(_MEDIA)),
    COMBO(combo2, QK_LEADER),
};


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_F):
            return TAPPING_TERM -50;
        case LSFT_T(KC_J):
            return TAPPING_TERM -50;
        case LT(_NAV,KC_SPACE):
            return TAPPING_TERM -50;
        case  LT(_NUM,KC_TAB):
            return TAPPING_TERM -50;
        default:
            return TAPPING_TERM;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, _NUM, _NAV, _FN);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t mod_state;
  mod_state = get_mods();
  switch (keycode) {
    case CLR_MODS:
    if (record->event.pressed) {
        clear_mods();
    }
    break;
    case MX_URL_REGEX:
    if (record->event.pressed) {
        SEND_STRING("(https?:\\/\\/)?(www\\.)?[-a-zA-Z0-9@:%._\\+~#=]{1,256}\\.[a-zA-Z0-9()]{1,6}\\b([-a-zA-Z0-9()@:%_\\+.~#?&\\/=]*)\\r");
    }
    case TOG_GAME:
    if (record->event.pressed) {
        default_layer_set((layer_state_t)1 << _BASE2);
        autoshift_disable();
    }
    break;
    case TOG_NORMAL:
    if (record->event.pressed) {
        default_layer_set((layer_state_t)1 << _BASE);
        autoshift_enable();
    }
    break;
    case TD(DANCE_0):
    case TD(DANCE_1):
    case TD(DANCE_2):
        action = &tap_dance_actions[TD_INDEX(keycode)];
        if (!record->event.pressed && action->state.count && !action->state.finished) {
            tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
            tap_code16(tap_hold->tap);
        }
        break;
    case KC_BSPC:
        {
        // Initialize a boolean variable that keeps track
        // of the delete key status: registered or not?
        static bool delkey_registered;
        if (record->event.pressed) {
            // Detect the activation of either shift keys
            if (mod_state & MOD_MASK_SHIFT) {
                // First temporarily canceling both shifts so that
                // shift isn't applied to the KC_DEL keycode
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_DEL);
                // Update the boolean variable to reflect the status of KC_DEL
                delkey_registered = true;
                // Reapplying modifier state so that the held shift key(s)
                // still work even after having tapped the Backspace/Delete key.
                set_mods(mod_state);
                return false;
            }
        } else { // on release of KC_BSPC
            // In case KC_DEL is still being sent even after the release of KC_BSPC
            if (delkey_registered) {
                unregister_code(KC_DEL);
                delkey_registered = false;
                return false;
            }
        }
        // Let QMK process the KC_BSPC keycode as usual outside of shift
        return true;
    }
  }
  return true;
}

void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    if (leader_sequence_two_keys(KC_PERCENT, KC_Y)) {
        // Leader, d, d => CTL+A, CTL+C
        SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    } else if (leader_sequence_two_keys(KC_V, KC_R)) {
        // Leader, (v)irtual, (r)ight => Display Right
        tap_code16(LCG(KC_RIGHT));
    } else if (leader_sequence_two_keys(KC_V, KC_L)) {
        // Leader, (v)irtual, (left) => Display Left
        tap_code16(LCG(KC_LEFT));
    } else if (leader_sequence_two_keys(KC_W, KC_S)) {
        // Leader, (w)indows, (s)earch => GUI+S
        tap_code16(LGUI(KC_S));
    } else if (leader_sequence_two_keys(KC_W, KC_O)) {
        // Leader, (w)indows, (o)mnibar => CTL+Space
        tap_code16(LCG(LALT(KC_SPACE)));
    } else if (leader_sequence_two_keys(KC_P, KC_E)) {
        // Leader, (p)rint, (e)mail => email
        SEND_STRING("andre.dessert@premworx.com");
    } else if (leader_sequence_three_keys(KC_U, KC_R, KC_L)) {
        // Leader, u, r, l => url
        SEND_STRING("(https?:\\/\\/)?(www\\.)?[-a-zA-Z0-9@:%._\\+~#=]{1,256}\\.[a-zA-Z0-9()]{1,6}\\b([-a-zA-Z0-9()@:%_\\+.~#?&\\/=]*)\\r");
    } else if (leader_sequence_three_keys(KC_S, KC_C, KC_E)) {
        // Leader, (s)ymbols, (c)heckbox, (e)mpty => -[ ]
        SEND_STRING(SS_TAP(X_MINUS) SS_DELAY(10) SS_TAP(X_SPACE) SS_DELAY(10) SS_TAP(X_LBRC) SS_DELAY(10) SS_TAP(X_SPACE) SS_DELAY(10) SS_TAP(X_RBRC));
    } else if (leader_sequence_three_keys(KC_S, KC_C, KC_D)) {
        // Leader, (s)ymbols, (c)heckbox, (d)one => -[ ]
        SEND_STRING(SS_TAP(X_MINUS) SS_DELAY(10) SS_TAP(X_SPACE) SS_DELAY(10) SS_TAP(X_LBRC) SS_DELAY(10) SS_TAP(X_X) SS_DELAY(10) SS_TAP(X_RBRC));
    } else if (leader_sequence_three_keys(KC_S, KC_C, KC_C)) {
        // Leader, (s)ymbols, (c)heckbox, (c)hecked => -[ ]
        SEND_STRING(SS_TAP(X_MINUS) SS_DELAY(10) SS_TAP(X_SPACE) SS_DELAY(10) SS_TAP(X_LBRC) SS_DELAY(10) SS_TAP(X_V) SS_DELAY(10) SS_TAP(X_RBRC));
    }
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[2];

uint8_t dance_step(tap_dance_state_t *state);

uint8_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

void on_scln_ralt(tap_dance_state_t *state, void *user_data);
void scln_ralt_finished(tap_dance_state_t *state, void *user_data);
void scln_ralt_reset(tap_dance_state_t *state, void *user_data);

void on_scln_ralt(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_SCLN);
        tap_code16(KC_SCLN);
        tap_code16(KC_SCLN);
    }
    if(state->count > 3) {
        tap_code16(KC_SCLN);
    }
}

void scln_ralt_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(KC_SCLN); break;
        case SINGLE_HOLD: register_code16(KC_COLN); break;
        case DOUBLE_TAP: register_code16(KC_SCLN); register_code16(KC_SCLN); break;
        case DOUBLE_HOLD: register_code16(KC_RIGHT_ALT); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_SCLN); register_code16(KC_SCLN);
    }
}

void scln_ralt_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_SCLN); break;
        case SINGLE_HOLD: unregister_code16(KC_COLN); break;
        case DOUBLE_TAP: unregister_code16(KC_SCLN); break;
        case DOUBLE_HOLD: unregister_code16(KC_RIGHT_ALT); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_SCLN); break;
    }
    dance_state[1].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [DANCE_0]   = ACTION_TAP_DANCE_TAP_HOLD(KC_MEDIA_NEXT_TRACK, KC_MEDIA_FAST_FORWARD),
    [DANCE_1]   = ACTION_TAP_DANCE_TAP_HOLD(KC_MEDIA_PREV_TRACK, KC_MEDIA_REWIND),
    [DANCE_2]   = ACTION_TAP_DANCE_TAP_HOLD(KC_Q, KC_Q),
    [SCLN_RALT] = ACTION_TAP_DANCE_FN_ADVANCED(on_scln_ralt, scln_ralt_finished, scln_ralt_reset),
};

//Pressing shift, then the auto shift key, causes the unshifted key to repeat. (ex. Shift+KC_LPRN causes KC_COMMA to be output.)
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_DOT:
        case KC_COMMA:
        case KC_LPRN:
        case KC_RPRN:
            return true;
        default:
            return false;
    }
}

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case KC_COMMA:
            register_code16((!shifted) ? KC_COMMA : KC_QUOTE);
            break;
        case KC_DOT:
            register_code16((!shifted) ? KC_DOT : KC_DOUBLE_QUOTE);
            break;
         case KC_LPRN:
            register_code16((!shifted) ? KC_LPRN : KC_LT);
            break;
        case KC_RPRN:
            register_code16((!shifted) ? KC_RPRN : KC_GT);
            break;
        default:
            if (shifted) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            // register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
            register_code16(keycode);
    }
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case KC_COMMA:
            unregister_code16((!shifted) ? KC_COMMA : KC_QUOTE);
            break;
        case KC_DOT:
            unregister_code16((!shifted) ? KC_DOT : KC_DOUBLE_QUOTE);
            break;
        case KC_LPRN:
            unregister_code16((!shifted) ? KC_LPRN : KC_LT);
            break;
        case KC_RPRN:
            unregister_code16((!shifted) ? KC_RPRN : KC_GT);
            break;
        default:
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            // The IS_RETRO check isn't really necessary here, always using
            // keycode & 0xFF would be fine.
            //unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
            unregister_code16(keycode);
    }
}
