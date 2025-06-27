//
// Bitmovin Player iOS SDK
// Copyright (C) 2019, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface _M3U8ScteTagInfo : NSObject

@property (readonly, nonatomic) NSDictionary *contents;
@property (readonly, nonatomic) NSString *rawString;
@property (readonly, nonatomic) NSInteger sequenceNumber;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)initWithDictionary:(NSDictionary *)dictionary
                         rawString:(NSString *)rawString
                     mediaSequence:(NSInteger)mediaSequence NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
