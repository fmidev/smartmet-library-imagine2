# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

`smartmet-library-imagine2` is a 2D graphics rendering library for the SmartMet Server ecosystem (Finnish Meteorological Institute). It is the Cairo-based successor to the original `imagine` library and produces `libsmartmet-imagine2.so`. Headers install to `smartmet/imagine2/`.

## Build commands

```bash
make                  # Build libsmartmet-imagine2.so
make test             # Build and run all tests in test/
make format           # Run clang-format on all source and test files
make clean            # Clean build artifacts
make rpm              # Build RPM package
make install          # Install library and headers (PREFIX=/usr)
```

To run a single test:
```bash
cd test && make NFmiBezierToolsTest && ./NFmiBezierToolsTest
```

## Dependencies

**SmartMet libraries:** macgyver, newbase, gis (headers at `/usr/include/smartmet/`)

**System libraries:** cairomm-1.0, freetype2, GDAL, fmt (12.x), Boost (regex, thread), libjpeg, libpng, zlib

The library must be built after macgyver and newbase but before any engines or plugins that use it.

## Architecture

Everything lives in the `Imagine` namespace. Cairo rendering is always active via `IMAGINE_WITH_CAIRO` (defined in `imagine-config.h`, not Makefiles).

### Key subsystems

- **ImagineXr** — Cairo-based rendering surface. Wraps PDF/PS/SVG/Image Cairo surfaces. This is the primary rendering class (`ImagineXr_or_NFmiImage` typedef resolves to `ImagineXr`).
- **NFmiImage** — Legacy pixel-buffer image class (JPEG/PNG/GIF/PNM read/write). Used for raster operations and pixel-level compositing; many methods are `#ifdef`'d out when Cairo is active.
- **NFmiPath / NFmiPathElement** — PostScript-style path representation (MoveTo, LineTo, GhostLineTo, ConicTo, CubicTo). Central data structure for vector drawing — paths are projected, simplified, stroked, and filled onto surfaces.
- **NFmiContourTree / NFmiEdgeTree** — Marching-squares contouring engine. Generates contour polygons from gridded data matrices using linear, nearest-neighbour, or discrete interpolation.
- **NFmiEsri\*** — ESRI Shapefile reader/writer. Full support for Point/PolyLine/Polygon types including M and Z variants, plus dBASE attribute handling.
- **NFmiColorTools / NFmiColorBlend** — Porter-Duff color blending (32-bit RGBA as single `int`), ~20 blend rules.
- **NFmiColorReduce** — Color quantization for palette output.
- **NFmiFreeType / NFmiFace** — FreeType-based font rendering.
- **NFmiBezierTools / NFmiApproximateBezierFit / NFmiCardinalBezierFit / NFmiTightBezierFit** — Bezier curve fitting and manipulation.
- **NFmiGeoShape / NFmiGshhsTools** — Geographic shape handling and GSHHS coastline data support.

### Conditional compilation

Many classes have `#ifdef IMAGINE_WITH_CAIRO` / `#ifndef IMAGINE_WITH_CAIRO` blocks. The non-Cairo code paths (NFmiDrawable, NFmiFillMap, NFmiAffine for paths) are legacy and not compiled in normal builds. Do not remove these — they exist for the Windows workstation build.

## CI

CircleCI builds and tests on RHEL 8 and RHEL 10 using `fmidev/smartmet-cibase-{8,10}` Docker images with `ci-build deps/rpm/testprep/test` commands.
