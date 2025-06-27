//
// Bitmovin Player iOS SDK
// Copyright (C) 2020, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol BMPSource;

NS_SWIFT_NAME(_PlaylistApiDelegate)
@protocol _BMPPlaylistApiDelegate <NSObject>
@property (nonatomic, readonly) NSArray<id<BMPSource>> *playlistApi_sources;
- (void)playlistApi_seek:(id<BMPSource>)source time:(NSTimeInterval)time;
- (void)playlistApi_addSource:(id<BMPSource>)source atIndex:(NSInteger)index NS_SWIFT_NAME(playlistApi_add(source:at:));
- (void)playlistApi_addSource:(id<BMPSource>)source NS_SWIFT_NAME(playlistApi_add(source:));
- (void)playlistApi_removeSourceAtIndex:(NSInteger)index NS_SWIFT_NAME(playlistApi_remove(sourceAt:));
@end

NS_ASSUME_NONNULL_END
