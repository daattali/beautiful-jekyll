require 'exifr/jpeg'

#Based on https://github.com/benib/jekyll-exiftag by Beni Buess (MIT License)
#Edited to work as a Liquid-Block instead of a Liquid-Tag, reads the filename from between the
#brackets. --T.Winter

module Jekyll
  class ExifTag < Liquid::Block

    def initialize(tag_name, params, token)
      super
      @args = self.split_params(params)
    end

    def render(context)
      #abort context.registers[:site].config['source'].inspect
      sources = Array.new(context.registers[:site].config['exiftag']['sources'])
      # first param is the exif tag
      tag = @args[0]

      # if a second parameter is passed, use it as a possible img source
      if @args.count > 1
        sources.unshift(@args[1])
      end

      # the image can be passed as the third parameter
      img = super

      # first check if the given img is already the path
      if File.exist?(img)
        file_name = img
      else
      # then start testing with the sources from _config.yml
        begin
          source = sources.shift
          file_name = File.join(context.registers[:site].config['source'], source, img)
        end until File.exist?(file_name) or sources.count == 0
      end
      # try it and return empty string on failure
      begin
        exif = EXIFR::JPEG::new(file_name)
        return tag.split('.').inject(exif){|o,m| o.send(m)}
      rescue
        "ERROR, EXIF-Tag RB"
      end
    end

    def split_params(params)
      params.split(",").map(&:strip)
    end
  end
end

Liquid::Template.register_tag('exiftag', Jekyll::ExifTag)
