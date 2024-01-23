@REM g++ src/*.cpp src/titleScreen/*.cpp src/gameScreen/*.cpp classes/*.cpp -Wl,--subsystem,windows -mwindows -o game -I include -I classes -L lib -lraylib -lopengl32 -lgdi32 -lwinmm

@REM g++ src/main.cpp -Wl,--subsystem,windows -mwindows -o game -I include -I classes -L lib -lraylib -lopengl32 -lgdi32 -lwinmm

@REM g++ src/main.cpp src/0_startup_screen/startup_screen.cpp src/1_title_screen/title_screen.cpp -Wl,--subsystem,windows -mwindows -o game -I include -I classes -lraylib -lopengl32 -lgdi32 -lwinmm

g++ classes/*.cpp src/main.cpp src/0_startup_screen/startup_screen.cpp src/1_title_screen/title_screen.cpp src/2_menu_screen/menu_screen.cpp src/3_overworld_screen/overworld_screen.cpp src/4_battle_screen/battle_screen.cpp -o game -I include -I classes -lraylib -lopengl32 -lgdi32 -lwinmm