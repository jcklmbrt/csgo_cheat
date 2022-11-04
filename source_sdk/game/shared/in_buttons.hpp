
#ifndef CSGO_CHEAT_SOURCE_SDK_GAME_SHARED_IN_BUTTONS_HPP_
#define CSGO_CHEAT_SOURCE_SDK_GAME_SHARED_IN_BUTTONS_HPP_

constexpr unsigned IN_ATTACK = (1 << 0);
constexpr unsigned IN_JUMP = (1 << 1);
constexpr unsigned IN_DUCK = (1 << 2);
constexpr unsigned IN_FORWARD = (1 << 3);
constexpr unsigned IN_BACK = (1 << 4);
constexpr unsigned IN_USE = (1 << 5);
constexpr unsigned IN_CANCEL = (1 << 6);
constexpr unsigned IN_LEFT = (1 << 7);
constexpr unsigned IN_RIGHT = (1 << 8);
constexpr unsigned IN_MOVELEFT = (1 << 9);
constexpr unsigned IN_MOVERIGHT = (1 << 10);
constexpr unsigned IN_ATTACK2 = (1 << 11);
constexpr unsigned IN_RUN = (1 << 12);
constexpr unsigned IN_RELOAD = (1 << 13);
constexpr unsigned IN_ALT1 = (1 << 14);
constexpr unsigned IN_ALT2 = (1 << 15);
constexpr unsigned IN_SCORE = (1 << 16);   // Used by client.dll for when scoreboard is held down
constexpr unsigned IN_SPEED = (1 << 17);        // Player is holding the speed key
constexpr unsigned IN_WALK = (1 << 18);        // Player holding walk key
constexpr unsigned IN_ZOOM = (1 << 19);        // Zoom key for HUD zoom
constexpr unsigned IN_WEAPON1 = (1 << 20);        // weapon defines these bits
constexpr unsigned IN_WEAPON2 = (1 << 21);        // weapon defines these bits
constexpr unsigned IN_BULLRUSH = (1 << 22);
constexpr unsigned IN_GRENADE1 = (1 << 23);        // grenade 1
constexpr unsigned IN_GRENADE2 = (1 << 24);        // grenade 2
constexpr unsigned IN_LOOKSPIN = (1 << 25);

#endif //CSGO_CHEAT_SOURCE_SDK_GAME_SHARED_IN_BUTTONS_HPP_
