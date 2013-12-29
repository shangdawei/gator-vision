/*
 * FileSystem.h
 *
 *  Created on: Jul 15, 2013
 *      Author: Jeff
 */

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <stdint.h>
#include <string>
using namespace std;

class FileSystem
{
public:
   FileSystem();
   virtual ~FileSystem();

   /* Set of enum values borrowed from FatFS as a starting point */
   enum FSResult
   {
      OK = 0,              /* (0) Succeeded */
      DISK_ERR,            /* (1) A hard error occurred in the low level disk I/O layer */
      INT_ERR,             /* (2) Assertion failed */
      NOT_READY,           /* (3) The physical drive cannot work */
      NO_FILE,             /* (4) Could not find the file */
      NO_PATH,             /* (5) Could not find the path */
      INVALID_NAME,        /* (6) The path name format is invalid */
      DENIED,              /* (7) Access denied due to prohibited access or directory full */
      EXIST,               /* (8) Access denied due to prohibited access */
      INVALID_OBJECT,      /* (9) The file/directory object is invalid */
      WRITE_PROTECTED,     /* (10) The physical drive is write protected */
      INVALID_DRIVE,       /* (11) The logical drive number is invalid */
      NOT_ENABLED,         /* (12) The volume has no work area */
      NO_FILESYSTEM,       /* (13) There is no valid FAT volume */
      MKFS_ABORTED,        /* (14) The f_mkfs() aborted due to any parameter error */
      TIMEOUT,             /* (15) Could not get a grant to access the volume within defined period */
      LOCKED,              /* (16) The operation is rejected according to the file sharing policy */
      NOT_ENOUGH_CORE,     /* (17) LFN working buffer could not be allocated */
      TOO_MANY_OPEN_FILES, /* (18) Number of open files > _FS_SHARE */
      INVALID_PARAMETER    /* (19) Given parameter is invalid */
   };

   struct FileInfo
   {
      uint64_t Size;
      uint32_t Date;
      uint32_t Time;
      uint32_t Attrib;
      string   Name;
   };

   struct FileHandle
   {
      string         FilePath;
      FileSystem *   Source;
      void *         TrackingObject;
   };

   struct DirHandle
   {
      string         DirPath;
      FileSystem *   Source;
      void *         TrackingObject;
   };

protected:
   // These are blocking functions implemented by the specific filesystem type
   virtual FSResult Mount(const string & logical_drive) = 0;
   virtual FSResult Stat(FileInfo & file_info, const string & path) = 0;
   virtual FSResult Open(FileHandle & file_hndl, const string & file_path, uint8_t mode) = 0;
   virtual FSResult Read(FileHandle & file_hndl, uint8_t * buf, uint32_t btr, uint32_t & br) = 0;
   virtual FSResult Write(FileHandle & file_hndl, const uint8_t * buf, uint32_t btw, uint32_t & bw) = 0;
   virtual uint64_t Tell(const FileHandle & file_hndl) = 0;
   virtual uint64_t Size(const FileHandle & file_hndl) = 0;
   virtual bool EOF(const FileHandle & file_hndl) = 0;
   virtual bool Error(const FileHandle & file_hndl) = 0;
   virtual FSResult Seek(FileHandle & file_hndl, uint32_t offset) = 0;
   virtual FSResult Truncate(FileHandle & file_hndl) = 0;
   virtual FSResult Sync(FileHandle & file_hndl) = 0;
   virtual FSResult OpenDir(DirHandle & dir_hndl, const string & dir_path) = 0;
   virtual FSResult ReadDir(DirHandle & dir_hndl, FileInfo & file_info) = 0;
   virtual FSResult CloseDir(DirHandle & dir_hndl) = 0;
   virtual FSResult MkDir(const string & dir_path) = 0;
   virtual FSResult Unlink(const string & path) = 0;
   virtual FSResult ChMod(const string & path, uint8_t attr, uint8_t mask) = 0;
   virtual FSResult UTime(const string & path, const FileInfo & date_time) = 0;
   virtual FSResult Rename(const string & old_name, const string & new_name) = 0;
   virtual FSResult GetFree(uint64_t & free_bytes) = 0;
   virtual FSResult GetLabel(string & label, string & serial_no) = 0;
};

#endif /* FILESYSTEM_H_ */