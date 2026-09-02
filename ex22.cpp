#include <fmt/core.h>
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using std::cin, fmt::println, fmt::print, std::string, std::vector, std::find;

string prompt() {
    string buffer;
    print("> ");
    getline(cin, buffer);
    return buffer;
}

bool can_craft_ender_eye(vector<string>& inv) {
    if (find(inv.begin(), inv.end(), "ender_pearl") != inv.end() &&
        find(inv.begin(), inv.end(), "blaze_rod") != inv.end()) {
            return true;
    } else {
        return false;
    }
}

enum class RoomId {
    OVERWORLD,
    THE_NETHER,
    END,
    DEATH,
    WIN
};

//using enum RoomId;

RoomId death(bool& alive) {
    println("You died...");
    alive = false;
    return RoomId::DEATH;
}

RoomId win(bool& alive) {
    println("You won. Congratulations.");
    alive = false;
    return RoomId::WIN;
}

RoomId end(vector<string>& inventory) {
    println("Your in a wired dimension.");
    println("There is an floating island and a dragon.");
    string cmd = prompt();

    if (cmd == "fight dragon") {
        println("You kill the dragon.");
        print("You pick up the egg that appears after the death of the dragon.");
        println(" And you jump in the portal.");
        return RoomId::WIN;
    } else if (cmd == "run") {
        println("You try to run but the dragon is faster than you.");
        return RoomId::DEATH;
    } else {
        println("I don't understand that.");
        return RoomId::END;
    }
};

RoomId the_nether(vector<string>& inventory) {
    println("You'r in the nether wastes.");
    println("There is a fortress, a bastion and a warped forest around you.");
    string cmd = prompt();

    if(cmd == "go fortress") {
        println("You go to the fortress and kill blazes.");
        inventory.push_back("blaze_rod");
        println("You got blaze rod now.");
        return RoomId::THE_NETHER;
    } else if(cmd == "go warped forest") {
        println("You go to the warped forest and kill endermans.");
        inventory.push_back("ender_pearl");
        println("You got ender pearl now.");
        return RoomId::THE_NETHER;
    } else if(cmd == "go bastion") {
        println("You go to the bastion...");
        println("But a brute saw you.");
        return RoomId::DEATH;
    } else if(cmd == "go overworld") {
        println("You come back to the overworld.");
        return RoomId::OVERWORLD;
    } else {
        println("I don't understand that.");
        return RoomId::THE_NETHER;
    }
}

RoomId overworld(vector<string>& inventory) {
    string cmd = prompt();

    if(cmd == "flint and steel") {
        println("You light a fire on an osbidian portal.");
        println("You enter in a hot dimension, cald THE NETHER.");
        return RoomId::THE_NETHER;
    } else if(cmd == "chicken jockey") {
        println("The chicken jockey run in your direction.");
        return RoomId::DEATH;
    } else if(cmd == "go strongold") {
        if (can_craft_ender_eye(inventory)) {
            println("You craft ender eyes and locate de strongold.");
            println("You open the end portal, and jump right in it.");
            return RoomId::END;
        } else {
            println("You can't find the strongold yet.");
            return RoomId::OVERWORLD;
        }
    } else {
        println("I don't understand that.");
        return RoomId::OVERWORLD;
    }
}

int main(int argc, char *argv[]) {
    RoomId room=RoomId::OVERWORLD;
    vector<string> inventory;
    bool alive = true;

    println("You spawn in a cubic world.");
    while(alive == true) {
        switch(room) {
        case RoomId::OVERWORLD:
            room = overworld(inventory);
            break;
        case RoomId::THE_NETHER:
            room = the_nether(inventory);
            break;
        case RoomId::END:
            room = end(inventory);
            break;
        case RoomId::DEATH:
            room = death(alive);
            break;
        case RoomId::WIN:
            room = win(alive);
            break;
        }
    }
}
