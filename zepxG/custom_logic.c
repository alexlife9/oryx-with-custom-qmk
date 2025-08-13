// --- custom_logic.c ---

// ========================================================================

// 1. найди функцию bool process_record_user(...) 
// 2. вставь так: 

//#include "custom_logic.c"                                            // это первое добавление
//bool process_record_user(uint16_t keycode, keyrecord_t *record) {    // это оригинальная строка
//    if (!process_record_custom(keycode, record)) { return false; }   // это второе добавление

// ========================================================================
    

// Этот файл содержит всю кастомную логику для умного переключения слоев и языка.

// --- Глобальная переменная для отслеживания языка ---
// true = русский, false = английский.
// По умолчанию при включении клавиатуры считаем, что активен русский язык (слой 0).
#include "quantum.h" // Для get_highest_layer, layer_state_t
#include "timer.h"   // Для timer_read и timer_elapsed

static bool is_russian_lang_active = true;

// Переменные для отслеживания состояния OSM(MOD_LSFT)
static bool shift_held = false;
static uint16_t shift_timer = 0;

// Callback для обработки изменений состояния слоёв
layer_state_t layer_state_set_user(layer_state_t state) {
    bool desired_russian = (get_highest_layer(state) == 0);
    if (is_russian_lang_active != desired_russian) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        is_russian_lang_active = desired_russian;
    }
    return state;
}

// Кастомная функция-обработчик нажатий
bool process_record_custom(uint16_t keycode, keyrecord_t *record) {
    if (keycode == OSM(MOD_LSFT)) {
        if (record->event.pressed) {
            // Нажатие: начинаем отсчёт времени для определения tap/hold
            shift_timer = timer_read();
            shift_held = true;
            register_code(KC_LSFT); // Регистрируем шифт сразу для hold
        } else {
            // Отпускание
            shift_held = false;
            unregister_code(KC_LSFT); // Снимаем шифт
            // Если время нажатия меньше TAPPING_TERM, это tap
            if (timer_elapsed(shift_timer) < TAPPING_TERM) {
                set_oneshot_mods(MOD_BIT(KC_LSFT)); // Активируем залипающий шифт
            }
        }
        return false; // Не даём QMK обрабатывать OSM(MOD_LSFT) дальше
    }

    // Остальная логика для других keycodes
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case TO(0):
            layer_move(0);
            return false;

        case TO(1):
            layer_move(1);
            return false;

        case TT(2):
            return true;

        case OSL(3):
            return true;

        default:
            return true;
    }
}