#include QMK_KEYBOARD_H
#include <moonlander.h>
#include <version.h>
#define MOON_LED_LEVEL LED_LEVEL
#define LCG(kc) (QK_LCTL | QK_LGUI | (kc))

#define _BASE 0
#define _NUM 1
#define _NAV 2
#define _FN 3
#define _MEDIA 4
#define _MOUSE 5

bool caps_lock_active = false;

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  MX_SIGNATURE,
  MX_URL_REGEX,
  MX_DPI_CHANGE,
  MX_MS_SCROLL,
  MX_PLOOPY_BOOT,
  CLR_MODS,
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
  POWER,
  MS_RIGHT_MIDDLE,
  SCLN_RALT,
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_moonlander(
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         CLR_MODS,                       KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_Q,                   KC_W,                   KC_E,                   KC_R,                   KC_T,                   KC_TRANSPARENT,         KC_TRANSPARENT,                 MX_DPI_CHANGE,          KC_TRANSPARENT,         KC_Y,                   KC_U,                   KC_I,                   KC_O,                   KC_P,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    LALT_T(KC_A),           LGUI_T(KC_S),           LCTL_T(KC_D),           LSFT_T(KC_F),           KC_G,                   KC_TRANSPARENT,         KC_TRANSPARENT,                 KC_MS_BTN1,             TD(MS_RIGHT_MIDDLE),    KC_H,                   LSFT_T(KC_J),           RCTL_T(KC_K),           RGUI_T(KC_L),           TD(SCLN_RALT),
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|                                                       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_Z,                   KC_X,                   KC_C,                   KC_V,                   KC_B,                   KC_TRANSPARENT,                                                                 LT(0, KC_CAPS),         KC_N,                   KC_M,                   KC_COMMA,               KC_DOT,                 KC_SLASH,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-------RED KEY---------|                                                       |---RED KEY-------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_BSPC,                LT(_NUM,KC_TAB),        KC_PRINT_SCREEN,                                                                KC_TRANSPARENT,         LT(_NAV,KC_SPACE),      MEH_T(KC_ENTER),        KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,
//|--THUMB 1--------------|---THUMB 2-------------|---THUMB 3-------------|                                                                                                                                                                                                       |---THUMB 3-------------|---------THUMB 2-------|-----THUMB 1-----------|
    KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,                                                                                                                                                                                                                 KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT
  ),
    [_NUM] = LAYOUT_moonlander (
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,                 KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,                  KC_TRANSPARENT,         KC_TRANSPARENT,                 KC_NO,                  KC_TRANSPARENT,         KC_NO,                  KC_7,                   KC_8,                   KC_9,                   KC_EQUAL,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,                  MX_URL_REGEX,           KC_TRANSPARENT,         KC_TRANSPARENT,                 KC_NO,                  KC_NO,                  KC_BSLS,                KC_4,                   KC_5,                   KC_6,                   KC_SCLN,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|                                                       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_NO,                  KC_ESC,                 KC_NO,                  KC_NO,                  KC_NO,                  KC_TRANSPARENT,                                                                 KC_NO,                  KC_NO,                  KC_1,                   KC_2,                   KC_3,                   KC_NO,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-------RED KEY---------|                                                       |---RED KEY-------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_NO,                                                                          KC_TRANSPARENT,         KC_TRANSPARENT,         KC_0,                   KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,
//|--THUMB 1--------------|---THUMB 2-------------|---THUMB 3-------------|                                                                                                                                                                                                       |---THUMB 3-------------|---------THUMB 2-------|-----THUMB 1-----------|
    KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,                                                                                                                                                                                                                 KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT
  ),
    [_NAV] = LAYOUT_moonlander(
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,                 KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_ESC,                 KC_GRAVE,               KC_LPRN,                KC_RPRN,                KC_NO,                  KC_TRANSPARENT,         KC_TRANSPARENT,                 KC_TRANSPARENT,         KC_TRANSPARENT,         KC_NO,                  KC_PAGE_UP,             KC_UP,                  KC_DELETE,              KC_INSERT,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_QUOTE,               KC_MINUS,               KC_LBRC,                KC_RBRC,                KC_NO,                  KC_TRANSPARENT,         KC_TRANSPARENT,                 KC_TRANSPARENT,         KC_TRANSPARENT,         KC_HOME,                KC_LEFT,                KC_DOWN,                KC_RIGHT,               KC_END,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|                                                       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_NO,                  KC_NO,                  KC_NO,                  KC_QUOTE,               KC_NO,                  KC_TRANSPARENT,                                                                 KC_TRANSPARENT,         KC_NO,                  KC_PAGE_DOWN,           KC_NO,                  KC_ESC,                 KC_NO,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-------RED KEY---------|                                                       |---RED KEY-------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_NO,                                                                          KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,
//|--THUMB 1--------------|---THUMB 2-------------|---THUMB 3-------------|                                                                                                                                                                                                       |---THUMB 3-------------|---------THUMB 2-------|-----THUMB 1-----------|
    KC_TRANSPARENT,         KC_TRANSPARENT,         KC_NO,                                                                                                                                                                                                                          KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT
  ),
    [_FN] = LAYOUT_moonlander(
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,                 KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_F24,                 KC_F23,                 KC_F22,                 KC_F21,                 KC_NO,                  KC_TRANSPARENT,         KC_TRANSPARENT,                 KC_TRANSPARENT,         KC_TRANSPARENT,         KC_NO,                  KC_F9,                  KC_F10,                 KC_F11,                 KC_F12,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_F20,                 KC_F19,                 KC_F18,                 KC_F17,                 KC_NO,                  KC_TRANSPARENT,         KC_TRANSPARENT,                 KC_NO,                  KC_NO,                  KC_NO,                  KC_F5,                  KC_F6,                  KC_F7,                  KC_F8,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|                                                       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_F16,                 KC_F15,                 KC_F14,                 KC_F13,                 KC_NO,                  KC_TRANSPARENT,                                                                 KC_NO,                  KC_NO,                  KC_F1,                  KC_F2,                  KC_F3,                  KC_F4,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-------RED KEY---------|                                                       |---RED KEY-------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_NO,                                                                          KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,
//|--THUMB 1--------------|---THUMB 2-------------|---THUMB 3-------------|                                                                                                                                                                                                       |---THUMB 3-------------|---------THUMB 2-------|-----THUMB 1-----------|
    KC_TRANSPARENT,         KC_TRANSPARENT,         KC_NO,                                                                                                                                                                                                                          KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT
  ),

    [_MEDIA] = LAYOUT_moonlander(
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,                 KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    QK_BOOT,                KC_NO,                  TD(DANCE_0),            KC_AUDIO_VOL_UP,        KC_NO,                  KC_TRANSPARENT,         KC_TRANSPARENT,                 KC_TRANSPARENT,         KC_TRANSPARENT,         KC_NO,                  KC_BRIGHTNESS_UP,       KC_NO,                  KC_NO,                  KC_NO,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_NO,                  KC_NO,                  KC_MEDIA_PLAY_PAUSE,    KC_AUDIO_MUTE,          KC_NO,                  KC_TRANSPARENT,         KC_TRANSPARENT,                 KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,                  MX_SIGNATURE,           KC_NO,                  KC_NO,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|                                                       |-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    MX_PLOOPY_BOOT,         KC_NO,                  TD(DANCE_1),            KC_AUDIO_VOL_DOWN,      KC_NO,                  KC_TRANSPARENT,                                                                 KC_NO,                  KC_NO,                  KC_BRIGHTNESS_DOWN,     KC_NO,                  KC_NO,                  KC_NO,
//|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|-------RED KEY---------|                                                       |---RED KEY-------------|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|
    KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         TD(POWER),                                                                      KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT,
//|--THUMB 1--------------|---THUMB 2-------------|---THUMB 3-------------|                                                                                                                                                                                                       |---THUMB 3-------------|---------THUMB 2-------|-----THUMB 1-----------|
    KC_TRANSPARENT,         KC_TRANSPARENT,         KC_NO,                                                                                                                                                                                                                          KC_TRANSPARENT,         KC_TRANSPARENT,         KC_TRANSPARENT
  ),
};
const uint16_t PROGMEM combo0[] = { LSFT_T(KC_F), LSFT_T(KC_J), COMBO_END};
const uint16_t PROGMEM combo1[] = { KC_W, KC_Q, COMBO_END};
const uint16_t PROGMEM combo2[] = { LT(_NAV,KC_SPACE), MEH_T(KC_ENTER), COMBO_END};
const uint16_t PROGMEM combo3[] = { LCTL_T(KC_D), RCTL_T(KC_K), COMBO_END};
const uint16_t PROGMEM combo4[] = { KC_MS_BTN1, KC_MS_BTN2, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, KC_CAPS),
    COMBO(combo1, KC_ESCAPE),
    COMBO(combo2, TT(_MEDIA)),
    COMBO(combo3, QK_LEADER),
    COMBO(combo4, KC_MS_BTN3),
};


// bool led_update_user(led_t state) {
//     if (state.scroll_lock == 1) {
//         wait_ms(10);
//         layer_on(_MOUSE);
//     } else {
//         layer_off(_MOUSE);
//     }

//     return true;
// }

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_F):
            return TAPPING_TERM -50;
        case LSFT_T(KC_J):
            return TAPPING_TERM -50;
        case LT(_NAV,KC_SPACE):
            return TAPPING_TERM -50;
        default:
            return TAPPING_TERM;
    }
}

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {0,0,0}, {194,255,255}, {157,255,255}, {194,255,255}, {0,0,0}, {0,0,0}, {194,255,255}, {157,255,255}, {194,255,255}, {0,0,0}, {0,0,0}, {194,255,255}, {157,255,255}, {194,255,255}, {0,0,0}, {0,0,0}, {194,255,255}, {157,255,255}, {194,255,255}, {194,255,255}, {0,0,0}, {194,255,255}, {194,255,255}, {194,255,255}, {194,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {131,255,255}, {0,0,0}, {0,0,0}, {194,255,255}, {194,255,255}, {194,255,255}, {194,255,255}, {0,0,0}, {194,255,255}, {157,255,255}, {194,255,255}, {0,0,0}, {0,0,0}, {194,255,255}, {157,255,255}, {194,255,255}, {0,0,0}, {0,0,0}, {194,255,255}, {157,255,255}, {194,255,255}, {0,0,0}, {0,0,0}, {194,255,255}, {157,255,255}, {194,255,255}, {194,255,255}, {0,0,0}, {194,255,255}, {194,255,255}, {194,255,255}, {194,255,255}, {0,0,0}, {0,0,0}, {0,245,245}, {131,255,255}, {0,0,0}, {131,255,255}, {0,245,245}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [1] = { {0,0,0}, {0,245,245},   {43,255,255},   {0,0,0},        {0,0,0},    {0,0,0}, {43,255,255},  {43,255,255},   {0,0,0},        {0,0,0}, {0,0,0}, {43,255,255},     {43,255,255},   {0,0,0}, {0,0,0}, {0,0,0}, {43,255,255}, {43,255,255}, {0,0,0}, {194,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {194,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {219,255,255}, {219,255,255}, {219,255,255}, {219,255,255}, {0,0,0}, {43,255,255}, {43,255,255}, {43,255,255}, {0,0,0}, {0,0,0}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {0,0,0}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {0,0,0}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {0,0,0}, {43,255,255}, {0,0,0}, {194,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [2] = { {0,0,0}, {0,245,245},   {43,255,255},   {0,0,0},        {0,0,0},    {0,0,0}, {43,255,255},  {43,255,255},   {0,0,0},        {0,0,0}, {0,0,0}, {43,255,255},     {43,255,255},   {0,0,0}, {0,0,0}, {0,0,0}, {43,255,255}, {43,255,255}, {0,0,0}, {194,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {194,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {142,255,255}, {142,255,255}, {142,255,255}, {142,255,255}, {0,0,0}, {20,255,255}, {20,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {20,255,255}, {74,255,255}, {0,245,245}, {0,0,0}, {0,0,0}, {74,255,255}, {74,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {20,255,255}, {74,255,255}, {20,255,255}, {194,255,255}, {0,0,0}, {0,0,0}, {20,255,255}, {0,0,0}, {194,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [3] = { {0,0,0}, {219,255,255}, {219,255,255},  {219,255,255},  {0,0,0},    {0,0,0}, {219,255,255}, {219,255,255},  {219,255,255},  {0,0,0}, {0,0,0}, {219,255,255},    {219,255,255},  {219,255,255}, {0,0,0}, {0,0,0}, {219,255,255}, {219,255,255}, {219,255,255}, {194,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {194,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {172,255,255}, {172,255,255}, {172,255,255}, {172,255,255}, {0,0,0}, {219,255,255}, {219,255,255}, {219,255,255}, {0,0,0}, {0,0,0}, {219,255,255}, {219,255,255}, {219,255,255}, {0,0,0}, {0,0,0}, {219,255,255}, {219,255,255}, {219,255,255}, {0,0,0}, {0,0,0}, {219,255,255}, {219,255,255}, {219,255,255}, {194,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {194,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [4] = { {0,0,0}, {0,245,245},   {0,0,0},        {0,245,245},    {0,0,0},    {0,0,0}, {0,0,0},       {0,0,0},        {0,0,0},        {0,0,0}, {0,0,0}, {152,255,255},    {152,255,255},  {152,255,255}, {0,0,0}, {0,0,0}, {74,255,255}, {74,255,255}, {74,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {14,229,244}, {14,229,244}, {14,229,244}, {14,229,244}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {43,255,255}, {0,0,0}, {43,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [5] = { {0,0,0}, {0,245,245},   {157,255,255},  {0,0,0},        {0,0,0},    {0,0,0}, {0,245,245},   {157,255,255},  {20,255,255},   {0,0,0}, {0,0,0}, {0,0,0},          {157,255,255},  {20,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {157,255,255}, {20,255,255}, {194,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {194,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {86,255,255}, {86,255,255}, {86,255,255}, {86,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {194,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {194,255,255}, {0,0,0}, {0,0,0}, {131,255,255}, {0,245,245}, {0,0,0}, {0,0,0}, {0,245,245}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, _NUM, _NAV, _FN);
}

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) {
      return false;
  }
  if (keyboard_config.disable_layer_led) { return false; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}

bool led_update_user(led_t led_state) {
  caps_lock_active = led_state.caps_lock;
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t mod_state;
  mod_state = get_mods();
  switch (keycode) {
    case MX_SIGNATURE:
    if (record->event.pressed) {
        SEND_STRING("30487987");
    }
    break;
    case MX_URL_REGEX:
    if (record->event.pressed) {
        SEND_STRING("(https?:\/\/)?(www\.)?[-a-zA-Z0-9@:%._\+~#=]{1,256}\.[a-zA-Z0-9()]{1,6}\b([-a-zA-Z0-9()@:%_\+.~#?&\/=]*)\r");
    }
    break;
    case MX_DPI_CHANGE:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_TAP(X_SCRL));
    }
    break;
    case LT(0, KC_CAPS):
    if (!record->tap.count && record->event.pressed) {
      if (caps_lock_active) {
        SEND_STRING(SS_DOWN(X_LSFT));
      } else {
        SEND_STRING(SS_TAP(X_CAPS) SS_DOWN(X_LSFT));
      }
    } else if (!record->event.pressed) {
      SEND_STRING(SS_UP(X_LSFT));
    }
    break;
    case MX_PLOOPY_BOOT:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_NUM) SS_TAP(X_NUM) SS_TAP(X_SCRL) SS_TAP(X_SCRL));
    }
    break;
    case CLR_MODS:
    if (record->event.pressed) {
        clear_mods();
    }
    break;
    case TD(DANCE_0):
    case TD(DANCE_1):
        action = &tap_dance_actions[TD_INDEX(keycode)];
        if (!record->event.pressed && action->state.count && !action->state.finished) {
            tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
            tap_code16(tap_hold->tap);
        }
        break;
    case RGB_SLD:
        if (rawhid_state.rgb_control) {
            return false;
        }
        if (record->event.pressed) {
            rgblight_mode(1);
        }
        return false;
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
        SEND_STRING("(https?:\/\/)?(www\.)?[-a-zA-Z0-9@:%._\+~#=]{1,256}\.[a-zA-Z0-9()]{1,6}\b([-a-zA-Z0-9()@:%_\+.~#?&\/=]*)\r")
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

void on_ms_right_middle(tap_dance_state_t *state, void *user_data);
void ms_right_middle_finished(tap_dance_state_t *state, void *user_data);
void ms_right_middle_reset(tap_dance_state_t *state, void *user_data);

void on_ms_right_middle(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_MS_BTN2);
        tap_code16(KC_MS_BTN2);
        tap_code16(KC_MS_BTN2);
    }
    if(state->count > 3) {
        tap_code16(KC_MS_BTN2);
    }
}

void ms_right_middle_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(KC_MS_BTN2); break;
        case DOUBLE_TAP: register_code16(KC_MS_BTN3); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_MS_BTN2); register_code16(KC_MS_BTN2);
    }
}

void ms_right_middle_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(KC_MS_BTN2); break;
        case DOUBLE_TAP: unregister_code16(KC_MS_BTN3); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_MS_BTN2); break;
    }
    dance_state[0].step = 0;
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
        [DANCE_0]           = ACTION_TAP_DANCE_TAP_HOLD(KC_MEDIA_NEXT_TRACK, KC_MEDIA_FAST_FORWARD),
        [DANCE_1]           = ACTION_TAP_DANCE_TAP_HOLD(KC_MEDIA_PREV_TRACK, KC_MEDIA_REWIND),
        [POWER]             = ACTION_TAP_DANCE_TAP_HOLD(KC_WAKE, KC_SLEP),
        [MS_RIGHT_MIDDLE]   = ACTION_TAP_DANCE_FN_ADVANCED(on_ms_right_middle, ms_right_middle_finished, ms_right_middle_reset),
        [SCLN_RALT] = ACTION_TAP_DANCE_FN_ADVANCED(on_scln_ralt, scln_ralt_finished, scln_ralt_reset),
};

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
