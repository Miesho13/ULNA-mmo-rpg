/**
 * This header contains compile-time configuration constants and macros
 * used by the client application, such as server IP address, port
 * numbers, buffer sizes, timeouts, and other immutable parameters.
 *
 * Keeping these values in one place simplifies maintenance and ensures
 * consistent configuration across the project.
 *
 * Usage:
 *  - Modify values here to change client build-time configuration.
 *  - Include this file in modules that require client settings.
 *
 * Note:
 *  - Do NOT place runtime-modifiable variables here.
 *  - Avoid storing sensitive information (e.g., credentials) in this file.
 *
 * @author Marcin Ryzewski 
 * @date   1-11-2025
 */

#ifndef CLIENT_CONFIG
#define CLIENT_CONFIG

// RENDERER
#define RENDER_MAX_SPRITE_SIZE (1024)

// LOGIN SCREAN DEFINES
#define LOGIN_SCREAN_PADDING_H   (0.2)
#define LOGIN_SCREAN_PADDING_W   (0.2)
#define LOGIN_SCREAN_FONT_SIZE   (32)
#define LOGIN_SCREAN_FONT_COLOR  (0xf4514bff) // RGB_32
#define LOGIN_SCREAN_MARGIN_TEXT (10)


#endif // CLIENT_CONFIG
