package com.example.examen.service;

import com.example.examen.domain.*;
import com.example.examen.repository.*;
import com.example.examen.utils.observer.Observer;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Service {
    //repo
    //validator
    //constructor
    //functions

    private final LocationDbRepository locationDbRepository;
    private final HotelDbRepository hotelDbRepository;
    private final SpecialOfferDbRepository specialOfferDbRepository;
    private final ClientDbRepository clientDbRepository;
    private final ReservationDbRepository reservationDbRepository;

    public Service(LocationDbRepository locationDbRepository, HotelDbRepository hotelDbRepository, SpecialOfferDbRepository specialOfferDbRepository, ClientDbRepository clientDbRepository, ReservationDbRepository reservationDbRepository) {
        this.locationDbRepository = locationDbRepository;
        this.hotelDbRepository = hotelDbRepository;
        this.specialOfferDbRepository = specialOfferDbRepository;
        this.clientDbRepository = clientDbRepository;
        this.reservationDbRepository = reservationDbRepository;
    }

    public Iterable<Location> getAllLocations() {
        return this.locationDbRepository.findAll();
    }

    public List<HotelDTO> getAllHotelsDTO() {
        List<HotelDTO> hotelDTOList = new ArrayList<>();
        this.hotelDbRepository.findAll().forEach(hotel -> {
            hotelDTOList.add(new HotelDTO(hotel.getHotelId(), this.locationDbRepository.findOne(hotel.getLocationId()).getLocationName(),
                    hotel.getHotelName(), hotel.getNoRooms(), hotel.getPricePerNight(), hotel.getType()));
        });
        return hotelDTOList;
    }

    public List<HotelDTO> getAllHotelsDTOOfLocation(String locationName) {
        List<HotelDTO> hotelDTOList = new ArrayList<>();
        this.hotelDbRepository.findAll().forEach(hotel -> {
            if(Objects.equals(locationName, "") || Objects.equals(this.locationDbRepository.findOne(hotel.getLocationId()).getLocationName(), locationName))
                hotelDTOList.add(new HotelDTO(hotel.getHotelId(), this.locationDbRepository.findOne(hotel.getLocationId()).getLocationName(),
                    hotel.getHotelName(), hotel.getNoRooms(), hotel.getPricePerNight(), hotel.getType()));
        });
        return hotelDTOList;
    }

    public List<SpecialOffer> getSpecialOffersOfHotel(Double hotelId) {
        List<SpecialOffer> specialOffers = new ArrayList<>();
        this.specialOfferDbRepository.findAll().forEach(specialOffer -> {
            if (specialOffer.getHotelId() == hotelId) {
                specialOffers.add(specialOffer);
            }
        });
        return  specialOffers;
    }


    public List<SpecialOffer> getSpecialOffersOfHotelInRange(Double hotelId, LocalDate startDate, LocalDate endDate) {
        List<SpecialOffer> specialOffers = new ArrayList<>();
        this.specialOfferDbRepository.findAll().forEach(specialOffer -> {
            if (specialOffer.getHotelId() == hotelId && specialOffer.getStartDate().isAfter(startDate) &&
                    specialOffer.getEndDate().isBefore(endDate)) {
                specialOffers.add(specialOffer);
            }
        });
        return  specialOffers;
    }

    public List<SpecialOfferDTO> getSpecialOffersOfClient(Client client) {
        List<SpecialOfferDTO> specialOffers = new ArrayList<>();
        this.specialOfferDbRepository.findAll().forEach(specialOffer -> {
            if (client.getFidelityGrade() > specialOffer.getPercents() &&
                    specialOffer.getStartDate().isAfter(LocalDate.now()))
                specialOffers.add(
                        new SpecialOfferDTO(specialOffer.getSpecialOfferId(),
                                hotelDbRepository.findOne(specialOffer.getHotelId()).getHotelName(),
                                locationDbRepository.findOne(hotelDbRepository.findOne(specialOffer.getHotelId()).getLocationId()).getLocationName(),
                                specialOffer.getStartDate(), specialOffer.getEndDate())
                );
        });
        return specialOffers;
    }

    public Client getClient(Long clientId) {
        return clientDbRepository.findOne(clientId);
    }

    public void saveReservation(Reservation reservation){
        reservationDbRepository.save(reservation);
    }

    public void addObservers(Observer observer) {
        System.out.println("HERE");
        this.reservationDbRepository.addObserver(observer);
    }

    public String getHotelName(Double hotelId) {
        return this.hotelDbRepository.findOne(hotelId).getHotelName();
    }
}
