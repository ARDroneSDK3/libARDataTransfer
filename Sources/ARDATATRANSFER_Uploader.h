/*
    Copyright (C) 2014 Parrot SA

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the 
      distribution.
    * Neither the name of Parrot nor the names
      of its contributors may be used to endorse or promote products
      derived from this software without specific prior written
      permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
    OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
    AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
    OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.
*/
/**
 * @file ARDATATRANSFER_Uploader.h
 * @brief libARDataTransfer uploader header file.
 * @date 21/05/2014
 * @author david.flattin.ext@parrot.com
 **/

#ifndef _ARDATATRANSFER_UPLOADER_PRIVATE_H_
#define _ARDATATRANSFER_UPLOADER_PRIVATE_H_


/**
 * @brief DataDownloader structure
 * @param isInitialized Is set to 1 if Uploader initilized else 0
 * @param isCanceled Is set to 1 if Uploader Thread is canceled else 0
 * @param isRunning Is set to 1 if Uploader Thread is running else 0
 * @param ftp The FTP Uploader connection
 * @param localDirectory The local directory where Uploader download files
 * @param sem The semaphore to cancel the Uploader Thread and its FTP connection
 * @see ARDATATRANSFER_Uploader_New ()
 */
typedef struct
{
    int isCanceled;
    int isRunning;
    eARDATATRANSFER_UPLOADER_RESUME resume;
    ARUTILS_Manager_t *ftpManager;
    char remotePath[ARUTILS_FTP_MAX_PATH_SIZE];
    char localPath[ARUTILS_FTP_MAX_PATH_SIZE];
    ARSAL_Sem_t threadSem;
    
    ARDATATRANSFER_Uploader_ProgressCallback_t progressCallback;
    void *progressArg;
    ARDATATRANSFER_Uploader_CompletionCallback_t completionCallback;
    void *completionArg;
    
} ARDATATRANSFER_Uploader_t;


void ARDATATRANSFER_Uploader_Ftp_ProgressCallback(void* arg, float percent);


#endif /* _ARDATATRANSFER_UPLOADER_PRIVATE_H_ */

