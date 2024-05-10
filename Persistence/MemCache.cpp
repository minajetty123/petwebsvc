#include "MemCache.h"
#include <boost/date_time/posix_time/posix_time.hpp>

MemCache::MemCache() {
    std::cout<<"MemoryCache is initialized";
}

Pet* MemCache::createPet(const std::string& name) {
    auto pet = new Pet;
    pet->id = this->pets.size() + 1;
    pet->name = name;
    pet->createdAt = boost::posix_time::second_clock::universal_time();
    pets.push_back(pet);
    return pet;
}

std::optional<Pet*> MemCache::getPet(unsigned long id) {
    for (const auto& pet : this->pets) {
        if (pet->id == id) {
            return pet;
        }
    }
    return std::nullopt;
}

std::vector<Pet*> MemCache::listPets() {
    return this->pets;
}

bool MemCache::deletePet(unsigned long id) {
    for (auto it = this->pets.begin(); it != this->pets.end(); ++it) {
        if ((*it)->id == id) {
            const auto deletedPet = pets.erase(it);
            delete *deletedPet;
            return true;
        }
    }
    return false;
}
