package com.example.examen.service;

import com.example.examen.domain.*;
import com.example.examen.repository.Repository;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Service {
    //repo
    //validator
    //constructor
    //functions
    private final Repository<Double, Location> locationRepository;
    private final Repository<Double, Hotel> hotelRepository;

    private final Repository<Double, SpecialOffer> specialOfferRepository;

    private final Repository<Long, Client> clientRepository;





    public Service(Repository<Double, Location> locationRepository, Repository<Double, Hotel> hotelRepository, Repository<Double, SpecialOffer> specialOfferRepository, Repository<Long, Client> clientRepository) {
        this.locationRepository = locationRepository;
        this.hotelRepository = hotelRepository;
        this.specialOfferRepository = specialOfferRepository;
        this.clientRepository = clientRepository;
    }


    public Iterable<Location> getAllLocations(){
        return this.locationRepository.findAll();
    }

    public Iterable<Hotel> getAllHotels(){
        return this.hotelRepository.findAll();
    }


    public List<HotelDTO> getAllHotelsDTO(){
        List<HotelDTO> hotelsDTO = new ArrayList<>();
        this.hotelRepository.findAll().forEach(
                hotel -> {
                    hotelsDTO.add(new HotelDTO(hotel.getId(), this.locationRepository.findOne(hotel.getLocationId()).getLocationaName(),
                            hotel.getHotelName(), hotel.getNoRooms(), hotel.getPricePerNight(),
                            hotel.getType()));
                }
        );

        return hotelsDTO;
    }

    public List<SpecialOffer> getOffersOfHotel(Double hotelId) {
        List<SpecialOffer> specialOffers = new ArrayList<>();
        this.specialOfferRepository.findAll().forEach(
                specialOffer -> {
                    if (Objects.equals(specialOffer.getHotelId(), hotelId) || hotelId == 0)
                        specialOffers.add(specialOffer);
                }
        );
        return specialOffers;
    }

    public Client findClient(Long clientId) {
        return this.clientRepository.findOne(clientId);
    }
}
