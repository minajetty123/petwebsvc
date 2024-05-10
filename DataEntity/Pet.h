#ifndef PET_H
#define PET_H

#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>

struct Pet {
    unsigned long id;
    std::string name;
    boost::posix_time::ptime createdAt;
};

#endif // PET_H
