/*
 * FTPSession.cpp
 *
 *  Created on: Jul 16, 2013
 *      Author: Jeff
 */

#include "FTPSession.h"

const char FTPSession::REPLY_110[] = "110 MARK %4s = %4s\r\n";
const char FTPSession::REPLY_120[] = "120 Service ready in %u minutes.\r\n";
const char FTPSession::REPLY_125[] = "125 Data connection already open; transfer starting.\r\n";
const char FTPSession::REPLY_150[] = "150 File status okay; about to open data connection.\r\n";
const char FTPSession::REPLY_200[] = "200 Command okay.\r\n";
const char FTPSession::REPLY_202[] = "202 Command not implemented, superfluous at this site.\r\n";
const char FTPSession::REPLY_211[] = "211 System status, or system help reply.\r\n";
const char FTPSession::REPLY_212[] = "212 Directory status.\r\n";
const char FTPSession::REPLY_213[] = "213 File status.\r\n";
const char FTPSession::REPLY_214[] = "214 Help message.\r\n";
const char FTPSession::REPLY_215[] = "215 Awesome open-source firmware!\r\n";
const char FTPSession::REPLY_220[] = "220 Best damn FTP server ever is ready for action!\r\n";
const char FTPSession::REPLY_221[] = "221 Goodbye.\r\n";
const char FTPSession::REPLY_225[] = "225 Data connection open; no transfer in progress.\r\n";
const char FTPSession::REPLY_226[] = "226 Requested file action successful.  Closing data connection.\r\n";
const char FTPSession::REPLY_227[] = "227 Entering Passive Mode (%u,%u,%u,%u,%u,%u).\r\n";
const char FTPSession::REPLY_230[] = "230 User logged in, proceed.\r\n";
const char FTPSession::REPLY_250[] = "250 Requested file action okay, completed.\r\n";
const char FTPSession::REPLY_257[] = "257 \"%s\" created.\r\n";
const char FTPSession::REPLY_331[] = "331 User name okay, need password.\r\n";
const char FTPSession::REPLY_332[] = "332 Need account for login.\r\n";
const char FTPSession::REPLY_350[] = "350 Requested file action pending further information.\r\n";
const char FTPSession::REPLY_421[] = "421 Service not available, closing control connection.\r\n";
const char FTPSession::REPLY_425[] = "425 Can't open data connection.\r\n";
const char FTPSession::REPLY_426[] = "426 Connection closed; transfer aborted.\r\n";
const char FTPSession::REPLY_450[] = "450 File busy; requested action not taken.\r\n";
const char FTPSession::REPLY_451[] = "451 Requested action aborted: local error in processing.\r\n";
const char FTPSession::REPLY_452[] = "452 Insufficient storage space; requested action not taken.\r\n";
const char FTPSession::REPLY_500[] = "500 Syntax error, command unrecognized.\r\n";
const char FTPSession::REPLY_501[] = "501 Syntax error in parameters or arguments.\r\n";
const char FTPSession::REPLY_502[] = "502 Command not implemented.\r\n";
const char FTPSession::REPLY_503[] = "503 Bad sequence of commands.\r\n";
const char FTPSession::REPLY_504[] = "504 Command not implemented for that parameter.\r\n";
const char FTPSession::REPLY_530[] = "530 Not logged in.\r\n";
const char FTPSession::REPLY_532[] = "532 Need account for storing files.\r\n";
const char FTPSession::REPLY_550[] = "550 File not found; requested action not taken.\r\n";
const char FTPSession::REPLY_551[] = "551 Requested action aborted: page type unknown.\r\n";
const char FTPSession::REPLY_552[] = "552 Exceeded storage allocation; requested file action aborted.\r\n";
const char FTPSession::REPLY_553[] = "553 File name not allowed; requested action not taken.\r\n";


bool FTPSession::Poll()
{
   bool stay_alive = true;
   bool new_cmd;
   enum FTPCommand cmd;
   char * params_ptr;
   int params_size;

   switch (State)
   {
   case FTP_INIT:
      LineBuffCount = 0;
      CmdBuffCount = 0;
      LineTooLong = false;
      Reply(REPLY_220);
      State = FTP_USERNAME;
      break;

   case FTP_USERNAME:
      new_cmd = GetLine();
      if (new_cmd)
      {
         cmd = GetCurrentCmd(&params_ptr, &params_size);
         if (CMD_USER == cmd)
         {
            Reply(REPLY_331);
            State = FTP_PASSWORD;
         }
         else
         {
            Reply(REPLY_530);
         }
      }
      break;

   case FTP_PASSWORD:
      new_cmd = GetLine();
      if (new_cmd)
      {
         cmd = GetCurrentCmd(&params_ptr, &params_size);
         if (CMD_PASS == cmd)
         {
            Reply(REPLY_230);
            State = FTP_LOGGEDIN;
         }
         else
         {
            Reply(REPLY_530);
            State = FTP_USERNAME;
         }
      }
      break;

   case FTP_LOGGEDIN:
      new_cmd = GetLine();
      if (new_cmd)
      {
         cmd = GetCurrentCmd(&params_ptr, &params_size);
         Reply(REPLY_421);
         stay_alive = false;
      }

      break;

   default:
      stay_alive = false;
      break;
   }

   //

   return stay_alive;
}

bool FTPSession::GetLine()
{
   int numbytes;
   bool found_crlf = false;
   size_t crlf_pos;


   do
   {
      // Read the socket stream
      if (LineTooLong)
      {
         // Not gonna use the cmd anyway... just read out chunks the size of the whole buffer
         numbytes = read(SocketNum, LineBuffer, MAX_LINE_LENGTH);
      }
      else
      {
         numbytes = read(SocketNum, LineBuffer + LineBuffCount, MAX_LINE_LENGTH - LineBuffCount);
      }
      LineBuffCount += numbytes;

      // Is the line too long?
      if (LineBuffCount >= MAX_LINE_LENGTH)
      {
         // Set flag
         LineTooLong = true;
      }

      // Look for a crlf
      if (LineTooLong)
      {
         std::string ln(LineBuffer,MAX_LINE_LENGTH);
         crlf_pos = ln.find("\r\n", 0, 2);
         found_crlf = (crlf_pos != std::string::npos);

         if (found_crlf)
         {
            // Just clear the line buffer
            LineBuffCount = 0;
         }
      }
      else
      {
         std::string ln(LineBuffer,MAX_LINE_LENGTH);
         crlf_pos = ln.find("\r\n", 0, 2);
         found_crlf = (crlf_pos != std::string::npos && (crlf_pos < LineBuffCount - 1));

         if (found_crlf)
         {
            // Copy the command line into the command buffer
            memcpy(CmdBuffer, LineBuffer, crlf_pos);
            CmdBuffCount = crlf_pos;

            // Shift the rest of the line buffer to front
            memcpy(LineBuffer, LineBuffer + crlf_pos + 2, MAX_LINE_LENGTH - crlf_pos - 2);
            LineBuffCount -= crlf_pos + 2;
         }
      }

   } while (!found_crlf && numbytes > 0);

   return found_crlf;

}

FTPSession::FTPCommand FTPSession::GetCurrentCmd(char ** params, int * params_size)
{
   FTPSession::FTPCommand cmd;
   if (LineTooLong)
   {
      cmd = CMD_LINETOOLONG;
      LineTooLong = false;
   }
   else if (0 == strncmp(CmdBuffer,"USER",4))
      cmd = CMD_USER;
   else if (0 == strncmp(CmdBuffer,"PASS",4))
      cmd = CMD_PASS;


   switch (cmd)
   {
   case CMD_CWD:
   case CMD_RMD:
   case CMD_MKD:
   case CMD_PWD:
      *params = CmdBuffer + 4;
      *params_size = CmdBuffCount - 4;
      break;

   default:
      *params = CmdBuffer + 5;
      *params_size = CmdBuffCount - 5;
      break;

   }

   return cmd;
}

void FTPSession::Reply(const char * rpl)
{
   write(SocketNum, rpl, strlen(rpl));
}

FTPSession::~FTPSession()
{

}


