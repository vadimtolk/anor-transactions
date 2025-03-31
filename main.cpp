#include "header.h"

std::map<unsigned, User*> users = {};
std::map<unsigned, std::array<unsigned, 3>> anor_marketplace = {};

int main() {
    const unsigned vadim = User::createUser(1, 11, 1000, 1000);
    const unsigned sher = User::createUser(2, 22, 1000, 1000);

    User* user_vadim = users[vadim];
    User* user_sher = users[sher];

    user_vadim->stakeAnor(stakeAnorContract, 6000, 300);
    user_sher->buyAnor(buyAnorContract, vadim, 300);

    user_vadim->getInfo();
    user_sher->getInfo();

    user_vadim->unstakeAnor(unstakeAnorContract);
    user_vadim->getInfo();

    return 0;
}