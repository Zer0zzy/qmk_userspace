#define PLOOPY_DPI_OPTIONS { 500, 150 }
#define PLOOPY_DPI_DEFAULT 0
#define SCROLL_BUTT_DEBOUNCE 1000
#define NUM_LOCK_BITMASK 0b01
#define SCROLL_LOCK_BITMASK 0b10

// World record for fastest index finger tapping is 1092 taps per minute, which
// is 55ms for a single tap.
// https://recordsetter.com/world-record/index-finger-taps-minute/46066
#define LED_CMD_TIMEOUT 60
#define MOUSE_TIMEOUT 70
#define MOUSE_DELAY 40
#define SCROLL_X_THRESHOLD 15    
#define SCROLL_Y_THRESHOLD 15
// 3 requires about 1/8th of a turn in a second to activate
// 5 requires about 1/4th of a turn in a second
#define THRES 3

// Mouse Wheel defines
#define MK_KINETIC_SPEED	
#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 5	
#define MOUSEKEY_WHEEL_BASE_MOVEMENTS 32	
#define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 48	