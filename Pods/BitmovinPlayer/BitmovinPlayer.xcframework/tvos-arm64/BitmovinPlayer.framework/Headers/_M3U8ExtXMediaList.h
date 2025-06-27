//
//  _M3U8ExtXMediaList.h
//  M3U8Kit
//
//  Created by Sun Jin on 3/25/14.
//  Copyright (c) 2014 Jin Sun. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "_M3U8ExtXMedia.h"

@interface _M3U8ExtXMediaList : NSObject

@property (nonatomic, assign ,readonly) NSUInteger count;

- (void)addExtXMedia:(_M3U8ExtXMedia *)extXMedia;
- (_M3U8ExtXMedia *)xMediaAtIndex:(NSUInteger)index;
- (_M3U8ExtXMedia *)firstExtXMedia;
- (_M3U8ExtXMedia *)lastExtXMedia;

- (_M3U8ExtXMediaList *)audioList;
- (_M3U8ExtXMedia *)suitableAudio;

- (_M3U8ExtXMediaList *)videoList;
- (_M3U8ExtXMedia *)suitableVideo;

- (_M3U8ExtXMediaList *)subtitleList;
- (_M3U8ExtXMedia *)suitableSubtitle;

// BITMOVIN CHANGES START

- (NSArray<_M3U8ExtXMedia *> *)toArray;

// BITMOVIN CHANGES END

@end
