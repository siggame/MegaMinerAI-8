// if this were for windows only I would make this file a DLL
//but it isn't, so I'm forced to make this just a seperate .cpp
//for ease of editing
// 	~Alex Shepard
//	aksfkb@mst.edu

#include "resourceman.h"
#include "typedefs.h"
#include <QDir>
#include <QFileInfo>
#include <QString>
#include <iostream>
#include <fstream>
#include <sstream>

namespace visualizer
{

  ResourceType getResTypeFromStr(const std::string & typeBuff)
  {
    if ( "texture" == typeBuff )
      return RT_TEXTURE;

    if ( "animation" == typeBuff )
      return RT_ANIMATION;

    if( "font" == typeBuff )
      return RS_FONT;

    return RT_NONE;
  }


  bool _ResourceMan::loadResourceFile(const std::string & filename)
  {
    QFileInfo fInfo( filename.c_str() );

    std::ifstream input(filename.c_str());

    if( !input.is_open() )
    {    
      THROW
        (
        FileException, 
        "Unable to load resource file: \n  %s", filename.c_str()
        );
    } 

    if (input.eof())
    {
      THROW
        (
        FileException,
        "Resource file is empty: \n  %s", filename.c_str()
        );
    }

    std::string buffer;
    unsigned int lineNum = 1;
    while (!input.eof())
    {
      std::stringstream ss;

      getline(input,buffer);

      if (buffer.size())
      {
        //2 different line carriages because windows is strange
        if (buffer.c_str()[0] != '#' && buffer.c_str()[0] != '\n' && buffer.c_str()[0] != (char)13)
        {
          ss << buffer;
          std::string typebuff;
          std::string namebuff;

          ss >> typebuff;
          ResourceType rt = getResTypeFromStr(typebuff);

          if (ss >> namebuff)
          {
            if (!exists(namebuff))
            {
              std::string tempPath, pathBuff;
              ss >> tempPath; 
              pathBuff = qPrintable( fInfo.dir().path() );
              pathBuff += "/";
              pathBuff += tempPath;

              switch (rt)
              {
                case RT_TEXTURE:
                {
                  loadTexture( pathBuff, namebuff );
                  break;
                }
                case RT_ANIMATION:
                {
                  loadAnimation( pathBuff, namebuff );

                } break;
                case RS_FONT:
                {
                  std::string fontWidthFile;
                  ss >> fontWidthFile;
                  std::string fontPath = qPrintable( fInfo.dir().path() );
                  fontPath += "/";
                  fontPath += fontWidthFile;
                  loadFont( fontPath, pathBuff, namebuff );
                } break;
                default:
                  THROW
                    (
                    Exception,
                    "Resource Load Error Line %d: '%s' is not a type.",
                    lineNum, 
                    typebuff.c_str()
                    );
              }
            }
            else
            {
#if __DEBUG__
             cerr << "Resource Load Error Line " << lineNum << ": Resource name '" << namebuff << "' already exists" << endl;
#endif
            }
          }
          else
          {
            THROW
              (
              Exception,
              "Resource Load Error Line %d: Name buffer read error.",
              lineNum
              );
          }
        }
      }

      lineNum++;
    }

    input.close();
    return true;

  }


  /** @brief reg
   * register a value from a file
   * @param rName the id to register the resource with
   * @param filename the value exists at (ex: mypic.png)
   * @return true if the file load was successful and the id didnt exist
   */
  bool _ResourceMan::regFile(const ResID_t& rName, const std::string& /*filename*/)
  {
    if (!exists(rName))
    {
      //load File

      return true;
    }

    THROW
      (
      Exception,
      "Resource name conflict. Name: '%s' already exists\n",
      rName.c_str()
      );
    return false;
  }


  /** @brief saveResourceFile
   * save the resources to a file
   * @param filename the name of the file to save to
   * @return true if it is successful
   */
  bool _ResourceMan::saveResourceFile(const std::string& /*filename*/)
  {

    return false;
  }

} // visualizer

