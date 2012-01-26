#ifndef IMAGEFILE_HH_
# define IMAGEFILE_HH_

#include <string>
#include <vector>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_image.h>

class ImageFile
{
public:
    struct Color
    {
        Color()
            : red(0), green(0), blue(0), alpha(0)
        {
        }

        Color(Uint8 cred, Uint8 cgreen, Uint8 cblue, Uint8 calpha)
            : red(cred), green(cgreen), blue(cblue), alpha(calpha)
        {
        }

        Uint8 red;
        Uint8 green;
        Uint8 blue;
        Uint8 alpha;
    };
public:
    typedef std::vector<Color> pixels_type;
    typedef pixels_type::const_iterator const_iterator;
public:
    ImageFile(const std::string& filename);
    ~ImageFile();

    bool loadImage();

    const Color& operator()(int x, int y) const;
    Color& operator()(int x, int y);
    const_iterator begin() const;
    const_iterator end() const;
    int getWidth() const;
    int getHeight() const;
private:
    int               _width;
    int               _heigth;
    const std::string _filename;
    pixels_type       _pixels;
};

#endif /* !IMAGEFILE_HH_ */
