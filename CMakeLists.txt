cmake_minimum_required(VERSION 3.12)
project(HearthStone)

set(CMAKE_CXX_STANDARD 14)

include_directories(C:/Users/yawen/a5-sorcery-new)

add_executable(
        HearthStone
        main.cpp
        Board.cpp
        Board.h
        Player.cpp
        Player.h
        Card.cpp
        Card.h
        Minion.cpp
        Minion.h
        Spell.cpp
        Spell.h
        Ritual.cpp
        Ritual.h
        Enchantment.cpp
        Enchantment.h
        Display.cpp
        Display.h
        ascii_graphics.h
        ascii_graphics.cc
)
