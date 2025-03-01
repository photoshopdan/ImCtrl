cmake_minimum_required(VERSION 3.26...3.31)
project(
    ImCtrl
    LANGUAGES CXX)

add_subdirectory(extern/SDL)

# Add SDL_image build options.
set(SDLIMAGE_AVIF OFF CACHE BOOL "Disable AVIF support" FORCE)
set(SDLIMAGE_BMP OFF CACHE BOOL "Disable BMP support" FORCE)
set(SDLIMAGE_GIF OFF CACHE BOOL "Disable GIF support" FORCE)
set(SDLIMAGE_JPG ON CACHE BOOL "Enable JPG support" FORCE)
set(SDLIMAGE_JXL OFF CACHE BOOL "Disable JXL support" FORCE)
set(SDLIMAGE_LBM OFF CACHE BOOL "Disable LBM support" FORCE)
set(SDLIMAGE_PCX OFF CACHE BOOL "Disable PCX support" FORCE)
set(SDLIMAGE_PNG ON CACHE BOOL "Enable PNG support" FORCE)
set(SDLIMAGE_PNM OFF CACHE BOOL "Disable PNM support" FORCE)
set(SDLIMAGE_QOI OFF CACHE BOOL "Disable QOI support" FORCE)
set(SDLIMAGE_SVG OFF CACHE BOOL "Disable SVG support" FORCE)
set(SDLIMAGE_TGA OFF CACHE BOOL "Disable TGA support" FORCE)
set(SDLIMAGE_TIF OFF CACHE BOOL "Disable TIF support" FORCE)
set(SDLIMAGE_WEBP OFF CACHE BOOL "Disable WEBP support" FORCE)
set(SDLIMAGE_XCF OFF CACHE BOOL "Disable XCF support" FORCE)
set(SDLIMAGE_XPM OFF CACHE BOOL "Disable XPM support" FORCE)
set(SDLIMAGE_XV OFF CACHE BOOL "Disable XV support" FORCE)
add_subdirectory(extern/SDL_image)

add_subdirectory(src)