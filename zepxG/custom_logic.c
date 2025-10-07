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

// Переменная для отслеживания последнего активного базового слоя (0=Рус, 1=Англ)
static uint8_t last_base_layer = 0;

// Отправляет в ОС комбинацию клавиш для переключения языка (Ctrl+Shift)
void switch_lang(void) {
    register_code(KC_LCTL);
    register_code(KC_LSFT);
    unregister_code(KC_LSFT);
    unregister_code(KC_LCTL);
}

// Callback функция для обработки изменений состояния слоёв.
// Вызывается автоматически QMK каждый раз, когда меняется активный слой (например, при активации/деактивации через TT, OSL, TO).
layer_state_t layer_state_set_user(layer_state_t state) {

    uint8_t highest_layer = get_highest_layer(state);
    // Запоминаем базовый слой, только если мы переключились на 0 или 1
    if (highest_layer == 0 || highest_layer == 1) {
        last_base_layer = highest_layer;
    }

    // Определяем желаемый язык: русский, если наивысший слой == 0, иначе английский.
    bool desired_russian = (get_highest_layer(state) == 0);

    // Если текущий язык не совпадает с желаемым, переключаем его в ОС и обновляем флаг.
    if (is_russian_lang_active != desired_russian) {
        switch_lang();
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


        // !! ВНИМАТЕЛЬНО – на третьем слое номер макроса может меняться!!

        // печатаем 'ы́'
        case ST_MACRO_13:
            if (record->event.pressed) {

                // Проверяем, что мы ТОЧНО на 3-м слое
                if (get_highest_layer(layer_state) == 3) {
                    
                    // Временно переключаемся на русский язык
                    switch_lang();
                    is_russian_lang_active = true; // Важно! Синхронизируем наш флаг

                    // Печатаем 'ы'
                    tap_code16(RU_YERU);

                    // Добавляем ударение (Unicode U+0301)
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_PLUS) SS_TAP(X_KP_0) SS_TAP(X_KP_3) SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_LEFT_ALT) ));

                    // Возвращаемся на английский, как и должно быть на 3-м слое
                    switch_lang();
                    is_russian_lang_active = false;

                    return false;
                }
            }
            return true;

        // печатаем 'я́'
        case ST_MACRO_16:
            if (record->event.pressed) {

                // Проверяем, что мы ТОЧНО на 3-м слое
                if (get_highest_layer(layer_state) == 3) {
                    
                    // Временно переключаемся на русский язык
                    switch_lang();
                    is_russian_lang_active = true; // Важно! Синхронизируем наш флаг

                    // Печатаем 'я'
                    tap_code16(RU_YA);

                    // Добавляем ударение (Unicode U+0301)
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_PLUS) SS_TAP(X_KP_0) SS_TAP(X_KP_3) SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_LEFT_ALT) ));


                    // Возвращаемся на английский, как и должно быть на 3-м слое
                    switch_lang();
                    is_russian_lang_active = false; // Синхронизируем флаг обратно

                    return false;
                }
            }
            return true;    

        // печатаем 'ú-у́' в зависимости от слоя из которого пришли 
        case ST_MACRO_11:
        if (record->event.pressed) {
            // Работаем только на 3-м слое
            if (get_highest_layer(layer_state) == 3) {

                // узнаём слой из которого пришли
                if (last_base_layer == 0) {
                    // Если КОНТЕКСТ БЫЛ РУССКИЙ, то будем печатать русскую 'у́'
                    switch_lang(); // переключаем язык на русский
                    is_russian_lang_active = true; // активируем флаг

                    // Печатаем 'у'
                    tap_code16(RU_U); 

                    // Добавляем ударение (Unicode U+0301)
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_PLUS) SS_TAP(X_KP_0) SS_TAP(X_KP_3) SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_LEFT_ALT) ));

                    switch_lang(); // переключаем язык обратно на английский
                    is_russian_lang_active = false; // выключаем флаг

                } else { // Если last_base_layer был 1 или любой другой, 
                    // то КОНТЕКСТ БЫЛ АНГЛИЙСКИЙ и сразу будем печатать английскую 'ú' (Alt + 0250)
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_5) SS_TAP(X_KP_0) SS_TAP(X_LEFT_ALT) ));
                }
                
                return false;
            }
        }
        return true;

        // печатаем 'é-é' в зависимости от слоя из которого пришли 
        case ST_MACRO_12:
        if (record->event.pressed) {
            // Работаем только на 3-м слое
            if (get_highest_layer(layer_state) == 3) {

                // узнаём слой из которого пришли
                if (last_base_layer == 0) {
                    // Если КОНТЕКСТ БЫЛ РУССКИЙ, то будем печатать русскую 'é'
                    switch_lang(); // переключаем язык на русский
                    is_russian_lang_active = true; // активируем флаг

                    // Печатаем 'е'
                    tap_code16(RU_IE); 

                    // Добавляем ударение (Unicode U+0301)
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_PLUS) SS_TAP(X_KP_0) SS_TAP(X_KP_3) SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_LEFT_ALT) ));

                    switch_lang(); // переключаем язык обратно на английский
                    is_russian_lang_active = false; // выключаем флаг

                } else { // Если last_base_layer был 1 или любой другой, 
                    // то КОНТЕКСТ БЫЛ АНГЛИЙСКИЙ и сразу будем печатать английскую 'é' (Alt + 0233)
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_3) SS_TAP(X_LEFT_ALT) ));
                }
                
                return false;
            }
        }
        return true;

        // печатаем 'á-á' в зависимости от слоя из которого пришли 
        case ST_MACRO_15:
        if (record->event.pressed) {
            // Работаем только на 3-м слое
            if (get_highest_layer(layer_state) == 3) {

                // узнаём слой из которого пришли
                if (last_base_layer == 0) {
                    // Если КОНТЕКСТ БЫЛ РУССКИЙ, то будем печатать русскую 'á'
                    switch_lang(); // переключаем язык на русский
                    is_russian_lang_active = true; // активируем флаг

                    // Печатаем 'а'
                    tap_code16(RU_A); 

                    // Добавляем ударение (Unicode U+0301)
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_PLUS) SS_TAP(X_KP_0) SS_TAP(X_KP_3) SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_LEFT_ALT) ));

                    switch_lang(); // переключаем язык обратно на английский
                    is_russian_lang_active = false; // выключаем флаг

                } else { // Если last_base_layer был 1 или любой другой, 
                    // то КОНТЕКСТ БЫЛ АНГЛИЙСКИЙ и сразу будем печатать английскую 'á' (Alt + 0225)
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_2) SS_TAP(X_KP_5) SS_TAP(X_LEFT_ALT) ));
                }
                
                return false;
            }
        }
        return true;

        // печатаем 'ó-ó' в зависимости от слоя из которого пришли 
        case ST_MACRO_19:
        if (record->event.pressed) {
            // Работаем только на 3-м слое
            if (get_highest_layer(layer_state) == 3) {

                // узнаём слой из которого пришли
                if (last_base_layer == 0) {
                    // Если КОНТЕКСТ БЫЛ РУССКИЙ, то будем печатать русскую 'ó'
                    switch_lang(); // переключаем язык на русский
                    is_russian_lang_active = true; // активируем флаг

                    // Печатаем 'о'
                    tap_code16(RU_O); 

                    // Добавляем ударение (Unicode U+0301)
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_PLUS) SS_TAP(X_KP_0) SS_TAP(X_KP_3) SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_LEFT_ALT) ));

                    switch_lang(); // переключаем язык обратно на английский
                    is_russian_lang_active = false; // выключаем флаг

                } else { // Если last_base_layer был 1 или любой другой, 
                    // то КОНТЕКСТ БЫЛ АНГЛИЙСКИЙ и сразу будем печатать английскую 'ó' (Alt + 0243)
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_3) SS_TAP(X_LEFT_ALT) ));
                }
                
                return false;
            }
        }
        return true;

        // печатаем 'í-и́' в зависимости от слоя из которого пришли 
        case ST_MACRO_17:
        if (record->event.pressed) {
            // Работаем только на 3-м слое
            if (get_highest_layer(layer_state) == 3) {

                // узнаём слой из которого пришли
                if (last_base_layer == 0) {
                    // Если КОНТЕКСТ БЫЛ РУССКИЙ, то будем печатать русскую 'и́'
                    switch_lang(); // переключаем язык на русский
                    is_russian_lang_active = true; // активируем флаг

                    // Печатаем 'и'
                    tap_code16(RU_I); 

                    // Добавляем ударение (Unicode U+0301)
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_PLUS) SS_TAP(X_KP_0) SS_TAP(X_KP_3) SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_LEFT_ALT) ));

                    switch_lang(); // переключаем язык обратно на английский
                    is_russian_lang_active = false; // выключаем флаг

                } else { // Если last_base_layer был 1 или любой другой, 
                    // то КОНТЕКСТ БЫЛ АНГЛИЙСКИЙ и сразу будем печатать английскую 'í' (Alt + 0237)
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_7) SS_TAP(X_LEFT_ALT) ));
                }
                
                return false;
            }
        }
        return true;

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
