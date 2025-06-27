//
//  DetailView.swift
//  wiinvent-ios-sample-swift
//
//  Created by Nam Co on 29/03/2023.
//  Copyright © 2023 wiinvent. All rights reserved.
//

import UIKit
import WISDK
import AVKit
import MediaPlayer
import GoogleInteractiveMediaAds

class DetailView: UIView, NibInstantiatable, WIAdsInStreamLoaderDelegate, UIGestureRecognizerDelegate {
    
//    static let SAMPLE_VOD_URL: String = "http://qthttp.apple.com.edgesuite.net/1010qwoeiuryfg/sl.m3u8";
    static let SAMPLE_LIVE_URL: String = "https://bitdash-a.akamaihd.net/content/sintel/hls/playlist.m3u8"
    
    private weak var viewController: ViewController?
    @IBOutlet weak var backBtn: UIButton!
    @IBOutlet weak var videoControls: UIToolbar!
    @IBOutlet weak var playHeadBtn: UIButton!
    @IBOutlet weak var playHeadTimeTxt: UITextField!
    @IBOutlet weak var progressBar: UISlider!
    @IBOutlet weak var durationTimeTxt: UITextField!
    @IBOutlet weak var consoleView: UITextView!
    @IBOutlet weak var containerView: UIView!
    
    var contentPlayer: AVPlayer?
    var contentPlayerLayer: AVPlayerLayer?
    enum PlayButtonType: Int {
        case playButton = 0
        case pauseButton = 1
    }
    
    // Gesture recognizer for tap on video.
    var videoTapRecognizer: UITapGestureRecognizer?
    
    // Tracking for play/pause.
    var isAdPlayback = false
    var didRequestAds: Bool = false
    
    var contentRateContext: UInt8 = 1
    var contentDurationContext: UInt8 = 2
    
    var skipButton: WiAdsSkipButton?
    
    func initView(vc: ViewController) {
        viewController = vc
        
        // Set videoView on top of everything else (for fullscreen support).
        bringSubviewToFront(containerView)
        bringSubviewToFront(videoControls)
        
        setUpContentPlayer()
        setUpInStreamAds(vc: vc)
        
        let notificationCenter = NotificationCenter.default
        notificationCenter.addObserver(forName: UIApplication.didBecomeActiveNotification,
                                               object: nil,
                                               queue: OperationQueue.main) { [weak self] notification in
            guard let self = self else { return }
            self.didBecom(active: notification)
        }
        
        notificationCenter.addObserver(self, selector: #selector(appMovedToBackground), name: UIApplication.willResignActiveNotification, object: nil)
    }
    
    @objc private func didBecom(active notification: Notification){
        print("==> didBecom active")
        
        skipButton?.resume()
        WIAdsInStreamManager.shared().resume()
    }
    
    @objc func appMovedToBackground() {
        print("==> didBecom appMovedToBackground")
        
        skipButton?.pause()
        WIAdsInStreamManager.shared().movedToBackground()
    
    }
    
    override func didMoveToSuperview() {
        if self.superview != nil {
            guard !didRequestAds else {
                return
            }
            didRequestAds = true
            
//            self.contentPlayer?.play()
            
            //add friendly Obstruction View --> Phan nay quan trong, can khai bao het cac layer phu len tren player.
            var friendlyObstructionList: [IMAFriendlyObstruction] = []
            if skipButton != nil {
                let skipButtonObstruction = IMAFriendlyObstruction(view: skipButton!, purpose: IMAFriendlyObstructionPurpose.mediaControls, detailedReason: "Skip Button")
                friendlyObstructionList.append(skipButtonObstruction)
            }
            
            WIAdsInStreamManager.shared().initInstream(accountId: 14, env: WIEnvironment.SANDBOX, vastLoadTimeout: 5, loadVideoTimeout: 5, bufferingVideoTimeout: 5, bitrate: 2000, logLevel: WILevelLog.BODY, enablePiP: false, skipDuration: 6)
            
            // Make the request only once the view has been instantiated.
            let tapped = UIPanGestureRecognizer(target: self, action: #selector(self.panGesture(_:)))
            tapped.delegate = self
            
            
            let requestData = WIAdsRequestData(
                channelId: "998989,343434", //danh sách id của category & cách nhau bằng dấu ,
                streamId: "911", // id nội dung
                transId: "1111", //mã giao dịch tạo từ server đối tác - client liên hệ server để biết thêm thông tin
                contentType: WIContentType.FILM, //content type FIRM | TV | VIDEO
                title: "Highlights Áo vs Thổ Nhĩ Kỳ | Giao Hữu Quốc Tế 2024", // tiêu đề nội dung
                category: "Category1,Category2", // danh sach tiêu đề của category & cách nhau bằng dấu ,
                keyword: "keyword1,keyword2", //từ khoá nếu có | để "" nếu ko có
                age: 0, // tuổi , nếu không có thì để 0
                gender: WIGender.NONE, //giới tính nếu không có thì set NONE
                uid20: "", // unified id 2.0, nếu không có thì set ""
                segments: "123,123,123" //cac segment id cach nhau = dau ,
            )
            
            WIAdsInStreamManager.shared().requestAds(requestData: requestData, player: self.contentPlayer!, adContainer: self.containerView, viewController: self.viewController!, uiPanGestureRecognizer: tapped, friendlyObstructionList: friendlyObstructionList)
        }
        else {
            // the view was removed from its superview
        }
    }
    
    @objc func panGesture(_ recognizer: UITapGestureRecognizer?) {
        print("==========panGesture")
    }
    
    func setUpInStreamAds(vc: ViewController) {
        skipButton = Tv360SkipAdsButton()
//        skipButton?.isHidden = true //Only for test, remove it when run production
        skipButton?.addTarget(self, action: #selector(onCLickSkipButton), for: .touchUpInside)
        skipButton?.translatesAutoresizingMaskIntoConstraints = false
        self.addSubview(skipButton!)
        self.bringSubviewToFront(skipButton!)
        
        skipButton?.rightAnchor.constraint(equalTo: containerView.rightAnchor).isActive = true
        skipButton?.bottomAnchor.constraint(equalTo: containerView.bottomAnchor, constant: -50).isActive = true
        
        WIAdsInStreamManager.shared().loaderDelegate = self
    }
    
    func setUpContentPlayer() {
        // Set up CGRects for resizing the video and controls on rotate.
        let contentURL = URL(string: DetailView.SAMPLE_LIVE_URL)
        self.contentPlayer = AVPlayer(url: contentURL!)
//        self.contentPlayer?.allowsExternalPlayback = false
        guard let contentPlayer = self.contentPlayer else { return }
        
        contentPlayer.addPeriodicTimeObserver(
            forInterval: CMTimeMake(value: 1, timescale: 30),
            queue: nil,
            using: { (time: CMTime) -> Void in
                if self.contentPlayer != nil && self.contentPlayer!.currentItem != nil {
                    let duration = self.getPlayerItemDuration(self.contentPlayer!.currentItem!)
                    self.updatePlayheadWithTime(time, duration: duration)
                }
            })

        contentPlayer.addObserver(
            self,
            forKeyPath: "rate",
            options: NSKeyValueObservingOptions.new,
            context: &contentRateContext)

        contentPlayer.addObserver(
            self,
            forKeyPath: "currentItem.duration",
            options: NSKeyValueObservingOptions.new,
            context: &contentDurationContext)

        NotificationCenter.default.addObserver(
            self,
            selector: #selector(DetailView.contentDidFinishPlaying(_:)),
            name: NSNotification.Name.AVPlayerItemDidPlayToEndTime,
            object: contentPlayer.currentItem)
        
        // Create a player layer for the player.
        contentPlayerLayer = AVPlayerLayer(player: contentPlayer)
        contentPlayerLayer!.frame = containerView.bounds
        containerView.layer.addSublayer(contentPlayerLayer!)
    }
    
    // Handler for keypath listener that is added for content playhead observer.
    override func observeValue(
        forKeyPath keyPath: String?,
        of object: Any?,
        change: [NSKeyValueChangeKey: Any]?,
        context: UnsafeMutableRawPointer?
    ) {
        if context == &contentRateContext && contentPlayer == object as? AVPlayer {
            updatePlayheadState(contentPlayer!.rate != 0)
        } else if context == &contentDurationContext && contentPlayer == object as? AVPlayer {
            var time = CMTime.zero
            if let currentItem = contentPlayer?.currentItem {
                time = getPlayerItemDuration(currentItem)
            }
            updatePlayheadDurationWithTime(time)
        }
    }
    
    // Updates play button for provided playback state.
    func updatePlayheadState(_ isPlaying: Bool) {
        setPlayButtonType(isPlaying ? PlayButtonType.pauseButton : PlayButtonType.playButton)
    }
    
    // Sets play button type.
    func setPlayButtonType(_ buttonType: PlayButtonType) {
        playHeadBtn.tag = buttonType.rawValue
        playHeadBtn.setTitle(buttonType == PlayButtonType.pauseButton ? "Pause" : "Play", for: .normal)
    }
    
    // Get the duration value from the player item.
    func getPlayerItemDuration(_ item: AVPlayerItem) -> CMTime {
        var itemDuration = CMTime.invalid
        if item.responds(to: #selector(getter:CAMediaTiming.duration)) {
            itemDuration = item.duration
        } else {
            if item.asset.responds(to: #selector(getter:CAMediaTiming.duration)) {
                itemDuration = item.asset.duration
            }
        }
        return itemDuration
    }
    
    // Updates progress bar for provided time and duration.
    func updatePlayheadWithTime(_ time: CMTime, duration: CMTime) {
        if !CMTIME_IS_VALID(time) {
            return
        }
        let currentTime = CMTimeGetSeconds(time)
        if currentTime.isNaN {
            return
        }
        
        progressBar.value = Float(currentTime)
        playHeadTimeTxt.text =
        NSString(
            format: "%d:%02d", Int(currentTime / 60),
            Int(currentTime.truncatingRemainder(dividingBy: 60))) as String
        updatePlayheadDurationWithTime(duration)
    }
    
    func updatePlayheadDurationWithTime(_ time: CMTime!) {
        if !time.isValid {
            return
        }
        let durationValue = CMTimeGetSeconds(time)
        if durationValue.isNaN {
            return
        }
        progressBar.maximumValue = Float(durationValue)
        durationTimeTxt.text =
        NSString(
            format: "%d:%02d", Int(durationValue / 60),
            Int(durationValue.truncatingRemainder(dividingBy: 60))) as String
    }
    
    // Notify IMA SDK when content is done for post-rolls.
    @objc func contentDidFinishPlaying(_ notification: Notification) {
        // Make sure we don't call contentComplete as a result of an ad completing.
        if (notification.object as? AVPlayerItem) == contentPlayer!.currentItem {
            logMessage("content Did Finish")
            
            WIAdsInStreamManager.shared().contentComplete()
        }
    }
    
    func showContentPlayer() {
        contentPlayer!.play()
        videoControls?.alpha = 1.0
        isAdPlayback = false
    }
    
    func hideContentPlayer() {
        contentPlayer!.pause()
        videoControls?.alpha = 0
        isAdPlayback = true
    }
    
    //MARK: Begin WIAdsInStreamLoaderDelegate
    func wiManagerRequestPlayContent() {
        logMessage("=========wiManagerRequestPlayContent")
        
        showContentPlayer()
    }
    
    func wiManagerRequestPauseContent() {
        logMessage("==> wiManagerRequestPauseContent")
        
        hideContentPlayer()
    }
    
    func wiManagerRequestFailure() {
        logMessage("==> wiManagerRequestFailure")
        
        showContentPlayer()
    }
    
    func wiShowSkipButton(duration: Int) {
        skipButton?.startCountdown(duration: duration)
    }
    
    @objc func onCLickSkipButton(sender: UIButton!) {
        print("=========> onCLickSkipButton")
        WIAdsInStreamManager.shared().discardAdBreak()
        skipButton?.hide()
    }
    
    func wiRemoveSkipButton() {
        skipButton?.hide()
    }
    
    public func mediaProgress(mediaTime: TimeInterval, totalTime: TimeInterval) {
        print("============>WI mediaProgress mediaTime: \(mediaTime) - totalTime: \(totalTime) : \(totalTime - mediaTime)")
    }
    
    func onEvent(event: WISDK.WIAdEvent) {
        logMessage("==> onEvent: \(event.getTypeString()) - \(event.getCampaignId())")
    }
    //MARK: End WIAdsInStreamLoaderDelegate
    
    @IBAction func videoControlsTouchStarted(_ sender: Any) {
        
    }
    
    @IBAction func videoControlsTouchEnded(_ sender: Any) {
        
    }
    
    @IBAction func playheadValueChanged(_ sender: AnyObject) {
        if !sender.isKind(of: UISlider.self) {
            return
        }
        if !isAdPlayback {
            let slider = sender as! UISlider
            contentPlayer!.seek(to: CMTimeMake(value: Int64(slider.value), timescale: 1))
        }
    }
    
    @IBAction func playHeadBtnClicked(_ sender: Any) {
        if contentPlayer!.rate == 0 {
            contentPlayer!.play()
        } else {
            contentPlayer!.pause()
        }
    }
    
    @IBAction func backBtnClicked(_ sender: Any) {
        print("============backBtnClicked")
        self.contentPlayer?.pause()
        self.contentPlayer?.replaceCurrentItem(with: nil)
        
        WIAdsInStreamManager.shared().destroy();
        
        self.removeFromSuperview();
    }
    
    public func gestureRecognizer(_ gestureRecognizer: UIGestureRecognizer, shouldRecognizeSimultaneouslyWith otherGestureRecognizer: UIGestureRecognizer) -> Bool {
        return true
    }
    
    // MARK: Utility methods
    func logMessage(_ log: String!) {
        consoleView.text = consoleView.text + ("\n" + log)
        NSLog(log)
        if consoleView.text.count > 0 {
            let bottom = NSMakeRange(consoleView.text.count - 1, 1)
            consoleView.scrollRangeToVisible(bottom)
        }
    }
}
