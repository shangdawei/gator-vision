/*
 * FATFileSystem.h
 *
 *  Created on: Jul 15, 2013
 *      Author: Jeff
 */

#ifndef FATFILESYSTEM_H_
#define FATFILESYSTEM_H_

#include "FileSystem.h"

class FATFileSystem : public FileSystem
{
public:
   FATFileSystem();
   virtual ~FATFileSystem();

protected:
   // These are blocking functions implemented by the specific filesystem type
   FSResult Mount(const string & logical_drive);
   FSResult Stat(FileInfo & file_info, const string & path);
   FSResult Open(FileHandle & file_hndl, const string & file_path, uint8_t mode);
   FSResult Read(FileHandle & file_hndl, uint8_t * buf, uint32_t btr, uint32_t & br);
   FSResult Write(FileHandle & file_hndl, const uint8_t * buf, uint32_t btw, uint32_t & bw);
   uint64_t Tell(const FileHandle & file_hndl);
   uint64_t Size(const FileHandle & file_hndl);
   bool EOF(const FileHandle & file_hndl);
   bool Error(const FileHandle & file_hndl);
   FSResult Seek(FileHandle & file_hndl, uint32_t offset);
   FSResult Truncate(FileHandle & file_hndl);
   FSResult Sync(FileHandle & file_hndl);
   FSResult OpenDir(DirHandle & dir_hndl, const string & dir_path);
   FSResult ReadDir(DirHandle & dir_hndl, FileInfo & file_info);
   FSResult CloseDir(DirHandle & dir_hndl);
   FSResult MkDir(const string & dir_path);
   FSResult Unlink(const string & path);
   FSResult ChMod(const string & path, uint8_t attr, uint8_t mask);
   FSResult UTime(const string & path, const FileInfo & date_time);
   FSResult Rename(const string & old_name, const string & new_name);
   FSResult GetFree(uint64_t & free_bytes);
   FSResult GetLabel(string & label, string & serial_no);

};

#endif /* FATFILESYSTEM_H_ */
