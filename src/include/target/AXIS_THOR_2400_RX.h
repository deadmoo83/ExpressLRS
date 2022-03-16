#define DEVICE_NAME "AXIS THOR 2400RX"

// GPIO pin definitions
#define GPIO_PIN_NSS            15
#define GPIO_PIN_BUSY           5
#define GPIO_PIN_DIO1           4
#define GPIO_PIN_MOSI           13
#define GPIO_PIN_MISO           12
#define GPIO_PIN_SCK            14
#define GPIO_PIN_RST            2
#define GPIO_PIN_LED_RED        16 // LED_RED on TX, copied to LED on RX
#if defined(USE_DIVERSITY)
#define GPIO_PIN_ANTENNA_SELECT 0 // Low = Ant1, High = Ant2, pulled high by external resistor
#endif

#define POWER_OUTPUT_FIXED 13 //MAX power for 2400 RXes that doesn't have PA is 12.5dbm
