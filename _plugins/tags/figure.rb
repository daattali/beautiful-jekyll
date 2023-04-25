require 'json'

module Jekyll
  class RenderFigureTag < Liquid::Tag

    def initialize(tag_name, input, tokens)
      super
      @input = input
    end

    def render(context)
      output = "<figure>"

      image = ""
      alt = ""
      classes = ""
      width = ""
      height = ""
      caption = ""

      begin
        if( !@input.nil? && !@input.empty? )
            jdata = JSON.parse(@input)
            if( jdata.key?("image") )
              image = jdata["image"].strip
              output += "<img src=\"" + image + "\""
            
              if( jdata.key?("alt") )
                alt = jdata["alt"].strip
                output += " alt=\"" + alt + "\""
              end
              if( jdata.key?("classes") )
                classes = jdata["classes"].strip
                output += " class=\"" + classes + "\""
              end
              if( jdata.key?("width") )
                width = jdata["width"].strip
                output += " width=\"" + width + "\""
              end
              if( jdata.key?("height") )
                height = jdata["height"].strip
                output += " height=\"" + height + "\""
              end
              output += ">"
            end

            if( jdata.key?("caption") )
              caption = jdata["caption"].strip
              output += "<figcaption>" + caption + "</figcaption>"
            end
        end
      rescue
      end

      output += "</figure>"

      return output
    end
  end
end

Liquid::Template.register_tag('figure', Jekyll::RenderFigureTag)
