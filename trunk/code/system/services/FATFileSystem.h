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
   ;~FATFileSystem();

protected:
   // These are blocking functions implemented by the specific filesystem type
   FSResult Mount(const char (&logical_drive)[_MAX_PATH+1]);
   FSResult Stat(FileInfo & file_info, const char (&path)[_MAX_PATH+1]);
   FSResult Open(FileHandle & file_hndl, const char (&file_path)[_MAX_PATH+1], uint8_t mode);
   FSResult Read(FileHandle & file_hndl, uint8_t * buf, uint32_t btr, uint32_t & br);
   FSResult Write(FileHandle & file_hndl, const uint8_t * buf, uint32_t btw, uint32_t & bw);
   uint64_t Tell(const FileHandle & file_hndl);
   uint64_t Size(const FileHandle & file_hndl);
   bool EOF(const FileHandle & file_hndl);
   bool Error(const FileHandle & file_hndl);
   FSResult Seek(FileHandle & file_hndl, uint32_t offset);
   FSResult Truncate(FileHandle & file_hndl);
   FSResult Sync(FileHandle & file_hndl);
   FSResult OpenDir(DirHandle & dir_hndl, const char (&dir_path)[_MAX_PATH+1]);
   FSResult ReadDir(DirHandle & dir_hndl, FileInfo & file_info);
   FSResult CloseDir(DirHandle & dir_hndl);
   FSResult MkDir(const char (&dir_path)[_MAX_PATH+1]);
   FSResult Unlink(const char (&path)[_MAX_PATH+1]);
   FSResult ChMod(const char (&path)[_MAX_PATH+1], uint8_t attr, uint8_t mask);
   FSResult UTime(const char (&path)[_MAX_PATH+1], const FileInfo & date_time);
   FSResult Rename(const char (&old_name)[_MAX_PATH+1], const char (&new_name)[_MAX_PATH+1]);
   FSResult GetFree(uint64_t & free_bytes);
   FSResult GetLabel(char (&label)[_MAX_LABEL]);

};

#endif /* FATFILESYSTEM_H_ */
