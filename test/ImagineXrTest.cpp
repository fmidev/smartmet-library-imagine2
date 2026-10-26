// ======================================================================
/*!
 * \file
 * \brief Regression tests for class ImagineXr
 */
// ======================================================================

#include "imagine-config.h"

#include "ImagineXr.h"
#include "tframe.h"
#include <cstdio>
#include <string>
#include <unistd.h>

using namespace std;

//! Protection against conflicts with global functions
namespace ImagineXrTest
{
// ----------------------------------------------------------------------
/*!
 * \brief Test reading a PNG file as the base image
 */
// ----------------------------------------------------------------------

void from_png()
{
  using namespace Imagine;

  const string fn = "/tmp/imaginexr_test_" + to_string(getpid()) + ".png";

  {
    ImagineXr img(30, 20, fn, "png");
    img.Erase(0x00ff0000);
    img.Write();
  }

  // The width used to be read from the surface before the file was loaded
  ImagineXr png(fn);
  std::remove(fn.c_str());

  if (png.Width() != 30)
    TEST_FAILED("Width of the PNG should be 30, not " + to_string(png.Width()));
  if (png.Height() != 20)
    TEST_FAILED("Height of the PNG should be 20, not " + to_string(png.Height()));

  TEST_PASSED();
}

// ----------------------------------------------------------------------
/*!
 * The actual test suite
 */
// ----------------------------------------------------------------------

class tests : public tframe::tests
{
  virtual const char* error_message_prefix() const { return "\n\t"; }
  void test(void) { TEST(from_png); }
};

}  // namespace ImagineXrTest

//! The main program
int main(void)
{
  using namespace std;
  cout << endl << "ImagineXr tester" << endl << "================" << endl;
  ImagineXrTest::tests t;
  return t.run();
}

// ======================================================================
