#include "regroup.hpp"

#include <iostream>
#include <fstream>

std::string Regroup::parse_json_files()
{
    for (auto &&json_file_path : this->input_files_paths)
    {
        // Open each file and parse them
        try
        {
            std::ifstream input_file(json_file_path);
            ordered_json input_json = ordered_json::parse(input_file);
            this->files.push_back(input_json);
        }
        catch (const std::exception &e)
        {
            return e.what();
        }
    }
    return "parse complete";
}

Regroup::Regroup(std::vector<std::string> input_files_paths)
{
}

Regroup::Regroup()
{
}

std::string Regroup::regroup_by_criteria()
{
    std::string ret = this->parse_json_files();
    if (ret != "parse complete")
    {
        return ret;
    }

    std::map<std::string, std::vector<ordered_json>> grouped_bodies; // Store grouped groups

    std::size_t file_number = 0; // Keep track at which file is being computed
    for (const auto &json_file : this->files)
    {

        std::function<void(const ordered_json &)> process_children = [&](const ordered_json &node)
        {
            if (node.contains("children"))
            {
                for (const auto &child : node["children"])
                {
                    process_children(child); // Recursion for searching children deeper
                }
            }
            else if (node["type"] == "body")
            {
                std::string key;
                for (const auto &criteria : this->criterias)
                {
                    if (!key.empty())
                        key += " "; // Separate criterias names

                    if (node.contains(criteria))
                    {
                        key += node[criteria].get<std::string>();
                    }
                    else
                    {
                        key += "undefined"; // If criteria not found
                    }
                }

                grouped_bodies[key].push_back(node);
            }
        };

        process_children(json_file);

        ordered_json result;
        result["name"] = "root";
        result["type"] = "group";

        for (const auto &group : grouped_bodies)
        {
            ordered_json group_node;
            group_node["name"] = "group " + group.first;
            group_node["type"] = "group";
            group_node["children"] = group.second;

            result["children"].push_back(group_node);
        }

        // Create an 'out version' of the file
        std::string new_filename = this->input_files_paths.at(file_number).filename().string(); // Get the filename of the current file being computed
        size_t pos = new_filename.find("in");
        if (pos != std::string::npos) {
            new_filename.replace(pos, 2, "out");
        }

        std::ofstream out_file(this->input_files_paths.at(file_number).parent_path().string() + "/" + new_filename);
        if (!out_file.is_open())
        {
            return "Error : cannot open file.";
        }
        out_file << result.dump(4);
        out_file.close();

        file_number++; // Increment, go through another json file
    }

    return "Regrouping complete, output written to output file";
}

void Regroup::set_json_files_paths(std::vector<std::filesystem::path> json_paths)
{
    this->input_files_paths = json_paths;
}

std::vector<std::filesystem::path> Regroup::get_json_files_paths()
{
    return this->input_files_paths;
}

void Regroup::set_criterias(std::vector<std::string> criterias)
{
    this->criterias = criterias;
}

std::vector<std::string> Regroup::get_criterias()
{
    return this->criterias;
}

std::vector<nlohmann::ordered_json> Regroup::get_json_files()
{
    return this->files;
}

Regroup::~Regroup()
{
}
