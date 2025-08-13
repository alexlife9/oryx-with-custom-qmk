// ========================================================================

// 1. найди функцию bool process_record_user(...) 
// 2. вставь так: 

//#include "custom_logic.c"                                            // это первое добавление
//bool process_record_user(uint16_t keycode, keyrecord_t *record) {    // это оригинальная строка
//    if (!process_record_custom(keycode, record)) { return false; }   // это второе добавление

// ========================================================================
    

#include "quantum.h" // Для get_highest_layer, layer_state_t, rgb_matrix
#include "timer.h"   // Для timer_read и timer_elapsed

static bool is_russian_lang_active = true;

// Переменные для отслеживания состояния OSM(MOD_LSFT)
static bool shift_held = false;
static uint16_t shift_timer = 0;

// --- Глобальная переменная для отслеживания языка ---
// true = русский, false = английский.
// По умолчанию при включении клавиатуры считаем, что активен русский язык (слой 0).

// Массив для отслеживания времени нажатия каждой клавиши (до 72 LED для Moonlander)
static uint16_t key_press_timers[RGB_MATRIX_LED_COUNT] = {0};
// Длительность вспышки в миллисекундах
#define FLASH_DURATION 100
// Цвет вспышки (белый: RGB 255,255,255)
#define FLASH_COLOR_R 255
#define FLASH_COLOR_G 255
#define FLASH_COLOR_B 255

// Внешняя функция из keymap.c для восстановления цвета слоя
extern void set_layer_color(int layer);

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

// Кастомная функция для обработки RGB индикаторов
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Вызываем существующую функцию для установки цветов слоя
    if (!rawhid_state.rgb_control && !keyboard_config.disable_layer_led) {
        set_layer_color(biton32(layer_state));
    }

    // Проверяем каждую клавишу на активную вспышку
    for (uint8_t i = led_min; i <= led_max; i++) {
        if (key_press_timers[i] != 0 && timer_elapsed(key_press_timers[i]) < FLASH_DURATION) {
            // Клавиша всё ещё в состоянии вспышки
            rgb_matrix_set_color(i, FLASH_COLOR_R, FLASH_COLOR_G, FLASH_COLOR_B);
        } else {
            // Сбрасываем таймер, чтобы цвет слоя восстановился
            key_press_timers[i] = 0;
        }
    }
    return true;
}

// Наша главная кастомная функция-обработчик.
// Она перехватывает нажатия кнопок до того, как их обработает стандартная логика Oryx.
// Логика переключения языка теперь полностью в layer_state_set_user, так что здесь только управление слоями.
bool process_record_custom(uint16_t keycode, keyrecord_t *record) {

        // Получаем индекс LED для нажатой клавиши
    uint8_t led_index = g_led_config.matrix_co[record->event.key.row][record->event.key.col];

    // Если клавиша имеет LED и нажата, запускаем вспышку
    if (led_index != NO_LED && record->event.pressed) {
        key_press_timers[led_index] = timer_read();
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