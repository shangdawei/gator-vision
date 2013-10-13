/*
 * FTPSession.h
 *
 *  Created on: Jul 16, 2013
 *      Author: Jeff
 */

#ifndef FTPSESSION_H_
#define FTPSESSION_H_

#include <cstring>
#include <string>
#include "TCPSession.h"

class FTPSession: public TCPSession
{
public:
   FTPSession(int sockfd) : TCPSession(sockfd) {State = FTP_INIT; }
   bool Poll();
   ~FTPSession();

private:
   enum FTPState
   {
      FTP_INIT = 0,
      FTP_USERNAME,
      FTP_PASSWORD,
      FTP_LOGGEDIN
   };

   /* FTP Commands (enumeration) */
   enum FTPCommand
   {
      CMD_UNKNOWN = 0,
      CMD_LINETOOLONG,
      CMD_USER, CMD_PASS, CMD_ACCT, CMD_CWD,  CMD_CDUP, CMD_SMNT,
      CMD_QUIT, CMD_REIN, CMD_PORT, CMD_PASV, CMD_TYPE, CMD_STRU,
      CMD_MODE, CMD_RETR, CMD_STOR, CMD_STOU, CMD_APPE, CMD_ALLO,
      CMD_REST, CMD_RNFR, CMD_RNTO, CMD_ABOR, CMD_DELE, CMD_RMD,
      CMD_MKD,  CMD_PWD,  CMD_LIST, CMD_NLST, CMD_SITE, CMD_SYST,
      CMD_STAT, CMD_HELP, CMD_NOOP, CMD_XCUP, CMD_XCWD, CMD_XMKD,
      CMD_XPWD, CMD_XRMD
   };

   bool GetLine();
   FTPCommand GetCurrentCmd(char ** params, int * params_size);
   void Reply(const char * rpl);

   enum FTPState State;
   static const size_t MAX_LINE_LENGTH = 200;
   char LineBuffer[MAX_LINE_LENGTH];
   size_t LineBuffCount;
   char CmdBuffer[MAX_LINE_LENGTH];
   size_t CmdBuffCount;
   bool LineTooLong;

   /* FTP Reply Codes (sprintf format strings) */
   static const char REPLY_110[];
   static const char REPLY_120[];
   static const char REPLY_125[];
   static const char REPLY_150[];
   static const char REPLY_200[];
   static const char REPLY_202[];
   static const char REPLY_211[];
   static const char REPLY_212[];
   static const char REPLY_213[];
   static const char REPLY_214[];
   static const char REPLY_215[];
   static const char REPLY_220[];
   static const char REPLY_221[];
   static const char REPLY_225[];
   static const char REPLY_226[];
   static const char REPLY_227[];
   static const char REPLY_230[];
   static const char REPLY_250[];
   static const char REPLY_257[];
   static const char REPLY_331[];
   static const char REPLY_332[];
   static const char REPLY_350[];
   static const char REPLY_421[];
   static const char REPLY_425[];
   static const char REPLY_426[];
   static const char REPLY_450[];
   static const char REPLY_451[];
   static const char REPLY_452[];
   static const char REPLY_500[];
   static const char REPLY_501[];
   static const char REPLY_502[];
   static const char REPLY_503[];
   static const char REPLY_504[];
   static const char REPLY_530[];
   static const char REPLY_532[];
   static const char REPLY_550[];
   static const char REPLY_551[];
   static const char REPLY_552[];
   static const char REPLY_553[];



};

#endif /* FTPSESSION_H_ */
