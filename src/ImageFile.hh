#ifndef IMAGEFILE_HH_
# define IMAGEFILE_HH_

#include <string>
#include <vector>
#include <GL/gl.h>
#include <SDL/SDL_image.h>

/*!
** @class ImageFile
**
** Load any type of image and provide an easy way to access each pixel.
*/
class ImageFile
{
public:
    /*!
    ** @struct Color
    **
    ** Internal struct to handle color properties.
    */
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
    /*!
    ** Keep the file name, until it's load.
    **
    ** @param filename The name of the image file.
    */
    ImageFile(const std::string& filename);

    /*!
    ** Load the image from the file.
    **
    ** @return If load succeed.
    */
    bool loadImage();

    /*!
    ** Write the current memory matrix into a stream.
    **
    ** @param An output stream.
    **
    ** Should be used like this:
    ** @code
    ** ImageFile img("image1.png");
    ** img(0,0).red = 56;
    ** std::ofstream file("image2.png");
    ** img.write(file);
    ** @endcode
    */
    void write(std::ostream&) const;

    /*!
    ** Get the color of the pixel at the given coords (no change).
    **
    ** @param x Width coord.
    ** @param y Height coord.
    ** @return Color of the pixel.
    */
    const Color& operator()(int x, int y) const;

    /*!
    ** Get the color of the pixel at the given coords, to change it.
    **
    ** @param x Width coord.
    ** @param y Height coord.
    ** @return Color of the pixel.
    */
    Color& operator()(int x, int y);

    /*!
    ** Get an iterator on the first pixel of the list.
    **
    ** @return An iterator of the first pixel.
    */
    const_iterator begin() const;

    /*!
    ** Get an iterator on the end of the list (after the last pixel).
    **
    ** @return An iterator of the end of the list.
    */
    const_iterator end() const;

    /*!
    ** Get the width of the image.
    **
    ** @return The width of the image.
    */
    int getWidth() const;

    /*!
    ** Get the height of the image.
    **
    ** @return The height of the image.
    */
    int getHeight() const;

    /*!
    ** Check if the ImageFile is correctly loaded.
    **
    ** @return If valid.
    */
    bool isValid() const;

private:
    const std::string _filename;
    int               _width;
    int               _heigth;
    bool              _isValid;
    pixels_type       _pixels;
};

#endif /* !IMAGEFILE_HH_ */
