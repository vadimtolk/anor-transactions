#include "header.h"

User::User(unsigned pub_key, unsigned priv_key, unsigned own_anor, unsigned pseudo_bal) : public_key{pub_key}, private_key{priv_key} {
    this->own_anor = own_anor;
    this->pseudo_balance = pseudo_bal;
}

unsigned User::createUser(unsigned pub_key, unsigned priv_key, unsigned own_anor, unsigned pseudo_bal) {
    users[pub_key] = new User(pub_key, priv_key, own_anor, pseudo_bal);
    return pub_key;
}

void User::stakeAnor(StakeAnorContract contract, unsigned expiration_time, unsigned anor_value) {
    const bool result = contract(this, expiration_time, anor_value);
    if (result) std::cout << "Success. You make order on " << anor_value << " ANOR. Price : " << anor_price << " FUTH | Expiration Time : " << expiration_time << " s\n";
}

void User::buyAnor(BuyAnorContract contract, unsigned address, unsigned anor_value) {
    const bool result = contract(this, address, anor_value);
    if (result) std::cout << "Success. The transaction was done.\n";
}

void User::unstakeAnor(UnstakeAnorContract contract) {
    std::pair<const bool, const unsigned*> result = contract(this);
    if (result.first) {
        std::cout << "You unstaked " << *result.second << " ANOR.\n";
        delete result.second;
    }

    else std::cout << "You must finished all your transactions with ANOR before unstake them.\n";
}

void User::getInfo() {
    std::cout << "User : " << public_key << 
    "\n\tOwn ANOR : " << own_anor <<
    "\n\tBought ANOR : " << bought_anor <<
    "\n\tStaked ANOR : " << staked_anor <<
    "\n\tAvalible ANOR from stake: " << staked_anor <<
    "\n\tAnor Price : " << anor_price << " FUTH/ANOR" <<
    "\n\tBalance : " << pseudo_balance << " FUTH\n";
}