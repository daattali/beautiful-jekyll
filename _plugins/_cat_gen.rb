module Jekyll
    class CatIndex < Page
      def initialize(site, base, dir, cat)
        @site = site
        @base = base
        @dir = dir
        @name = 'index.html'
        self.process(@name)
        self.read_yaml(File.join(base, '_layouts'), 'cat_index.html')
        self.data['cat'] = cat
     end
    end
    class CatGenerator < Generator
      safe true
      def generate(site)
        if site.layouts.key? 'cat_index'
          dir = 'blog/categories'
          site.categories.keys.each do |cat|
            write_cat_index(site, File.join(dir, cat), cat)
          end
        end
      end
      def write_cat_index(site, dir, cat)
        index = CatIndex.new(site, site.source, dir, cat)
        index.render(site.layouts, site.site_payload)
        index.write(site.dest)
        site.pages << index
      end
    end
  end