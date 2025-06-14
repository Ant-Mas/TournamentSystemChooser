#include <hpdf.h>
#include <vector>
#include <string>
#include <iostream>

void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data) {
    std::cerr << "libharu error: error_no=" << std::hex << error_no << ", detail_no=" << std::hex << detail_no << "\n";
    throw std::runtime_error("libharu error");
}

void createPDFWithCenteredText(const std::vector<std::pair<std::string, std::string> > &bracket,
                               const std::string &filename = "output.pdf") {
    HPDF_Doc pdf;
    HPDF_Page page;
    HPDF_Font font;
    HPDF_STATUS status;

    const float page_width = 595.0f; // A4 width in points
    const float page_height = 842.0f; // A4 height in points
    const float font_size = 16.0f;
    const float line_spacing = 24.0f;
    const float top_margin = 50.0f;
    const float sep_padding = 10.0f;
    const std::string separator = "--";


    // Create PDF document
    pdf = HPDF_New(nullptr, nullptr);
    if (!pdf) {
        std::cerr << "Error: Cannot create PDF object\n";
        return;
    }

    try {
        // Add a new page and set size
        page = HPDF_AddPage(pdf);
        HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

        // Set font
        font = HPDF_GetFont(pdf, "Helvetica", nullptr);
        HPDF_Page_SetFontAndSize(page, font, font_size);

        float y = page_height - top_margin;

        for (const auto pair: bracket) {
            if (y < top_margin) {
                // Add new page if we're out of space
                page = HPDF_AddPage(pdf);
                HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
                HPDF_Page_SetFontAndSize(page, font, font_size);
                y = page_height - top_margin;
            }


            float sep_width = HPDF_Page_TextWidth(page, separator.c_str()) / 2;
            float x = (page_width) / 2.0f;
            float text_width = HPDF_Page_TextWidth(page, pair.first.c_str());

            HPDF_Page_BeginText(page);
            HPDF_Page_TextOut(page, x - sep_width - sep_padding - text_width, y, pair.first.c_str());
            HPDF_Page_TextOut(page, x - sep_width, y, separator.c_str());
            HPDF_Page_TextOut(page, x + sep_width + sep_padding, y, pair.second.c_str());
            HPDF_Page_EndText(page);

            y -= line_spacing;
        }

        // Save to file
        status = HPDF_SaveToFile(pdf, filename.c_str());
        if (status != HPDF_OK) {
            std::cerr << "Error saving PDF to file\n";
        }

        HPDF_Free(pdf);
    } catch (...) {
        HPDF_Free(pdf);
        std::cerr << "Exception occurred during PDF creation\n";
    }
}

void createPDFWithLeftText(const std::vector<std::string> &lines, const std::string &filename = "output.pdf") {
    HPDF_Doc pdf;
    HPDF_Page page;
    HPDF_Font font;
    HPDF_STATUS status;

    const float page_width = 595.0f; // A4 width in points
    const float page_height = 842.0f; // A4 height in points
    const float font_size = 16.0f;
    const float line_spacing = 24.0f;
    const float top_margin = 50.0f;
    const float left_margin = 40.0f;

    // Create PDF document
    pdf = HPDF_New(nullptr, nullptr);
    if (!pdf) {
        std::cerr << "Error: Cannot create PDF object\n";
        return;
    }

    try {
        // Add a new page and set size
        page = HPDF_AddPage(pdf);
        HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

        // Set font
        font = HPDF_GetFont(pdf, "Helvetica", nullptr);
        HPDF_Page_SetFontAndSize(page, font, font_size);

        float y = page_height - top_margin;

        for (const std::string &line: lines) {
            if (y < top_margin) {
                // Add new page if we're out of space
                page = HPDF_AddPage(pdf);
                HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
                HPDF_Page_SetFontAndSize(page, font, font_size);
                y = page_height - top_margin;
            }

            HPDF_Page_BeginText(page);
            HPDF_Page_TextOut(page, left_margin, y, line.c_str());
            HPDF_Page_EndText(page);

            y -= line_spacing;
        }

        // Save to file
        status = HPDF_SaveToFile(pdf, filename.c_str());
        if (status != HPDF_OK) {
            std::cerr << "Error saving PDF to file\n";
        }

        HPDF_Free(pdf);
    } catch (...) {
        HPDF_Free(pdf);
        std::cerr << "Exception occurred during PDF creation\n";
    }
}


void createPDFTableFromVectors(
    const std::vector<Player *> &players,
    const std::string &filename = "table_output.pdf"
) {
    HPDF_Doc pdf = HPDF_New(error_handler, nullptr);
    if (!pdf) {
        throw std::runtime_error("Failed to create PDF document.");
    }

    const HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", nullptr);

    const float font_size = 12.0f;
    const float row_height = 20.0f;
    const float top_margin = 40.0f;
    const float left_margin = 40.0f;
    const std::vector<std::string> headers = {"Player name", "Wins", "Losses"};
    const std::vector<float> columnWidths = {200.0F, 60.0F, 60.0F};

    try {
        HPDF_Page page = HPDF_AddPage(pdf);
        HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
        HPDF_Page_SetFontAndSize(page, font, font_size);

        const float page_width = HPDF_Page_GetWidth(page);
        const float page_height = HPDF_Page_GetHeight(page);

        float y = page_height - top_margin;

        auto drawRow = [&](const std::vector<std::string> &row, float &y_position) {
            float x = left_margin;

            HPDF_Page_BeginText(page);
            for (int i = 0; i < 3; ++i) {
                // Cell border
                HPDF_Page_EndText(page); // End before drawing
                HPDF_Page_Rectangle(page, x, y_position - row_height, columnWidths[i], row_height);
                HPDF_Page_Stroke(page);
                HPDF_Page_BeginText(page);

                HPDF_Page_TextOut(page, x + 2, y_position - row_height + 5, row[i].c_str());
                x += columnWidths[i];
            }
            HPDF_Page_EndText(page);
            y_position -= row_height;
        };

        // Draw headers
        drawRow(headers, y);

        // Draw data rows
        for (size_t i = 0; i < players.size(); ++i) {
            if (y < row_height + 40.0f) {
                // Start new page
                page = HPDF_AddPage(pdf);
                HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
                HPDF_Page_SetFontAndSize(page, font, font_size);
                y = page_height - top_margin;
                drawRow(headers, y);
            }

            std::vector row = {
                players[i]->get_name(), std::to_string(players[i]->get_wins()), std::to_string(players[i]->get_losses())
            };
            drawRow(row, y);
        }

        HPDF_SaveToFile(pdf, filename.c_str());
        HPDF_Free(pdf);
    } catch (...) {
        HPDF_Free(pdf);
        throw;
    }
}
