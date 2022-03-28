
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>
#include "PDFWriter/PDFWriter.h"
#include "PDFWriter/PageContentContext.h"

using namespace PDFHummus;

int main()
{
    PDFWriter pdfWriter;
    pdfWriter.StartPDF("test.pdf", ePDFVersion13);
    PDFPage* page = new PDFPage();
    page->SetMediaBox(PDFRectangle(0, 0, 595, 842));
    pdfWriter.WritePage(page);
    delete page;
    pdfWriter.EndPDF();
    return EXIT_SUCCESS;
}