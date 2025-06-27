//
// Bitmovin Player iOS SDK
// Copyright (C) 2020, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(_WeakObjectsStore)
@interface _BMPWeakObjectsStore<ObjectType> : NSObject
@property (readonly, nonatomic, assign) BOOL isEmpty;
/// Adds the passed object by holding a weak reference to that object.
/// If the object is already added it will not be added a second time.
- (void)addObject:(ObjectType)object;
- (void)removeObject:(ObjectType)object;
- (BOOL)containsObject:(ObjectType)object;
- (void)forEach:(void (NS_NOESCAPE ^)(ObjectType))block;
@end

NS_ASSUME_NONNULL_END
