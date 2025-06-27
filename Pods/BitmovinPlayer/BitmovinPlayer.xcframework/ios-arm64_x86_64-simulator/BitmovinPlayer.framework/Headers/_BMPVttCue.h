//
// Bitmovin Player iOS SDK
// Copyright (C) 2018, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Represents a base VTT cue.
 */
NS_SWIFT_NAME(_VttCue)
@interface _BMPVttCue : NSObject
/** The Index of the cue*/
@property (nonatomic, readonly) NSUInteger index;
/** The start time of the cue */
@property (nonatomic, readonly) NSTimeInterval start;
/** The end time of the cue */
@property (nonatomic, readonly) NSTimeInterval end;
/** The text of the cue */
@property (nonatomic, readonly, copy) NSString *text;
/** The settings - e.g. positioning information - of the cue. */
@property (nonatomic, readonly, copy, nullable) NSString *settings;

/// :nodoc:
- (instancetype)initWithIndex:(NSUInteger)index
                        start:(NSTimeInterval)start
                          end:(NSTimeInterval)end
                         text:(NSString *)text
                     settings:(nullable NSString *)settings;

@end

NS_ASSUME_NONNULL_END
