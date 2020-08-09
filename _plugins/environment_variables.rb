module Jekyll
  class EnvironmentVariablesGenerator < Generator
    priority :highest

    def generate(site)
      if ENV.key?('JEKYLL_URL')
        site.config['url'] = ENV['JEKYLL_URL']
      end
    end
  end
end
