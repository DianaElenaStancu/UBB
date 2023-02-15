package com.example.examen.service;

import com.example.examen.domain.City;
import com.example.examen.domain.Event;
import com.example.examen.domain.TrainStation;
import com.example.examen.repository.CityDbRepository;
import com.example.examen.repository.TrainStationsDbRepository;
import com.example.examen.utils.observer.ConcreteObservable;

import java.util.*;

public class Service extends ConcreteObservable<Event> {
    private final CityDbRepository cityDbRepository;
    private final TrainStationsDbRepository trainStationsDbRepository;
    private static final float PRET_PER_STATIE = 10;

    private List<Event> eventList = new ArrayList<>();

    public Service(CityDbRepository cityDbRepository, TrainStationsDbRepository trainStationsDbRepository) {
        this.cityDbRepository = cityDbRepository;
        this.trainStationsDbRepository = trainStationsDbRepository;
    }

    public List<City> getAllCities(){
        List<City> cities = new ArrayList<>();
        this.cityDbRepository.findAll().forEach(
                cities::add
        );
        return cities;
    }

    public void removePers(City departureCity, City destinationCity, int clientId) {
        notifyObservers(departureCity, destinationCity, clientId);
        for(int index = 0; index < eventList.size(); index++) {
            Event event = eventList.get(index);
            if ((departureCity != null && Objects.equals(event.getCities().get(0), departureCity.getId())) &&
                    (destinationCity != null && Objects.equals(event.getCities().get(1), destinationCity.getId()))) {
                if (event.getCount() != 0) {
                    eventList.get(index).setCount(eventList.get(index).getCount()-1);
                }
            }
        }
    }
    private int getNoPers(City departureCity, City destinationCity, int clientId){
        for (Event event : eventList) {
            if (Objects.equals(event.getCities().get(0), departureCity.getId()) && Objects.equals(event.getCities().get(1), destinationCity.getId())){

               if(clientId != event.getClientId()) {
                   event.setCount(event.getCount()+1);
                   return event.getCount();
               } else {
                   return event.getCount();
               }
            }
        }
        List<String> list = new ArrayList<>();
        list.add(departureCity.getId());
        list.add(destinationCity.getId());
        eventList.add(new Event(1, list, clientId));
        return 1;
    }

    public void notifyObservers(City departureCity, City destinationCity, int clientId){
        List<String> list = new ArrayList<>();
        list.add(departureCity.getId());
        list.add(destinationCity.getId());
        notifyObservers(new Event(getNoPers(departureCity, destinationCity, clientId), list, clientId));
    }

    public int getNoStations(String route) {
        int noStations = 0;
        for(int ch = 0; ch < route.length(); ch++) {
            if (route.charAt(ch) == '>') {
                ++noStations;
            }
        }
        return noStations;
    }

    public List<String> getListWithPrices(List<String> list){
        List<String> listWithPrices = new ArrayList<>();
        list.forEach(element ->{
            element+= ", price: " + (getNoStations(element)*PRET_PER_STATIE);
            listWithPrices.add(element);
        });
        return listWithPrices;
    }

    public List<String> getDirectRoutes(City departureCity, City destinationCity, Map<String, String> citiesNames, List<String> finalRoutes){
        Map<String, List<TrainStation>> stations = new HashMap<>();
        trainStationsDbRepository.findAll().forEach(trainStation -> {
            String key = trainStation.getTrainId();
            if(!stations.containsKey(key))
                stations.put(key, new ArrayList<>());
            stations.get(key).add(trainStation);
        });

        stations.forEach((trainId, trainStations) -> {
            List<List<TrainStation>> results = new ArrayList<>();
            bkt(departureCity.getId(), destinationCity.getId(), trainStations, new ArrayList<>(), results);

            results.forEach(route->{
                var ref = new Object() {
                    String ruta = "";
                };
                ref.ruta += departureCity.getName();

                route.forEach(station->{
                    ref.ruta += "-" + station.getTrainId() + "->" +citiesNames.get(station.getDestinationCityId());
                });

                finalRoutes.add(ref.ruta);
            });
        });
        return finalRoutes;
    }

    public List<String> getAllRoutes(City departureCity, City destinationCity,  Map<String, String> citiesNames, List<String> finalRoutes) {
        List<TrainStation> trainStations = new ArrayList<>();
        trainStationsDbRepository.findAll().forEach(trainStation -> {
            trainStations.add(trainStation);
        });

        List<List<TrainStation>> results = new ArrayList<>();
        bkt(departureCity.getId(), destinationCity.getId(), trainStations, new ArrayList<>(), results);

        results.forEach(route->{
            var ref = new Object() {
                String ruta = "";
            };
            ref.ruta += departureCity.getName();

            route.forEach(station->{
                ref.ruta += "--" + station.getTrainId() + "-->" + citiesNames.get(station.getDestinationCityId());
            });

            finalRoutes.add(ref.ruta);
        });
        return finalRoutes;
    }

    public List<String> getRoutes(City departureCity, City destinationCity, Boolean direct, int clientId) {

        notifyObservers(departureCity, destinationCity, clientId);

        Map<String, String> cities = new HashMap<>();
        cityDbRepository.findAll().forEach(city -> {
            cities.put(city.getName(), city.getId());
        });

        Map<String, String> citiesNames = new HashMap<>();
        cityDbRepository.findAll().forEach(city -> {
            citiesNames.put(city.getId(), city.getName());
        });

        List<String> finalRoutes = new ArrayList<>();

        if(direct) {
            getDirectRoutes(departureCity, destinationCity, citiesNames, finalRoutes);
        }
        else {
            getAllRoutes(departureCity, destinationCity, citiesNames, finalRoutes);
        }

        return finalRoutes;
    }

    private void bkt(String departure, String destination, List<TrainStation> trainStations, List<TrainStation> col, List<List<TrainStation>> results) {
        if(departure.equals(destination)) {
            results.add(col.stream().toList());
        }
        trainStations.forEach(trainStation -> {
            if(trainStation.getDepartureCityId().equals(departure)) {
                col.add(trainStation);
                bkt(trainStation.getDestinationCityId(), destination, trainStations, col, results);
                col.remove(col.size()-1);
            }
        });
    }

}
