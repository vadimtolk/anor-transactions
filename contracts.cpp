#include "header.h"

bool stakeAnorContract(User* this_user, unsigned expiration_time, unsigned anor_value) {
    unsigned anor_price = 0;

    std::cout << "Enter 1 ANOR price : ";
    std::cin >> anor_price;

    if (anor_price > std::pow(2, 32) - 1) {
        std::cout << "Very high price.\n";
        return false;
    }

    if (this_user->own_anor >= anor_value) {
        this_user->anor_price = anor_price;
        this_user->own_anor -= anor_value;
        this_user->staked_anor += anor_value;
        this_user->avalible_anor = this_user->staked_anor;

        anor_marketplace[this_user->public_key] = {this_user->avalible_anor, anor_price, expiration_time};
        return true;
    } 
    
    std::cout << "You havent " << anor_value << " ANOR.\n";
    return false;
}

bool buyAnorContract(User* this_user, unsigned address, unsigned anor_value) {
    User*& contragent = users[address];
    unsigned& contragent_anor_value = anor_marketplace[address][0];
    unsigned& anor_price = anor_marketplace[address][1];
    unsigned& expiration_time = anor_marketplace[address][2];

    if (this_user->pseudo_balance >= anor_price * anor_value && contragent_anor_value >= anor_value) {
        unsigned locked_balance = anor_price * anor_value;

        contragent->avalible_anor -= anor_value;
        this_user->bought_anor += anor_value;
        this_user->pseudo_balance -= locked_balance;

        std::cout << "You bougth " << anor_value << " ANOR from " << address << ". Expiration time : " << expiration_time << '\n';

        unsigned alert_time = expiration_time - 4000;

        Sleep(alert_time); //  3'600'000 == 1 hour
        std::cout << "Alert! You ANOR transaction will be expirated of " << expiration_time - alert_time << " s\n";
        Sleep(expiration_time - alert_time); // expiration emulation. It will be work with threads and async

        this_user->bought_anor -= anor_value;
        contragent->pseudo_balance += locked_balance;
        contragent->avalible_anor += anor_value;

        return true;
    }  

    std::cout << "You balance is low or contragent haven't neccesary ANOR.\n";
    return false;
}

std::pair<const bool, const unsigned*> unstakeAnorContract(User* this_user) {
    if (this_user->staked_anor && (this_user->avalible_anor == this_user->staked_anor)) {
        std::pair<const bool, const unsigned*> result = std::make_pair(true, new unsigned(this_user->avalible_anor));

        anor_marketplace.erase(this_user->public_key);
        this_user->own_anor += this_user->avalible_anor;
        this_user->avalible_anor = this_user->staked_anor = 0;

        return result;
    }
    return std::make_pair(false, nullptr);
}