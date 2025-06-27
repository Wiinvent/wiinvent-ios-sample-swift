//
// Bitmovin Player iOS SDK
// Copyright (C) 2021, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <AVFoundation/AVFoundation.h>
#import <AVKit/AVKit.h>
#import <BitmovinPlayer/BMPPlayerEventHandler.h>
#import <BitmovinPlayer/BMPRemoteControlApi.h>
#import <BitmovinPlayer/BMPThumbnail.h>
#import <BitmovinPlayer/BMPBufferApi.h>
#import <BitmovinPlayer/BMPTimeMode.h>

@protocol BMPPlaylistApi;
@protocol BMPSource;
@class BMPSharePlayApi;
@class BMPPlayerConfig;
@class BMPSourceConfig;
@class BMPPlaylistConfig;
@class BMPSubtitleTrack;
@class BMPAudioTrack;
@class BMPVideoQuality;
@class BMPAdItem;

NS_ASSUME_NONNULL_BEGIN

/**
 * Loads, controls and renders audio and video content represented through `Source`s. A player instance can be created
 * via the `PlayerFactory.create` function and will idle until one or more `Source`s are loaded. Once load is called,
 * the player becomes active and initiates necessary downloads to start playback of the loaded source(s).
 *
 * In case multiple sources were loaded into the player, `Source.isActive` identifies which source is currently active
 * in the player (i.e. being played back). Only one source can be active at any time and API calls on the player will
 * act on that source. More information on how to manage multiple sources can be found on the `PlaylistApi`.
 *
 * The player emits events during a player session. See `PlayerEventHandler` on how to subscribe to events. `Event`s are divided
 * into `PlayerEvent` and `SourceEvent`, depending on if they are specific to a player session or a source. While
 * `SourceEvent`s are naturally emitted from a source, they are also emitted from the player for the active source. This
 * allows for all event handling to be done through the player in case only a single source is loaded, enabling the same
 * workflows as on v2 of the Bitmovin Player SDK, where it was not possible to load multiple sources and where each
 * event was a `PlayerEvent`.
 *
 * The player implements the `RemoteControlApi`, which offers the ability to connect to a cast-compatible device,
 * allowing remote playback of the loaded sources.
 *
 * By default, a player instance does not provide any UI components. To use the default Bitmovin Player Web UI, a player
 * instance can be attached to a `PlayerView`. The `PlayerView` already comes with a Layer to render video into,
 * the Bitmovin Player Web UI and handling for standard UI use-cases. If a custom UI is
 * preferred, an `AVPlayerLayer` or an `AVPlayerViewController` can be registered via
 * `registerPlayerLayer` / `registerPlayerViewController`. See `PlayerView` for more details.
 */
NS_SWIFT_NAME(Player)
@protocol BMPPlayer <NSObject, BMPPlayerEventHandler, BMPRemoteControlApi>
/**
 * Flag to indicate if the player is destroyed.
 */
@property (nonatomic, readonly) BOOL isDestroyed;

/**
 * Returns `true` if the player is muted.
 */
@property (nonatomic, readonly) BOOL isMuted;

/**
 * Get/set the player’s volume between 0 (silent) and 100 (max volume). This property is used to control the player audio
 * volume relative to the system volume.
 */
@property (nonatomic) NSInteger volume;

/**
 * Returns `true` if the player has started playback but is currently paused.
 */
@property (nonatomic, readonly) BOOL isPaused;

/**
 * Returns `true` if the player is currently playing, i.e. has started and is not paused.
 */
@property (nonatomic, readonly) BOOL isPlaying;

/**
 * Returns `true` if the displayed video is a live stream.
 */
@property (nonatomic, readonly) BOOL isLive;

/**
 * Returns the total duration in seconds of the current video or INFINITY if it’s a live stream.
 */
@property (nonatomic, readonly) NSTimeInterval duration;

/**
 * Returns the current playback time in seconds.
 * For VoD streams the returned time ranges between 0 and the duration of the asset.
 * For live streams a Unix timestamp denoting the current playback position is returned.
 */
@property (nonatomic, readonly) NSTimeInterval currentTime;

/**
 * Returns the current player config object of this player instance.
 */
@property (nonatomic, nonnull, readonly) BMPPlayerConfig *config;

/**
 * Returns the currently active source or null if no source is active.
 */
@property (nonatomic, nullable, readonly) id<BMPSource> source;

/**
 * Returns the limit in seconds for time shift. Is either negative or 0. Is applicable for live streams only.
 */
@property (nonatomic, readonly) NSTimeInterval maxTimeShift;

/**
 * When set, shifts the time to the given offset in seconds from the live edge. Has to be within `Player#maxTimeShift`
 * (which is a negative value) and 0. Only works in live streams. The offset can be positive and is then interpreted as
 * a UNIX timestamp in seconds. The value has to be within the timeShift window, as specified by `Player#maxTimeShift`.
 */
@property (nonatomic) NSTimeInterval timeShift;

/**
 * Returns an array containing `SubtitleTrack` objects for all available subtitle tracks.
 */
@property (nonatomic, readonly) NSArray<BMPSubtitleTrack *> *availableSubtitles;

/**
 * Returns the currently used `SubtitleTrack`.
 */
@property (nonatomic, readonly) BMPSubtitleTrack *subtitle;

/**
 * Returns an array containing all available audio tracks.
 */
@property (nonatomic, readonly) NSArray<BMPAudioTrack *> *availableAudio;

/**
 * Returns the currently used audio track.
 *
 * @Note:
 * Before the `Source` finished loading (`SourceLoadedEvent`) this method will always return `nil`.
 */
@property (nonatomic, readonly, nullable) BMPAudioTrack *audio;

/**
 * Returns `true` while an ad is played back or content playback has been paused for ad playback, `false` otherwise.
 */
@property (nonatomic, readonly) BOOL isAd;

/**
 * Returns `true` when media is played externally using AirPlay.
 */
@property (nonatomic, readonly) BOOL isAirPlayActive;

/**
 * Returns `true` when AirPlay is available.
 */
@property (nonatomic, readonly) BOOL isAirPlayAvailable;

/**
 * Indicates whether visual output is obscured by the `Player` due to insufficient external protection for
 * the active `Source`.
 *
 * A `Source` that incorporates copy protection or other forms of security may have its visual content obscured if
 * the current device configuration does not meet the requirements for protecting the `Source`. Current device
 * configuration includes connection to an external display with a High-Definition Multimedia Interface (HDMI) cable.
 * The `Source` may not support playback on an external display, or the HDMI cable may provide insufficient protection
 * due to a lower High-bandwidth Digital Content Protection (HDCP) version.
 *
 * Note that the external protection requirements of the active `Source` determines the value of this property.
 * These requirements are ingrained in the content itself, and cannot be externally specified.
 * If the active `Source` does not require external protection or if the device configuration sufficiently protects
 * the active `Source`, the value of this property will be `false`.
 */
@property (nonatomic, readonly) BOOL isOutputObscured;

/**
 * Returns an array containing all available video qualities the player can adapt between.
 *
 * @return An array containing all available video qualities the player can adapt between.
 */
@property (nonatomic, readonly) NSArray<BMPVideoQuality *> *availableVideoQualities;

/**
 * Returns the currently selected video quality.
 *
 * @return The currently selected video quality.
 */
@property (nonatomic, readonly, nullable) BMPVideoQuality *videoQuality;

/**
 * Get/set the playback speed of the player. Fast forward, slow motion and reverse playback are supported.
 * @note Slow motion is used by values between 0 and 1, fast forward by values greater than 2, slow reverse
 *       is used by values between 0 and -1, and fast reverse is used by values less than -1.
 * @note Negative values are ignored during Casting.
 * @note During reverse playback the playback will continue until the beginning of the active source is reached.
 *       When reaching the beginning of the source, playback will be paused and the playback speed will be
 *       reset to its default value of 1. No `PlaybackFinishedEvent` will be emitted in this case.
 */
@property (nonatomic) float playbackSpeed;

/**
 * The upper bitrate boundary in bits per second for network bandwidth consumption of the currently played source. Can
 * be set to 0 for no limitation. The value set here is only valid for the currently played source and will not be
 * carried over to subsequently loaded sources. Use BMPAdaptationConfig#maxSelectableBitrate to set a value which
 * is persistent for all loaded sources of one BitmovinPlayer instance.
 *
 * Default value is 0.
 */
@property (nonatomic) NSUInteger maxSelectableBitrate;

/**
 * Returns the currently playing video frame rate in units of frames per second.
 */
@property (nonatomic, readonly) float currentVideoFrameRate;

/**
 * The `BufferApi` for interactions regarding the buffer.
 */
@property (nonatomic, readonly) id<BMPBufferApi> buffer API_AVAILABLE(ios(10.0), tvos(10.0));

/**
 * The `PlaylistApi` for interactions regarding the playlist.
 */
@property (nonatomic, readonly) id<BMPPlaylistApi> playlist;

/**
 * The `SharePlayApi` for interactions regarding Apple SharePlay. This API is only available for usage from Swift
 */
@property (nonatomic, readonly) BMPSharePlayApi *sharePlay API_AVAILABLE(ios(15.0), tvos(15.0));

/**
 * Loads a new `Source` based on the provided SourceConfig into the player.
 *
 * @param sourceConfig  The source config used to set a new media source.
 */
- (void)loadSourceConfig:(BMPSourceConfig *)sourceConfig NS_SWIFT_NAME(load(sourceConfig:));

/**
 * Loads a new `Source` into the player.
 *
 * @param source The source used to set a new media source.
 */
- (void)loadSource:(id<BMPSource>)source NS_SWIFT_NAME(load(source:));

/**
 * Loads a playlist containing multiple `Source`s into the player. The first source in the `PlaylistConfig` becomes
 * active immediately.
 *
 * @param playlistConfig The playlist config used to set a queue of media sources.
 */
- (void)loadPlaylistConfig:(BMPPlaylistConfig *)playlistConfig NS_SWIFT_NAME(load(playlistConfig:));

/**
 * Unloads all `Source`s in the player.
 */
- (void)unload;

/**
 * Destroys the player and releases all allocated resources.
 *
 * The player instance must not be used after calling this method.
 */
- (void)destroy;

/**
 * Starts playback or resumes after being paused. Has no effect if the player is already playing.
 */
- (void)play;

/**
 * Pauses the video if it is playing. Has no effect if the player is already paused.
 */
- (void)pause;

/**
 * Seeks to the given playback time.
 *
 * Seeks to the given playback time specified by the parameter time in seconds. Must not be
 * greater than the total duration of the video. Has no effect when watching a live stream as
 * seeking is not possible.
 *
 * @param time The time to seek to.
 */
- (void)seek:(NSTimeInterval)time NS_SWIFT_NAME(seek(time:));

/**
 * Mutes the player if an audio track is available. Has no effect if the player is already muted.
 */
- (void)mute;

/**
 * Unmutes the player it it is already muted. Has no effect if the player is not muted.
 */
- (void)unmute;

/**
 * Adds a new external subtitle file. The BMPSubtitleTrack is only added to the available tracks, but is not set active.
 * Use BMPPlayer#subtitle: to active it. If the ID already exists, the existing BMPSubtitleTrack is overwritten with the new one.
 *
 * @param subtitleTrack The BMPSubtitleTrack to be added to the available subtitles.
 */
- (void)addSubtitle:(BMPSubtitleTrack *)subtitleTrack NS_SWIFT_NAME(addSubtitle(track:)) __deprecated_msg("Use SourceConfig#add(subtitleTrack:) instead.");

/**
 * Removes the existing BMPSubtitleTrack with the track ID specified by subtitleTrackID. If the track is currently active,
 * it will be deactivated and then removed. If no BMPSubtitleTrack with the given ID exists, the call will be ignored.
 * The BMPSubtitleTrack is removed from the available tracks, use BMPPlayer#subtitle:nil to disable an active BMPSubtitleTrack.
 *
 * @param subtitleTrackID The ID of the BMPSubtitleTrack to be removed.
 */
- (void)removeSubtitle:(NSString *)subtitleTrackID NS_SWIFT_NAME(removeSubtitle(trackIdentifier:));

/**
 * Sets the subtitle track to the ID specified by trackID. A list can be retrieved by calling BMPPlayer#availableSubtitles.
 * Using nil as ID disables subtitles.
 *
 * @param subtitleTrackID The id of the BMPSubtitleTrack which should be set.
 */
- (void)setSubtitleWithIdentifier:(nullable NSString *)subtitleTrackID NS_SWIFT_NAME(setSubtitle(trackIdentifier:));

/**
 * Sets the audio track to the ID specified by audioTrackID. A list can be retrieved by calling BMPPlayer#availableAudio.
 *
 * @param audioTrackID The ID of the BMPAudioTrack which should be set.
 *
 * @Note:
 * Before the `Source` finished loading (`SourceLoadedEvent`) calling this method will result in a no-op.
 */
- (void)setAudioWithIdentifier:(NSString *)audioTrackID NS_SWIFT_NAME(setAudio(trackIdentifier:));

/**
 Returns the thumbnail image for the active `Source` at a certain time.
 Requires a configured `ThumbnailTrack` in the corresponding `SourceConfig`.

 @note This function returns `nil`
 - If there is no active source
 - If the thumbnails were not loaded yet
 - If there are no `ThumbnailTrack` provided in the corresponding `SourceConfig`
 - If there is no thumbnail available at the provided time

 @param time The time for which the thumbnail should be returned.
 @return An instance of BMPThumbnail for the given time, or nil.
 */
- (nullable BMPThumbnail *)thumbnailForTime:(NSTimeInterval)time NS_SWIFT_NAME(thumbnail(forTime:));

/**
 * Skips the current ad. Has no effect if ad is not skippable or if no ad is played back.
 */
- (void)skipAd;

/**
 * Schedules an ad for playback.
 *
 * @param adItem the ad item to be scheduled.
 */
- (void)scheduleAd:(BMPAdItem *)adItem NS_SWIFT_NAME(scheduleAd(adItem:));

/**
 * Shows the AirPlay playback target picker.
 */
- (void)showAirPlayTargetPicker;

/**
 * Returns the current playback time in seconds.
 * For VoD streams the returned time ranges between 0 and the duration of the asset.
 * For live streams it can be specified if an absolute unix timestamp or a value relative to the playback start should be returned.
 *
 * @param timeMode to specify if an absolute unix timestamp or an relative time should be returned.
 */
- (NSTimeInterval)currentTime:(BMPTimeMode)timeMode;

/**
 * Registers the internal AVPlayer instance to an existing AVPlayerLayer. Calling this method has no effect if
 * the AVPlayer instance is already registered on the given playerLayer.
 *
 * @param playerLayer a AVPlayerLayer instance to which the internal AVPlayer instance should be assigned.
 */
- (void)registerPlayerLayer:(AVPlayerLayer *)playerLayer;

/**
 * Unregisters the internal AVPlayer instance from an existing AVPlayerLayer.
 *
 * @param playerLayer a AVPlayerLayer instance from which the internal AVPlayer instance should be unregistered.
 */
- (void)unregisterPlayerLayer:(AVPlayerLayer *)playerLayer;

/**
 * Registers the internal AVPlayer instance to an existing AVPlayerViewController. Calling this method has no
 * effect if the AVPlayer instance is already registered on the given playerViewController.
 *
 * @param playerViewController a AVPlayerViewController instance to which the internal AVPlayer instance should be assigned.
 */
- (void)registerPlayerViewController:(AVPlayerViewController *)playerViewController;

/**
 * Unregisters the internal AVPlayer instance from an existing AVPlayerViewController.
 *
 * @param playerViewController a AVPlayerViewController instance from which the internal AVPlayer instance should be unregistered.
 */
- (void)unregisterPlayerViewController:(AVPlayerViewController *)playerViewController;

/**
 * Registers the container for displaying ads.
 *
 * @param adContainer the container view which should contain the rendered ads.
 */
- (void)registerAdContainer:(UIView *)adContainer;

/**
 * Sets subtitle styles on the current AVPlayerItem.
 *
 * @param subtitleStyles The subtitle styles which should be set
 */
- (void)setSubtitleStyles:(nullable NSArray<AVTextStyleRule *> *)subtitleStyles;

/**
 * Checks the possibility to play the media at specified playback speed.
 *
 * @param playbackSpeed The playback speed to check.
 */
- (BOOL)canPlayAtPlaybackSpeed:(float)playbackSpeed;
@end

NS_ASSUME_NONNULL_END
