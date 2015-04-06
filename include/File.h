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
  };
  
  class FileReader
  {
  private:
    std::string mFile;
  public:

    FileReader(const std::string& fname) : mFile(fname)
    { 
      File afile(fname);
      
      if(!(afile.exists()&&afile.isregular()))
      {
        throw TITCException<exceptions::ITCGeneral>(errno);
      }
      itc::getLog()->info("Reading configuration file: %s", mFile.c_str());
    }

    const std::string& getFileName() const
    {
      return mFile;
    }

    const std::string read()
    {
      std::stringstream s;
      std::fstream fs(mFile, std::ios_base::in);
      if(fs)
      {
        s << fs.rdbuf();
        fs.close();
      }
      return s.str();
    }
  };

}


#endif	/* __FILE_H__ */

