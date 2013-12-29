/*
 * FATFileSystem.cpp
 *
 *  Created on: Jul 15, 2013
 *      Author: Jeff
 */

#include "FATFileSystem.h"

FATFileSystem::FATFileSystem()
{
   // TODO Auto-generated constructor stub

}

FATFileSystem::~FATFileSystem()
{
   // TODO Auto-generated destructor stub
}

FileSystem::FSResult FATFileSystem::Mount(const string & logical_drive)
{
   return DISK_ERR;
}

FileSystem::FSResult FATFileSystem::Stat(FileInfo & file_info, const string & path)
{
   return DISK_ERR;
}

FileSystem::FSResult FATFileSystem::Open(FileHandle & file_hndl, const string & file_path, uint8_t mode)
{
   return DISK_ERR;
}

FileSystem::FSResult FATFileSystem::Read(FileHandle & file_hndl, uint8_t * buf, uint32_t btr, uint32_t & br)
{
   return DISK_ERR;
}

FileSystem::FSResult FATFileSystem::Write(FileHandle & file_hndl, const uint8_t * buf, uint32_t btw, uint32_t & bw)
{
   return DISK_ERR;
}

uint64_t FATFileSystem::Tell(const FileHandle & file_hndl)
{
   return 0;
}

uint64_t FATFileSystem::Size(const FileHandle & file_hndl)
{
   return 0;
}

bool FATFileSystem::EOF(const FileHandle & file_hndl)
{
   return false;
}

bool FATFileSystem::Error(const FileHandle & file_hndl)
{
   return false;
}

FileSystem::FSResult FATFileSystem::Seek(FileHandle & file_hndl, uint32_t offset)
{
   return DISK_ERR;
}

FileSystem::FSResult FATFileSystem::Truncate(FileHandle & file_hndl)
{
   return DISK_ERR;
}

FileSystem::FSResult FATFileSystem::Sync(FileHandle & file_hndl)
{
   return DISK_ERR;
}

FileSystem::FSResult FATFileSystem::OpenDir(DirHandle & dir_hndl, const string & dir_path)
{
   return DISK_ERR;
}

FileSystem::FSResult FATFileSystem::ReadDir(DirHandle & dir_hndl, FileInfo & file_info)
{
   return DISK_ERR;
}

FileSystem::FSResult FATFileSystem::CloseDir(DirHandle & dir_hndl)
{
   return DISK_ERR;
}

FileSystem::FSResult FATFileSystem::MkDir(const string & dir_path)
{
   return DISK_ERR;
}

FileSystem::FSResult FATFileSystem::Unlink(const string & path)
{
   return DISK_ERR;
}

FileSystem::FSResult FATFileSystem::ChMod(const string & path, uint8_t attr, uint8_t mask)
{
   return DISK_ERR;
}

FileSystem::FSResult FATFileSystem::UTime(const string & path, const FileInfo & date_time)
{
   return DISK_ERR;
}

FileSystem::FSResult FATFileSystem::Rename(const string & old_name, const string & new_name)
{
   return DISK_ERR;
}

FileSystem::FSResult FATFileSystem::GetFree(uint64_t & free_bytes)
{
   return DISK_ERR;
}

FileSystem::FSResult FATFileSystem::GetLabel(string & label, string & serial_no)
{
   return DISK_ERR;
}

