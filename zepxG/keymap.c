#include QMK_KEYBOARD_H
#include "version.h"
#include "i18n.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
  ST_MACRO_0,
  ST_MACRO_1,
  ST_MACRO_2,
  ST_MACRO_3,
  ST_MACRO_4,
  ST_MACRO_5,
  ST_MACRO_6,
  ST_MACRO_7,
  ST_MACRO_8,
  ST_MACRO_9,
  ST_MACRO_10,
  ST_MACRO_11,
  ST_MACRO_12,
  ST_MACRO_13,
  ST_MACRO_14,
  ST_MACRO_15,
  ST_MACRO_16,
  ST_MACRO_17,
  ST_MACRO_18,
  ST_MACRO_19,
  ST_MACRO_20,
  ST_MACRO_21,
  ST_MACRO_22,
  ST_MACRO_23,
};



enum tap_dance_codes {
  DANCE_0,
  DANCE_1,
};

#define DUAL_FUNC_0 LT(6, KC_F19)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_moonlander(
    KC_ESCAPE,      ST_MACRO_0,     RU_PERC,        RU_EXLM,        ST_MACRO_1,     ST_MACRO_2,     ST_MACRO_3,                                     RU_DQUO,        RU_UNDS,        KC_LABK,        RU_QUES,        ST_MACRO_4,     ST_MACRO_5,     KC_PSCR,        
    KC_TAB,         RU_SHTI,        RU_TSE,         RU_U,           RU_KA,          RU_IE,          RU_SCLN,                                        RU_COLN,        RU_EN,          RU_GHE,         RU_SHA,         RU_ZE,          RU_E,           LCTL(KC_F),     
    KC_KP_PLUS,     RU_EF,          RU_YERU,        RU_VE,          RU_A,           RU_PE,          RU_LPRN,                                                                        RU_RPRN,        RU_ER,          RU_O,           RU_EL,          RU_DE,          RU_ZHE,         KC_KP_ASTERISK, 
    KC_KP_MINUS,    RU_YA,          RU_CHE,         RU_ES,          RU_EM,          RU_I,                                           RU_TE,          RU_SOFT,        RU_BE,          RU_HA,          RU_YU,          KC_KP_SLASH,    
    TD(DANCE_0),    LCTL(KC_A),     KC_LEFT,        KC_RIGHT,       RU_COMM,        KC_ENTER,                                                                                                       KC_BSPC,        RU_DOT,         KC_UP,          KC_DOWN,        ST_MACRO_6,     TO(1),          
    OSM(MOD_LSFT),  TG(2),          OSL(3),                         TD(DANCE_1),    MT(MOD_LCTL, KC_DELETE),KC_SPACE
  ),
  [1] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_HASH,        KC_PERC,        KC_EXLM,        KC_DLR,         KC_AT,          KC_QUOTE,                                       KC_DQUO,        KC_UNDS,        KC_LABK,        KC_QUES,        KC_RABK,        KC_AMPR,        KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_Q,           KC_W,           KC_U,           KC_K,           KC_E,           KC_SCLN,                                        KC_COLN,        KC_N,           KC_G,           KC_Y,           KC_NO,          KC_NO,          KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_F,           KC_S,           KC_V,           KC_A,           KC_P,           KC_LPRN,                                                                        KC_RPRN,        KC_R,           KC_O,           KC_L,           KC_D,           KC_NO,          KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_Z,           KC_H,           KC_C,           KC_M,           KC_I,                                           KC_T,           KC_J,           KC_B,           KC_X,           KC_NO,          KC_TRANSPARENT, 
    DUAL_FUNC_0,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_COMMA,       KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_DOT,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [2] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_HASH,        KC_PERC,        KC_EXLM,        KC_DLR,         KC_AT,          KC_QUOTE,                                       KC_DQUO,        KC_UNDS,        KC_LABK,        KC_QUES,        KC_RABK,        KC_AMPR,        KC_TRANSPARENT, 
    LCTL(LSFT(KC_X)),LCTL(KC_B),     KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_LCBR,        KC_SCLN,                                        KC_COLN,        KC_RCBR,        KC_HOME,        KC_UP,          KC_END,         KC_CIRC,        KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_KP_0,        KC_KP_4,        KC_KP_5,        KC_KP_6,        KC_LBRC,        KC_LPRN,                                                                        KC_RPRN,        KC_RBRC,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_PIPE,        KC_TRANSPARENT, 
    KC_TRANSPARENT, ST_MACRO_7,     KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_EQUAL,                                       ST_MACRO_8,     ST_MACRO_9,     KC_TILD,        KC_GRAVE,       KC_BSLS,        KC_TRANSPARENT, 
    DUAL_FUNC_0,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_COMMA,       KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_DOT,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_BSPC,        KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [3] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,                                          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         KC_NO,          
    KC_NO,          KC_NO,          KC_NO,          ST_MACRO_10,    KC_NO,          ST_MACRO_11,    KC_NO,                                          KC_NO,          ST_MACRO_17,    KC_NO,          RU_SHCH,        KC_NO,          KC_NO,          KC_NO,          
    KC_NO,          KC_NO,          ST_MACRO_12,    ST_MACRO_13,    ST_MACRO_14,    KC_NO,          KC_NO,                                                                          KC_NO,          KC_NO,          ST_MACRO_18,    KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    KC_NO,          ST_MACRO_15,    KC_NO,          KC_NO,          KC_NO,          ST_MACRO_16,                                    KC_NO,          RU_HARD,        KC_NO,          KC_NO,          ST_MACRO_19,    KC_NO,          
    TO(0),          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_NO
  ),
  [4] = LAYOUT_moonlander(
    KC_ESCAPE,      RU_NUM,         KC_NO,          ST_MACRO_20,    KC_NO,          KC_LEFT_GUI,    KC_NO,                                          QK_BOOT,        KC_RIGHT_GUI,   QK_AUDIO_OFF,   ST_MACRO_23,    KC_PAUSE,       KC_NO,          KC_TRANSPARENT, 
    KC_NO,          KC_NO,          KC_HOME,        KC_UP,          KC_END,         KC_BSPC,        KC_NO,                                          KC_NO,          KC_RIGHT_SHIFT, QK_AUDIO_ON,    KC_INSERT,      KC_NO,          KC_NO,          KC_NO,          
    KC_NO,          KC_LEFT_SHIFT,  KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_DELETE,      KC_PSCR,                                                                        KC_NO,          KC_RIGHT_CTRL,  KC_NO,          KC_SCRL,        KC_NO,          KC_PAGE_UP,     KC_NO,          
    KC_NO,          KC_LEFT_CTRL,   ST_MACRO_21,    ST_MACRO_22,    KC_NO,          KC_LEFT_ALT,                                    KC_RIGHT_ALT,   KC_HOME,        KC_UP,          KC_END,         KC_PGDN,        KC_NO,          
    TO(0),          LCTL(KC_Z),     KC_NO,          KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_TRANSPARENT, KC_TRANSPARENT, 
    LSFT(KC_RIGHT), TO(2),          KC_NO,                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [5] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_F2,          KC_F3,          KC_1,           KC_2,           KC_3,           KC_4,                                           KC_NO,          KC_KP_MINUS,    KC_7,           KC_8,           KC_9,           KC_KP_PLUS,     KC_TRANSPARENT, 
    KC_TAB,         KC_T,           KC_Q,           KC_W,           KC_E,           KC_R,           KC_5,                                           KC_KP_ASTERISK, KC_N,           KC_K,           KC_O,           KC_P,           KC_NO,          KC_NO,          
    KC_LEFT_SHIFT,  KC_G,           KC_A,           KC_S,           KC_D,           KC_F,           KC_6,                                                                           KC_KP_SLASH,    KC_Y,           KC_H,           KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    KC_LEFT_CTRL,   KC_B,           KC_Z,           KC_X,           KC_C,           KC_V,                                           KC_NO,          KC_NO,          KC_UP,          KC_NO,          KC_NO,          KC_NO,          
    KC_LEFT_ALT,    KC_J,           KC_I,           KC_L,           KC_M,           KC_ENTER,                                                                                                       KC_TRANSPARENT, KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_NO,          KC_TRANSPARENT, 
    KC_SPACE,       KC_0,           KC_NO,                          KC_NO,          KC_LEFT_CTRL,   KC_SPACE
  ),
};


const uint16_t PROGMEM combo0[] = { TG(2), KC_ENTER, COMBO_END};
const uint16_t PROGMEM combo1[] = { MT(MOD_LCTL, KC_DELETE), KC_BSPC, COMBO_END};
const uint16_t PROGMEM combo2[] = { RU_SHA, RU_EL, COMBO_END};
const uint16_t PROGMEM combo3[] = { RU_O, RU_SOFT, COMBO_END};
const uint16_t PROGMEM combo4[] = { LCTL(KC_A), RU_YA, COMBO_END};
const uint16_t PROGMEM combo5[] = { RU_ER, RU_RPRN, COMBO_END};
const uint16_t PROGMEM combo6[] = { KC_KP_PLUS, KC_KP_MINUS, COMBO_END};
const uint16_t PROGMEM combo7[] = { MT(MOD_LCTL, KC_DELETE), KC_SPACE, COMBO_END};
const uint16_t PROGMEM combo8[] = { RU_PE, RU_I, COMBO_END};
const uint16_t PROGMEM combo9[] = { RU_SCLN, RU_LPRN, COMBO_END};
const uint16_t PROGMEM combo10[] = { RU_EF, MT(MOD_LCTL, KC_DELETE), COMBO_END};
const uint16_t PROGMEM combo11[] = { MT(MOD_LCTL, KC_DELETE), KC_TAB, COMBO_END};
const uint16_t PROGMEM combo12[] = { KC_LEFT, KC_RIGHT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, LCTL(KC_ENTER)),
    COMBO(combo1, LCTL(KC_BSPC)),
    COMBO(combo2, RU_SHCH),
    COMBO(combo3, RU_HARD),
    COMBO(combo4, LCTL(KC_Z)),
    COMBO(combo5, RU_RUBL),
    COMBO(combo6, KC_EQUAL),
    COMBO(combo7, KC_ENTER),
    COMBO(combo8, KC_DELETE),
    COMBO(combo9, KC_BSPC),
    COMBO(combo10, TO(3)),
    COMBO(combo11, KC_CAPS),
    COMBO(combo12, KC_SPACE),
};



extern rgb_config_t rgb_matrix_config;

RGB hsv_to_rgb_with_value(HSV hsv) {
  RGB rgb = hsv_to_rgb( hsv );
  float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
  return (RGB){ f * rgb.r, f * rgb.g, f * rgb.b };
}

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {0,245,245}, {152,255,255}, {41,255,255}, {41,255,255}, {139,8,255}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {21,252,195}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {133,255,255}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {133,255,255}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {41,255,255}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {41,255,255}, {41,255,255}, {41,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {0,245,245}, {152,255,255}, {21,252,195}, {41,255,255}, {41,255,255}, {204,218,204}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {0,245,245}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {133,255,255}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {133,255,255}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {41,255,255}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {152,255,255}, {152,255,255}, {0,245,245} },

    [1] = { {0,245,245}, {175,255,255}, {41,255,255}, {41,255,255}, {139,8,255}, {41,255,255}, {204,218,204}, {204,218,204}, {204,218,204}, {21,252,195}, {41,255,255}, {204,218,204}, {204,218,204}, {204,218,204}, {133,255,255}, {41,255,255}, {204,218,204}, {204,218,204}, {204,218,204}, {133,255,255}, {41,255,255}, {204,218,204}, {204,218,204}, {204,218,204}, {41,255,255}, {41,255,255}, {204,218,204}, {204,218,204}, {204,218,204}, {41,255,255}, {41,255,255}, {41,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {0,245,245}, {152,255,255}, {21,252,195}, {41,255,255}, {41,255,255}, {204,218,204}, {41,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,245,245}, {41,255,255}, {0,0,0}, {204,218,204}, {204,218,204}, {133,255,255}, {41,255,255}, {204,218,204}, {204,218,204}, {204,218,204}, {133,255,255}, {41,255,255}, {204,218,204}, {204,218,204}, {204,218,204}, {41,255,255}, {41,255,255}, {204,218,204}, {204,218,204}, {204,218,204}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {152,255,255}, {152,255,255}, {0,245,245} },

    [2] = { {0,245,245}, {21,250,190}, {41,255,255}, {41,255,255}, {139,8,255}, {41,255,255}, {21,250,190}, {90,241,183}, {21,252,195}, {21,252,195}, {41,255,255}, {90,241,183}, {90,241,183}, {90,241,183}, {133,255,255}, {41,255,255}, {90,241,183}, {90,241,183}, {90,241,183}, {133,255,255}, {41,255,255}, {90,241,183}, {90,241,183}, {90,241,183}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {0,245,245}, {152,255,255}, {152,255,255}, {0,245,245}, {152,255,255}, {21,252,195}, {41,255,255}, {41,255,255}, {204,218,204}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {0,245,245}, {41,255,255}, {175,255,255}, {133,255,255}, {41,255,255}, {133,255,255}, {41,255,255}, {133,255,255}, {133,255,255}, {41,255,255}, {133,255,255}, {41,255,255}, {175,255,255}, {133,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {21,252,195}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {152,255,255}, {152,255,255}, {0,245,245} },

    [3] = { {0,245,245}, {0,0,0}, {0,0,0}, {0,0,0}, {139,8,255}, {90,241,183}, {0,0,0}, {0,0,0}, {139,8,255}, {0,0,0}, {90,241,183}, {0,0,0}, {139,8,255}, {0,0,0}, {0,0,0}, {90,241,183}, {205,116,210}, {205,116,210}, {0,0,0}, {0,0,0}, {90,241,183}, {0,0,0}, {205,116,210}, {0,0,0}, {0,0,0}, {90,241,183}, {205,116,210}, {0,0,0}, {205,116,210}, {90,241,183}, {0,0,0}, {0,0,0}, {152,255,255}, {152,255,255}, {152,255,255}, {0,245,245}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {204,218,204}, {90,241,183}, {0,0,0}, {0,0,0}, {139,8,255}, {0,0,0}, {90,241,183}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {90,241,183}, {139,8,255}, {0,0,0}, {0,0,0}, {0,0,0}, {90,241,183}, {0,0,0}, {205,116,210}, {139,8,255}, {0,0,0}, {90,241,183}, {205,116,210}, {0,0,0}, {0,0,0}, {90,241,183}, {0,0,0}, {0,0,0}, {0,0,0}, {152,255,255}, {152,255,255}, {0,245,245} },

    [4] = { {0,245,245}, {0,0,0}, {0,0,0}, {0,0,0}, {139,8,255}, {41,255,255}, {0,0,0}, {175,255,255}, {175,255,255}, {21,252,195}, {0,0,0}, {175,255,255}, {133,255,255}, {21,252,195}, {0,0,0}, {41,255,255}, {133,255,255}, {133,255,255}, {21,252,195}, {0,0,0}, {0,0,0}, {175,255,255}, {133,255,255}, {0,0,0}, {0,0,0}, {175,255,255}, {0,245,245}, {0,245,245}, {175,255,255}, {0,0,0}, {0,0,0}, {152,255,255}, {21,252,195}, {152,255,255}, {0,0,0}, {0,245,245}, {152,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {204,218,204}, {0,0,0}, {0,0,0}, {175,255,255}, {175,255,255}, {0,245,245}, {133,255,255}, {0,0,0}, {0,0,0}, {175,255,255}, {133,255,255}, {41,255,255}, {175,255,255}, {175,255,255}, {133,255,255}, {133,255,255}, {133,255,255}, {133,255,255}, {0,0,0}, {175,255,255}, {133,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {0,245,245}, {0,0,0}, {0,0,0}, {41,255,255}, {152,255,255}, {152,255,255}, {0,245,245} },

    [5] = { {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {152,255,255}, {204,218,204}, {204,218,204}, {204,218,204}, {204,218,204}, {152,255,255}, {204,218,204}, {133,255,255}, {204,218,204}, {204,218,204}, {90,241,183}, {133,255,255}, {133,255,255}, {204,218,204}, {204,218,204}, {90,241,183}, {204,218,204}, {133,255,255}, {204,218,204}, {204,218,204}, {90,241,183}, {204,218,204}, {204,218,204}, {204,218,204}, {90,241,183}, {90,241,183}, {90,241,183}, {41,255,255}, {90,241,183}, {0,0,0}, {0,245,245}, {152,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,245,245}, {41,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {90,241,183}, {204,218,204}, {0,0,0}, {0,0,0}, {133,255,255}, {90,241,183}, {204,218,204}, {0,0,0}, {133,255,255}, {133,255,255}, {90,241,183}, {204,218,204}, {204,218,204}, {0,0,0}, {133,255,255}, {41,255,255}, {204,218,204}, {204,218,204}, {0,0,0}, {0,0,0}, {41,255,255}, {41,255,255}, {41,255,255}, {0,245,245}, {0,0,0}, {0,245,245} },

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
        RGB rgb = hsv_to_rgb_with_value(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) {
      return false;
  }
  if (!keyboard_config.disable_layer_led) { 
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
      case 5:
        set_layer_color(5);
        break;
     default:
        if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
          rgb_matrix_set_color_all(0, 0, 0);
        }
    }
  } else {
    if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
      rgb_matrix_set_color_all(0, 0, 0);
    }
  }

  return true;
}



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


void on_dance_0(tap_dance_state_t *state, void *user_data);
void dance_0_finished(tap_dance_state_t *state, void *user_data);
void dance_0_reset(tap_dance_state_t *state, void *user_data);

void on_dance_0(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(RU_YO);
        tap_code16(RU_YO);
        tap_code16(RU_YO);
    }
    if(state->count > 3) {
        tap_code16(RU_YO);
    }
}

void dance_0_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(RU_YO); break;
        case SINGLE_HOLD: register_code16(KC_LEFT_CTRL); break;
        case DOUBLE_TAP: layer_move(5); break;
        case DOUBLE_SINGLE_TAP: tap_code16(RU_YO); register_code16(RU_YO);
    }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(RU_YO); break;
        case SINGLE_HOLD: unregister_code16(KC_LEFT_CTRL); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(RU_YO); break;
    }
    dance_state[0].step = 0;
}
void on_dance_1(tap_dance_state_t *state, void *user_data);
void dance_1_finished(tap_dance_state_t *state, void *user_data);
void dance_1_reset(tap_dance_state_t *state, void *user_data);

void on_dance_1(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_AUDIO_MUTE);
        tap_code16(KC_AUDIO_MUTE);
        tap_code16(KC_AUDIO_MUTE);
    }
    if(state->count > 3) {
        tap_code16(KC_AUDIO_MUTE);
    }
}

void dance_1_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(KC_AUDIO_MUTE); break;
        case SINGLE_HOLD: register_code16(KC_LEFT_ALT); break;
        case DOUBLE_TAP: layer_move(4); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_AUDIO_MUTE); register_code16(KC_AUDIO_MUTE);
    }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_AUDIO_MUTE); break;
        case SINGLE_HOLD: unregister_code16(KC_LEFT_ALT); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_AUDIO_MUTE); break;
    }
    dance_state[1].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_3) SS_TAP(X_KP_5) SS_TAP(X_LEFT_ALT) ));
    }
    break;
    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_3) SS_TAP(X_KP_6) SS_TAP(X_LEFT_ALT) ));
    }
    break;
    case ST_MACRO_2:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_6) SS_TAP(X_KP_4) SS_TAP(X_LEFT_ALT) ));
    }
    break;
    case ST_MACRO_3:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_3) SS_TAP(X_KP_9) SS_TAP(X_LEFT_ALT) ));
    }
    break;
    case ST_MACRO_4:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_6) SS_TAP(X_KP_2) SS_TAP(X_LEFT_ALT) ));
    }
    break;
    case ST_MACRO_5:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_3) SS_TAP(X_KP_8) SS_TAP(X_LEFT_ALT) ));
    }
    break;
    case ST_MACRO_6:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_LEFT_CTRL)));
    }
    break;
    case ST_MACRO_7:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTL(SS_TAP(X_L))SS_DELAY(100)  SS_LCTL(SS_TAP(X_C)));
    }
    break;
    case ST_MACRO_8:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_F2)SS_DELAY(100)  SS_TAP(X_HOME));
    }
    break;
    case ST_MACRO_9:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_7) SS_TAP(X_KP_7) SS_TAP(X_LEFT_ALT) ));
    }
    break;
    case ST_MACRO_10:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_5) SS_TAP(X_KP_0) SS_TAP(X_LEFT_ALT) ));
    }
    break;
    case ST_MACRO_11:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_3) SS_TAP(X_LEFT_ALT) ));
    }
    break;
    case ST_MACRO_12:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_1) SS_TAP(X_KP_0) SS_TAP(X_KP_9) SS_TAP(X_KP_9) SS_TAP(X_LEFT_ALT) ));
    }
    break;
    case ST_MACRO_13:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_5) SS_TAP(X_KP_2) SS_TAP(X_LEFT_ALT) ));
    }
    break;
    case ST_MACRO_14:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_2) SS_TAP(X_KP_5) SS_TAP(X_LEFT_ALT) ));
    }
    break;
    case ST_MACRO_15:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_1) SS_TAP(X_KP_1) SS_TAP(X_KP_0) SS_TAP(X_KP_3) SS_TAP(X_LEFT_ALT) ));
    }
    break;
    case ST_MACRO_16:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_7) SS_TAP(X_LEFT_ALT) ));
    }
    break;
    case ST_MACRO_17:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_1) SS_TAP(X_LEFT_ALT) ));
    }
    break;
    case ST_MACRO_18:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_3) SS_TAP(X_LEFT_ALT) ));
    }
    break;
    case ST_MACRO_19:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_1) SS_TAP(X_KP_1) SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_LEFT_ALT) ));
    }
    break;
    case ST_MACRO_20:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_6) SS_TAP(X_KP_1) SS_TAP(X_LEFT_ALT) ));
    }
    break;
    case ST_MACRO_21:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_D)  SS_DELAY(100) SS_TAP(X_ENTER));
    }
    break;
    case ST_MACRO_22:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_MINUS)  SS_DELAY(100) SS_TAP(X_ENTER));
    }
    break;
    case ST_MACRO_23:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_9) SS_TAP(X_KP_1) SS_TAP(X_LEFT_ALT) ));
    }
    break;

    case DUAL_FUNC_0:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          layer_move(0);
        } else {
          layer_move(0);
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_LEFT_CTRL);
        } else {
          unregister_code16(KC_LEFT_CTRL);
        }  
      }  
      return false;
    case RGB_SLD:
        if (rawhid_state.rgb_control) {
            return false;
        }
        if (record->event.pressed) {
            rgblight_mode(1);
        }
        return false;
  }
  return true;
}

