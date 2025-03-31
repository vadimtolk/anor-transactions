#include <iostream>
#include <windows.h>
#include <cstdio>
#include <memory>
#include <array>
#include <map>
#include <cmath>

typedef unsigned anor_32;

class User;

using StakeAnorContract = bool (*)(User* this_user, unsigned expiration_time, unsigned anor_value);
using BuyAnorContract = bool (*)(User* this_user, unsigned address, unsigned anor_value);
using UnstakeAnorContract = std::pair<const bool, const unsigned*> (*)(User* this_user);

/*make struct with theese functions (private fields)*/

bool stakeAnorContract(User* this_user, unsigned expiration_time, unsigned anor_value);
bool buyAnorContract(User* this_user, unsigned address, unsigned anor_value);
std::pair<const bool, const unsigned*> unstakeAnorContract(User* this_user);

class User {
    friend bool stakeAnorContract(User* this_user, unsigned expitarion_time, unsigned anor_value);
    friend bool buyAnorContract(User* this_user, unsigned address, unsigned anor_value);
    friend std::pair<const bool, const unsigned*> unstakeAnorContract(User* this_user);

    private:
        anor_32 own_anor = 0;
        anor_32 bought_anor = 0;

        const unsigned public_key;
        const unsigned private_key; 

        unsigned anor_price = 0;
        unsigned pseudo_balance = 0;

        //unsigned staked_balance = 0;
        anor_32 staked_anor = 0;
        anor_32 avalible_anor = 0;

        User(unsigned pub_key, unsigned priv_key, unsigned own_anor, unsigned pseudo_bal);
    public:
        static unsigned createUser(unsigned pub_key, unsigned priv_key, unsigned own_anor, unsigned pseudo_bal);

        void stakeAnor(StakeAnorContract contract, unsigned expitarion_time, unsigned anor_value); 
        void unstakeAnor(UnstakeAnorContract contract);
        void buyAnor(BuyAnorContract contract, unsigned address, unsigned anor_value);

        void getInfo();
};

extern std::map<unsigned, User*> users;
extern std::map<unsigned, std::array<unsigned, 3>> anor_marketplace;

