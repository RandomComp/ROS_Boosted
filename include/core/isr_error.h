#ifndef _RANDOM_OS_FATAL_ERROR_H
#define _RANDOM_OS_FATAL_ERROR_H

#include "core/types.h"

#include "core/isr_error_types.h"

/*
@brief Опасная функция, лучше в пользователском коде использовать Exception

@param errorType Тип 
*/

/// @brief Функция, которая вызывает исключение ISR с указанным типом ошибки, дополнительно надо указать сообщение объясняющую причину возникновения ошибки.
/// @param errorType 
/// @param why 
void ISR_throw(ISR_ErrorTypes errorType, CP437_CharacterCode* why);

#endif