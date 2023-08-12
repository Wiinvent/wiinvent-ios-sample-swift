//
//  Tv360SkipAdsButton.swift
//  wiinvent-ios-sample-swift
//
//  Created by Nam Co on 2023-08-12.
//  Copyright © 2023 wiinvent. All rights reserved.
//

import Foundation
import WISDK

public class Tv360SkipAdsButton: WiAdsSkipButton {
    
    override init(frame: CGRect) {
        super.init(frame: frame)
    }
    
    override public func normalUi() {
        super.normalUi()
    }
    
    override public func skipUi() {
        super.skipUi()
    }
    
    required public init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
}
