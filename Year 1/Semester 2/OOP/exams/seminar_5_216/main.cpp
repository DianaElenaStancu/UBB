#include <QApplication>
#include <QPushButton>
#include "service.h"
#include <iostream>
#include "conutry_ui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repository<Country> repo;
    Service service{repo};

    service.add("Romania","Bucharest",20);
    service.add("Germny","Berlin",80);
    service.add("France","Paris",60);
    service.add("Englnd","London",40);


    for(auto&elem:service.find_by_population(50)){
        std::cout<<elem.get_name()<<std::endl;
    }
    std::cout<<"here";
    CountryUI ui{service};
    ui.show();
    return QApplication::exec();
}
