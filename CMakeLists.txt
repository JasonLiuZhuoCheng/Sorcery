cmake_minimum_required(VERSION 3.12)
project(HearthStone)

set(CMAKE_CXX_STANDARD 14)

add_executable(HearthStone main.cpp Card/Card.cpp Card/Card.h Card/Minion.cpp Card/Minion.h Card/Spell.cpp Card/Spell.h Board.cpp Board.h Player.cpp Player.h Card/Ritual.cpp Card/Ritual.h Card/Enchantment.cpp Card/Enchantment.h)