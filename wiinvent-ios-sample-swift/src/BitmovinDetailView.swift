//
//  DetailView.swift
//  wiinvent-ios-sample-swift
//
//  Created by Nam Co on 29/03/2023.
//  Copyright © 2023 wiinvent. All rights reserved.
//

import UIKit
import WISDK
//import BitmovinPlayer
import GoogleInteractiveMediaAds

extension BitmovinDetailView {
    enum State {
        case enterBackground, becomActive, enterForeground, willResign
    }
}

class BitmovinDetailView: UIView, NibInstantiatable {
//    private let playerLicenseKey = "22a5430e-a8cc-46d3-98b1-e64808844d87"
//    
//    @IBOutlet weak var backBtn: UIButton!
//    @IBOutlet weak var consoleView: UITextView!
//    @IBOutlet weak var containerView: UIView!
//    
//    
//    private weak var viewController: ViewController?
//    private var player: Player!
//    private var playerView: PlayerView!
//    private var contentPlayhead: IMAContentPlayhead?
//    
//    
//    // Gesture recognizer for tap on video.
//    var videoTapRecognizer: UITapGestureRecognizer?
//        
//    var skipButton: WiAdsSkipButton?
//    
//    func initView(vc: ViewController) {
//        self.viewController = vc
//        
//        let notificationCenter = NotificationCenter.default
//        notificationCenter.addObserver(forName: UIApplication.didBecomeActiveNotification,
//                                               object: nil,
//                                               queue: OperationQueue.main) { [weak self] notification in
//            guard let self = self else { return }
//            self.didBecom(active: notification)
//        }
//        notificationCenter.addObserver(self, selector: #selector(appMovedToBackground), name: UIApplication.willResignActiveNotification, object: nil)
//    }
//    
//    override func didMoveToWindow() {
//        super.didMoveToWindow()
//        if window != nil {
//            setupPlayer()
//            initSkipButton(vc: self.viewController!)
//            setupIMA()
//            
//        }
//    }
//    
//    private func setupPlayer() {
//        // Player Configuration
//        let config = PlayerConfig()
//        config.key = playerLicenseKey
//        
//        // Initialize player
//        player = PlayerFactory.create(playerConfig: config)
//        playerView = PlayerView(player: player, frame: frame)
//        playerView.frame = self.containerView.bounds
//        self.containerView.addSubview(playerView)
//        
//        // Add listener for player events if needed
//        player.add(listener: self)
//        
//        // Load content
//        if let url = URL(string: "https://bitdash-a.akamaihd.net/content/sintel/hls/playlist.m3u8") {
//            let sourceConfig = SourceConfig(url: url, type: .progressive)
//            player.load(sourceConfig: sourceConfig)
//            player.play()
//        }
//    }
//    
//    private func setupIMA() {
//        WIAdsInStreamManager.shared().initInstream(accountId: 14, env: WIEnvironment.SANDBOX, vastLoadTimeout: 5, loadVideoTimeout: 15, bufferingVideoTimeout: 5, bitrate: 2000, logLevel: WILevelLog.BODY, enablePiP: false, skipDuration: 6)
//        WIAdsInStreamManager.shared().loaderDelegate = self
//        
//        let tapped = UIPanGestureRecognizer(target: self, action: #selector(self.panGesture(_:)))
//        tapped.delegate = self
//        let requestData = WIAdsRequestData(
//            channelId: "998989,998989",
//            streamId: "4444",
//            transId: "1111",
//            contentType: WIContentType.FILM,
//            title: "Sao nhập ngũ 2024 - Tập 16,,$# - Những chiến binh Thành Đồng - Vì sa", //"Highlights Áo vs Thổ Nhĩ Kỳ | Giao Hữu Quốc Tế 2024",
//            category: "Category1,Category2",
//            keyword: "",
//            age: 0,
//            gender: WIGender.NONE,
//            uid20: "", segments: "abc,123,123"
//        )
//        
//        //            add friendly Obstruction View
//        var friendlyObstructionList: [IMAFriendlyObstruction] = []
//        if skipButton != nil {
//            let skipButtonObstruction = IMAFriendlyObstruction(view: skipButton!, purpose: IMAFriendlyObstructionPurpose.mediaControls, detailedReason: "Skip Button")
//            friendlyObstructionList.append(skipButtonObstruction)
//        }
//        
//        WIAdsInStreamManager.shared().requestAds(requestData: requestData, player: self.player, adContainer: self.containerView, viewController: self.viewController!, uiPanGestureRecognizer: tapped, friendlyObstructionList: friendlyObstructionList)
//        
//        WIAdsInStreamManager.shared().addFriendlyObstruction(friendlyObstructionList: friendlyObstructionList)
//    }
//    
//    func initSkipButton(vc: ViewController) {
//        skipButton = Tv360SkipAdsButton()
//        //        skipButton?.isHidden = true //Only for test, remove it when run production
//        skipButton?.addTarget(self, action: #selector(onCLickSkipButton), for: .touchUpInside)
//        skipButton?.translatesAutoresizingMaskIntoConstraints = false
//        self.addSubview(skipButton!)
//        self.bringSubviewToFront(skipButton!)
//        
//        skipButton?.rightAnchor.constraint(equalTo: containerView.rightAnchor).isActive = true
//        skipButton?.bottomAnchor.constraint(equalTo: containerView.bottomAnchor, constant: -50).isActive = true
//    }
//    
//    func showContentPlayer() {
//        player.play()
//    }
//    
//    func hideContentPlayer() {
//        player.pause()
//    }
//    
//    @objc func onCLickSkipButton(sender: UIButton!) {
//        print("=========> onCLickSkipButton")
//        WIAdsInStreamManager.shared().discardAdBreak()
//        skipButton?.hide()
//    }
//    
//    @objc func appMovedToBackground() {
//        print("==> didBecom appMovedToBackground")
//    
//        skipButton?.pause()
//        WIAdsInStreamManager.shared().movedToBackground()
//    }
//    
//    
//    @objc private func didBecom(active notification: Notification){
//        print("==> didBecom active")
//        
//        skipButton?.resume()
//        WIAdsInStreamManager.shared().resume()
//    }
//    
//    @IBAction func onPipButtonClicked(_ sender: Any) {
//        
//    }
//    
//    @IBAction func backBtnClicked(_ sender: Any) {
//        print("============backBtnClicked")
//        self.player?.destroy()
//        
//        WIAdsInStreamManager.shared().destroy();
//        
//        self.removeFromSuperview();
//    }
//    
//    // MARK: Utility methods
//    func logMessage(_ log: String!) {
//        consoleView.text = consoleView.text + ("\n" + log)
//        NSLog(log)
//        if consoleView.text.count > 0 {
//            let bottom = NSMakeRange(consoleView.text.count - 1, 1)
//            consoleView.scrollRangeToVisible(bottom)
//        }
//    }
}

//extension BitmovinDetailView: PlayerListener {
//    func on(event: Event, from player: Player) {
//        if event is PlaybackFinishedEvent {
//            WIAdsInStreamManager.shared().contentComplete()
//        }
//    }
//}
//
//extension BitmovinDetailView: WIAdsInStreamLoaderDelegate {
//    func wiManagerRequestPlayContent() {
//        logMessage("=========wiManagerRequestPlayContent")
//        
//        showContentPlayer()
//    }
//    
//    func wiManagerRequestPauseContent() {
//        logMessage("==> wiManagerRequestPauseContent")
//        
//        hideContentPlayer()
//    }
//    
//    func wiManagerRequestFailure() {
//        logMessage("==> wiManagerRequestFailure")
//        
//        showContentPlayer()
//    }
//    
//    func onEvent(event: WIAdEvent) {
//        //        print("=========Wi Ad Event Type: \(event.getEventType()) - \(event.getCampaignId())")
//        logMessage("==> onEvent: \(event.getTypeString()) - \(event.getCampaignId())")
//    }
//    
//    func wiShowSkipButton(duration: Int) {
//        skipButton?.startCountdown(duration: duration)
//    }
//    
//    func wiRemoveSkipButton() {
//        skipButton?.hide()
//    }
//}
//
//extension BitmovinDetailView: UIGestureRecognizerDelegate {
//    @objc func panGesture(_ recognizer: UITapGestureRecognizer?) {
//        print("==========panGesture")
//    }
//}
