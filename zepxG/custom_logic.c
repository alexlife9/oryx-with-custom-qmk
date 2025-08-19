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

// Переменные для обработки двойного клика KC_LPRN - '(-()'
static uint16_t lprn_timer = 0;
static uint8_t lprn_tap_count = 0;

// Переменные для обработки двойного клика KC_LCBR - '{-{}'
static uint16_t lcbr_timer = 0;
static uint8_t lcbr_tap_count = 0;

// Переменные для обработки двойного клика KC_LBRC - '[-[]'
#define LBRC_TAPPING_TERM 150 // Настраиваемый тайм-аут
static uint16_t lbrc_timer = 0;

// Переменные для обработки двойного клика RU_SHA - 'Ш-Щ'
#define SHA_TAPPING_TERM 150 // Настраиваемый тайм-аут
static uint16_t sha_timer = 0;

// Переменные для обработки двойного клика RU_SOFT - 'Ь-Ъ'
#define SOFT_TAPPING_TERM 150 // Настраиваемый тайм-аут
static uint16_t soft_timer = 0;

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
    switch (keycode) {

        // Скобка "(" с двойным кликом
        case KC_LPRN:
            if (record->event.pressed) {
                if (lprn_tap_count == 0) {
                    lprn_timer = timer_read();
                    lprn_tap_count = 1;
                } else if (lprn_tap_count == 1 && timer_elapsed(lprn_timer) < 150) {
                    // Двойной клик: печатаем () и ставим курсор внутрь
                    lprn_tap_count = 2;
                    SEND_STRING(")" SS_TAP(X_LEFT));
                    lprn_tap_count = 0;
                    return false;
                } else {
                    // Сброс, если таймаут вышел
                    lprn_tap_count = 0;
                    lprn_timer = timer_read();
                    lprn_tap_count = 1;
                }
            } else { // Отпускание
                if (lprn_tap_count == 1 && timer_elapsed(lprn_timer) > 150) {
                    // Одиночное нажатие: печатаем (
                    SEND_STRING(SS_DELAY(10) "(");
                    lprn_tap_count = 0;
                    return false;
                }
            }
            return true;
        
        // Скобка "{" с двойным кликом
        case KC_LCBR:
            if (record->event.pressed) {
                if (lcbr_tap_count == 0) {
                    lcbr_timer = timer_read();
                    lcbr_tap_count = 1;
                } else if (lcbr_tap_count == 1 && timer_elapsed(lcbr_timer) < 150) {
                    // Двойной клик: печатаем () и ставим курсор внутрь
                    lcbr_tap_count = 2;
                    SEND_STRING("}" SS_TAP(X_LEFT));
                    lcbr_tap_count = 0;
                    return false;
                } else {
                    // Сброс, если таймаут вышел
                    lcbr_tap_count = 0;
                    lcbr_timer = timer_read();
                    lcbr_tap_count = 1;
                }
            } else { // Отпускание
                if (lcbr_tap_count == 1 && timer_elapsed(lcbr_timer) > 150) {
                    // Одиночное нажатие: печатаем (
                    SEND_STRING(SS_DELAY(10) "{");
                    lprn_tap_count = 0;
                    return false;
                }
            }
            return true;
        
        // Скобка "[" с двойным кликом
        case KC_LBRC:
            if (get_highest_layer(layer_state) != 2) {
                return true; // На других слоях не работаем
            }
            if (record->event.pressed) {
                // Проверяем, было ли предыдущее нажатие '[' совсем недавно.
                if (timer_elapsed(lbrc_timer) < LBRC_TAPPING_TERM) {
                    // ДА, это двойное нажатие.
                    // "Исправляем" предыдущее действие.
                    tap_code(KC_BSPC);                // 1. Стираем '['
                    SEND_STRING("[]" SS_TAP(X_LEFT)); // 2. Печатаем [] и ставим курсор внутрь

                    // Сбрасываем таймер, чтобы последовательность не продолжилась.
                    lbrc_timer = 0;
                } else {
                    // НЕТ, это одиночное нажатие.
                    // Действуем немедленно.
                    tap_code(KC_LBRC); // 1. Печатаем '['

                    // Запускаем таймер, чтобы отследить возможное второе нажатие.
                    lbrc_timer = timer_read();
                }
            }
            return false;

        // Буквы Ш-Щ с двойным кликом
        case RU_SHA:
            if (get_highest_layer(layer_state) != 0) {
                return true; // На других слоях не работаем
            }
            if (record->event.pressed) {
                // Проверяем, было ли предыдущее нажатие 'Ш' совсем недавно.
                if (timer_elapsed(sha_timer) < SHA_TAPPING_TERM) {
                    // ДА, это двойное нажатие.
                    // "Исправляем" предыдущее действие.
                    tap_code(KC_BSPC); // 1. Стираем 'Ш'
                    tap_code(RU_SHCH); // 2. Печатаем 'Щ'

                    // Сбрасываем таймер, чтобы последовательность не продолжилась.
                    sha_timer = 0;
                } else {
                    // НЕТ, это одиночное нажатие.
                    // Действуем немедленно.
                    tap_code(RU_SHA); // 1. Печатаем 'Ш'

                    // Запускаем таймер, чтобы отследить возможное второе нажатие.
                    sha_timer = timer_read();
                }
            }
            return false;

        // Буквы Ь-Ъ с двойным кликом
        case RU_SOFT:
            if (get_highest_layer(layer_state) != 0) {
                return true; // На других слоях не работаем
            }
            if (record->event.pressed) {
                // Проверяем, было ли предыдущее нажатие 'Ь' совсем недавно.
                if (timer_elapsed(soft_timer) < SOFT_TAPPING_TERM) {
                    // ДА, это двойное нажатие.
                    // "Исправляем" предыдущее действие.
                    tap_code(RU_SOFT); // 1. Стираем 'Ь'
                    tap_code(RU_HARD); // 2. Печатаем 'Ъ'

                    // Сбрасываем таймер, чтобы последовательность не продолжилась.
                    soft_timer = 0;
                } else {
                    // НЕТ, это одиночное нажатие.
                    // Действуем немедленно.
                    tap_code(RU_SOFT); // 1. Печатаем 'Ь'

                    // Запускаем таймер, чтобы отследить возможное второе нажатие.
                    soft_timer = timer_read();
                }
            }
            return false;    

        case TO(0):
            if (record->event.pressed) layer_move(0);
            return false;

        case TO(1):
            if (record->event.pressed) layer_move(1);
            return false;

        case TT(2):
            return true;  // Разрешаем стандартную обработку

        case OSL(3):
            return true;  // Разрешаем стандартную обработку

        // ------------------------------------------------
        // Всё остальное
        // ------------------------------------------------
        default:
            // Если это отпускание — пропускаем
            if (!record->event.pressed) return true;
            return true;
    }
}
