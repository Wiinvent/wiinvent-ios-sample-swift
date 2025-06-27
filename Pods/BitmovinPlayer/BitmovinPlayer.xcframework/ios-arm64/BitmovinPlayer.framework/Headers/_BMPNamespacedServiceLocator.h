//
// Bitmovin Player iOS SDK
// Copyright (C) 2020, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import "_BMPPlaybackService.h"
#import "_BMPCastMessagingService.h"

@protocol _BMPLogger;
@protocol _BMPPlayerEventEmitter;
@protocol _BMPResourceLoaderService;
@protocol _BMPDeficiencyService;
@protocol _BMPConfigService;
@protocol _BMPPlaylistService;
@protocol _BMPBufferService;
@protocol _BMPSeekingService;
@protocol _BMPStallingService;
@protocol _BMPCurrentSourceProvider;
@protocol _BMPPlaylistSourcesProvider;
@protocol _BMPTimeService;
@protocol _BMPAdvertisingService;
@protocol _BMPInitializationService;
@protocol _BMPCaptionService;
@protocol _BMPAudioService;
@protocol _BMPPlaybackFinishedService;

NS_ASSUME_NONNULL_BEGIN

/// :nodoc:
NS_SWIFT_NAME(_NamespacedServiceLocator)
@protocol _BMPNamespacedServiceLocator <NSObject>
@property (nonatomic, strong, readonly) id<_BMPPlayerEventEmitter> eventEmitter;
@property (nonatomic, strong, readonly) id<_BMPDeficiencyService> deficiencyService;
@property (nonatomic, strong, readonly) id<_BMPConfigService> configService;
@property (nonatomic, strong, readonly) id<_BMPLogger> logger;
@property (nonatomic, strong, readonly) id<_BMPTimeService> timeService;
@property (nonatomic, strong, readonly) id<_BMPBufferService> bufferService;
@property (nonatomic, strong, readonly) id<_BMPPlaybackService> playbackService;
@property (nonatomic, strong, readonly) id<_BMPStallingService> stallingService;
@property (nonatomic, strong, readonly) id<_BMPSeekingService> seekingService;
@property (nullable, nonatomic, strong, readonly) id<_BMPAdvertisingService> advertisingService;
@property (nonatomic, strong, readonly) id<_BMPInitializationService> initializationService;
@property (nonatomic, strong, readonly) id<
    _BMPPlaylistService,
    _BMPCurrentSourceProvider,
    _BMPPlaylistSourcesProvider
> playlistService;
@property (nonatomic, strong, readonly) id<_BMPPlaybackFinishedService> playbackFinishedService;
@property (nonatomic, strong, readonly) id<_BMPCastMessagingService> castMessagingService;
@property (nonatomic, strong, readonly) id<_BMPCaptionService> captionService;
@property (nonatomic, strong, readonly) id<_BMPAudioService> audioService;

- (void)addService:(id<_BMPService>)service;
- (void)removeService:(_BMPServiceType)serviceType;
- (void)removeServices:(NSArray<NSNumber *> *)services;
@end

NS_ASSUME_NONNULL_END
