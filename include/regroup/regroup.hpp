#if !defined(REGROUP_HPP)
#define REGROUP_HPP

#include <vector>
#include <string>

class Regroup
{
private:
    std::string default_json_samples_location;
    std::vector<std::string> input_files;
public:
    Regroup(std::vector<std::string> input_files);
    Regroup();
    ~Regroup();
};

#endif // REGROUP_HPP
