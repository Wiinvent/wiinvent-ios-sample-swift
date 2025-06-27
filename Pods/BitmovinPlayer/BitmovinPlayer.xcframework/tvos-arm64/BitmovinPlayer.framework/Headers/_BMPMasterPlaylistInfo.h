//
// Bitmovin Player iOS SDK
// Copyright (C) 2019, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import <BitmovinPlayer/_M3U8MasterPlaylist.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Currently this is just a wrapper around the M3U8Playlist object of our parsing framework
 */
NS_SWIFT_NAME(_MasterPlaylistInfo)
@interface _BMPMasterPlaylistInfo : NSObject
/**
 Holds all media playlist urls

 @Note urls from EXT-X-I-FRAME-STREAM-INF are not included.
 They are unmodified and exactly as they are in the manifest
 */
@property (readonly) NSArray<NSURL *> *rawMediaPlaylistUrls;
@property (readonly) NSArray<NSURL *> *absoluteMediaPlaylistUrls;
/**
 Holds all EXT-X-I-FRAME-STREAM-INF urls

 @Note They are unmodified and exactly as they are in the manifest
 */
@property (readonly) NSArray<NSURL *> *rawIFramePlaylistUrls;
- (instancetype)initWithM3U8MasterPlaylist:(_M3U8MasterPlaylist *)m3u8MasterPlaylist;
@end

NS_ASSUME_NONNULL_END
