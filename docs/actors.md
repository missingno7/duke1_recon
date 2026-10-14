# Duke Nukum actor map

The code names in `src/` follow this table (`create_objects_from_level_map` turns map words into actors).  Identities use the map switch/callback logic in `src/GAME1.C`, sprite cells decoded from the episode's ANIM/OBJECT/SOLID files (rendered locally, not committed), and the [Duke 1 Level Format table](https://moddingwiki.shikadi.net/wiki/Duke_1_Level_Format) (MW). Enemy names were checked against the [Duke Nukem I enemies list](https://dukenukem.fandom.com/wiki/Enemies_in_Duke_Nukem_I); tile decoding follows [ProGraphx Toolbox tileset format](https://moddingwiki.shikadi.net/wiki/Crystal_Caves_Tileset_Format). All sheets use Episode 1 art; corresponding ANIM, OBJECT, and SOLID assets match byte-for-byte across Episodes 1-3.

`S` = source case/handler or interaction behavior; `MW` = ModdingWiki map-code description; every identity was also checked against the rendered sprite. Levels are WORLDAL suffixes (`1`-`9`, `a`-`c`) grouped by episode. 

| Map word | Identity | Evidence used for this word | Confidence | Episodes / levels |
|---|---|---|---|---|
| `0x3000` | Empty grey bonus box | S: `update_empty_bonus_box`: updates position; score path 500L; MW. | High | E1 1,3,4,6,7,8,9,b; E2 5,6,8,a,b; E3 1,3,4,5,6,8,a,b |
| `0x3001` | Elevator | S: `update_elevator`: updates position; sound ids 0x14; hint: "Secret Tip: Press the UP ARROW to activate the ELEVATORS."; MW. | High | E1 1,6,7,8,b,c; E2 1,4,5,6,8,a,b,c; E3 3,8,9,b,c |
| `0x3002` | Left-moving conveyor belt start | S: `update_conveyor_belt`: advances animation/state; tests player contact; MW. | High | E1 7,8,a,b,c; E2 6,8,9,b,c; E3 8,c |
| `0x3003` | Left-moving conveyor belt end | S: `update_conveyor_belt`: advances animation/state; tests player contact; MW. | High | E1 7,8,a,b,c; E2 6,8,9,b,c; E3 8,c |
| `0x3004` | Right-moving conveyor belt start | S: `update_conveyor_belt`: advances animation/state; tests player contact; MW. | High | E1 7,8,a,b,c; E2 5,6,8,b,c; E3 a,b,c |
| `0x3005` | Right-moving conveyor belt end | S: `update_conveyor_belt`: advances animation/state; tests player contact; MW. | High | E1 7,8,a,b,c; E2 5,6,8,b,c; E3 a,b,c |
| `0x3006` | Jump boots bonus box | S: `update_jump_boots_box`: updates position; tests player contact; score path 1000L, 500L; sound ids 0x0c; MW. | High | E1 5,c; E2 6,c; E3 5,c |
| `0x3007` | Rocket | S: `update_rocket`: updates position; score path 200L; sound ids 0x1e; MW. | High | E1 7,8,9,b,c; E2 8,b,c; E3 a,c |
| `0x3008` | Ceiling-clinger bonus box | S: `update_ceiling_clinger_box`: updates position; tests player contact; score path 1000L, 500L; MW. | High | E1 8,c; E2 8,a,c; E3 8,c |
| `0x3009` | Right-firing flamethrower | S: `update_right_flame_turret`: tests player contact; sound ids 0x2b; MW. | High | E1 1,4,5,6,8,a,b,c; E2 1,3,4,6,8,9,c; E3 3,4,8,9,b,c |
| `0x300A` | Left-firing flamethrower | S: `update_left_flame_turret`: tests player contact; sound ids 0x2b; MW. | High | E1 1,5,6,8,9,a,b,c; E2 1,3,4,6,7,9,c; E3 1,3,4,6,8,9,a,b,c |
| `0x300B` | Flying Techbot | S: `update_flying_techbot`: updates position; tests player contact; score path 200L; sound ids 18; MW. | High | E1 3,4,5,6,7,8,9,a,b,c; E2 1,3,4,5,6,7,8,9,a,b,c; E3 1,3,4,5,6,7,8,9,a,b,c |
| `0x300C` | Jumping Techbot | S: `update_jumping_techbot`: updates position; score path 2000L; MW. | High | E1 1,3,4,5,6,7,8,9,a,b,c; E2 1,3,4,5,6,7,8,9,a,b,c; E3 4,5,6,7,9,a,b,c |
| `0x300D` | Wheeled Techbot | S: `update_wheeled_techbot`: updates position; score path 2500L; sound ids 0x12; MW. | High | E1 1,3,6,7,8,9,a,b,c; E2 1,3,4,6,7,8,c; E3 3,4,5,6,7,b,c |
| `0x300E` | Fire Wheel Techbot | S: `update_fire_wheel_techbot`: updates position; score path 5000L; MW. | High | E1 3,4,5,6,7,8,b,c; E2 3,5,6,8,c; E3 1,4,5,9,c |
| `0x300F` | Raygun ammunition bonus | S: `update_ammo_box`: updates position; tests player contact; score path 1000L, 500L; sound ids 0xc; MW. | High | E1 5,6,b,c; E2 1,3,4,6,7,9,b,c; E3 6,7,c |
| `0x3010` | Robot Techbot | S: `update_robot_techbot`: updates position; tests player contact; score path 100L; sound ids 0x12; MW. | High | E1 1,3,4,6,8,9,b,c; E2 1,3,4,5,6,7,8,9,a,c; E3 1,3,4,5,6,8,9,b,c |
| `0x3011` | Exit door | S: map switch sets exit-door interaction state; MW. | High | E1 1,2,3,4,5,6,7,8,9,a,c; E2 1,2,3,4,5,6,7,8,9,a,c; E3 1,2,3,4,5,6,7,8,9,a,c |
| `0x3012` | Dynamite bonus | S: `update_dynamite_box`: updates position; score path 500L; sound ids 0x21; MW. | High | E1 1,3,4,5,6,7,8,9,a,b,c; E2 1,3,4,5,6,8,9,a,b,c; E3 1,3,4,5,6,7,8,9,a,b,c |
| `0x3013` | Snake Techbots | S: `update_snake_techbot`: advances animation/state; tests player contact; score path 10000L, 1000L; sound ids 10; MW. | High | E1 5,8,9,b; E2 6,7,9,b; E3 4,6,8,a,b |
| `0x3014` | Shimmering water effect | S: `update_water_shimmer`: copies an animated planar region; MW. | Medium | E1 8,9,b,c; E2 4,6,9,c; E3 4,6,7,c |
| `0x3015` | Soda-can bonus box | S: `update_soda_can_bonus`: updates position; tests player contact; score path 1000L, 200L, 500L; sound ids 0x10, 1, 2; hint: "Secret Tip: Drink soda to increase your health!"; MW. | High | E1 1,3,4,5,6,7,8,9,a,b,c; E2 1,4,5,6,8,9,b,c; E3 1,3,4,5,6,7,8,9,a,c |
| `0x3016` | Right-facing Wallcrawler | S: `update_wallcrawler`: updates position; tests player contact; score path 100L; sound ids 18; MW. | High | E1 1,3,4,5,6,7,8,9,a,b; E2 5,7,8,9,a; E3 1,3,4,5,7,8,a |
| `0x3017` | Left-facing Wallcrawler | S: `update_wallcrawler`: updates position; tests player contact; score path 100L; sound ids 18; MW. | High | E1 1,3,4,5,6,7,8,9,a,b; E2 5,6,7,8,a; E3 1,4,5,6,7,8,9,a,b |
| `0x3018` | Turkey drumstick bonus box | S: `update_turkey_bonus`: updates position; tests player contact; score path 100L, 200L, 500L; sound ids 1; hint: "Secret Tip: Eat turkey to increase your health!"; MW. | High | E1 1,4,5,6,7,8,9,a,b; E2 6,7,8,9,a,b; E3 3,4,5,7,8,9,a,b |
| `0x3019` | Collapsing bridge | S: `update_collapsing_bridge`: advances animation/state; tests player contact; MW. | High | E1 1,5,6,7,9,a,b; E3 8,a |
| `0x301A` | Horizontal blue force field | S: `update_horizontal_force_field`: advances animation/state; tests player contact; sound ids 21; MW. | High | E1 5,6,7; E2 5,6,7,8,b; E3 3,4,9,b |
| `0x301B` | Left-blowing rotating fan | S: `update_rotating_fan`: tests player contact; score path 1000L; sound ids 18; MW. | High | E1 5,6,9,a,b; E2 7,8; E3 1,9 |
| `0x301C` | Right-blowing rotating fan | S: `update_rotating_fan`: tests player contact; score path 1000L; sound ids 18; MW. | High | E1 4,6,8,9,a; E2 5; E3 1 |
| `0x301D` | Football bonus box | S: `update_football_box`: updates position; tests player contact; score path 100L, 500L; sound ids 16; MW. | High | E1 1,3,4,5,6,7,8,b,c; E2 1,3,4,5,6,8,9,a,c; E3 1,3,4,5,6,7,8,9,c |
| `0x301E` | Joystick bonus box | S: `update_joystick_box`: updates position; tests player contact; score path 2000L, 500L; sound ids 16; MW. | High | E1 1,4,5,6,7,8,9,a,b; E2 3,4,5,6,7,8,9,a; E3 1,3,4,5,6,7,9,a,b |
| `0x301F` | DN floppy bonus box | S: `update_floppy_disk_box`: updates position; tests player contact; score path 5000L, 500L; sound ids 16; MW. | High | E1 1,3,4,5,6,7,8,9,a,b,c; E2 1,3,4,5,6,7,8,a,c; E3 1,3,4,5,8,9,a,c |
| `0x3020` | Robohand bonus box | S: `update_robohand_box`: updates position; tests player contact; score path 1000L, 500L; sound ids 12; MW. | High | E1 7; E2 4; E3 7 |
| `0x3021` | Vertical force field | S: `update_vertical_force_field`: advances animation/state; tests player contact; sound ids 21; MW. | High | E1 4,b,c; E2 1,5,7,b,c; E3 3,7,8,9,b,c |
| `0x3022` | Helicopter Techbot | S: `update_helicopter_techbot`: updates position; score path 5000L; MW. | High | E1 4,8,9,b,c; E2 4,6,8,9,b,c; E3 3,4,6,c |
| `0x3023` | Balloon bonus box | S: `update_balloon_bonus`: updates position; tests player contact; score path 10000L, 500L; sound ids 3; MW. | High | E1 1,3,4,5,6,7,8,9,a,b,c; E2 1,3,4,5,6,7,8,9,a,b,c; E3 1,3,4,5,6,7,8,a,b,c |
| `0x3024` | Security camera | S: `update_security_camera`: score path 100L; sound ids 18; MW. | High | E1 1,3,4,5,6,7,8,9,a,b,c; E2 1,6,a,c; E3 1,3,8,9,a,c |
| `0x3025` | Brown ceiling spikes decoration | S: `draw_level_marker_tiles`: draws its sprite/animation; MW. | High | E1 1,3,5,b,c; E2 6,b,c; E3 3,5,c |
| `0x3026` | Rock left half | S: `draw_level_marker_tiles`: draws its sprite/animation; MW. | High | E1 8,9; E2 6,7; E3 5,6 |
| `0x3027` | Rock right half | S: `draw_level_marker_tiles`: draws its sprite/animation; MW. | High | E1 9; E2 6,7; E3 5,6 |
| `0x3028` | Rounded grey window | S: `draw_level_marker_tiles`: draws its sprite/animation; MW. | High | E1 9; E2 6,7; E3 5,6 |
| `0x3029` | Nuclear molecule bonus box | S: `update_molecule_bonus_box`: updates position; tests player contact; score path 1000L, 500L; sound ids 4; hint: "Secret Tip: The nuclear molecule increases your health to maximum!"; MW. | High | E1 1,4,5,6,7,8,9,a,b,c; E2 1,3,4,5,6,7,8,9,b,c; E3 3,4,5,6,8,9,b,c |
| `0x302A` | Falling ACME sign | S: `update_falling_sign`: updates position; tests player contact; score path 500L; sound ids 32; MW. | High | E1 1,3,5,6,7,8,9,a,b; E2 6,8,9,a; E3 3,4,8,9,a,b |
| `0x302B` | Blue reactor hazard | S: `update_reactor`: advances animation/state; tests player contact; score path 20000L; sound ids 10, 17, 36; MW. | High | E1 1,5,6,8,b,c; E2 5,7,c; E3 3,4,7,9,a,b,c |
| `0x302C` | Pop-up floor spike | S: `update_popup_spikes`: tests player contact; MW. | High | E1 3,4,5,8; E2 7,8,9,a; E3 1,4,7,8,a,b |
| `0x302D` | Magenta flag bonus box | S: `update_magenta_flag_box`: updates position; tests player contact; score path 100L, 2000L, 5000L, 500L; sound ids 16; MW. | High | E1 1,3,4,6,a,b,c; E2 4,5,6,8,9,a,b,c; E3 3,4,5,6,8,9,a,c |
| `0x302E` | Radio bonus box | S: `update_radio_box`: updates position; tests player contact; score path 100L, 2000L, 5000L, 500L; sound ids 16; MW. | High | E1 1,4,6,9,c; E2 1,3,4,5,7,8,b,c; E3 4,7,8,a,c |
| `0x302F` | Teleporter endpoint leading to 0x3030 | S: `activate_teleporter_entry`: advances animation/state; MW. | High | E1 4,7,8,a,b,c; E2 5,6,c; E3 1,4,6,b,c |
| `0x3030` | Teleporter endpoint leading to 0x302F | S: `activate_teleporter_exit`: advances animation/state; tests player contact; sound ids 7; hint: "Secret Tip: Press the UP ARROW to activate the TRANSPORTER."; MW. | High | E1 4,7,8,a,b,c; E2 5,6,c; E3 1,4,6,b,c |
| `0x3031` | Bouncing spiky bomb | S: `update_red_bomb`: updates position; tests player contact; sound ids 34; MW. | High | E1 1,3,4,5,6,7,8,9,b,c; E2 1,4,5,6,7,9,b,c; E3 1,3,4,5,6,7,8,9,a,b,c |
| `0x3032` | Player start point | S: map switch sets player start position; no sprite); MW. | High | E1 1,2,3,4,5,6,7,8,9,a,b,c; E2 1,2,3,4,5,6,7,8,9,a,b,c; E3 1,2,3,4,5,6,7,8,9,a,b,c |
| `0x3033` | Access-card bonus box | S: `update_access_card_box`: updates position; tests player contact; score path 1000L, 500L; sound ids 12; MW. | High | E1 4,b,c; E2 1,5,7,b,c; E3 3,7,8,9,b,c |
| `0x3034` | Access-card reader | S: `update_access_card_reader`: tests player contact; sound ids 31; hint: "Secret Tip: Find the ACCESS CARD and press the UP ARROW here. / Secret Tip: Find the ACCESS CARD first and then insert it in here."; MW. | High | E1 4,b,c; E2 1,5,7,b,c; E3 3,7,8,9,b,c |
| `0x3035` | Robohand activation switch | S: `update_robohand_switch`: advances animation/state; tests player contact; sound ids 5; hint: "Secret Tip: Press the UP ARROW here after you have found the ROBOHAND."; MW. | High | E1 7,8,a,b; E2 4,8,b; E3 7,a |
| `0x3036` | Robohand bridge girder | S: `update_robohand_bridge_state`: updates position; MW. | Medium | E1 7,8,a,b; E2 4,8,b; E3 7,a |
| `0x3037` | Letter D bonus | S: `update_letter_bonus`: updates position; tests player contact; score path 10000L, 500L; sound ids 16, 37; MW. | High | E1 1,4,6,7,a; E2 3,7,9; E3 4,5,6 |
| `0x3038` | Letter U bonus | S: `update_letter_bonus`: updates position; tests player contact; score path 10000L, 500L; sound ids 16, 37; MW. | High | E1 1,4,6,7,a; E2 3,7,9; E3 4,5,6 |
| `0x3039` | Letter K bonus | S: `update_letter_bonus`: updates position; tests player contact; score path 10000L, 500L; sound ids 16, 37; MW. | High | E1 1,4,6,7,a; E2 3,7,9; E3 4,5,6 |
| `0x303A` | Letter E bonus | S: `update_letter_bonus`: updates position; tests player contact; score path 10000L, 500L; sound ids 16, 37; MW. | High | E1 1,4,6,7,a; E2 3,7,9; E3 4,5,6 |
| `0x303B` | Purple rabbit bonus | S: `update_rabbit_bonus`: updates position; tests player contact; score path 200L, 5000L; sound ids 18, 35; MW. | High | E1 4,6,7,8,9,a,b,c; E2 5,6,7,8,9,c; E3 4,6,7,8,9,a,b,c |
| `0x303C` | Flame creature | S: `update_fire_creature`: updates position; tests player contact; MW. | High | E1 8,9,b; E2 5,6,9; E3 3,7,8,b |
| `0x303D` | Diamond wire mesh | S: `draw_level_marker_tiles`: draws its sprite/animation; MW. | High | E1 5,8,b,c; E2 1,3,7,c; E3 1,9,b,c |
| `0x303E` | Backdrop window left half | S: `draw_level_marker_tiles`: draws its sprite/animation; MW. | High | E1 1,4,5,8,b; E2 3,8 |
| `0x303F` | Backdrop window right half | S: `draw_level_marker_tiles`: draws its sprite/animation; MW. | High | E1 1,4,5,8,b; E2 3,8 |
| `0x3040` | Message sign | S: `update_message_sign`: tests player contact; hint: "Secret Tip: Press the UP ARROW to read the notes."; MW. | High | E1 2; E2 2; E3 2 |
| `0x3041` | Dr. Proton display screen | S: `update_dr_proton`; MW. | Medium | E1 3,5,6,7,8,9,a,b; E2 3,6,a; E3 3,5,7,9 |
| `0x3042` | Dr. Proton boss (Episode 3) | S: `update_dr_proton`; MW. | High | E3 b |
| `0x3043` | Dr. Proton boss (Episodes 1-2) | S: `update_dr_proton`; MW. | High | E1 b; E2 b |
| `0x3044` | Red key | S: `update_door_keys`: tests player contact; score path 1000L; sound ids 9; MW. | High | E1 1,3,4,6,b; E2 3,5,7,a; E3 8 |
| `0x3045` | Green key | S: `case 0x3045`; MW. | High | E1 4,6,7,8,a,b,c; E2 3,9,c; E3 4,6,c |
| `0x3046` | Blue key | S: `case 0x3046`; MW. | High | E1 3,4,6; E2 3; E3 6,a |
| `0x3047` | Magenta key | S: `case 0x3047`; MW. | High | E1 4,9,b; E2 3,7; E3 9 |
| `0x3048` | Red key lock | S: `update_door_locks`: advances animation/state; tests player contact; score path 1000L; sound ids 0x1f; hint: "Secret Tip: Find the key that goes here and press the UP ARROW. / Secret Tip: You need the correct key before you can use this lock."; MW. | High | E1 1,3,4,6,b; E2 3,5,7,a; E3 8 |
| `0x3049` | Green key lock | S: `update_door_locks`: advances animation/state; tests player contact; score path 1000L; sound ids 0x1f; hint: "Secret Tip: Find the key that goes here and press the UP ARROW. / Secret Tip: You need the correct key before you can use this lock."; MW. | High | E1 4,6,7,8,a,b,c; E2 3,9,c; E3 4,6,c |
| `0x304A` | Blue key lock | S: `update_door_locks`: advances animation/state; tests player contact; score path 1000L; sound ids 0x1f; hint: "Secret Tip: Find the key that goes here and press the UP ARROW. / Secret Tip: You need the correct key before you can use this lock."; MW. | High | E1 3,4,6; E2 3; E3 6,a |
| `0x304B` | Magenta key lock | S: `update_door_locks`: advances animation/state; tests player contact; score path 1000L; sound ids 0x1f; hint: "Secret Tip: Find the key that goes here and press the UP ARROW. / Secret Tip: You need the correct key before you can use this lock."; MW. | High | E1 4,9,b; E2 3,7; E3 9 |
| `0x304C` | Red-keyed door | S: `animate_level_tile_records`: advances animation/state; MW. | High | E1 1,3,4,6,b; E2 3,5,7,a; E3 8 |
| `0x304D` | Green-keyed door | S: `animate_level_tile_records`: advances animation/state; MW. | High | E1 4,6,7,8,a,b,c; E2 3,9,c; E3 4,6,c |
| `0x304E` | Blue-keyed door | S: `animate_level_tile_records`: advances animation/state; MW. | High | E1 3,4,6; E2 3; E3 6,a |
| `0x304F` | Magenta-keyed door | S: `animate_level_tile_records`: advances animation/state; MW. | High | E1 4,9,b; E2 3,7; E3 9 |
| `0x3050` | Football pickup | S: `update_football_box`: updates position; tests player contact; score path 100L, 500L; sound ids 16; MW. | High | E1 1,3,4,5,6,7,9,a,b,c; E2 1,4,5,6,8,9,a,c; E3 1,3,4,8,a,b,c |
| `0x3051` | Turkey drumstick pickup | S: `update_turkey_bonus`: updates position; tests player contact; score path 100L, 200L, 500L; sound ids 1; hint: "Secret Tip: Eat turkey to increase your health!"; MW. | High | E1 4,6,8,9,b,c; E2 1,3,4,5,6,7,8,9,a,b,c; E3 3,5,7,8,a,b,c |
| `0x3052` | Soda-can pickup | S: `update_soda_can_bonus`: updates position; tests player contact; score path 1000L, 200L, 500L; sound ids 0x10, 1, 2; hint: "Secret Tip: Drink soda to increase your health!"; MW. | High | E1 1,3,4,5,6,7,8,9,a,b,c; E2 1,3,4,5,6,7,8,9,a,b,c; E3 4,5,7,a,b,c |
| `0x3053` | DN floppy pickup | S: `update_floppy_disk_box`: updates position; tests player contact; score path 5000L, 500L; sound ids 16; MW. | High | E1 1,3,4,5,6,8,9,b,c; E2 1,9,a,c; E3 1,4,5,6,7,8,9,a,c |
| `0x3054` | Joystick pickup | S: `update_joystick_box`: updates position; tests player contact; score path 2000L, 500L; sound ids 16; MW. | High | E1 1,3,4,5,6,8,c; E2 1,4,7,9,c; E3 4,8,a,c |
| `0x3055` | Purple flag pickup | S: `update_magenta_flag_box`: updates position; tests player contact; score path 100L, 2000L, 5000L, 500L; sound ids 16; MW. | High | E1 1,3,4,5,6,7,8,9,a,b,c; E2 1,3,4,5,6,7,a,b,c; E3 1,4,5,6,8,9,a,c |
| `0x3056` | Radio pickup | S: `update_radio_box`: updates position; tests player contact; score path 100L, 2000L, 5000L, 500L; sound ids 16; MW. | High | E1 1,3,4,6,8,a,b,c; E2 1,6,a,c; E3 4,5,6,8,b,c |
| `0x3057` | Stationary spiky bomb | S: `update_stationary_bomb_hazards`: updates position; tests player contact; sound ids 33; MW. | High | E1 4,5,6,7,9,b; E2 4,5,6,b; E3 1,4,a,b |
| `0x3058` | Upward floor spikes | S: `draw_spike_hazard_sprites`: tests player contact; MW. | High | E1 1,3,4,6,7,9,b,c; E2 3,c; E3 8,9,a,b,c |
| `0x3059` | Downward ceiling spikes | S: `draw_spike_hazard_sprites`: tests player contact; MW. | High | E1 1,5,6,7,8,9,b,c; E2 6,c; E3 4,8,a,c |
