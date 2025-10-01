#include <iostream>
#include <windows.h>
#include <clocale>
#include <string>
#include <vector>

class Monitor {
private:
    std::string name;
public:
    Monitor(std::string n) {
        name = n;
    }

    std::string get_name() {
        return name;
    }
};

class Computer {
private:
    Computer() {
        std::cout << "Computer создан!\n";
    }

    std::vector<Monitor> items;

public:
    static Computer& getInstance() {
        static Computer instance;
        return instance;
    }

    void add_monitor(Monitor& m) {
        items.push_back(m);
        std::cout << m.get_name() << " добавлен\n";
    }

    void print_all_monitors() {
        if (items.size() == 0) {
            std::cout << "В Computer нет мониторов\n";
        }
        else {
            std::cout << "Computer соджержит:\n";
            for (int i = 0; i < items.size(); i++) {
                std::cout << "Монитор " << i + 1 << ": " << items[i].get_name() << "\n";
            }
        }
    }
};

int main1()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::locale::global(std::locale("Russian_Russia.1251"));

    // part1
    std::cout << "Первая часть\n";
    Monitor m1("monitor1");
    Monitor m2("monitor2");

    Computer& comp = Computer::getInstance();

    comp.add_monitor(m1);
    comp.add_monitor(m2);

    comp.print_all_monitors();

    return 0;

}
