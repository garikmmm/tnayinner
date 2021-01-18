#include <string>
#include <unordered_map>
#include <sstream>
class api {
private:
   std::unordered_map<std::string, std::string> *db;
   int index;
   std::string get_index_as_string();

public:
    api();
    ~api();
    std::string convert_to_short_url(std::string);
    std::string get_original_url(std::string);
};


