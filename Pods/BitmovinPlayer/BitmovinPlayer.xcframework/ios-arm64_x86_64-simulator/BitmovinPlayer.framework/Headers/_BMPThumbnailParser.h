//
// Bitmovin Player iOS SDK
// Copyright (C) 2018, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import <BitmovinPlayer/BMPThumbnail.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(_ThumbnailParser)
@interface _BMPThumbnailParser : NSObject
/**
 Parses the content of a provided VTT file containing thumbnails.

 @param vttString The string representation of the desired VTT file.
 @param baseUrl The base URL of the VTT file.
 @param error An NSError pointer which will be set if an error occurs while parsing.
 @return An array of BMPThumbails parsed from the input string or nil if an error occurred.
 */
- (nullable NSArray<BMPThumbnail *> *)parseThumbnails:(NSString *)vttString baseUrl:(NSURL *)baseUrl error:(NSError **)error;
/**
 Creates a WebVTT string from an array of thumbnails.

 @param thumbnails The thumbnails which should be represented by the resulting WebVTT string.
 @return A NSString representing a the given thumbnails as WebVTT content.
 */
- (nullable NSString *)createVttStringFromThumbnails:(NSArray<BMPThumbnail *> *)thumbnails;
@end

NS_ASSUME_NONNULL_END
