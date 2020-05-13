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
    
    static let SAMPLE_ACCOUNT_ID: Int = 1
    static let SAMPLE_CHANNEL_ID: String = "##"
    static let SAMPLE_STREAM_ID: String = "##"
    static let SAMPLE_TOKEN: String = ""
    
    var player: AVPlayer?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        
        player = AVPlayer()
        let avController = AVPlayerViewController()
        avController.player = player
        avController.showsPlaybackControls = true
        avController.view.frame = view.frame

        view.addSubview(avController.view)
        addChild(avController)
        player?.play()

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
        
        WISDK.onVoted = { ( userId, channelId, streamId, entryId, numPredictSame) in
            print("====onConfigReady: \(userId)")
        }
       
        WISDK.onUserPurchase = { (userId, productId) in
            print("====onConfigReady: \(userId)")
        }
        
         let overlayData = WIOverlayData(channelId: ViewController.SAMPLE_CHANNEL_ID,
                                               streamId: ViewController.SAMPLE_STREAM_ID,
                                               //Optional
                                               thirdPartyToken: "token",
                                               accountId: ViewController.SAMPLE_ACCOUNT_ID,
                                               mappingType: WIOverlayData.MappingType.THIRDPARTY,
                                               platform: nil,
                                               env: WIOverlayData.Environment.DEV,
                                               deviceType: WIOverlayData.DeviceType.PHONE,
                                               debug: true)
        WISDK.addOverlaysToPlayerView(container: view, overlayData: overlayData)
        
    }


}

