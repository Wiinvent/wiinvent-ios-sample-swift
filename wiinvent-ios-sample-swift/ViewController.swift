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

class ViewController: UIViewController, WIAdsInStreamLoaderDelegate, WIGameDelegate {
    
    static let SAMPLE_ACCOUNT_ID: Int = 14
    static let SAMPLE_CHANNEL_ID: String = "1"
    static let SAMPLE_STREAM_ID: String = "79"
    static let SAMPLE_TOKEN: String = "5001"
    static let SAMPLE_VOD_URL: String = "https://commondatastorage.googleapis.com/gtv-videos-bucket/sample/WeAreGoingOnBullrun.mp4";
    
    var player: AVPlayer?
    var playerViewController: AVPlayerViewController!
    var containerView: UIView!;
//    var loader: WIAdsLoaderDelegate
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
//        initExoPlayer()
//        initInstream()
//        initOverlay();
        initGame();
        
//        initLandingPage();
        
    }


    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated);

//        let requestData = WIAdsRequestData(channelId: "11683", streamId: "13545")
//        WIAdsInStreamManager.shared().requestAds(requestData: requestData, player: player!, adContainer: containerView, viewController: self)
//
//        print("=======request instream ads")
    }
    
    func initGame() {
        containerView = UIView(frame: CGRect(x: 0, y: 0, width: view.frame.width, height: view.frame.height))
        containerView.backgroundColor = UIColor.blue
        view.addSubview(containerView);
        
        let gameData = WIGameData(accountId: String(ViewController.SAMPLE_ACCOUNT_ID),
                                  channelId: ViewController.SAMPLE_CHANNEL_ID,
                                  streamId: ViewController.SAMPLE_STREAM_ID,
                                  token: "5002",
                                  env: WIGameData.GameEnv.SANDBOX)
        
        WIGameManager.shared().addGameView(container: containerView, data: gameData, gameDelegate: self)
    }
    
    func initExoPlayer() {
//        containerView = UIView(frame: CGRect(x: 0, y: 0, width: view.frame.width, height: 250))
        containerView = UIView(frame: CGRect(x: 0, y: 0, width: view.frame.width, height: view.frame.height))
        containerView.backgroundColor = UIColor.blue
        view.addSubview(containerView);
        
        
        let contentURL = URL(string: ViewController.SAMPLE_VOD_URL)
        player = AVPlayer(url: contentURL!)
        playerViewController = AVPlayerViewController()
        playerViewController.player = player
        playerViewController.showsPlaybackControls = true
        playerViewController.view.translatesAutoresizingMaskIntoConstraints = false;
        
//        showContentPlayer();
    }
    
    func initInstream() {
        //Begin khoi tao 1 lan trong toan ung dung
        WIAdsInStreamManager.shared().initInstream(accountId: ViewController.SAMPLE_ACCOUNT_ID, env: WIAdsInStreamManager.AdsEnvironment.SANDBOX, timeoutInSecond: 10, logLevel: WIAdsInStreamManager.LevelLog.BODY)
        //End khoi tao 1 lan trong toan ung dung
        
        WIAdsInStreamManager.shared().loaderDelegate = self
    }
    
    func initLandingPage() {
        let overlayData = WIOverlayData(type: WIOverlayData.OverlayType.PROFILE,
                                        accountId: ViewController.SAMPLE_ACCOUNT_ID,
                                        thirdPartyToken: nil,
                                        env: WIOverlayData.Environment.LOCAL
                                        )
        WIOverlayManager.addOverlaysToPlayerView(container: containerView, overlayData: overlayData);
        WIOverlayManager.onUserLogin = {
            self.showToastFaded(message: "Login")
        }
    }
    
    func initOverlay() {

//        playerViewController.player?.play()
        
        print("==========initOverlay")
                
       
    
//        containerView.addSubview(playerViewController.view)
//        addChild(avController)

//

        WIOverlayManager.monitorAVPlayer(player: player)
        WIOverlayManager.onConfigReady = { configData in
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
                                        env: WIOverlayData.Environment.SANDBOX)

        WIOverlayManager.addOverlaysToPlayerView(container: containerView, overlayData: overlayData)

        WIOverlayManager.onOverlayError = { () in
            //TODO: SDK error
            self.showToastFaded(message: "onOverlayError")
        }

        WIOverlayManager.onUserLogin = { () in
            //TODO: Show Login Form
            self.showToastFaded(message: "onUserLogin")
        }


        WIOverlayManager.onTokenExpire = { () in
            //TODO: Token user expired
            self.showToastFaded(message: "onTokenExpire")
        }

        WIOverlayManager.onAdsEvent = { (event) in
            switch event.getEventType() {
                case WIAdEvent.AdEventType.START:
                    print("==========WIAdEvent.AdEventType.START: " + event.getCampaignId())
                    print("==========WIAdEvent.AdEventType.START: " + String(event.isLinear()))
                    print("==========WIAdEvent.AdEventType.START: " + String(event.getErrorCode()))
                    print("==========WIAdEvent.AdEventType.START: " + event.getErrorMessage())
                    self.showToastFaded(message: "campaign id: " + event.getCampaignId() + " -isLinear: " + String(event.isLinear()))
                    break
                default: break
            }

        }

//        WISDK.removeOverlays();
//        showToastFaded(message: "hello")
    }
    
    // MARK:
    func showContentPlayer() {
        self.addChild(playerViewController)
        self.containerView.insertSubview(playerViewController.view, at: 0)
        playerViewController.didMove(toParent: self)
        
        NSLayoutConstraint.activate([
              playerViewController.view.leadingAnchor.constraint(equalTo: containerView.leadingAnchor, constant: 0),
              playerViewController.view.trailingAnchor.constraint(equalTo: containerView.trailingAnchor, constant: 0),
              playerViewController.view.topAnchor.constraint(equalTo: containerView.topAnchor, constant: 0),
              playerViewController.view.bottomAnchor.constraint(equalTo: containerView.bottomAnchor, constant: 0),
        ])
    }
    
    func hideContentPlayer() {
        playerViewController.willMove(toParent: nil)
        playerViewController.view.removeFromSuperview()
        playerViewController.removeFromParent()
    }
    
    //MARK: Begin WIAdsInStreamLoaderDelegate
    func wiManagerRequestPlayContent() {
        showContentPlayer()
        playerViewController.player?.play()
    }
    
    func wiManagerRequestPauseContent() {
        playerViewController.player?.pause()
        hideContentPlayer()
    }
    
    func wiManagerRequestFailure() {
        showContentPlayer()
        playerViewController.player?.play()
    }
    
    func onEvent(event: WIAdEvent) {
        print("=========Wi Ad Event Type: \(event.getEventType()) - \(event.getCampaignId())")
    }
    
    //MARK: End WIAdsInStreamLoaderDelegate
    
    //MARK: WIGameDelegate begin
    func onDismiss() {
        self.showToastFaded(message: "onDismiss")
    }
    
    func onError() {
        self.showToastFaded(message: "onError")
    }
    
    func onTimeout() {
        self.showToastFaded(message: "onTimeout")
    }
    //MARK: WIGameDelegate end
    
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

