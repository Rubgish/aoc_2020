#include "utils.hpp"

int main(int argc, char *argv[])
{
    int64_t card_aim = 19241437;
    // int64_t card_aim = 5764801;
    int64_t door_aim = 17346587;
    // int64_t door_aim = 17807724;

    int64_t card = 1;
    int64_t door = 1;

    int card_loop = 0;
    while (card != card_aim)
    {
        card = ((card * 7) % 20201227);
        card_loop++;
    }
    std::cout << card_loop << "\n";

    int door_loop = 0;
    while (door != door_aim)
    {
        door = (door * 7) % 20201227;
        door_loop++;
    }
    std::cout << door_loop << "\n";
    std::cout << door << "\n";

    for (int i = 1; i < card_loop; i++)
    {
        door = ((door * door_aim) % 20201227);
    }
    std::cout << door << "\n";
}

// 14292335
