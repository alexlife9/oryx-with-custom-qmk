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

// Переменные для обработки двойного клика RU_SHA - 'Ш'
static uint16_t sha_timer = 0;
static uint8_t sha_tap_count = 0;

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
            // Выполняем логику только на слое 0
            if (get_highest_layer(layer_state) != 0) {
                return true; // На других слоях 'Ш' работает как обычно
            }

            if (record->event.pressed) {
                if (sha_tap_count == 0) {
                    // Это первое нажатие. Запускаем таймер и счетчик.
                    sha_timer = timer_read();
                    sha_tap_count = 1;
                } else if (sha_tap_count == 1 && timer_elapsed(sha_timer) < 175) {
                    // Это второе нажатие (двойной клик).
                    sha_tap_count = 2; // Отмечаем, что это был двойной клик
                    tap_code(RU_SHCH); // Сразу печатаем 'Щ'
                    sha_tap_count = 0; // Сбрасываем счётчик
                    return false;      // И блокируем дальнейшую обработку
                } else {
                    // Таймаут истек, это снова первое нажатие.
                    sha_tap_count = 0;
                    sha_timer = timer_read();
                    sha_tap_count = 1;
                }
            } else { // При отпускании
                // Если это было одиночное нажатие и прошло достаточно времени...
                if (sha_tap_count == 1 && timer_elapsed(sha_timer) > 175) {
                    // ...печатаем 'Ш'.
                    tap_code(RU_SHA);
                    sha_tap_count = 0; // Сбрасываем счетчик
                    return false;      // Блокируем дальнейшую обработку
                }
            }
            // ВАЖНО: Блокируем стандартный обработчик, чтобы он не напечатал лишнюю 'Ш'.
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

        default:
            // === ПРАВИЛЬНОЕ МЕСТО ДЛЯ СБРОСА СЧЕТЧИКОВ ===
            // Этот блок сработает для любой другой клавиши.
            if (record->event.pressed) {
                lprn_tap_count = 0;
                sha_tap_count = 0;
            }
            return true;
    }
}
