#include QMK_KEYBOARD_H
#include "version.h"
#include "i18n.h"
#define MOON_LED_LEVEL LED_LEVEL
#define CUSTOM_SAFE_RANGE ZSA_SAFE_RANGE
#include "lang_shift/include.h"

enum custom_keycodes {
  RGB_SLD = CUSTOM_SAFE_RANGE,
  ST_MACRO_0,
  ST_MACRO_1,
};



enum tap_dance_codes {
  DANCE_0,
  DANCE_1,
  DANCE_2,
  DANCE_3,
  DANCE_4,
};

//const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    //---------------------------------------------------------------------------
//  [0] = LAYOUT(
//    EN_AMPR, 
//    EN_W,    
//    SFT_N,   
//    LA_CHNG), // & w <Шифт> <Переключение языка>
//  [1] = LAYOUT(EN_7,    EN_S_W,  _______, RU_NUME), // 7 W <Шифт> №
//  [2] = LAYOUT(RU_7 ,   RU_JU,   SFT_N,   LA_CHNG), // 7 ю <Шифт> <Переключение языка>
//  [3] = LAYOUT(RU_QUES, RU_S_JU, _______, EN_GRV ), // ? Ю <Шифт> `
//};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_HASH,        KC_TRANSPARENT, KC_EXLM,        KC_RABK,        KC_AT,          KC_DELETE,                                      KC_DQUO,        KC_PERC,        KC_DLR,         KC_QUES,        KC_UNDS,        KC_AMPR,        KC_PSCR,        
    KC_TAB,         RU_SHTI,        RU_TSE,         RU_U,           RU_KA,          RU_IE,          KC_LPRN,                                        KC_RPRN,        RU_EN,          RU_GHE,         TD(DANCE_1),    RU_ZE,          RU_E,           RU_YO,          
    KC_SCLN,        RU_EF,          RU_YERU,        RU_VE,          RU_A,           RU_PE,          KC_COMMA,                                                                       KC_DOT,         RU_ER,          RU_O,           RU_EL,          RU_DE,          RU_ZHE,         KC_COLN,        
    KC_TRANSPARENT, RU_YA,          RU_CHE,         RU_ES,          RU_EM,          RU_I,                                           RU_TE,          TD(DANCE_2),    RU_BE,          RU_HA,          RU_YU,          KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LEFT_GUI,    KC_EQUAL,       KC_ENTER,                                                                                                       KC_BSPC,        KC_KP_SLASH,    KC_KP_ASTERISK, KC_KP_MINUS,    KC_KP_PLUS,     TO(1),          
    TD(DANCE_0),    KC_LEFT_CTRL,   TT(2),                          TT(3),          TT(4),          KC_SPACE
  ),
  [1] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_Q,           KC_W,           KC_U,           KC_K,           KC_E,           KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_N,           KC_G,           KC_Y,           KC_NO,          KC_NO,          KC_NO,          
    KC_TRANSPARENT, KC_F,           KC_S,           KC_V,           KC_A,           KC_P,           KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_R,           KC_O,           KC_L,           KC_D,           KC_NO,          KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_Z,           KC_H,           KC_C,           KC_M,           KC_I,                                           KC_T,           KC_J,           KC_B,           KC_X,           KC_NO,          KC_TRANSPARENT, 
    TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [2] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_NO,          KC_NO,          KC_KP_SLASH,    KC_KP_ASTERISK, KC_KP_MINUS,    KC_DELETE,                                      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_NO,          KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_KP_PLUS,     KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_HOME,        KC_UP,          KC_END,         KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_NO,          KC_KP_4,        KC_KP_5,        KC_KP_6,        KC_TRANSPARENT, KC_KP_COMMA,                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_NO,          KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    TO(0),          KC_NO,          KC_NO,          KC_KP_0,        KC_KP_EQUAL,    KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TO(1),          
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_RIGHT_ALT,   KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [3] = LAYOUT_moonlander(
    TO(0),          KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,                                          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         KC_NO,          
    ST_MACRO_0,     RU_NUM,         KC_NO,          TD(DANCE_3),    KC_NO,          US_EACU,        KC_NO,                                          KC_NO,          US_NTIL,        RU_RUBL,        RU_SHCH,        KC_NO,          KC_NO,          KC_NO,          
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          US_AACU,        KC_NO,          KC_NO,                                                                          KC_NO,          KC_NO,          TD(DANCE_4),    KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    QK_BOOT,        KC_NO,          KC_NO,          KC_NO,          KC_NO,          US_IACU,                                        KC_NO,          RU_HARD,        KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    TO(0),          KC_NO,          KC_NO,          KC_NO,          ST_MACRO_1,     KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          TO(1),          
    KC_TRANSPARENT, KC_TRANSPARENT, KC_LEFT_ALT,                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [4] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          
    KC_NO,          RU_NUM,         KC_HOME,        KC_UP,          KC_END,         KC_PGDN,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TILD,        KC_LBRC,        KC_PIPE,        KC_RBRC,        KC_QUOTE,       KC_GRAVE,       
    KC_TRANSPARENT, KC_NO,          KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_PAGE_UP,     KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_CIRC,        KC_LCBR,        KC_TRANSPARENT, KC_RCBR,        KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_BSLS,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TO(1),          
    KC_NO,          KC_TRANSPARENT, TO(2),                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
  'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
                 'L', 'L', 'L', 'R', 'R', 'R'
);


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
    [0] = { {0,245,245}, {41,255,255}, {41,255,255}, {0,0,0}, {139,8,255}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {152,255,255}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {152,255,255}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {74,255,206}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {41,255,255}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {0,245,245}, {41,255,255}, {41,255,255}, {74,255,206}, {74,255,206}, {19,245,233}, {0,245,245}, {152,255,255}, {139,8,255}, {41,255,255}, {0,0,0}, {204,218,204}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {41,255,255}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {41,255,255}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {41,255,255}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {41,255,255}, {41,255,255}, {139,8,255}, {139,8,255}, {139,8,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {19,245,233}, {19,245,233}, {0,245,245} },

    [1] = { {0,245,245}, {41,255,255}, {41,255,255}, {0,0,0}, {139,8,255}, {41,255,255}, {204,218,204}, {204,218,204}, {204,218,204}, {152,255,255}, {41,255,255}, {204,218,204}, {204,218,204}, {204,218,204}, {152,255,255}, {41,255,255}, {204,218,204}, {204,218,204}, {204,218,204}, {74,255,206}, {41,255,255}, {204,218,204}, {204,218,204}, {204,218,204}, {41,255,255}, {41,255,255}, {204,218,204}, {204,218,204}, {204,218,204}, {0,245,245}, {41,255,255}, {41,255,255}, {74,255,206}, {74,255,206}, {19,245,233}, {0,245,245}, {152,255,255}, {0,0,0}, {41,255,255}, {0,0,0}, {204,218,204}, {41,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {41,255,255}, {41,255,255}, {0,0,0}, {204,218,204}, {204,218,204}, {41,255,255}, {41,255,255}, {204,218,204}, {204,218,204}, {204,218,204}, {41,255,255}, {41,255,255}, {204,218,204}, {204,218,204}, {204,218,204}, {41,255,255}, {41,255,255}, {204,218,204}, {204,218,204}, {204,218,204}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {19,245,233}, {19,245,233}, {0,245,245} },

    [2] = { {0,245,245}, {0,0,0}, {0,0,0}, {0,0,0}, {139,8,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {166,200,217}, {166,200,217}, {166,200,217}, {0,0,0}, {41,255,255}, {166,200,217}, {166,200,217}, {166,200,217}, {166,200,217}, {41,255,255}, {166,200,217}, {166,200,217}, {166,200,217}, {41,255,255}, {41,255,255}, {41,255,255}, {0,0,0}, {0,0,0}, {0,245,245}, {0,0,0}, {41,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,245,245}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {204,218,204}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {8,218,204}, {0,0,0}, {0,0,0}, {0,0,0}, {8,218,204}, {8,218,204}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {8,218,204}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,245,245} },

    [3] = { {0,245,245}, {0,215,255}, {0,0,0}, {0,215,255}, {139,8,255}, {166,200,217}, {41,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {166,200,217}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {166,200,217}, {205,116,210}, {0,0,0}, {0,0,0}, {0,0,0}, {166,200,217}, {0,0,0}, {205,116,210}, {0,0,0}, {41,255,255}, {166,200,217}, {205,116,210}, {0,0,0}, {205,116,210}, {166,200,217}, {0,0,0}, {0,0,0}, {74,255,206}, {74,255,206}, {74,255,206}, {0,245,245}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {204,218,204}, {166,200,217}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {166,200,217}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {166,200,217}, {139,8,255}, {0,0,0}, {0,0,0}, {0,0,0}, {166,200,217}, {41,255,255}, {205,116,210}, {139,8,255}, {0,0,0}, {166,200,217}, {205,116,210}, {0,0,0}, {0,0,0}, {166,200,217}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,245,245} },

    [4] = { {0,245,245}, {0,0,0}, {41,255,255}, {0,0,0}, {139,8,255}, {41,255,255}, {41,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {41,255,255}, {0,0,0}, {8,218,204}, {0,0,0}, {0,0,0}, {41,255,255}, {8,218,204}, {8,218,204}, {0,0,0}, {0,0,0}, {41,255,255}, {0,0,0}, {8,218,204}, {0,0,0}, {41,255,255}, {41,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,245,245}, {41,255,255}, {41,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,245,245}, {0,0,0}, {41,255,255}, {41,255,255}, {0,0,0}, {204,218,204}, {41,255,255}, {41,255,255}, {0,0,0}, {0,0,0}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {0,0,0}, {41,255,255}, {41,255,255}, {41,255,255}, {0,0,0}, {0,0,0}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {0,0,0}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {0,0,0}, {0,0,0}, {0,245,245} },

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
      if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
        rgb_matrix_set_color_all(0, 0, 0);
      }
  }

  return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!lang_shift_process_record(keycode, record))
    return false;
  switch (keycode) {
    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_DELETE) ));
    }
    break;
    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_LEFT_ALT) SS_TAP(X_KP_8) SS_TAP(X_KP_8) SS_TAP(X_KP_0) SS_TAP(X_KP_0) ));
    }
    break;

    switch (keycode) {
	  case TO(1):
	    if (record->event.pressed) {
	      lang_activate(0);
	      register_code(KC_LCTRL);
	      register_code(KC_D);
	      unregister_code(KC_D);
	      unregister_code(KC_LCTRL);
	    }
	    return false;
	    break;
	}
	return true;

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

void user_timer(void) {
  lang_shift_user_timer();
}

void matrix_scan_user(void) {
  user_timer();
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

static tap dance_state[5];

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


void dance_0_finished(tap_dance_state_t *state, void *user_data);
void dance_0_reset(tap_dance_state_t *state, void *user_data);

void dance_0_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_HOLD: register_code16(KC_LEFT_SHIFT); break;
        case DOUBLE_TAP: register_code16(KC_CAPS); break;
    }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_HOLD: unregister_code16(KC_LEFT_SHIFT); break;
        case DOUBLE_TAP: unregister_code16(KC_CAPS); break;
    }
    dance_state[0].step = 0;
}
void on_dance_1(tap_dance_state_t *state, void *user_data);
void dance_1_finished(tap_dance_state_t *state, void *user_data);
void dance_1_reset(tap_dance_state_t *state, void *user_data);

void on_dance_1(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(RU_SHA);
        tap_code16(RU_SHA);
        tap_code16(RU_SHA);
    }
    if(state->count > 3) {
        tap_code16(RU_SHA);
    }
}

void dance_1_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(RU_SHA); break;
        case DOUBLE_TAP: register_code16(RU_SHCH); break;
        case DOUBLE_SINGLE_TAP: tap_code16(RU_SHA); register_code16(RU_SHA);
    }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(RU_SHA); break;
        case DOUBLE_TAP: unregister_code16(RU_SHCH); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(RU_SHA); break;
    }
    dance_state[1].step = 0;
}
void on_dance_2(tap_dance_state_t *state, void *user_data);
void dance_2_finished(tap_dance_state_t *state, void *user_data);
void dance_2_reset(tap_dance_state_t *state, void *user_data);

void on_dance_2(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(RU_SOFT);
        tap_code16(RU_SOFT);
        tap_code16(RU_SOFT);
    }
    if(state->count > 3) {
        tap_code16(RU_SOFT);
    }
}

void dance_2_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[2].step = dance_step(state);
    switch (dance_state[2].step) {
        case SINGLE_TAP: register_code16(RU_SOFT); break;
        case DOUBLE_TAP: register_code16(RU_HARD); break;
        case DOUBLE_SINGLE_TAP: tap_code16(RU_SOFT); register_code16(RU_SOFT);
    }
}

void dance_2_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[2].step) {
        case SINGLE_TAP: unregister_code16(RU_SOFT); break;
        case DOUBLE_TAP: unregister_code16(RU_HARD); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(RU_SOFT); break;
    }
    dance_state[2].step = 0;
}
void on_dance_3(tap_dance_state_t *state, void *user_data);
void dance_3_finished(tap_dance_state_t *state, void *user_data);
void dance_3_reset(tap_dance_state_t *state, void *user_data);

void on_dance_3(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(US_UACU);
        tap_code16(US_UACU);
        tap_code16(US_UACU);
    }
    if(state->count > 3) {
        tap_code16(US_UACU);
    }
}

void dance_3_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[3].step = dance_step(state);
    switch (dance_state[3].step) {
        case SINGLE_TAP: register_code16(US_UACU); break;
        case DOUBLE_TAP: register_code16(US_UDIA); break;
        case DOUBLE_SINGLE_TAP: tap_code16(US_UACU); register_code16(US_UACU);
    }
}

void dance_3_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[3].step) {
        case SINGLE_TAP: unregister_code16(US_UACU); break;
        case DOUBLE_TAP: unregister_code16(US_UDIA); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(US_UACU); break;
    }
    dance_state[3].step = 0;
}
void on_dance_4(tap_dance_state_t *state, void *user_data);
void dance_4_finished(tap_dance_state_t *state, void *user_data);
void dance_4_reset(tap_dance_state_t *state, void *user_data);

void on_dance_4(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(US_OACU);
        tap_code16(US_OACU);
        tap_code16(US_OACU);
    }
    if(state->count > 3) {
        tap_code16(US_OACU);
    }
}

void dance_4_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[4].step = dance_step(state);
    switch (dance_state[4].step) {
        case SINGLE_TAP: register_code16(US_OACU); break;
        case DOUBLE_TAP: register_code16(US_ODIA); break;
        case DOUBLE_SINGLE_TAP: tap_code16(US_OACU); register_code16(US_OACU);
    }
}

void dance_4_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[4].step) {
        case SINGLE_TAP: unregister_code16(US_OACU); break;
        case DOUBLE_TAP: unregister_code16(US_ODIA); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(US_OACU); break;
    }
    dance_state[4].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
        [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_3, dance_3_finished, dance_3_reset),
        [DANCE_4] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_4, dance_4_finished, dance_4_reset),
};
