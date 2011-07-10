#ifndef IRENDER_H
#define IRENDER_H

//this is a place holder
typedef GameObject renderObj;

class IRenderer
{
  public:
    virtual bool registerConstantObj( const unsigned int& id, renderObj* obj ) = 0;
    virtual bool deleteConstantObj( const unsigned int& id ) = 0;

    virtual bool refresh() = 0;
    virtual bool resize
      (
      const unsigned int& width,
      const unsigned int& height,
      const unsigned int& depth
      ) = 0;

    virtual bool isSetup() = 0;

    virtual unsigned int height() = 0;
    virtual unsigned int width() = 0;
    virtual unsigned int depth() = 0;

    virtual bool update
      (
      const unsigned int& turn,
      const unsigned int& frame
      ) = 0;

    virtual void update() = 0;
    
};

#endif
