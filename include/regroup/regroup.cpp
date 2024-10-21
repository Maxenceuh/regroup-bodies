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
    
    // Store grouped groups
    std::map<std::string, std::vector<ordered_json>> grouped_bodies;

    for (const auto &input_json : this->files)
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

        process_children(input_json);
    }

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

    std::ofstream out_file("out.json");
    if (!out_file.is_open())
    {
        return "Error : cannot open file.";
    }
    out_file << result.dump(4);
    out_file.close();

    return "regrouping complete, output written to out.json";
}

void Regroup::set_json_files_paths(std::vector<std::string> json_paths)
{
    this->input_files_paths = json_paths;
}

std::vector<std::string> Regroup::get_json_files_paths()
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
