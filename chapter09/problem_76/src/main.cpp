#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
struct CastingRole
{
    std::string actorName_{};
    std::string characterName_{};
};

struct Movie
{
    std::size_t id_{};
    std::string title_{};
    std::size_t year_{};
    std::size_t length_{};

    std::vector<CastingRole> cast_{};
    std::vector<std::string> directors_{};
    std::vector<std::string> writers_{};
};

using json = nlohmann::json;

void from_json(const json& j, CastingRole& cast)
{
    j.at("star").get_to(cast.actorName_);
    j.at("name").get_to(cast.characterName_);
}

void from_json(const json& j, Movie& movie)
{
    j.at("id").get_to(movie.id_);
    j.at("title").get_to(movie.title_);
    j.at("year").get_to(movie.year_);
    j.at("length").get_to(movie.length_);
    j.at("directors").get_to(movie.directors_);
    j.at("writers").get_to(movie.writers_);
    j.at("cast").get_to(movie.cast_);
}

[[nodiscard]] json deserializeJSON(const std::string& filepath)
{
    std::ifstream file{ filepath };
    if (file)
    {
        json j{};
        file >> j;
        return j;
    }
    else
    {
        throw std::system_error(errno, std::system_category(),
                                "failed to find " + filepath);
    }
}

int main()
{
    try
    {
        json j = deserializeJSON("data/movies.json");
        std::cout << std::setw(2) << j;
    }
    catch (const std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << '\n';
    }
    return EXIT_SUCCESS;
}