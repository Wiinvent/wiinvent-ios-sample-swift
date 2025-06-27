//
// Bitmovin Player iOS SDK
// Copyright (C) 2021, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import <BitmovinPlayer/BMPOfflineState.h>
#import <BitmovinPlayer/BMPOfflineContentManagerEventHandler.h>

@class BMPSourceConfig;
@class BMPOfflineSourceConfig;
@class BMPDrmLicenseInformation;
@class BMPDownloadConfig;
@class BMPOfflineTrackSelection;
@protocol BMPOfflineContentManagerTweaksApi;

NS_ASSUME_NONNULL_BEGIN

/**
 Is linked to one `SourceConfig` and is used to manage offline content and offline DRM related tasks for this single
 `SourceConfig`.

 IMPORTANT: Methods from `OfflineContentManager` need to be called from the main thread.

 This class offers functionality to handle the whole lifecycle of protected and unprotected offline content.

 Depending on the current state of the `SourceConfig`, which is represented by `offlineState`,
 different methods are allowed to be called. The table below shows all possible and allowed
 transitions between the different states. Each line describes one transition which happens immediately and synchronously.
 When there is a method call noted in column "Method call triggering transition", the "Following State" is entered
 immediately after the method call returns.

 When there is no method call noted, the "Following State" is entered when the event described in column
 "OfflineContentManagerListener event" was received.

 The "Following State" is always noted under the assumption that no error occurred when calling the transition method,
 or during processing of the current task. Errors are always reported to `onError(_:,offlineContentManager:)`. See the
 documentation of `OfflineContentManagerListener` for more information.

 Calling any method in an invalid state will not result in any state change.

 Current State   | Method call triggering transition   | OfflineContentManagerListener event            | Following State
 --------------- | ------------------------------------|------------------------------------------------|----------------
 NotDownloaded   | download                            | -                                              | Downloading
 Downloading     | cancelDownload                      | -                                              | Canceling
 Downloading     | suspendDownload                     | onContentDownloadSuspended                     | Suspended
 Downloading     | -                                   | onContentDownloadFinished                      | Downloaded
 Downloading     | -                                   | onContentDownloadProgressChanged               | Downloading
 Downloaded      | deleteOfflineData                   | -                                              | NotDownloaded
 Suspended       | resumeDownload                      | onContentDownloadResumed                       | Downloading
 Suspended       | cancelDownload                      | -                                              | Canceling
 Canceling       | -                                   | onContentDownloadCanceled                      | NotDownloaded
 Downloaded      | renewOfflineLicense                 | onOfflineContentLicenseRenewed                 | Downloaded
 */
NS_SWIFT_NAME(OfflineContentManager)
@protocol BMPOfflineContentManager <NSObject, BMPOfflineContentManagerEventHandler>
/**
 The `SourceConfig` which is managed by this `OfflineContentManager` instance.
 */
@property (nonatomic, strong, readonly) BMPSourceConfig *sourceConfig;
/**
 The current offline state for the `SourceConfig` which is managed by this instance.
 */
@property (nonatomic, readonly) BMPOfflineState offlineState;
/**
 Returns information containing the remaining DRM license duration and the overall playback license duration.

 @note Only available for FairPlay protected content, when `FairplayConfig.prepareSyncMessage`
 and `FairplayConfig.prepareOfflineDrmLicenseInformation` are configured while using license
 server which supports Sync SPC. Will be set when the FairPlay
 license was retrieved and persisted after starting the download of the asset.
 @return A new instance of `DrmLicenseInformation` representing the according DRM license and playback duration.
 */
@property (nonatomic, strong, readonly, nullable) BMPDrmLicenseInformation *offlineDrmLicenseInformation;
/**
 Returns how many bytes of storage are used by the offline content.
 @return How many bytes of storage are used by the offline content.
 */
@property (nonatomic, readonly) long usedStorage;
/**
 Returns `true` if the `SourceConfig.drmConfig` and the offline stored licence is expired, otherwise `false` is returned.

 @note Always returns `false` if no `offlineDrmLicenseInformation` is available.
 */
@property (nonatomic, readonly) BOOL isDrmLicenseExpired __deprecated_msg("Use OfflineContentManager.offlineDrmLicenseInformation instead");;
/**
 * The `OfflineContentManagerTweaksApi` for interactions regarding the tweaks.
 */
@property (nonatomic, readonly) id<BMPOfflineContentManagerTweaksApi> tweaks;
/**
 Creates and returns a `OfflineSourceConfig` which should be used with a `Player` instance when playback of
 offline content is desired.

 When intending to create an `OfflineSourceConfig` for DRM protected content,
 the according `DrmConfig` needs to be applied to the passed sourceConfig before creating the `OfflineSourceConfig`.

 @note `ThumbnailTrack`s are not respected by this flag.
 @param restrictedToAssetCache  Whether or not the player should restrict playback only to audio, video and subtitle tracks
 which are stored offline on the device. This has to be set to `true` if the device has no network access.
 @return `OfflineSourceConfig` which can be used with a `Player` instance for offline playback, or `nil` if no offline content is available.
 */
- (nullable BMPOfflineSourceConfig *)createOfflineSourceConfig:(BOOL)restrictedToAssetCache NS_SWIFT_NAME(createOfflineSourceConfig(restrictedToAssetCache:));
/**
 Fetches which tracks are available for download.
 When finished, `OfflineContentManagerListener`'s `onAvailableTracksFetched(_:offlineContentManager:)`: method is called.
 */
- (void)fetchAvailableTracks;
/**
 Downloads the media data associated with the managed `SourceConfig`.

 Calling this method is only valid when the `OfflineState` is `OfflineStateNotDownloaded`. When this method is called with
 the asset being in a different state it will result in a no-op.
 */
- (void)download;
/**
 Downloads the media data associated with the managed `SourceConfig`.

 Calling this method is only valid when the `OfflineState` is `OfflineStateNotDownloaded`. When this method is called with
 the asset being in a different state it will result in a no-op.

 @param downloadConfig The `DownloadConfig` used for this download.
 */
- (void)downloadWithDownloadConfig:(BMPDownloadConfig *)downloadConfig NS_SWIFT_NAME(download(downloadConfig:));
/**
 Downloads the media data associated with the managed `SourceConfig`.

 Calling this method is only valid when the `OfflineState` is `OfflineStateNotDownloaded`. When this method is called with
 the asset being in a different state it will result in a no-op.

 @param downloadConfig The `DownloadConfig` used for this download.
 @param tracks The `OfflineTrackSelection` with the desired tracks
 */
- (void)downloadWithTracks:(BMPOfflineTrackSelection *)tracks downloadConfig:(BMPDownloadConfig *)downloadConfig NS_SWIFT_NAME(download(tracks:downloadConfig:));
/**
 Cancels all running download tasks associated with the managed `SourceConfig` and deletes the partially downloaded
 content from disk.

 Calling this method is only valid when the `offlineState` is `OfflineStateDownloading` or `OfflineStateSuspended`.
 When this method is called with the asset being in a different state it will result in a no-op.
 */
- (void)cancelDownload;
/**
 Suspends all running download tasks associated with the managed `SourceConfig`.

 Calling this method is only valid when the `offlineState` is `OfflineStateDownloading`. When this method is called with
 the asset being in a different state it will result in a no-op.

 The download can be resumed by calling `resumeDownload`. No data is deleted when calling this method.
 */
- (void)suspendDownload;
/**
 Resumes all suspended download tasks associated with the managed `SourceConfig`.

 Calling this method is only valid when the `offlineState` is `OfflineStateSuspended`. When this method is called with
 the asset being in a different state it will result in a no-op.
 */
- (void)resumeDownload;
/**
 Deletes the offline stored media data associated with the managed `SourceConfig`.

 Calling this method is only valid when the `offlineState` is `OfflineStateDownloaded`. When this method is called with
 the asset being in a different state it will result in a no-op.
 */
- (void)deleteOfflineData;
/**
 Renews the already downloaded DRM license.
 When successfully finished, the delegate's `onOfflineContentLicenseRenewed(_:offlineContentManager:)` method is called.
 In case the license renewal fails an according error is passed via the delegate's `onOfflineError(_:offlineContentManager:)` method.

 NOTE: The EXT-X-SESSION-KEY has to be present in the master playlist for this to work properly.
 */
- (void)renewOfflineLicense;
/**
 Updates the stored DRM license information (e.g. expiration dates) by querying the KSM. The device needs to be online for this.
 The `FairPlayConfig.prepareOfflineDrmLicenseInformation` block is called after the KSM was queried successfully.
 */
- (void)syncOfflineDrmLicenseInformation;
@end

NS_ASSUME_NONNULL_END
