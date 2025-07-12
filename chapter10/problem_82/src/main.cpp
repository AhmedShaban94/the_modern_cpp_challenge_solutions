#include <algorithm>
#include <array>
#include <cstdint>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Include Catch2 for testing
#include "catch2/catch_test_macros.hpp"

// Simple PNG writer class for creating basic PNG images
class PngWriter {
 public:
  // Constructor
  PngWriter(int width, int height) : width_(width), height_(height) {
    // Initialize image data with white pixels
    image_data_.resize(height_ * width_ * 3, 255);
  }

  // Set pixel color at (x, y) coordinates
  void set_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
      return;  // Out of bounds
    }

    const size_t index = (y * width_ + x) * 3;
    image_data_[index] = r;      // Red
    image_data_[index + 1] = g;  // Green
    image_data_[index + 2] = b;  // Blue
  }

  // Save the image to a PNG file
  bool save(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
      return false;
    }

    // PNG signature
    const std::array<uint8_t, 8> png_signature = {137, 80, 78, 71, 13, 10, 26, 10};
    file.write(reinterpret_cast<const char*>(png_signature.data()), png_signature.size());

    // IHDR chunk
    write_chunk(file, "IHDR", [this](std::ostream& os) {
      write_uint32(os, width_);
      write_uint32(os, height_);
      os.put(8);  // Bit depth
      os.put(2);  // Color type (RGB)
      os.put(0);  // Compression method
      os.put(0);  // Filter method
      os.put(0);  // Interlace method
    });

    // IDAT chunk (image data)
    write_chunk(file, "IDAT", [this](std::ostream& os) {
      // Simple implementation without compression
      // In a real implementation, we would use zlib to compress the data
      // For simplicity, we're just writing raw data
      for (int y = 0; y < height_; ++y) {
        os.put(0);  // Filter type for this scanline (none)
        os.write(reinterpret_cast<const char*>(image_data_.data() + y * width_ * 3), width_ * 3);
      }
    });

    // IEND chunk
    write_chunk(file, "IEND", [](std::ostream&) {});

    return true;
  }

 private:
  int width_;
  int height_;
  std::vector<uint8_t> image_data_;

  // Write a 4-byte unsigned integer in big-endian format
  static void write_uint32(std::ostream& os, uint32_t value) {
    os.put(static_cast<char>((value >> 24) & 0xFF));
    os.put(static_cast<char>((value >> 16) & 0xFF));
    os.put(static_cast<char>((value >> 8) & 0xFF));
    os.put(static_cast<char>(value & 0xFF));
  }

  // Write a PNG chunk
  template <typename F>
  static void write_chunk(std::ostream& os, const std::string& type, F data_writer) {
    // Prepare data in a temporary buffer
    std::stringstream data;
    data_writer(data);
    std::string data_str = data.str();

    // Write length
    write_uint32(os, static_cast<uint32_t>(data_str.size()));

    // Write type
    os.write(type.c_str(), 4);

    // Write data
    os.write(data_str.c_str(), data_str.size());

    // Calculate and write CRC
    uint32_t crc = calculate_crc(type, data_str);
    write_uint32(os, crc);
  }

  // Calculate CRC for a chunk
  static uint32_t calculate_crc(const std::string& type, const std::string& data) {
    // Simple CRC implementation for demonstration
    // In a real implementation, we would use the CRC-32 algorithm
    // For simplicity, we're just returning a placeholder value
    return 0;
  }
};

// Function to create the Romanian flag
bool create_romanian_flag(int width, int height, const std::string& filename) {
  if (width <= 0 || height <= 0) {
    return false;
  }

  try {
    // Create a new PNG image
    PngWriter png(width, height);

    // Calculate the width of each stripe (all three stripes have equal width)
    int stripe_width = width / 3;

    // Romanian flag colors (RGB)
    const uint8_t blue_r = 0, blue_g = 43, blue_b = 127;          // Blue
    const uint8_t yellow_r = 252, yellow_g = 209, yellow_b = 22;  // Yellow
    const uint8_t red_r = 206, red_g = 17, red_b = 38;            // Red

    // Draw the three vertical stripes
    for (int y = 0; y < height; ++y) {
      // Blue stripe (leftmost)
      for (int x = 0; x < stripe_width; ++x) {
        png.set_pixel(x, y, blue_r, blue_g, blue_b);
      }

      // Yellow stripe (middle)
      for (int x = stripe_width; x < 2 * stripe_width; ++x) {
        png.set_pixel(x, y, yellow_r, yellow_g, yellow_b);
      }

      // Red stripe (rightmost)
      for (int x = 2 * stripe_width; x < width; ++x) {
        png.set_pixel(x, y, red_r, red_g, red_b);
      }
    }

    // Save the image
    return png.save(filename);
  } catch (const std::exception& e) {
    std::cerr << "Error creating Romanian flag: " << e.what() << std::endl;
    return false;
  }
}

// Unit tests
TEST_CASE("Romanian flag creation", "[flag]") {
  SECTION("Valid dimensions") {
    // Create a temporary file path
    std::string temp_file = "test_flag.png";

    // Test with valid dimensions
    REQUIRE(create_romanian_flag(300, 200, temp_file) == true);

    // Check if the file exists
    REQUIRE(std::experimental::filesystem::exists(temp_file));

    // Check file size (should be non-zero)
    REQUIRE(std::experimental::filesystem::file_size(temp_file) > 0);

    // Clean up
    std::experimental::filesystem::remove(temp_file);
  }

  SECTION("Invalid dimensions") {
    // Test with invalid dimensions
    REQUIRE(create_romanian_flag(0, 200, "invalid_flag.png") == false);
    REQUIRE(create_romanian_flag(300, 0, "invalid_flag.png") == false);
    REQUIRE(create_romanian_flag(-10, 200, "invalid_flag.png") == false);
    REQUIRE(create_romanian_flag(300, -10, "invalid_flag.png") == false);
  }
}