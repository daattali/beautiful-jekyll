#Jekyll-Photo-Gallery generates a HTML page for every photo specified in _data/photos.yaml
#Author: Theo Winter (https://github.com/aerobless)

module Jekyll
  class PhotoPage < Page
    def initialize(site, base, dir, photo_url, previous_pic, next_pic, title, description)
      @site = site
      @base = base
      @dir = dir
      @name = 'index.html'

      self.process(@name)
      self.read_yaml(File.join(base, '_layouts'), 'photo.html')
      self.data['photo_url'] = photo_url
      self.data['previous_pic'] = previous_pic
      self.data['next_pic'] = next_pic
      self.data['title'] = title
      self.data['description'] = description
      self.data['comments'] = true
    end
  end

  class PhotoList < Page
    def initialize(site, base, dir, photolist, title)
      @site = site
      @base = base
      @dir = dir
      @name = 'index.html'

      self.process(@name)
      self.read_yaml(File.join(base, '_layouts'), 'photoIndex.html')
      self.data['photolist'] = photolist
      self.data['title'] = title
    end
  end

  class PhotoPageGenerator < Generator
    safe true

    def generate(site)
      photos = YAML::load_file('_data/photos.yaml')
      dir = site.config['photo_dir'] || 'photography'

      site.pages << PhotoList.new(site, site.source, File.join(dir), photos["photos"], "Photography")

      #Reference in site, used for sitemap
      photoSlugs = Array.new

      photos.each do |photo,details|
        #Iterate through array & return previous, current & next
        [nil, *details, nil].each_cons(3){|prev, curr, nxt|
          photo_url = curr["img"]
          title = curr["title"]
          description = curr["description"]
          title_stub = title.strip.gsub(' ', '-').gsub(/[^\w-]/, '') #remove non-alpha and replace spaces with hyphens
          if(prev != nil)
            previous_pic = prev["title"].strip.gsub(' ', '-').gsub(/[^\w-]/, '')
          else
            previous_pic = ""
          end
          if(nxt != nil)
            next_pic = nxt["title"].strip.gsub(' ', '-').gsub(/[^\w-]/, '')
          else
            next_pic = ""
          end
          photoSlugs << photo_url
          site.pages << PhotoPage.new(site, site.source, File.join(dir, title_stub), photo_url, previous_pic, next_pic, title, description)
        }
      end
      site.data['photoSlugs'] = photoSlugs

      #Create a array containing all countries
      countryArray = Array.new
      photos.each do |photo,details|
        [nil, *details, nil].each_cons(3){|prev, curr, nxt|
          photoCountry = curr["country"]
          countryArray.push(photoCountry)
        }
      end
      countryArray = countryArray.uniq

      countryArray.each do |name|
        photosPerCountry = Array.new
        countrySlug = name.strip.gsub(' ', '-').gsub(/[^\w-]/, '')
        photos.each do |photo, details|
          [nil, *details, nil].each_cons(3){|prev, curr, nxt|
            if(curr["country"] == name)
              photosPerCountry.push(curr)
            end
          }
        end

        #Make page
        site.pages << PhotoList.new(site, site.source, File.join('photography', countrySlug), photosPerCountry, name)
      end
    end
  end
end

module TextFilter
  def toStub(input)
    input.strip.gsub(' ', '-').gsub(/[^\w-]/, '')
  end
end

Liquid::Template.register_filter(TextFilter)

module Jekyll
  class IncludeGalleryTag < Liquid::Tag

    def initialize(tag_name, text, tokens)
      super
      @result = '<div id="gallery" style="display:none; margin-bottom: 20px;">'
      photos = YAML::load_file('_data/photos.yaml')
      photos.each do |photo, details|
        [nil, *details, nil].each_cons(3){|prev, curr, nxt|
          if(curr["album"] == text.strip)
            @result = @result+'<div itemscope itemtype="http://schema.org/Photograph">
                                      <a itemprop="image" class="swipebox" title="'+curr["title"]+'" href="/photography/'+curr["title"].strip.gsub(' ', '-').gsub(/[^\w-]/, '')+'/">
                                        <img alt="'+curr["title"]+'" itemprop="thumbnailUrl" src="/images/photography/thumbnails/'+curr["img"]+'.jpg"/>
                                        <meta itemprop="name" content="'+curr["title"]+'" />
                                        <meta itemprop="isFamilyFriendly" content="true" />
                                        <div itemprop="creator" itemscope itemtype="http://schema.org/Person">
                                          <div itemprop="sameAs" href="http://theowinter.ch/about">
                                            <meta itemprop="name" content="Theo Winter"/>
                                          </div>
                                        </div>
                                      </a>
                                    </div>'
          end
        }
      end
      @result = @result + '</div>'

      #If you want to configure each album gallery individually you can remove this script
      #and add it in the template/post directly.
      @result = @result + '<script>
                              window.onload=function(){
                                  $("#gallery").justifiedGallery({
                                      rowHeight : 220,
                                      maxRowHeight: 340,
                                      margins : 5,
                                      border : 0,
                                      fixedHeight: false,
                                      lastRow : \'nojustify\',
                                      captions: true
                                  });
                                  $("#gallery").fadeIn(500);
                              }
                          </script>'
    end

    def render(context)
      "#{@result}"
    end
  end
end
Liquid::Template.register_tag('includeGallery', Jekyll::IncludeGalleryTag)
