//
// Bitmovin Player iOS SDK
// Copyright (C) 2022, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
@protocol BMPSource;

NS_ASSUME_NONNULL_BEGIN

/// :nodoc:
NS_SWIFT_NAME(_CastPlaylistQueueManipulator)
@protocol _BMPCastPlaylistQueueManipulator <NSObject>
- (void)addSource:(id<BMPSource>)source atIndex:(NSInteger)index NS_SWIFT_NAME(addSource(_:at:));
- (void)removeSourceAtIndex:(NSInteger)index NS_SWIFT_NAME(removeSource(at:));
@end

NS_ASSUME_NONNULL_END
