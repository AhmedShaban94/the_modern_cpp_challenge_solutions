#include <iostream>
#include <optional>
#include <vector>
#include "pugixml.hpp"

struct CastingRole {
    std::string actorName_{};
    std::string characterName_{};
};

struct Movie {
    size_t id_{};
    std::string title_{};
    size_t year_{};
    size_t length_{};

    std::vector<std::string> directors_{};
    std::vector<std::string> writers_{};
    std::vector<CastingRole> cast_{};
};

std::ostream& operator<<(std::ostream& os, const Movie& m) {
    os << "title: " << m.title_ << '\n'
       << "id: " << m.id_ << '\n'
       << "year: " << m.year_ << '\n'
       << "length: " << m.length_ << '\n';

    os << "writers: " << '\n';
    for (const auto& writer : m.writers_)
        os << writer << '\n';

    os << "directors: \n";
    for (const auto& director : m.directors_)
        std::cout << director << '\n';

    os << "Cast: \n";
    for (const auto& role : m.cast_)
        os << "star: " << role.actorName_ << '\t'
           << "name: " << role.characterName_ << '\n';

    return os;
}

void serializeMovies(const std::vector<Movie>& movies,
                     const std::string& xmlFileName) {
    pugi::xml_document doc{};
    auto root_node = doc.append_child("movies");

    for (const auto& movie : movies) {
        auto movie_node = root_node.append_child("movie");
        movie_node.append_attribute("id").set_value(movie.id_);
        movie_node.append_attribute("title").set_value(movie.title_.c_str());
        movie_node.append_attribute("year").set_value(movie.year_);
        movie_node.append_attribute("length").set_value(movie.length_);

        auto cast_node = movie_node.append_child("cast");
        for (const auto& role : movie.cast_) {
            auto role_node = cast_node.append_child("role");
            role_node.append_attribute("star").set_value(
                role.actorName_.c_str());
            role_node.append_attribute("name").set_value(
                role.characterName_.c_str());
        }

        auto directors_node = movie_node.append_child("directors");
        for (const auto& director : movie.directors_)
            directors_node.append_child("director")
                .append_attribute("name")
                .set_value(director.c_str());

        auto writers_node = movie_node.append_child("writers");
        for (const auto& writer : movie.writers_)
            writers_node.append_child("writer")
                .append_attribute("name")
                .set_value(writer.c_str());
    }

    doc.save_file(xmlFileName.c_str());
}

std::optional<std::vector<Movie>> deserializeMovies(std::string sourceFile) {
    pugi::xml_document doc{};
    const auto result = doc.load_file(sourceFile.c_str());
    if (result) {
        const auto root = doc.child("movies");
        std::vector<Movie> movies{};
        for (const auto& movieNode : root) {
            Movie m{};
            m.id_ = movieNode.attribute("id").as_uint();
            m.title_ = movieNode.attribute("title").as_string();
            m.year_ = movieNode.attribute("year").as_uint();
            m.length_ = movieNode.attribute("length").as_uint();

            const auto directorsNode = movieNode.child("directors");
            std::vector<std::string> directors{};
            for (const auto& director : directorsNode)
                directors.push_back(director.attribute("name").as_string());
            m.directors_ = directors;

            const auto writersNode = movieNode.child("writers");
            std::vector<std::string> writers{};
            for (const auto& writer : writersNode)
                writers.push_back(writer.attribute("name").as_string());
            m.writers_ = writers;

            const auto castNode = movieNode.child("cast");
            std::vector<CastingRole> cast;
            for (const auto& role : castNode) {
                CastingRole r{};
                r.actorName_ = role.attribute("star").as_string();
                r.characterName_ = role.attribute("name").as_string();
                cast.push_back(r);
            }
            m.cast_ = cast;

            movies.push_back(m);
        }
        return movies;
    } else {
        std::cout << "XML [" << sourceFile
                  << "] parsed with errors, attr value: ["
                  << doc.child("node").attribute("attr").value() << "]\n";
        std::cout << "Error description: " << result.description() << "\n";
        std::cout << "Error offset: " << result.offset << " (error at [..."
                  << (sourceFile.c_str() + result.offset) << "]\n\n";
        return std::nullopt;
    }
}

int main() {
    const auto movies = deserializeMovies("data/movies.xml");
    for (const auto& movie : movies.value())
        std::cout << movie << '\n';
    return EXIT_SUCCESS;
}