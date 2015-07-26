/**
 * Copyright Pavel Kraynyukhov 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 * 
 * $Id: file.h 5 Апрель 2015 г. 1:28 pk$
 * 
 * EMail: pavel.kraynyukhov@gmail.com
 * 
 **/

#ifndef __FILE_H__
#  define	__FILE_H__

#  include <sys/types.h>
#  include <sys/stat.h>
#  include <unistd.h>
#  include <string>
#  include <sstream>

namespace utils
{

  class File
  {
   private:
    std::string mName;
    struct stat mStats;
    bool mExists;
   public:

    File(const std::string& name)
      :mName(name), mExists(false)
    {
      if(name.empty())
        throw std::logic_error("File(), - empty string provided as the file name");

      if(!exists())
        throw std::runtime_error("No such file or directory: " + mName);
    }

    bool exists()
    {
      struct stat buf;
      int ret = stat(mName.c_str(), &mStats);
      if(ret == 0)
      {
        mExists = true;
        return true;
      }
      else
      {
        return false;
      }
    }

    const bool isdir() const
    {
      return((mStats.st_mode & S_IFDIR) != 0);
    }

    const bool isregular() const
    {
      return((mStats.st_mode & S_IFREG) != 0);
    }

    const bool isfifo() const
    {
      return((mStats.st_mode & S_IFIFO) != 0);
    }

    const bool ischar() const
    {
      return((mStats.st_mode & S_IFCHR) != 0);
    }

    const bool isblock() const
    {
      return((mStats.st_mode & S_IFBLK) != 0);
    }

    const bool islink() const
    {
      return((mStats.st_mode & S_IFLNK) != 0);
    }

    const bool issocket() const
    {
      return((mStats.st_mode & S_IFSOCK) != 0);
    }
    
    const std::string& getName() const
    {
      return mName;
    }
  };
  
  class FileReader
  {
  private:
    std::string mFile;
  public:

    explicit FileReader(const std::string& fname) : mFile(fname)
    { 
      if(mFile.length() > 0)
      {
        File afile(fname);

        if(!(afile.exists()&&afile.isregular()))
        {
          throw std::logic_error("File "+fname+" does not exists or is not regular");
        }
      }
      else
      {
        throw std::logic_error("FileReader(), - file name is empty.");
      }
    }

    const std::string& getFileName() const
    {
      return mFile;
    }

    const std::string readAsText()
    {
      std::stringstream s;
      std::fstream fs(getFileName(), std::ios_base::in);
      
      if(fs)
      {
        s << fs.rdbuf();
        fs.close();
      }
      else
      {
        const std::string msg(std::string("FileReader::readAsText(), - Can't open the file for reading."));
        throw std::logic_error(msg);
      }
      return s.str();
    }
  };

}


#endif	/* __FILE_H__ */

