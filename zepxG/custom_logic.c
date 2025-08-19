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

// Переменные для обработки двойного клика KC_LPRN - '('
static uint16_t lprn_timer = 0;
static uint8_t lprn_tap_count = 0;

// Переменные для обработки двойного тапа RU_SHA
static uint16_t sha_timer = 0;
static bool sha_double_tap = false;

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
                } else if (lprn_tap_count == 1 && timer_elapsed(lprn_timer) < 175) {
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
                if (lprn_tap_count == 1 && timer_elapsed(lprn_timer) > 175) {
                    // Одиночное нажатие: печатаем (
                    SEND_STRING(SS_DELAY(10) "(");
                    lprn_tap_count = 0;
                    return false;
                }
            }
            return true;

        // Буквы Ш-Щ с двойным кликом
        case RU_SHA:
            if (record->event.pressed) {
                // Нажатие клавиши
                if (timer_elapsed(sha_timer) < 175) {
                    // Двойной тап
                    sha_double_tap = true;
                } else {
                    // Одиночный тап или сброс
                    sha_double_tap = false;
                    sha_timer = timer_read();
                }
            } else {
                // Отпускание клавиши
                if (sha_double_tap) {
                    // Двойной тап: отправляем RU_SHCH ('щ')
                    tap_code16(RU_SHCH);
                } else if (timer_elapsed(sha_timer) > 175) {
                    // Одиночный тап: отправляем RU_SHA ('ш')
                    tap_code16(RU_SHA);
                }
                sha_double_tap = false;
            }
            return false; // Блокируем стандартную обработку
        default:
            return true; // Обрабатываем другие клавиши стандартно

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
