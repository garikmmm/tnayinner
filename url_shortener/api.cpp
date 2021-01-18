#include "api.h"

api::api() {
    db = new std::unordered_map<std::string, std::string>;
    index = 0;
}

api::~api() {
    delete db;
}

std::string api::get_index_as_string() {
    std::stringstream stream;
    stream << std::hex << index;
    std::string result( stream.str() );
    return result;
}

std::string api::convert_to_short_url(std::string url) {
    ++index;
    std::string key = get_index_as_string();
    db[key] = url;
    return key;
}

std::string api::get_original_url(std::string key) {
    std::unordered_map<std::string, std::string>::const_iterator it = db->find(key);
    if (it == db->end()) {
        return "";
    }
    return it->second;
}


