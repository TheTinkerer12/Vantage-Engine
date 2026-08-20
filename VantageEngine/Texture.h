
#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:
    unsigned int ID;
    const char *name;

    Texture(unsigned int ID, const char *name)
    {
        this -> ID = ID;
        this -> name = name;
    }
};

#endif