#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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

    std::vector<std::string> directors_{};
    std::vector<std::string> writers_{};
    std::vector<CastingRole> cast_{};
};

void to_json(nlohmann::json &j, const CastingRole &role)
{
    j = nlohmann::json{{"star", role.actorName_}, {"name", role.characterName_}};
}

void to_json(nlohmann::json &j, const Movie &movie)
{
    j = nlohmann::json{{"id", movie.id_},
        {"title", movie.title_},
        {"year", movie.year_},
        {"length", movie.length_},
        {"cast", movie.cast_},
        {"directors", movie.directors_},
        {"writers", movie.writers_}};
}

void serializeJSON(const std::vector<Movie> &movies, const std::string& filename)
{
    if (movies.empty())
        return;

    nlohmann::json j{"movies", movies};
    std::ofstream file{filename};
    if (file)
        file << std::setw(4) << j;
}

int main()
{
    Movie forrest_gump{};
    forrest_gump.id_ = 9871;
    forrest_gump.title_ = "Forrest Gump";
    forrest_gump.year_ = 1994;
    forrest_gump.length_ = 202;
    forrest_gump.cast_ = {{"Tom Hanks",
                           "Forrest Gump"},
                          {"Sally Field",
                           "Mrs. Gump"},
                          {"Robin Wright",
                           "Jenny Curran"},
                          {"Mykelti Williamson",
                           "Bubba Blue"}};
    forrest_gump.directors_ = {"Robert Zemeckis"};
    forrest_gump.writers_ = {"Winston Groom", "Eric Roth"};

    std::vector<Movie> movies{forrest_gump};
    serializeJSON(movies, "movies.json");
    return EXIT_SUCCESS;
}