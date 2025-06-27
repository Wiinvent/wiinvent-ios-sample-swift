//
// Bitmovin Player iOS SDK
// Copyright (C) 2018, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import "_BMPVttCue.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(_VTTParser)
@interface _BMPVTTParser : NSObject
/**
 Parses the cues of a provided VTT file.

 @param string The string representation of the desired VTT file.
 @param error An NSError pointer which will be set if an error occurs while parsing.
 @return An array of _BMPVttCues parsed from the input string or nil if an error occurred.
 */
+ (nullable NSArray<_BMPVttCue *> *)parseVttCuesFromString:(NSString *)string error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
