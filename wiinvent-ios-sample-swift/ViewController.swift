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

class ViewController: UIViewController {

    static let SAMPLE_ACCOUNT_ID: Int = 13
    static let SAMPLE_CHANNEL_ID: String = "107578015"
    static let SAMPLE_STREAM_ID: String = "957"
    static let SAMPLE_TOKEN: String = "5001"
    static let SAMPLE_VOD_URL: String = "https://commondatastorage.googleapis.com/gtv-videos-bucket/sample/WeAreGoingOnBullrun.mp4";
    
    var player: AVPlayer?

    override func viewDidLoad() {
        super.viewDidLoad()

        showToastFaded(message: "hello")
        
        initOverlay();
    }
    
    func initOverlay() {
//        let containerView = UIView(frame: CGRect(x: 0, y: 0, width: view.frame.width, height: 250))
        let containerView = UIView(frame: CGRect(x: 0, y: 0, width: view.frame.width, height: view.frame.height))
        containerView.backgroundColor = UIColor.blue
        view.addSubview(containerView);
        
        player = AVPlayer(url: URL.init(string: ViewController.SAMPLE_VOD_URL)!)
        let avController = AVPlayerViewController()
        avController.player = player
        avController.showsPlaybackControls = true
        avController.view.translatesAutoresizingMaskIntoConstraints = false;
    
        containerView.addSubview(avController.view)
        addChild(avController)
        
        NSLayoutConstraint.activate([
            avController.view.leadingAnchor.constraint(equalTo: containerView.leadingAnchor, constant: 0),
            avController.view.trailingAnchor.constraint(equalTo: containerView.trailingAnchor, constant: 0),
            avController.view.topAnchor.constraint(equalTo: containerView.topAnchor, constant: 0),
            avController.view.bottomAnchor.constraint(equalTo: containerView.bottomAnchor, constant: 0),
             ])

        WISDK.monitorAVPlayer(player: player)

        WISDK.onConfigReady = { configData in
            if let sources = configData.sources {
                for source in sources {
                    if let url = source.url, AVAsset(url: url).isPlayable {
                        print("====onConfigReady: \(url)")
                        self.player?.replaceCurrentItem(with: AVPlayerItem(url: url))
                    }
                }
            }
        }
    
        let overlayData = WIOverlayData(channelId: ViewController.SAMPLE_CHANNEL_ID,
                                        streamId: ViewController.SAMPLE_STREAM_ID,
                                        thirdPartyToken: "",
                                        contentType: WIOverlayData.ContentType.LIVESTREAM,
                                        accountId: ViewController.SAMPLE_ACCOUNT_ID,
                                        platform: nil,
                                        env: WIOverlayData.Environment.PRODUCTION)

        WISDK.addOverlaysToPlayerView(container: containerView, overlayData: overlayData)

        WISDK.onConfigReady = { (configData) in
            //TODO: SDK ready, can be call ads request
            self.showToastFaded(message: "onConfigReady")
        }
        
        WISDK.onDisplayOverlay = {(isDisplay) in
            self.showToastFaded(message: "====isDisplay: \(isDisplay)")
        }


//        WISDK.removeOverlays();
        
        showToastFaded(message: "hello")
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

