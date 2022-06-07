
#include "PDFWriter/PDFPage.h"
#include "PDFWriter/PDFWriter.h"
#include "PDFWriter/PageContentContext.h"
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

#if defined(_WIN32)
static const std::string fontsDir{ R"(c:/windows/fonts/)" };
#elif defined(__APPLE__)
static const std::string fontsDir{ R"(/Library/Fonts/)" };
#else
static const std::string fontsDir{ R"(/usr/share/fonts/)" };
#endif

using namespace PDFHummus;

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

void printPDF(const std::vector<Movie>& movies, const std::string& path)
{
    constexpr std::size_t height      = 842;
    constexpr std::size_t width       = 595;
    constexpr std::size_t left        = 60;
    constexpr std::size_t top         = 770;
    constexpr std::size_t right       = 535;
    constexpr std::size_t bottom      = 60;
    constexpr std::size_t line_height = 28;

    PDFWriter pdf{};
    pdf.StartPDF(path, ePDFVersion13);
    PDFUsedFont* font = pdf.GetFontForFile(fontsDir + "arial.ttf");

    AbstractContentContext::GraphicOptions pathStrokeOptions(
        AbstractContentContext::eStroke, AbstractContentContext::eRGB,
        0xff000000, 1);

    std::unique_ptr<PDFPage> page{ nullptr };
    std::unique_ptr<PageContentContext> context{ nullptr };
    std::size_t index{ 0 };
    for (std::size_t i{ 0 }; i < movies.size(); ++i)
    {
        index = i % 25;
        if (index == 0)
        {
            if (page != nullptr)
            {
                DoubleAndDoublePairList pathPoints;
                pathPoints.push_back(DoubleAndDoublePair(left, bottom));
                pathPoints.push_back(DoubleAndDoublePair(right, bottom));
                context->DrawPath(pathPoints, pathStrokeOptions);
                pdf.EndPageContentContext(context.get());
                pdf.WritePageAndRelease(page.get());
            }
            page = std::make_unique<PDFPage>();
            page->SetMediaBox(PDFRectangle(0, 0, width, height));
            context = std::make_unique<PageContentContext>(
                pdf.StartPageContentContext(page.get()));
            {
                DoubleAndDoublePairList pathPoints;
                pathPoints.push_back(DoubleAndDoublePair(left, top));
                pathPoints.push_back(DoubleAndDoublePair(right, top));
                context->DrawPath(pathPoints, pathStrokeOptions);
            }
        }

        if (i == 0)
        {
            AbstractContentContext::TextOptions const textOptions(
                font, 26, AbstractContentContext::eGray, 0);
            context->WriteText(left, top + 15, "List of movies", textOptions);
        }

        auto textw = 0;
        {
            AbstractContentContext::TextOptions const textOptions(
                font, 20, AbstractContentContext::eGray, 0);
            context->WriteText(left, top - 20 - line_height * index,
                               movies[i].title_, textOptions);
            auto textDimensions
                = font->CalculateTextDimensions(movies[i].title_, 20);
            textw = textDimensions.width;
        }
        {
            AbstractContentContext::TextOptions const textOptions(
                font, 16, AbstractContentContext::eGray, 0);
            context->WriteText(left + textw + 5, top - 20 - line_height * index,
                               " (" + std::to_string(movies[i].year_) + ")",
                               textOptions);
            std::stringstream s;
            s << movies[i].length_ / 60 << ':' << std::setw(2)
              << std::setfill('0') << movies[i].length_ % 60;
            context->WriteText(right - 30, top - 20 - line_height * index,
                               s.str(), textOptions);
        }
    }
}

int main()
{
    PDFWriter pdfWriter;
    pdfWriter.StartPDF("test.pdf", ePDFVersion13);
    PDFPage* page = new PDFPage;
    page->SetMediaBox(PDFRectangle(0, 0, 595, 842));
    pdfWriter.WritePage(page);
    delete page;
    pdfWriter.EndPDF();
    return EXIT_SUCCESS;
}