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
    
    static let SAMPLE_CHANNEL_ID: String = "1"
    static let SAMPLE_STREAM_ID: String = "1"
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
        let overlayData = WIOverlayData(channelId: ViewController.SAMPLE_CHANNEL_ID, streamId: ViewController.SAMPLE_STREAM_ID, env: WIOverlayData.Environment.DEV, debug: true)
        WISDK.addOverlaysToPlayerView(container: view, overlayData: overlayData)
        
    }


}

