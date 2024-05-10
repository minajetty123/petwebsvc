#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <optional>
#include <string>
#include "../DataEntity/Pet.h"
#include <optional>

class MemCache{
public:
    std::vector<Pet*> pets;
    MemCache();
    Pet* createPet(const std::string& name);
    std::optional<Pet*> getPet(unsigned long id);
    std::vector<Pet*> listPets();
    bool deletePet(unsigned long id);
};

#endif // DATABASE_H
