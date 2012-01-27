#include "ImageFile.hh"
#include <cassert>

ImageFile::ImageFile(const std::string& filename)
    : _filename(filename), _width(0), _heigth(0), _isValid(false), _pixels()
{
}

namespace
{
    void addPixel(ImageFile::pixels_type& pixels,
                  Uint32 pixel, const SDL_PixelFormat* fmt)
    {
        Uint32 temp;
        temp = pixel & fmt->Rmask;
        temp = temp >> fmt->Rshift;
        temp = temp << fmt->Rloss;
        const Uint8 red = static_cast<Uint8>(temp);

        temp = pixel & fmt->Gmask;
        temp = temp >> fmt->Gshift;
        temp = temp << fmt->Gloss;
        const Uint8 green = static_cast<Uint8>(temp);

        temp = pixel & fmt->Bmask;
        temp = temp >> fmt->Bshift;
        temp = temp << fmt->Bloss;
        const Uint8 blue = static_cast<Uint8>(temp);

        temp = pixel & fmt->Amask;
        temp = temp >> fmt->Ashift;
        temp = temp << fmt->Aloss;
        const Uint8 alpha = static_cast<Uint8>(temp);

        pixels.push_back(ImageFile::Color(red, green, blue, alpha));
    }
}

bool
ImageFile::loadImage()
{
    SDL_Surface* surface = IMG_Load(_filename.c_str());
    if (!surface)
        return false;

    const SDL_PixelFormat* fmt = surface->format;
    SDL_LockSurface(surface);

    const int width = surface->w;
    const int height = surface->h;
    _pixels.reserve(width * height);
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            Uint32 pixel = *static_cast<Uint32*>(surface->pixels) + x * width + y;
            addPixel(_pixels, pixel, fmt);
        }
    }

    SDL_UnlockSurface(surface);

    _isValid = true;
    return true;
}

void
ImageFile::write(std::ostream&) const
{
    // FIXME
    assert(false && "Not implemented yet !");
}

const ImageFile::Color&
ImageFile::operator()(int x, int y) const
{
    assert(_isValid && "Can't use invalid ImageFile !");
    return _pixels[x + _pixels.size() + y];
}

ImageFile::Color&
ImageFile::operator()(int x, int y)
{
    assert(_isValid && "Can't use invalid ImageFile !");
    return _pixels[x + _pixels.size() + y];
}

ImageFile::const_iterator
ImageFile::begin() const
{
    assert(_isValid && "Can't use invalid ImageFile !");
    return _pixels.begin();
}

ImageFile::const_iterator
ImageFile::end() const
{
    assert(_isValid && "Can't use invalid ImageFile !");
    return _pixels.end();
}

int
ImageFile::getWidth() const
{
    assert(_isValid && "Can't use invalid ImageFile !");
    return _width;
}

int
ImageFile::getHeight() const
{
    assert(_isValid && "Can't use invalid ImageFile !");
    return _heigth;
}

bool
ImageFile::isValid() const
{
    return _isValid;
}
