# Uncomment the next line to define a global platform for your project
source 'https://github.com/CocoaPods/Specs.git'
source 'https://github.com/bitmovin/cocoapod-specs.git'
platform :ios, '13'

target 'wiinvent-ios-sample-swift' do
  # Comment the next line if you don't want to use dynamic frameworks
  use_frameworks!
  pod 'WISDK', '1.21.5'
#  pod 'BitmovinPlayer', '3.36.0'

  # Pods for wiinvent-ios-sample-swift

  target 'wiinvent-ios-sample-swiftTests' do
    inherit! :search_paths
    # Pods for testing
  end

  target 'wiinvent-ios-sample-swiftUITests' do
    # Pods for testing
  end

end


post_install do |installer|
  installer.pods_project.targets.each do |target|
    target.build_configurations.each do |config|
      config.build_settings['ONLY_ACTIVE_ARCH'] = 'NO'
      config.build_settings['BUILD_LIBRARY_FOR_DISTRIBUTION'] = 'YES'
    end
  end
end
