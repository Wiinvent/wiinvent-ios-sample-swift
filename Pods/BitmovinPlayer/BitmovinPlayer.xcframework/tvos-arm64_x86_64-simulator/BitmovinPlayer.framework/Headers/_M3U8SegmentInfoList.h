//
//  _M3U8SegmentInfoList.h
//  M3U8Kit
//
//  Created by Oneday on 13-1-11.
//  Copyright (c) 2013年 0day. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "_M3U8SegmentInfo.h"

@interface _M3U8SegmentInfoList : NSObject

@property (nonatomic, assign ,readonly) NSUInteger count;

// BITMOVIN CHANGES START
@property (nonatomic, strong, readonly) NSArray<_M3U8SegmentInfo *> *segments;
// BITMOVIN CHANGES END

- (void)addSegementInfo:(_M3U8SegmentInfo *)segment;
- (_M3U8SegmentInfo *)segmentInfoAtIndex:(NSUInteger)index;

@end
