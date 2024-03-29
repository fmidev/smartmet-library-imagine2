// ======================================================================
/*!
 * \file
 * \brief Regression tests for namespace NFmiTightBezierFit
 */
// ======================================================================

#include "NFmiPath.h"
#include "NFmiTightBezierFit.h"
#include "tframe.h"
#include <cmath>

using namespace std;

//! Protection against conflicts with global functions
namespace NFmiTightBezierFitTest
{
#define EXPECT(a, b) \
  if (a.SVG() != b)  \
    TEST_FAILED("Expected '" + string(b) + "', got '" + a.SVG() + "'");

// ----------------------------------------------------------------------
/*!
 * \brief Test NFmiTightBezierFit::Fit
 */
// ----------------------------------------------------------------------

void Fit()
{
  using namespace Imagine;

  {
    NFmiPath p, s;
    p.MoveTo(230.878189, 135.041138);
    p.LineTo(227.785355, 137.013580);
    p.LineTo(226.464218, 140.816055);
    p.LineTo(226.098022, 141.471664);
    p.LineTo(225.875824, 141.540802);
    p.LineTo(225.806458, 141.569244);
    p.LineTo(225.650833, 141.626785);
    p.LineTo(220.831345, 142.943329);
    p.LineTo(219.354843, 143.687881);
    p.LineTo(216.888992, 145.444397);
    p.LineTo(215.845871, 147.902191);
    p.LineTo(214.917480, 149.909866);
    p.LineTo(214.353790, 152.886902);
    p.LineTo(213.895218, 154.332718);
    p.LineTo(213.738541, 155.165314);
    p.LineTo(212.949051, 160.717590);
    p.LineTo(212.941086, 160.763260);
    p.LineTo(212.937546, 160.797470);
    p.LineTo(212.903229, 161.092224);
    p.LineTo(212.032822, 161.630829);
    p.LineTo(208.817719, 163.121628);
    p.LineTo(206.451614, 166.623535);
    p.LineTo(205.617096, 161.595047);
    p.LineTo(205.584091, 160.763260);
    p.LineTo(205.606445, 159.920853);
    p.LineTo(205.410156, 155.370773);
    p.LineTo(205.434219, 154.332718);
    p.LineTo(205.432297, 153.316742);
    p.LineTo(205.752792, 148.598740);
    p.LineTo(205.751282, 147.902191);
    p.LineTo(205.484451, 146.938187);
    p.LineTo(204.591675, 143.325516);
    p.LineTo(204.034851, 141.471664);
    p.LineTo(204.586670, 139.612823);
    p.LineTo(206.451614, 136.416595);
    p.LineTo(207.009415, 135.597122);
    p.LineTo(207.301056, 135.041138);
    p.LineTo(208.888962, 132.611755);
    p.LineTo(209.474136, 131.623245);
    p.LineTo(212.286087, 128.610596);
    p.LineTo(212.604126, 128.312469);
    p.LineTo(212.903229, 127.959412);
    p.LineTo(214.719482, 126.800285);
    p.LineTo(216.497543, 125.762650);
    p.LineTo(219.354843, 123.283577);
    p.LineTo(221.595032, 124.412941);
    p.LineTo(222.881836, 125.095154);
    p.LineTo(225.806458, 126.421570);
    p.LineTo(226.857635, 127.562851);
    p.LineTo(229.247894, 128.610596);
    p.LineTo(229.897461, 130.963486);
    p.LineTo(230.405579, 133.194702);

    s = NFmiTightBezierFit::Fit(p, 5);
    EXPECT(s,
           "M230.878,135.041 C220.229,141.832 216.719,162.98 206.452,166.624 204.85,167.192 "
           "205.844,163.279 205.617,161.595 203.095,142.849 223.33,102.126 230.406,133.195");
  }

  {
    NFmiPath p, s;

    p.MoveTo(0, 0);
    p.LineTo(0, 3);
    p.LineTo(3, 3);
    s = NFmiTightBezierFit::Fit(p, 1.5);
    EXPECT(s, "M0,0 C0,3.143 -0.143,3 3,3");

    p.LineTo(3, 0);
    s = NFmiTightBezierFit::Fit(p, 1.5);
    EXPECT(s, "M0,0 C0,4.17 3,4.17 3,0");

    p.LineTo(0, 0);
    s = NFmiTightBezierFit::Fit(p, 1.5);
    EXPECT(s, "M0,0 C-1.647,1.647 1.353,4.647 3,3 4.647,1.353 1.647,-1.647 0,0");
  }

  {
    NFmiPath p, s;
    p.MoveTo(85.381981, 327.957031);
    p.LineTo(84.955460, 326.876068);
    p.LineTo(83.870964, 325.901672);
    p.LineTo(81.028053, 325.123413);
    p.LineTo(80.431259, 324.954956);
    p.LineTo(77.419357, 324.149628);
    p.LineTo(74.917046, 325.462891);
    p.LineTo(71.074730, 327.957031);
    p.LineTo(71.086594, 328.075500);
    p.LineTo(70.967743, 328.559448);
    p.LineTo(70.379112, 333.800873);
    p.LineTo(70.150650, 334.387573);
    p.LineTo(70.190468, 335.162323);
    p.LineTo(70.967743, 335.926910);
    p.LineTo(74.003410, 337.792358);
    p.LineTo(74.830643, 338.237854);
    p.LineTo(77.419357, 339.685333);
    p.LineTo(78.697594, 339.544037);
    p.LineTo(83.114151, 340.063751);
    p.LineTo(83.870964, 339.922058);
    p.LineTo(84.904381, 335.417603);
    p.LineTo(84.909729, 334.387573);
    p.LineTo(85.007240, 333.255005);
    p.LineTo(85.257103, 329.338654);
    p.LineTo(85.381981, 327.957031);
    s = NFmiTightBezierFit::Fit(p, 5);
    EXPECT(s,
           "M85.382,327.957 C84.455,320.386 65.295,325.94 70.19,335.162 76.155,346.399 "
           "86.64,338.231 85.382,327.957");
  }

  {
    NFmiPath p, s;
    p.MoveTo(86.442192, 192.915909);
    p.LineTo(84.604469, 193.647018);
    p.LineTo(83.870964, 193.921692);
    p.LineTo(82.977676, 193.806274);
    p.LineTo(80.969513, 192.915909);
    p.LineTo(82.224884, 191.275208);
    p.LineTo(83.870964, 189.746033);
    p.LineTo(85.917007, 190.876556);
    p.LineTo(86.442192, 192.915909);
    s = NFmiTightBezierFit::Fit(p, 5);
    EXPECT(s, "M86.442,192.916 C83.251,199.652 89.095,187.316 86.442,192.916");
  }

  // A self touching curve:
  {
    NFmiPath p, s;
    p.MoveTo(-100, 0);
    p.LineTo(-50, -50);
    p.LineTo(0, 0);
    p.LineTo(50, -50);
    p.LineTo(100, 0);
    p.LineTo(50, 50);
    p.LineTo(0, 0);
    p.LineTo(-50, 50);
    p.LineTo(-100, 0);

    s = NFmiTightBezierFit::Fit(p, 1);
    EXPECT(
        s,
        "M-100,0 C-100.651,0.651 -98.698,-1.302 -98.047,-1.953 -96.875,-3.125 -95.703,-4.297 "
        "-94.531,-5.469 -91.016,-8.984 -87.5,-12.5 -83.984,-16.016 -75.521,-24.479 -67.057,-32.943 "
        "-58.594,-41.406 -57.754,-42.246 -50.187,-50 -50,-50 -49.787,-50 -41.189,-41.189 "
        "-40.234,-40.234 -30.339,-30.339 -20.443,-20.443 -10.547,-10.547 -9.516,-9.516 -0.23,0 0,0 "
        "0.213,0 8.811,-8.811 9.766,-9.766 19.661,-19.661 29.557,-29.557 39.453,-39.453 "
        "40.484,-40.484 49.77,-50 50,-50 51.585,-50 56.567,-43.433 57.812,-42.188 65.365,-34.635 "
        "72.917,-27.083 80.469,-19.531 85.286,-14.714 90.104,-9.896 94.922,-5.078 95.731,-4.269 "
        "100,-1.03 100,0 100,1.03 95.731,4.269 94.922,5.078 90.104,9.896 85.286,14.714 "
        "80.469,19.531 72.917,27.083 65.365,34.635 57.812,42.188 56.567,43.433 51.585,50 50,50 "
        "49.787,50 41.189,41.189 40.234,40.234 30.339,30.339 20.443,20.443 10.547,10.547 "
        "9.516,9.516 0.23,0 0,0 -0.213,0 -8.811,8.811 -9.766,9.766 -19.661,19.661 -29.557,29.557 "
        "-39.453,39.453 -40.484,40.484 -49.77,50 -50,50 -50.213,50 -58.811,41.189 -59.766,40.234 "
        "-69.401,30.599 -79.036,20.964 -88.672,11.328 -91.146,8.854 -93.62,6.38 -96.094,3.906 "
        "-97.396,2.604 -98.698,-1.302 -100,0");
  }

  // A difficult case for NFmiApproximateBezierFit:
  {
    NFmiPath p, s;
    p.MoveTo(60.2, 95.8);
    p.LineTo(3.9, 63.7);
    p.LineTo(12.2, 59.5);  // 1
    p.LineTo(15.9, 56.9);  // ->
    p.LineTo(27.8, 50.2);  // 2
    p.LineTo(39.8, 43.5);
    p.LineTo(49.3, 53.4);
    p.LineTo(60.2, 95.8);
    s = NFmiTightBezierFit::Fit(p, 1.0);
    EXPECT(s,
           "M60.2,95.8 C60.168,95.849 54.961,92.813 54.482,92.54 48.031,88.862 41.58,85.184 "
           "35.129,81.505 27.212,76.991 19.295,72.477 11.377,67.963 10.642,67.544 3.827,64.178 "
           "3.9,63.7 3.928,63.521 16.634,56.487 20.363,54.387 22.767,53.034 38.453,43.3 39.8,43.5 "
           "41.309,43.725 44.617,48.519 45.737,49.688 53.179,57.443 54.292,72.82 56.964,83.212 "
           "57.263,84.374 60.209,95.786 60.2,95.8");
  }

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
  void test(void) { TEST(Fit); }
};

}  // namespace NFmiTightBezierFitTest

//! The main program
int main(void)
{
  using namespace std;
  cout << endl << "NFmiTightBezierFit tester" << endl << "=========================" << endl;
  NFmiTightBezierFitTest::tests t;
  return t.run();
}

// ======================================================================
