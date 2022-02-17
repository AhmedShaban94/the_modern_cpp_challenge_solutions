#include "pugixml.hpp"
#include <exception>
#include <iostream>
#include <vector>

struct query
{
    std::string attribute{};
    std::string searchString{};
    mutable std::vector<std::string> queryResults{};
};

void selectMovies(
    const std::vector<std::reference_wrapper<const query>>& queries,
    const std::string& filePath)
{
    pugi::xml_document doc{};
    const auto result = doc.load_file(filePath.c_str());
    
    if (result)
    {
        for (const auto& query : queries)
        {
            try
            {
                const auto results
                    = doc.select_nodes(query.get().searchString.c_str());
                for (const auto& res : results)
                {
                    const auto str
                        = res.node()
                              .attribute(query.get().attribute.c_str())
                              .as_string();
                    query.get().queryResults.push_back(str);
                }
            }
            catch (const pugi::xpath_exception& xpath_ex)
            {
                std::cerr << "Error: " << xpath_ex.what() << '\n';
            }
        }
    }
    else
    {
        std::cout << "XML [" << filePath
                  << "] parsed with errors, attr value: ["
                  << doc.child("node").attribute("attr").value() << "]\n";
        std::cout << "Error description: " << result.description() << "\n";
        std::cout << "Error offset: " << result.offset << " (error at [..."
                  << (filePath.c_str() + result.offset) << "]\n\n";
    }
}

int main()
{
    const query movieTitles{ "title", "/movies/movie[@year>1995]" };
    const query movieRoles{ "star", "/movies/movie/cast/role[last()]" };
    const std::string fileName{ "data/movies.xml" };

    selectMovies({ std::cref(movieRoles), std::cref(movieTitles) }, fileName);

    std::cout << movieTitles.attribute << ": \n";
    for (const auto& title : movieTitles.queryResults)
        std::cout << '\t' << title << '\n';

    std::cout << movieRoles.attribute << ": \n";
    for (const auto& role : movieRoles.queryResults)
        std::cout << '\t' << role << '\n';

    return EXIT_SUCCESS;
}