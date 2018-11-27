cmake_minimum_required(VERSION 3.12)
project(HearthStone)

set(CMAKE_CXX_STANDARD 14)

add_executable(HearthStone
        main.cpp Card.cpp Card.h Minion.cpp Minion.h Spell.cpp Spell.h Board.cpp Board.h Player.cpp Player.h Ritual.cpp Ritual.h Enchantment.cpp Enchantment.h
        Display.cpp Display.h ascii_graphics.h ascii_graphics.cc default.deck help.txt)
