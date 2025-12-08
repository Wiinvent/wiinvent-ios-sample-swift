import UIKit
import WISDK

extension WI3rdBannerSampleTableViewController {
    enum Item {
        case bannerAd(String)
        case other
    }
}

final class WI3rdBannerSampleTableViewController: UIViewController, StoryboardInstantiable {
    // MARK: - Outlet
    @IBOutlet weak var tableView: UITableView!
    
    // MARK: - Variable
    private lazy var items: [Item] = []
    private var adManager: WI3rdBannerReusableManager? {
        willSet {
            adManager?.cleanUp()
        }
    }
    
    // MARK: - Life Cycle
    static func instantiate() -> Self {
        let vc = instantiateViewController()
        vc.modalPresentationStyle = .fullScreen
        return vc
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupTableView()
        loadData()
    }
    
    deinit {
        adManager = nil
    }
    
    // MARK: - Layout
    private func setupTableView() {
        WI3rdBannerReusableManager.registerCell(for: tableView)
        
        let control = UIRefreshControl()
        control.tintColor = .white
        control.addTarget(target, action: #selector(onRefresh), for: .valueChanged)
        tableView.refreshControl = control
    }
    
    // MARK: - Action
    @IBAction func onClosePressed(_ sender: UIButton) {
        dismiss(animated: true)
    }
    
    @objc private func onRefresh() {
        loadData()
        tableView.refreshControl?.endRefreshing()
    }
}

// MARK: - Data
extension WI3rdBannerSampleTableViewController {
    private func loadData() {
        items = (0..<50).map { _ in Item.other }
        tableView.reloadData()
        
        loadAd()
    }
    
    private func loadAd() {
        let bannerLarge = WI3rdBannerAdData(
            position: "subpage1",
            accountId: String(14),
            env: .SANDBOX,
            channelId: "",
            streamId: "",
            transId: "1111",
            contentType: WIContentType.FILM,
            title: "Highlights Áo vs Thổ Nhĩ Kỳ | Giao Hữu Quốc Tế 2024",
            category: "Category 1,Category 2",
            keyword: "keyword1,keyword2",
            age: 30,
            gender: WIGender.MALE,
            adSize: .MEDIUM_BANNER,
            uid20: "",
            segments: "123,123,123",
            bannerType: .display,
            padding: .init(top: 0, left: 12, bottom: 0, right: 12)
        )
        
        let bannerMedium = WI3rdBannerAdData(
            position: "subpage2",
            accountId: String(14),
            env: .SANDBOX,
            channelId: "",
            streamId: "",
            transId: "1111",
            contentType: WIContentType.FILM,
            title: "Highlights Áo vs Thổ Nhĩ Kỳ | Giao Hữu Quốc Tế 2024",
            category: "Category 1,Category 2",
            keyword: "keyword1,keyword2",
            age: 30,
            gender: WIGender.MALE,
            adSize: .MEDIUM_BANNER,
            uid20: "",
            segments: "123,123,123",
            bannerType: .display,
            padding: .init(top: 12, left: 12, bottom: 0, right: 12)
        )
        
        let adManager = WI3rdBannerReusableManager()
        adManager.request(ads: [bannerLarge, bannerMedium]) { [weak self] pids in
            var indexPaths: [IndexPath] = []
            for pid in pids {
                switch pid {
                case "subpage1":
                    self?.items.insert(.bannerAd(pid), at: 0)
                    indexPaths.append(.init(row: 0, section: 0))
                case "subpage2":
                    self?.items.insert(.bannerAd(pid), at: 2)
                    indexPaths.append(.init(row: 2, section: 0))
                default:
                    break
                }
            }
            if !indexPaths.isEmpty {
                self?.tableView.insertRows(at: indexPaths, with: .none)
            }
        }
        self.adManager = adManager
    }
}

// MARK: - UITableViewDataSource
extension WI3rdBannerSampleTableViewController: UITableViewDataSource {
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        items.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let item = items[indexPath.row]
        switch item {
        case .bannerAd(let adId):
            guard let cell = adManager?.tableView(tableView, cellForRowAt: indexPath, adId: adId) else {
                fatalError("dequeueReusableCell failed")
            }
            return cell
        case .other:
            return tableView.dequeueReusableCell(withIdentifier: "WI3rdSampleTableOtherCell", for: indexPath)
        }
    }
}

// MARK: - UITableViewDelegate
extension WI3rdBannerSampleTableViewController: UITableViewDelegate {
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        let item = items[indexPath.row]
        switch item {
        case .bannerAd(let adId):
            let height = adManager?.tableView(tableView, heightForRowAt: indexPath, adId: adId)
            return height ?? 0
        case .other:
            return UITableView.automaticDimension
        }
    }
}
