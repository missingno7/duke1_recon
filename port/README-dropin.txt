Duke Nukum v2.0 - SDL3 port (test build)
=========================================

Copy duke1.exe and SDL3.dll into the folder that holds your Duke Nukum game files
(*.dn1, *.dn2, *.dn3) and run duke1.exe.  One program plays all episodes: with more
than one episode in the folder it asks which one to play; Esc quits.  The game files
themselves are not included.

The game is the original 1991 code, rebuilt from source: same screens, rules,
controls and file formats (saves, high scores, demos and settings are read and
written in the game folder, compatible with the DOS version).

Keys: as in the original (arrows to move, Ctrl jump, Alt fire, F1 help; redefinable
in the game setup menu).
Sound: the original PC speaker effects (S toggles sound in the game, as in DOS).
Alt+Enter: fullscreen.  Q)uit in the main menu returns to the episode dialog, where
Esc ends the program; closing the window ends it at once.

Options:
  --data DIR      game files in DIR instead of the program's folder
  --episode N     start episode N directly (1, 2 or 3)
  --select        always show the episode dialog
  --trace         log hardware/file activity to duke1.log

This is a work-in-progress build:
  - no joystick yet
  - only the start-up screens, menus and the start of play have been compared with
    the original so far; report anything that looks or behaves differently.

SDL3 is (c) Sam Lantinga and contributors, zlib licence (LICENSE-SDL3.txt).
