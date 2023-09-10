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
import GoogleInteractiveMediaAds

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

class ViewController: UIViewController, WIWelcomeAdDelegate {
    
    var instreamBtn: UIButton!
    var welcomeBtn: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        instreamBtn = UIButton(frame: CGRect(x: 100, y: 100, width: 200, height: 50))
        instreamBtn.backgroundColor = .red
        instreamBtn.setTitle("Instream Detail", for: .normal)
        instreamBtn.addTarget(self, action: #selector(instreamAction), for: .touchUpInside)
        view.addSubview(instreamBtn)
        view.bringSubviewToFront(instreamBtn)
        
        welcomeBtn = UIButton(frame: CGRect(x: 100, y: 200, width: 200, height: 50))
        welcomeBtn.backgroundColor = .red
        welcomeBtn.setTitle("Welcome Detail", for: .normal)
        welcomeBtn.addTarget(self, action: #selector(welcomeAction), for: .touchUpInside)
        view.addSubview(welcomeBtn)
        view.bringSubviewToFront(welcomeBtn)
        
    }

    @objc func instreamAction(sender: UIButton!) {
        print("Button tapped")
        let detailView: DetailView = DetailView.fromNib();
        //        detailView.viewController = self;
        detailView.initView(vc: self);
        view.addSubview(detailView)
    }
    
    @objc func welcomeAction(sender: UIButton!) {
        print("===> welcomeAction")
        initWelcomeAd()
    }
    
    func initWelcomeAd() {
        let adData = WIWelcomeAdData(accountId: String(14), domainUrl: "", env: WIEnvironment.SANDBOX)
        // add friendly Obstruction View
        var friendlyObstructionList: [IMAFriendlyObstruction] = []
        
        WIWelcomeAdManager.shared().requestAds(requestData: adData, container: view, viewController: self, delegate: self, timeoutInSecond: 5, levelLog: WILevelLog.NODE, friendlyObstructionList: friendlyObstructionList);

        print("-----request ads")
    }
    
    
    func onDisplayAds() {
        print("-----onDisplayAds")
    }
    
    func onNoAds() {
        print("-----onNoAds")
        showToastFaded(message: "no ads")
    }
    
    func onAdsWelcomeDismiss() {
        print("-----onAdsWelcomeDismiss")
    }
    
    func onAdsWelcomeClick(clickThroughType: WIClickThroughType, contentId: String, campaignId: Int64) {
        print("-----onAdsWelcomeDismiss \(clickThroughType.rawValue) - \(contentId) - campaignId \(campaignId)")
        
        showToastFaded(message: "-----content \(clickThroughType.rawValue) - \(contentId) - campaignId \(campaignId)")
    }
    
    func onAdsWelcomeImpression(campaignId: Int64) {
        print("-----onAdsWelcomeImpression")
    }
    
    func onAdsWelcomeSkip(campaignId: Int64) {
        print("-----onAdsWelcomeSkip")
    }
    
    func onAdsWelcomeError() {
        print("-----onAdsWelcomeError")
    }
    
    func onAdsWelcomeTimeout() {
        print("-----onAdsWelcomeTimeout")
    }
    
    func showToastFaded(message : String) {
        let toastLabel = UILabel(frame: CGRect(x: self.view.frame.size.width/2 - 125, y: self.view.frame.size.height-100, width: 250, height: 35))
        toastLabel.numberOfLines = 0
        toastLabel.backgroundColor = UIColor.black.withAlphaComponent(0.6)
        toastLabel.textColor = UIColor.white
        toastLabel.textAlignment = .center;
        toastLabel.text = message
        toastLabel.alpha = 1.0
        toastLabel.layer.cornerRadius = 10;
        toastLabel.clipsToBounds  =  true
        toastLabel.sizeToFit()
        toastLabel.frame = CGRect( x: toastLabel.frame.minX, y: toastLabel.frame.minY,width:   toastLabel.frame.width + 20, height: toastLabel.frame.height + 8)
        
        self.view.addSubview(toastLabel)
        UIView.animate(withDuration: 4.0, delay: 0.1, options: .curveEaseOut, animations: {
            toastLabel.alpha = 0.0
        }, completion: {(isCompleted) in
            toastLabel.removeFromSuperview()
        })
    }

}

