//
// Bitmovin Player iOS SDK
// Copyright (C) 2020, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/// :nodoc:
@interface UIView (BMPParentViewController)
- (nullable UIViewController *)_bmp_findResponsibleViewController;
@end

NS_ASSUME_NONNULL_END
