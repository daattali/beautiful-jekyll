# frozen_string_literal: true

source "https://rubygems.org"

gem "wdm", "~> 0.1.1", :install_if => Gem.win_platform?

# Windows and JRuby does not include zoneinfo files, so bundle the tzinfo-data gem
# and associated library.
platforms :mingw, :x64_mingw, :mswin, :jruby do
    gem "tzinfo", ">= 1", "< 3"
    gem "tzinfo-data"
  end
  
gemspec

