# coding: utf-8

Gem::Specification.new do |spec|
  spec.name          = "beautiful-jekyll-theme"
  spec.version       = "0.1.0"
  spec.authors       = ["Dean Attali"]
  spec.email         = ["daattali@gmail.com"]

  spec.summary       = %q{Beautiful Jekyll is a ready-to-use Jekyll theme to help you create an awesome website quickly. Perfect for personal blogs or simple project websites, with a focus on responsive and clean design.}
  spec.homepage      = "http://deanattali.com/beautiful-jekyll"
  spec.license       = "MIT"

  spec.files         = `git ls-files -z`.split("\x0").select { |f| f.match(%r{^(assets|_layouts|_includes|_posts|LICENSE|README|aboutme|feed|_config)}i) }

  spec.add_runtime_dependency "jekyll", "~> 3.3"

  spec.add_development_dependency "bundler", "~> 1.12"
  spec.add_development_dependency "rake", "~> 10.0"
  spec.add_development_dependency "jekyll-paginate", "~> 1.1"
end
