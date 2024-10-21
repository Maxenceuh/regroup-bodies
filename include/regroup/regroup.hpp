#if !defined(REGROUP_HPP)
#define REGROUP_HPP

#include <vector>
#include <string>
#include <json.hpp>

using ordered_json = nlohmann::ordered_json;

/// @brief A class to regroup bodies inside a JSON file according to some criterias. Every JSON file listed follow one set of criterias.
class Regroup
{
private:
    std::vector<std::filesystem::path> input_files_paths;
    std::vector<ordered_json> files;
    std::vector<std::string> criterias;
private: 
    /// @brief Open, read and deserialize json file(s).
    /// @return 
    std::string parse_json_files();
    
public:
    Regroup(std::vector<std::string> input_files_paths);
    Regroup();
    ~Regroup();

    /// @brief Performs regrouping according to criteria(s) and store the result in an output JSON file.
    /// @return 
    std::string regroup_by_criteria();

    /// @brief Set the path(s) of the file(s) for regrouping.
    /// @param json_paths path/to/the/json/file.json
    void set_json_files_paths(std::vector<std::filesystem::path> json_paths);

    /// @brief Get path(s) of the JSON file(s) set by the ```set_json_files_paths()``` method.
    /// @return A standard container to access set paths by the ```set_json_files_paths()``` method.
    std::vector<std::filesystem::path> get_json_files_paths();

    /// @brief Set criterias to group bodies inside the JSON file.
    /// @param criterias Attributes in JSON file to group bodies.
    void set_criterias(std::vector<std::string> criterias);
    std::vector<std::string> get_criterias();

    /// @brief Get the deserialized JSON files if parsed.
    /// @return A standard container to access JSON files.
    std::vector<ordered_json> get_json_files();
};

#endif // REGROUP_HPP
