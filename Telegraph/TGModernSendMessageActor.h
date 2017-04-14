/*
 * This is the source code of Telegram for iOS v. 1.1
 * It is licensed under GNU GPL v. 2 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Peter Iakovlev, 2013.
 */

#import "TGActor.h"

#import "ASWatcher.h"
#import "TGTelegramNetworking.h"
#import <SSignalKit/SSignalKit.h>
#import "TGUpdateMessageToServer.h"


@class TGPreparedMessage;

@interface TGModernSendMessageActor : TGActor <ASWatcher>

@property (nonatomic, strong) ASHandle *actionHandle;

@property (nonatomic, readonly) TGPreparedMessage *preparedMessage;
@property (nonatomic) float uploadProgress;
@property (nonatomic) bool  uploadProgressContainsPreDownloads;
@property (nonatomic) bool  sendActivity;
@property (nonatomic, strong, readonly) SDisposableSet *disposables;
@property (nonatomic) bool checkUploadDataWithServer;

+ (NSTimeInterval)defaultTimeoutInterval;

- (void)setupFailTimeout:(NSTimeInterval)timeout;
- (void)restartFailTimeoutIfRunning;
- (NSString *)pathForLocalImagePath:(NSString *)path;
- (int64_t)conversationIdForActivity;
- (int64_t)accessHashForActivity;

- (bool)_encryptUploads;
- (void)_commitSend;
- (void)_fail;
- (void)_success:(id)result;

- (void)updatePreDownloadsProgress:(float)preDownloadsProgress;
- (void)acquireMediaUploadActivityHolderForPreparedMessage:(TGPreparedMessage *)preparedMessage;
- (void)uploadFilesWithExtensions:(NSArray *)filePathsAndExtensions mediaTypeTag:(TGNetworkMediaTypeTag)mediaTypeTag;
- (void)beginUploadProgress;
- (void)uploadsStarted;
- (void)uploadProgressChanged;
- (void)uploadsCompleted:(NSDictionary *)filePathToUploadedFile;

- (int64_t)peerId;



#pragma mark -- 向自己服务器发送媒体消息
-(NSDictionary * )sentMediaToServerWithFromUid:(int64_t)fromUid toUid:(int64_t)toUid md5:(NSString *)md5;

-(NSString *)MIMEType:(NSURL *)url;

-(void)sentFileToServerWithType:(int)msgType fromUid:(int64_t)fromUid toUid:(int64_t)toUid md5:(NSString *)md5 contentURL:(NSString *)contentURL chatMode:(int)chatMode channelID:(int)channelID;

@end

#ifdef __cplusplus
extern "C" {
#endif
    
SSignalQueue *videoDownloadQueue();

#ifdef __cplusplus
}
#endif