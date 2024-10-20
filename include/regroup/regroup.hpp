#if !defined(REGROUP_HPP)
#define REGROUP_HPP

#include <vector>
#include <string>
#include <json.hpp>

using json = nlohmann::json;

class Regroup
{
private:
    std::vector<std::string> input_files_paths;
    std::vector<json> files;
    std::vector<std::string> criterias;
private: 
    std::string parse_json_files();
    
public:
    Regroup(std::vector<std::string> input_files_paths);
    Regroup();
    ~Regroup();

    void regroup_by_criteria();

    void set_json_files_paths(std::vector<std::string> json_paths);
    std::vector<std::string> get_json_files_paths();

    void set_criterias(std::vector<std::string> criterias);
    std::vector<std::string> get_criterias();

    std::vector<json> get_json_files();
};

#endif // REGROUP_HPP
