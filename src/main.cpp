#include <iostream>
#include <json.hpp>
#include "regroup/regroup.hpp"

using json = nlohmann::json;

int main()
{
    std::cout << json::meta() << std::endl;
}
