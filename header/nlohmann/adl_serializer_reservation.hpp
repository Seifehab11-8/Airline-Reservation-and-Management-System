#pragma once
#include "json.hpp"
#include "../flight/Reservation.hpp"
#include "../payment/IPayment.hpp"
#include "../payment/Paypal.hpp"
#include "../payment/CreditCard.hpp"
#include "../payment/Cash.hpp"

namespace nlohmann
{
    template <>
    struct adl_serializer<Reservation>
    {
        static void to_json(json& j, const Reservation& p)
        {
            j = json{{"flightNumber", p.getFlightNumber()},
                    {"passengerUsername", p.getPassengerUsername()},
                    {"seatNumber", p.getSeatNumber()},
                    {"id", p.getID()},
                    {"status", p.getStatus()},
                    {"paymentMethodType", p.getPaymentMethodType()},
                    {"pricePaid", p.getPricePaid()}};

            if(p.getPaymentMethodType() == "CreditCard")
            {
                std::shared_ptr<CreditCard> cc = std::dynamic_pointer_cast<CreditCard>(p.getPaymentMethod());
                if (cc)
                {
                    j["paymentMethod"] = json{
                        {"cardNumber", cc->getCardNumber()},
                        {"cardHolderName", cc->getCardHolderName()},
                        {"cvv", cc->getCVV()}};
                }
            }
            else if(p.getPaymentMethodType() == "Paypal")
            {
                std::shared_ptr<Paypal> pp = std::dynamic_pointer_cast<Paypal>(p.getPaymentMethod());
                if (pp)
                {
                    j["paymentMethod"] = json{
                        {"email", pp->getEmail()},
                        {"password", pp->getPassword()}};
                }
            }
            else if(p.getPaymentMethodType() == "Cash")
            {
                j["paymentMethod"] = json{};
            }
        }

        static void from_json(const json& j, Reservation& p)
        {
            p.setFlightNumber(j.at("flightNumber").get<std::string>());
            p.setPassengerUsername(j.at("passengerUsername").get<std::string>());
            p.setSeatNumber(j.at("seatNumber").get<std::string>());
            p.setID(j.at("id").get<int>());
            p.setStatus(j.at("status").get<std::string>());
            p.setPaymentMethodType(j.at("paymentMethodType").get<std::string>());
            p.setPricePaid(j.at("pricePaid").get<double>());

            if (p.getPaymentMethodType() == "CreditCard")
            {
                std::shared_ptr<CreditCard> cc = std::make_shared<CreditCard>();
                cc->setCardNumber(j.at("paymentMethod").at("cardNumber").get<std::string>());
                cc->setCardHolderName(j.at("paymentMethod").at("cardHolderName").get<std::string>());
                cc->setCVV(j.at("paymentMethod").at("cvv").get<std::string>());
                p.setPaymentMethod(cc);
            }
            else if (p.getPaymentMethodType() == "Paypal")
            {   
                std::shared_ptr<Paypal> pp = std::make_shared<Paypal>();
                pp->setEmail(j.at("paymentMethod").at("email").get<std::string>());
                pp->setPassword(j.at("paymentMethod").at("password").get<std::string>());
                p.setPaymentMethod(pp);
            }
            else if (p.getPaymentMethodType() == "Cash")
            {
                p.setPaymentMethod(std::make_shared<Cash>());
            }
        }
    };
} // namespace nlohmann

