//
//  ViewController.swift
//  wiinvent-ios-sample-swift
//
//  Created by mcg-corp on 4/29/20.
//  Copyright © 2020 wiinvent. All rights reserved.
//

import UIKit
import WISDK
import PTVSDK
import AVKit

class ViewController: UIViewController {
    
    static let SAMPLE_ACCOUNT_ID: Int = 81
    static let SAMPLE_CHANNEL_ID: String = "30"
    static let SAMPLE_STREAM_ID: String = "90000"
    static let SAMPLE_TOKEN: String = "1001"
    
    var player: AVPlayer?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let frame = CGRect(x: 0, y: 0, width: view.frame.width, height: 250)
//        let frame = CGRect(x: 0, y: 0, width: view.frame.width, height: view.frame.height)
        
        let videoURL = URL(string: "https://www.soundhelix.com/examples/mp3/SoundHelix-Song-1.mp3")
        
        player = AVPlayer(url: videoURL!)
        let avController = AVPlayerViewController()
        avController.player = player
        avController.showsPlaybackControls = true
        avController.view.frame = frame
      
        view.addSubview(avController.view)
        addChild(avController)
        
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

//        WISDK.onVoted = { ( userId, channelId, streamId, entryId, numPredictSame) in
//            print("====onConfigReady: \(userId)")
//        }

        WISDK.onUserPurchase = { (userId, productId) in
            print("====onConfigReady: \(userId)")
        }

         let overlayData = WIOverlayData(channelId: ViewController.SAMPLE_CHANNEL_ID,
                                               streamId: ViewController.SAMPLE_STREAM_ID,
                                               //Optional
                                               thirdPartyToken: ViewController.SAMPLE_TOKEN,
                                               contentType: WIOverlayData.ContentType.LIVESTREAM,
                                               accountId: ViewController.SAMPLE_ACCOUNT_ID,
                                               mappingType: WIOverlayData.MappingType.THIRDPARTY,
                                               platform: nil,
                                               env: WIOverlayData.Environment.DEV,
                                               deviceType: WIOverlayData.DeviceType.PHONE,
                                               debug: true)
        WISDK.addOverlaysToPlayerView(container: view, overlayData: overlayData)
        
    }


}

