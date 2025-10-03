#include <iostream>
#include <windows.h>
#include <clocale>
#include <string>
#include <vector>
#include <limits>
#undef max

enum class Status { StationOk = 0, StationBad = 1, WorkerInWork = 10, WorkerRest = 11 };

class PayPlan {
private:
    int id;
    std::string name;
    float cost;

    static int generate_id() {
        static int counter = 0;
        return counter++;
    }
public:
    PayPlan(std::string n = "", float c = 0) {
        id = generate_id();
        name = n;
        cost = c;
    }

    float get_cost() {
        return cost;
    }

    std::string get_name() {
        return name;
    }

    int get_id() {
        return id;
    }
};

class Client {
private:
    static int generate_id() {
        static int counter = 0;
        return counter++;
    }

    int id;
    std::string name;
    PayPlan pay_plan;
    int traffic; // 1 = 1Мб

public:
    Client(std::string n, PayPlan i, int t = 0) {
        id = generate_id();
        name = n;
        pay_plan = i;
        traffic = t;
    }

    std::string get_name() {
        return name;
    }

    int get_id() {
        return id;
    }

    PayPlan get_pay_plan() {
        return pay_plan;
    }

    int get_traffic() {
        return traffic;
    }

    float get_cost_of_trafic() {
        return traffic * pay_plan.get_cost();
    }

    void change_traffic(int t) {
        traffic = t;
    }
};

class Worker {
private:
    static int generate_id() {
        static int counter = 0;
        return counter++;
    }

    int id;
    std::string name;
    std::string email;
    Status status;

public:
    Worker(std::string n, std::string e, Status s) {
        id = generate_id();
        name = n;
        email = e;
        status = s;
    }
};

class Station {
private:
    static int generate_id() {
        static int counter = 0;
        return counter++;
    }

    int id;
    std::string adress;
    Status status;

public:
    Station(std::string a, Status s) {
        id = generate_id();
        adress = a;
        status = s;
    }
};

class InternetOperator {
private:
    static InternetOperator* instance;

    InternetOperator() {
        std::cout << "InternetOperator создан!\n";
    }

    std::vector<Client> clients;
    std::vector<Worker> workers;
    std::vector<Station> stations;
    std::vector<PayPlan> pay_plans;

public:
    static InternetOperator* getInstance() {
        if (instance == nullptr) {
            instance = new InternetOperator();
        }

        return instance;
    }

    void add_pay_plan(std::string n, float c) {
        if (c >= 0 and n != "") {
            pay_plans.push_back(PayPlan(n, c));
        }
        else {
            std::cout << "Неверные значения" << std::endl;
        }
    }

    void print_pay_plans() {
        for (int i = 0; i < pay_plans.size(); i++) {
            std::cout << "\nТариф " << '"' << pay_plans[i].get_name() << '"' << std::endl;
            std::cout << "Id: " << pay_plans[i].get_id() << " Цена за 1Мб: " << pay_plans[i].get_cost() << std::endl;
        }
    }

    void register_client(std::string n, int id_pay_plan, int t = 0) {
        if (n == "" or t < 0) {
            std::cout << "Неверные значения" << std::endl;
        }

        for (int i = 0; i < pay_plans.size(); i++) {
            if (pay_plans[i].get_id() == id_pay_plan) {
                clients.push_back(Client(n, pay_plans[i], t));
                return;
            }
        }
        std::cout << "Не существует такого id" << std::endl;

    }

    void print_clients() {
        for (int i = 0; i < clients.size(); i++) {
            std::cout << "\nКлиент " << '"' << clients[i].get_name() << '"' << std::endl;
            std::cout << "Id: " << clients[i].get_id() << " Id тарифа: " << clients[i].get_pay_plan().get_id() << std::endl;
        }
    }

    void change_client_traffic(int t, int id_client) {
        for (int i = 0; i < clients.size(); i++) {
            if (clients[i].get_id() == id_client) {
                clients[i].change_traffic(t);
                std::cout << "\nТекущий трафик пользователя " << clients[i].get_name() << " теперь равен " << t << std::endl;
                return;
            }
        }
        std::cout << "Не существует такого id клиента" << std::endl;

    }

    void get_cost_all_trafic() {
        double value = 0;
        for (int i = 0; i < clients.size(); i++) {
            value += clients[i].get_cost_of_trafic();
        }
        std::cout << "Всего компания заработала: " << value << "\n";
    }

    void find_profit_client() {
        float max = 0;
        int id_profit_client = -1;

        if (clients.size() == 0) {
            std::cout << "Нет клиентов\n";
            return;
        }

        for (int i = 0; i < clients.size(); i++) {
            if (clients[i].get_cost_of_trafic() > max) {
                id_profit_client = clients[i].get_id();
            }
        }

        for (int i = 0; i < clients.size(); i++) {
            if (id_profit_client == clients[i].get_id()) {
                std::cout << "Самый денежный клиент: " << clients[i].get_name() << "\n";
            }
        }
    }

    ~InternetOperator() {
        std::cout << "=== Деструктор InternetOperator ===" << std::endl;
        std::cout << "Удалено клиентов: " << clients.size() << std::endl;
        std::cout << "Удалено тарифов: " << pay_plans.size() << std::endl;
    }
};

InternetOperator* InternetOperator::instance = nullptr;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::locale::global(std::locale("Russian_Russia.1251"));

    InternetOperator* operator_1 = InternetOperator::getInstance();

    std::cout << "Добавьте тарифы" << std::endl;
    std::string cancel = "";

    while (cancel != "1") {
        std::string name;
        float cost;
        try {
            std::cout << "Название тарифа: ";
            std::cin >> name;
            std::cout << "Стоимость тарифа: ";
            std::cin >> cost;
        }
        catch (...) {
            std::cout << "Что-то не так, попробуйте заново" << std::endl;
            continue;
        }

        if (std::cin.fail()) {
            std::cout << "Что-то не так, попробуйте заново" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        operator_1->add_pay_plan(name, cost);
        std::cout << "Это был последний тариф? (да - 1, нет - иное): ";
        std::cin >> cancel;
    }

    std::cout << "Вы записали следующие тарифы:" << std::endl;
    operator_1->print_pay_plans();

    std::cout << "\nДобавьте клиентов" << std::endl;
    cancel = "";

    while (cancel != "1") {
        std::string name;
        int id_pp;
        int t;
        try {
            std::cout << "Имя клиента: ";
            std::cin >> name;
            std::cout << "Id тарифа клиента: ";
            std::cin >> id_pp;
        }
        catch (...) {
            std::cout << "Что-то не так, попробуйте заново";
            continue;
        }
        try {
            std::cout << "Трафик клиента: ";
            std::cin >> t;
        }
        catch (...) {
            std::cout << "Что-то не так, попробуйте заново";
            continue;
        }
        if (std::cin.fail()) {
            std::cout << "Что-то не так, попробуйте заново" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        operator_1->register_client(name, id_pp, t);
        std::cout << "Это был последний клиент? (да - 1, нет - иное): ";
        std::cin >> cancel;
    }

    std::cout << "Вы записали следующих клиентов:" << std::endl;
    operator_1->print_clients();

    cancel = "";
    std::cout << "\nЖелаете поменять трафик клиентов? (да - 1, нет - иное): ";
    std::cin >> cancel;

    while (cancel == "1") {
        int id;
        int t;
        try {
            std::cout << "Введите id клиента: ";
            std::cin >> id;
        }
        catch (...) {
            std::cout << "Что-то не так, попробуйте заново";
            continue;
        }
        try {
            std::cout << "Введите трафик клиента: ";
            std::cin >> t;
        }
        catch (...) {
            std::cout << "Что-то не так, попробуйте заново";
            continue;
        }
        if (std::cin.fail()) {
            std::cout << "Что-то не так, попробуйте заново" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        operator_1->change_client_traffic(t, id);
        std::cout << "\nЖелаете продолжить? (да - 1, нет - иное): ";
        std::cin >> cancel;
    }

    operator_1->get_cost_all_trafic();

    operator_1->find_profit_client();

    delete operator_1;

    return 0;
}
