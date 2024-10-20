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
            json input_json = json::parse(input_file);
            this->files.push_back(input_json);
        }
        catch(const std::exception& e)
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

void Regroup::regroup_by_criteria()
{
    std::string ret = this->parse_json_files();
    if (ret == "parse complete")
    {
        std::cout << "all good" << "\n";
    }else
    {
        std::cout << "not good" << "\n";
    }
    
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

std::vector<nlohmann::json> Regroup::get_json_files()
{    
    return this->files;
}

Regroup::~Regroup()
{
}
