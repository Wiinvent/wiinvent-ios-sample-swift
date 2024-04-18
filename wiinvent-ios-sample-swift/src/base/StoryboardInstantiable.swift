import UIKit

protocol StoryboardInstantiable {
    associatedtype T
    static var fileName: String { get }
    static func instantiateViewController(_ bundle: Bundle?) -> T
}

extension StoryboardInstantiable where Self: UIViewController {
    
    static var fileName: String {
        return String(describing: Self.self)
    }
    
    static func instantiateViewController(_ bundle: Bundle? = nil) -> Self {
        let storyboard = UIStoryboard(name: fileName, bundle: bundle)
        guard let viewController = storyboard.instantiateInitialViewController() as? Self else {
            fatalError("Cannot instantiate initial view controller \(Self.self) from storyboard with name \(fileName)")
        }
        return viewController
    }
}
