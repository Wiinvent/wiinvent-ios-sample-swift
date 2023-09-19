//
//  Tv360SkipAdsButton.swift
//  wiinvent-ios-sample-swift
//
//  Created by Nam Co on 2023-08-12.
//  Copyright © 2023 wiinvent. All rights reserved.
//

import Foundation
import WISDK
import UIKit

public class Tv360SkipAdsButton: WiAdsSkipButton {
    
    override init(frame: CGRect) {
        super.init(frame: frame)
    }
    
    override public func normalUi() {
        super.normalUi()
        setTitleColor(.white, for: .normal)
        titleLabel?.font = UIFont.boldSystemFont(ofSize: 18)
        backgroundColor      = UIColor.black.withAlphaComponent(0.4)
        layer.cornerRadius   = 4
        layer.borderWidth = 1
        layer.borderColor = UIColor.white.cgColor
        contentEdgeInsets = UIEdgeInsets(top: 10.0, left: 20.0, bottom: 10.0, right: 20.0)
    }
    
    override public func skipUi() {
        super.skipUi()
        setTitle("Bỏ qua quảng cáo", for: .normal)
    }
    
    required public init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
}
