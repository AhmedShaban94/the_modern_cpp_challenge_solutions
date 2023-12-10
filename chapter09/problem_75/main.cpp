#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"

struct CastingRole {
    std::string actorName_{};
    std::string characterName_{};
};

struct Movie {
    size_t id_{};
    std::string title_{};
    size_t year_{};
    size_t length_{};

    std::vector<CastingRole> cast_{};
    std::vector<std::string> directors_{};
    std::vector<std::string> writers_{};
};

void to_json(nlohmann::json& j, const CastingRole& role) {
    j = nlohmann::json{{"star", role.actorName_},
                       {"name", role.characterName_}};
}

void to_json(nlohmann::json& j, const Movie& movie) {
    j = nlohmann::json{
        {"id", movie.id_},          {"title", movie.title_},
        {"year", movie.year_},      {"length", movie.length_},
        {"cast", movie.cast_},      {"directors", movie.directors_},
        {"writers", movie.writers_}};
}

void serializeJSON(const std::vector<Movie>& movies,
                   const std::string& filename) {
    if (movies.empty())
        return;

    nlohmann::json j{};
    j["movies"] = movies;
    std::ofstream file{filename};
    if (file)
        file << std::setw(2) << j;
    else
        throw std::system_error(errno, std::system_category(),
                                "failed to create " + filename);
}

int main() {
    std::vector<Movie> movies{{
                                  11001,
                                  "The Matrix",
                                  1999,
                                  196,
                                  {{"Keanu Reeves", "Neo"},
                                   {"Laurence Fishburne", "Morpheus"},
                                   {"Carrie-Anne Moss", "Trinity"},
                                   {"Hugo Weaving", "Agent Smith"}},
                                  {"Lana Wachowski", "Lilly Wachowski"},
                                  {"Lana Wachowski", "Lilly Wachowski"},
                              },
                              {
                                  9871,
                                  "Forrest Gump",
                                  1994,
                                  202,
                                  {{"Tom Hanks", "Forrest Gump"},
                                   {"Sally Field", "Mrs. Gump"},
                                   {"Robin Wright", "Jenny Curran"},
                                   {"Mykelti Williamson", "Bubba Blue"}},
                                  {"Robert Zemeckis"},
                                  {"Winston Groom", "Eric Roth"},
                              }};

    try {
        serializeJSON(movies, "movies.json");
    } catch (const std::exception& ex) {
        std::cerr << "ERROR: " << ex.what() << '\n';
    }
    return EXIT_SUCCESS;
}