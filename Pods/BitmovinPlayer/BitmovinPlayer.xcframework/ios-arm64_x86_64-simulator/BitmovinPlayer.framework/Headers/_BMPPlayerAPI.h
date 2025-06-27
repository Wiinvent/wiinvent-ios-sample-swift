//
// Bitmovin Player iOS SDK
// Copyright (C) 2017, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import <AVKit/AVKit.h>
#import <BitmovinPlayer/BMPThumbnail.h>
#import <BitmovinPlayer/BMPBufferApi.h>
#import <BitmovinPlayer/BMPTimeMode.h>

@protocol BMPPlaylistApi;
@protocol BMPSource;
@class BMPPlayerConfig;
@class BMPPlaylistConfig;
@class BMPSourceConfig;
@class BMPSubtitleTrack;
@class BMPAudioTrack;
@class BMPVideoQuality;
@class BMPAdItem;

NS_ASSUME_NONNULL_BEGIN

/// :nodoc:
NS_SWIFT_NAME(_PlayerAPI)
@protocol _BMPPlayerAPI <NSObject>
@property (nonatomic, readonly) BOOL isMuted;
@property (nonatomic) NSInteger volume;
@property (nonatomic, readonly) BOOL isPaused;
@property (nonatomic, readonly) BOOL isPlaying;
@property (nonatomic, readonly) BOOL isLive;
@property (nonatomic, readonly) NSTimeInterval duration;
@property (nonatomic, readonly) NSTimeInterval currentTime;
@property (nonatomic, nonnull, readonly) BMPPlayerConfig *config;
@property (nonatomic, nullable, readonly) id<BMPSource> source;
@property (nonatomic, readonly) NSTimeInterval maxTimeShift;
@property (nonatomic) NSTimeInterval timeShift;
@property (nonatomic, readonly) NSArray<BMPSubtitleTrack *> *availableSubtitles;
@property (nonatomic, readonly) BMPSubtitleTrack *subtitle;
@property (nonatomic, readonly) NSArray<BMPAudioTrack *> *availableAudio;
@property (nonatomic, readonly, nullable) BMPAudioTrack *audio;
@property (nonatomic, readonly) BOOL isAd;
@property (nonatomic, readonly) BOOL isAirPlayActive;
@property (nonatomic, readonly) BOOL isAirPlayAvailable;
@property (nonatomic, readonly) BOOL isOutputObscured;
@property (nonatomic, readonly) NSArray<BMPVideoQuality *> *availableVideoQualities;
@property (nonatomic, readonly, nullable) BMPVideoQuality *videoQuality;
@property (nonatomic) float playbackSpeed;
@property (nonatomic) NSUInteger maxSelectableBitrate;
@property (nonatomic, readonly) float currentVideoFrameRate;
@property (nonatomic, readonly) id<BMPBufferApi> buffer API_AVAILABLE(ios(10.0), tvos(10.0));
@property (nonatomic, readonly) id<BMPPlaylistApi> playlist;

- (void)loadSource:(id<BMPSource>)source NS_SWIFT_NAME(load(source:));
- (void)loadPlaylistConfig:(BMPPlaylistConfig *)playlistConfig NS_SWIFT_NAME(load(playlistConfig:));
- (void)unload;
- (void)destroy;
- (void)play;
- (void)pause;
- (void)seek:(NSTimeInterval)time NS_SWIFT_NAME(seek(time:));
- (void)mute;
- (void)unmute;
- (void)addSubtitle:(BMPSubtitleTrack *)subtitleTrack NS_SWIFT_NAME(addSubtitle(track:)) __deprecated_msg("Use SourceConfig#add(subtitleTrack:) instead.");
- (void)removeSubtitle:(NSString *)subtitleTrackID NS_SWIFT_NAME(removeSubtitle(trackIdentifier:));
- (void)setSubtitleWithIdentifier:(nullable NSString *)subtitleTrackID NS_SWIFT_NAME(setSubtitle(trackIdentifier:));
- (void)setAudioWithIdentifier:(NSString *)audioTrackID NS_SWIFT_NAME(setAudio(trackIdentifier:));
- (nullable BMPThumbnail *)thumbnailForTime:(NSTimeInterval)time NS_SWIFT_NAME(thumbnail(forTime:));
- (void)skipAd;
- (void)scheduleAd:(BMPAdItem *)adItem NS_SWIFT_NAME(scheduleAd(adItem:));
- (void)showAirPlayTargetPicker;
- (NSTimeInterval)currentTime:(BMPTimeMode)timeMode;

@end

NS_ASSUME_NONNULL_END
