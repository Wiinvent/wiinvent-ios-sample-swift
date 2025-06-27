//
// Bitmovin Player iOS SDK
// Copyright (C) 2019, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import "_BMPMasterPlaylistInfo.h"
#import "_BMPVariantPlaylistInfo.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(_PlaylistParser)
@interface _BMPPlaylistParser : NSObject

+ (BOOL)isMasterPlaylist:(nullable NSString *)playlist;
+ (BOOL)isMediaPlaylist:(nullable NSString *)playlist;
+ (BOOL)isPlaylistTypeTagPresentInVariantPlaylistData:(NSData *)variantPlaylistData;
+ (BOOL)isPlaylistTypeTagPresentInVariantPlaylistString:(NSString *)variantPlaylistString;
+ (_BMPVariantPlaylistInfo *)playlistInfoOfVariantPlaylist:(NSData *)variantPlaylistData fromUrl:(NSURL *)url;
+ (nullable _BMPMasterPlaylistInfo *)playlistInfoOfMasterPlaylist:(NSData *)masterPlaylistData fromUrl:(NSURL *)url;
+ (NSArray<NSString *> *)extractKeyUrlsFromVariantPlaylist:(NSString *)variantPlaylist;
+ (NSArray<NSString *> *)extractKeyUrlsFromVariantPlaylist:(NSString *)variantPlaylist
                                           excludedSchemes:(NSArray<NSString *> *)excludedSchemes;
+ (NSArray<NSString *> *)extractKeyUrlsFromVariantPlaylist:(NSString *)variantPlaylist
                                           includedSchemes:(NSArray<NSString *> *)includedSchemes;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
