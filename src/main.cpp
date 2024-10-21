#include <iostream>
#include <fstream>

#include "regroup/regroup.hpp"

int main()
{
    Regroup to_group = Regroup();

    to_group.set_json_files_paths(
        {"../json_samples/1_sample_in.json",
         "../json_samples/2_sample_in.json"});

    to_group.set_criterias({"shape", "material"});
    to_group.regroup_by_criteria();

    std::vector<std::filesystem::path> files = to_group.get_json_files_paths();
    for (auto &&file : files)
    {
        std::cout << file << "\n";
    }
    std::cout << std::endl;
}
