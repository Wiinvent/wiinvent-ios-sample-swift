//
// Bitmovin Player iOS SDK
// Copyright (C) 2017, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import <BitmovinPlayer/BMPOfflineState.h>

@protocol BMPOfflineManagerListener;
@protocol BMPOfflineManagerDelegate;
@protocol BMPOfflineContentManager;
@class BMPSourceConfig;
@class BMPOfflineSourceConfig;
@class BMPOfflineTrackSelection;
@class BMPOfflineConfig;
@class BMPDrmLicenseInformation;
@class BMPDownloadConfig;

NS_ASSUME_NONNULL_BEGIN

/**
 * IMPORTANT: Methods from BMPOfflineManager need to be called from the main thread.
 *
 * This class offers functionality to handle the whole lifecycle of protected and unprotected offline content. Do not
 * create own instances of it, instead use [OfflineManager sharedInstance] to obtain a reference to the singleton.
 *
 * Depending on the current state of the SourceConfig, which can be obtained by calling offlineStateForSourceConfig:,
 * different methods are allowed to be called on the BMPOfflineManager. The table below shows all possible and allowed
 * transitions between the different states. Each line describes one transition which happens immediately and synchronous.
 * When there is a method call noted in column "Method call triggering transition", the "Following State" is entered
 * immediately after the method call returns.
 *
 * When there is no method call noted, the "Following State" is entered when the event described in column
 * "BMPOfflineManagerListener event" was received.
 *
 * The "Following State" is always noted under the assumption that no error occurred when calling the transition method,
 * or during processing of the current task. Errors are always reported to offlineManager:didFailWithError:. See the
 * documentation of OfflineManagerListener for more information.
 *
 *  Current State   | Method call triggering transition   | BMPOfflineManagerListener event               | Following State
 *  --------------- | ------------------------------------|-----------------------------------------------|----------------
 *  NotDownloaded   | downloadSourceConfig:               | -                                             | Downloading
 *  Downloading     | cancelDownloadForSourceConfig:      | -                                             | Canceling
 *  Downloading     | suspendDownloadForSourceConfig:     | offlineManagerDidSuspendDownload:             | Suspended
 *  Downloading     | -                                   | offlineManagerDidFinishDownload:              | Downloaded
 *  Downloading     | -                                   | offlineManager:didProgressTo:                 | Downloading
 *  Downloaded      | deleteOfflineDataForSourceConfig:   | -                                             | NotDownloaded
 *  Suspended       | resumeDownloadForSourceConfig:      | offlineManager:didResumeDownloadWithProgress: | Downloading
 *  Suspended       | cancelDownloadForSourceConfig:      | -                                             | Canceling
 *  Canceling       | -                                   | offlineManagerDidCancelDownload:              | NotDownloaded
 *  Downloaded      | renewOfflineLicenseForSourceConfig: | offlineManagerDidRenewOfflineLicense:         | Downloaded
 *
 */
NS_SWIFT_NAME(OfflineManager)
@interface BMPOfflineManager : NSObject
/**
 * Value in megabytes for minimum system free space available before suspending active downloads.
 * Default value is 500Mb.
 */
@property (class, nonatomic) NSUInteger minimumAvailableSpaceThreshold;
/**
 * Indicates if the OfflineManager is initialized.
 */
@property (class, readonly) BOOL isOfflineManagerInitialized;
/**
 * Specifies if an active WiFi connection is required for downloading media for offline playback.
 * Default is `NO`.
 */
@property (nonatomic, assign) BOOL restrictMediaDownloadsToWiFi;

/**
 Indicates if the `OfflineManager` has finished restoring suspended downloads.
 @warning Any `resume` or `cancel` actions triggered before this returns `true` are not guaranteed and might result in unexpected behaviour.
 */
@property (nonatomic, readonly) BOOL areSuspendedDownloadsRestored;

/**
 The delegate for the `OfflineManager`
 */
@property (nonatomic, weak) id<BMPOfflineManagerDelegate> delegate;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
/**
 * @return The singleton instance of the BMPOfflineManager.
 */
+ (instancetype)sharedInstance __TVOS_PROHIBITED;
/**
 * Has to be called in your AppDelegate's `application(application:didFinishLaunchingWithOptions:)` method to initialize
 * handling of offline content.
 *
 * If the shared instance is already initialized, this method will not have any effect.
 */
+ (void)initializeOfflineManager __TVOS_PROHIBITED;
/**
 * Has to be called in your AppDelegate's `application(application:didFinishLaunchingWithOptions:)` method to initialize
 * handling of offline content.
 *
 * Initializes the shared instance with a given `OfflineConfig`.
 * If the shared instance is already initialized, this method will not have any effect.
 *
 * @param offlineConfig The `OfflineConfig`
 */
+ (void)initializeOfflineManagerWithOfflineConfig:(BMPOfflineConfig *)offlineConfig NS_SWIFT_NAME(initializeOfflineManager(offlineConfig:)) __TVOS_PROHIBITED;
/**
 * Returns an `OfflineContentManager` instance which can be used to manage offline content and offline
 * DRM related tasks for the provided `SourceConfig`.
 *
 * The instance returned by this method will always be the same for the same `SourceConfig`.
 *
 * This method will throw an error (or return `nil` in ObjC) in case a `SourceConfig` is passed that is not supported for being downloaded.
 * A `SourceConfig` is only valid for download when it's configured using an HLS asset.
 *
 * @param sourceConfig A `SourceConfig` for which the `OfflineContentManger` is requested.
 * @return `OfflineContentManager` instance for the provided `SourceConfig`
 * @throws an error if the provided `SourceConfig` is not supported.
 */
- (nullable id<BMPOfflineContentManager>)offlineContentManagerForSourceConfig:(BMPSourceConfig *)sourceConfig
                                                                        error:(NSError **)error;
/**
 * Returns an `OfflineContentManager` instance which can be used to manage offline content and offline
 * DRM related tasks for the provided `SourceConfig`.
 *
 * The provided `identifier` will be used to create a folder containing needed resources for the offline content.
 *
 * The instance returned by this method will always be the same for the same `identifier`.
 *
 * This method will throw an error (or return `nil` in ObjC) in case a `SourceConfig` is passed that is not supported for being downloaded.
 * A `SourceConfig` is only valid for download when it's configured using an HLS asset.
 *
 * @warning If an `OfflineContentManager` is acquired using this method, subsequent calls to
 * any content related API on the `OfflineManager` are not supported, meaning
 * they could result in unexpected behaviour.
 * @param sourceConfig A `SourceConfig` for which the `OfflineContentManger` is requested.
 * @param identifier A unique identifier for the given `SourceConfig` which must not change once provided.
 * @return `OfflineContentManager` instance for the provided `SourceConfig`
 * @throws an error if the provided `SourceConfig` is not supported. 
 */
- (nullable id<BMPOfflineContentManager>)offlineContentManagerForSourceConfig:(BMPSourceConfig *)sourceConfig
                                                                   identifier:(NSString *)identifier
                                                                        error:(NSError **)error NS_SWIFT_NAME(offlineContentManager(for:id:));
/**
 * Returns the offline state for the given BMPSourceConfig.
 *
 * @param sourceConfig A BMPSourceConfig instance for which the offline state should be determined.
 * @return The offline state for the given BMPSourceConfig.
 */
- (BMPOfflineState)offlineStateForSourceConfig:(BMPSourceConfig *)sourceConfig NS_SWIFT_NAME(offlineState(for:)) __deprecated_msg("Use OfflineContentManager.offlineState instead");
/**
 * Deletes the offline stored media data associated with the given BMPSourceConfig. Calling this method is only valid when
 * offlineStateForSourceConfig: for the same BMPSourceConfig instance returns BMPOfflineStateDownloaded.
 *
 * @param sourceConfig A BMPSourceConfig instance for which the offline data should be deleted.
 */
- (void)deleteOfflineDataForSourceConfig:(BMPSourceConfig *)sourceConfig __deprecated_msg("Use OfflineContentManager.deleteOfflineData() instead");
/**
 * Fetches which tracks are available for download.
 * When finished, BMPOfflineManagerListener's didFetchAvailableTracks:: method is called.
 *
 * @param sourceConfig A BMPSourceConfig instance for which the available tracks should be fetched.
 */
- (void)fetchAvailableTracksForSourceConfig:(BMPSourceConfig *)sourceConfig __deprecated_msg("Use OfflineContentManager.fetchAvailableTracks() instead");
/**
 * Downloads the media data associated with the given BMPSourceConfig. The highest media bitrate will be selected for
 * download by default. If you want to specify which bitrate should be selected for download, use
 * downloadSourceConfig:minimumBitrate:.
 *
 * Calling this method is only valid when offlineStateForSourceConfig: for the same BMPSourceConfig instance returns
 * BMPOfflineStateNotDownloaded.
 *
 * @param sourceConfig A BMPSourceConfig instance for which the media data should be downloaded.
 */
- (void)downloadSourceConfig:(BMPSourceConfig *)sourceConfig NS_SWIFT_NAME(download(sourceConfig:)) __deprecated_msg("Use OfflineContentManager.download() instead");
/**
 * Downloads the media data associated with the given BMPSourceConfig. Calling this method is only valid when
 * offlineStateForSourceConfig: for the same BMPSourceConfig instance returns BMPOfflineStateNotDownloaded.
 *
 * @param sourceConfig A BMPSourceConfig instance for which the media data should be downloaded.
 * @param downloadConfig The BMPDownloadConfig used for this download
 */
- (void)downloadSourceConfig:(BMPSourceConfig *)sourceConfig downloadConfig:(BMPDownloadConfig *)downloadConfig NS_SWIFT_NAME(download(sourceConfig:downloadConfig:)) __deprecated_msg("Use OfflineContentManager.download(downloadConfig:) instead");
/**
 * Downloads the media data associated with the given BMPSourceConfig depending on the given BMPOfflineTrackSelection.
 * Calling this method is only valid when offlineStateForSourceConfig: for the same BMPSourceConfig instance returns BMPOfflineStateNotDownloaded.
 *
 * @param sourceConfig A BMPSourceConfig instance for which the media data should be downloaded.
 * @param tracks a BMPOfflineTrackSelection specifying which tracks to download
 * @param downloadConfig The BMPDownloadConfig used for this download
 */
- (void)downloadSourceConfig:(BMPSourceConfig *)sourceConfig
                      tracks:(BMPOfflineTrackSelection *)tracks
              downloadConfig:(BMPDownloadConfig *)downloadConfig NS_SWIFT_NAME(download(sourceConfig:tracks:downloadConfig:)) __deprecated_msg("Use OfflineContentManager.download(tracks:downloadConfig:) instead");
/**
 * Cancels all running download tasks associated with the given BMPSourceConfig and deletes the partially downloaded
 * content from disk. Calling this method is only valid when offlineStateForSourceConfig: for the same BMPSourceConfig
 * instance returns BMPOfflineStateDownloading or BMPOfflineStateSuspended.
 *
 * @param sourceConfig A BMPSourceConfig instance for which all associated running download tasks should be cancelled.
 */
- (void)cancelDownloadForSourceConfig:(BMPSourceConfig *)sourceConfig NS_SWIFT_NAME(cancelDownload(for:)) __deprecated_msg("Use OfflineContentManager.cancelDownload() instead");
/**
 * Suspends all running download tasks associated with the given BMPSourceConfig. Calling this method is only valid when
 * offlineStateForSourceConfig: for the same BMPSourceConfig instance returns BMPOfflineStateDownloading. The download can
 * be resumed by calling resumeDownloadForSourceConfig:. Not data is deleted when calling this method.
 *
 * @param sourceConfig A BMPSourceConfig instance for which all associated running download tasks should be suspended.
 */
- (void)suspendDownloadForSourceConfig:(BMPSourceConfig *)sourceConfig NS_SWIFT_NAME(suspendDownload(for:)) __deprecated_msg("Use OfflineContentManager.suspendDownload() instead");
/**
 * Resumes all suspended download tasks associated with the given BMPSourceConfig. Calling this method is only valid when
 * offlineStateForSourceConfig: for the same BMPSourceConfig instance returns BMPOfflineStateSuspended.
 *
 * @param sourceConfig A BMPSourceConfig instance for which all associated suspended download tasks should be resumed.
 */
- (void)resumeDownloadForSourceConfig:(BMPSourceConfig *)sourceConfig NS_SWIFT_NAME(resumeDownload(for:)) __deprecated_msg("Use OfflineContentManager.resumeDownload() instead");
/**
 * Updates the stored DRM license information (e.g. expiration dates) by querying the KSM. The device needs to be online for this.
 * The FairPlayConfig#prepareOfflineDrmLicenseInformation block is called after the KSM was queried successfully.
 */
- (void)syncOfflineDrmLicenseInformationForSourceConfig:(BMPSourceConfig *)sourceConfig NS_SWIFT_NAME(syncOfflineDrmLicenseInformation(for:)) __deprecated_msg("Use OfflineContentManager.syncOfflineDrmLicenseInformation() instead");
/**
 * Returns information about the offline DRM license for a given SourceConfig, e.g. the remaining license duration.
 * The device does not need to be online for this.
 *
 * @param sourceConfig A BMPSourceConfig instance for which the DRM license information should be returned.
 */
- (nullable BMPDrmLicenseInformation *)offlineDrmLicenseInformationForSourceConfig:(BMPSourceConfig *)sourceConfig NS_SWIFT_NAME(offlineDrmLicenseInformation(for:)) __deprecated_msg("Use OfflineContentManager.offlineDrmLicenseInformation instead");
/**
 * Renews the already downloaded DRM license for a given SourceConfig.
 * When successfully finished, BMPOfflineManagerListener's offlineManagerDidRenewOfflineLicense: method is called.
 * In case the license renewal fails an according error is passed via the listener's offlineManager:didFailWithError: method.
 *
 * NOTE: The EXT-X-SESSION-KEY has to be present in the master playlist for this to work properly.
 *
 * @param sourceConfig A BMPSourceConfig instance for which the DRM license should be renewed.
 */
- (void)renewOfflineLicenseForSourceConfig:(BMPSourceConfig *)sourceConfig NS_SWIFT_NAME(renewOfflineLicense(for:)) __deprecated_msg("Use OfflineContentManager.renewOfflineLicense() instead");
/**
 * Creates and returns a BMPOfflineSourceConfig which should be used with a BMPPlayer instance when playback of
 * offline content is desired.
 *
 * Note: When intending to create an OfflineSourceConfig for DRM protected content,
 * the according DrmConfig needs to be applied to the passed sourceConfig before creating the OfflineSourceConfig.
 *
 * @param sourceConfig A BMPSourceConfig instance for which a new BMPOfflineSourceConfig instance should be created
 * @param restrictedToAssetCache Whether or not the player should restrict playback only to audio, video and subtitle tracks
 *      which are stored offline on the device. This has to be set to YES if the device has no network access.
 * @return A BMPOfflineSourceConfig which can be used with a BMPPlayer instance for offline playback.
 */
- (nullable BMPOfflineSourceConfig *)createOfflineSourceConfigForSourceConfig:(BMPSourceConfig *)sourceConfig restrictedToAssetCache:(BOOL)restrictedToAssetCache NS_SWIFT_NAME(createOfflineSourceConfig(for:restrictedToAssetCache:)) __deprecated_msg("Use OfflineContentManager.createOfflineSourceConfig() instead");
/**
 * Adds a listener to the BMPOfflineManager.
 *
 * @param listener The listener to add.
 * @param sourceConfig The BMPSourceConfig instance for which the listener should be added.
 */
- (void)addListener:(id<BMPOfflineManagerListener>)listener forSourceConfig:(BMPSourceConfig *)sourceConfig NS_SWIFT_NAME(add(listener:for:)) __deprecated_msg("Use OfflineContentManager.add(listener:) instead");
/**
 * Removes a listener from the BMPOfflineManager.
 *
 * @param listener The listener to remove.
 * @param sourceConfig The BMPSourceConfig instance for which the listener should be removed.
 */
- (void)removeListener:(id<BMPOfflineManagerListener>)listener forSourceConfig:(BMPSourceConfig *)sourceConfig NS_SWIFT_NAME(remove(listener:for:)) __deprecated_msg("Use OfflineContentManager.remove(listener:) instead");
/**
 * Should be called from your AppDelegate when application(application:handleEventsForBackgroundURLSession:completionHandler:)
 * is called by the system.
 *
 * @param completionHandler The completion handler which is provided by the system.
 * @param identifier The identifier which is provided by the system.
 */
- (void)addCompletionHandler:(void (^)(void))completionHandler forIdentifier:(NSString *)identifier NS_SWIFT_NAME(add(completionHandler:for:));
/**
 * Can be used to determine if the BMPSourceConfig is playable without a network connection.
 * @param sourceConfig A BMPSourceConfig instance for which the state should be determined.
 * @return YES, if the BMPSourceConfig instance is playable without a network connection, NO otherwise.
 */
- (BOOL)isSourceConfigPlayableOffline:(BMPSourceConfig *)sourceConfig NS_SWIFT_NAME(isPlayableOffline(sourceConfig:)) __deprecated_msg("Use OfflineContentManager.offlineState == .downloaded instead");
/**
 * Returns how many bytes of storage are used by the offline content.
 *
 * This can be used to get the current storage for in-progress downloads.
 *
 * @param sourceConfig A BMPSourceConfig instance for which the storage size in bytes should be calculated.
 * @return How many bytes of storage are used by the offline content.
 */
- (long)usedStorageForSourceConfig:(BMPSourceConfig *)sourceConfig NS_SWIFT_NAME(usedStorage(for:)) __deprecated_msg("Use OfflineContentManager.usedStorage instead");
@end

NS_ASSUME_NONNULL_END
