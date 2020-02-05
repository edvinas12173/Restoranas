#include <iostream>
#include <string>
#include <vector>

using namespace std;

char func;
bool running = true;

//strukturos
//meniu itemai
struct menu_item {
    string title;
    float price;
};

//uzsakymai
struct order {
    int id;
    int worker_id;
    vector<int> menu_item_ids;
};

//darbuotojai
struct worker {
    string name;
    string last_name;
    string pos;
};

//funkcijos
void showProgramMenu(char &_func);
void showMenu(vector<menu_item> _menu);
void addMenuItem (vector<menu_item> &_menu);
void orderFood(vector<order> &_orders, vector<worker> &_workers, vector<menu_item> &_menu);
void hireWorker(vector<worker> &_workers);
void fireWorker(vector<worker> &_workers);
void payOrder(vector<order> &_orders, vector<menu_item> &_menu);

int main()
{
    //inicializuojami strukturu vektoriai, kitaip sakant dinamiski masyvai
    vector<menu_item> menu;
    vector<order> orders;
    vector<worker> workers;

    cout << "" << endl << endl << endl;
    cout << "############################" << endl;
    cout << "Restoranas 'VIKO KOLEGIJA' " << endl;
    cout << "############################" << endl;
    cout << "" << endl << endl << endl;

    while (running) {
        showProgramMenu(func);

        //ijungiama atitinkama programos funkcija
        switch (func)
        {
            case '1':
                addMenuItem(menu);
                break;
            case '2':
                showMenu(menu);
                break;
            case '3':
                orderFood(orders, workers, menu);
                break;
            case '4':
                hireWorker(workers);
                break;
            case '5':
                fireWorker(workers);
                break;
            case '6':
                payOrder(orders, menu);
                break;
            case '7':
                cout << "Restoranas 'VIKO KOLEGIJA'!" << endl;
                running = false;
                break;
            default:
                cout << "Tokios funkcijos nera!" << endl << endl;
                break;
        }
    }
}

//funkcija programos meniu rodymui
void showProgramMenu(char &_func)
{
    cout << "#####################################" << endl;
    cout << "----------- FUNKCIJOS -----------" << endl;
    cout << "1. Prideti patiekala i meniu" << endl;
    cout << "2. Perziureti restorano meniu" << endl;
    cout << "3. Sukurti uzsakyma" << endl;
    cout << "4. Idarbinti darbuotoja" << endl;
    cout << "5. Atleisti darbuotoja" << endl;
    cout << "6. Apmoketi uzsakymo saskaita" << endl;
    cout << "7. Isjungti programa" << endl;
    cout << "#####################################" << endl;
    cout << endl;
    cout << "Pasirinkite funkcija ivesdami skaiciuka: ";
    cin >> func;
}
//funkcija restorano meniu rodymui
void showMenu(vector<menu_item> _menu)
{
    //jei meniu nera patiekalu
    if (_menu.size() == 0) {
        cout << "Restorano meniu tuscias!" << endl << endl;
        return;
    }

    //jei yra, parodomas meniu
    cout << "Restorano meniu:" << endl;
    for (int i = 0; i < _menu.size(); i++) {
        cout << i+1 << ". "
             << _menu[i].title << ", kaina "
             << _menu[i].price << endl;
    }
    cout << endl;
}
//funkcija patiekalo pridejimui i meniu
void addMenuItem (vector<menu_item> &_menu)
{
    string title;
    float price;

    cout << "Iveskite patiekalo pavadinima: ";
    cin >> title;

    //tikrinama, ar ivesta tinkama kaina, t.y., ar nera raidziu ir kitokiu simboliu
    bool price_not_okay = true;
    while (price_not_okay) {
        cout << "Iveskite patiekalo kaina: ";
        if (!(cin >> price)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Kaina sudaroma is skaiciu, arba skaiciu ir skaiciu po tasko!" << endl;
            continue;
        }

        price_not_okay = false;
    }

    //jei viskas gerai, prie pagrindinio patiekalu masyvo pridedamas naujas patiekalas
    _menu.push_back({title, price});

    cout << "Patiekalas pridetas!" << endl << endl;
}
//maisto uzsakymo funkcija
void orderFood(vector<order> &_orders, vector<worker> &_workers, vector<menu_item> &_menu)
{
    bool order_id_not_okay = true;
    int order_id;
    int worker_id;
    int menu_item_id;
    char yesNo;
    bool doneOrdering = false;

    //jei nera darbuotoju, negalima sukurti uzsakymo
    if (_workers.size() == 0) {
        cout << "Dar neturite darbuotoju, kuriems galite priskirti uzsakyma!" << endl << endl;
        return;
    }

    //jei nera patiekalu meniu, negalima sukurti uzsakymo
    if (_menu.size() == 0) {
        cout << "Dar neturite patiekalu restorano meniu, kuriuos galima uzsisakyti!" << endl << endl;
        return;
    }

    //tikrinama ar ivestas tinkamas uzsakymo numeris, t.y. ar nera raidziu, kitokiu simboliu
    //bei ar dar nera uzsakymo su tokiu numeriu
    while (order_id_not_okay) {
        bool reEnterOrderNumber = false;

        cout << "Iveskite uzsakymo numeri: ";
        if (!(cin >> order_id)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Numeris sudaromas is skaiciu!" << endl;
            continue;
        }

        for (int i = 0; i < _orders.size(); i++) {
            if (order_id == _orders[i].id) {
                cout << "Toks uzsakymo numeris jau egzistuoja!" << endl;
                reEnterOrderNumber = true;
            }
        }

        if (reEnterOrderNumber) continue;

        order_id_not_okay = false;
    }

    order order;
    order.id = order_id;

    //parodomas darbuotoju sarasas, pasirinkimui, kad priskirti uzsakyma darbuotojui
    cout << "Darbuotoju sarasas (vardas, pavarde, pareigos):" << endl;
    for (int i = 0; i < _workers.size(); i++) {
        cout << i+1 << ". "
             << _workers[i].name << " "
             << _workers[i].last_name << " "
             << _workers[i].pos << endl;
    }

    //tikrinama ar ivestas geras darbuotojo numeris, t.y. ar nera raidziu ir kitokiu
    //simboliu bei ar yra toks darbuotojas
    bool worker_id_not_okay = true;
    while (worker_id_not_okay) {
        cout << "Iveskite skaiciuka darbuotojo, kuriam norite priskirti uzsakyma: ";
        if (!(cin >> worker_id)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Darbuotojo skaiciukas sudaromas is skaiciu!" << endl;
            continue;
        }

        if (worker_id > 0 && worker_id <= _workers.size()) {
            order.worker_id = worker_id;
            worker_id_not_okay = false;
            break;
        }

        cout << "Tokio darbuotojo nera, iveskite teisinga skaiciuka" << endl;
    }

    //parodomas patiekalu sarasas
    cout << "Patiekalu sarasas:" << endl;
    for (int i = 0; i < _menu.size(); i++) {
        cout << i+1 << ". "
             << _menu[i].title << ", kaina "
             << _menu[i].price << endl;
    }

    //ciklas, kuris skirtas vienam uzsakymui priskirti daug patiekalu
    while (!doneOrdering) {
        //is pradziu patikrinama ar ivestas geras patiekalo numeris is meniu, t.y. ar nera
        //raidziu, kitokiu simboliu bei ar toks patiekalas pagal numeri egizstuoja
        bool menu_item_id_not_okay = true;
        while (menu_item_id_not_okay) {
            cout << "Iveskite skaiciuka patiekalo, kuri norite priskirti uzsakymui: ";
            if (!(cin >> menu_item_id)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Patiekalo skaiciukas sudaromas is skaiciu!" << endl;
                continue;
            }

            if (menu_item_id > 0 && menu_item_id <= _menu.size()) {
                order.menu_item_ids.push_back(menu_item_id);
                menu_item_id_not_okay = false;
                break;
            }

            cout << "Tokio patiekalo nera, iveskite teisinga skaiciuka" << endl;
        }

        //paklausiama ar norima prideti dar viena patiekala i uzsakyma bei tikrinama ar
        //atsakymui yra ivedama tai, ko prasoma, pvz Y - jei norima prideti dar, N - jei ne
        bool yes_no_is_not_okay = true;
        while (yes_no_is_not_okay) {
            cout << "Ar norite prideti dar viena patiekala i uzsakyma? (Y/N): ";
            cin >> yesNo;

            if (yesNo == 'Y' || yesNo == 'N') {
                if (yesNo == 'N') {
                    doneOrdering = true;
                }
            } else {
                cout << "Ivedete ne tai, ko praseme! Y - taip, N - ne!" << endl;
                continue;
            }

            yes_no_is_not_okay = false;
        }
    }

    //prie pagrindinio uzsakymu masyvo pridedamas naujas uzsakymas
    _orders.push_back(order);
    cout << "Uzsakymas sukurtas!" << endl << endl;
}
//darbuotojo priemimo funkcija
void hireWorker(vector<worker> &_workers)
{
    string name;
    string last_name;
    string pos;

    cout << "Iveskite darbuotojo varda: ";
    cin >> name;
    cout << "Iveskite darbuotojo pavarde: ";
    cin >> last_name;
    cout << "Iveskite darbuotojo pareigas: ";
    cin >> pos;

    //prie pagrindinio darbuotoju masyvo pridedamas naujas darbuotojas
    _workers.push_back({name, last_name, pos});

    cout << "Darbuotojas idarbintas!" << endl << endl;
}
//darbuotojo atleidimo funkcija
void fireWorker(vector<worker> &_workers)
{
    int id;
    bool id_okay = false;

    //tikrinama ar yra darbuotoju, kad butu ka atleisti
    if (_workers.size() == 0) {
        cout << "Dar neturite darbuotoju!"<< endl << endl;
        return;
    }

    //parodomas darbuotoju sarasas
    cout << "Darbuotoju sarasas (vardas, pavarde, pareigos):" << endl;
    for (int i = 0; i < _workers.size(); i++) {
        cout << i+1 << ". "
             << _workers[i].name << " "
             << _workers[i].last_name << " "
             << _workers[i].pos << endl;
    }
    cout << endl;

    //tikrinama ar ivestas geras darbuotojo numeris, t.y. ar nera raidziu bei kitokiu
    //simboliu bei ar toks darbuotojas pagal numeri egzistuoja
    while (!id_okay) {
        cout << "Iveskite skaiciuka darbuotojo, kuri norite atleisti: ";
        if (!(cin >> id)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Darbutojo skaiciukas sudaromas is skaiciu!" << endl;
            continue;
        }

        if (id > 0 && id <= _workers.size()) {
            id_okay = true;
            break;
        }

        cout << "Tokio darbuotojo nera, iveskite teisinga skaiciuka" << endl;
    }

    //is pagrindinio darbuotoju masyvo istrinamas atleidziamas darbuotojas
    _workers.erase(_workers.begin() + id - 1);
    cout << "Darbuotojas atleistas!" << endl << endl;
}
//uzsakymo apmokejimo funkcija
void payOrder(vector<order> &_orders, vector<menu_item> &_menu)
{
    int index;
    int id;
    int menu_item_id;
    char yesNo;

    //tikirnama ar yra uzsakymu, kad butu, ka apmoketi
    if (_orders.size() == 0) {
        cout << "Nera uzsakymu!" << endl;
        return;
    }

    //parodomi turimi uzsakymai
    cout << "Turimi uzsakymu numeriai:" << endl;
    for (int i = 0; i < _orders.size(); i++) {
        cout << _orders[i].id << endl;
    }

    //tikrinama ar ivestas uzsakymo numeris, kuri norima apmoketi yra geras t.y., ar nera
    //raidziu, kitokiu simboliu bei ar uzsakymas tokiu numeriu egzistuoja
    bool continue_while = true;
    bool order_id_not_okay = true;
    while (order_id_not_okay) {
        cout << "Iveskite uzsakymo numeri, kuri norite apmoketi: ";
        if (!(cin >> id)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Uzsakymo numeris sudaromas is skaiciu!" << endl;
            continue;
        }

        for (int i = 0; i < _orders.size(); i++) {
            if (_orders[i].id == id) {
                index = i;
                continue_while = false;
                break;
            }
        }

        if (continue_while) {
            cout << "Tokio uzsakymo nera, iveskite teisinga uzsakymo skaiciuka " << endl;
            continue;
        }

        order_id_not_okay = false;
    }

    //parodoma, kokie patiekalai ieina i uzsakyma ir paskaiciuojama bei parodoma visa
    //uzsakymo suma
    float total = 0.0f;
    cout << "Uzsakymas nr. " << id << ":" << endl;

    for (int i = 0; i < _orders[index].menu_item_ids.size(); i++) {
        for (int j = 0; j < _menu.size(); j++) {
            if (_orders[index].menu_item_ids[i] == j+1) {
                total += _menu[j].price;
                cout << i+1 << " " << _menu[j].title << ", kaina " << _menu[j].price << endl;
            }
        }
    }
    cout << "Bendra uzsakymo suma: " << total << endl;

    //tikrinama ar paklausus, ar norima apmoketi uzsakyma, yra ivesta tai, ko prasoma, t.y.
    //Y - jei norima apmoketi, N - jei ne
    bool yes_no_is_not_okay = true;
    while (yes_no_is_not_okay) {
        cout << "Patvirtinti uzsakymo apmokejima? (Y/N): ";
        cin >> yesNo;

        if (yesNo == 'Y' || yesNo == 'N') {
            if (yesNo == 'Y') {
                cout << "Uzsakymas apmoketas!" << endl << endl;
                _orders.erase(_orders.begin() + id - 1);
                return;
            }
        } else {
            cout << "Ivedete ne tai, ko praseme! Y - taip, N - ne!" << endl;
            continue;
        }

        yes_no_is_not_okay = false;
    }

    cout << "Uzsakymas neapmoketas!" << endl << endl;
}