// ========================================================================

// 1. найди функцию bool process_record_user(...) 
// 2. вставь так: 

//#include "custom_logic.c"                                            // это первое добавление
//bool process_record_user(uint16_t keycode, keyrecord_t *record) {    // это оригинальная строка bool process_record_user
//    if (!process_record_custom(keycode, record)) { return false; }   // это второе добавление

// ========================================================================

#include "quantum.h" // Для get_highest_layer, layer_state_t
#include "timer.h"   // Для timer_read и timer_elapsed

static bool is_russian_lang_active = true;

#define CUSTOM_TAPPING_TERM 180 // Настраиваемый тайм-аут

// Переменные для обработки двойного клика KC_DQUO: "␣"
static uint16_t dquo_timer = 0;

// Переменные для обработки двойного клика KC_LPRN: (␣)
static uint16_t lprn_timer = 0;

// Переменные для обработки двойного клика KC_LCBR: {␣}
static uint16_t lcbr_timer = 0;

// Переменные для обработки двойного клика KC_LBRC: [␣]
static uint16_t lbrc_timer = 0;

// Переменные для обработки двойного клика KC_LABK: <!--␣-->
static uint16_t labk_timer = 0;

// Переменные для обработки двойного клика KC_KP_ASTERISK: *-•
static uint16_t asterisk_timer = 0;

// Переменные для обработки двойного клика KC_KP_MINUS: - –
static uint16_t minus_timer = 0;

// Переменные для обработки двойного клика LCTL(KC_A): добавляем KC_С
static uint16_t ctlkca_timer = 0;

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

        // Кавычки " с двойным кликом на рус слое
        case RU_DQUO:
            if (get_highest_layer(layer_state) != 0) {
                return true; // На других слоях не работаем
            }
            if (record->event.pressed) {
                // Проверяем, было ли предыдущее нажатие " совсем недавно.
                if (timer_elapsed(dquo_timer) < CUSTOM_TAPPING_TERM) {
                    // ДА, это двойное нажатие.
                    // "Исправляем" предыдущее действие.
                    tap_code16(RU_DQUO);   // печатаем вторую кавычку
                    tap_code16(KC_LEFT);   // и ставим курсор внутри

                    // Сбрасываем таймер, чтобы последовательность не продолжилась.
                    dquo_timer = 0;
                } else {
                    // НЕТ, это одиночное нажатие.
                    // Действуем немедленно.
                    tap_code16(RU_DQUO); // Печатаем "

                    // Запускаем таймер, чтобы отследить возможное второе нажатие.
                    dquo_timer = timer_read();
                }
            }
            return false;

        // Кавычки " с двойным кликом на англ слое
        case KC_DQUO:
            if (get_highest_layer(layer_state) != 1 && get_highest_layer(layer_state) != 2) {
                return true; // На других слоях не работаем
            }
            if (record->event.pressed) {
                // Проверяем, было ли предыдущее нажатие " совсем недавно.
                if (timer_elapsed(dquo_timer) < CUSTOM_TAPPING_TERM) {
                    // ДА, это двойное нажатие.
                    // "Исправляем" предыдущее действие.
                    tap_code(KC_BSPC);                  // 1. Стираем "
                    SEND_STRING("\"\"" SS_TAP(X_LEFT)); // 2. печатаем "" и ставим курсор внутри

                    // Сбрасываем таймер, чтобы последовательность не продолжилась.
                    dquo_timer = 0;
                } else {
                    // НЕТ, это одиночное нажатие.
                    // Действуем немедленно.
                    tap_code16(KC_DQUO); // Печатаем "

                    // Запускаем таймер, чтобы отследить возможное второе нажатие.
                    dquo_timer = timer_read();
                }
            }
            return false;

        // Скобка "(" с двойным кликом
        case KC_LPRN:
            if (record->event.pressed) {
                // Проверяем, было ли предыдущее нажатие '(' совсем недавно.
                if (timer_elapsed(lprn_timer) < CUSTOM_TAPPING_TERM) {
                    // ДА, это двойное нажатие.
                    // "Исправляем" предыдущее действие.
                    tap_code(KC_BSPC);                // 1. Стираем (
                    SEND_STRING("()"SS_TAP(X_LEFT)); // 2. Печатаем () и ставим курсор внутрь

                    // Сбрасываем таймер, чтобы последовательность не продолжилась.
                    lprn_timer = 0;
                } else {
                    // НЕТ, это одиночное нажатие.
                    // Действуем немедленно.
                    tap_code16(KC_LPRN); // Печатаем '('

                    // Запускаем таймер, чтобы отследить возможное второе нажатие.
                    lprn_timer = timer_read();
                }
            }
            return false;

        // Скобка "{" с двойным кликом
        case KC_LCBR:
            if (get_highest_layer(layer_state) != 2) {
                return true; // На других слоях не работаем
            }
            if (record->event.pressed) {
                // Проверяем, было ли предыдущее нажатие '[' совсем недавно.
                if (timer_elapsed(lcbr_timer) < CUSTOM_TAPPING_TERM) {
                    // ДА, это двойное нажатие.
                    // "Исправляем" предыдущее действие.
                    tap_code(KC_BSPC);                // 1. Стираем {
                    SEND_STRING("{}"SS_TAP(X_LEFT)); // 2. Печатаем {} и ставим курсор внутрь

                    // Сбрасываем таймер, чтобы последовательность не продолжилась.
                    lcbr_timer = 0;
                } else {
                    // НЕТ, это одиночное нажатие.
                    // Действуем немедленно.
                    tap_code16(KC_LCBR); // Печатаем '{'

                    // Запускаем таймер, чтобы отследить возможное второе нажатие.
                    lcbr_timer = timer_read();
                }
            }
            return false;

        // Скобка "[" с двойным кликом
        case KC_LBRC:
            if (get_highest_layer(layer_state) != 2) {
                return true; // На других слоях не работаем
            }
            if (record->event.pressed) {
                // Проверяем, было ли предыдущее нажатие '[' совсем недавно.
                if (timer_elapsed(lbrc_timer) < CUSTOM_TAPPING_TERM) {
                    // ДА, это двойное нажатие.
                    // "Исправляем" предыдущее действие.
                    tap_code(KC_BSPC);                // 1. Стираем [
                    SEND_STRING("[]"SS_TAP(X_LEFT)); // 2. Печатаем [] и ставим курсор внутрь

                    // Сбрасываем таймер, чтобы последовательность не продолжилась.
                    lbrc_timer = 0;
                } else {
                    // НЕТ, это одиночное нажатие.
                    // Действуем немедленно.
                    tap_code(KC_LBRC); // Печатаем '['

                    // Запускаем таймер, чтобы отследить возможное второе нажатие.
                    lbrc_timer = timer_read();
                }
            }
            return false;

        // Скобка угловая для комментария в РНР '<' с двойным кликом для <!-- -->
        case KC_LABK:
            if (record->event.pressed) {
                // Проверяем, было ли предыдущее нажатие '<' совсем недавно.
                if (timer_elapsed(labk_timer) < CUSTOM_TAPPING_TERM) {
                    // ДА, это двойное нажатие.
                    // "Исправляем" предыдущее действие.
                    tap_code(KC_BSPC);                // 1. Стираем <
                    SEND_STRING(
                        SS_LALT(SS_TAP(X_KP_6) SS_TAP(X_KP_0) SS_TAP(X_LEFT_ALT) )
                        "!----"
                        SS_LALT(SS_TAP(X_KP_6) SS_TAP(X_KP_2) SS_TAP(X_LEFT_ALT) )
                        SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT)); // 2. Печатаем <!-- --> и ставим курсор внутрь

                    // Сбрасываем таймер, чтобы последовательность не продолжилась.
                    labk_timer = 0;
                } else {
                    // НЕТ, это одиночное нажатие.
                    // Действуем немедленно.
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_6) SS_TAP(X_KP_0) SS_TAP(X_LEFT_ALT) )); // Печатаем '<'

                    // Запускаем таймер, чтобы отследить возможное второе нажатие.
                    labk_timer = timer_read();
                }
            }
            return false;   
            
        // Звездочка '*' с двойным кликом
        case KC_KP_ASTERISK:
            if (record->event.pressed) {
                // Проверяем, было ли предыдущее нажатие '*' совсем недавно.
                if (timer_elapsed(asterisk_timer) < CUSTOM_TAPPING_TERM) {
                    // ДА, это двойное нажатие.
                    // "Исправляем" предыдущее действие.
                    tap_code(KC_BSPC);                // 1. Стираем '*'
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_4) SS_TAP(X_KP_9) SS_TAP(X_LEFT_ALT) )); // 2. Печатаем '•'

                    // Сбрасываем таймер, чтобы последовательность не продолжилась.
                    asterisk_timer = 0;
                } else {
                    // НЕТ, это одиночное нажатие.
                    // Действуем немедленно.
                    tap_code(KC_KP_ASTERISK); // Печатаем '*'

                    // Запускаем таймер, чтобы отследить возможное второе нажатие.
                    asterisk_timer = timer_read();
                }
            }
            return false;

        // Среднее тире '–' по двойныму клику
        case KC_KP_MINUS:
            if (record->event.pressed) {
                // Проверяем, было ли предыдущее нажатие '-' совсем недавно.
                if (timer_elapsed(minus_timer) < CUSTOM_TAPPING_TERM) {
                    // ДА, это двойное нажатие.
                    // "Исправляем" предыдущее действие.
                    tap_code(KC_BSPC);                // 1. Стираем '-'
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_5) SS_TAP(X_KP_0) SS_TAP(X_LEFT_ALT) )); // 2. Печатаем '–'

                    // Сбрасываем таймер, чтобы последовательность не продолжилась.
                    minus_timer = 0;
                } else {
                    // НЕТ, это одиночное нажатие.
                    // Действуем немедленно.
                    tap_code(KC_KP_MINUS); // Печатаем '-'

                    // Запускаем таймер, чтобы отследить возможное второе нажатие.
                    minus_timer = timer_read();
                }
            }
            return false;

        // По двойныму клику LCTL(KC_A): добавляем KC_С
        case LCTL(KC_A):
            if (record->event.pressed) {
                // Проверяем, было ли предыдущее нажатие LCTL(KC_A)
                if (timer_elapsed(ctlkca_timer) < CUSTOM_TAPPING_TERM) {
                    // ДА, это двойное нажатие.
                    // Сразу добавляем копирование:
                    tap_code16(LCTL(KC_C));

                    // Сбрасываем таймер, чтобы последовательность не продолжилась.
                    ctlkca_timer = 0;
                } else {
                    // НЕТ, это одиночное нажатие.
                    // Действуем немедленно.
                    tap_code16(LCTL(KC_A)); // выполняем LCTL(KC_A)

                    // Запускаем таймер, чтобы отследить возможное второе нажатие.
                    ctlkca_timer = timer_read();
                }
            }
            return false;

/*            
        // Добавляем букву Ы с ударением на третьем слое - номер макроса может меняться! 
        case ST_MACRO_13:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_KP_PLUS) SS_TAP(X_KP_0) SS_TAP(X_KP_4) SS_TAP(X_KP_4) SS_TAP(KC_B) ));  
                SEND_STRING(SS_LALT(SS_TAP(X_KP_PLUS) SS_TAP(X_KP_0) SS_TAP(X_KP_3) SS_TAP(X_KP_0) SS_TAP(X_KP_1) )); 
            }
            return false;
*/

        // Добавляем букву Ы с ударением. На третьем слое - номер макроса может меняться! 
        case ST_MACRO_16:
            if (record->event.pressed) {
                //сначала меняем язык на русский
                    if (is_russian_lang_active != desired_russian) {
                        register_code(KC_LCTL);
                        register_code(KC_LSFT);
                        unregister_code(KC_LSFT);
                        unregister_code(KC_LCTL);
                        is_russian_lang_active = desired_russian;
                    }
                // Печатаем 'ы'
                tap_code(RU_YERU);

                // Добавляем ударение (Unicode U+0301)
                register_code(KC_LALT);
                tap_code(KC_KP_PLUS);
                tap_code(KC_KP_0);
                tap_code(KC_KP_3);
                tap_code(KC_KP_0);
                tap_code(KC_KP_1);
                unregister_code(KC_LALT);
            }
            return false;

        case TO(0):
            if (record->event.pressed) layer_move(0);
            return false;

        case TO(1):
            if (record->event.pressed) layer_move(1);
            return false;

        case TG(2):
            return true;  // Разрешаем стандартную обработку

        case OSL(3):
            return true;  // Разрешаем стандартную обработку

        default:
            // Если это отпускание — пропускаем
            if (!record->event.pressed) return true;
            return true;
    }
}
