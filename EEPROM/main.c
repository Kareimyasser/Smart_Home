#include "EEPROM.h"
#include <avr/io.h>

#define USERNAME_MAX_LEN 32  // Adjust as needed, considering EEPROM space
#define HASH_LEN           32  // Adjust based on chosen hash function

// Function prototypes (replace with actual implementations from your EEPROM library)
uint8_t EEPROM_readByte(uint16_t address);
void EEPROM_writeByte(uint16_t address, uint8_t data);
void EEPROM_writeString(uint16_t address, const char* str);

// Function to get the starting address for a user type
uint16_t get_user_start_address(enum UserType user_type) {
    switch (user_type) {
        case LOCAL_USER:
            return 0;
        case ADMIN_USER:
            return 30 * 64; // Assuming 64 bytes per page
        case REMOTE_USER:
            return (30 + 2) * 64;
        default:
            return 0; // Handle invalid user type gracefully (e.g., return error code)
    }
}

// Function to read username and password hash for a user
bool read_user_credentials(enum UserType user_type, char* username, uint8_t* password_hash) {
    uint16_t start_address = get_user_start_address(user_type);

    // Read username (null-terminated string)
    uint8_t username_idx = 0;
    while (username_idx < USERNAME_MAX_LEN && EEPROM_readByte(start_address + username_idx) != 0) {
        username[username_idx] = EEPROM_readByte(start_address + username_idx);
        username_idx++;
    }
    username[username_idx] = '\0'; // Ensure null termination

    // Check if username is valid (not empty)
    if (username_idx == 0) {
        return false; // Username not found
    }

    // Skip separator byte
    start_address += username_idx + 1;

    // Read password hash
    for (int i = 0; i < HASH_LEN; i++) {
        password_hash[i] = EEPROM_readByte(start_address + i);
    }

    return true;
}

// Function to write username and password hash for a user (secure hashing required)
bool write_user_credentials(enum UserType user_type, const char* username, const uint8_t* password_hash) {
    uint16_t start_address = get_user_start_address(user_type);

    // Ensure username fits within allocated space
    if (strlen(username) >= USERNAME_MAX_LEN) {
        return false; // Username too long
    }

    // Write username (null-terminated string)
    EEPROM_writeString(start_address, username);

    // Skip separator byte (write after username)
    start_address += strlen(username) + 1;

    // Write password hash
    for (int i = 0; i < HASH_LEN; i++) {
        EEPROM_writeByte(start_address + i, password_hash[i]);
    }

    return true;
}
