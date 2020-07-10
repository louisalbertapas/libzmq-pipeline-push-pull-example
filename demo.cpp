#include <cstdlib>
#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Please input one arguments. (number of workers)" << std::endl;
        return 0;
    }
    else
    {
        int n = std::stoi(argv[1]);
        if (n <= 0)
        {
            std::cout << "number of worker should be greater than 0" << std::endl;
            return 0;
        }

        system("dbus-launch gnome-terminal -- \"./dispatcher\"");
        for (int i = 0; i < n; ++i)
            system("dbus-launch gnome-terminal -- \"./worker\"");
        system("dbus-launch gnome-terminal -- \"./output\"");

    }
}
