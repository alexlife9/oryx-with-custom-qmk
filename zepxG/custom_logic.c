// --- custom_logic.c ---

// ========================================================================

// 1. найди функцию bool process_record_user(...) 

// 2. вставь так: 

// #include "custom_logic.c"                                         // это первое добавление
// bool process_record_user(uint16_t keycode, keyrecord_t *record) { // это оригинальная строка
//  if (!process_record_custom(keycode, record)) { return false; }   // это второе добавление

// ========================================================================
    

// Этот файл содержит всю кастомную логику для умного переключения слоев и языка.

// Вспомогательная функция, чтобы определить, "активен" ли сейчас русский язык.
// Мы считаем, что язык русский, если текущий слой - 0.
bool is_russian_language_active(void) {
    return biton32(layer_state) == 0;
}

// Наша главная кастомная функция-обработчик.
// Она перехватывает нажатия кнопок до того, как их обработает стандартная логика Oryx.
bool process_record_custom(uint16_t keycode, keyrecord_t *record) {
    // Мы реагируем только на нажатия, а не на отпускания клавиш.
    if (!record->event.pressed) {
        return true; 
    }

    switch (keycode) {
        case TO(0): // Цель: перейти на слой 0 и включить русский язык
            // Если сейчас не активен русский язык, переключаем его в ОС.
            if (!is_russian_language_active()) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            // Выполняем смену слоя САМОСТОЯТЕЛЬНО.
            layer_move(0);
            // Говорим QMK, что мы все сделали, и дальнейшая обработка этой кнопки не нужна.
            return false; 

        case TO(1): // Цель: перейти на слой 1 и включить английский язык
            // Если сейчас активен русский язык, переключаем его в ОС.
            if (is_russian_language_active()) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            // Выполняем смену слоя САМОСТОЯТЕЛЬНО.
            layer_move(1);
            // Говорим QMK, что мы все сделали, и дальнейшая обработка этой кнопки не нужна.
            return false;

        default:
            // Это не TO(0) и не TO(1). Мы не обрабатываем эту кнопку.
            // Пусть ее обрабатывает стандартная логика Oryx.
            return true;
    }
}