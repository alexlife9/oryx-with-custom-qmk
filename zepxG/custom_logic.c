// ========================================================================

// 1. найди функцию bool process_record_user(...) 
// 2. вставь так: 

//#include "custom_logic.c"                                            // это первое добавление
//bool process_record_user(uint16_t keycode, keyrecord_t *record) {    // это оригинальная строка
//    if (!process_record_custom(keycode, record)) { return false; }   // это второе добавление

// ========================================================================

#include "quantum.h" // Для get_highest_layer, layer_state_t
#include "timer.h"   // Для timer_read и timer_elapsed

static bool is_russian_lang_active = true;

// Переменные для обработки двойного клика KC_LPRN
//#define PAREN_TAPPING_TERM 100 // Настраиваемый тайм-аут для скобок в миллисекундах
static uint16_t lprn_timer = 0;
static uint8_t lprn_tap_count = 0;

// Callback функция для обработки изменений состояния слоёв.
// Вызывается автоматически QMK каждый раз, когда меняется активный слой (например, при активации/деактивации через TT, OSL, TO).
layer_state_t layer_state_set_user(layer_state_t state) {
    // Определяем желаемый язык: русский, если наивысший слой == 0, иначе английский.
    bool desired_russian = (get_highest_layer(state) == 0);

    // Если текущий язык не совпадает с желаемым, переключаем его в ОС и обновляем флаг.
    if (is_russian_lang_active != desired_russian) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        is_russian_lang_active = desired_russian;
    }

    return state; // Возвращаем состояние слоёв без изменений.
}

// Наша главная кастомная функция-обработчик.
// Она перехватывает нажатия кнопок до того, как их обработает стандартная логика Oryx.
// Логика переключения языка теперь полностью в layer_state_set_user, так что здесь только управление слоями.
bool process_record_custom(uint16_t keycode, keyrecord_t *record) {

    // Обработка двойного клика для KC_LPRN
    if (keycode == KC_LPRN) {
        if (record->event.pressed) {
            if (lprn_tap_count == 0) {
                lprn_timer = timer_read();
                lprn_tap_count = 1;
            } else if (lprn_tap_count == 1 && timer_elapsed(lprn_timer) < 175) { // Локальный таймаут 175 мс
                lprn_tap_count = 2;
                // Двойной клик: печатаем () и перемещаем курсор
                SEND_STRING("()"SS_TAP(X_LEFT));
                lprn_tap_count = 0; // Сбрасываем счётчик
                return false;
            } else {
                lprn_tap_count = 0; // Сбрасываем, если истёк таймаут
                lprn_timer = timer_read();
                lprn_tap_count = 1;
            }
        } else { // При отпускании
            if (lprn_tap_count == 1 && timer_elapsed(lprn_timer) > 175) {
                // Одиночное нажатие: печатаем ( с учётом текущей раскладки
                SEND_STRING(SS_DELAY(10)"(")
                lprn_tap_count = 0;
                return false;
            }
        }
        return true; // Разрешаем стандартную обработку KC_LPRN, если не обработали
    }


    // Остальная логика для других keycodes
    if (!record->event.pressed) { // Реагируем только на нажатия, а не на отпускания (для TO, TT, OSL).
        return true;
    }

    switch (keycode) {
        case TO(0): // Перейти на слой 0 (язык обработает layer_state_set_user)
            layer_move(0);
            return false; // Не даём QMK обрабатывать дальше.

        case TO(1): // Перейти на слой 1 (язык обработает layer_state_set_user)
            layer_move(1);
            return false; // Не даём QMK обрабатывать дальше.

        case TT(2): // Переключение на слой 2 (tap-toggle), язык обработает layer_state_set_user
            return true; // Разрешаем QMK обработать TT(2).

        case OSL(3): // One-shot на слой 3, язык обработает layer_state_set_user
            return true; // Разрешаем QMK обработать OSL(3).

        default:
            // Не наша клавиша, пусть QMK обрабатывает.
            return true;
    }
}