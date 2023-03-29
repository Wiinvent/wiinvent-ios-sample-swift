//
//  ViewController.swift
//  wiinvent-ios-sample-swift
//
//  Created by mcg-corp on 4/29/20.
//  Copyright © 2020 wiinvent. All rights reserved.
//

import UIKit
import WISDK
import AVKit

public protocol NibInstantiatable {
    static func nibName() -> String
}

extension NibInstantiatable {
    static func nibName() -> String {
        return String(describing: self)
    }
}

extension NibInstantiatable where Self: UIView {
    static func fromNib() -> Self {
        let bundle = Bundle(for: self)
        let nib = bundle.loadNibNamed(nibName(), owner: self, options: nil)
        return nib!.first as! Self
    }
}

class ViewController: UIViewController {
    
    var instreamBtn: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        instreamBtn = UIButton(frame: CGRect(x: 100, y: 100, width: 200, height: 50))
        instreamBtn.backgroundColor = .red
        instreamBtn.setTitle("Instream Detail", for: .normal)
        instreamBtn.addTarget(self, action: #selector(instreamAction), for: .touchUpInside)
        view.addSubview(instreamBtn)
        view.bringSubviewToFront(instreamBtn)
        
    }

    @objc func instreamAction(sender: UIButton!) {
        print("Button tapped")
        let detailView: DetailView = DetailView.fromNib();
        //        detailView.viewController = self;
        detailView.initView(vc: self);
        view.addSubview(detailView)
    }

}

