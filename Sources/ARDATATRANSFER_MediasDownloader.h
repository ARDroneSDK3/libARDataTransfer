/**
 * @file ARDATATRANSFER_MediasDownloader.h
 * @brief libARDataTransfer MediasDownloader header file.
 * @date 19/12/2013
 * @author david.flattin.ext@parrot.com
 **/

#ifndef _ARDATATRANSFER_MEDIAS_DOWNLOADER_PRIVATE_H_
#define _ARDATATRANSFER_MEDIAS_DOWNLOADER_PRIVATE_H_

/**
 * @brief Initialize the MediasDownloader
 * @param medias The pointer address of the media list
 * @param count The number of medias in the media list
 * @see ARDATATRANSFER_MediasDownloader_GetAvailableMedias (), ARDATATRANSFER_Media_t
 */
typedef struct
{
    ARDATATRANSFER_Media_t **medias;
    int count;
    
} ARDATATRANSFER_MediaList_t;

/**
 * @brief MediasDownloader structure
 * @param isInitialized Is set to 1 if MediasDownloader initilized else 0
 * @param isRunning Is set to 1 if MediasDownloader Queue Thread is running else 0
 * @param isCanceled Is set to 1 if MediasDownloader Queue Thread is canceled else 0
 * @param isCancelQueued Is set to 1 if MediasDownloader Queue is cancelling all medias else 0
 * @param listFtp The FTP List medias MediasDownloader connection
 * @param ftp The FTP medias body MediasDownloader connection
 * @param localDirectory The local directory where MediasDownloader download files
 * @param listSem The semaphore to cancel the DataDownloader FTP List connection
 * @param queueSem The semaphore to cancel the DataDownloader Queue
 * @param threadSem The semaphore to cancel the DataDownloader Thread and its FTP connection
 * @param queue The medias queue
 * @see ARDATATRANSFER_MediasDownloader_New ()
 */
typedef struct
{
    int isRunning;
    int isCanceled;
    ARUTILS_Ftp_Connection_t *listFtp;
    ARUTILS_Ftp_Connection_t *deleteFtp;
    ARUTILS_Ftp_Connection_t *ftp;
    char localDirectory[ARUTILS_FTP_MAX_PATH_SIZE];
    ARSAL_Sem_t listSem;
    ARSAL_Sem_t queueSem;
    ARSAL_Sem_t threadSem;
    ARSAL_Mutex_t mediasLock;
    ARDATATRANSFER_MediaList_t medias;
    ARDATATRANSFER_MediasQueue_t queue;

} ARDATATRANSFER_MediasDownloader_t;

/**
 * @brief Initialize the MediasDownloader
 * @warning This function allocates memory
 * @param manager The pointer of the ARDataTransfer Manager
 * @param deviceIP The IP address of the Device
 * @param devicePort The FTP port of the Device
 * @param localDirectory The path of the local directory where to store medias
 * @retval On success, returns ARDATATRANSFER_OK. Otherwise, it returns an error number of eARDATATRANSFER_ERROR.
 * @see ARDATATRANSFER_MediasDownloader_ThreadRun ()
 */
eARDATATRANSFER_ERROR ARDATATRANSFER_MediasDownloader_Initialize(ARDATATRANSFER_Manager_t *manager, const char *deviceIP, int port, const char *localDirectory);

/**
 * @brief Delete an ARDataTransfer MediasDownloader connection data
 * @warning This function frees memory
 * @param manager The address of the pointer on the ARDataTransfer Manager
 * @see ARDATATRANSFER_MediasDownloader_New ()
 */
void ARDATATRANSFER_MediasDownloader_Clear(ARDATATRANSFER_Manager_t *manager);

/**
 * @brief Get the media thumbnail from the device FTP server
 * @warning This function allocates memory
 * @param manager The address of the pointer on the ARDataTransfer Manager
 * @param media The media for which the thumbnail is requested
 * @retval On success, returns ARDATATRANSFER_OK. Otherwise, it returns an error number of eARDATATRANSFER_ERROR.
 * @see
 */
eARDATATRANSFER_ERROR ARDATATRANSFER_MediasDownloader_GetThumbnail(ARDATATRANSFER_Manager_t *manager, ARDATATRANSFER_Media_t *media);

/**
 * @brief Progress callback of the FtpMedia download
 * @param manager The address of the pointer on the ARDataTransfer Manager
 * @param arg The progress arg (ftpMedia)
 * @param percent The percent size of the media file already downloaded
 * @see ARDATATRANSFER_MediasDownloader_DownloadMedia ()
 */
void ARDATATRANSFER_MediasDownloader_FtpProgressCallback(void* arg, uint8_t percent);

/**
 * @brief Download an FTP Media
 * @param manager The address of the pointer on the ARDataTransfer Manager
 * @param ftpMedia The media to be downloaded
 * @param percent The percent size of the media file already downloaded
 * @retval On success, returns ARDATATRANSFER_OK. Otherwise, it returns an error number of eARDATATRANSFER_ERROR.
 * @see ARDATATRANSFER_MediasDownloader_FtpProgressCallback ()
 */
eARDATATRANSFER_ERROR ARDATATRANSFER_MediasDownloader_DownloadMedia(ARDATATRANSFER_Manager_t *manager, ARDATATRANSFER_FtpMedia_t *ftpMedia);

/**
 * @brief Remove a media from the medias list
 * @param manager The address of the pointer on the ARDataTransfer Manager
 * @param media The media to remove from the medias list
 * @see ARDATATRANSFER_MediasDownloader_GetAvailableMediasSync ()
 */
eARDATATRANSFER_ERROR ARDATATRANSFER_MediasDownloader_RemoveMediaFromMediaList(ARDATATRANSFER_Manager_t *manager, ARDATATRANSFER_Media_t *media);

/**
 * @brief Free a medias list
 * @param mediaList The list of medias
 * @see ARDATATRANSFER_MediasDownloader_GetAvailableMediasSync ()
 */
void ARDATATRANSFER_MediasDownloader_FreeMediaList(ARDATATRANSFER_MediaList_t *mediaList);

#endif /* _ARDATATRANSFER_MEDIAS_DOWNLOADER_PRIVATE_H_ */
