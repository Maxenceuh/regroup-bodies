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
    
    // Dictionnaire pour stocker les groupes regroupés (clé générée à partir des critères)
    std::map<std::string, std::vector<json>> grouped_bodies;

    // Parcours des fichiers JSON déjà parsés
    for (const auto &input_json : this->files)
    {
        // Fonction récursive pour parcourir les groupes imbriqués et trouver les corps
        std::function<void(const json &)> process_children = [&](const json &node)
        {
            if (node.contains("children"))
            {
                for (const auto &child : node["children"])
                {
                    process_children(child); // Récursion pour descendre dans les groupes imbriqués
                }
            }
            else if (node["type"] == "body")
            {
                // Générer une clé unique basée sur les critères shape et material
                std::string key;
                for (const auto &criteria : this->criterias)
                {
                    if (!key.empty())
                        key += " "; // Séparateur entre les critères dans la clé

                    if (node.contains(criteria))
                    {
                        key += node[criteria].get<std::string>(); // Ajouter la valeur du critère
                    }
                    else
                    {
                        key += "undefined"; // Si le critère n'est pas présent
                    }
                }

                // Ajouter le corps au groupe correspondant basé sur la clé
                grouped_bodies[key].push_back(node);
            }
        };

        // Traiter le fichier JSON, en commençant par la racine
        process_children(input_json);
    }

    // Créer une nouvelle structure JSON regroupée
    json result;
    result["name"] = "root";
    result["type"] = "group";

    // Ajouter chaque groupe basé sur les critères dans la structure JSON
    for (const auto &group : grouped_bodies)
    {
        json group_node;
        group_node["name"] = "group " + group.first;
        group_node["type"] = "group";
        group_node["children"] = group.second; // Ajouter tous les objets enfants au groupe

        result["children"].push_back(group_node);
    }

    // Écrire le résultat dans un fichier out.json
    std::ofstream out_file("out.json");
    if (!out_file.is_open())
    {
        return "Erreur : Impossible d'ouvrir le fichier de sortie.";
    }
    out_file << result.dump(4); // Belle indentation avec 4 espaces
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

std::vector<nlohmann::json> Regroup::get_json_files()
{
    return this->files;
}

Regroup::~Regroup()
{
}
