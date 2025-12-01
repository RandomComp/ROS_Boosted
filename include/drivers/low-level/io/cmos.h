#ifndef _CMOS_H
#define _CMOS_H

#include "core/types.h"

#include "core/time.h"

#define CMOS_ADDRESS_PORT 	0x70

#define CMOS_DATA_PORT 		0x71

typedef uint8 Register;

// CMOS коды для чтения/записи значений.
typedef enum UniversalCMOSCode {
	CMOS_RTC_SECONDS, 					// Получение значения секунд. 					                                        Чтение и запись разрешены.
	CMOS_RTC_SECONDS_ALARM, 			// Получение значения секунд будильника. 		                                        Чтение и запись разрешены.
	CMOS_RTC_MINUTES,					// Получение значения минут. 					                                        Чтение и запись разрешены.
	CMOS_RTC_MINUTES_ALARM,				// Получение значения минут будильника. 		                                        Чтение и запись разрешены.
	CMOS_RTC_HOURS,						// Получение значения часов. 					                                        Чтение и запись разрешены.
	CMOS_RTC_HOURS_ALARM,				// Получение значения часов будильника. 		                                        Чтение и запись разрешены.
	CMOS_RTC_DAY_OF_WEEK,				// Получение значения дня недели. 				                                        Чтение и запись разрешены.
	CMOS_RTC_DAY_OF_MONTH,				// Получение значения дня месяца. 				                                        Чтение и запись разрешены.
	CMOS_RTC_MONTHS,					// Получение значения месяца. 					                                        Чтение и запись разрешены.
	CMOS_RTC_YEARS,						// Получение значения годов. 					                                        Чтение и запись разрешены.
	CMOS_RTC_CENTURY = 0x32,            // Получение значения века.                                                             Чтение и запись разрешены.
	CMOS_RTC_REGISTER_A,				// Получение регистра A. см RegisterA_Bits. 	                                        Чтение и запись разрешены.
	CMOS_RTC_REGISTER_B,				// Получение регистра B. см RegisterB_Bits. 	                                        Чтение и запись разрешены.
	CMOS_RTC_REGISTER_C,				// Получение регистра C. см RegisterC_Bits. 	                                        Только чтение.
	CMOS_RTC_REGISTER_D,				// Получение регистра D. см RegisterD_Bits. 	                                        Только чтение.
	CMOS_FLOPPY_TYPE = 0x10, 			// Получение типа дискетты.                                                             Только чтение.
	CMOS_HARD_DISK_TYPE = 0x12,         // Получение типа жесткого диска.                                                        Только чтение.
	CMOS_EQUIPMENT_BYTE = 0x14,         // Получение списка доступных устройств.                                                Только чтение.
	CMOS_BASE_MEMORY_KB_LOW_BYTE,       // Получение нижнего байта размера RAM до 1 МБ.                                         Только чтение.
	CMOS_BASE_MEMORY_KB_HIGH_BYTE,      // Получение верхнего байта размера RAM до 1 МБ.                                        Только чтение.
	CMOS_EXTENDED_KB_MEMORY_LOW_BYTE,   // Получение нижнего байта размера RAM после 1 МБ.                                      Только чтение.
	CMOS_EXTENDED_KB_MEMORY_HIGH_BYTE,  // Получение верхнего байта размера RAM после 1 МБ.                                     Только чтение.
	CMOS_CHECKSUM_HIGH_BYTE = 0x2E,     // Получение верхнего байта CMOS CHECKSUM.                                              Только чтение.
	CMOS_CHECKSUM_LOW_BYTE              // Получение нижнего байта CMOS CHECKSUM.                                               Только чтение.
} UniversalCMOSCode;

typedef enum AMICMOSCode {
    CMOS_AMI_KEYBOARD_TYPEMATIC_DATA =          0x11,   // Получение сведений про частоту нажатий клавиш на клавиатуре. Запись и чтение разрешены. В данный момент не поддерживается.
    CMOS_AMI_ADVANCED_SETUP_OPTIONS =           0x13,   // Получение сведений про уникальные опции загрузки. 
    CMOS_AMI_CONFIGURATION_OPTIONS =            0x2D,   // Получение сведений про конфигурацию опций. 
    CMOS_AMI_SHADOWING_AND_BOOT_PASSWORD =      0x34,   // 
    CMOS_AMI_SHADOWING =                        0x35,   // 
    CMOS_AMI_EXTENDED_CMOS_CHECKSUM_HIGH_BYTE = 0x3E,   // 
    CMOS_AMI_EXTENDED_CMOS_CHECKSUM_LOW_BYTE =  0x3F,   // 
    CMOS_AMI_EXTENDED_DMA_IO_EMR_BIT_CHECK =    0x41,   // 
    CMOS_AMI_NMI_STATUS =                       0x44,   // 
    CMOS_AMI_BUS_DELAY_STATES =                 0x45,   // 
    CMOS_AMI_BUS_WAIT_STATES =                  0x46,   //
    CMOS_AMI_BANK_0_1_STATES =                  0x51,   //
    CMOS_AMI_BANK_2_3_STATES =                  0x53,   //
} AMICMOSCode;

typedef enum IBMPS2CMOSCode {
    CMOS_IBM_PS2_DIAGNOSTIC_STATUS = 14, 	// Получение результата тестирования POST.		                Только чтение.
	CMOS_IBM_PS2_SHUTDOWN_STATUS, 			// Получение причины предыдущего выключения		                Только чтение.
    // Совсем скоро будет больше кодов CMOS
} IBMPS2CMOSCode;

// Чтение и запись разрешена для 0-6 битов.
typedef enum RegisterA_Bits {
	REGISTER_A_RATE_SELECT_0_BIT, 		// Настраивает частоту периодического прерывания, 				0 бит 4 битного числа - делителя, 0001
	REGISTER_A_RATE_SELECT_1_BIT, 		// Настраивает частоту периодического прерывания, 				1 бит 4 битного числа - делителя, 0010
	REGISTER_A_RATE_SELECT_2_BIT, 		// Настраивает частоту периодического прерывания, 				2 бит 4 битного числа - делителя, 0100
	REGISTER_A_RATE_SELECT_3_BIT, 		// Настраивает частоту периодического прерывания, 				3 бит 4 битного числа - делителя, 1000
	REGISTER_A_DIVIDER_SELECT_0_BIT, 	// Настраивает режим работы внутреннего делителя частоты RTC,  	0 бит 3 битного числа - делителя, 0001
	REGISTER_A_DIVIDER_SELECT_1_BIT, 	// Настраивает режим работы внутреннего делителя частоты RTC,  	1 бит 3 битного числа - делителя, 0010
	REGISTER_A_DIVIDER_SELECT_2_BIT, 	// Настраивает режим работы внутреннего делителя частоты RTC,  	2 бит 3 битного числа - делителя, 0100
	REGISTER_A_UPDATE_IN_PROGRESS 		// Флаг обновления RTC, только для чтения.
} RegisterABits;

// Разрешено чтение и запись для всех битов (0-7 бит).
typedef enum RegisterB_Bits {
	REGISTER_B_DAYLIGHT_SAVINGS_ENABLE,     // Флаг автоматического перехода на летнее время, т.е в последнее воскресенье марта переходят на час вперед, в последнее воскресенье октября начинается обычное время
	REGISTER_B_IS_24_FORMAT, 				// Флаг 24 часового режима, 1 - 0-24 часа, 0 - 0-12 часа, при 0 - AM/PM режим бит работает.
	REGISTER_B_DATA_MODE, 					// Переключение BCD и binary режимов.
	REGISTER_B_SQUARE_WAVE_ENABLE, 			// Вкл/выкл квадратный сигнал на вывод SQWB.
	REGISTER_B_UPDATE_INTERRUPT_ENABLE, 	// Вкл/выкл генерации прерывания при каждом обновлении секунды.
	REGISTER_B_ALARM_INTERRUPT_ENABLE, 		// Вкл/выкл генерации прерывания будильника.
	REGISTER_B_PERIODIC_INTERRUPT_ENABLE, 	// Вкл/выкл периодическую генерацию прерывания IRQ8.
	REGISTER_B_SET 							// Отключить обновление времени RTC. ( для записи )
} RegisterB_Bits;

// Важно: Чтение флагов из регистра C обнулят все флаги в этом регистре. Только чтение. Регистр C является регистром событий.
typedef enum RegisterC_Bits {
	REGISTER_C_UPDATE_FLAG = 4, 			// Если установлено в 1 то произошло обновление секунды по флагу REGISTER_B_UPDATE_INTERRUPT_ENABLE.
	REGISTER_C_ALARM_FLAG, 					// Если установлено в 1 то сработал будильник по флагу REGISTER_B_ALARM_INTERRUPT_ENABLE.
	REGISTER_C_PERIODIC_FLAG,				// Если установлено в 1 то сработало периодическое прерывание по флагу REGISTER_B_PERIODIC_INTERRUPT_ENABLE.
	REGISTER_C_INTERRUPT_REQUEST_FLAG 		// Если установлено в 1 то есть необработанные события.
} RegisterC_Bits;

// Только для чтения.
typedef enum RegisterD_Bits {
	REGISTER_D_IS_CMOS_BATTERY_CHARGED = 7 	// Если установлено в 1 - то заряжена, если в 0 то разряженна ( соответственно некорректная дата и время )
} RegisterD_Bits;

void CMOSWrite(UniversalCMOSCode code, uint8 data);

uint8 CMOSRead(UniversalCMOSCode code);

bool checkProgressFlag(void);

void setRTCTime(TimeStruct time);

TimeStruct getRTCTime();

#endif