// ========================================================================

// в файле keymap.c сделать изменения:

/* ==1== добавить в начало файла
void user_render_splash_effect(void);

*/

/* ==2== найти (строка 200) rgb_matrix_indicators_user и внизу после 'default:' добавить это:
      default:
        if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
          rgb_matrix_set_color_all(0, 0, 0);
        }
    }
  }

  // рисуем эффект "Широкой капли" поверх
  user_render_splash_effect();

  return true;

*/

/* ==3== найти (строка 320) bool process_record_user и добавить:
#include "custom_logic.c"                                            // перед строкой
bool process_record_user(uint16_t keycode, keyrecord_t *record) {    // это оригинальная строка bool process_record_user
    if (!process_record_custom(keycode, record)) { return false; }   // после строки

*/

// ========================================================================

#include "quantum.h" // Для get_highest_layer, layer_state_t
#include "timer.h"   // Для timer_read и timer_elapsed

// === ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ ===
static int8_t active_splash_led = -1; // Номер нажатого диода
static uint16_t splash_timer = 0;     // Таймер
static uint8_t center_x = 0;          // Координата X нажатия
static uint8_t center_y = 0;          // Координата Y нажатия

// === ЭФФЕКТ КАПЛИ С СОСЕДЯМИ (REACTIVE WIDE) ===
void user_render_splash_effect(void) {
    // Если эффекта нет - выходим сразу, чтобы не грузить проц
    if (active_splash_led == -1) return;

    // Параметры эффекта
    uint16_t duration = 300;     // Длительность (мс)
    uint8_t radius = 25;         // Радиус "пятна" (10 - одна клавиша, 40 - пятно будет больше)

    uint16_t elapsed = timer_elapsed(splash_timer);

    if (elapsed < duration) {
        // Вычисляем текущую яркость (от 255 до 0)
        uint8_t brightness = 255 - (255 * elapsed / duration);

        // Если уже почти погасло - выключаем, чтобы не считать лишнее
        if (brightness < 1) {
            active_splash_led = -1;
            return;
        }

        // ПРОБЕГАЕМ ПО ВСЕМ СВЕТОДИОДАМ
        for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
            // Берем координаты текущего проверяемого диода
            uint8_t x = g_led_config.point[i].x;
            uint8_t y = g_led_config.point[i].y;

            // Простая математика расстояния (без корней, чтобы не тормозило)
            // abs() - это модуль числа
            // Используем обычный int, он есть всегда
            int dist_x = abs(x - center_x);
            int dist_y = abs(y - center_y);

            // Если диод внутри радиуса
            if (dist_x + dist_y < radius) {
                // Рисуем его белым с текущей яркостью
                rgb_matrix_set_color(i, brightness, brightness, brightness);
            }
        }
    } else {
        // Время вышло
        active_splash_led = -1;
    }
}

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

// Она перехватывает нажатия кнопок до того, как их обработает стандартная логика Oryx.
// Логика переключения языка теперь полностью в layer_state_set_user, так что здесь только управление слоями.
bool process_record_custom(uint16_t keycode, keyrecord_t *record) {

    // 1. ЛОВИМ КООРДИНАТЫ ДЛЯ ЭФФЕКТА
    if (record->event.pressed) {
        uint8_t row = record->event.key.row;
        uint8_t col = record->event.key.col;
        int8_t led = g_led_config.matrix_co[row][col];
        
        if (led != -1) {
            active_splash_led = led;
            center_x = g_led_config.point[led].x;
            center_y = g_led_config.point[led].y;
            splash_timer = timer_read();
        }
    }

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
                    SEND_STRING("()"SS_TAP(X_LEFT));  // 2. Печатаем () и ставим курсор внутрь

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
                    SEND_STRING("{}"SS_TAP(X_LEFT));  // 2. Печатаем {} и ставим курсор внутрь

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
                    SEND_STRING("[]"SS_TAP(X_LEFT));  // 2. Печатаем [] и ставим курсор внутрь

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
                    // "Исправляем" предыдущее действие:
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

        // Замена # на № с двойным кликом
        case ST_MACRO_0:
            if (record->event.pressed) {

                // Проверяем, было ли предыдущее нажатие 
                if (timer_elapsed(ctlkca_timer) < CUSTOM_TAPPING_TERM) {
                    // ДА, это двойное нажатие.
                    // "Исправляем" предыдущее действие:
                    tap_code(KC_BSPC);  // стираем '#'
                    tap_code16(RU_NUM); // и печатаем '№'

                    // Сбрасываем таймер, чтобы последовательность не продолжилась.
                    ctlkca_timer = 0;
                } else {
                    // НЕТ, это одиночное нажатие.
                    // Действуем немедленно.
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_3) SS_TAP(X_KP_5) SS_TAP(X_LEFT_ALT))); // печатаем '#'

                    // Запускаем таймер, чтобы отследить возможное второе нажатие.
                    ctlkca_timer = timer_read();
                }
            }
            return false;

        // Замена $ на ₽ с двойным кликом
        case ST_MACRO_1:
            if (record->event.pressed) {

                // Проверяем, было ли предыдущее нажатие LCTL(KC_A)
                if (timer_elapsed(ctlkca_timer) < CUSTOM_TAPPING_TERM) {
                    // ДА, это двойное нажатие.
                    // "Исправляем" предыдущее действие:
                    tap_code(KC_BSPC);  // стираем '$'
                    tap_code16(RU_RUBL); // и печатаем '₽'

                    // Сбрасываем таймер, чтобы последовательность не продолжилась.
                    ctlkca_timer = 0;
                } else {
                    // НЕТ, это одиночное нажатие.
                    // Действуем немедленно.
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_3) SS_TAP(X_KP_6) SS_TAP(X_LEFT_ALT) )); // печатаем '$'

                    // Запускаем таймер, чтобы отследить возможное второе нажатие.
                    ctlkca_timer = timer_read();
                }
            }
            return false;    
/*
        // Запятая с пробелом при клике / Слой 4 при удержании
            case ST_MACRO_4:
            
            if (record->event.pressed) {
                // === НАЖАТИЕ ===
                macro4_timer = timer_read();
                layer_on(4); // Включаем слой 4
            } 
            else {
                // === ОТПУСКАНИЕ ===
                layer_off(4); // Выключаем слой 4

                // Проверяем, был ли это короткий клик (меньше 180мс)
                if (timer_elapsed(macro4_timer) < CUSTOM_TAPPING_TERM) {
                    
                    // Узнаем текущий слой (так как 4-й мы уже выключили, будет 0 или 1)
                    uint8_t current_layer = get_highest_layer(layer_state);

                    if (current_layer == 0) {
                        // Русский: , + пробел
                        tap_code16(RU_COMM);
                        tap_code16(KC_SPACE);
                    } 
                    else {
                        // Английский: , + пробел
                        tap_code16(KC_COMMA);
                        tap_code16(KC_SPACE);
                    }
                }
            }
            
            return false;
*/

        // печатаем 'ú-у́' в зависимости от слоя из которого пришли 
        case ST_MACRO_10: // слой [3]: строка 2, столбец 4
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
        case ST_MACRO_11: // слой [3]: строка 2, столбец 6
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

        // печатаем 'ы́'
        case ST_MACRO_12: // слой [3]: строка 3, столбец 3
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

        // печатаем 'á-á' в зависимости от слоя из которого пришли 
        case ST_MACRO_14: // слой [3]: строка 3, столбец 5
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

        // печатаем 'я́'
        case ST_MACRO_15: // слой [0]: строка 4, столбец 2
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

        // печатаем 'í-и́' в зависимости от слоя из которого пришли 
        case ST_MACRO_16:  // слой [3]: строка 4, столбец 6
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

        // Обработка ñ/Ñ в зависимости от Caps Lock
        case ST_MACRO_17:
            if (record->event.pressed) {
                
                // Проверяем, включен ли светодиод Caps Lock
                if (host_keyboard_led_state().caps_lock) {
                    // Caps Lock ВКЛЮЧЕН -> Печатаем заглавную 'Ñ' (Alt + 0209)
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_0) SS_TAP(X_KP_9) SS_TAP(X_LEFT_ALT)));
                } else {
                    // Caps Lock ВЫКЛЮЧЕН -> Печатаем строчную 'ñ' (Alt + 0241)
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_1) SS_TAP(X_LEFT_ALT)));
                }
                
                return false;
            }
            return true;

        // печатаем 'ó-ó' в зависимости от слоя из которого пришли 
        case ST_MACRO_18: // слой [3] (правая часть): строка 3, столбец 3
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

        // печатаем 'да' на 4-м слое 
        case ST_MACRO_21: // слой [4]: строка 5, столбец 3
        if (record->event.pressed) {
            // Работаем только на 4-м слое
            if (get_highest_layer(layer_state) == 4) {

                // узнаём слой из которого пришли
                if (last_base_layer == 0) {
                    // Если КОНТЕКСТ БЫЛ РУССКИЙ, то будем печатать русскую 'и́'
                    switch_lang(); // переключаем язык на русский
                    is_russian_lang_active = true; // активируем флаг

                    // Печатаем 'да' и сразу прожимаем энтер
                    SEND_STRING(SS_TAP(X_L) SS_TAP(X_F) SS_DELAY(100) SS_TAP(X_ENTER));

                    switch_lang(); // переключаем язык обратно на английский
                    is_russian_lang_active = false; // выключаем флаг
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
